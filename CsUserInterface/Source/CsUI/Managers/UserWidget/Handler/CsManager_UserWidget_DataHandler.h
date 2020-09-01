// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_DataHandler.h"
// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"
// Data
#include "Managers/UserWidget/Data/CsData_UserWidget.h"
#include "Managers/UserWidget/Data/CsData_UserWidgetInterfaceMap.h"
#pragma once

class CSUI_API FCsManager_UserWidget_DataHandler : public TCsManager_PooledObject_DataHandler<ICsData_UserWidget, FCsData_UserWidgetPtr, FCsData_UserWidgetInterfaceMap>
{
private:

	typedef TCsManager_PooledObject_DataHandler<ICsData_UserWidget, FCsData_UserWidgetPtr, FCsData_UserWidgetInterfaceMap> Super;

public:

	FCsManager_UserWidget_DataHandler();

// TCsManager_PooledObject_DataHandler Interface
#pragma region
protected:

	virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObjects) override;

	//virtual bool HasEmulatedDataInterfaces(const FString& Context, const int32& Index) const override;

	//virtual void CreateEmulatedDataFromDataTable(const FString& Context, const int32& Index, UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject) override;

	//virtual bool DeconstructEmulatedData(const FName& InterfaceImplName, void* Data) override;

#pragma endregion TCsManager_PooledObject_DataHandler Interface

protected:

	//const TSet<FECsProjectileData>& GetEmulatedDataInterfaces(const FString& Context, const int32& Index);
};