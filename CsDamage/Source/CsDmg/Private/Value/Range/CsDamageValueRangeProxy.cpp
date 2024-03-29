// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Value/Range/CsDamageValueRangeProxy.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName NCsDamage::NValue::NRange::FProxy::Name = FName("NCsDamage::NValue::NRange::FProxy");

namespace NCsDamage
{
	namespace NValue
	{
		namespace NRange
		{
			FProxy::FProxy() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// IRange
				MinValue(nullptr),
				MaxValue(nullptr)
			{
				// ICsGetInterfaceMap
				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FProxy>(this);

				InterfaceMap->Add<IValue>(static_cast<IValue*>(this));
				InterfaceMap->Add<IRange>(static_cast<IRange*>(this));
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