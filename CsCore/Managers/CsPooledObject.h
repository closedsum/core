// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "CsPooledObject.generated.h"

UCLASS()
class CSCORE_API ACsPooledObject : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;
	virtual void OutsideWorldBounds() override;

	FString Warning_FellOutOfWorld;
	FString Warning_OutsideWorldBounds;

	int32 PoolIndex;

	virtual void DeAllocate();

	bool IsAllocated;
};