// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Value/Point/CsDamageValuePointProxy.h"
#include "CsDmg.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName NCsDamage::NValue::NPoint::FProxy::Name = FName("NCsDamage::NValue::NPoint::FProxy");

namespace NCsDamage
{
	namespace NValue
	{
		namespace NPoint
		{
			FProxy::FProxy() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// IPoint
				Value(nullptr)
			{
				// ICsGetInterfaceMap
				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FProxy>(this);

				InterfaceMap->Add<IValue>(static_cast<IValue*>(this));
				InterfaceMap->Add<IPoint>(static_cast<IPoint*>(this));
			}

			FProxy::~FProxy()
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