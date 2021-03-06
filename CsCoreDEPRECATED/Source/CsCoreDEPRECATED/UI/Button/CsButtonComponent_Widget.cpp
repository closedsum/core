// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Button/CsButtonComponent_Widget.h"
#include "CsCoreDEPRECATED.h"

UCsButtonComponent_Widget::UCsButtonComponent_Widget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsButtonComponent_Widget::OnConstructor(const FObjectInitializer& ObjectInitializer){}

// State
#pragma region

void UCsButtonComponent_Widget::AddInstigator(const ECsButtonState &InState, UObject* InInstigator)
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

	for (int32 I = 0; I < Count; ++I)
	{
		UObject* Object = (*Objects)[I].IsValid() ? (*Objects)[I].Get() : nullptr;

		if (Object == InInstigator)
			return;
	}
	Objects->Add(InInstigator);
}

void UCsButtonComponent_Widget::RemoveInstigator(const ECsButtonState &InState, UObject* InInstigator)
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

	for (int32 I = Count - 1; I >= 0; --I)
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
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsButtonComponent_Widget::RemoveInstigator(%s - %s): Failed to find Instigator: %s in %s List."), *GetName(), *((*InteractiveTypeToString)(Type)), *(InInstigator->GetName()), *ECsInteractiveState::ToString(InState));
	}
	*/
}

void UCsButtonComponent_Widget::ClearInstigators()
{
	for (const ECsButtonState& Enum : EMCsButtonState::Get())
	{
		TArray<TWeakObjectPtr<UObject>>* Objects = Instigators.Find(Enum);

		if (!Objects)
			continue;

		Objects->Reset();
	}
}

TArray<TWeakObjectPtr<UObject>>* UCsButtonComponent_Widget::GetInstigators(const ECsButtonState &InState)
{
	return Instigators.Find(InState);
}

void UCsButtonComponent_Widget::GetInstigators_Script(const ECsButtonState &InState, TArray<UObject*> OutInstigators)
{
	TArray<TWeakObjectPtr<UObject>>* Objects = GetInstigators(InState);

	if (!Objects)
		return;

	const int32 Count = Objects->Num();

	for (int32 I = 0; I < Count; ++I)
	{
		UObject* Object = (*Objects)[I].IsValid() ? (*Objects)[I].Get() : nullptr;

		if (Object)
			OutInstigators.Add(Object);
	}
}

void UCsButtonComponent_Widget::OnInteraction_Script(const ECsButtonState &InState, UObject* InInstigator)
{
	if (InState == ECsButtonState::FirstHover) { OnFirstHover(InInstigator); return; }
	if (InState == ECsButtonState::Hover) { OnHover(InInstigator); return; }
	if (InState == ECsButtonState::FirstUnHover) { OnFirstUnHover(InInstigator); return; }
	if (InState == ECsButtonState::FirstPressed) { OnFirstPressed(InInstigator); return; }
	if (InState == ECsButtonState::Pressed) { OnPressed(InInstigator); return; }
	if (InState == ECsButtonState::FirstReleased) { OnFirstReleased(InInstigator); return; }
}

void UCsButtonComponent_Widget::OnInteraction(UObject* InInstigator)
{
}

void UCsButtonComponent_Widget::OnFirstHover(UObject* InInstigator)
{
	AddInstigator(ECsButtonState::FirstHover, InInstigator);
	State = ECsButtonState::FirstHover;
}

void UCsButtonComponent_Widget::OnHover(UObject* InInstigator)
{
	State = ECsButtonState::Hover;
}

void UCsButtonComponent_Widget::OnFirstUnHover(UObject* InInstigator)
{
	RemoveInstigator(ECsButtonState::FirstHover, InInstigator);
	RemoveInstigator(ECsButtonState::Hover, InInstigator);
	State = ECsButtonState::FirstUnHover;
}

void UCsButtonComponent_Widget::OnFirstPressed(UObject* InInstigator)
{
	AddInstigator(ECsButtonState::FirstPressed, InInstigator);
	State = ECsButtonState::FirstPressed;
}

void UCsButtonComponent_Widget::OnPressed(UObject* InInstigator)
{
	State = ECsButtonState::Pressed;
}

void UCsButtonComponent_Widget::OnFirstReleased(UObject* InInstigator)
{
	RemoveInstigator(ECsButtonState::FirstReleased, InInstigator);
	State = ECsButtonState::FirstReleased;
}

bool UCsButtonComponent_Widget::CanChangeState(const ECsButtonState &FromState, const ECsButtonState &ToState)
{
	return true;
}

bool UCsButtonComponent_Widget::CanChangeFromAnyState(const TArray<ECsButtonState> &FromStates, const ECsButtonState &ToState)
{
	const int32 Count = FromStates.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (CanChangeState(FromStates[I], ToState))
			return true;
	}
	return false;
}

#pragma endregion State

void UCsButtonComponent_Widget::Show()
{
	SetVisibility(true);
	SetHiddenInGame(false);
	SetComponentTickEnabled(true);
}

void UCsButtonComponent_Widget::Hide()
{
	SetVisibility(false);
	SetHiddenInGame(true);
	SetComponentTickEnabled(false);
}