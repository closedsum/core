// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsPooledObject.h"
#include "CsCore.h"

ACsPooledObject::ACsPooledObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	Warning_FellOutOfWorld	   = TEXT("ACsPooledObject::FellOutOfWorld");
	Warning_OutsideWorldBounds = TEXT("ACsPooledObject::OutsideWorldBounds");

	PoolIndex  = INDEX_NONE;
}

void ACsPooledObject::FellOutOfWorld(const class UDamageType& dmgType)
{
	UE_LOG(LogCs, Warning, TEXT("%s: Warning. Pool Objected with PoolIndex: %d is being FORCED DeAllocated."), *Warning_FellOutOfWorld, PoolIndex);
	DeAllocate();
}

void ACsPooledObject::OutsideWorldBounds()
{
	UE_LOG(LogCs, Warning, TEXT("%s: Warning. Pool Objected with PoolIndex: %d is being FORCED DeAllocated."), *Warning_OutsideWorldBounds, PoolIndex);
	DeAllocate();
}


void ACsPooledObject::DeAllocate(){}