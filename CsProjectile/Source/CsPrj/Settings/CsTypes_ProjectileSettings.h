// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "CsTypes_ProjectileSettings.generated.h"
#pragma once

// FCsProjectileSettings_DataTable_Projectiles
#pragma region

class UDataTable;

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileSettings_DataTable_Projectiles
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> Projectiles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<FECsProjectileData> EmulatedDataInterfaces;

	FCsProjectileSettings_DataTable_Projectiles() :
		Projectiles(nullptr),
		EmulatedDataInterfaces()
	{
	}
};

#pragma endregion FCsProjectileSettings_DataTable_Projectiles