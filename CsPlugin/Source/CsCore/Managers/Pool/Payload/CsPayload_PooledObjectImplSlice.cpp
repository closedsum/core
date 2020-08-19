// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"

// Container
#include "Containers/CsInterfaceMap.h"
// Reset
#include "Reset/CsReset.h"

const FName FCsPayload_PooledObjectImplSlice::Name = FName("FCsPayload_PooledObjectImplSlice");

FCsPayload_PooledObjectImplSlice::FCsPayload_PooledObjectImplSlice() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsPayload_PooledObject
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr),
	Time(),
	Resets()
{
}

void FCsPayload_PooledObjectImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
{
	checkf(InInterfaceMap, TEXT("FCsPayload_PooledObjectImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

	checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("FCsPayload_PooledObjectImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

	InterfaceMap = InInterfaceMap;

	InterfaceMap->Add<ICsPayload_PooledObject>(FCsPayload_PooledObjectImplSlice::Name, static_cast<ICsPayload_PooledObject*>(this));
}

// ICsPayload_PooledObject
#pragma region

void FCsPayload_PooledObjectImplSlice::Reset()
{
	// ICsPayload_PooledObject
	bAllocated = false;

	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Time.Reset();

	for (ICsReset* R : Resets)
	{
		R->Reset();
	}
}

#pragma endregion ICsPayload_PooledObject

void FCsPayload_PooledObjectImplSlice::AddReset(ICsReset* InReset)
{
	Resets.Add(InReset);
}

void FCsPayload_PooledObjectImplSlice::CopyFrom(const FCsPayload_PooledObjectImplSlice* From)
{
	Instigator = From->Instigator;
	Owner = From->Owner;
	Parent = From->Parent;
	Time = From->Time;
}