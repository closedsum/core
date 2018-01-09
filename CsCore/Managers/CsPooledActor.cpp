// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsPooledActor.h"
#include "CsCore.h"
#include "CsCVars.h"

ACsPooledActor::ACsPooledActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	Warning_FellOutOfWorld	   = TEXT("ACsPooledActor::FellOutOfWorld");
	Warning_OutsideWorldBounds = TEXT("ACsPooledActor::OutsideWorldBounds");

	PoolIndex  = INDEX_NONE;
}

void ACsPooledActor::FellOutOfWorld(const class UDamageType& dmgType)
{
	UE_LOG(LogCs, Warning, TEXT("%s: Warning. Pool Objected with PoolIndex: %d is being FORCED DeAllocated."), *Warning_FellOutOfWorld, PoolIndex);
	DeAllocate();
}

void ACsPooledActor::OutsideWorldBounds()
{
	UE_LOG(LogCs, Warning, TEXT("%s: Warning. Pool Objected with PoolIndex: %d is being FORCED DeAllocated."), *Warning_OutsideWorldBounds, PoolIndex);
	DeAllocate();
}

void ACsPooledActor::OnTick(const float &DeltaSeconds){}

void ACsPooledActor::OnTick_HandleCVars(const float &DeltaSeconds)
{
	if (CsCVarDrawPooledActorRootLocation->GetInt() == CS_CVAR_DRAW)
	{
		if (USceneComponent* Root = GetRootComponent())
		{
			const float Radius = 12.0f;

			DrawDebugSphere(GetWorld(), Root->GetComponentLocation(), Radius, 16, FColor::Red, false, DeltaSeconds + 0.005f, 0, 0.25f);
		}
	}
}

void ACsPooledActor::DeAllocate(){}
void ACsPooledActor::OnCreatePool(){}
void ACsPooledActor::Show() { Visibility = ECsVisibility::Visible; }
void ACsPooledActor::Hide() { Visibility = ECsVisibility::Hidden; }