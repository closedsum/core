// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsProjectile::NData::FInterfaceMap::Name = FName("NCsProjectile::NData::FInterfaceMap");

namespace NCsProjectile
{
	namespace NData
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