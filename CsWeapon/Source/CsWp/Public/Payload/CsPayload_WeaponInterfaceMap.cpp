// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_WeaponInterfaceMap.h"

// Container
#include "Containers/CsInterfaceMap.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"

const FName NCsWeapon::NPayload::FInterfaceMap::Name = FName("NCsWeapon::NPayload::FInterfaceMap");

namespace NCsWeapon
{
	namespace NPayload
	{
		FInterfaceMap::FInterfaceMap() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				DeconstructFnPtrByNameMap()
		{
			// ICsGetInterfaceMap
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FInterfaceMap>(this);
			InterfaceMap->SetUniqueBasedSlices();
		}

		FInterfaceMap::~FInterfaceMap()
		{
			// Deconstruct any Slice that have a Deconstruct Function associated with it
			const TMap<FName, void*>& InterfaceBySliceNameMap = InterfaceMap->GetInterfacesByUniqueBasedSliceRootName();

			for (TPair<FName, void(*)(void *)>& Pair : DeconstructFnPtrByNameMap)
			{
				const FName& SliceName		  = Pair.Key;
				void(*DeconstructImpl)(void*) = Pair.Value;

				void* Ptr = InterfaceBySliceNameMap[SliceName];

				DeconstructImpl(Ptr);
			}
			// ICsGetInterfaceMap
			delete InterfaceMap;
		}
	}
}