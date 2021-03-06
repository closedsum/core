// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsTypes_Data_ProjectileDamage.h"

#include "Managers/Damage/Data/CsData_DamagePointEmu.h"
#include "Managers/Damage/Data/Shape/CsData_DamageSphereEmu.h"

// FCsPrjData_DamagePoint
#pragma region

void FCsPrjData_DamagePoint::SetData(PointDataEmuType* Data)
{
	Data->SetValue(&Damage);
	Data->SetType(&Type);
}

#pragma endregion FCsPrjData_DamagePoint

// FCsPrjData_DamageSphere
#pragma region

void FCsPrjData_DamageSphere::SetData(SphereDataEmuType* Data)
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

#pragma endregion FCsPrjData_DamageSphere