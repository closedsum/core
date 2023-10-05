// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Data/Handler/CsManager_Data_ClassHandler.h"
// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "Managers/UserWidget/CsUserWidgetPooled.h"
// UI
#include "Blueprint/UserWidget.h"
#pragma once

namespace NCsUserWidget
{
	namespace NManager
	{
		namespace NHandler
		{
#define ClassHandlerType NCsData::NManager::NHandler::TClass

			/**
			*/
			class CSUI_API FClass : public ClassHandlerType<FCsUserWidgetPtr, FCsUserWidgetPtr, FECsUserWidgetClass>
			{
			private:

				typedef ClassHandlerType<FCsUserWidgetPtr, FCsUserWidgetPtr, FECsUserWidgetClass> Super;

			public:

				FClass();

			// ClassHandlerType
			#pragma region
			protected:

				virtual void GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject) override;

				virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObject) override;

			#pragma endregion ClassHandlerType
			};

			/**
			*/
			class CSUI_API FPooledClass : public ClassHandlerType<FCsUserWidgetPooled, FCsUserWidgetPooledPtr, FECsUserWidgetPooledClass>
			{
			private:

				typedef ClassHandlerType<FCsUserWidgetPooled, FCsUserWidgetPooledPtr, FECsUserWidgetPooledClass> Super;

			public:

				FPooledClass();

			// ClassHandlerType
			#pragma region
			protected:

				virtual void GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject) override;

				virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObject) override;

			#pragma endregion ClassHandlerType
			};

#undef ClassHandlerType
		}
	}
}