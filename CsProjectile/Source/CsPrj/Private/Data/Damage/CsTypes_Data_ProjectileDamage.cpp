// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsTypes_Data_ProjectileDamage.h"

#include "Managers/Damage/Data/Point/CsData_DamagePointProxy.h"
#include "Managers/Damage/Data/Shape/Sphere/CsData_DamageSphereImpl.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Data_ProjectileDamage)

// FCsPrjData_DamagePoint
#pragma region

void FCsPrjData_DamagePoint::SetData(PointDataProxyType* Data)
{
	Data->SetValue(&Damage);
	Data->SetType(&Type);
}

#pragma endregion FCsPrjData_DamagePoint

// FCsPrjData_DamageSphere
#pragma region

void FCsPrjData_DamageSphere::SetData(SphereDataProxyType* Data)
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

#pragma endregion FCsPrjData_DamageSphere