// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/Data/CsData_WidgetActorInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsWidgetActor::NData::FInterfaceMap::Name = FName("NCsWidgetActor::NData::FInterfaceMap");

namespace NCsWidgetActor
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
			delete InterfaceMap;
		}
	}
}