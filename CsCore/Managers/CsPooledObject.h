// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "../CoreUObject/Public/UObject/Object.h"
#include "CsPooledObject.generated.h"

UCLASS()
class CSCORE_API UCsPooledObject : public UObject
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Pool")
	int32 PoolIndex;

	virtual void DeAllocate();

	bool IsAllocated;
};