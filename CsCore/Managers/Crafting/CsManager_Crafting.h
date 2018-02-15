// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Recipe.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsManager_Crafting.generated.h"

struct FCsCraftingProcess
{
	bool IsAllocated;
	uint64 Id;
	FCsRoutine* R;
	TWeakObjectPtr<UObject> Instigator;

	FCsCraftingProcess()
	{
		Reset();
	}
	~FCsCraftingProcess() {}

	void Reset()
	{
		IsAllocated = false;
		Id = 0;
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

// Process
#pragma region 
protected:

	FCsCraftingProcess Processes[CS_CRAFTING_PAYLOAD_SIZE];

	uint8 ProcessIndex;

	FCsCraftingProcess* AllocateProcess();

	TMap<uint64, FCsCraftingProcess*> ProcessMap;

#pragma endregion Process

public:

	uint64 CurrentProcessIdIndex;

	virtual void CraftItem(FCsCraftingPayload* Payload);
	static char CraftItem_Internal(struct FCsRoutine* r);

	void CancelCraftingItem(const uint64 &Id);
	void CancelCraftingItems(UObject* Instigator);
};