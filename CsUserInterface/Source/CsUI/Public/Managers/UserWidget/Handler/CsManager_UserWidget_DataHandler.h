// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Data/Handler/CsManager_Data_DataHandler.h"
// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"
// Data
#include "Managers/UserWidget/Data/CsData_UserWidget.h"
#include "Managers/UserWidget/Data/CsData_UserWidgetInterfaceMap.h"
#pragma once

namespace NCsUserWidget
{
	namespace NManager
	{
		namespace NHandler
		{
		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define DataType NCsUserWidget::NData::IData
		#define DataInterfaceMapType NCsUserWidget::NData::FInterfaceMap

			/**
			*/
			class CSUI_API FData : public DataHandlerType<DataType, FCsData_UserWidgetPtr, DataInterfaceMapType>
			{
			private:

				typedef DataHandlerType<DataType, FCsData_UserWidgetPtr, DataInterfaceMapType> Super;

			public:

				FData();

			// DataHandlerType (NCsData::NManager::NHandler::TData)
			#pragma region
			protected:

				virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects) override;

			#pragma endregion DataHandlerType (NCsData::NManager::NHandler::TData)
			};

		#undef DataHandlerType
		#undef DataType
		#undef DataInterfaceMapType
		}
	}
}