// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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

// FCsProjectileModifier_InitialSpeedInfo
#pragma region

// NCsProjectile::NModifier::NSpeed::NInitial::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsProjectile, NModifier, NSpeed, NInitial, FImpl)

/**
* Describes how to modify the InitialSpeed of a Projectile.
*  InitialSpeed property is usually on the Projectile's Movement Component.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_InitialSpeedInfo
{
	GENERATED_USTRUCT_BODY()

	/** The value to apply to the InitialSpeed property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Value;

	/** How Value is applied to the existing InitialSpeed property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsIntegralValueModifierApplication Application;

	FCsProjectileModifier_InitialSpeedInfo() :
		Value(0.0f),
		Application(ECsIntegralValueModifierApplication::Multiply)
	{
	}

#define ImplType NCsProjectile::NModifier::NSpeed::NInitial::FImpl
	void CopyToImpl(ImplType* Impl);
	void CopyToImplAsValue(ImplType* Impl) const;

	ImplType* ConstructImpl();
#undef ImplType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

#pragma endregion FCsProjectileModifier_InitialSpeedInfo

// FCsProjectileModifier_MaxSpeedInfo
#pragma region

// NCsProjectile::NModifier::NSpeed::NMax::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsProjectile, NModifier, NSpeed, NMax, FImpl)

/**
* Describes how to modify the MaxSpeed of a Projectile.
*  MaxSpeed property is usually on the Projectile's Movement Component.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_MaxSpeedInfo
{
	GENERATED_USTRUCT_BODY()

	/** The value to apply to the MaxSpeed property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Value;

	/** How Value is applied to the existing MaxSpeed property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsIntegralValueModifierApplication Application;

	FCsProjectileModifier_MaxSpeedInfo() :
		Value(0.0f),
		Application(ECsIntegralValueModifierApplication::Multiply)
	{
	}

#define ImplType NCsProjectile::NModifier::NSpeed::NMax::FImpl
	void CopyToImpl(ImplType* Impl);
	void CopyToImplAsValue(ImplType* Impl) const;

	ImplType* ConstructImpl();
#undef ImplType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

#pragma endregion FCsProjectileModifier_MaxSpeedInfo

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

	/** Flag to indicate whether or note the InitialSpeed property should be modified. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bInitialSpeed;

	/** Describes how to modify the InitialSpeed property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (editcondition = "bInitialSpeed"))
	FCsProjectileModifier_InitialSpeedInfo InitialSpeed;

	/** Flag to indicate whether or note the MaxSpeed property should be modified. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bMaxSpeed;

	/** Describes how to modify the MaxSpeed property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (editcondition = "bMaxSpeed"))
	FCsProjectileModifier_MaxSpeedInfo MaxSpeed;

// NCsProjectile::NData::NDamage::IDamage

	FCsProjectileModifierInfo() :
		bLifeTime(false),
		LifeTime(),
		bInitialSpeed(false),
		InitialSpeed(),
		bMaxSpeed(false),
		MaxSpeed()
	{
	}

#define ModifierType NCsProjectile::NModifier::IModifier
	void ConstructModifiers(TArray<ModifierType*>& OutModifiers);
#undef ModifierType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

#pragma endregion FCsProjectileModifierInfo