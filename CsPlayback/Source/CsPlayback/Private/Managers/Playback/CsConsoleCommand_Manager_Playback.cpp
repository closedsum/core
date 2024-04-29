// Copyright 2017-2024 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Playback/CsConsoleCommand_Manager_Playback.h"
#include "CsPlayback.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_String.h"
#include "ConsoleCommand/CsLibrary_ConsoleCommand.h"
#include "Library/CsLibrary_Valid.h"
#include "Managers/Playback/CsLibrary_Manager_Playback.h"
// Utility
#include "Utility/CsPlaybackLog.h"
// Coordinators
#include "Coordinators/ConsoleCommand/CsCoordinator_ConsoleCommand.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

namespace NCsPlayback
{
	namespace NManager
	{
		namespace NConsoleCommand
		{
			namespace NCached
			{
				namespace Str
				{
					CSPLAYBACK_API const FString CategoryName = TEXT("Manager_Playback");

					CS_DEFINE_FUNCTION_NAME_AS_STRING(NCsPlayback::NManager::FConsoleCommand, Exec_PlayLatest);
				}
			}
		}

		// Enum
		#pragma region

		// FConsoleCommand::ECommand
		#define CS_TEMP_ADD_TO_ENUM_MAP(EnumElementName) const FConsoleCommand::ECommand FConsoleCommand::NCommand::EnumElementName = FConsoleCommand::EMCommand::Get().Add(FConsoleCommand::ECommand::EnumElementName, #EnumElementName)

		CS_TEMP_ADD_TO_ENUM_MAP(PlayLatest);

		#undef CS_TEMP_ADD_TO_ENUM_MAP

		#pragma endregion Enum

		FConsoleCommand::FConsoleCommand(UObject* InRoot)
		{
			MyRoot = InRoot;

			UCsCoordinator_ConsoleCommand* Coordinator_ConsoleCommand = UCsCoordinator_ConsoleCommand::Get(MyRoot->GetWorld()->GetGameInstance());
			Handle = Coordinator_ConsoleCommand->AddManager(this);

			OnDeconstruct_Event.BindUObject(Coordinator_ConsoleCommand, &UCsCoordinator_ConsoleCommand::OnDeconstructManager);

			typedef NCsConsoleCommand::FInfo InfoType;

			CommandInfos.Reset();

			// Populate CommandInfos
			{
				const int32& Count = EMCommand::Get().Num();

				CommandInfos.Reserve(Count);

				// Play Latest
				{
					CommandInfos.AddDefaulted();
					InfoType& Info = CommandInfos.Last();

					Info.PrimaryDefinitionIndex = 0;

					TArray<FString> Base;

					Base.Add(TEXT("ManagerPlaybackPlayLatest"));
					Base.Add(TEXT("ManagerPlayback PlayLatest"));
					Base.Add(TEXT("ManagerPlayback Play Latest"));
					Base.Add(TEXT("Manager Playback PlayLatest"));
					Base.Add(TEXT("Manager Playback Play Latest"));

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
							Definitions.Add(Str);
						}
					}
					// Description
					{
						FString& Description = Info.Description;
						Description += TEXT("Call the command Spawn.\n");
						Description += TEXT("- Checks for the following console commands:\n");

						for (FString& Str : Info.Definitions)
						{
							Description += TEXT("-- ") + Str + TEXT("\n");
						}
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
			// ManagerPlaybackPlayLatest
			// ManagerPlayback PlayLatest
			// ManagerPlayback Play Latest
			// Manager Playback PlayLatest
			// Manager Playback Play Latest
			if (Exec_PlayLatest(Cmd))
				return true;
			return false;
		}

		#pragma endregion ConsoleCommandManagerType (NCsConsoleCommand::NManager::IManager)

		bool FConsoleCommand::Exec_PlayLatest(const TCHAR* Cmd)
		{
			using namespace NConsoleCommand::NCached;

			const FString& Context = Str::Exec_PlayLatest;

			void(*Log)(const FString&) = &NCsPlayback::FLog::Warning;

			FString OutString;
			FParse::Line(&Cmd, OutString, true);

			OutString = OutString.ToLower();

			const TArray<FString>& Commands	   = CommandInfos[(uint8)ECommand::PlayLatest].Commands;
			const TArray<FString>& Definitions = CommandInfos[(uint8)ECommand::PlayLatest].Definitions;

			const int32 Count = Commands.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FString& Command	  = Commands[I];
				const FString& Definition = Definitions[I];

				if (OutString.RemoveFromStart(Command))
				{
					CS_IS_PTR_NULL(MyRoot)

					typedef NCsPlayback::NManager::NPlayback::FLibrary PlaybackLibrary;

					PlaybackLibrary::SafePlayLatest(Context, MyRoot);
					return true;
				}
			}
			return false;
		}
	}
}