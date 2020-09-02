// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/Point/CsDamageValuePointEmu.h"
#include "CsCore.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName FCsDamageValuePointEmu::Name = FName("FCsDamageValuePointEmu");

FCsDamageValuePointEmu::FCsDamageValuePointEmu() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsDamageValuePoint
	Value(nullptr)
{
	// ICsGetInterfaceMap
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsDamageValuePointEmu::Name);

	InterfaceMap->Add<ICsDamageValue>(static_cast<ICsDamageValue*>(this));
	InterfaceMap->Add<ICsDamageValuePoint>(static_cast<ICsDamageValuePoint*>(this));
}

FCsDamageValuePointEmu::~FCsDamageValuePointEmu()
{
	// ICsGetInterfaceMap
	if (InterfaceMap)
	{
		delete InterfaceMap;
		InterfaceMap = nullptr;
	}
}