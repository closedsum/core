// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Recipe.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsManager_Crafting.generated.h"

// OnBegin
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerCrafting_OnBeginCraftingProcess, const uint64&, ProcessId, const uint64&, PayloadId);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManagerCrafting_OnBeginCraftingProcess, const uint64&, const uint64&);
// OnCraft
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerCrafting_OnCraftItem, const uint64&, ProcessId, const uint64&, PayloadId);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManagerCrafting_OnCraftItem, const uint64&, const uint64&);
// OnFinish
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerCrafting_OnFinishCraftingProcess, const uint64&, ProcessId, const uint64&, PayloadId);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManagerCrafting_OnFinishCraftingProcess, const uint64&, const uint64&);

// Structs
#pragma region

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

#pragma endregion Payload

// Process
#pragma region 
protected:

	FCsCraftingProcess Processes[CS_CRAFTING_PAYLOAD_SIZE];

	uint8 ProcessIndex;
	uint64 CurrentProcessIdIndex;

	FCsCraftingProcess* AllocateProcess();

	TMap<uint64, FCsCraftingProcess*> ProcessMap;

#pragma endregion Process

public:

	virtual void CraftItems(FCsCraftingPayload* Payload);
	static char CraftItems_Internal(struct FCsRoutine* r);

	FBindableEvent_CsManagerCrafting_OnBeginCraftingProcess OnBeginCraftingProcess_Event;

	UPROPERTY(BlueprintAssignable, Category = "Crafting")
	FBindableDynEvent_CsManagerCrafting_OnBeginCraftingProcess OnBeginCraftingProcess_ScriptEvent;

	FBindableEvent_CsManagerCrafting_OnCraftItem OnCraftItem_Event;

	UPROPERTY(BlueprintAssignable, Category = "Crafting")
	FBindableDynEvent_CsManagerCrafting_OnCraftItem OnCraftItem_ScriptEvent;

	FBindableEvent_CsManagerCrafting_OnFinishCraftingProcess OnFinishCraftingProcess_Event;

	UPROPERTY(BlueprintAssignable, Category = "Crafting")
	FBindableDynEvent_CsManagerCrafting_OnFinishCraftingProcess OnFinishCraftingProcess_ScriptEvent;

	void CancelCraftingProcess(const uint64 &Id);
	void CancelCraftingProcesses(UObject* Instigator);
};