// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Button/CsButtonComponent_StaticMesh.h"
#include "CsCore.h"

UCsButtonComponent_StaticMesh::UCsButtonComponent_StaticMesh(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsButtonComponent_StaticMesh::OnConstructor(const FObjectInitializer& ObjectInitializer){}

// State
#pragma region

void UCsButtonComponent_StaticMesh::AddInstigator(const TEnumAsByte<ECsButtonState::Type> &InState, UObject* InInstigator)
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

void UCsButtonComponent_StaticMesh::RemoveInstigator(const TEnumAsByte<ECsButtonState::Type> &InState, UObject* InInstigator)
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
		UE_LOG(LogCs, Warning, TEXT("UCsButtonComponent_StaticMesh::RemoveInstigator(%s - %s): Failed to find Instigator: %s in %s List."), *GetName(), *((*InteractiveTypeToString)(Type)), *(InInstigator->GetName()), *ECsInteractiveState::ToString(InState));
	}
	*/
}

void UCsButtonComponent_StaticMesh::ClearInstigators()
{
	for (int32 I = 0; I < ECS_BUTTON_STATE_MAX; I++)
	{
		TArray<TWeakObjectPtr<UObject>>* Objects = Instigators.Find((TCsButtonState)I);

		if (!Objects)
			continue;

		Objects->Reset();
	}
}

TArray<TWeakObjectPtr<UObject>>* UCsButtonComponent_StaticMesh::GetInstigators(const TEnumAsByte<ECsButtonState::Type> &InState)
{
	return Instigators.Find(InState);
}

void UCsButtonComponent_StaticMesh::GetInstigators_Script(const TEnumAsByte<ECsButtonState::Type> &InState, TArray<UObject*> OutInstigators)
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

void UCsButtonComponent_StaticMesh::OnInteraction_Script(const TEnumAsByte<ECsButtonState::Type> &InState, UObject* InInstigator)
{
	if (InState == ECsButtonState::FirstHover) { OnFirstHover(InInstigator); return; }
	if (InState == ECsButtonState::Hover) { OnHover(InInstigator); return; }
	if (InState == ECsButtonState::FirstUnHover) { OnFirstUnHover(InInstigator); return; }
	if (InState == ECsButtonState::FirstPressed) { OnFirstPressed(InInstigator); return; }
	if (InState == ECsButtonState::Pressed) { OnPressed(InInstigator); return; }
	if (InState == ECsButtonState::FirstReleased) { OnFirstReleased(InInstigator); return; }
}

void UCsButtonComponent_StaticMesh::OnInteraction(UObject* InInstigator)
{
}

void UCsButtonComponent_StaticMesh::OnFirstHover(UObject* InInstigator)
{
	AddInstigator(ECsButtonState::FirstHover, InInstigator);
	State = ECsButtonState::FirstHover;
}

void UCsButtonComponent_StaticMesh::OnHover(UObject* InInstigator)
{
	State = ECsButtonState::Hover;
}

void UCsButtonComponent_StaticMesh::OnFirstUnHover(UObject* InInstigator)
{
	RemoveInstigator(ECsButtonState::FirstHover, InInstigator);
	RemoveInstigator(ECsButtonState::Hover, InInstigator);
	State = ECsButtonState::FirstUnHover;
}

void UCsButtonComponent_StaticMesh::OnFirstPressed(UObject* InInstigator)
{
	AddInstigator(ECsButtonState::FirstPressed, InInstigator);
	State = ECsButtonState::FirstPressed;
}

void UCsButtonComponent_StaticMesh::OnPressed(UObject* InInstigator)
{
	State = ECsButtonState::Pressed;
}

void UCsButtonComponent_StaticMesh::OnFirstReleased(UObject* InInstigator)
{
	RemoveInstigator(ECsButtonState::FirstReleased, InInstigator);
	State = ECsButtonState::FirstReleased;
}

bool UCsButtonComponent_StaticMesh::CanChangeState(const TEnumAsByte<ECsButtonState::Type> &FromState, const TEnumAsByte<ECsButtonState::Type> &ToState)
{
	return true;
}

bool UCsButtonComponent_StaticMesh::CanChangeFromAnyState(const TArray<TEnumAsByte<ECsButtonState::Type>> &FromStates, const TEnumAsByte<ECsButtonState::Type> &ToState)
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

void UCsButtonComponent_StaticMesh::Show()
{
	SetVisibility(true);
	SetHiddenInGame(false);
	SetComponentTickEnabled(true);
}

void UCsButtonComponent_StaticMesh::Hide()
{
	SetVisibility(false);
	SetHiddenInGame(true);
	SetComponentTickEnabled(false);
}