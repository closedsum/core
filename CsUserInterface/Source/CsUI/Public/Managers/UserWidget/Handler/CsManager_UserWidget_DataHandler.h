// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Data/Handler/CsManager_Data_DataHandler.h"
// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"
// Data
#include "Managers/UserWidget/Data/CsData_UserWidget.h"
#include "Managers/UserWidget/Data/CsData_UserWidgetInterfaceMap.h"

namespace NCsUserWidget
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NData
			{
				using DataType = NCsUserWidget::NData::IData;
				using DataInterfaceMapType = NCsUserWidget::NData::FInterfaceMap;
				using DataHandlerType = NCsData::NManager::NHandler::TData<DataType, FCsData_UserWidgetPtr, DataInterfaceMapType>;

				/**
				*/
				class CSUI_API FData : public DataHandlerType
				{
				private:

					using Super = DataHandlerType;

				public:

					FData();

				// DataHandlerType (NCsData::NManager::NHandler::TData)
				#pragma region
				protected:

					virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects) override;

				#pragma endregion DataHandlerType (NCsData::NManager::NHandler::TData)
				};
			}
		}
	}
}