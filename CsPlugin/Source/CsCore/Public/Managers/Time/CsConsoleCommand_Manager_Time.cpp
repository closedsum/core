// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Time/CsConsoleCommand_Manager_Time.h"
#include "CsCore.h"

// Library
#include "Managers/Time/CsLibrary_Manager_Time.h"
#include "ConsoleCommand/CsLibrary_ConsoleCommand.h"
#include "Library/CsLibrary_String.h"
#include "Library/CsLibrary_Valid.h"
// Utility
#include "Utility/CsLog.h"
// Coordinators
#include "Coordinators/ConsoleCommand/CsCoordinator_ConsoleCommand.h"

namespace NCsTime
{
	namespace NManager
	{
		namespace NConsoleCommand
		{
			namespace NCached
			{
				namespace Str
				{
					CSCORE_API const FString CategoryName = TEXT("Manager_Time");

					CS_DEFINE_FUNCTION_NAME_AS_STRING(NCsTime::NManager::FConsoleCommand, Exec_Pause);
					CS_DEFINE_FUNCTION_NAME_AS_STRING(NCsTime::NManager::FConsoleCommand, Exec_Unpause);
					CS_DEFINE_FUNCTION_NAME_AS_STRING(NCsTime::NManager::FConsoleCommand, Exec_CustomUpdate);
					
					const FString UpdateGroup = TEXT("UpdateGroup");
					const FString DeltaTime = TEXT("DeltaTime");
				}
			}
		}

		// Enum
		#pragma region

		// FConsoleCommqzand::ECommand
		#define CS_TEMP_ADD_TO_ENUM_MAP(EnumElementName) const FConsoleCommand::ECommand FConsoleCommand::NCommand::EnumElementName = FConsoleCommand::EMCommand::Get().Add(FConsoleCommand::ECommand::EnumElementName, #EnumElementName)

		CS_TEMP_ADD_TO_ENUM_MAP(Pause);

		#undef CS_TEMP_ADD_TO_ENUM_MAP

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

				// Pause
				{
					CommandInfos.AddDefaulted();
					InfoType& Info = CommandInfos.Last();

					Info.PrimaryDefinitionIndex = 1;

					// Params
					{
						typedef NCsConsoleCommand::NParam::FInfo ParamInfoType;
						typedef NCsConsoleCommand::NParam::EValue ParamValueType;

						TArray<ParamInfoType>& ParamInfos = Info.ParamInfos;

						ParamInfos.AddDefaulted(1);

						// UpdateGroup
						{
							static const int32 UPDATE_GROUP = 0;
							ParamInfoType& ParamInfo = ParamInfos[UPDATE_GROUP];

							ParamInfo.SetEnumStruct<EMCsUpdateGroup, FECsUpdateGroup>(TEXT("UpdateGroup"));
						}
					}

					TArray<FString> Base;
					Base.Add(TEXT("ManagerTimePause"));
					Base.Add(TEXT("ManagerTime Pause"));
					Base.Add(TEXT("Manager Time Pause"));

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
							Definitions.Add(Str + TEXT(" [UpdateGroup]"));
						}
					}
					// Description
					{
						FString& Description = Info.Description;
						Description += TEXT("Call the command Pause.\n");
						Description += TEXT("- Checks for the following console commands:\n");

						for (FString& Str : Info.Definitions)
						{
							Description += TEXT("-- ") + Str + TEXT("\n");
						}

						Description += TEXT("\n");
						Description += TEXT("[UpdateGroup] = The Update Group to pause.");
					}
				}
				// Unpause
				{
					CommandInfos.AddDefaulted();
					InfoType& Info = CommandInfos.Last();

					Info.PrimaryDefinitionIndex = 1;

					// Params
					{
						typedef NCsConsoleCommand::NParam::FInfo ParamInfoType;
						typedef NCsConsoleCommand::NParam::EValue ParamValueType;

						TArray<ParamInfoType>& ParamInfos = Info.ParamInfos;

						ParamInfos.AddDefaulted(1);

						// UpdateGroup
						{
							static const int32 UPDATE_GROUP = 0;
							ParamInfoType& ParamInfo = ParamInfos[UPDATE_GROUP];

							ParamInfo.SetEnumStruct<EMCsUpdateGroup, FECsUpdateGroup>(TEXT("UpdateGroup"));
						}
					}

					TArray<FString> Base;
					Base.Add(TEXT("ManagerTimeUnpause"));
					Base.Add(TEXT("ManagerTime Unpause"));
					Base.Add(TEXT("Manager Time Unpause"));

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
							Definitions.Add(Str + TEXT(" [UpdateGroup]"));
						}
					}
					// Description
					{
						FString& Description = Info.Description;
						Description += TEXT("Call the command Pause.\n");
						Description += TEXT("- Checks for the following console commands:\n");

						for (FString& Str : Info.Definitions)
						{
							Description += TEXT("-- ") + Str + TEXT("\n");
						}

						Description += TEXT("\n");
						Description += TEXT("[UpdateGroup] = The Update Group to unpause.");
					}
				}
				// CustomUpdate
				{
					CommandInfos.AddDefaulted();
					InfoType& Info = CommandInfos.Last();

					Info.PrimaryDefinitionIndex = 1;

					// Params
					{
						typedef NCsConsoleCommand::NParam::FInfo ParamInfoType;
						typedef NCsConsoleCommand::NParam::EValue ParamValueType;

						TArray<ParamInfoType>& ParamInfos = Info.ParamInfos;

						ParamInfos.AddDefaulted(2);

						// UpdateGroup
						{
							static const int32 UPDATE_GROUP = 0;
							ParamInfoType& ParamInfo = ParamInfos[UPDATE_GROUP];

							ParamInfo.SetEnumStruct<EMCsUpdateGroup, FECsUpdateGroup>(TEXT("UpdateGroup"));
						}
						// DeltaTime
						{
							static const int32 DELTA_TIME = 1;
							ParamInfoType& ParamInfo = ParamInfos[DELTA_TIME];

							ParamInfo.SetFloatMinOnly(TEXT("DeltaTime"), 0.01667f, 0.0001f);
						}
					}

					TArray<FString> Base;
					Base.Add(TEXT("ManagerTimeCustomUpdate"));
					Base.Add(TEXT("ManagerTime CustomUpdate"));
					Base.Add(TEXT("Manager Time CustomUpdate"));

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
							Definitions.Add(Str + TEXT(" [UpdateGroup] [DeltaTime]"));
						}
					}
					// Description
					{
						FString& Description = Info.Description;
						Description += TEXT("Call the command CustomUpdate.\n");
						Description += TEXT("- Checks for the following console commands:\n");

						for (FString& Str : Info.Definitions)
						{
							Description += TEXT("-- ") + Str + TEXT("\n");
						}

						Description += TEXT("\n");
						Description += TEXT("[UpdateGroup] = The Update Group to unpause.\n");
						Description += TEXT("[DeltaTime]   = Number > 0.0f.");
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
			// ManagerTimePause [UpdateGroup]
			// ManagerTime Pause [UpdateGroup]
			// Manager Time Pause [UpdateGroup]
			if (Exec_Pause(Cmd))
				return true;
			// ManagerTimeUnpause [UpdateGroup]
			// ManagerTime Unpause [UpdateGroup]
			// Manager Time Unpause [UpdateGroup]
			if (Exec_Unpause(Cmd))
				return true;
			// ManagerTimeCustomUpdate [UpdateGroup] [DeltaTime]
			// ManagerTime CustomUpdate [UpdateGroup] [DeltaTime]
			// Manager Time CustomUpdate [UpdateGroup] [DeltaTime]
			if (Exec_CustomUpdate(Cmd))
				return true;
			return false;
		}

		#pragma endregion ConsoleCommandManagerType (NCsConsoleCommand::NManager::IManager)

		bool FConsoleCommand::GetUpdateGroup(const FString& Context, const TCHAR*& Str, FECsUpdateGroup& OutValue, const FString& Definition)
		{
			typedef NCsConsoleCommand::NLibrary::FLibrary ConsoleCommandLibrary;

			return ConsoleCommandLibrary::GetEnumStruct<EMCsUpdateGroup, FECsUpdateGroup>(Context, Str, OutValue, NConsoleCommand::NCached::Str::UpdateGroup, Definition, &FCsLog::Warning);
		}

		bool FConsoleCommand::GetUpdateGroupAndAdvance(const FString& Context, const TCHAR*& StrAsChar, FString& Str, FECsUpdateGroup& OutValue, const FString& Definition)
		{
			if (!GetUpdateGroup(Context, StrAsChar, OutValue, Definition))
				return false;

			// Remove blank space ' '
			typedef NCsConsoleCommand::NLibrary::FLibrary ConsoleCommandLibrary;

			if (!ConsoleCommandLibrary::ConsumeNextCharAndCheckNotEmpty(Context, Str, Definition))
				return false;
			return true;
		}

		bool FConsoleCommand::GetDeltaTime(const FString& Context, const TCHAR*& Str, float& OutValue, const FString& Definition)
		{
			typedef NCsConsoleCommand::NLibrary::FParams_GetValue_float ParamsType;

			ParamsType Params;
			Params.OutValue	  = &OutValue;
			Params.CheckType  = ParamsType::ECheck::GreaterThan;
			Params.Value	  = 0.0f;
			Params.ValueName  = const_cast<FString*>(&NConsoleCommand::NCached::Str::DeltaTime);
			Params.Definition = const_cast<FString*>(&Definition);
			Params.Log		  = &FCsLog::Warning;

			typedef NCsConsoleCommand::NLibrary::FLibrary ConsoleCommandLibrary;

			return ConsoleCommandLibrary::Stream_GetValue<ParamsType>(Context, Str, Params);
		}

		bool FConsoleCommand::Exec_Pause(const TCHAR* Cmd)
		{
			using namespace NConsoleCommand::NCached;

			const FString& Context = Str::Exec_Pause;

			void(*Log)(const FString&) = &FCsLog::Warning;

			FString OutString;
			FParse::Line(&Cmd, OutString, true);

			OutString = OutString.ToLower();

			const TArray<FString>& Commands	   = CommandInfos[(uint8)ECommand::Pause].Commands;
			const TArray<FString>& Definitions = CommandInfos[(uint8)ECommand::Pause].Definitions;

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

					// Get UpdateGroup
					FECsUpdateGroup UpdateGroup;
					
					if (!GetUpdateGroup(Context, StrAsChar, UpdateGroup, Definition))
						return false;

					CS_IS_PTR_NULL(MyRoot)

					typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

					TimeManagerLibrary::SafePause(Context, MyRoot, UpdateGroup);

					return true;
				}
			}
			return false;
		}

		bool FConsoleCommand::Exec_Unpause(const TCHAR* Cmd)
		{
			using namespace NConsoleCommand::NCached;

			const FString& Context = Str::Exec_Unpause;

			void(*Log)(const FString&) = &FCsLog::Warning;

			FString OutString;
			FParse::Line(&Cmd, OutString, true);

			OutString = OutString.ToLower();

			const TArray<FString>& Commands	   = CommandInfos[(uint8)ECommand::Unpause].Commands;
			const TArray<FString>& Definitions = CommandInfos[(uint8)ECommand::Unpause].Definitions;

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

					// Get UpdateGroup
					FECsUpdateGroup UpdateGroup;
					
					if (!GetUpdateGroup(Context, StrAsChar, UpdateGroup, Definition))
						return false;

					CS_IS_PTR_NULL(MyRoot)

					typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

					TimeManagerLibrary::SafeUnpause(Context, MyRoot, UpdateGroup);

					return true;
				}
			}
			return false;
		}

		bool FConsoleCommand::Exec_CustomUpdate(const TCHAR* Cmd)
		{
			using namespace NConsoleCommand::NCached;

			const FString& Context = Str::Exec_CustomUpdate;

			void(*Log)(const FString&) = &FCsLog::Warning;

			FString OutString;
			FParse::Line(&Cmd, OutString, true);

			OutString = OutString.ToLower();

			const TArray<FString>& Commands	   = CommandInfos[(uint8)ECommand::CustomUpdate].Commands;
			const TArray<FString>& Definitions = CommandInfos[(uint8)ECommand::CustomUpdate].Definitions;

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

					// Get UpdateGroup
					FECsUpdateGroup UpdateGroup;
					
					if (!GetUpdateGroupAndAdvance(Context, StrAsChar, OutString, UpdateGroup, Definition))
						return false;

					// Get DeltaTime
					float DeltaTime;

					if (!GetDeltaTime(Context, StrAsChar, DeltaTime, Definition))
						return false;

					CS_IS_PTR_NULL(MyRoot)

					typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

					TimeManagerLibrary::SetSafeCustomUpdate(Context, MyRoot, UpdateGroup, DeltaTime, true);

					return true;
				}
			}
			return false;
		}
	}
}