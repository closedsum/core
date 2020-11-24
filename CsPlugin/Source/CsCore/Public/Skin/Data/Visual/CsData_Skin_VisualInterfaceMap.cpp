// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/CsData_Skin_VisualInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsSkin::NData::NVisual::FInterfaceMap::Name = FName("NCsSkin::NData::NVisual::FInterfaceMap");

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
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
}