// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_ClassHandler.h"
#include "Managers/WidgetActor/CsWidgetActorPooled.h"
#include "Managers/WidgetActor/CsTypes_WidgetActor.h"
#pragma once

namespace NCsWidgetActor
{
	namespace NManager
	{
		namespace NHandler
		{
#define ClassHandlerType NCsPooledObject::NManager::NHandler::TClass

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