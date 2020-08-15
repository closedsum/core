// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsTypes_Data_ProjectileDamage.h"

#include "Managers/Damage/Expression/CsDamagePointEmu.h"
#include "Managers/Damage/Shape/CsDamageSphereEmu.h"

// FCsPrjDamageExpressionPoint
#pragma region

void FCsPrjDamageExpressionPoint::SetExpression(FCsDamagePointEmu* Expression)
{
	Expression->SetValue(&Damage);
	Expression->SetType(&Type);
}

#pragma endregion FCsPrjDamageExpressionPoint

// FCsPrjDamageSphere
#pragma region

void FCsPrjDamageSphere::SetExpression(FCsDamageSphereEmu* Expression)
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

#pragma endregion FCsPrjDamageSphere