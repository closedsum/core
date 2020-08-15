// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsPayload_PooledObjectImplSlice::Name = FName("FCsPayload_PooledObjectImplSlice");

FCsPayload_PooledObjectImplSlice::FCsPayload_PooledObjectImplSlice() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsPayload_PooledObject
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr),
	Time()
{
}

void FCsPayload_PooledObjectImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
{
	checkf(InInterfaceMap, TEXT("FCsPayload_PooledObjectImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

	checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("FCsPayload_PooledObjectImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

	InterfaceMap = InInterfaceMap;

	InterfaceMap->Add<ICsPayload_PooledObject>(FCsPayload_PooledObjectImplSlice::Name, static_cast<FCsPayload_PooledObjectImplSlice*>(this));
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
}

#pragma endregion ICsPayload_PooledObject