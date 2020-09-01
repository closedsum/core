// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsTypes_Pool.h"
#include "CsCVars.h"
#pragma once

// FCsManagerPooledObjectConstructParams
#pragma region

class UWorld;
class UObject;
class UClass;

/**
*/
struct CSCORE_API FCsManagerPooledObjectConstructParams
{
public:

	UObject* Outer;

	UClass* Class;

	/** Pass through name of the Type. This additional data is not usually used in 
	    normal cases. Can be used a additional Type information for a nested object. */
	FName TypeName;

	/** Pass through name of the Class Type. This additional data is not usually used in
		normal cases. Can be used a additional Type information for a nested object. */
	FName ClassTypeName;

	ECsPooledObjectConstruction ConstructionType;

	FActorSpawnParameters ConstructionInfo;

	bool bReplicates;

	FCsManagerPooledObjectConstructParams();
};

#pragma endregion FCsManagerPooledObjectConstructParams

// FCsManagerPooledObjectParams
#pragma region

/**
*/
struct CSCORE_API FCsManagerPooledObjectParams
{
public:

	/** */
	FString Name;

	/** World associated with the Manager. */
	UWorld* World;

	/** */
	FECsCVarLog LogType;

	/** Parameters for describing how to Construct a Pooled Object. */
	FCsManagerPooledObjectConstructParams ConstructParams;

	/** Whether to Construct the Payloads on Init. */
	bool bConstructPayloads;

	/** Number of Payloads to Construct if bConstructPayloads is true. */
	int32 PayloadSize;

	/** Whether to Create a Pool on Init. */
	bool bCreatePool;

	/** Size of the Pool to create if bCreatePool is true. */
	int32 PoolSize;

	// Scoped Timer

	FECsScopedGroup ScopedGroup;

	/** Scoped Timer for CreatePool */
	FECsCVarLog CreatePoolScopedTimerCVar;
	/** Scoped Timer for Update */
	FECsCVarLog UpdateScopedTimerCVar;
	/** Scoped Timer for Updating a single Object */
	FECsCVarLog UpdateObjectScopedTimerCVar;
	/** Scoped Timer for Allocate */
	FECsCVarLog AllocateScopedTimerCVar;
	/** Scoped Timer for PooledObject->Allocate */
	FECsCVarLog AllocateObjectScopedTimerCVar;
	/** Scoped Timer for Deallocate */
	FECsCVarLog DeallocateScopedTimerCVar;
	/** Scoped Timer for PooledObject->Deallocate */
	FECsCVarLog DeallocateObjectScopedTimerCVar;
	/** Scoped Timer for Spawn */
	FECsCVarLog SpawnScopedTimerCVar;
	/** Scoped Timer for Destroy */
	FECsCVarLog DestroyScopedTimerCVar;

	FCsManagerPooledObjectParams();
};

#pragma endregion FCsManagerPooledObjectParams