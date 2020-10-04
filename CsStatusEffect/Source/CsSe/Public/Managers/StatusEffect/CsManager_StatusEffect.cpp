// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StatusEffect/CsManager_StatusEffect.h"
#include "CsSe.h"

// Coordinator
#include "Coordinators/StatusEffect/CsCoordinator_StatusEffect.h"
// Game
#include "GameFramework/GameStateBase.h"
// World
#include "Engine/World.h"

// Cached
#pragma region

namespace NCsManagerStatusEffectCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_StatusEffect, Shutdown);
	}
}

#pragma endregion Cached

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
	using namespace NCsManagerStatusEffectCached;

	const FString& Context = Str::Shutdown;

	// Deallocate any NCsStatusEffect::NEvent::IEvent objects from UCsStatusEffectCoordinator 
	UObject* Object			  = MyRoot.GetObject();
	UWorld* World			  = Object ? Object->GetWorld() : nullptr;
	AGameStateBase* GameState = World ? World->GetGameState() : nullptr;
	
	if (GameState &&
		UCsCoordinator_StatusEffect::IsValid(GameState))
	{
		UCsCoordinator_StatusEffect* StatusEffectCoordinator = UCsCoordinator_StatusEffect::Get(GameState);

		TCsDoubleLinkedList<FCsResource_StatusEffectEventInfo*>* Current = Manager_Event.GetAllocatedHead();
		TCsDoubleLinkedList<FCsResource_StatusEffectEventInfo*>* Next	 = Current;

		while (Next)
		{
			Current										 = Next;
			FCsResource_StatusEffectEventInfo* Container = **Current;
			Next										 = Current->GetNextLink();

			NCsStatusEffect::NEvent::FInfo* Info = Container->Get();

			if (Info->Container)
			{
				StatusEffectCoordinator->DeallocateEvent(Context, Info->Container);
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

		NCsStatusEffect::NEvent::FInfo* Info = Container->Get();

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

	// TODO: Need to create a copy

	FCsResource_StatusEffectEventInfo* EventInfoContainer = Manager_Event.Allocate();
	NCsStatusEffect::NEvent::FInfo* EventInfo			  = EventInfoContainer->Get();

	EventInfo->SetEvent(Event);
}

#define EventType NCsStatusEffect::NEvent::IEvent
void UCsManager_StatusEffect::ApplyStatusEffect(EventType* Event)
{
#undef EventType
	checkf(Event, TEXT("UCsManager_StatusEffect::ApplyStatusEffect::Event is NULL."));
}