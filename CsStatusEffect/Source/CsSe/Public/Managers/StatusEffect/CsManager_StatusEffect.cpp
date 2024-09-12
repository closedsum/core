// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StatusEffect/CsManager_StatusEffect.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Coordinators/StatusEffect/CsLibrary_Coordinator_StatusEffect.h"
#include "Data/CsLibrary_Data_StatusEffect.h"
// Coordinator
#include "Coordinators/StatusEffect/CsCoordinator_StatusEffect.h"
// Interface
#include "Managers/Time/CsUpdate.h"
// StatusEffect
#include "CsStatusEffect.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_StatusEffect)

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

UCsManager_StatusEffect::UCsManager_StatusEffect(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	MyRoot(),
	Manager_Allocated()
{
}

void UCsManager_StatusEffect::Init(UObject* InRoot)
{
	SetMyRoot(InRoot);
}

void UCsManager_StatusEffect::Shutdown(UObject* InRoot)
{
	using namespace NCsManagerStatusEffect::NCached;

	const FString& Context = Str::Shutdown;

	// Deallocate any AllocatedType (NCsStatusEffect::FAllocated) objects from UCsStatusEffectCoordinator
	typedef NCsStatusEffect::NCoordinator::FLibrary SeCoordinatorLibrary;
	typedef NCsStatusEffect::NAllocated::FResource AllocatedResourceType;
	typedef NCsStatusEffect::FAllocated AllocatedType;

	if (UCsCoordinator_StatusEffect* StatusEffectCoordinator = SeCoordinatorLibrary::GetSafe(MyRoot.GetObject()))
	{
		TCsDoubleLinkedList<AllocatedResourceType*>* Current = Manager_Allocated.GetAllocatedHead();
		TCsDoubleLinkedList<AllocatedResourceType*>* Next	 = Current;

		while (Next)
		{
			Current							 = Next;
			AllocatedResourceType* Container = **Current;
			Next							 = Current->GetNextLink();

			AllocatedType* R = Container->Get();

			R->Reset();
		}
	}
	Manager_Allocated.Shutdown();
}
	// Root
#pragma region

void UCsManager_StatusEffect::SetMyRoot(UObject* InRoot)
{
	MyRoot.SetObject(InRoot);
}

#pragma endregion Root

void UCsManager_StatusEffect::CreatePool(const int32& PoolSize)
{
	Manager_Allocated.CreatePool(PoolSize);
}

void UCsManager_StatusEffect::Update(const FCsDeltaTime& DeltaTime)
{
	typedef NCsStatusEffect::NAllocated::FResource AllocatedResourceType;
	typedef NCsStatusEffect::FAllocated AllocatedType;

	TCsDoubleLinkedList<AllocatedResourceType*>* Current = Manager_Allocated.GetAllocatedHead();
	TCsDoubleLinkedList<AllocatedResourceType*>* Next	 = Current;

	while (Next)
	{
		Current							 = Next;
		AllocatedResourceType* Container = **Current;
		Next							 = Current->GetNextLink();

		typedef NCsStatusEffect::IStatusEffect StatusEffectType;

		AllocatedType* R			   = Container->Get();
		StatusEffectType* StatusEffect = R->Get();
		/*
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
		*/
	}
}

#define EventType NCsStatusEffect::NEvent::IEvent
void UCsManager_StatusEffect::ApplyStatusEffect(EventType* Event)
{
#undef EventType
	checkf(Event, TEXT("UCsManager_StatusEffect::ApplyStatusEffect::Event is NULL."));
}