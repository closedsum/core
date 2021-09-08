// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_ProjectileInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsProjectile::NPayload::FInterfaceMap::Name = FName("NCsProjectile::NPayload::FInterfaceMap");

namespace NCsProjectile
{
	namespace NPayload
	{
		FInterfaceMap::FInterfaceMap() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr)
		{
			// ICsGetInterfaceMap
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FInterfaceMap>(this);
			InterfaceMap->SetUniqueBasedSlices();
		}

		FInterfaceMap::~FInterfaceMap()
		{
			// ICsGetInterfaceMap
			delete InterfaceMap;
		}
	}
}