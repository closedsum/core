// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsTypes_Data_Beam_Damage.h"

#include "Managers/Damage/Data/Point/CsData_DamagePointProxy.h"
#include "Managers/Damage/Data/Shape/CsData_DamageSphereProxy.h"

// FCsBeamData_DamagePoint
#pragma region

void FCsBeamData_DamagePoint::SetData(PointDataProxyType* Data)
{
	Data->SetValue(&Damage);
	Data->SetType(&Type);
}

#pragma endregion FCsBeamData_DamagePoint

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
	Data->SetInterpoloationMethod(&InterpolationMethod);
	Data->SetEasingType(&EasingType);
	Data->SetCurve(&Curve);
	// ICsData_DamageCollision
	Data->SetIgnoreHitResultObject(&bIgnoreHitResultObject);
}

#pragma endregion FCsBeamData_DamageSphere