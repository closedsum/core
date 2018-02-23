// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/CsAIPawn.h"
#include "CsCore.h"
#include "AI/CsAIController.h"

ACsAIPawn::ACsAIPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationYaw = true;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI	  = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACsAIController::StaticClass();
}


void ACsAIPawn::Init(const int32 &Index, const TCsAIType &InType)
{
	PoolIndex	= Index;
	Type		= InType;
	Type_Script = (uint8)Type;

	Cache.Set(Index, this);
}

void ACsAIPawn::OnCreatePool()
{
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ACsAIPawn::OnPostCreatePool(){}

template<typename T>
void ACsAIPawn::Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Cache.Init<T>(ActiveIndex, Time, RealTime, Frame, InOwner, InParent, InObject, OnDeAllocate);

	Allocate_Internal(Payload);
}

template<typename T>
void ACsAIPawn::Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Allocate<T>(ActiveIndex, Payload, Time, RealTime, Frame, nullptr, nullptr, InObject, OnDeAllocate);
}

void ACsAIPawn::Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent)
{
	Cache.Init(ActiveIndex, Time, RealTime, Frame, InOwner, InParent);

	Allocate_Internal(Payload);
}

void ACsAIPawn::Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame)
{
	Allocate(ActiveIndex, Payload, Time, RealTime, Frame, nullptr, nullptr);
}

void ACsAIPawn::Allocate_Internal(FCsAIPawnPayload* Payload)
{
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
}

void ACsAIPawn::DeAllocate()
{
	Cache.Reset();

	SetActorTickEnabled(false);
}

void ACsAIPawn::OnTick_HandleCVars(const float &DeltaSeconds){}