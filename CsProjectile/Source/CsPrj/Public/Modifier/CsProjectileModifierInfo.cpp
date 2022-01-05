// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsProjectileModifierInfo.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Modifier/LifeTime/CsProjectileModifier_LifeTimeImpl.h"

// FCsProjectileModifier_LifeTimeInfo
#pragma region

#define ImplType NCsProjectile::NModifier::NLifeTime::FImpl

void FCsProjectileModifier_LifeTimeInfo::CopyToImpl(ImplType* Impl)
{
	Impl->SetValue(&Value);

	typedef NCsModifier::NValue::NIntegral::EApplication ApplicationType;

	Impl->SetApplication((ApplicationType*)(&Application));
}

void FCsProjectileModifier_LifeTimeInfo::CopyToImplAsValue(ImplType* Impl) const
{
	Impl->SetValue(Value);

	typedef NCsModifier::NValue::NIntegral::EApplication ApplicationType;

	Impl->SetApplication((ApplicationType)Application);
}

ImplType* FCsProjectileModifier_LifeTimeInfo::ConstructImpl()
{
	ImplType* Impl = new ImplType();

	CopyToImpl(Impl);

	return Impl;
}

#undef ImplType

bool FCsProjectileModifier_LifeTimeInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Value, 0.0f)

	typedef EMCsIntegralValueModifierApplication ApplicationMapType;

	CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, Application);
	return true;
}

#pragma endregion FCsProjectileModifier_LifeTimeInfo

// FCsProjectileModifierInfo
#pragma region

#define ModifierType NCsProjectile::NModifier::IModifier
void FCsProjectileModifierInfo::ConstructModifiers(TArray<ModifierType*>& OutModifiers)
{
#undef ModifierType
	
	int32 Count = 0;

	if (bLifeTime)
		++Count;

	OutModifiers.Reset(Count);

	if (bLifeTime)
		OutModifiers.Add(LifeTime.ConstructImpl());
}

bool FCsProjectileModifierInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (bLifeTime && !LifeTime.IsValid(Context, Log))
		return false;
	return true;
}

#pragma endregion FCsProjectileModifierInfo