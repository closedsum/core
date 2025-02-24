// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes_Weapon.h"

#include "CsSettings_Manager_Weapon.generated.h"

// FCsSettings_Manager_Weapon_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FCsSettings_Manager_Weapon_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Manager|Weapon|Settings")
	FECsWeaponClass Class; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Manager|Weapon|Settings", meta = (ClampMin = "0", UIMin = "0"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Manager|Weapon|Settings", meta = (ClampMin = "0", UIMin = "0"))
	int32 PayloadSize;

	FCsSettings_Manager_Weapon_PoolParams() :
		Class(),
		PoolSize(0),
		PayloadSize(4)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

#pragma endregion FCsSettings_Manager_Weapon_PoolParams

// FCsSettings_Manager_Weapon_Modifiers
#pragma region

/** 
* Describes any settings related to Weapon Modifiers,
* objects that implement the interface: NCsWeapon::NModifier::IModifier
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsSettings_Manager_Weapon_Modifiers
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Manager|Weapon|Settings", meta = (ClampMin = "64", UIMin = "64"))
	int32 PoolSize;

	FCsSettings_Manager_Weapon_Modifiers() :
		PoolSize(256)
	{
	}

	static const FCsSettings_Manager_Weapon_Modifiers& Get();

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

#pragma endregion FCsSettings_Manager_Weapon_Modifiers

// FCsSettings_Manager_Weapon_Spread
#pragma region

/** 
* Describes any settings related to Weapon Spread.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsSettings_Manager_Weapon_Spread
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Manager|Weapon|Settings", meta = (ClampMin = "64", UIMin = "64"))
	int32 PoolSize;

	FCsSettings_Manager_Weapon_Spread() :
		PoolSize(256)
	{
	}

	static const FCsSettings_Manager_Weapon_Spread& Get();

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

#pragma endregion FCsSettings_Manager_Weapon_Spread

// FCsSettings_Manager_Weapon
#pragma region

class UCsManager_Weapon;
class UClass;

USTRUCT(BlueprintType)
struct CSWP_API FCsSettings_Manager_Weapon
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, NoClear, Category = "CsWp|Managers|Weapon|Settings")
	TSoftClassPtr<UCsManager_Weapon> Class;

	/** General Idea: Pool Sharing via Mapping of Types.
		Describes the mapping of a Weapon type to underlying Weapon type
		in terms the pool of Weapons.

		i.e. If Type 'A' is mapped to Type 'B' (TypeMap[A] = B), then
			 when a Weapon of type 'A' is spawned it will be allocated from
			 the pool of Weapons of type 'B'.

		The idea behind behind this mapping is Weapons of a different type may
		not have underlying code differences and just be differences in the data
		each respective character type uses. This provides the ability to save on both
		the number of pools created and the number of objects created for a pool. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Manager|Weapon|Settings")
	TMap<FECsWeapon, FECsWeapon> TypeMap;

	/** Describes any pool parameters (i.e. class, pool size, payload size, ... etc) for each Weapon type. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Manager|Weapon|Settings")
	TMap<FECsWeapon, FCsSettings_Manager_Weapon_PoolParams> PoolParams;

	/** Describes any settings related to Projectile Modifiers */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Manager|Weapon|Settings")
	FCsSettings_Manager_Weapon_Modifiers Modifiers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Manager|Weapon|Settings")
	FCsSettings_Manager_Weapon_Spread Spread;

	FCsSettings_Manager_Weapon();

	static const FCsSettings_Manager_Weapon& Get();
	static const FCsSettings_Manager_Weapon& GetEd();

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

	UClass* LoadClassChecked(const FString& Context) const;
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Manager|Weapon|Settings", meta = (AllowedClasses = "/Script/Engine.World"))
	FSoftObjectPath Map;

	/** Native class that implements the interfaces: ICsPooledObject, ICsUpdate, and ICsWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Manager|Weapon|Settings", meta = (MustImplement = "/Script.CsWp.CsWeapon"))
	TSoftClassPtr<UObject> ClassA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Manager|Weapon|Settings", meta = (MustImplement = "/Script.CsWp.CsWeapon"))
	TSoftClassPtr<UObject> ClassB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Manager|Weapon|Settings", meta = (MustImplement = "/Script.CsWp.CsWeapon"))
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