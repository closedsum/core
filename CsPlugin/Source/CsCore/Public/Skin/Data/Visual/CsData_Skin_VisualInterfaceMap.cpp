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
				InterfaceMap(nullptr),
				// ICsDeconstructInterfaceSliceMap
				SliceByNameMap(),
				DeconstructSliceImplByNameMap()

			{
				// ICsGetInterfaceMap
				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FInterfaceMap>(this);
				InterfaceMap->SetUniqueBasedSlices();
			}

			FInterfaceMap::~FInterfaceMap()
			{
				for (TPair<FName, void*>& Pair : SliceByNameMap)
				{
					const FName& SliceName = Pair.Key;
					void* Slice			   = Pair.Value;

					void(*DeconstructImpl)(void*) = DeconstructSliceImplByNameMap[SliceName];

					DeconstructImpl(Slice);

					Pair.Value = nullptr;
				}
				SliceByNameMap.Reset();
				DeconstructSliceImplByNameMap.Reset();

				// ICsGetInterfaceMap
				delete InterfaceMap;
			}
		}
	}
}