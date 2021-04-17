// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#pragma once
// Types
#include "Managers/Input/CsTypes_Input.h"
#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"

class UObject;

namespace NCsGameEvent
{
	namespace NCoordinator
	{
		struct CSCORE_API FLibrary
		{
		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoordinator_GameEvent from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsCoordinator_GameEvent
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, UObject* ContextObject) { return nullptr; }
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
			static UObject* GetSafeContextRoot(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) = nullptr);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) = nullptr) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsCoordinator_GameEvent from a ContextObject.
			*
			* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsCoordinator_GameEvent
			*/
			static UObject* GetSafeContextRoot(UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Group			The route / "group" to direct the GameEvent.
			* @param Info			
			*/
			static void ProcessGameEventInfoChecked(const FString& Context, UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info);

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
			static void BroadcastGameEventChecked(const FString& Context, UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const  FECsGameEvent& GameEvent, const float& Value = 0.0f, const FVector& Location = FVector::ZeroVector);

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
			*/
			static void SafeBroadcastGameEvent(const FString& Context, UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group, const  FECsGameEvent& GameEvent, const float& Value, const FVector& Location, void(*Log)(const FString&) = nullptr);
		};
	}
}