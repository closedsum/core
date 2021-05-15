// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_WeaponInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsWeapon::NData::FInterfaceMap::Name = FName("NCsWeapon::NData::FInterfaceMap");

namespace NCsWeapon
{
	namespace NData
	{
		FInterfaceMap::FInterfaceMap() :
				InterfaceMap(nullptr)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRootName(FInterfaceMap::Name);
			InterfaceMap->SetUniqueBasedSlices();
		}

		FInterfaceMap::~FInterfaceMap()
		{
		}
	}
}