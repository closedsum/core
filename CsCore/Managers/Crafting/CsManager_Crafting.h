// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Recipe.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsManager_Crafting.generated.h"

struct FCsCraftingCache
{
	bool IsAllocated;
	FCsRoutine* R;
	TWeakObjectPtr<UObject> Instigator;

	FCsCraftingCache()
	{
		Reset();
	}
	~FCsCraftingCache() {}

	void Reset()
	{
		IsAllocated = false;
		R = nullptr;
		Instigator.Reset();
		Instigator = nullptr;
	}

	UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
};

#define CS_CRAFTING_PAYLOAD_SIZE 256

UCLASS()
class CSCORE_API ACsManager_Crafting : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	static ACsManager_Crafting* Get(UWorld* InWorld);

// Payload
#pragma region
public:

	FCsCraftingPayload Payloads[CS_CRAFTING_PAYLOAD_SIZE];

	uint8 PayloadIndex;

	FCsCraftingPayload* AllocatePayload();

#pragma endregion Payload

// Cache
#pragma region 
protected:

	FCsCraftingCache Caches[CS_CRAFTING_PAYLOAD_SIZE];

	uint8 CacheIndex;

	FCsCraftingCache* AllocateCache();

	TMap<uint64, FCsCraftingCache*> CacheMap;

#pragma endregion Cache

public:

	uint64 CurrentIdIndex;

	virtual void CraftItem(FCsCraftingPayload* Payload);
	static char CraftItem_Internal(struct FCsRoutine* r);

	void CancelCraftingItem(const uint64 &Id);
	void CancelCraftingItems(UObject* Instigator);
};