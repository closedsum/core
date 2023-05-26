// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define DataType NCsWidgetActor::NData::IData
		#define DataInterfaceMapType NCsWidgetActor::NData::FInterfaceMap

			/**
			*/
			class CSUI_API FData : public DataHandlerType<DataType, FCsData_WidgetActorPtr, DataInterfaceMapType>
			{
			private:

				typedef DataHandlerType<DataType, FCsData_WidgetActorPtr, DataInterfaceMapType> Super;

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