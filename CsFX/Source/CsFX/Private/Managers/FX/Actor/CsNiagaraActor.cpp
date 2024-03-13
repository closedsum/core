// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Actor/CsNiagaraActor.h"

// Niagara
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
#endif // #if WITH_EDITOR

ACsNiagaraActor::ACsNiagaraActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// AActor Interface
#pragma region

void ACsNiagaraActor::PostRegisterAllComponents()
{
	AActor::PostRegisterAllComponents();

	// Set Notification Delegate
	if (GetNiagaraComponent())
	{
		GetNiagaraComponent()->SetComponentTickEnabled(true);
		GetNiagaraComponent()->OnSystemFinished.AddUniqueDynamic(this, &ACsNiagaraActor::OnNiagaraSystemFinished2);
	}
}

bool ACsNiagaraActor::ShouldTickIfViewportsOnly() const
{
#if WITH_EDITOR
	typedef NCsWorld::FLibrary WorldLibrary;

	if (WorldLibrary::IsPlayInEditorOrEditorPreview(this))
	{
		return true;
	}
#endif // #if WITH_EDITOR
	return Super::ShouldTickIfViewportsOnly();
}

#if WITH_EDITOR

bool ACsNiagaraActor::GetReferencedContentObjects(TArray<UObject*>& Objects) const
{
	AActor::GetReferencedContentObjects(Objects);

	if (UNiagaraSystem* System = GetNiagaraComponent()->GetAsset())
	{
		Objects.Add(System);
	}

	return true;
}

#endif // WITH_EDITOR

#pragma endregion AActor Interface

void ACsNiagaraActor::OnNiagaraSystemFinished2(UNiagaraComponent* FinishedComponent)
{
	if (bDestroyOnSystemFinish2)
	{
		SetLifeSpan(0.0001f);
	}
}