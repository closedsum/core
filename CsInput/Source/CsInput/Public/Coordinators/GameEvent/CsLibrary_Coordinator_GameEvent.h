// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Coordinators/GameEvent/CsCoordinator_GameEvent_Delegates.h"
// Log
#include "Utility/CsInputLog.h"

class UObject;
class UCsCoordinator_GameEvent;

namespace NCsGameEvent
{
	namespace NCoordinator
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					extern CSINPUT_API const FString GetSafe;
				}
			}
		}

		struct CSINPUT_API FLibrary
		{
		#define LogLevel void(*Log)(const FString&) = &NCsInput::FLog::Warning

		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoordinator_GameEvent from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsCoordinator_GameEvent
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsCoordinator_GameEvent from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			Log function for logging conditions that result in NOT getting
			*						the Context Root.
			* return				Context for UCsCoordinator_GameEvent
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, LogLevel);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, LogLevel) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsCoordinator_GameEvent from a ContextObject.
			*
			* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsCoordinator_GameEvent
			*/
			static UObject* GetSafeContextRoot(const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsCoordinator_GameEvent from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsCoordinator_GameEvent.
			*/
			static UCsCoordinator_GameEvent* GetChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Safely get the reference to UCsCoordinator_GameEvent from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log			(optional)
			* return				UCsCoordinator_GameEvent.
			*/
			static UCsCoordinator_GameEvent* GetSafe(const FString& Context, const UObject* ContextObject, LogLevel);

			/**
			* Safely get the reference to UCsCoordinator_GameEvent from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param OutSuccess		(out)
			* @param Log			(optional)
			* return				UCsCoordinator_GameEvent.
			*/
			static UCsCoordinator_GameEvent* GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, LogLevel);

			/**
			* Safely get the reference to UCsCoordinator_GameEvent from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsCoordinator_GameEvent.
			*/
			FORCEINLINE static UCsCoordinator_GameEvent* GetSafe(const UObject* ContextObject)
			{
				using namespace NCsGameEvent::NCoordinator::NLibrary::NCached;

				const FString& Context = Str::GetSafe;

				return GetSafe(Context, ContextObject, nullptr);
			}

		#pragma endregion Get

		// Active
		#pragma region
		public:

			FORCEINLINE static bool IsActiveChecked(const FString& Context, const UObject* ContextObject)
			{
				return GetChecked(Context, ContextObject) != nullptr;
			}

			FORCEINLINE static bool SafeIsActive(const FString& Context, const UObject* ContextObject, LogLevel)
			{
				return GetSafe(Context, ContextObject, Log) != nullptr;
			}
			FORCEINLINE static bool SafeIsActive(const UObject* ContextObject)
			{
				return GetSafe(ContextObject) != nullptr;
			}

		#pragma endregion Active

		// Class
		#pragma region
		public:

			static TSubclassOf<UCsCoordinator_GameEvent> GetClassChecked(const FString& Context);

		#pragma endregion Class

		// StartPlay
		#pragma region
		public:

			static void StartPlayChecked(const FString& Context, const UObject* ContextObject);

		#pragma endregion StartPlay

		// Event
		#pragma region
		public:

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Group			The route / "group" to direct the GameEvent.
			* @param Info			
			*/
			static void ProcessGameEventInfoChecked(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Group			The route / "group" to direct the GameEvent.
			* @param Info
			* @param Log			(optional)
			* return
			*/
			static bool SafeProcessGameEventInfo(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info, LogLevel);

			/**
			* Broadcast a GameEvent routed to the appropriated Group. Value and Location maybe be optional for
			* certain GameEvents.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Group			The route / "group" to direct the GameEvent.
			* @param Info			Game Event Info to broadcast.
			*/
			static void BroadcastGameEventChecked(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const  FCsGameEventInfo& Info);

			/**
			* Broadcast a GameEvent routed to the appropriated Group. Value and Location maybe be optional for
			* certain GameEvents.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Group			The route / "group" to direct the GameEvent.
			* @param Info			Game Event Info to broadcast.
			* @param Log			Log function for logging conditions that result in NOT processing
			*						the GameEvent.
			* return				Whether the info was broadcasted or not.
			*/
			static bool SafeBroadcastGameEvent(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const  FCsGameEventInfo& Info, LogLevel);

			/**
			* Broadcast a GameEvent routed to the appropriated Group. Value and Location maybe be optional for
			* certain GameEvents.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Group			The route / "group" to direct the GameEvent.
			* @param GameEvent		Game Event to broadcast.
			* @param Value			Value associated with the GameEvent.
			* @param Location		Location associated with the GameEvent.
			*/
			static void BroadcastGameEventChecked(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const  FECsGameEvent& GameEvent, const float& Value = 0.0f, const FVector3f& Location = FVector3f::ZeroVector);

			/**
			* Broadcast a GameEvent routed to the appropriated Group. Value and Location maybe be optional for 
			* certain GameEvents.
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Group			The route / "group" to direct the GameEvent.
			* @param GameEvent		Game Event to broadcast.
			* @param Value			Value associated with the GameEvent.
			* @param Location		Location associated with the GameEvent.
			* @param Log			Log function for logging conditions that result in NOT processing
			*						the GameEvent.
			* return				Whether the GameEvent, Value, Location was broadcasted or not.
			*/
			static bool SafeBroadcastGameEvent(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const  FECsGameEvent& GameEvent, const float& Value, const FVector3f& Location, LogLevel);

		#define OnProccessEventGameInfoEventType NCsGameEvent::NCoordinator::FOnProcessGameEventInfo
			static OnProccessEventGameInfoEventType& GetOnProcessGameEventInfo_EventChecked(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group);
		#undef OnProccessEventGameInfoEventType

		#pragma endregion Event

		#undef LogLevel
		};
	}
}

using CsGameEventCoordinatorLibrary = NCsGameEvent::NCoordinator::FLibrary;