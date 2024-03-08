// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes_Projectile.h"
#include "Debug/CsTypes_Debug.h"

#include "CsTypes_ProjectileSettings.generated.h"

// FCsProjectileSettings_DataTable_Projectiles
#pragma region

class UDataTable;

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileSettings_DataTable_Projectiles
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj")
	TSoftObjectPtr<UDataTable> Projectiles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj")
	TSet<FECsProjectileData> EmulatedDataInterfaces;

	FCsProjectileSettings_DataTable_Projectiles() :
		Projectiles(nullptr),
		EmulatedDataInterfaces()
	{
	}
};

#pragma endregion FCsProjectileSettings_DataTable_Projectiles

// FCsSettings_Projectile_Debug
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FCsSettings_Projectile_Debug
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj")
	FCsDebugDrawSphere Collision;

	FCsSettings_Projectile_Debug() :
		Collision()
	{
	}

	static const FCsSettings_Projectile_Debug& Get();
};

#pragma endregion FCsSettings_Projectile_Debug

// FCsSettings_Projectile
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FCsSettings_Projectile
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj")
	FCsSettings_Projectile_Debug Debug;

	FCsSettings_Projectile() :
		Debug()
	{
	}

	static const FCsSettings_Projectile& Get();
};

#pragma endregion FCsSettings_Projectile