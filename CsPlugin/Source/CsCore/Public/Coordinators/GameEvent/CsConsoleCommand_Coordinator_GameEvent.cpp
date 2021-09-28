// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
#include "Coordinators/GameEvent/CsConsoleCommand_Coordinator_GameEvent.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_String.h"
#include "ConsoleCommand/CsLibrary_ConsoleCommand.h"
#include "Coordinators/GameEvent/CsLibrary_Coordinator_GameEvent.h"
// Utility
#include "Utility/CsLog.h"
// Coordinators
#include "Coordinators/ConsoleCommand/CsCoordinator_ConsoleCommand.h"

namespace NCsGameEvent
{
	namespace NCoordinator
	{
		namespace NConsoleCommand
		{
			namespace NCached
			{
				namespace Str
				{
					CSCORE_API const FString CategoryName = TEXT("Coordinator_GameEvent");

					CS_DEFINE_FUNCTION_NAME_AS_STRING(NCsGameEvent::NCoordinator::FConsoleCommand, Exec_BroadcastGameEvent);
					
					const FString GameEventCoordinatorGroup = TEXT("GameEventCoordinatorGroup");
					const FString GameEvent = TEXT("GameEvent");
					const FString Value = TEXT("Value");
					const FString Location = TEXT("Location");
				}
			}
		}

		// Enum
		#pragma region

		// FConsoleCommand::ECommand
		#define CS_TENP_ADD_TO_ENUM_MAP(EnumElementName) const FConsoleCommand::ECommand FConsoleCommand::NCommand::EnumElementName = FConsoleCommand::EMCommand::Get().Add(FConsoleCommand::ECommand::EnumElementName, #EnumElementName)

		CS_TENP_ADD_TO_ENUM_MAP(BroadcastGameEvent);

		#undef CS_TENP_ADD_TO_ENUM_MAP

		#pragma endregion Enum

		FConsoleCommand::FConsoleCommand(UObject* InRoot)
		{
			MyRoot = InRoot;

			UCsCoordinator_ConsoleCommand* Coordinator_ConsoleCommand = UCsCoordinator_ConsoleCommand::Get(MyRoot);
			Handle = Coordinator_ConsoleCommand->AddManager(this);

			OnDeconstruct_Event.BindUObject(Coordinator_ConsoleCommand, &UCsCoordinator_ConsoleCommand::OnDeconstructManager);

			typedef NCsConsoleCommand::FInfo InfoType;

			CommandInfos.Reset();

			// Populate CommandInfos
			{
				const int32& Count = EMCommand::Get().Num();

				CommandInfos.Reserve(Count);

				// Spawn
				{
					CommandInfos.AddDefaulted();
					InfoType& Info = CommandInfos.Last();

					Info.PrimaryDefinitionIndex = 1;

					// Params
					{
						typedef NCsConsoleCommand::NParam::FInfo ParamInfoType;
						typedef NCsConsoleCommand::NParam::EValue ParamValueType;

						TArray<ParamInfoType>& ParamInfos = Info.ParamInfos;

						ParamInfos.AddDefaulted(4);

						// Group
						{
							static const int32 GROUP = 0;
							ParamInfoType& ParamInfo = ParamInfos[GROUP];

							ParamInfo.SetEnumStruct<EMCsGameEventCoordinatorGroup, FECsGameEventCoordinatorGroup>(TEXT("Group"));
						}
						// GameEvent
						{
							static const int32 GAME_EVENT = 1;
							ParamInfoType& ParamInfo = ParamInfos[GAME_EVENT];

							ParamInfo.SetEnumStruct<EMCsGameEvent, FECsGameEvent>(TEXT("GameEvent"));
						}
						// Value
						{
							static const int32 VALUE = 2;
							ParamInfoType& ParamInfo = ParamInfos[VALUE];

							ParamInfo.SetInteger(TEXT("Value"), 0.0f);
						}
						// Location
						{
							static const int32 LOCATION = 3;
							ParamInfoType& ParamInfo = ParamInfos[LOCATION];

							ParamInfo.SetString(TEXT("Location"));
						}
					}

					TArray<FString> Base;
					Base.Add(TEXT("BroadcastGameEvent"));
					Base.Add(TEXT("Broadcast GameEvent"));
					Base.Add(TEXT("Broadcast Game Event"));

					// Commands
					{
						TArray<FString>& Commands = Info.Commands;
						Commands.Reset(Base.Num());

						for (FString& Str : Base)
						{
							Commands.Add(Str.ToLower());
						}
					}
					// Definitions
					{
						TArray<FString>& Definitions = Info.Definitions;
						Definitions.Reset(Base.Num());

						for (FString& Str : Base)
						{
							Definitions.Add(Str + TEXT(" [Group] [GameEvent] [Value(optional|default=0)] [Location(optional|default=X=0Y=0Z=0)]"));
						}
					}
					// Description
					{
						FString& Description = Info.Description;
						Description += TEXT("Call the command BroadcastGameEvent.\n");
						Description += TEXT("- Checks for the following console commands:\n");

						for (FString& Str : Info.Definitions)
						{
							Description += TEXT("-- ") + Str + TEXT("\n");
						}

						Description += TEXT("\n");
						Description += TEXT("[Group]	  = The route / 'group' to direct the GameEvent. See FECsGameEventCoordinatorGroup.\n");
						Description += TEXT("[GameEvent] = The type of GameEvent. See FECsGameEvent.\n");
						Description += TEXT("[Value]	  = Optional float value. Defaults to 0.0f.\n");
						Description += TEXT("[Location]  = Optional FVector value. Defaults to FVector::ZeroVector or FVector(0.0f, 0.0f, 0.0f).");
					}
				}
			}
		}

		FConsoleCommand::~FConsoleCommand()
		{
			OnDeconstruct_Event.Execute(this, Handle);
		}

		// ConsoleCommandManagerType (NCsConsoleCommand::NManager::IManager)
		#pragma region

		bool FConsoleCommand::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out /*=*GLog*/)
		{
			// BroadcastGameEvent [Group] [GameEvent] [Value(optional | default = 0)] [Location(optional | default = X = 0Y = 0Z = 0)]
			// BroadcastGameEvent [Group] [GameEvent] [Location(optional | default = X = 0Y = 0Z = 0)]
			// Broadcast GameEvent [Group] [GameEvent] [Value(optional | default = 0)] [Location(optional | default = X = 0Y = 0Z = 0)]
			// Broadcast GameEvent [Group] [GameEvent] [Location(optional | default = X = 0Y = 0Z = 0)]
			// Broadcast Game Event [Group] [GameEvent] [Value(optional | default = 0)] [Location(optional | default = X = 0Y = 0Z = 0)]
			// Broadcast Game Event [Group] [GameEvent] [Location(optional | default = X = 0Y = 0Z = 0)]
			if (Exec_BroadcastGameEvent(Cmd))
				return true;
			return false;
		}

		#pragma endregion ConsoleCommandManagerType (NCsConsoleCommand::NManager::IManager)

		bool FConsoleCommand::GetGameEventCoordinatorGroup(const FString& Context, const TCHAR*& Str, FECsGameEventCoordinatorGroup& OutValue, const FString& Definition)
		{
			typedef NCsConsoleCommand::NLibrary::FLibrary ConsoleCommandLibrary;
			typedef EMCsGameEventCoordinatorGroup _EnumMapType;
			typedef FECsGameEventCoordinatorGroup EnumType;

			const FString& EnumName = NConsoleCommand::NCached::Str::GameEventCoordinatorGroup;

			return ConsoleCommandLibrary::GetEnumStruct<_EnumMapType, EnumType>(Context, Str, OutValue, EnumName, Definition, &FCsLog::Warning);
		}

		bool FConsoleCommand::GetGameEventCoordinatorGroupAndAdvance(const FString& Context, const TCHAR*& StrAsChar, FString& Str, FECsGameEventCoordinatorGroup& OutValue, const FString& Definition)
		{
			if (!GetGameEventCoordinatorGroup(Context, StrAsChar, OutValue, Definition))
				return false;

			// Remove blank space ' '
			typedef NCsConsoleCommand::NLibrary::FLibrary ConsoleCommandLibrary;

			if (!ConsoleCommandLibrary::ConsumeNextCharAndCheckNotEmpty(Context, Str, Definition))
				return false;
			return true;
		}

		bool FConsoleCommand::GetGameEvent(const FString& Context, const TCHAR*& Str, FECsGameEvent& OutValue, const FString& Definition)
		{
			typedef NCsConsoleCommand::NLibrary::FLibrary ConsoleCommandLibrary;
			typedef EMCsGameEvent _EnumMapType;
			typedef FECsGameEvent EnumType;

			const FString& EnumName = NConsoleCommand::NCached::Str::GameEvent;

			return ConsoleCommandLibrary::GetEnumStruct<_EnumMapType, EnumType>(Context, Str, OutValue, EnumName, Definition, &FCsLog::Warning);
		}

		bool FConsoleCommand::GetGameEventAndAdvance(const FString& Context, const TCHAR*& StrAsChar, FString& Str, FECsGameEvent& OutValue, const FString& Definition)
		{
			if (!GetGameEvent(Context, StrAsChar, OutValue, Definition))
				return false;

			// Remove blank space ' '
			typedef NCsConsoleCommand::NLibrary::FLibrary ConsoleCommandLibrary;

			if (!ConsoleCommandLibrary::ConsumeNextCharAndCheckNotEmpty(Context, Str, Definition))
				return false;
			return true;
		}

		bool FConsoleCommand::GetValue(const FString& Context, const TCHAR*& Str, float& OutValue, const FString& Definition)
		{
			typedef NCsConsoleCommand::NLibrary::FParams_GetValue_float ParamsType;

			ParamsType Params;
			Params.OutValue	  = &OutValue;
			Params.ValueName  = const_cast<FString*>(&NConsoleCommand::NCached::Str::Value);
			Params.Definition = const_cast<FString*>(&Definition);

			typedef NCsConsoleCommand::NLibrary::FLibrary ConsoleCommandLibrary;

			return ConsoleCommandLibrary::Stream_GetValue<ParamsType>(Context, Str, Params);
		}

		bool FConsoleCommand::GetLocation(const FString& Context, const TCHAR*& Str, FVector& OutLocation, const FString& Definition)
		{
			typedef NCsConsoleCommand::NLibrary::FParams_GetValue_Vector ParamsType;

			ParamsType Params;
			Params.OutValue	  = &OutLocation;
			Params.ValueName  = const_cast<FString*>(&NConsoleCommand::NCached::Str::Location);
			Params.Definition = const_cast<FString*>(&Definition);

			typedef NCsConsoleCommand::NLibrary::FLibrary ConsoleCommandLibrary;

			return ConsoleCommandLibrary::Stream_GetValue<ParamsType>(Context, Str, Params);
		}

		bool FConsoleCommand::Exec_BroadcastGameEvent(const TCHAR* Cmd)
		{
			using namespace NConsoleCommand::NCached;

			const FString& Context = Str::Exec_BroadcastGameEvent;

			FString OutString;
			FParse::Line(&Cmd, OutString, true);

			OutString.ToLower();

			const TArray<FString>& Commands	   = CommandInfos[(uint8)ECommand::BroadcastGameEvent].Commands;
			const TArray<FString>& Definitions = CommandInfos[(uint8)ECommand::BroadcastGameEvent].Definitions;

			const int32 Count = Commands.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FString& Command	  = Commands[I];
				const FString& Definition = Definitions[I];

				if (OutString.RemoveFromStart(Command))
				{
					if (OutString.IsEmpty())
					{
						UE_LOG(LogCs, Warning, TEXT("%s: Command: %s."), *Context, *Definition);
						return false;
					}

					typedef NCsConsoleCommand::NLibrary::FLibrary ConsoleCommandLibrary;

					// Remove blank space ' '
					if (!ConsoleCommandLibrary::ConsumeNextCharAndCheckNotEmpty(Context, OutString, Definition))
						return false;

					const TCHAR* StrAsChar = *OutString;

					// Get GameEventCoordinatorGroup
					FECsGameEventCoordinatorGroup Group;

					if (!GetGameEventCoordinatorGroupAndAdvance(Context, StrAsChar, OutString, Group, Definition))
						return false;

					// Get GameEvent
					FECsGameEvent GameEvent;
					
					if (!GetGameEventAndAdvance(Context, StrAsChar, OutString, GameEvent, Definition))
						return false;

					// TODO: Look into Queuing GameEvent so its processing inline with other events

					typedef NCsGameEvent::NCoordinator::FLibrary GameEventCoordinatorLibrary;

					// Try Get Location
					{
						FVector Location = FVector::ZeroVector;

						if (GetLocation(Context, StrAsChar, Location, Definition))
						{
							GameEventCoordinatorLibrary::SafeBroadcastGameEvent(Context, MyRoot, Group, GameEvent, 0.0f, Location, &FCsLog::Warning);
							return true;
						}
					}

					// Try Get Value then Try Get Location
					{
						// Try Get Value
						float Value = 0.0f;

						if (GetValue(Context, StrAsChar, Value, Definition))
						{
							// Remove blank space ' '
							if (ConsoleCommandLibrary::ConsumeNextCharAndCheckNotEmpty(Context, OutString, Definition))
							{
								// Try Get Location
								FVector Location = FVector::ZeroVector;
							
								if (GetLocation(Context, StrAsChar, Location, Definition))
								{
									GameEventCoordinatorLibrary::SafeBroadcastGameEvent(Context, MyRoot, Group, GameEvent, Value, Location, &FCsLog::Warning);
									return true;
								}
							}
							GameEventCoordinatorLibrary::SafeBroadcastGameEvent(Context, MyRoot, Group, GameEvent, Value, FVector::ZeroVector, &FCsLog::Warning);
							return true;
						}
					}

					GameEventCoordinatorLibrary::SafeBroadcastGameEvent(Context, MyRoot, Group, GameEvent, 0.0f, FVector::ZeroVector, &FCsLog::Warning);
					return true;
				}
			}
			return false;
		}
	}
}