// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Expression/CsTypes_DamageExpression.h"

#include "Managers/Damage/Expression/CsDamagePointEmu.h"

// FCsScriptDamagePoint
#pragma region

void FCsScriptDamagePoint::SetExpression(FCsDamagePointEmu* Expression)
{
	Expression->SetValue(&Damage);
	Expression->SetType(&Type);
}

#pragma endregion FCsScriptDamagePoint