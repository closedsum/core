// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Projectile/CsProjectileWeaponModifierInfo.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Modifier/Projectile/TimeBetweenShots/CsProjectileWeaponModifier_TimeBetweenShotsImpl.h"

// FCsProjectileWeaponModifier_TimeBetweenShotsInfo
#pragma region

#define ImplType NCsWeapon::NProjectile::NModifier::NTimeBetweenShots::FImpl

void FCsProjectileWeaponModifier_TimeBetweenShotsInfo::CopyToImpl(ImplType* Impl)
{
	Impl->SetValue(&Value);

	typedef NCsModifier::NValue::NIntegral::EApplication ApplicationType;

	Impl->SetApplication((ApplicationType*)(&Application));
}

void FCsProjectileWeaponModifier_TimeBetweenShotsInfo::CopyToImplAsValue(ImplType* Impl) const
{
	Impl->SetValue(Value);

	typedef NCsModifier::NValue::NIntegral::EApplication ApplicationType;

	Impl->SetApplication((ApplicationType)Application);
}

ImplType* FCsProjectileWeaponModifier_TimeBetweenShotsInfo::ConstructImpl()
{
	ImplType* Impl = new ImplType();

	CopyToImpl(Impl);

	return Impl;
}

#undef ImplType

bool FCsProjectileWeaponModifier_TimeBetweenShotsInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Value, 0.0f)

	typedef EMCsIntegralValueModifierApplication ApplicationMapType;

	CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, Application);
	return true;
}

#pragma endregion FCsProjectileWeaponModifier_TimeBetweenShotsInfo

// FCsProjectileWeaponModifierInfo
#pragma region

#define ModifierType NCsWeapon::NModifier::IModifier
void FCsProjectileWeaponModifierInfo::ConstructModifiers(TArray<ModifierType*>& OutModifiers)
{
#undef ModifierType
	
	int32 Count = 0;

	if (bTimeBetweenShots)
		++Count;

	OutModifiers.Reset(Count);

	if (bTimeBetweenShots)
		OutModifiers.Add(TimeBetweenShots.ConstructImpl());
}

bool FCsProjectileWeaponModifierInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (bTimeBetweenShots && !TimeBetweenShots.IsValid(Context, Log))
		return false;
	return true;
}

#pragma endregion FCsProjectileModifierInfo