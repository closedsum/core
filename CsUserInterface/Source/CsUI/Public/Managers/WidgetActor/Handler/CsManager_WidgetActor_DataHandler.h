// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_DataHandler.h"
// Types
#include "Managers/WidgetActor/CsTypes_WidgetActor.h"
// Data
#include "Managers/WidgetActor/Data/CsData_WidgetActor.h"
#include "Managers/WidgetActor/Data/CsData_WidgetActorInterfaceMap.h"
#pragma once

namespace NCsWidgetActor
{
	namespace NManager
	{
		namespace NHandler
		{
#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
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

			// DataHandlerType (NCsPooledObject::NManager::NHandler::TData)
			#pragma region
			protected:

				virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects) override;

			#pragma endregion DataHandlerType (NCsPooledObject::NManager::NHandler::TData)
			};

#undef DataHandlerType
#undef DataType
#undef DataInterfaceMapType
		}
	}
}