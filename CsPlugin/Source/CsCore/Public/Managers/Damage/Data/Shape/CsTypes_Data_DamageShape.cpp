// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Shape/CsTypes_Data_DamageShape.h"

#include "Managers/Damage/Data/Shape/CsData_DamageSphereEmu.h"

// FCsScriptData_DamageSphere
#pragma region

void FCsScriptData_DamageSphere::SetData(FCsData_DamageSphereEmu* Data)
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

#pragma endregion FCsScriptData_DamageSphere