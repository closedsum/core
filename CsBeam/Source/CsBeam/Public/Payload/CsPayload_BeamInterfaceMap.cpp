// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Payload/CsPayload_BeamInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsBeam::NPayload::FInterfaceMap::Name = FName("NCsBeam::NPayload::FInterfaceMap");

namespace NCsBeam
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