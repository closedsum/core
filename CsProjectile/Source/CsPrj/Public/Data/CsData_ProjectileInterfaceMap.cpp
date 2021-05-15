// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

			InterfaceMap->SetRootName(FInterfaceMap::Name);
			InterfaceMap->SetUniqueBasedSlices();
		}

		FInterfaceMap::~FInterfaceMap()
		{
			// ICsGetInterfaceMap
			delete InterfaceMap;
		}
	}
}