// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Range/CsDamageRangeProxy.h"
#include "CsDmg.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName NCsDamage::NRange::FProxy::Name = FName("NCsDamage::NRange::FProxy");

namespace NCsDamage
{
	namespace NRange
	{
		FProxy::FProxy() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// IRange
			MinRange(nullptr),
			MaxRange(nullptr)
		{
			// ICsGetInterfaceMap
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FProxy>(this);

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