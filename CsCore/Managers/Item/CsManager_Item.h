// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Item.h"
#include "CsManager_Item.generated.h"

#define CS_ITEM_POOL_SIZE 65535

UCLASS()
class CSCORE_API ACsManager_Item : public AActor
{
	GENERATED_UCLASS_BODY()

	static ACsManager_Item* Get(UWorld* InWorld);

	FCsItem Pool[CS_ITEM_POOL_SIZE];
};