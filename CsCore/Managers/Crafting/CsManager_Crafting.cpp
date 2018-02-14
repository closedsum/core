// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Crafting/CsManager_Crafting.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "Game/CsGameState.h"

#include "Coroutine/CsCoroutineScheduler.h"

// Managers
#include "Managers/Item/CsManager_Item.h"
#include "Managers/Inventory/CsManager_Inventory.h"
// Data
#include "Data/CsData_Recipe.h"

// Cache
#pragma region

namespace ECsManagerCraftingCachedName
{
	namespace Name
	{
		// Functions
		const FName CraftItem_Internal = FName("ACsManager_Crafting::CraftItem_Internal");
	};
}

namespace ECsManagerCraftingCachedString
{
	namespace Str
	{
		// Functions
		const FString CraftItem_Internal = TEXT("ACsManager_Crafting::CraftItem_Internal");
	};
}

#pragma endregion Cache

ACsManager_Crafting::ACsManager_Crafting(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

/*static*/ ACsManager_Crafting* ACsManager_Crafting::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_Crafting;
}

// Payload
#pragma region

FCsCraftingPayload* ACsManager_Crafting::AllocatePayload()
{
	for (uint8 I = 0; I < CS_CRAFTING_PAYLOAD_SIZE; ++I)
	{
		const uint8 Index			= (PayloadIndex + I) % CS_CRAFTING_PAYLOAD_SIZE;
		FCsCraftingPayload* Payload = &(Payloads[Index]);

		if (!Payload->IsAllocated)
		{
			Payload->IsAllocated = true;
			return Payload;
		}
	}
	checkf(0, TEXT("ACsManager_Crafting::AllocatePayload: Pool is exhausted"));
	return nullptr;
}

#pragma endregion Payload

// Cache
#pragma region 

FCsCraftingCache * ACsManager_Crafting::AllocateCache()
{
	for (uint8 I = 0; I < CS_CRAFTING_PAYLOAD_SIZE; ++I)
	{
		const uint8 Index		= (CacheIndex + I) % CS_CRAFTING_PAYLOAD_SIZE;
		FCsCraftingCache* Cache = &(Caches[Index]);

		if (!Cache->IsAllocated)
		{
			Cache->IsAllocated = true;
			return Cache;
		}
	}
	checkf(0, TEXT("ACsManager_Crafting::AllocateCache: Pool is exhausted"));
	return nullptr;
}

#pragma endregion Cache

void ACsManager_Crafting::CraftItem(FCsCraftingPayload* Payload)
{
	if (Payload->Count == CS_EMPTY)
	{
		ACsData_Recipe* Recipe   = Payload->GetRecipe();
		const FString RecipeName = Recipe->ShortCode.ToString();

		UE_LOG(LogCs, Warning, TEXT("ACsManager_Crafting::CraftItem: Attemping to craft Recipe: %s 0 times. Count must be > 0."), *RecipeName);
		return;
	}

	UCsCoroutineScheduler* Scheduler		= UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* CoroutinePayload	= Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	CoroutinePayload->Schedule		  = Schedule;
	CoroutinePayload->Function		  = &ACsManager_Crafting::CraftItem_Internal;
	CoroutinePayload->Actor			  = Payload->GetManager_Inventory();
	CoroutinePayload->Object		  = Payload->GetInstigator();
	//CoroutinePayload->Stop = &UCsCommon::CoroutineStopCondition_CheckObject;
	//CoroutinePayload->Type = (uint8)ECsWidgetCraftingRoutine::CraftItem_Internal;
	CoroutinePayload->DoInit		  = true;
	CoroutinePayload->PerformFirstRun = false;
	CoroutinePayload->Name			  = ECsManagerCraftingCachedName::Name::CraftItem_Internal;
	CoroutinePayload->NameAsString	  = ECsManagerCraftingCachedString::Str::CraftItem_Internal;

	FCsRoutine* R = Scheduler->Allocate(CoroutinePayload);

	R->floats[0] = GetWorld()->GetTimeSeconds();
	R->voidPointers[0] = (void*)Payload;

	// Add to CacheMap
	CurrentIdIndex++;

	FCsCraftingCache* Cache = AllocateCache();
	Cache->R				= R;
	Cache->Instigator		= Payload->GetInstigator();

	CacheMap.Add(CurrentIdIndex, Cache);
	// Start Routine
	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(ACsManager_Crafting, CraftItem_Internal)
{
	ACsManager_Inventory* inventory = Cast<ACsManager_Inventory>(r->GetActor());
	UCsCoroutineScheduler* s		= r->scheduler;
	UWorld* w						= inventory->GetWorld();
	
	FCsCraftingPayload* Payload = (FCsCraftingPayload*)r->voidPointers[0];
	ACsData_Recipe* Recipe	    = Payload->GetRecipe();

	TArray<FCsRecipeIngredient>* Ingredients = Recipe->GetIngredients();

	const uint16& Count		= Payload->Count; 
	const bool UseBulkTime	= Recipe->GetUseBulkTime();
	const float Time			= UseBulkTime ? Recipe->GetUseBulkTime() : Recipe->GetTime();
	const float& StartTime	= r->floats[0];
	const float CurrentTime	= w->GetTimeSeconds();

	const int32& Index = r->indexers[0];

	CS_COROUTINE_BEGIN(r);

	do
	{
		CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime < Time);

		{

			
		}
		r->indexers[0]++;
	} while (Index < Count);

	CS_COROUTINE_END(r);
}

void ACsManager_Crafting::CancelCraftingItem(const uint64 &Id)
{
	FCsCraftingCache** CachePtr = CacheMap.Find(Id);

	if (!CachePtr)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Crafting::CancelCraftingItem: Attemping to cancel Crafting Process: %d, but it does NOT exist."), Id);
		return;
	}

	FCsCraftingCache* Cache = *CachePtr;

	Cache->R->End(ECsCoroutineEndReason::StopCondition);

	CacheMap.Remove(Id);
}

void ACsManager_Crafting::CancelCraftingItems(UObject* Instigator)
{
	TArray<uint64> Keys;
	CacheMap.GetKeys(Keys);

	const int32 Count = Keys.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const uint64& Id		= Keys[I];
		FCsCraftingCache* Cache = *(CacheMap.Find(Id));

		if (Instigator == Cache->GetInstigator())
		{
			CacheMap.Remove(Id);
		}
	}
}