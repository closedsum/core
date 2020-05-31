// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsTypes_Pool.h"
#include "CsCVars.h"
#pragma once

// FCsManagerPooledObjectConstructParams
#pragma region

class UWorld;
class UObject;
class UClass;

struct CSCORE_API FCsManagerPooledObjectConstructParams
{
public:

	UClass* Class;

	ECsPooledObjectConstruction ConstructionType;

	FActorSpawnParameters ConstructionInfo;

	bool bReplicates;

	FCsManagerPooledObjectConstructParams();
};

#pragma endregion FCsManagerPooledObjectConstructParams

// FCsManagerPooledObjectParams
#pragma region

struct CSCORE_API FCsManagerPooledObjectParams
{
public:

	/** */
	FString Name;

	/** */
	UWorld* World;

	/** */
	FECsCVarLog LogType;

	/** */
	FCsManagerPooledObjectConstructParams ConstructParams;

	/** */
	bool bConstructPayloads;

	/** */
	int32 PayloadSize;

	/** */
	bool bCreatePool;

	/** */
	int32 PoolSize;

	FCsManagerPooledObjectParams();
};

#pragma endregion FCsManagerPooledObjectParams