// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Data/Handler/CsManager_Data_ClassHandler.h"
// WidgetActor
#include "Managers/WidgetActor/CsWidgetActorPooled.h"
// Types
#include "Managers/WidgetActor/Types/CsTypes_WidgetActor.h"

namespace NCsWidgetActor
{
	namespace NManager
	{
		namespace NHandler
		{
			namespace NClass
			{
				using ClassHandlerType = NCsData::NManager::NHandler::TClass<FCsWidgetActorPooled, FCsWidgetActorPtr, FECsWidgetActorClass>;

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