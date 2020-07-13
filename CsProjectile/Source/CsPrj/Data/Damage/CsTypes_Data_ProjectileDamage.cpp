// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsTypes_Data_ProjectileDamage.h"
#include "Managers/Damage/Expression/CsDamageExpressionPoint.h"


void FCsPrjDamageExpressionPoint::SetExpression(FCsDamageExpressionPoint* Expression)
{
	Expression->SetDamage(&Damage);
	Expression->SetType(&Type);
}