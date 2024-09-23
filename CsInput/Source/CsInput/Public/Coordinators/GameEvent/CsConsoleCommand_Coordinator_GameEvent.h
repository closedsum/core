// Copyright 2017-2024 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Misc/OutputDevice.h"
// Interfaces
#include "Managers/ConsoleCommand/CsManager_ConsoleCommand.h"
// Types
#include "Types/Enum/CsEnumMap.h"
// GameEvent
#include "Managers/Input/GameEvent/CsGameEvent.h"

#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"

class UObject;
class UWorld;

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
					extern CSINPUT_API const FString CategoryName;
				}
			}
		}

	#define ConsoleCommandManagerType NCsConsoleCommand::NManager::IManager
	
		class CSINPUT_API FConsoleCommand : ConsoleCommandManagerType
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
			
			/** Root for Coordinator_GameEvent */
			UObject* MyRoot;

			TArray<InfoType> CommandInfos;


			bool GetGameEventCoordinatorGroup(const FString& Context, const TCHAR*& Str, FECsGameEventCoordinatorGroup& OutValue, const FString& Definition);
			bool GetGameEventCoordinatorGroupAndAdvance(const FString& Context, const TCHAR*& StrAsChar, FString& Str, FECsGameEventCoordinatorGroup& OutValue, const FString& Definition);

			bool GetGameEvent(const FString& Context, const TCHAR*& Str, FECsGameEvent& OutValue, const FString& Definition);
			bool GetGameEventAndAdvance(const FString& Context, const TCHAR*& StrAsChar, FString& Str, FECsGameEvent& OutValue, const FString& Definition);

			bool GetValue(const FString& Context, const TCHAR*&Str, float& OutValue, const FString& Definition);
			bool GetLocation(const FString& Context, const TCHAR*& Str, FVector3f& OutLocation, const FString& Definition);

		private:

			enum class ECommand : uint8
			{
				BroadcastGameEvent
			};

			struct EMCommand : TCsEnumMap<ECommand>
			{
				CS_ENUM_MAP_BODY(EMCommand, ECommand)
			};

			struct NCommand
			{
				typedef ECommand Type;

				static const Type BroadcastGameEvent;
			};

			/**
			* Call the command BroadcastGameEvent.
			* Checks for the following console commands:
			* - BroadcastGameEvent [Group] [GameEvent] [Value (optional|default=0)] [Location (optional|default=X=0Y=0Z=0)]
			* - BroadcastGameEvent [Group] [GameEvent] [Location (optional|default=X=0Y=0Z=0)]
			* - Broadcast GameEvent [Group] [GameEvent] [Value (optional|default=0)] [Location (optional|default=X=0Y=0Z=0)]
			* - Broadcast GameEvent [Group] [GameEvent] [Location (optional|default=X=0Y=0Z=0)]
			* - Broadcast Game Event [Group] [GameEvent] [Value (optional|default=0)] [Location (optional|default=X=0Y=0Z=0)]
			* - Broadcast Game Event [Group] [GameEvent] [Location (optional|default=X=0Y=0Z=0)]
			*
			* [Group]	  = The route / "group" to direct the GameEvent. See FECsGameEventCoordinatorGroup.
			* [GameEvent] = The type of GameEvent. See FECsGameEvent.
			* [Value]	  = Optional float value. Defaults to 0.0f.
			* [Location]  = Optional FVector3f value. Defaults to FVector3f::ZeroVector or FVector3f(0.0f, 0.0f, 0.0f)
			* 
			* @param Cmd	Console Command
			* return		Whether the console command was found / executed
			*/
			bool Exec_BroadcastGameEvent(const TCHAR* Cmd);

		#undef HandleType
		#undef InfoType
		};
	#undef ConsoleCommandManagerType
	}
}