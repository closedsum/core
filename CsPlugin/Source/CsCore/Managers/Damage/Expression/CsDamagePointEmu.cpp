// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Expression/CsDamagePointEmu.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsDamagePointEmu::Name = FName("FCsDamagePointEmu");

FCsDamagePointEmu::FCsDamagePointEmu() :
	InterfaceMap(),
	Damage(nullptr),
	Type(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsDamagePointEmu::Name);

	InterfaceMap->Add<ICsDamageExpression>(static_cast<ICsDamageExpression*>(this));
}

FCsDamagePointEmu::~FCsDamagePointEmu()
{

}