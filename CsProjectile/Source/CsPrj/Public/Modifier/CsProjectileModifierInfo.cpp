// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsProjectileModifierInfo.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Modifier/LifeTime/CsProjectileModifier_LifeTimeImpl.h"
#include "Modifier/Speed/CsProjectileModifier_InitialSpeedImpl.h"
#include "Modifier/Speed/CsProjectileModifier_MaxSpeedImpl.h"

// FCsProjectileModifier_LifeTimeInfo
#pragma region

#define ImplType NCsProjectile::NModifier::NLifeTime::FImpl

void FCsProjectileModifier_LifeTimeInfo::CopyToImpl(ImplType* Impl)
{
	Impl->SetValue(&Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Impl->SetApplication((ApplicationType*)(&Application));
}

void FCsProjectileModifier_LifeTimeInfo::CopyToImplAsValue(ImplType* Impl) const
{
	Impl->SetValue(Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

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

	typedef EMCsNumericValueModifierApplication ApplicationMapType;

	CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, Application);
	return true;
}

#pragma endregion FCsProjectileModifier_LifeTimeInfo

// FCsProjectileModifier_InitialSpeedInfo
#pragma region

#define ImplType NCsProjectile::NModifier::NSpeed::NInitial::FImpl

void FCsProjectileModifier_InitialSpeedInfo::CopyToImpl(ImplType* Impl)
{
	Impl->SetValue(&Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Impl->SetApplication((ApplicationType*)(&Application));
}

void FCsProjectileModifier_InitialSpeedInfo::CopyToImplAsValue(ImplType* Impl) const
{
	Impl->SetValue(Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Impl->SetApplication((ApplicationType)Application);
}

ImplType* FCsProjectileModifier_InitialSpeedInfo::ConstructImpl()
{
	ImplType* Impl = new ImplType();

	CopyToImpl(Impl);

	return Impl;
}

#undef ImplType

bool FCsProjectileModifier_InitialSpeedInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Value, 0.0f)

	typedef EMCsNumericValueModifierApplication ApplicationMapType;

	CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, Application);
	return true;
}

#pragma endregion FCsProjectileModifier_LifeTimeInfo

// FCsProjectileModifier_MaxSpeedInfo
#pragma region

#define ImplType NCsProjectile::NModifier::NSpeed::NMax::FImpl

void FCsProjectileModifier_MaxSpeedInfo::CopyToImpl(ImplType* Impl)
{
	Impl->SetValue(&Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Impl->SetApplication((ApplicationType*)(&Application));
}

void FCsProjectileModifier_MaxSpeedInfo::CopyToImplAsValue(ImplType* Impl) const
{
	Impl->SetValue(Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Impl->SetApplication((ApplicationType)Application);
}

ImplType* FCsProjectileModifier_MaxSpeedInfo::ConstructImpl()
{
	ImplType* Impl = new ImplType();

	CopyToImpl(Impl);

	return Impl;
}

#undef ImplType

bool FCsProjectileModifier_MaxSpeedInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Value, 0.0f)

	typedef EMCsNumericValueModifierApplication ApplicationMapType;

	CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, Application);
	return true;
}

#pragma endregion FCsProjectileModifier_MaxSpeedInfo

// FCsProjectileModifierInfo
#pragma region

#define ModifierType NCsProjectile::NModifier::IModifier
void FCsProjectileModifierInfo::ConstructModifiers(TArray<ModifierType*>& OutModifiers)
{
#undef ModifierType
	
	int32 Count = 0;

	if (bLifeTime)
		++Count;
	if (bInitialSpeed)
		++Count;
	if (bMaxSpeed)
		++Count;

	OutModifiers.Reset(Count);

	if (bLifeTime)
		OutModifiers.Add(LifeTime.ConstructImpl());
	if (bInitialSpeed)
		OutModifiers.Add(InitialSpeed.ConstructImpl());
	if (bMaxSpeed)
		OutModifiers.Add(MaxSpeed.ConstructImpl());
}

bool FCsProjectileModifierInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (bLifeTime && !LifeTime.IsValid(Context, Log))
		return false;
	if (bInitialSpeed && !InitialSpeed.IsValid(Context, Log))
		return false;
	if (bMaxSpeed && !MaxSpeed.IsValid(Context, Log))
		return false;
	return true;
}

#pragma endregion FCsProjectileModifierInfo