// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "../CoreUObject/Public/UObject/Object.h"
#include "CsPooledObjectOld.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableDynEvent_CsPooledObject_OnCreatePool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableDynEvent_CsPooledObject_DeAllocate);

UCLASS()
class CSCORE_API UCsPooledObjectOld : public UObject
{
	GENERATED_UCLASS_BODY()

	DECLARE_MULTICAST_DELEGATE(FOnCreatePool);
	DECLARE_MULTICAST_DELEGATE(FDeAllocate);

	virtual void OnCreatePool();

	FOnCreatePool OnCreatePool_Event;
	UPROPERTY(BlueprintAssignable, Category = "Pooled Object")
	FBindableDynEvent_CsPooledObject_OnCreatePool OnCreatePool_ScriptEvent;

	virtual void DeAllocate();

	FDeAllocate DeAllocate_Event;
	UPROPERTY(BlueprintAssignable, Category = "Pooled Object")
	FBindableDynEvent_CsPooledObject_DeAllocate DeAllocate_ScriptEvent;
};