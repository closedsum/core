// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Expression/CsDamageExpressionPoint.h"

const FName FCsDamageExpressionPoint::Name = FName("FCsDamageExpressionPoint");

FCsDamageExpressionPoint::FCsDamageExpressionPoint() :
	InterfaceMap(),
	Damage(nullptr),
	Type(nullptr)
{
	InterfaceMap.SetRootName(FCsDamageExpressionPoint::Name);

	InterfaceMap.Add<ICsDamageExpression>(static_cast<ICsDamageExpression*>(this));
}