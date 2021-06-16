// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/Range/CsDamageValueRangeEmu.h"
#include "CsCore.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName NCsDamage::NValue::NRange::FEmu::Name = FName("NCsDamage::NValue::NRange::FEmu");

namespace NCsDamage
{
	namespace NValue
	{
		namespace NRange
		{
			FEmu::FEmu() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// IRange
				MinValue(nullptr),
				MaxValue(nullptr)
			{
				// ICsGetInterfaceMap
				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FEmu>(this);

				InterfaceMap->Add<IValue>(static_cast<IValue*>(this));
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
}