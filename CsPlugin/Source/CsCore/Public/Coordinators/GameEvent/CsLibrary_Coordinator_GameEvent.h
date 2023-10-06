// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"
// GameEvent
#include "Managers/Input/GameEvent/CsGameEvent.h"
// Log
#include "Utility/CsLog.h"

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
					extern CSCORE_API const FString GetSafe;
				}
			}
		}

		struct CSCORE_API FLibrary
		{
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
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning) { return nullptr; }
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
			static UCsCoordinator_GameEvent* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static UCsCoordinator_GameEvent* GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static bool SafeBroadcastGameEvent(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const  FCsGameEventInfo& Info, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static bool SafeBroadcastGameEvent(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const  FECsGameEvent& GameEvent, const float& Value, const FVector3f& Location, void(*Log)(const FString&) = &FCsLog::Warning);
		};
	}
}