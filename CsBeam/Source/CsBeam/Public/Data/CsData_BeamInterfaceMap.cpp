// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_BeamInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsBeam::NData::FInterfaceMap::Name = FName("NCsBeam::NData::FInterfaceMap");

namespace NCsBeam
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