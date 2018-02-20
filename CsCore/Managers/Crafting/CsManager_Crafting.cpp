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
		const FName CraftItems_Internal = FName("ACsManager_Crafting::CraftItems_Internal");
	};
}

namespace ECsManagerCraftingCachedString
{
	namespace Str
	{
		// Functions
		const FString CraftItems_Internal = TEXT("ACsManager_Crafting::CraftItems_Internal");
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
			Payload->Id			 = CurrentPayloadIdIndex;

			PayloadMap.Add(Payload->Id, Payload);
			CurrentPayloadIdIndex++;
			return Payload;
		}
	}
	checkf(0, TEXT("ACsManager_Crafting::AllocatePayload: Pool is exhausted"));
	return nullptr;
}

FCsCraftingPayload* ACsManager_Crafting::GetPayload(const uint64 &Id)
{
	return *(PayloadMap.Find(Id));
}

#pragma endregion Payload

// Process
#pragma region 

FCsCraftingProcess* ACsManager_Crafting::AllocateProcess()
{
	for (uint8 I = 0; I < CS_CRAFTING_PAYLOAD_SIZE; ++I)
	{
		const uint8 Index		    = (ProcessIndex + I) % CS_CRAFTING_PAYLOAD_SIZE;
		FCsCraftingProcess* Process = &(Processes[Index]);

		if (!Process->IsAllocated)
		{
			Process->IsAllocated = true;
			Process->Id			 = CurrentProcessIdIndex;

			ProcessMap.Add(Process->Id, Process);
			CurrentProcessIdIndex++;
			return Process;
		}
	}
	checkf(0, TEXT("ACsManager_Crafting::AllocateProcess: Pool is exhausted"));
	return nullptr;
}

FCsCraftingProcess* ACsManager_Crafting::GetProcess(const uint64 &Id)
{
	return *(ProcessMap.Find(Id));
}

#pragma endregion Process

void ACsManager_Crafting::CraftItems(FCsCraftingPayload* Payload)
{
	if (Payload->Count == CS_EMPTY)
	{
		ACsData_Recipe* Recipe   = Payload->GetRecipe();
		const FString RecipeName = Recipe->ShortCode.ToString();

		UE_LOG(LogCs, Warning, TEXT("ACsManager_Crafting::CraftItems: Attemping to craft Recipe: %s 0 times. Count must be > 0."), *RecipeName);
		return;
	}

	UCsCoroutineScheduler* Scheduler		= UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* CoroutinePayload	= Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	CoroutinePayload->Schedule		  = Schedule;
	CoroutinePayload->Function		  = &ACsManager_Crafting::CraftItems_Internal;
	CoroutinePayload->Actor			  = this;
	CoroutinePayload->Stop			  = &UCsCommon::CoroutineStopCondition_CheckActor;
	CoroutinePayload->DoInit		  = true;
	CoroutinePayload->PerformFirstRun = false;
	CoroutinePayload->Name			  = ECsManagerCraftingCachedName::Name::CraftItems_Internal;
	CoroutinePayload->NameAsString	  = ECsManagerCraftingCachedString::Str::CraftItems_Internal;

	FCsRoutine* R = Scheduler->Allocate(CoroutinePayload);

	R->floats[0]	   = GetWorld()->GetTimeSeconds();
	R->voidPointers[0] = (void*)Payload;

	// Allocate Process
	FCsCraftingProcess* Process = AllocateProcess();
	Process->R					= R;
	Process->Instigator			= Payload->GetInstigator();

	R->voidPointers[1] = (void*)Process;

	// Start Routine
	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(ACsManager_Crafting, CraftItems_Internal)
{
	ACsManager_Crafting* c	 = Cast<ACsManager_Crafting>(r->GetActor());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = c->GetWorld();
	
	ACsManager_Item* Manager_Item			= ACsManager_Item::Get(w);
	FCsCraftingPayload* Payload				= (FCsCraftingPayload*)r->voidPointers[0];
	ACsManager_Inventory* Manager_Inventory = Payload->GetManager_Inventory();
	AActor* InventoryOwner					= Manager_Inventory->GetMyOwner();
	ACsData_Recipe* Recipe					= Payload->GetRecipe();

	TArray<FCsRecipeIngredient>* Ingredients = Recipe->GetIngredients();

	const bool UseBulkTime	= Recipe->GetUseBulkTime();
	const int32 ProcessCount = UseBulkTime ? 1 : Payload->Count;
	const float Time		= UseBulkTime ? Recipe->GetUseBulkTime() : Recipe->GetTime();
	const float& StartTime	= r->floats[0];
	const float CurrentTime	= w->GetTimeSeconds();

	const int32& Index = r->indexers[0];

	FCsCraftingProcess* Process = (FCsCraftingProcess*)r->voidPointers[1];

	CS_COROUTINE_BEGIN(r);

	// Log Begin
	if (CsCVarLogManagerCraftingTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString RecipeName = Recipe->ShortCode.ToString();
		const FString ItemName   = Recipe->GetCreatedItem().ToString();

		UE_LOG(LogCs, Warning, TEXT("ACsManager_Crafting::CraftItems_Internal: Beginning crafting (Process: %d, Payload: %d) for Recipe: %s to create Item: %s."), Process->Id, Payload->Id, *RecipeName, *ItemName);
	}

	c->OnBeginCraftingProcess_Event.Broadcast(Process->Id, Payload->Id);
	c->OnBeginCraftingProcess_Event.Clear();

	do
	{
		CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime < Time);

		{
			const int32 Count = UseBulkTime ? Payload->Count : 1;

			for (int32 I = 0; I < Count; ++I)
			{
				// Create the Item
				FCsItem* CreatedItem = Manager_Item->Allocate(Recipe->GetCreatedItem(), Payload->AddToInventory ? Cast<UObject>(InventoryOwner) : w);

				if (Payload->AddToInventory)
				{
					CreatedItem->InventoryProperties.SetVisible();
					CreatedItem->InventoryProperties.Bag = Payload->Bag;
				}

				const int32 IngredientCount = Ingredients->Num();

				for (int32 J = 0; J < IngredientCount; ++J)
				{
					const FCsRecipeIngredient& Ingredient = (*Ingredients)[J];
					// Process Items
					TArray<FCsItem*> ProcessedItems;
					Payload->ProcessItems(Ingredient.ShortCode, Ingredient.Count, ProcessedItems);

					const int32 ProcessedItemCount = ProcessedItems.Num();

					for (int32 K = 0; K < ProcessedItemCount; ++K)
					{
						// Consume
						if (Ingredient.Consume)
						{
							Manager_Inventory->ConsumeItem(ProcessedItems[K]);
						}
						// Add to Contents
						if (Ingredient.AddToContents)
						{
							CreatedItem->Contents.Add(ProcessedItems[K]->UniqueId);
							Manager_Inventory->HideItem(ProcessedItems[K]);
						}
					}
				}
				Payload->OutItems.Add(CreatedItem);
				Manager_Item->Save(CreatedItem);

				// Log Craft
				if (CsCVarLogManagerCraftingTransactions->GetInt() == CS_CVAR_SHOW_LOG)
				{
					const FString ItemName   = Recipe->GetCreatedItem().ToString();
					const FString RecipeName = Recipe->ShortCode.ToString();

					UE_LOG(LogCs, Warning, TEXT("ACsManager_Crafting::CraftItems_Internal: Crafted (Process: %d, Payload: %d) Item: %s for Recipe: %s."), Process->Id, Payload->Id, *ItemName, *RecipeName);
				}

				Process->OnCraftItem_Event.Broadcast(Process->Id, Payload->Id);
			}
		}
		r->indexers[0]++;
	} while (Index < ProcessCount);

	// Check to Add Crafted Items to the Inventory
	if (Payload->AddToInventory)
		Manager_Inventory->AddItems(Payload->OutItems);

	// Log Finish
	if (CsCVarLogManagerCraftingTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString RecipeName = Recipe->ShortCode.ToString();
		const FString ItemName   = Recipe->GetCreatedItem().ToString();
		const int32 ItemCount	 = Payload->OutItems.Num();

		UE_LOG(LogCs, Warning, TEXT("ACsManager_Crafting::CraftItems_Internal: Finishing crafting (Process: %d, Payload: %d) for Recipe: %s to create %d Items: %s."), Process->Id, Payload->Id, *RecipeName, ItemCount, *ItemName);
	}

	Process->OnFinishCraftingProcess_Event.Broadcast(Process->Id, Payload->Id);

	// Free the Payload
	c->PayloadMap.Remove(Payload->Id);
	Payload->Reset();
	// Free the Process
	c->ProcessMap.Remove(Process->Id);
	Process->Reset();

	CS_COROUTINE_END(r);
}

void ACsManager_Crafting::CancelCraftingProcess(const uint64 &Id)
{
	FCsCraftingProcess** ProcessPtr = ProcessMap.Find(Id);

	if (!ProcessPtr)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Crafting::CancelCraftingProcess: Attemping to cancel Crafting Process: %d, but it does NOT exist."), Id);
		return;
	}

	FCsCraftingProcess* Process	= *ProcessPtr;
	FCsCraftingPayload* Payload = (FCsCraftingPayload*)(Process->R->voidPointers[0]);

	if (CsCVarLogManagerCraftingTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		ACsData_Recipe* Recipe	 = Payload->GetRecipe();
		const FString RecipeName = Recipe->ShortCode.ToString();
		const FString ItemName	 = Recipe->GetCreatedItem().ToString();
		UObject* Instigator		 = Process->GetInstigator();
		const FString InstigatorName = Instigator->GetName();

		UE_LOG(LogCs, Warning, TEXT("ACsManager_Crafting::CancelCraftingProcess: Canceling crafting (Process: %d, Payload: %d) for Recipe: %s to create Item: %s started by %s."), Process->Id, Payload->Id, *RecipeName, *ItemName, *InstigatorName);
	}

	// Free the Payload
	PayloadMap.Remove(Payload->Id);
	Payload->Reset();
	// End the Routine
	Process->R->End(ECsCoroutineEndReason::Manual);
	// Free the Process
	ProcessMap.Remove(Id);
	Process->Reset();
}

void ACsManager_Crafting::CancelCraftingProcesses(UObject* Instigator)
{
	TArray<uint64> Keys;
	ProcessMap.GetKeys(Keys);

	const int32 Count = Keys.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const uint64& Id			= Keys[I];
		FCsCraftingProcess* Process = *(ProcessMap.Find(Id));

		if (Instigator == Process->GetInstigator())
		{
			FCsCraftingPayload* Payload = (FCsCraftingPayload*)(Process->R->voidPointers[0]);

			if (CsCVarLogManagerCraftingTransactions->GetInt() == CS_CVAR_SHOW_LOG)
			{
				ACsData_Recipe* Recipe	 = Payload->GetRecipe();
				const FString RecipeName = Recipe->ShortCode.ToString();
				const FString ItemName   = Recipe->GetCreatedItem().ToString();
				const FString InstigatorName = Instigator->GetName();

				UE_LOG(LogCs, Warning, TEXT("ACsManager_Crafting::CancelCraftingProcesses: Canceling crafting (Process: %d, Payload: %d) for Recipe: %s to create Item: %s started by %s."), Process->Id, Payload->Id, *RecipeName, *ItemName, *InstigatorName);
			}

			// Free the Payload
			PayloadMap.Remove(Payload->Id);
			Payload->Reset();
			// End the Routine
			Process->R->End(ECsCoroutineEndReason::Manual);
			// Free the Process
			ProcessMap.Remove(Id);
			Process->Reset();
		}
	}
}