// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Damage/CsTypes_Data_Beam_Damage.h"

#include "Managers/Damage/Data/Point/CsData_DamagePointProxy.h"
#include "Managers/Damage/Data/Shape/Sphere/CsData_DamageSphereImpl.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Data_Beam_Damage)

// FCsBeamData_DamagePoint
#pragma region

void FCsBeamData_DamagePoint::SetData(PointDataProxyType* Data)
{
	Data->SetValue(&Damage);
	Data->SetType(&Type);
}

#pragma endregion FCsBeamData_DamagePoint

using SphereDataProxyType = NCsDamage::NData::NShape::NSphere::NProxy::FProxy;

// FCsBeamData_DamageSphere
#pragma region

void FCsBeamData_DamageSphere::SetData(SphereDataProxyType* Data)
{
	// ICsData_Damage
	Data->SetType(&Type);
	// ICsData_DamageShape
	Data->SetMinDamage(&MinDamage);
	Data->SetMaxDamage(&MaxDamage);
	Data->SetMinRadius(&MinRadius);
	Data->SetMaxRadius(&MaxRadius);
	Data->SetInterpolationMethod(&InterpolationMethod);
	Data->SetEasingType(&EasingType);
	Data->SetCurve(Curve.GetPtr());
	// ICsData_DamageCollision
	//Data->SetIgnoreHitResultObject(&bIgnoreHitResultObject);
}

#pragma endregion FCsBeamData_DamageSphere