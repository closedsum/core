// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Range/CsDamageRangeEmu.h"
#include "CsCore.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName FCsDamageRangeEmu::Name = FName("FCsDamageRangeEmu");

FCsDamageRangeEmu::FCsDamageRangeEmu() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsDamageValueRange
	MinRange(nullptr),
	MaxRange(nullptr)
{
	// ICsGetInterfaceMap
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsDamageRangeEmu::Name);

	InterfaceMap->Add<ICsDamageRange>(static_cast<ICsDamageRange*>(this));
}

FCsDamageRangeEmu::~FCsDamageRangeEmu()
{
	// ICsGetInterfaceMap
	if (InterfaceMap)
	{
		delete InterfaceMap;
		InterfaceMap = nullptr;
	}
}