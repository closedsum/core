// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Modifier/CsTypes_Modifier.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsProjectileModifierInfo.generated.h"

// FCsProjectileModifier_LifeTimeInfo
#pragma region

// NCsProjectile::NModifier::NLifeTime::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NLifeTime, FImpl)

/**
* Describes how to modify the LifeTime of a Projectile,
* object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_LifeTimeInfo
{
	GENERATED_USTRUCT_BODY()

	/** The value to apply to the LifeTime property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Value;

	/** How Value is applied to the existing LifeTime property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsIntegralValueModifierApplication Application;

	FCsProjectileModifier_LifeTimeInfo() :
		Value(0.0f),
		Application(ECsIntegralValueModifierApplication::Multiply)
	{
	}

#define ImplType NCsProjectile::NModifier::NLifeTime::FImpl
	void CopyToImpl(ImplType* Impl);
	void CopyToImplAsValue(ImplType* Impl) const;

	ImplType* ConstructImpl();
#undef ImplType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

#pragma endregion FCsProjectileModifier_LifeTimeInfo

// virtual const float& GetInitialSpeed() const = 0;
// virtual const float& GetMaxSpeed() const = 0;

// FCsProjectileModifierInfo
#pragma region

// NCsProjectile::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, IModifier)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifierInfo
{
	GENERATED_USTRUCT_BODY()

// NCsProjectile::NData::IData

	/** Flag to indicate whether or note the LifeTime property should be modified. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bLifeTime;

	/** Describes how to modify the LifeTime property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (editcondition = "bLifeTime"))
	FCsProjectileModifier_LifeTimeInfo LifeTime;

// NCsProjectile::NData::NDamage::IDamage

	FCsProjectileModifierInfo() :
		bLifeTime(false),
		LifeTime()
	{
	}

#define ModifierType NCsProjectile::NModifier::IModifier
	void ConstructModifiers(TArray<ModifierType*>& OutModifiers);
#undef ModifierType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

#pragma endregion FCsProjectileModifierInfo