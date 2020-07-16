// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Expression/CsDamageExpressionPointEmu.h"

const FName FCsDamageExpressionPointEmu::Name = FName("FCsDamageExpressionPointEmu");

FCsDamageExpressionPointEmu::FCsDamageExpressionPointEmu() :
	InterfaceMap(),
	Damage(nullptr),
	Type(nullptr)
{
	InterfaceMap.SetRootName(FCsDamageExpressionPointEmu::Name);

	InterfaceMap.Add<ICsDamageExpression>(static_cast<ICsDamageExpression*>(this));
}