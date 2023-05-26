// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Engine/DataTable.h"

#include "CsTypes_TraceWeapon.generated.h"
#pragma once

// FCsTraceWeaponPtr
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponPtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsTraceWeapon"))
	TSoftClassPtr<UObject> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Weapon_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Weapon_Class;

	FCsTraceWeaponPtr() :
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

// FCsTraceWeaponEntry
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsWeapon) name for the weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	/** The enum (FECsWeapon) display name for the weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	/** Soft Reference to a weapon of type: ICsTraceWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTraceWeaponPtr Weapon;

	/** Whether to perform a Fire action on input pressed or released. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDoFireOnRelease;

	/** Whether the Fire action continues to execute when the Fire action is
	    active. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bFullAuto;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxAmmo;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TracesPerShot;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeBetweenShots;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeBetweenAutoShots;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeBetweenTracesPerShot;

	FCsTraceWeaponEntry() :
		Name(),
		DisplayName(),
		Weapon(),
		bDoFireOnRelease(false),
		bFullAuto(false),
		MaxAmmo(0),
		TracesPerShot(0),
		TimeBetweenShots(0.0f),
		TimeBetweenAutoShots(0.0f),
		TimeBetweenTracesPerShot(0.0f)
	{
	}
};

#pragma endregion FCsProjectileWeaponEntry