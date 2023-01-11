// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsInterfaceMap.h"
// Types
#include "Managers/WidgetActor/CsTypes_WidgetActor.h"
// Data
#include "Managers/WidgetActor/Data/CsData_WidgetActor.h"
// Log
#include "Utility/CsUILog.h"

class UObject;
class UCsManager_WidgetActor;
struct FCsWidgetActorPooled;

// NCsWidgetActor::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWidgetActor, NPayload, IPayload)

namespace NCsWidgetActor
{
	namespace NManager
	{
		/**
		*/
		struct CSUI_API FLibrary
		{
		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_WidgetActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_WidgetActor
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_WidgetActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsManager_WidgetActor
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsUI::FLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsUI::FLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_WidgetActor from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_WidgetActor
			*/
			static UObject* GetSafeContextRoot(const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

		/**
			* Get the reference to UCsManager_WidgetActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_WidgetActor.
			*/
			static UCsManager_WidgetActor* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the reference to UCsManager_WidgetActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				UCsManager_WidgetActor.
			*/
			static UCsManager_WidgetActor* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely get the reference to UCsManager_WidgetActor from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_WidgetActor.
			*/
			static UCsManager_WidgetActor* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Payload
		#pragma region
		public:

		#define PayloadType NCsWidgetActor::NPayload::IPayload

			/*
			* Allocate a Payload (used to Spawn a UserWidget from Manager_WidgetActor).
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* return				Payload
			*/
			static PayloadType* AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FECsWidgetActor& Type);

		#undef PayloadType 

		#pragma endregion Payload

		// Spawn
		#pragma region
		public:

		#define PayloadType NCsWidgetActor::NPayload::IPayload

			/**
			* Spawn a WidgetActor with the given Payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			
			* @param Payload
			* return				Spawned WidgetActor
			*/
			static const FCsWidgetActorPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, const FECsWidgetActor& Type, PayloadType* Payload);

		#undef PayloadType

		#pragma endregion Spawn
		};
	}
}