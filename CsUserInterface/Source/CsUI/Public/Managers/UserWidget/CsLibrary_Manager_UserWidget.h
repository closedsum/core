// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsInterfaceMap.h"
// Library
#include "Managers/UserWidget/Data/CsLibrary_Data_UserWidget.h"
// Managers
#include "Managers/UserWidget/CsManager_UserWidget.h"
// Data
#include "Managers/UserWidget/Data/CsData_UserWidget.h"
// Log
#include "Utility/CsUILog.h"

class UObject;
class UCsManager_UserWidget;
struct FCsUserWidgetPooled;

// NCsUserWidget::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NPayload, IPayload)

class UUserWidget;

namespace NCsUserWidget
{
	namespace NManager
	{
		/**
		*/
		struct CSUI_API FLibrary
		{
		private:

			using PayloadType = NCsUserWidget::NPayload::IPayload;

		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_UserWidget from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_UserWidget
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_UserWidget from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsManager_UserWidget
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsUI::FLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsUI::FLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_UserWidget from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_UserWidget
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
			* Get the reference to UCsManager_UserWidget from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_UserWidget.
			*/
			static UCsManager_UserWidget* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the reference to UCsManager_UserWidget from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				UCsManager_UserWidget.
			*/
			static UCsManager_UserWidget* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely get the reference to UCsManager_UserWidget from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_UserWidget.
			*/
			static UCsManager_UserWidget* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Payload
		#pragma region
		public:

			/*
			* Allocate a Payload (used to Spawn a UserWidget from Manager_UserWidget).
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* return				Payload
			*/
			static PayloadType* AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FECsUserWidgetPooled& Type);

		#pragma endregion Payload

		// Spawn
		#pragma region
		public:

			/**
			* Spawn a UserWidget with the given Payload.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			
			* @param Payload
			* return				Spawned StaticMeshActor
			*/
			static const FCsUserWidgetPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, const FECsUserWidgetPooled& Type, PayloadType* Payload);

		#pragma endregion Spawn

		// Data
		#pragma region
		public:

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* return
			*/
			template<typename InterfaceType>
			static InterfaceType* GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsUserWidgetPooled& Type)
			{
				typedef NCsUserWidget::NData::NLibrary::FLibrary DataLibrary;
				typedef NCsUserWidget::NData::IData DataType;

				UCsManager_UserWidget* Manager_UserWidget = GetChecked(Context, WorldContext);
				DataType* Data							  = Manager_UserWidget->GetDataChecked(Context, Type);	

				return DataLibrary::GetInterfaceChecked<InterfaceType>(Context, Data);
			}

		#pragma endregion Data
		};

		namespace NSetPositionInViewports
		{
			struct CSUI_API FLibrary
			{
			public:

				static int32 AllocateChecked(const FString& Context, const UObject* WorldContext, UUserWidget* Widget);

				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, const int32& ID);

				static void UpdateWorldPositionAndOffsetChecked(const FString& Context, const UObject* WorldContext, const int32& ID, const FVector3f& WorldPosition, const FVector2f& Offset);
			};
		}
	}
}

using CsWidgetManagerLibrary = NCsUserWidget::NManager::FLibrary;