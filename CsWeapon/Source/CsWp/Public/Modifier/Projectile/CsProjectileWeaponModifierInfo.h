// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Modifier/CsTypes_Modifier.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsProjectileWeaponModifierInfo.generated.h"

// FCsProjectileWeaponModifier_TimeBetweenShotsInfo
#pragma region

// NCsWeapon::NProjectile::NModifier::NTimeBetweenShots::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NModifier, NTimeBetweenShots, FImpl)

/**
* Describes how to modify the TimeBetweenShots of a Projectile Weapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeaponModifier_TimeBetweenShotsInfo
{
	GENERATED_USTRUCT_BODY()

	/** The value to apply to the TimeBetweenShots property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Value;

	/** How Value is applied to the existing LifeTime property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsIntegralValueModifierApplication Application;

	FCsProjectileWeaponModifier_TimeBetweenShotsInfo() :
		Value(0.0f),
		Application(ECsIntegralValueModifierApplication::Multiply)
	{
	}

#define ImplType NCsWeapon::NProjectile::NModifier::NTimeBetweenShots::FImpl
	void CopyToImpl(ImplType* Impl);
	void CopyToImplAsValue(ImplType* Impl) const;

	ImplType* ConstructImpl();
#undef ImplType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

#pragma endregion FCsProjectileWeaponModifier_TimeBetweenShotsInfo

// FCsProjectileWeaponModifierInfo
#pragma region

// NCsWeapon::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, IModifier)

USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeaponModifierInfo
{
	GENERATED_USTRUCT_BODY()

// NCsWeapon::NProjectile::NData::IData

	/** Flag to indicate whether or note the TimeBetweenShots property should be modified. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bTimeBetweenShots;

	/** Describes how to modify the TimeBetweenShots property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (editcondition = "bTimeBetweenShots"))
	FCsProjectileWeaponModifier_TimeBetweenShotsInfo TimeBetweenShots;

	FCsProjectileWeaponModifierInfo() :
		bTimeBetweenShots(false),
		TimeBetweenShots()
	{
	}

#define ModifierType NCsWeapon::NModifier::IModifier
	void ConstructModifiers(TArray<ModifierType*>& OutModifiers);
#undef ModifierType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

#pragma endregion FCsProjectileWeaponModifierInfo