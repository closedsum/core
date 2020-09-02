// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_ClassHandler.h"
#include "Managers/WidgetActor/CsWidgetActorPooled.h"
#include "Managers/WidgetActor/CsTypes_WidgetActor.h"
#pragma once


class CSUI_API FCsManager_WidgetActor_ClassHandler : public TCsManager_PooledObject_ClassHandler<FCsWidgetActorPooled, FCsWidgetActorPtr, FECsWidgetActorClass>
{
private:

	typedef TCsManager_PooledObject_ClassHandler<FCsWidgetActorPooled, FCsWidgetActorPtr, FECsWidgetActorClass> Super;

public:

	FCsManager_WidgetActor_ClassHandler();

// TCsManager_PooledObject_ClassHandler Interface
#pragma region
protected:

	virtual void GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject) override;

	virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObject) override;

#pragma endregion TCsManager_PooledObject_ClassHandler Interface
};