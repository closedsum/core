// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Pawn/CsInteractiveAIPawn.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "CsCommon.h"

ACsInteractiveAIPawn::ACsInteractiveAIPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationYaw = true;

	State = ECsInteractiveState::ECsInteractiveState_MAX;


	PhysicsStateTimers.Reset();

	for (int32 I = 0; I < ECS_INTERACTIVE_PHYSICS_STATE_EDITOR_MAX; I++)
	{
		PhysicsStateTimers.Add(0.0f);
	}
}

void ACsInteractiveAIPawn::DeAllocate()
{
	Super::DeAllocate();

	State = ECsInteractiveState::None;
}

// State
#pragma region

void ACsInteractiveAIPawn::AddInteractedInfo(const TEnumAsByte<ECsInteractiveState::Type> &InState, const FCsInteractedActorInfo &Info)
{
	TArray<FCsInteractedActorInfo>* Infos = InteractedInfos.Find(InState);

	if (!Infos)
	{
		TArray<FCsInteractedActorInfo> InfosToAdd;
		InfosToAdd.AddDefaulted();
		InfosToAdd[CS_FIRST] = Info;
		InteractedInfos.Add(InState, InfosToAdd);
		return;
	}
	const int32 Count = Infos->Num();

	for (int32 I = 0; I < Count; I++)
	{
		if ((*Infos)[I].GetInstigator() == Info.GetInstigator())
			return;
	}
	Infos->AddDefaulted();
	(*Infos)[Infos->Num() - 1] = Info;
}

void ACsInteractiveAIPawn::RemoveInteractedInfo(const TEnumAsByte<ECsInteractiveState::Type> &InState, const FCsInteractedActorInfo &Info)
{
	TArray<FCsInteractedActorInfo>* Infos = InteractedInfos.Find(InState);

	if (!Infos)
	{
		TArray<FCsInteractedActorInfo> ObjectsToAdd;
		InteractedInfos.Add(InState, ObjectsToAdd);
		return;
	}

	bool Found = false;
	const int32 Count = Infos->Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		if ((*Infos)[I].GetInstigator() == Info.GetInstigator())
		{
			Infos->RemoveAt(I);
			Found = true;
		}
	}
	/*
	if (!Found)
	{
	UE_LOG(LogCs, Warning, TEXT("ACsInteractiveActor::RemoveInstigator(%s - %s): Failed to find Instigator: %s in %s List."), *GetName(), *((*InteractiveTypeToString)(Type)), *(InInstigator->GetName()), *ECsInteractiveState::ToString(InState));
	}
	*/
}

void ACsInteractiveAIPawn::ClearInteractedInfos()
{
	for (int32 I = 0; I < ECS_INTERACTIVE_STATE_MAX; I++)
	{
		TArray<FCsInteractedActorInfo>* Infos = InteractedInfos.Find((TCsInteractiveState)I);

		if (!Infos)
			continue;

		Infos->Reset();
	}
}

TArray<FCsInteractedActorInfo>* ACsInteractiveAIPawn::GetInteractedInfos(const TEnumAsByte<ECsInteractiveState::Type> &InState)
{
	return InteractedInfos.Find(InState);
}

void ACsInteractiveAIPawn::GetInteractedInfos_Script(const TEnumAsByte<ECsInteractiveState::Type> &InState, TArray<FCsInteractedActorInfo> &OutInfos)
{
	TArray<FCsInteractedActorInfo>* Infos = GetInteractedInfos(InState);

	if (!Infos)
		return;

	const int32 Count = Infos->Num();

	for (int32 I = 0; I < Count; I++)
	{
		OutInfos.AddDefaulted();
		OutInfos[I] = (*Infos)[I];
	}
}

void ACsInteractiveAIPawn::OnInteraction_Script(const TEnumAsByte<ECsInteractiveState::Type> &InState, const FCsInteractedActorInfo &Info)
{
	if (InState == ECsInteractiveState::FirstFreeze) { OnFirstFreeze(Info); return; }
	if (InState == ECsInteractiveState::Freeze) { OnFreeze(Info); return; }
	if (InState == ECsInteractiveState::FirstUnFreeze) { OnFirstUnFreeze(Info); return; }
	if (InState == ECsInteractiveState::FirstHold) { OnFirstHold(Info); return; }
	if (InState == ECsInteractiveState::Hold) { OnHold(Info); return; }
	if (InState == ECsInteractiveState::Release) { OnRelease(Info); return; }
	if (InState == ECsInteractiveState::FirstTouch) { OnFirstTouch(Info); return; }
	if (InState == ECsInteractiveState::Touch) { OnTouch(Info); return; }
	if (InState == ECsInteractiveState::FirstHover) { OnFirstHover(Info); return; }
	if (InState == ECsInteractiveState::Hover) { OnHover(Info); return; }
	if (InState == ECsInteractiveState::FirstUnHover) { OnFirstUnHover(Info); return; }
	if (InState == ECsInteractiveState::FirstCollide) { OnFirstCollide(Info); return; }
	if (InState == ECsInteractiveState::Collide) { OnCollide(Info); return; }
	if (InState == ECsInteractiveState::FirstUnCollide) { OnFirstUnCollide(Info); return; }
	if (InState == ECsInteractiveState::Remove) { OnRemove(Info); return; }
}

void ACsInteractiveAIPawn::OnInteraction(const FCsInteractedActorInfo &Info){}

void ACsInteractiveAIPawn::OnFirstFreeze(const FCsInteractedActorInfo &Info)
{
	AddInteractedInfo(ECsInteractiveState::FirstFreeze, Info);
	State = ECsInteractiveState::FirstFreeze;
}

void ACsInteractiveAIPawn::OnFreeze(const FCsInteractedActorInfo &Info) 
{
	State = ECsInteractiveState::Freeze;
}

void ACsInteractiveAIPawn::OnFirstUnFreeze(const FCsInteractedActorInfo &Info) 
{
	RemoveInteractedInfo(ECsInteractiveState::FirstFreeze, Info);
	State = ECsInteractiveState::FirstUnFreeze;
}

void ACsInteractiveAIPawn::OnFirstHold(const FCsInteractedActorInfo &Info)
{
	RemoveInteractedInfo(ECsInteractiveState::FirstHover, Info);
	RemoveInteractedInfo(ECsInteractiveState::Hover, Info);
	AddInteractedInfo(ECsInteractiveState::FirstHold, Info);

	if (State != ECsInteractiveState::FirstCollide && State != ECsInteractiveState::Collide)
		State = ECsInteractiveState::FirstHold;
}

void ACsInteractiveAIPawn::OnHold(const FCsInteractedActorInfo &Info)
{
	if (State != ECsInteractiveState::FirstCollide && State != ECsInteractiveState::Collide)
		State = ECsInteractiveState::Hold;
}

void ACsInteractiveAIPawn::OnRelease(const FCsInteractedActorInfo &Info)
{
	RemoveInteractedInfo(ECsInteractiveState::FirstHold, Info);
	RemoveInteractedInfo(ECsInteractiveState::Hold, Info);
	State = ECsInteractiveState::Release;
}

void ACsInteractiveAIPawn::OnFirstTouch(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::FirstTouch;
}

void ACsInteractiveAIPawn::OnTouch(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::Touch;
}

void ACsInteractiveAIPawn::OnFirstHover(const FCsInteractedActorInfo &Info)
{
	AddInteractedInfo(ECsInteractiveState::FirstHover, Info);
	State = ECsInteractiveState::FirstHover;
}

void ACsInteractiveAIPawn::OnHover(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::Hover;
}

void ACsInteractiveAIPawn::OnFirstUnHover(const FCsInteractedActorInfo &Info)
{
	RemoveInteractedInfo(ECsInteractiveState::FirstHover, Info);
	RemoveInteractedInfo(ECsInteractiveState::Hover, Info);
	State = ECsInteractiveState::FirstUnHover;
}

void ACsInteractiveAIPawn::OnFirstCollide(const FCsInteractedActorInfo &Info)
{
	AddInteractedInfo(ECsInteractiveState::FirstCollide, Info);
	State = ECsInteractiveState::FirstCollide;
}

void ACsInteractiveAIPawn::OnCollide(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::Collide;
}

void ACsInteractiveAIPawn::OnFirstUnCollide(const FCsInteractedActorInfo &Info)
{
	RemoveInteractedInfo(ECsInteractiveState::FirstCollide, Info);
	RemoveInteractedInfo(ECsInteractiveState::Collide, Info);
	State = ECsInteractiveState::FirstUnCollide;
}

void ACsInteractiveAIPawn::OnRemove(const FCsInteractedActorInfo &Info)
{
	ClearInteractedInfos();
	State = ECsInteractiveState::Remove;
}

bool ACsInteractiveAIPawn::CanChangeState(const TEnumAsByte<ECsInteractiveState::Type> &FromState, const TEnumAsByte<ECsInteractiveState::Type> &ToState)
{
	return true;
}

bool ACsInteractiveAIPawn::CanChangeFromAnyState(const TArray<TEnumAsByte<ECsInteractiveState::Type>> &FromStates, const TEnumAsByte<ECsInteractiveState::Type> &ToState)
{
	const int32 Count = FromStates.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (CanChangeState(FromStates[I], ToState))
			return true;
	}
	return false;
}

bool ACsInteractiveAIPawn::IsInTouchRange(UObject* InInstigator) { return false; }
bool ACsInteractiveAIPawn::CanBeTouched(UObject* InInstigator) { return false; }

#pragma endregion State

void ACsInteractiveAIPawn::Show(){}

void ACsInteractiveAIPawn::Hide(){}

// Collision
#pragma region

bool ACsInteractiveAIPawn::IsPhysicsState(const ECsInteractivePhysicsState &StateType)
{
	return CS_TEST_BLUEPRINT_BITFLAG(PhysicsState, StateType);
}

void ACsInteractiveAIPawn::SetPhysicsState(const ECsInteractivePhysicsState &StateType)
{
	const int32 Last_PhysicsState = PhysicsState;

	CS_SET_BLUEPRINT_BITFLAG(PhysicsState, StateType);

	if (CsCVarLogInteractiveAIPawnPhysicsStateChange->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString StateAsString			   = ECsInteractivePhysicsState_Editor::ToString(StateType);
		const FString LastPhysicsStateAsString = UCsCommon::InteractivePhysicsStateToString(Last_PhysicsState);
		const FString PhysicsStateAsString	   = UCsCommon::InteractivePhysicsStateToString(PhysicsState);

		UE_LOG(LogCs, Log, TEXT("ACsInteractiveAIPawn::SetPhysicsState (%s): Setting PhysicsState: %s. (%s) -> (%s)"), *GetName(), *StateAsString, *LastPhysicsStateAsString, *PhysicsStateAsString);
	}
}

void ACsInteractiveAIPawn::ClearPhysicsState(const ECsInteractivePhysicsState &StateType)
{
	const int32 Last_PhysicsState = PhysicsState;

	CS_CLEAR_BLUEPRINT_BITFLAG(PhysicsState, StateType);

	if (CsCVarLogInteractiveAIPawnPhysicsStateChange->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString StateAsString			   = ECsInteractivePhysicsState_Editor::ToString(StateType);
		const FString LastPhysicsStateAsString = UCsCommon::InteractivePhysicsStateToString(Last_PhysicsState);
		const FString PhysicsStateAsString	   = UCsCommon::InteractivePhysicsStateToString(PhysicsState);

		UE_LOG(LogCs, Log, TEXT("ACsInteractiveAIPawn::ClearPhysicsState (%s): Clearing PhysicsState: %s. (%s) -> (%s)"), *GetName(), *StateAsString, *LastPhysicsStateAsString, *PhysicsStateAsString);
	}
}

void ACsInteractiveAIPawn::IncrementPhysicsStateTimer(const ECsInteractivePhysicsState &StateType, const float& Value)
{
	PhysicsStateTimers[(uint8)StateType] += Value;
}

void ACsInteractiveAIPawn::SetPhysicsStateTimer(const ECsInteractivePhysicsState &StateType, const float& Value)
{
	PhysicsStateTimers[(uint8)StateType] = Value;
}

#pragma endregion Collision