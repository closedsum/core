// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
#include "Misc/OutputDevice.h"
// Interfaces
#include "Managers/ConsoleCommand/CsManager_ConsoleCommand.h"
// Types
#include "Types/Enum/CsEnumMap.h"
#pragma once

class UObject;
class UWorld;

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
					extern CSPLAYBACK_API const FString CategoryName;
				}
			}
		}

	#define ConsoleCommandManagerType NCsConsoleCommand::NManager::IManager
	
		class CSPLAYBACK_API FConsoleCommand : ConsoleCommandManagerType
		{
		#define HandleType NCsConsoleCommand::NManager::FHandle
		#define InfoType NCsConsoleCommand::FInfo

		public:

			FConsoleCommand(UObject* InRoot);
			~FConsoleCommand();
			
		// ConsoleCommandManagerType (NCsConsoleCommand::NManager::IManager)
		#pragma region
		public:

			FORCEINLINE const TArray<InfoType>& GetCommandInfos() const { return CommandInfos; }

			FORCEINLINE const FString& GetCategoryName() const { return NConsoleCommand::NCached::Str::CategoryName; }

			bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out = *GLog);

		#pragma endregion ConsoleCommandManagerType NCsConsoleCommand::NManager::IManager

		private:
			
			DECLARE_DELEGATE_TwoParams(FOnDeconstruct, ConsoleCommandManagerType* /*Manager*/, const HandleType& /*Handle*/);

			FOnDeconstruct OnDeconstruct_Event;

			HandleType Handle;
			
			UObject* MyRoot;

			TArray<InfoType> CommandInfos;

		private:

			enum class ECommand : uint8
			{
				PlayLatest
			};

			struct EMCommand : TCsEnumMap<ECommand>
			{
				CS_ENUM_MAP_BODY(EMCommand, ECommand)
			};

			struct NCommand
			{
				typedef ECommand Type;

				static const Type PlayLatest;
			};

			/**
			* Call the command Playback Latest.
			* Checks for the following console commands:
			* - ManagerPlaybackPlayLatest
			* - ManagerPlayback PlayLatest
			* - ManagerPlayback Play Latest
			* - Manager Playback PlayLatest
			* - Manager Playback Play Latest
			* 
			* @param Cmd	Console Command
			* return		Whether the console command was found / executed
			*/
			bool Exec_PlayLatest(const TCHAR* Cmd);

		#undef HandleType
		#undef InfoType
		};
	#undef ConsoleCommandManagerType
	}
}