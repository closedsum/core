// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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

			InterfaceMap->SetRoot<FInterfaceMap>(this);
			InterfaceMap->SetUniqueBasedSlices();
		}

		FInterfaceMap::~FInterfaceMap()
		{
			delete InterfaceMap;
		}
	}
}