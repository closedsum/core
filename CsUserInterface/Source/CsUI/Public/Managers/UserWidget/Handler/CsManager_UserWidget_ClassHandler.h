// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Data/Handler/CsManager_Data_ClassHandler.h"
// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "Managers/UserWidget/CsUserWidgetPooled.h"
// UI
#include "Blueprint/UserWidget.h"

namespace NCsUserWidget
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NClass
			{
				using ClassHandlerType = NCsData::NManager::NHandler::TClass<FCsUserWidgetPtr, FCsUserWidgetPtr, FECsUserWidgetClass>;

				/**
				*/
				class CSUI_API FClass : public ClassHandlerType
				{
				private:

					using Super = ClassHandlerType;

				public:

					FClass();

				// ClassHandlerType
				#pragma region
				protected:

					virtual void GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject) override;

					virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObject) override;

				#pragma endregion ClassHandlerType
				};
			}
		}
	}
}

namespace NCsUserWidget
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NPooledClass
			{
				using ClassHandlerType = NCsData::NManager::NHandler::TClass<FCsUserWidgetPooled, FCsUserWidgetPooledPtr, FECsUserWidgetPooledClass>;

				/**
				*/
				class CSUI_API FPooledClass : public ClassHandlerType
				{
				private:

					using Super = ClassHandlerType;

				public:

					FPooledClass();

				// ClassHandlerType
				#pragma region
				protected:

					virtual void GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject) override;

					virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObject) override;

				#pragma endregion ClassHandlerType
				};
			}
		}
	}
}