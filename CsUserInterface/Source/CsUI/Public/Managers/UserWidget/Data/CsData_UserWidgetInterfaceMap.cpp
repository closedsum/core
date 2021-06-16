// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Data/CsData_UserWidgetInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsUserWidget::NData::FInterfaceMap::Name = FName("NCsUserWidget::NData::FInterfaceMap");

namespace NCsUserWidget
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