// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Singleton/CsManager_Singleton_Actor.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_World.h"

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