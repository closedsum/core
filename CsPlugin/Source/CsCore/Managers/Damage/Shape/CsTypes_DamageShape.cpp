// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Shape/CsTypes_DamageShape.h"

#include "Managers/Damage/Shape/CsDamageSphereEmu.h"

// FCsScriptDamageSphere
#pragma region

void FCsScriptDamageSphere::SetExpression(FCsDamageSphereEmu* Expression)
{
	// ICsDamageExpression
	Expression->SetType(&Type);
	// ICsDamageShape
	Expression->SetMinDamage(&MinDamage);
	Expression->SetMaxDamage(&MaxDamage);
	Expression->SetMinRadius(&MinRadius);
	Expression->SetMaxRadius(&MaxRadius);
	Expression->SetInterpoloationMethod(&InterpolationMethod);
	Expression->SetEasingType(&EasingType);
	Expression->SetCurve(&Curve);
	// ICsDamageCollision
	Expression->SetIgnoreHitResultObject(&bIgnoreHitResultObject);
}

#pragma endregion FCsScriptDamageSphere