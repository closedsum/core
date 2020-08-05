// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_Weapon.h"
#include "CsSettings_Manager_Weapon.generated.h"
#pragma once

// FCsSettings_Manager_Weapon_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FCsSettings_Manager_Weapon_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement ="CsWeapon"))
	FECsWeaponClass Class; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 PayloadSize;

	FCsSettings_Manager_Weapon_PoolParams() :
		Class(),
		PoolSize(0),
		PayloadSize(4)
	{
	}
};

#pragma endregion FCsSettings_Manager_Weapon_PoolParams

// FCsSettings_Manager_Weapon
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSWP_API FCsSettings_Manager_Weapon
{
	GENERATED_USTRUCT_BODY()

public:

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsWeapon, FECsWeapon> TypeMap;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsWeapon, FCsSettings_Manager_Weapon_PoolParams> PoolParams;

	FCsSettings_Manager_Weapon() :
		TypeMap(),
		PoolParams()
	{
	}
};

#pragma endregion FCsSettings_Manager_Weapon

// FCsSettings_Manager_Weapon_UnitTest
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSWP_API FCsSettings_Manager_Weapon_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	/** Map used for testing. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "World"))
	FSoftObjectPath Map;

	/** Native class that implements the interfaces: ICsPooledObject, ICsUpdate, and ICsWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsWeapon"))
	TSoftClassPtr<UObject> ClassA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsWeapon"))
	TSoftClassPtr<UObject> ClassB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsWeapon"))
	TSoftClassPtr<UObject> ClassC;

	FCsSettings_Manager_Weapon_UnitTest() :
		Map(),
		ClassA(FSoftObjectPath("/Script/CsWp.CsWeapon_UnitTest_A")),
		ClassB(nullptr),
		ClassC(nullptr)
	{
	}
};

#pragma endregion FCsSettings_Manager_Weapon_UnitTest