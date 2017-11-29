// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Button/CsButtonComponent.h"
#include "CsCore.h"
#include "Components/CsWidgetComponent.h"
#include "Components/CsSkeletalMeshComponent.h"
#include "Components/CsStaticMeshComponent.h"

UCsButtonComponent::UCsButtonComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UCsButtonComponent::OnConstructor(const FObjectInitializer& ObjectInitializer)
{
	// Widget
	if (UseWidget)
	{
		WidgetComponent = ObjectInitializer.CreateDefaultSubobject<UCsWidgetComponent>(this, TEXT("WidgetComponent"));
		WidgetComponent->SetupAttachment(this);
		VisualComponent = WidgetComponent;
	}
	// Skeletal Mesh
	if (UseSkeletalMesh)
	{
		SkeletalMeshComponent = ObjectInitializer.CreateDefaultSubobject<UCsSkeletalMeshComponent>(this, TEXT("SkeletalMeshComponent"));
		SkeletalMeshComponent->SetupAttachment(this);
		VisualComponent = SkeletalMeshComponent;
	}
	// Static Mesh
	if (UseStaticMesh)
	{
		StaticMeshComponent = ObjectInitializer.CreateDefaultSubobject<UCsStaticMeshComponent>(this, TEXT("StaticMeshComponent"));
		StaticMeshComponent->SetupAttachment(this);
		VisualComponent = StaticMeshComponent;
	}
}

// State
#pragma region

void UCsButtonComponent::AddInstigator(const TEnumAsByte<ECsButtonState::Type> &InState, UObject* InInstigator)
{
	TArray<TWeakObjectPtr<UObject>>* Objects = Instigators.Find(InState);

	if (!Objects)
	{
		TArray<TWeakObjectPtr<UObject>> ObjectsToAdd;
		ObjectsToAdd.Add(InInstigator);
		Instigators.Add(InState, ObjectsToAdd);
		return;
	}

	// TODO: Potentially setup code flow that it is NOT possible to Add the same Instigator twice
	const int32 Count = Objects->Num();

	for (int32 I = 0; I < Count; I++)
	{
		UObject* Object = (*Objects)[I].IsValid() ? (*Objects)[I].Get() : nullptr;

		if (Object == InInstigator)
			return;
	}
	Objects->Add(InInstigator);
}

void UCsButtonComponent::RemoveInstigator(const TEnumAsByte<ECsButtonState::Type> &InState, UObject* InInstigator)
{
	TArray<TWeakObjectPtr<UObject>>* Objects = Instigators.Find(InState);

	if (!Objects)
	{
		TArray<TWeakObjectPtr<UObject>> ObjectsToAdd;
		Instigators.Add(InState, ObjectsToAdd);
		return;
	}

	bool Found = false;
	const int32 Count = Objects->Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		UObject* Object = (*Objects)[I].IsValid() ? (*Objects)[I].Get() : nullptr;

		if (Object == InInstigator)
		{
			Objects->RemoveAt(I);
			Found = true;
		}
	}
	/*
	if (!Found)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsButtonComponent::RemoveInstigator(%s - %s): Failed to find Instigator: %s in %s List."), *GetName(), *((*InteractiveTypeToString)(Type)), *(InInstigator->GetName()), *ECsInteractiveState::ToString(InState));
	}
	*/
}

void UCsButtonComponent::ClearInstigators()
{
	for (int32 I = 0; I < ECS_BUTTON_STATE_MAX; I++)
	{
		TArray<TWeakObjectPtr<UObject>>* Objects = Instigators.Find((TCsButtonState)I);

		if (!Objects)
			continue;

		Objects->Reset();
	}
}

TArray<TWeakObjectPtr<UObject>>* UCsButtonComponent::GetInstigators(const TEnumAsByte<ECsButtonState::Type> &InState)
{
	return Instigators.Find(InState);
}

void UCsButtonComponent::GetInstigators_Script(const TEnumAsByte<ECsButtonState::Type> &InState, TArray<UObject*> OutInstigators)
{
	TArray<TWeakObjectPtr<UObject>>* Objects = GetInstigators(InState);

	if (!Objects)
		return;

	const int32 Count = Objects->Num();

	for (int32 I = 0; I < Count; I++)
	{
		UObject* Object = (*Objects)[I].IsValid() ? (*Objects)[I].Get() : nullptr;

		if (Object)
			OutInstigators.Add(Object);
	}
}

void UCsButtonComponent::OnInteraction_Script(const TEnumAsByte<ECsButtonState::Type> &InState, UObject* InInstigator)
{
	if (InState == ECsButtonState::FirstHover) { OnFirstHover(InInstigator); return; }
	if (InState == ECsButtonState::Hover) { OnHover(InInstigator); return; }
	if (InState == ECsButtonState::FirstUnHover) { OnFirstUnHover(InInstigator); return; }
	if (InState == ECsButtonState::FirstPressed) { OnFirstPressed(InInstigator); return; }
	if (InState == ECsButtonState::Pressed) { OnPressed(InInstigator); return; }
	if (InState == ECsButtonState::FirstReleased) { OnFirstReleased(InInstigator); return; }
}

void UCsButtonComponent::OnInteraction(UObject* InInstigator)
{
}

void UCsButtonComponent::OnFirstHover(UObject* InInstigator)
{
	AddInstigator(ECsButtonState::FirstHover, InInstigator);
	State = ECsButtonState::FirstHover;
}

void UCsButtonComponent::OnHover(UObject* InInstigator)
{
	State = ECsButtonState::Hover;
}

void UCsButtonComponent::OnFirstUnHover(UObject* InInstigator)
{
	RemoveInstigator(ECsButtonState::FirstHover, InInstigator);
	RemoveInstigator(ECsButtonState::Hover, InInstigator);
	State = ECsButtonState::FirstUnHover;
}

void UCsButtonComponent::OnFirstPressed(UObject* InInstigator)
{
	AddInstigator(ECsButtonState::FirstPressed, InInstigator);
	State = ECsButtonState::FirstPressed;
}

void UCsButtonComponent::OnPressed(UObject* InInstigator)
{
	State = ECsButtonState::Pressed;
}

void UCsButtonComponent::OnFirstReleased(UObject* InInstigator)
{
	RemoveInstigator(ECsButtonState::FirstReleased, InInstigator);
	State = ECsButtonState::FirstReleased;
}

bool UCsButtonComponent::CanChangeState(const TEnumAsByte<ECsButtonState::Type> &FromState, const TEnumAsByte<ECsButtonState::Type> &ToState)
{
	return true;
}

bool UCsButtonComponent::CanChangeFromAnyState(const TArray<TEnumAsByte<ECsButtonState::Type>> &FromStates, const TEnumAsByte<ECsButtonState::Type> &ToState)
{
	const int32 Count = FromStates.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (CanChangeState(FromStates[I], ToState))
			return true;
	}
	return false;
}

#pragma endregion State

void UCsButtonComponent::Show()
{
	SetVisibility(true);
	SetHiddenInGame(false);

	if (VisualComponent)
	{
		VisualComponent->SetVisibility(true);
		VisualComponent->SetHiddenInGame(false);
		VisualComponent->SetComponentTickEnabled(true);
	}
	SetComponentTickEnabled(true);
}

void UCsButtonComponent::Hide()
{
	SetVisibility(false);
	SetHiddenInGame(true);

	if (VisualComponent)
	{
		VisualComponent->SetVisibility(false);
		VisualComponent->SetHiddenInGame(true);
		VisualComponent->SetComponentTickEnabled(false);
	}
	SetComponentTickEnabled(false);
}