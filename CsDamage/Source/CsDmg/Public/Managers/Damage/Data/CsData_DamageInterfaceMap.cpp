// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsData_DamageInterfaceMap.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsDamage::NData::FInterfaceMap::Name = FName("NCsDamage::NData::FInterfaceMap");

namespace NCsDamage
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