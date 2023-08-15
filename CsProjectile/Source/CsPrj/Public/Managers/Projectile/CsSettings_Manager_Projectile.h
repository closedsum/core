// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// Types
#pragma once
#include "Types/CsTypes_Projectile.h"
#include "Payload/CsTypes_Payload_Projectile.h"
#include "Managers/Time/CsTypes_Update.h"

#include "CsSettings_Manager_Projectile.generated.h"

// FCsSettings_Manager_Projectile_TypeArray
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FCsSettings_Manager_Projectile_TypeArray
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj")
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj")
	FECsProjectileClass Class;

	/** The maximum size of the pool. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj", meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;

	/** The maximum payload size. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj", meta = (ClampMin = "4", UIMin = "4"))
	int32 PayloadSize;

	FCsSettings_Manager_Projectile_PoolParams() :
		Class(),
		PoolSize(4),
		PayloadSize(4)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

#pragma endregion FCsSettings_Manager_Projectile_PoolParams

// FCsSettings_Manager_Projectile_Variables
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FCsSettings_Manager_Projectile_Variables
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj", meta = (ClampMin = "256", UIMin = "256"))
	int32 PoolSize;

	FCsSettings_Manager_Projectile_Variables() :
		PoolSize(1024)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

#pragma endregion FCsSettings_Manager_Projectile_Variables

// FCsSettings_Manager_Projectile_Modifiers
#pragma region

/** 
* Describes any settings related to Projectile Modifiers,
* objects that implement the interface: NCsProjectile::NModifier::IModifier
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsSettings_Manager_Projectile_Modifiers
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj", meta = (ClampMin = "64", UIMin = "64"))
	int32 PoolSize;

	FCsSettings_Manager_Projectile_Modifiers() :
		PoolSize(256)
	{
	}

	static const FCsSettings_Manager_Projectile_Modifiers& Get();
};

#pragma endregion FCsSettings_Manager_Projectile_Modifiers

// FCsSettings_Manager_Projectile
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSPRJ_API FCsSettings_Manager_Projectile
{
	GENERATED_USTRUCT_BODY()

public:

	/** General Idea: Pool Sharing via Mapping of Types.
		Describes the mapping of a Projectile type to underlying Projectile type
		in terms the pool of Projectiles.

		i.e. If Type 'A' is mapped to Type 'B' (TypeMap[A] = B), then
			 when a Projectile of type 'A' is spawned it will be allocated from
			 the pool of Projectiles of type 'B'.

		The idea behind behind this mapping is Projectiles of a different type may
		not have underlying code differences and just be differences in the data
		each respective projectile type uses. This provides the ability to save on both
		the number of pools created and the number of objects created for a pool. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj")
	TMap<FECsProjectile, FECsProjectile> TypeMap;

	/** Which payload to support. The payload is "dynamically" built to some extent.
		The approach assume a UOWYN (Use Only What you Need). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj")
	TSet<FECsProjectilePayload> PayloadTypes;

	/** Mapping between Update Groups, the "tick" / update group, and Sound types. This
		is important to indicate when a particular Projectile type WILL or will NOT get "ticked" or updated. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj")
	TMap<FECsUpdateGroup, FCsSettings_Manager_Projectile_TypeArray> TypesByUpdateGroupMap;

	/** Describes any pool parameters (i.e. class, pool size, payload size, ... etc) for each Projectile type. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj")
	TMap<FECsProjectile, FCsSettings_Manager_Projectile_PoolParams> PoolParams;

	/**  Describes any settings related to Projectile Variables */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj")
	FCsSettings_Manager_Projectile_Variables Variables;

	/**  Describes any settings related to Projectile Modifiers */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj")
	FCsSettings_Manager_Projectile_Modifiers Modifiers;

	FCsSettings_Manager_Projectile() :
		TypeMap(),
		PayloadTypes(),
		TypesByUpdateGroupMap(),
		PoolParams(),
		Variables(),
		Modifiers()
	{
	}

	static const FCsSettings_Manager_Projectile& Get();
	static const FCsSettings_Manager_Projectile& GetEd();

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj", meta = (AllowedClasses = "/Script/CsCore.World"))
	FSoftObjectPath Map;

	/** Native class that implements the interfaces: ICsPooledObject, ICsUpdate, and ICsProjectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj", meta = (MustImplement = "/Script.CsPrj.CsProjectile"))
	TSoftClassPtr<AActor> ClassA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj", meta = (MustImplement = "/Script.CsPrj.CsProjectile"))
	TSoftClassPtr<AActor> ClassB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj", meta = (MustImplement = "/Script.CsPrj.CsProjectile"))
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