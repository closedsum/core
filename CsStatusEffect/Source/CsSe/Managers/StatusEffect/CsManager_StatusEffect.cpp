// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StatusEffect/CsManager_StatusEffect.h"
#include "CsSe.h"

// Coordinator
#include "Coordinator/CsStatusEffectCoordinator.h"
// Game
#include "GameFramework/GameStateBase.h"
// World
#include "Classes/Engine/World.h"

UCsManager_StatusEffect::UCsManager_StatusEffect(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsManager_StatusEffect::Init(UObject* InRoot)
{
	SetMyRoot(InRoot);

	// TODO: Add Config

	static const int32 PoolSize = 32;

	Manager_Event.CreatePool(PoolSize);
}

void UCsManager_StatusEffect::Shutdown(UObject* InRoot)
{
	// Deallocate any ICsStatusEffectEvent objects from UCsStatusEffectCoordinator 
	UObject* Object			  = MyRoot.GetObject();
	UWorld* World			  = Object ? Object->GetWorld() : nullptr;
	AGameStateBase* GameState = World ? World->GetGameState() : nullptr;
	
	if (GameState &&
		UCsStatusEffectCoordinator::IsValid(GameState))
	{
		UCsStatusEffectCoordinator* StatusEffectCoordinator = UCsStatusEffectCoordinator::Get(GameState);

		TCsDoubleLinkedList<FCsResource_StatusEffectEventInfo*>* Current = Manager_Event.GetAllocatedHead();
		TCsDoubleLinkedList<FCsResource_StatusEffectEventInfo*>* Next	 = Current;

		while (Next)
		{
			Current										 = Next;
			FCsResource_StatusEffectEventInfo* Container = **Current;
			Next										 = Current->GetNextLink();

			FCsStatusEffectEventInfo* Info = Container->Get();

			if (Info->Container)
			{
				StatusEffectCoordinator->DeallocateEvent(Info->Container);
			}
		}
	}
	Manager_Event.Shutdown();
}
	// Root
#pragma region

void UCsManager_StatusEffect::SetMyRoot(UObject* InRoot)
{
	MyRoot.SetObject(InRoot);
}

#pragma endregion Root

void UCsManager_StatusEffect::Update(const FCsDeltaTime& DeltaTime)
{
	TCsDoubleLinkedList<FCsResource_StatusEffectEventInfo*>* Current = Manager_Event.GetAllocatedHead();
	TCsDoubleLinkedList<FCsResource_StatusEffectEventInfo*>* Next	 = Current;

	while (Next)
	{
		Current										 = Next;
		FCsResource_StatusEffectEventInfo* Container = **Current;
		Next										 = Current->GetNextLink();

		FCsStatusEffectEventInfo* Info = Container->Get();

		// Check Apply Status Effect
		if (Info->CanApply())
		{
			MyRoot.ApplyStatusEffect(Info->Event);

			Info->Increment();
		}

		// Check Complete
		if (Info->IsComplete())
		{
			Info->Reset();
			Manager_Event.Deallocate(Container);
		}
		// Update
		else
		{
			Info->Update(DeltaTime);
		}
	}
}

void UCsManager_StatusEffect::ApplyStatusEffect(FCsResource_StatusEffectEvent* Event)
{
	checkf(Event, TEXT("UCsManager_StatusEffect::ApplyStatusEffect::Event is NULL."));

	FCsResource_StatusEffectEventInfo* EventInfoContainer = Manager_Event.Allocate();
	FCsStatusEffectEventInfo* EventInfo					  = EventInfoContainer->Get();

	EventInfo->SetEvent(Event);
}

void UCsManager_StatusEffect::ApplyStatusEffect(ICsStatusEffectEvent* Event)
{
	checkf(Event, TEXT("UCsManager_StatusEffect::ApplyStatusEffect::Event is NULL."));
}