// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Data/Handler/CsManager_Data_DataHandler.h"
// Types
#include "Managers/WidgetActor/Types/CsTypes_WidgetActor.h"
// Data
#include "Managers/WidgetActor/Data/CsData_WidgetActor.h"
#include "Managers/WidgetActor/Data/CsData_WidgetActorInterfaceMap.h"

namespace NCsWidgetActor
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NData
			{
				using DataType = NCsWidgetActor::NData::IData;
				using DataInterfaceMapType = NCsWidgetActor::NData::FInterfaceMap;
				using DataHandlerType = NCsData::NManager::NHandler::TData<DataType, FCsData_WidgetActorPtr, DataInterfaceMapType>;
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