// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "CsSettings_Manager_Projectile.generated.h"
#pragma once

// FCsSettings_Manager_Projectile_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FCsSettings_Manager_Projectile_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement ="CsProjectile"))
	TSoftClassPtr<AActor> Class; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 PayloadSize;

	FCsSettings_Manager_Projectile_PoolParams() :
		Class(nullptr),
		PoolSize(0),
		PayloadSize(4)
	{
	}
};

#pragma endregion FCsSettings_Manager_Projectile_PoolParams

// FCsSettings_Manager_Projectile
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSPRJ_API FCsSettings_Manager_Projectile
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsProjectile, FCsSettings_Manager_Projectile_PoolParams> PoolParams;

	FCsSettings_Manager_Projectile() :
		PoolParams()
	{
	}
};

#pragma endregion FCsSettings_Manager_Projectile

// FCsSettings_Manager_Projectile_UnitTest
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSPRJ_API FCsSettings_Manager_Projectile_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	/** Map used for testing. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "World"))
	FSoftObjectPath Map;

	/** Native class that implements the interfaces: ICsPooledObject, ICsUpdate, and ICsProjectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsProjectile"))
	TSoftClassPtr<AActor> ClassA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsProjectile"))
	TSoftClassPtr<AActor> ClassB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsProjectile"))
	TSoftClassPtr<AActor> ClassC;

	FCsSettings_Manager_Projectile_UnitTest() :
		Map(),
		ClassA(FSoftObjectPath("/Script/CsPrj.CsProjectile_UnitTest_A")),
		ClassB(nullptr),
		ClassC(nullptr)
	{
	}
};

#pragma endregion FCsSettings_Manager_Projectile_UnitTest