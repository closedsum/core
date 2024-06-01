// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Misc/OutputDevice.h"
// Interfaces
#include "Managers/ConsoleCommand/CsManager_ConsoleCommand.h"
// Types
#include "Types/Enum/CsEnumMap.h"
#include "Managers/Time/CsTypes_Update.h"

class UObject;
class UWorld;

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
					extern CSTIME_API const FString CategoryName;
				}
			}
		}

	#define ConsoleCommandManagerType NCsConsoleCommand::NManager::IManager
	
		class CSTIME_API FConsoleCommand : ConsoleCommandManagerType
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

			/**
			*
			*
			* @param Str
			* @param OutValue
			* @param OutString
			* return
			*/
			bool GetUpdateGroup(const FString& Context, const TCHAR*& Str, FECsUpdateGroup& OutValue, const FString& Definition);
			bool GetUpdateGroupAndAdvance(const FString& Context, const TCHAR*& StrAsChar, FString& Str, FECsUpdateGroup& OutValue, const FString& Definition);

			bool GetDeltaTime(const FString& Context, const TCHAR*& Str, float& OutValue, const FString& Definition);

		private:

			enum class ECommand : uint8
			{
				Pause,
				Unpause,
				CustomUpdate,
			};

			struct EMCommand : TCsEnumMap<ECommand>
			{
				CS_ENUM_MAP_BODY(EMCommand, ECommand)
			};

			struct NCommand
			{
				typedef ECommand Type;

				static const Type Pause;
				static const Type Unpause;
			};

			/**
			* Call the command Pause.
			* Checks for the following console commands:
			* - ManagerTimePause [UpdateGroup]
			* - ManagerTime Pause [UpdateGroup]
			* - Manager Time Pause [UpdateGroup]
			*
			* [UpdateGroup] = The Update Group to pause.
			* 
			* @param Cmd	Console Command
			* return		Whether the console command was found / executed
			*/
			bool Exec_Pause(const TCHAR* Cmd);

			/**
			* Call the command Unpause.
			* Checks for the following console commands:
			* - ManagerTimeUnpause [UpdateGroup]
			* - ManagerTime Unpause [UpdateGroup]
			* - Manager Time Unpause [UpdateGroup]
			*
			* [UpdateGroup] = The Update Group to pause.
			*
			* @param Cmd	Console Command
			* return		Whether the console command was found / executed
			*/
			bool Exec_Unpause(const TCHAR* Cmd);

			/**
			* Call the command CustomUpdate.
			* Checks for the following console commands:
			* - ManagerTimeCustomUpdate [UpdateGroup] [DeltaTime]
			* - ManagerTime CustomUpdate [UpdateGroup] [DeltaTime]
			* - Manager Time CustomUpdate [UpdateGroup] [DeltaTime]
			*
			* [UpdateGroup] = The Update Group to pause.
			* [DeltaTime]	= Number > 0.0f.
			*
			* @param Cmd	Console Command
			* return		Whether the console command was found / executed
			*/
			bool Exec_CustomUpdate(const TCHAR* Cmd);

		#undef HandleType
		#undef InfoType
		};
	#undef ConsoleCommandManagerType
	}
}