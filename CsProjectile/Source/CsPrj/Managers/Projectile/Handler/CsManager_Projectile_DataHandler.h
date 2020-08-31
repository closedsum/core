// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_DataHandler.h"
// Types
#include "Managers/Projectile/CsTypes_Projectile.h"
// Data
#include "Data/CsData_Projectile.h"
#include "Data/CsData_ProjectileInterfaceMap.h"
#pragma once

class CSPRJ_API FCsManager_Projectile_DataHandler : public TCsManager_PooledObject_DataHandler<ICsData_Projectile, FCsData_ProjectilePtr, FCsData_ProjectileInterfaceMap>
{
private:

	typedef TCsManager_PooledObject_DataHandler<ICsData_Projectile, FCsData_ProjectilePtr, FCsData_ProjectileInterfaceMap> Super;

public:

	FCsManager_Projectile_DataHandler();

// TCsManager_PooledObject_DataHandler Interface
#pragma region
protected:

	virtual bool HasEmulatedDataInterfaces(const FString& Context, const int32& Index) const override;

	virtual void CreateEmulatedDataFromDataTable(const FString& Context, const int32& Index, UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject) override;

	virtual bool DeconstructEmulatedData(const FName& InterfaceImplName, void* Data) override;

#pragma endregion TCsManager_PooledObject_DataHandler Interface

protected:

	const TSet<FECsProjectileData>& GetEmulatedDataInterfaces(const FString& Context, const int32& Index);
};