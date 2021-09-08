// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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

namespace NCsUserWidget
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
				UCsManager_UserWidget* Manager_UserWidget = GetChecked(Context, WorldContext);

				typedef NCsUserWidget::NData::IData DataType;

				DataType* Data = Manager_UserWidget->GetDataChecked(Context, Type);

				typedef NCsUserWidget::NData::FLibrary DataLibrary;

				return DataLibrary::GetInterfaceChecked<InterfaceType>(Context, Data);
			}
		};
	}
}