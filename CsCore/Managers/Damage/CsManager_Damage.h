// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Damage.h"
#include "CsManager_Damage.generated.h"

#define CS_DAMAGE_POOL_SIZE 255
#define CS_DAMAGE_POOL_INVALID_INDEX 255

UCLASS()
class CSCORE_API ACsManager_Damage : public AActor
{
	GENERATED_UCLASS_BODY()

private:

	static TWeakObjectPtr<UObject> MyOwner;

	static UObject* GetMyOwner();

public:

	static void Init(UObject* InOwner);
	static ACsManager_Damage* Get(UWorld* InWorld);

	FCsDamageEvent Pool[CS_DAMAGE_POOL_SIZE];

	uint8 PoolIndex;

	virtual FCsDamageEvent* Allocate();

	TArray<FCsDamageEvent*> ActiveEvents;

	virtual void DeAllocate(const uint8 &Index);
	virtual void DeAllocate(FCsDamageEvent* InEvent);
};