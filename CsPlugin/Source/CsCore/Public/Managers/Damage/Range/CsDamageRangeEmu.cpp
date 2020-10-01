// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Range/CsDamageRangeEmu.h"
#include "CsCore.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName NCsDamage::NRange::FEmu::Name = FName("NCsDamage::NRange::FEmu");

namespace NCsDamage
{
	namespace NRange
	{
		FEmu::FEmu() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// IRange
			MinRange(nullptr),
			MaxRange(nullptr)
		{
			// ICsGetInterfaceMap
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRootName(FEmu::Name);

			InterfaceMap->Add<IRange>(static_cast<IRange*>(this));
		}

		FEmu::~FEmu()
		{
			// ICsGetInterfaceMap
			if (InterfaceMap)
			{
				delete InterfaceMap;
				InterfaceMap = nullptr;
			}
		}
	}
}