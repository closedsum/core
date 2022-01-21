// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes_Projectile.h"

#include "CsTypes_ProjectileSettings.generated.h"

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