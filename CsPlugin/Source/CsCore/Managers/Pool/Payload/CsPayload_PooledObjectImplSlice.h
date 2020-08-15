// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

/**
* Basic "slice" implementation of the interface: ICsPayload_PooledObject.
* The slice is intended to "layered" with other objects of the same category.
* In this case, payload.
* The slice shares a InterfaceMap with other slices.
* The InterfaceMap is usually stored in a separate object for that category.
*/
struct CSCORE_API FCsPayload_PooledObjectImplSlice : ICsPayload_PooledObject
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap
	FCsInterfaceMap* InterfaceMap;

public:

	// ICsPayload_PooledObject

	bool bAllocated;

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;

	FCsTime Time;

	FCsPayload_PooledObjectImplSlice();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

public:

	void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

// ICsPayload_PooledObject
#pragma region
public:

	FORCEINLINE const bool& IsAllocated() const
	{
		return bAllocated;
	}

	FORCEINLINE UObject* GetInstigator() const
	{
		return Instigator;
	}

	FORCEINLINE UObject* GetOwner() const
	{
		return Owner;
	}

	FORCEINLINE UObject* GetParent() const
	{
		return Parent;
	}

	FORCEINLINE const FCsTime& GetTime() const 
	{
		return Time;
	}

	FORCEINLINE void Allocate()
	{
		bAllocated = true;
	}

	void Reset();

#pragma endregion ICsPayload_PooledObject
};