// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsTypes_ProjectileModifier.h"

// ProjectileModifier
#pragma region

namespace NCsProjectileModifier
{
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(InitialSpeed, "NCsProjectile::NModifier::NSpeed::NInitial::FImpl");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(MaxSpeed, "NCsProjectile::NModifier::NSpeed::NMax::FImpl");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(DamageValuePoint, "NCsProjectile::NModifier::NDamage::NValue::NPoint::FImpl");
	//CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(ValueRange, "NCsDamage::NModifier::NValue::NRange::IRange");
}

#pragma endregion ProjectileModifier