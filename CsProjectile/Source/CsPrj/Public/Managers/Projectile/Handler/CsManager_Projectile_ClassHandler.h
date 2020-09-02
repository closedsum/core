// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_ClassHandler.h"
// Types
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "Managers/Projectile/CsProjectilePooled.h"
#pragma once

/**
*/
class CSPRJ_API FCsManager_Projectile_ClassHandler : public TCsManager_PooledObject_ClassHandler<FCsProjectilePooled, FCsProjectilePtr, FECsProjectileClass>
{
private:

	typedef TCsManager_PooledObject_ClassHandler<FCsProjectilePooled, FCsProjectilePtr, FECsProjectileClass> Super;

public:

	FCsManager_Projectile_ClassHandler();

// TCsManager_PooledObject_ClassHandler Interface
#pragma region
protected:

	virtual void GetClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject) override;

	virtual void GetDatasDataTablesChecked(const FString& Context, TArray<UDataTable*>& OutDataTables, TArray<TSoftObjectPtr<UDataTable>>& OutDataTableSoftObject) override;

#pragma endregion TCsManager_PooledObject_ClassHandler Interface
};