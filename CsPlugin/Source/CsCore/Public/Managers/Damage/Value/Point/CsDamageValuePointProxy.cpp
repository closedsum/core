// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/Point/CsDamageValuePointProxy.h"
#include "CsCore.h"

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