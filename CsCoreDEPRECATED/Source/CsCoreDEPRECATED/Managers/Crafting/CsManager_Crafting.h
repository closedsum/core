// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Recipe.h"
#include "Coroutine/CsTypes_Coroutine.h"
#include "CsManager_Crafting.generated.h"

// Structs
#pragma region

struct CSCOREDEPRECATED_API FCsCraftingProcess
{
	bool bAllocated;
	uint64 Id;
	FCsRoutine* R;
	TWeakObjectPtr<UObject> Instigator;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCraftItem, const uint64&, const uint64&);

	FOnCraftItem OnCraftItem_Event;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFinishCraftingProcess, const uint64&, const uint64&);

	FOnFinishCraftingProcess OnFinishCraftingProcess_Event;

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
class CSCOREDEPRECATED_API ACsManager_Crafting : public AActor
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

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBeginCraftingProcess, const uint64&, const uint64&);

	FOnBeginCraftingProcess OnBeginCraftingProcess_Event;

	void CancelCraftingProcess(const uint64& Id);
	void CancelCraftingProcesses(UObject* Instigator);
};