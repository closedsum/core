// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Payload/CsPayload_UserWidgetInterfaceMap.h"

// Containers
#include "Containers/CsInterfaceMap.h"

const FName NCsUserWidget::NPayload::FInterfaceMap::Name = FName("NCsUserWidget::NPayload::FInterfaceMap");

namespace NCsUserWidget
{
	namespace NPayload
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