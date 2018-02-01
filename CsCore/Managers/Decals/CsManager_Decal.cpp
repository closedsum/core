// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Decals/CsManager_Decal.h"
#include "CsCore.h"
#include "Game/CsGameState.h"

ACsManager_Decal::ACsManager_Decal(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PoolSize = 1;
}

void ACsManager_Decal::Shutdown()
{
	Super::Shutdown();

	DeAllocateAll();
	Pool.Reset();
	ActiveDecals.Reset();
}

void ACsManager_Decal::Destroyed()
{
	Shutdown();

	Super::Destroyed();
}

void ACsManager_Decal::CreatePool(const int32 &Size)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	for (int32 I = 0; I < Size; ++I)
	{
		ADecalActor* DecalActor = GetWorld()->SpawnActor<ADecalActor>(SpawnInfo);
		DecalActor->SetActorHiddenInGame(true);
		FCsDecalCache DecalCache;
		DecalCache.DecalActor = DecalActor;
		DecalCache.PoolIndex = I;
		Pool.Add(DecalCache);
	}
}

void ACsManager_Decal::OnTick(const float &DeltaSeconds)
{
	/*
	const uint8 Count = ActiveWidgetActors.Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
	ACsWidgetActor* Widget = ActiveWidgetActors[I];

	if (GetWorld()->TimeSeconds - Sound->Cache.Time > Sound->Cache.Duration)
	{
	Widget->DeAllocate();
	ActiveWidgetActors.RemoveAt(I);
	}
	}
	*/
}

/*static*/ ACsManager_Decal* ACsManager_Decal::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_Decal;
}

FCsDecalCache ACsManager_Decal::Allocate()
{
	if (Pool.Num() < 1)
	{
		DeAllocate(0);
	}

	FCsDecalCache Decal = Pool.Pop();
	Decal.DecalActor->SetActorHiddenInGame(false);
	Decal.Index = ActiveDecals.Num();
	ActiveDecals.Add(Decal);

	return Decal;
}

void ACsManager_Decal::DeAllocate(const int32 &Index)
{
	FCsDecalCache Decal = ActiveDecals[Index];
	Decal.DecalActor->SetActorHiddenInGame(true);
	ActiveDecals.RemoveAt(Index);
	Pool.Add(Decal);

}

void ACsManager_Decal::DeAllocateAll()
{
	for (int32 I = ActiveDecals.Num() - 1; I >= 0; I--)
	{
		DeAllocate(I);
	}
}
