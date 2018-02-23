// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/CsAIPawn.h"
#include "CsCore.h"
#include "../AIModule/Classes/AIController.h"

ACsAIPawn::ACsAIPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationYaw = true;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI	  = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();
}


void ACsAIPawn::Init(const int32 &Index, const TCsAIType &InType)
{
	PoolIndex	= Index;
	Type		= InType;
	Type_Script = (uint8)Type;

	Cache.Set(Index, this);
}

void ACsAIPawn::OnCreatePool(){}
void ACsAIPawn::OnPostCreatePool(){}

template<typename T>
void ACsAIPawn::Allocate(const uint16 &ActiveIndex, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Cache.Init<T>(ActiveIndex, Time, RealTime, Frame, InOwner, InParent, InObject, OnDeAllocate);

	Allocate_Internal();
}

template<typename T>
void ACsAIPawn::Allocate(const uint16 &ActiveIndex, const float &Time, const float &RealTime, const uint64 &Frame, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Cache.Init<T>(ActiveIndex, Time, RealTime, Frame, InObject, OnDeAllocate);

	Allocate_Internal();
}

void ACsAIPawn::Allocate(const uint16 &ActiveIndex, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent)
{
	Cache.Init(ActiveIndex, Time, RealTime, Frame, InOwner, InParent);

	Allocate_Internal();
}

void ACsAIPawn::Allocate(const uint16 &ActiveIndex, const float &Time, const float &RealTime, const uint64 &Frame)
{
	Cache.Init(ActiveIndex, Time, RealTime, Frame);

	Allocate_Internal();
}

void ACsAIPawn::Allocate_Internal()
{
	SetActorTickEnabled(true);
}

void ACsAIPawn::DeAllocate()
{
	Cache.Reset();

	SetActorTickEnabled(false);
}

void ACsAIPawn::OnTick_HandleCVars(const float &DeltaSeconds){}