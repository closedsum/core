// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/CsTypes_Projectile.h"
#include "Payload/CsTypes_Payload_Projectile.h"
#include "Managers/Time/CsTypes_Update.h"

#include "CsSettings_Manager_Projectile.generated.h"
#pragma once

// FCsSettings_Manager_Projectile_TypeArray
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FCsSettings_Manager_Projectile_TypeArray
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FECsProjectile> Types;

	FCsSettings_Manager_Projectile_TypeArray() :
		Types()
	{
	}
};

#pragma endregion FCsSettings_Manager_Sound_TypeArray

// FCsSettings_Manager_Projectile_PoolParams
#pragma region

/**
* Describes any pool parameters (i.e. class, pool size, payload size, ... etc) for each Projectile type.
* These parameters are used when initially creating the pool.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsSettings_Manager_Projectile_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The class of the pooled Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsProjectileClass Class;
	/** The maximum size of the pool. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;
	/** The maximum payload size. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PayloadSize;

	FCsSettings_Manager_Projectile_PoolParams() :
		Class(),
		PoolSize(4),
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

	/** Mapping for sharing a pool of projectiles between many Projectile types. This is useful
		when multiple Projectile types share the same Projectile Class. In this case, it is not
		necessary to create separate pool for each Projectile type. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsProjectile, FECsProjectile> TypeMap;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<FECsProjectilePayload> PayloadTypes;

	/** Mapping between Update Groups, the "tick" / update group, and Sound types. This
		is important to indicate when a particular Sound type WILL or will NOT get "ticked" or updated. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsUpdateGroup, FCsSettings_Manager_Projectile_TypeArray> TypesByUpdateGroupMap;

	/** Describes any pool parameters (i.e. class, pool size, payload size, ... etc) for each Projectile type. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsProjectile, FCsSettings_Manager_Projectile_PoolParams> PoolParams;

	FCsSettings_Manager_Projectile() :
		TypeMap(),
		PayloadTypes(),
		TypesByUpdateGroupMap(),
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