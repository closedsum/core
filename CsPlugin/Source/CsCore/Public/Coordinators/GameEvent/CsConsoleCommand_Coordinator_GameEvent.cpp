// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
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

					// Commands
					{
						TArray<FString>& Commands = Info.Commands;
						Commands.Add(TEXT("broadcastgameevent"));
						Commands.Add(TEXT("broadcast gameevent"));
						Commands.Add(TEXT("broadcast game event"));
					}
					// Definitions
					{
						TArray<FString>& Definitions = Info.Definitions;
						Definitions.Add(TEXT("BroadcastGameEvent [Group] [GameEvent] [Value(optional | default = 0)] [Location(optional | default = X = 0Y = 0Z = 0)]"));
						Definitions.Add(TEXT("Broadcast GameEvent [Group] [GameEvent] [Value(optional | default = 0)] [Location(optional | default = X = 0Y = 0Z = 0)]"));
						Definitions.Add(TEXT("Broadcast Game Event [Group] [GameEvent] [Value(optional | default = 0)] [Location(optional | default = X = 0Y = 0Z = 0)]"));
					}
					// Description
					{
						FString& Description = Info.Description;
						Description += TEXT("Call the command BroadcastGameEvent.\n");
						Description += TEXT("- Checks for the following console commands:\n");
						Description += TEXT("-- BroadcastGameEvent [Group] [GameEvent] [Value (optional|default=0)] [Location (optional|default=X=0Y=0Z=0)]\n");
						Description += TEXT("-- BroadcastGameEvent [Group] [GameEvent] [Location (optional|default=X=0Y=0Z=0)]\n");
						Description += TEXT("-- Broadcast GameEvent [Group] [GameEvent] [Value (optional|default=0)] [Location (optional|default=X=0Y=0Z=0)]\n");
						Description += TEXT("-- Broadcast GameEvent [Group] [GameEvent] [Location (optional|default=X=0Y=0Z=0)]\n");
						Description += TEXT("-- Broadcast Game Event [Group] [GameEvent] [Value (optional|default=0)] [Location (optional|default=X=0Y=0Z=0)]\n");
						Description += TEXT("-- Broadcast Game Event [Group] [GameEvent] [Location (optional|default=X=0Y=0Z=0)]\n");
						Description += TEXT("\n");
						Description += TEXT("[Group]	  = The route / 'group' to direct the GameEvent. See FECsGameEventCoordinatorGroup.\n");
						Description += TEXT("[GameEvent] = The type of GameEvent. See FECsGameEvent.\n");
						Description += TEXT("[Value]	  = Optional float value. Defaults to 0.0f.");
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

		bool FConsoleCommand::GetGameEvent(const FString& Context, const TCHAR*& Str, FECsGameEvent& OutValue, const FString& Definition)
		{
			typedef NCsConsoleCommand::NLibrary::FLibrary ConsoleCommandLibrary;
			typedef EMCsGameEvent _EnumMapType;
			typedef FECsGameEvent EnumType;

			const FString& EnumName = NConsoleCommand::NCached::Str::GameEvent;

			return ConsoleCommandLibrary::GetEnumStruct<_EnumMapType, EnumType>(Context, Str, OutValue, EnumName, Definition, &FCsLog::Warning);
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

					if (!GetGameEventCoordinatorGroup(Context, StrAsChar, Group, Definition))
						return false;

					// Remove blank space ' '
					if (!ConsoleCommandLibrary::ConsumeNextCharAndCheckNotEmpty(Context, OutString, Definition))
						return false;

					// Get GameEvent
					FECsGameEvent GameEvent;
					
					if (!GetGameEvent(Context, StrAsChar, GameEvent, Definition))
						return false;

					// Remove blank space ' '
					if (!ConsoleCommandLibrary::ConsumeNextCharAndCheckNotEmpty(Context, OutString, Definition))
						return false;

					// TODO: Look into Queueing GameEvent so its processing inlined with other events

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