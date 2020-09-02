// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_ClassHandler.h"
// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "Managers/UserWidget/CsUserWidgetPooled.h"
#pragma once

/**
*/
class CSUI_API FCsManager_UserWidget_ClassHandler : public TCsManager_PooledObject_ClassHandler<FCsUserWidgetPtr, FCsUserWidgetPtr, FECsUserWidgetClass>
{
private:

	typedef TCsManager_PooledObject_ClassHandler<FCsUserWidgetPtr, FCsUserWidgetPtr, FECsUserWidgetClass> Super;

public:

	FCsManager_UserWidget_ClassHandler();

// TCsManager_PooledObject_ClassHandler Interface
#pragma region
protected:

	virtual void GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject) override;

	virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObject) override;

#pragma endregion TCsManager_PooledObject_ClassHandler Interface
};

/**
*/
class CSUI_API FCsManager_UserWidget_Pooled_ClassHandler : public TCsManager_PooledObject_ClassHandler<FCsUserWidgetPooled, FCsUserWidgetPooledPtr, FECsUserWidgetPooledClass>
{
private:

	typedef TCsManager_PooledObject_ClassHandler<FCsUserWidgetPooled, FCsUserWidgetPooledPtr, FECsUserWidgetPooledClass> Super;

public:

	FCsManager_UserWidget_Pooled_ClassHandler();

	// TCsManager_PooledObject_ClassHandler Interface
#pragma region
protected:

	virtual void GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject) override;

	virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObject) override;

#pragma endregion TCsManager_PooledObject_ClassHandler Interface
};