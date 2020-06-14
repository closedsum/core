// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Engine/DataTable.h"

#include "CsTypes_ProjectileWeapon.generated.h"
#pragma once

// FCsProjectileWeaponPtr
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeaponPtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsProjectileWeapon"))
	TSoftObjectPtr<UObject> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Weapon_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Weapon_Class;

	FCsProjectileWeaponPtr() :
		Weapon(nullptr),
		Load_Flags(0),
		Weapon_Internal(nullptr),
		Weapon_Class(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Weapon_Internal; }

	FORCEINLINE UClass* GetClass() const { return Weapon_Class; }
};

#pragma endregion FCsProjectileWeaponPtr

// FCsProjectileWeaponEntry
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeaponEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsProjectileWeaponPtr Weapon;

	FCsProjectileWeaponEntry() :
		Name(),
		DisplayName(),
		Weapon()
	{
	}
};

#pragma endregion FCsProjectileWeaponEntry