// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/StaticMeshActor.h"
#include "CsStaticMeshActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsStaticMeshActorOnTick, ACsStaticMeshActor*, Actor, float, DeltaSeconds);
DECLARE_DELEGATE_OneParam(FBindableEvent_ACsStaticMeshActor_OnFellOutOfWorld, const int32&);
DECLARE_DELEGATE_OneParam(FBindableEvent_ACsStaticMeshActor_OnOutsideWorldBounds, const int32&);

UCLASS()
class CSCORE_API ACsStaticMeshActor : public AStaticMeshActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintAssignable, Category = "0 Pool")
	FBindableDynEvent_CsStaticMeshActorOnTick OnTick_ScriptEvent;

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;
	virtual void OutsideWorldBounds() override;

	FBindableEvent_ACsStaticMeshActor_OnFellOutOfWorld OnFellOutOfWorld_Event;
	FBindableEvent_ACsStaticMeshActor_OnOutsideWorldBounds OnOutsideWorldBounds_Event;

	int32 CacheIndex;
	int32 PoolIndex;

	virtual void OnAllocate(const int32 &InCacheIndex);
	virtual void OnDeAllocate();
};