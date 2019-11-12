// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Recipe.h"
#include "Coroutine/CsTypes_Coroutine.h"
#include "CsManager_Crafting.generated.h"

// OnBegin
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManagerCrafting_OnBeginCraftingProcess, const uint64&, const uint64&);
// OnCraft
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManagerCrafting_OnCraftItem, const uint64&, const uint64&);
// OnFinish
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManagerCrafting_OnFinishCraftingProcess, const uint64&, const uint64&);

// Structs
#pragma region

struct FCsCraftingProcess
{
	bool bAllocated;
	uint64 Id;
	FCsRoutine* R;
	TWeakObjectPtr<UObject> Instigator;

	FBindableEvent_CsManagerCrafting_OnCraftItem OnCraftItem_Event;
	FBindableEvent_CsManagerCrafting_OnFinishCraftingProcess OnFinishCraftingProcess_Event;

	FCsCraftingProcess()
	{
		Reset();
	}
	~FCsCraftingProcess() {}

	void Reset()
	{
		bAllocated = false;
		Id = 0;
		R = nullptr;
		Instigator.Reset();
		Instigator = nullptr;

		OnCraftItem_Event.Clear();
		OnFinishCraftingProcess_Event.Clear();
	}

	UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
};

#pragma endregion Structs

#define CS_CRAFTING_PAYLOAD_SIZE 256

UCLASS()
class CSCORE_API ACsManager_Crafting : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	static ACsManager_Crafting* Get(UWorld* InWorld);

// Payload
#pragma region
protected:

	FCsCraftingPayload Payloads[CS_CRAFTING_PAYLOAD_SIZE];

	uint8 PayloadIndex;
	uint64 CurrentPayloadIdIndex;

public:
	FCsCraftingPayload* AllocatePayload();
protected:
	TMap<uint64, FCsCraftingPayload*> PayloadMap;
public:
	FCsCraftingPayload* GetPayload(const uint64& Id);

#pragma endregion Payload

// Process
#pragma region 
protected:

	FCsCraftingProcess Processes[CS_CRAFTING_PAYLOAD_SIZE];

	uint8 ProcessIndex;
	uint64 CurrentProcessIdIndex;

	FCsCraftingProcess* AllocateProcess();

	TMap<uint64, FCsCraftingProcess*> ProcessMap;

public:

	FCsCraftingProcess* GetProcess(const uint64& Id);

#pragma endregion Process

public:

	virtual void CraftItems(FCsCraftingPayload* Payload);
	static char CraftItems_Internal(struct FCsRoutine* r);

	FBindableEvent_CsManagerCrafting_OnBeginCraftingProcess OnBeginCraftingProcess_Event;

	void CancelCraftingProcess(const uint64& Id);
	void CancelCraftingProcesses(UObject* Instigator);
};