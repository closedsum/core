// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_StatusEffectInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsStatusEffect::NData::FInterfaceMap::Name = FName("NCsStatusEffect::NData::FInterfaceMap");

namespace NCsStatusEffect
{
	namespace NData
	{
		FInterfaceMap::FInterfaceMap() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// ICsDeconstructInterfaceSliceMap
				SliceByNameMap(),
				DeconstructSliceImplByNameMap()
		{
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

			delete InterfaceMap;
		}
	}
}