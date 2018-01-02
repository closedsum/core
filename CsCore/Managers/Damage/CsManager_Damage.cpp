// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsManager_Damage.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Game/CsGameState.h"

ACsManager_Damage::ACsManager_Damage(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	for (uint8 I = 0; I < CS_DAMAGE_POOL_SIZE; ++I)
	{
		Pool[I].Init(I);
	}
}

/*static*/ ACsManager_Damage* ACsManager_Damage::Get(UWorld* InWorld)
{
	return nullptr;// InWorld->GetGameState<ACsGameState>()->Manager_Item;
}

FCsDamageEvent* ACsManager_Damage::Allocate()
{
	for (uint8 I = 0; I < CS_DAMAGE_POOL_SIZE; ++I)
	{
		const uint8 Index	   = (PoolIndex + I) % CS_DAMAGE_POOL_SIZE;
		FCsDamageEvent* Event = &(Pool[Index]);

		//if (Event->Index == CS_DAMAGE_POOL_INVALID_INDEX)
		//	Event->Init(I);

		if (!Event->IsAllocated)
		{
			Event->IsAllocated = true;
			ActiveEvents.Add(Event);
			return Event;
		}
	}
	checkf(0, TEXT("ACsManager_Damage::Allocate: Pool is exhausted"));
	return nullptr;
}

void ACsManager_Damage::DeAllocate(const uint8 &Index)
{
	for (int32 I = CS_DAMAGE_POOL_SIZE - 1; I >= 0; --I)
	{
		FCsDamageEvent* Event = ActiveEvents[I];

		if (Index == Event->Index)
		{
			Event->Reset();
			ActiveEvents.RemoveAt(I);
			break;
		}
	}
	UE_LOG(LogCs, Warning, TEXT("ACsManager_Damage::DeAllocate: Attempting to deallocate a DamageEvent with Index: %d, but it is already deallocated."), Index);
}

void ACsManager_Damage::DeAllocate(FCsDamageEvent* InEvent)
{
	DeAllocate(InEvent->Index);
}