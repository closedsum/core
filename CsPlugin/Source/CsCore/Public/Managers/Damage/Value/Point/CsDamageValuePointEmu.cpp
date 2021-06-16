// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/Point/CsDamageValuePointEmu.h"
#include "CsCore.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName NCsDamage::NValue::NPoint::FEmu::Name = FName("NCsDamage::NValue::NPoint::FEmu");

namespace NCsDamage
{
	namespace NValue
	{
		namespace NPoint
		{
			FEmu::FEmu() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// IPoint
				Value(nullptr)
			{
				// ICsGetInterfaceMap
				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FEmu>(this);

				InterfaceMap->Add<IValue>(static_cast<IValue*>(this));
				InterfaceMap->Add<IPoint>(static_cast<IPoint*>(this));
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