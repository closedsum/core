// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Expression/CsDamageExpressionPointEmu.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsDamageExpressionPointEmu::Name = FName("FCsDamageExpressionPointEmu");

FCsDamageExpressionPointEmu::FCsDamageExpressionPointEmu() :
	InterfaceMap(),
	Damage(nullptr),
	Type(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsDamageExpressionPointEmu::Name);

	InterfaceMap->Add<ICsDamageExpression>(static_cast<ICsDamageExpression*>(this));
}

FCsDamageExpressionPointEmu::~FCsDamageExpressionPointEmu()
{

}