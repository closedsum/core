// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsInterfaceMap.h"
// Library
#include "Managers/UserWidget/Data/CsLibrary_Data_UserWidget.h"
// Managers
#include "Managers/UserWidget/CsManager_UserWidget.h"
// Data
#include "Managers/UserWidget/Data/CsData_UserWidget.h"
#pragma once

class UObject;

namespace NCsUserWidget
{
	namespace NManager
	{

		/**
		*/
		struct CSUI_API FLibrary
		{
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_UserWidget from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_UserWidget
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_UserWidget from a WorldContext.
			*
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_UserWidget
			*/
			static UObject* GetSafeContextRoot(UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

			/**
			*/
			template<typename InterfaceType>
			static InterfaceType* GetDataChecked(const FString& Context, UObject* ContextRoot, const FECsUserWidgetPooled& Type)
			{
				checkf(ContextRoot, TEXT("%s: ContextRoot is NULL"), *Context);

				UCsManager_UserWidget* Manager_UserWidget = UCsManager_UserWidget::Get(ContextRoot);

				typedef NCsUserWidget::NData::IData DataType;

				DataType* Data = Manager_UserWidget->GetDataChecked(Context, Type);

				typedef NCsUserWidget::NData::FLibrary DataLibrary;

				return DataLibrary::GetInterfaceChecked<InterfaceType>(Context, Data);
			}
		};
	}
}