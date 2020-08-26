// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsData_DamagePointEmu.h"

// Library
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Point/CsDamageValuePointEmu.h"

const FName FCsData_DamagePointEmu::Name = FName("FCsData_DamagePointEmu");

FCsData_DamagePointEmu::FCsData_DamagePointEmu() :
	// ICsInterfaceMap
	InterfaceMap(nullptr),
	// ICsData_Damage
	Value(nullptr),
	Type(nullptr)
{
	// ICsInterfaceMap

	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsData_DamagePointEmu::Name);

	InterfaceMap->Add<ICsData_Damage>(static_cast<ICsData_Damage*>(this));

	// ICsData_Damage
	Value = new FCsDamageValuePointEmu();
}

FCsData_DamagePointEmu::~FCsData_DamagePointEmu()
{
	// ICsInterfaceMap
	if (InterfaceMap)
	{
		delete InterfaceMap;
		InterfaceMap = nullptr;
	}
	// ICsData_Damage
	if (Value)
	{
		delete Value;
		Value = nullptr;
	}
}

void FCsData_DamagePointEmu::SetValue(float* InValue)
{
	FCsDamageValuePointEmu* Emu = static_cast<FCsDamageValuePointEmu*>(Value);
	Emu->SetValue(InValue);
}