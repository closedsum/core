// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/Range/CsDamageValueRangeEmu.h"
#include "CsCore.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName FCsDamageValueRangeEmu::Name = FName("FCsDamageValueRangeEmu");

FCsDamageValueRangeEmu::FCsDamageValueRangeEmu() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsDamageValueRange
	MinValue(nullptr),
	MaxValue(nullptr)
{
	// ICsGetInterfaceMap
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsDamageValueRangeEmu::Name);

	InterfaceMap->Add<ICsDamageValue>(static_cast<ICsDamageValue*>(this));
	InterfaceMap->Add<ICsDamageValueRange>(static_cast<ICsDamageValueRange*>(this));
}

FCsDamageValueRangeEmu::~FCsDamageValueRangeEmu()
{
	// ICsGetInterfaceMap
	if (InterfaceMap)
	{
		delete InterfaceMap;
		InterfaceMap = nullptr;
	}
}