// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsStaticMeshActor.h"
#include "CsCore.h"

ACsStaticMeshActor::ACsStaticMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;
}

void ACsStaticMeshActor::Tick(float DeltaSeconds)
{
#if WITH_EDITOR
	OnTick_ScriptEvent.Broadcast(this, DeltaSeconds);
#endif // #if WITH_EDITOR
}

void ACsStaticMeshActor::FellOutOfWorld(const class UDamageType& dmgType)
{
	UE_LOG(LogCs, Warning, TEXT("ACsStaticMeshActor::FellOutOfWorld: Warning. Pool Objected with CacheIndex: %d and PoolIndex: %d is being FORCED DeAllocated."), CacheIndex, PoolIndex);
	OnFellOutOfWorld_Event.ExecuteIfBound(CacheIndex);
}

void ACsStaticMeshActor::OutsideWorldBounds()
{
	UE_LOG(LogCs, Warning, TEXT("ACsStaticMeshActor::FellOutOfWorld: Warning. Pool Objected with CacheIndex: %d and PoolIndex: %d is being FORCED DeAllocated."), CacheIndex, PoolIndex);
	OnOutsideWorldBounds_Event.ExecuteIfBound(CacheIndex);
}

void ACsStaticMeshActor::OnAllocate(const int32 &InCacheIndex)
{
	CacheIndex = InCacheIndex;
}

void ACsStaticMeshActor::OnDeAllocate()
{
	CacheIndex = INDEX_NONE;
}