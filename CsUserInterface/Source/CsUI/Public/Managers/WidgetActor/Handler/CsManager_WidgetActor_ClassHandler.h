// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
		#define ClassHandlerType NCsData::NManager::NHandler::TClass

			class CSUI_API FClass : public ClassHandlerType<FCsWidgetActorPooled, FCsWidgetActorPtr, FECsWidgetActorClass>
			{
			private:

				typedef ClassHandlerType<FCsWidgetActorPooled, FCsWidgetActorPtr, FECsWidgetActorClass> Super;

			public:

				FClass();

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