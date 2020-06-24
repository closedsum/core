// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Creep/UnitTest/CsTdCreep_UnitTest_A.h"
#include "CsTd.h"

// Pool
#include "Managers/Pool/CsPooledObjectCache.h"
#include "Managers/Pool/CsPooledObjectPayload.h"
// Components
#include "Components/StaticMeshComponent.h"
// Creep
#include "Managers/Creep/Cache/CsTdCreepPooledCacheImpl.h"

ACsTdCreep_UnitTest_A::ACsTdCreep_UnitTest_A(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->Mobility = EComponentMobility::Movable;
	StaticMeshComponent->SetGenerateOverlapEvents(false);

	RootComponent = StaticMeshComponent;
}

// UObject Interface
#pragma region

void ACsTdCreep_UnitTest_A::BeginDestroy()
{
	Super::BeginDestroy();

	delete Cache;
}

#pragma endregion UObject Interface

// AActor Interface
#pragma region

void ACsTdCreep_UnitTest_A::BeginPlay()
{
	Super::BeginPlay();

	Cache = new FCsTdCreepPooledCacheImpl();
}

#pragma endregion AActor Interface

// ICsUpdate
#pragma region

void ACsTdCreep_UnitTest_A::Update(const FCsDeltaTime& DeltaTime)
{
}

#pragma endregion ICsUpdate

// ICsPooledObject
#pragma region

ICsPooledObjectCache* ACsTdCreep_UnitTest_A::GetCache() const
{
	return Cache;
}

void ACsTdCreep_UnitTest_A::Allocate(ICsPooledObjectPayload* Payload)
{
}

void ACsTdCreep_UnitTest_A::Deallocate()
{

}

#pragma endregion ICsPooledObject