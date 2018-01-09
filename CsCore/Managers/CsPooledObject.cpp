// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsPooledObject.h"
#include "CsCore.h"

UCsPooledObject::UCsPooledObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PoolIndex  = INDEX_NONE;
}

void UCsPooledObject::DeAllocate(){}