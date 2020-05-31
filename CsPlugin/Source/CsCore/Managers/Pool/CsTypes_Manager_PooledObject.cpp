// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsTypes_Manager_PooledObject.h"

FCsManagerPooledObjectConstructParams::FCsManagerPooledObjectConstructParams() :
	Class(nullptr),
	ConstructionType(ECsPooledObjectConstruction::Object),
	ConstructionInfo(),
	bReplicates(false)
{
}

FCsManagerPooledObjectParams::FCsManagerPooledObjectParams() :
	Name(),
	World(nullptr),
	LogType(),
	ConstructParams(),
	bConstructPayloads(false),
	PayloadSize(0),
	bCreatePool(false),
	PoolSize(0)
{
}