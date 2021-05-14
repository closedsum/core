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

namespace NCsManagerStatusEffect
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_StatusEffect, Shutdown);
		}
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
	using namespace NCsManagerStatusEffect::NCached;

	const FString& Context = Str::Shutdown;

	// Deallocate any NCsStatusEffect::NEvent::IEvent objects from UCsStatusEffectCoordinator 
	UObject* Object			  = MyRoot.GetObject();
	UWorld* World			  = Object ? Object->GetWorld() : nullptr;
	AGameStateBase* GameState = World ? World->GetGameState() : nullptr;
	
	typedef NCsStatusEffect::NEvent::NInfo::FResource EventInfoResourceType;
	typedef NCsStatusEffect::NEvent::NInfo::FImpl EventInfoType;

	if (GameState &&
		UCsCoordinator_StatusEffect::IsValid(GameState))
	{
		UCsCoordinator_StatusEffect* StatusEffectCoordinator = UCsCoordinator_StatusEffect::Get(GameState);

		TCsDoubleLinkedList<EventInfoResourceType*>* Current = Manager_Event.GetAllocatedHead();
		TCsDoubleLinkedList<EventInfoResourceType*>* Next	 = Current;

		while (Next)
		{
			Current										 = Next;
			EventInfoResourceType* Container = **Current;
			Next										 = Current->GetNextLink();

			EventInfoType* Info = Container->Get();

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
	typedef NCsStatusEffect::NEvent::NInfo::FResource EventInfoResourceType;
	typedef NCsStatusEffect::NEvent::NInfo::FImpl EventInfoType;

	TCsDoubleLinkedList<EventInfoResourceType*>* Current = Manager_Event.GetAllocatedHead();
	TCsDoubleLinkedList<EventInfoResourceType*>* Next	 = Current;

	while (Next)
	{
		Current										 = Next;
		EventInfoResourceType* Container = **Current;
		Next										 = Current->GetNextLink();

		EventInfoType* Info = Container->Get();

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

#define EventResourceType NCsStatusEffect::NEvent::FResource
void UCsManager_StatusEffect::ApplyStatusEffect(EventResourceType* Event)
{
#undef EventResourceType

	checkf(Event, TEXT("UCsManager_StatusEffect::ApplyStatusEffect::Event is NULL."));

	typedef NCsStatusEffect::NEvent::NInfo::FResource EventInfoResourceType;
	typedef NCsStatusEffect::NEvent::NInfo::FImpl EventInfoType;

	// TODO: Need to create a copy

	EventInfoResourceType* EventInfoContainer = Manager_Event.Allocate();
	EventInfoType* EventInfo				  = EventInfoContainer->Get();

	EventInfo->SetEvent(Event);
}

#define EventType NCsStatusEffect::NEvent::IEvent
void UCsManager_StatusEffect::ApplyStatusEffect(EventType* Event)
{
#undef EventType
	checkf(Event, TEXT("UCsManager_StatusEffect::ApplyStatusEffect::Event is NULL."));
}