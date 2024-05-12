// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Singleton/CsManager_Singleton_Actor.h"

// Library
#include "Library/CsLibrary_World.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_Singleton_Actor)

ACsManager_Singleton_Actor::ACsManager_Singleton_Actor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// UObject Interface
#pragma region

void ACsManager_Singleton_Actor::BeginDestroy()
{
	Super::BeginDestroy();

	ShutdownSingletons();
}

#pragma endregion UObject Interface

// AActor Interface
#pragma region

void ACsManager_Singleton_Actor::PostActorCreated()
{
	Super::PostActorCreated();

	typedef NCsWorld::FLibrary WorldLibrary;

	if (WorldLibrary::IsPlayInEditor(GetWorld()) ||
		WorldLibrary::IsPlayInEditorPreview(GetWorld()))
	{
		SetupSingletons();

		OnDestroyed.AddDynamic(this, &ACsManager_Singleton_Actor::OnDestroy);
	}
}

#pragma endregion AActor Interface

void ACsManager_Singleton_Actor::OnDestroy(AActor* Actor)
{
	ShutdownSingletons();
}