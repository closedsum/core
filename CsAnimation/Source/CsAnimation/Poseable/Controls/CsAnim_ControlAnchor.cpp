// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Poseable/Controls/CsAnim_ControlAnchor.h"
#include "CsAnimation.h"

// Library
#include "Library/CsLibrary_Common.h"

ACsAnim_ControlAnchor::ACsAnim_ControlAnchor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	DefaultRootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("DefaultRootComponent"));
	DefaultRootComponent->SetMobility(EComponentMobility::Movable);
	SetRootComponent(DefaultRootComponent);
}

void ACsAnim_ControlAnchor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

#if WITH_EDITOR
	// Handle Waypoints placed in Editor
	if (UCsLibrary_Common::IsPlayInEditor(GetWorld()))
	{
		OnTick_Editor(DeltaSeconds);
		return;
	}
#endif // #if WITH_EDITOR
}

bool ACsAnim_ControlAnchor::ShouldTickIfViewportsOnly() const
{
#if WITH_EDITOR
	if (UCsLibrary_Common::IsPlayInEditor(GetWorld()))
		return true;
#endif // #if WITH_EDITOR
	return Super::ShouldTickIfViewportsOnly();
}

void ACsAnim_ControlAnchor::OnTick_Editor(const float &DeltaSeconds)
{
	if (!HasTickedInEditor)
	{
		HasTickedInEditor = true;
	}
}