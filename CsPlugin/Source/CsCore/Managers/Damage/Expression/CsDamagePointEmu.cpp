// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Expression/CsDamagePointEmu.h"

// Library
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Point/CsDamageValuePointEmu.h"

const FName FCsDamagePointEmu::Name = FName("FCsDamagePointEmu");

FCsDamagePointEmu::FCsDamagePointEmu() :
	// ICsInterfaceMap
	InterfaceMap(nullptr),
	// ICsDamageExpression
	Value(nullptr),
	Type(nullptr)
{
	// ICsInterfaceMap

	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsDamagePointEmu::Name);

	InterfaceMap->Add<ICsDamageExpression>(static_cast<ICsDamageExpression*>(this));

	// ICsDamageExpression
	Value = new FCsDamageValuePointEmu();
}

FCsDamagePointEmu::~FCsDamagePointEmu()
{
	// ICsInterfaceMap
	if (InterfaceMap)
	{
		delete InterfaceMap;
		InterfaceMap = nullptr;
	}
	// ICsDamageExpression
	if (Value)
	{
		delete Value;
		Value = nullptr;
	}
}

void FCsDamagePointEmu::SetValue(float* InValue)
{
	FCsDamageValuePointEmu* Emu = static_cast<FCsDamageValuePointEmu*>(Value);
	Emu->SetValue(InValue);
}