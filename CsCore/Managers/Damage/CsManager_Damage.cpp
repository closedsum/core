// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsManager_Damage.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

// Game
#include "Game/CsGameState.h"

// static initializations
TWeakObjectPtr<UObject> ACsManager_Damage::MyOwner;

ACsManager_Damage::ACsManager_Damage(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Event
	for (uint8 I = 0; I < CS_DAMAGE_EVENT_POOL_SIZE; ++I)
	{
		EventPool[I].Init(I);
	}
	// Result
	for (uint8 I = 0; I < CS_DAMAGE_RESULT_POOL_SIZE; ++I)
	{
		ResultPool[I].Init(I);
	}
}

/*static*/ UObject* ACsManager_Damage::GetMyOwner() { return MyOwner.IsValid() ? MyOwner.Get() : nullptr; }

/*static*/ void ACsManager_Damage::Init(UObject* InOwner)
{
	MyOwner = InOwner;
}

/*static*/ ACsManager_Damage* ACsManager_Damage::Get(UWorld* InWorld)
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(InWorld))
	{
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		return Cast<ACsGameState>(GetMyOwner())->Manager_Damage;
	}
	return nullptr;
}

// Event
#pragma region

FCsDamageEvent* ACsManager_Damage::AllocateEvent()
{
	for (uint8 I = 0; I < CS_DAMAGE_EVENT_POOL_SIZE; ++I)
	{
		EventPoolIndex		  = (EventPoolIndex + 1) % CS_DAMAGE_EVENT_POOL_SIZE;
		FCsDamageEvent* Event = &(EventPool[EventPoolIndex]);

		if (!Event->bAllocated)
		{
			Event->bAllocated = true;
			return Event;
		}
	}
	checkf(0, TEXT("ACsManager_Damage::AllocateEvent: Pool is exhausted"));
	return nullptr;
}

#pragma endregion Event

// Result
#pragma region

FCsDamageResult* ACsManager_Damage::AllocateResult()
{
	for (uint8 I = 0; I < CS_DAMAGE_RESULT_POOL_SIZE; ++I)
	{
		ResultPoolIndex			= (ResultPoolIndex + 1) % CS_DAMAGE_RESULT_POOL_SIZE;
		FCsDamageResult* Result = &(ResultPool[ResultPoolIndex]);

		if (!Result->bAllocated)
		{
			Result->bAllocated = true;
			return Result;
		}
	}
	checkf(0, TEXT("ACsManager_Damage::AllocateResult: Pool is exhausted"));
	return nullptr;
}

#pragma endregion Result