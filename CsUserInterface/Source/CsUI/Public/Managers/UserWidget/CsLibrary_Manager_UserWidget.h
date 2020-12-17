// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsInterfaceMap.h"
// Library
#include "Managers/UserWidget/Data/CsLibrary_Data_UserWidget.h"
// Managers
#include "Managers/UserWidget/CsManager_UserWidget.h"
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