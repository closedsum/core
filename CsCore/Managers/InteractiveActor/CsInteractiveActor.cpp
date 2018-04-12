// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/InteractiveActor/CsInteractiveActor.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

// Components
#include "Components/CsSkeletalMeshComponent.h"
#include "Components/CsStaticMeshComponent.h"
#include "Components/CsBoxComponent.h"
#include "Components/CsSphereComponent.h"

#include "MotionController/CsMotionController.h"
// Player
#include "Player/CsPlayerController.h"

ACsInteractiveActor::ACsInteractiveActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Warning_FellOutOfWorld	   = TEXT("ACsInteractiveActor::FellOutOfWorld");
	Warning_OutsideWorldBounds = TEXT("ACsInteractiveActor::OutsideWorldBounds");

	CS_SET_BLUEPRINT_BITFLAG(PhysicsState, ECsInteractivePhysicsState::Grounded);

	InteractiveCollisionEnabled = ECollisionEnabled::QueryOnly;

	MinPhysicsLinearVelocityForMovement = CS_MIN_PHYSICS_LINEAR_VELOCITY_FOR_MOVEMENT;
	MinPhysicsAngularVelocityForMovement = CS_MIN_PHYSICS_ANGULAR_VELOCITY_FOR_MOVEMENT;
}

void ACsInteractiveActor::OnConstructor(const FObjectInitializer& ObjectInitializer)
{
	// Skeletal Mesh
	if (UseSkeletalMesh)
	{
		SkeletalMeshComponent = ObjectInitializer.CreateDefaultSubobject<UCsSkeletalMeshComponent>(this, TEXT("SkeletalMeshComponent"));
		SetRootComponent(SkeletalMeshComponent);
		WorldCollisionComponent = SkeletalMeshComponent;
	}
	// Static Mesh
	if (UseStaticMesh)
	{
		StaticMeshComponent = ObjectInitializer.CreateDefaultSubobject<UCsStaticMeshComponent>(this, TEXT("StaticMeshComponent"));
		SetRootComponent(StaticMeshComponent);
		WorldCollisionComponent = StaticMeshComponent;
	}
	// Box Collision
	if (UseBoxCollision)
	{
		BoxComponent = ObjectInitializer.CreateDefaultSubobject<UCsBoxComponent>(this, TEXT("BoxComponent"));
		InteractiveCollisionComponent = BoxComponent;
		BoxComponent->SetupAttachment(GetRootComponent());
	}
	// SphereCollision
	if (UseSphereCollision)
	{
		SphereComponent = ObjectInitializer.CreateDefaultSubobject<UCsSphereComponent>(this, TEXT("SphereComponent"));
		InteractiveCollisionComponent = SphereComponent;
		SphereComponent->SetupAttachment(GetRootComponent());
	}
}

void ACsInteractiveActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Skeletal Mesh
	if (UseSkeletalMesh)
	{
		if (!IsPlaceable)
			UCsCommon::InitComponent(SkeletalMeshComponent, nullptr, ECollisionChannel::ECC_WorldStatic, ECsViewType::ECsViewType_MAX);
	}
	// Static Mesh
	if (UseStaticMesh)
	{
		if (!IsPlaceable)
			UCsCommon::InitComponent(StaticMeshComponent, nullptr, ECollisionChannel::ECC_WorldStatic, ECsViewType::ECsViewType_MAX);
	}
	// Box Collision
	if (UseBoxCollision)
	{
		if (!IsPlaceable)
			UCsCommon::InitComponent(BoxComponent, nullptr, ECollisionChannel::ECC_WorldStatic, ECsViewType::ECsViewType_MAX);
	}
	// SphereCollision
	if (UseSphereCollision)
	{
		if (!IsPlaceable)
			UCsCommon::InitComponent(SphereComponent, nullptr, ECollisionChannel::ECC_WorldStatic, ECsViewType::ECsViewType_MAX);
	}
}

void ACsInteractiveActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACsInteractiveActor::Init(const int32 &Index, const TCsInteractiveType &InType)
{
	PoolIndex   = Index;
	Type		= InType;
	Type_Script = (uint8)Type;

	Cache.Set(Index, this);
	Cache.Type		  = Type_Script;
	Cache.Type_Script = Type;
}

// Allocate / DeAllocate
#pragma region

template<typename T>
void ACsInteractiveActor::Allocate(const uint16 &ActiveIndex, FCsInteractiveActorPayload* Payload, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Cache.Init<T>(ActiveIndex, Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(GetWorld()), InOwner, InParent, InObject, OnDeAllocate);

	Allocate_Internal(Payload);
}

template<typename T>
void ACsInteractiveActor::Allocate(const uint16 &ActiveIndex, FCsInteractiveActorPayload* Payload, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Cache.Init<T>(ActiveIndex, Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(GetWorld()), InObject, OnDeAllocate);

	Allocate_Internal(Payload);
}

void ACsInteractiveActor::Allocate(const uint16 &ActiveIndex, FCsInteractiveActorPayload* Payload, UObject* InOwner, UObject* InParent)
{
	Cache.Init(ActiveIndex, Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(GetWorld()), InOwner, InParent);

	Allocate_Internal(Payload);
}

void ACsInteractiveActor::Allocate(const uint16 &ActiveIndex, FCsInteractiveActorPayload* Payload)
{
	Cache.Init(ActiveIndex, Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(GetWorld()));

	Allocate_Internal(Payload);
}

void ACsInteractiveActor::Allocate_Internal(FCsInteractiveActorPayload* Payload)
{
	ACsData_Interactive* Data = Cache.GetData();

	if (WorldCollisionComponent)
	{
		// Collision
		if (Data->UseWorldCollisionPreset())
		{
			Data->SetWorldCollisionFromPreset(WorldCollisionComponent);
		}
		// Physics
		if (Data->UsePhysicsPreset())
		{
			Data->SetPhysicsFromPreset(WorldCollisionComponent);

			WorldCollisionSimulatesPhysics = Data->SimulatePhysics();

			if (WorldCollisionSimulatesPhysics)
			{
				CS_SET_BLUEPRINT_BITFLAG(PhysicsState, ECsInteractivePhysicsState::Grounded);
			}
			WorldCollisionComponent->WakeAllRigidBodies();
		}

		WorldCollisionComponent->SetVisibility(true);
		WorldCollisionComponent->SetHiddenInGame(false);
		WorldCollisionComponent->SetComponentTickEnabled(true);
	}

	if (InteractiveCollisionComponent)
	{
		InteractiveCollisionComponent->SetCollisionEnabled(InteractiveCollisionEnabled);
		InteractiveCollisionComponent->SetComponentTickEnabled(true);
	}
	SetActorTickEnabled(true);

	const FVector Location = Payload->bLocation ? Cache.Location : GetActorLocation();
	const FRotator Rotation = Payload->bRotation ? Cache.Rotation : GetActorRotation();

	TeleportTo(Location, Rotation, false, true);

	SetActorScale3D(Payload->bScale ? Cache.Scale : FVector::OneVector);

	if (Data->UseSpawnPhysicsImpulse())
	{
		Data->ApplySpawnPhysicsImpulse(WorldCollisionComponent, true);
	}
}

void ACsInteractiveActor::DeAllocate()
{
	Super::DeAllocate();

	State = ECsInteractiveState::None;

	// Clear BitMask
	PhysicsState = 0;

	if (WorldCollisionComponent)
	{
		WorldCollisionComponent->SetSimulatePhysics(false);
		WorldCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WorldCollisionComponent->SetEnableGravity(false);
		WorldCollisionComponent->SetVisibility(false);
		WorldCollisionComponent->SetHiddenInGame(true);
		WorldCollisionComponent->SetComponentTickEnabled(false);
	}

	if (InteractiveCollisionComponent)
	{
		InteractiveCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		InteractiveCollisionComponent->SetVisibility(false);
		InteractiveCollisionComponent->SetHiddenInGame(true);
		InteractiveCollisionComponent->SetComponentTickEnabled(false);
	}
	CollidableActors.Reset();
	IgnoredActors.Reset();
	SetActorTickEnabled(false);

	ScreenPosition.Reset();
	WorldPosition.Reset();

	Cache.DeAllocate();
}

#pragma endregion Allocate / DeAllocate

// State
#pragma region

	// InteractedInfo
#pragma region

void ACsInteractiveActor::AddInteractedInfo(const TEnumAsByte<ECsInteractiveState::Type> &InState, const FCsInteractedActorInfo &Info)
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

	// TODO: Potentially setup code flow that it is NOT possible to Add the same Instigator twice
	const int32 Count = Infos->Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if ((*Infos)[I].GetInstigator() == Info.GetInstigator())
			return;
	}
	Infos->AddDefaulted();
	(*Infos)[Infos->Num() - 1] = Info;
}

void ACsInteractiveActor::RemoveInteractedInfo(const TEnumAsByte<ECsInteractiveState::Type> &InState, const FCsInteractedActorInfo &Info)
{
	TArray<FCsInteractedActorInfo>* Infos = InteractedInfos.Find(InState);

	if (!Infos)
	{
		TArray<FCsInteractedActorInfo> InfosToAdd;
		InteractedInfos.Add(InState, InfosToAdd);
		return;
	}

	bool Found		  = false;
	const int32 Count = Infos->Num();

	for (int32 I = Count - 1; I >= 0; --I)
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

void ACsInteractiveActor::ClearInteractedInfos()
{
	for (int32 I = 0; I < ECS_INTERACTIVE_STATE_MAX; ++I)
	{
		TArray<FCsInteractedActorInfo>* Infos = InteractedInfos.Find((TCsInteractiveState)I);

		if (!Infos)
			continue;

		Infos->Reset();
	}
}

TArray<FCsInteractedActorInfo>* ACsInteractiveActor::GetInteractedInfos(const TEnumAsByte<ECsInteractiveState::Type> &InState)
{
	return InteractedInfos.Find(InState);
}

void ACsInteractiveActor::GetInteractedInfos_Script(const TEnumAsByte<ECsInteractiveState::Type> &InState, TArray<FCsInteractedActorInfo> &OutInfos)
{
	TArray<FCsInteractedActorInfo>* Infos = GetInteractedInfos(InState);

	if (!Infos)
		return;

	const int32 Count = Infos->Num();

	for (int32 I = 0; I < Count; ++I)
	{
		OutInfos.AddDefaulted();
		OutInfos[I] = (*Infos)[I];
	}
}

#pragma endregion InteractedInfo

void ACsInteractiveActor::OnInteraction_Script(const TEnumAsByte<ECsInteractiveState::Type> &InState, const FCsInteractedActorInfo& Info)
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

void ACsInteractiveActor::OnInteraction(const FCsInteractedActorInfo& Info)
{
}

void ACsInteractiveActor::OnFirstFreeze(const FCsInteractedActorInfo& Info)
{
	AddInteractedInfo(ECsInteractiveState::FirstFreeze, Info);
	State = ECsInteractiveState::FirstFreeze;
}

void ACsInteractiveActor::OnFreeze(const FCsInteractedActorInfo& Info)
{
	State = ECsInteractiveState::Freeze;
}

void ACsInteractiveActor::OnFirstUnFreeze(const FCsInteractedActorInfo& Info)
{
	RemoveInteractedInfo(ECsInteractiveState::FirstFreeze, Info);
	State = ECsInteractiveState::FirstUnFreeze;
}

void ACsInteractiveActor::OnFirstHold(const FCsInteractedActorInfo& Info)
{
	RemoveInteractedInfo(ECsInteractiveState::FirstHover, Info);
	RemoveInteractedInfo(ECsInteractiveState::Hover, Info);
	AddInteractedInfo(ECsInteractiveState::FirstHold, Info);

	if (State != ECsInteractiveState::FirstCollide && State != ECsInteractiveState::Collide)
		State = ECsInteractiveState::FirstHold;
}

void ACsInteractiveActor::OnHold(const FCsInteractedActorInfo& Info)
{
	if (State != ECsInteractiveState::FirstCollide && State != ECsInteractiveState::Collide)
		State = ECsInteractiveState::Hold;
}

void ACsInteractiveActor::OnRelease(const FCsInteractedActorInfo& Info)
{
	RemoveInteractedInfo(ECsInteractiveState::FirstHold, Info);
	RemoveInteractedInfo(ECsInteractiveState::Hold, Info);
	State = ECsInteractiveState::Release;
}

void ACsInteractiveActor::OnFirstTouch(const FCsInteractedActorInfo& Info)
{
	State = ECsInteractiveState::FirstTouch;
}

void ACsInteractiveActor::OnTouch(const FCsInteractedActorInfo& Info)
{
	State = ECsInteractiveState::Touch;
}

void ACsInteractiveActor::OnFirstHover(const FCsInteractedActorInfo& Info)
{
	AddInteractedInfo(ECsInteractiveState::FirstHover, Info);
	State = ECsInteractiveState::FirstHover;
}

void ACsInteractiveActor::OnHover(const FCsInteractedActorInfo& Info)
{
	State = ECsInteractiveState::Hover;
}

void ACsInteractiveActor::OnFirstUnHover(const FCsInteractedActorInfo& Info)
{
	RemoveInteractedInfo(ECsInteractiveState::FirstHover, Info);
	RemoveInteractedInfo(ECsInteractiveState::Hover, Info);
	State = ECsInteractiveState::FirstUnHover;
}

void ACsInteractiveActor::OnFirstCollide(const FCsInteractedActorInfo& Info)
{
	AddInteractedInfo(ECsInteractiveState::FirstCollide, Info);
	State = ECsInteractiveState::FirstCollide;
}

void ACsInteractiveActor::OnCollide(const FCsInteractedActorInfo& Info)
{
	State = ECsInteractiveState::Collide;
}

void ACsInteractiveActor::OnFirstUnCollide(const FCsInteractedActorInfo& Info)
{
	RemoveInteractedInfo(ECsInteractiveState::FirstCollide, Info);
	RemoveInteractedInfo(ECsInteractiveState::Collide, Info);
	State = ECsInteractiveState::FirstUnCollide;
}

void ACsInteractiveActor::OnRemove(const FCsInteractedActorInfo& Info)
{
	ClearInteractedInfos();
	State = ECsInteractiveState::Remove;
}

bool ACsInteractiveActor::CanChangeState(const TEnumAsByte<ECsInteractiveState::Type> &FromState, const TEnumAsByte<ECsInteractiveState::Type> &ToState)
{
	return true;
}

bool ACsInteractiveActor::CanChangeFromAnyState(const TArray<TEnumAsByte<ECsInteractiveState::Type>> &FromStates, const TEnumAsByte<ECsInteractiveState::Type> &ToState)
{
	const int32 Count = FromStates.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (CanChangeState(FromStates[I], ToState))
			return true;
	}
	return false;
}

ACsMotionController* ACsInteractiveActor::GetDominantHand_HoldingMe()
{
	TArray<TEnumAsByte<ECsInteractiveState::Type>> States;
	States.Add(ECsInteractiveState::FirstHold);
	States.Add(ECsInteractiveState::Hold);

	const int32 StateCount = States.Num();

	for (int32 I = 0; I < StateCount; ++I)
	{
		TArray<FCsInteractedActorInfo>* Infos = InteractedInfos.Find(States[I]);

		if (!Infos)
			continue;

		const int32 Count = Infos->Num();

		for (int32 J = 0; J < Count; J++)
		{
			UObject* Object			  = (*Infos)[I].GetInstigator();
			ACsMotionController* Hand = Cast<ACsMotionController>(Object);

			if (!Hand)
				continue;

			if (Hand == Cast<ACsMotionController>(GetAttachParentActor()))
				return Hand;
		}
	}
	return nullptr;
}

ACsMotionController* ACsInteractiveActor::GetLastHand_HoveringOverMe()
{
	// FirstHover
	if (TArray<FCsInteractedActorInfo>* Infos = InteractedInfos.Find(ECsInteractiveState::FirstHover))
	{
		TArray<ACsMotionController*> FirstHoverHands;

		const int32 Count = Infos->Num();

		for (int32 J = 0; J < Count; J++)
		{
			UObject* Object			  = (*Infos)[J].GetInstigator();
			ACsMotionController* Hand = Cast<ACsMotionController>(Object);

			if (Hand)
				FirstHoverHands.Add(Hand);
		}

		const int32 HandCount = FirstHoverHands.Num();

		if (HandCount > CS_EMPTY)
			return FirstHoverHands[HandCount - 1];
	}
	// Hover
	if (TArray<FCsInteractedActorInfo>* Infos = InteractedInfos.Find(ECsInteractiveState::Hover))
	{
		TArray<ACsMotionController*> HoverHands;

		const int32 Count = Infos->Num();

		for (int32 J = 0; J < Count; J++)
		{
			UObject* Object			  = (*Infos)[J].GetInstigator();
			ACsMotionController* Hand = Cast<ACsMotionController>(Object);

			if (Hand)
				HoverHands.Add(Hand);
		}

		const int32 HandCount = HoverHands.Num();

		if (HandCount > CS_EMPTY)
			return HoverHands[HandCount - 1];
	}
	return nullptr;
}

#pragma endregion State

// Routines
#pragma region

bool ACsInteractiveActor::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	if (Super::AddRoutine_Internal(Routine, Type))
		return true;
	return false;
}

bool ACsInteractiveActor::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	if (Super::RemoveRoutine_Internal(Routine, Type))
		return true;
	return false;
}

#pragma endregion Routines

// Visibility
#pragma region

void ACsInteractiveActor::Show()
{
	Super::Show();

	ACsData_Interactive* Data = Cache.GetData();

	if (WorldCollisionComponent)
	{
		Data->ToggleWorldCollisionAndPhysics(WorldCollisionComponent, true);

		WorldCollisionComponent->WakeAllRigidBodies();

		WorldCollisionComponent->SetVisibility(true);
		WorldCollisionComponent->SetHiddenInGame(false);
		WorldCollisionComponent->SetComponentTickEnabled(true);
	}

	if (InteractiveCollisionComponent)
	{
		InteractiveCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		InteractiveCollisionComponent->SetComponentTickEnabled(true);
	}
	SetActorTickEnabled(true);
}

void ACsInteractiveActor::Hide()
{
	Super::Hide();

	ACsData_Interactive* Data = Cache.GetData();

	if (WorldCollisionComponent)
	{
		Data->ToggleWorldCollisionAndPhysics(WorldCollisionComponent, false);

		WorldCollisionComponent->SetVisibility(false);
		WorldCollisionComponent->SetHiddenInGame(true);
		WorldCollisionComponent->SetComponentTickEnabled(false);
	}

	if (InteractiveCollisionComponent)
	{
		InteractiveCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		InteractiveCollisionComponent->SetComponentTickEnabled(false);
	}
	SetActorTickEnabled(false);
}

#pragma endregion Visibility

// Collision
#pragma region

bool ACsInteractiveActor::IsPhysicsState(const ECsInteractivePhysicsState &StateType)
{
	return CS_TEST_BLUEPRINT_BITFLAG(PhysicsState, StateType);
}

void ACsInteractiveActor::SetPhysicsState(const ECsInteractivePhysicsState &StateType)
{
	const int32 Last_PhysicsState = PhysicsState;

	CS_SET_BLUEPRINT_BITFLAG(PhysicsState, StateType);

	if (CsCVarLogInteractiveActorPhysicsStateChange->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString& StateAsString		   = ECsInteractivePhysicsState_Editor::ToString(StateType);
		const FString LastPhysicsStateAsString = UCsCommon::InteractivePhysicsStateToString(Last_PhysicsState);
		const FString PhysicsStateAsString	   = UCsCommon::InteractivePhysicsStateToString(PhysicsState);

		UE_LOG(LogCs, Log, TEXT("ACsInteractiveActor::SetPhysicsState (%s): Setting PhysicsState: %s. (%s) -> (%s)"), *GetName(), *StateAsString, *LastPhysicsStateAsString, *PhysicsStateAsString);
	}
}

void ACsInteractiveActor::ClearPhysicsState(const ECsInteractivePhysicsState &StateType)
{
	const int32 Last_PhysicsState = PhysicsState;

	CS_CLEAR_BLUEPRINT_BITFLAG(PhysicsState, StateType);

	if (CsCVarLogInteractiveActorPhysicsStateChange->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString& StateAsString		   = ECsInteractivePhysicsState_Editor::ToString(StateType);
		const FString LastPhysicsStateAsString = UCsCommon::InteractivePhysicsStateToString(Last_PhysicsState);
		const FString PhysicsStateAsString	   = UCsCommon::InteractivePhysicsStateToString(PhysicsState);

		UE_LOG(LogCs, Log, TEXT("ACsInteractiveActor::ClearPhysicsState (%s): Clearing PhysicsState: %s. (%s) -> (%s)"), *GetName(), *StateAsString, *LastPhysicsStateAsString, *PhysicsStateAsString);
	}
}

void ACsInteractiveActor::OnTick_Handle_PhysicsState()
{
	if (!WorldCollisionSimulatesPhysics)
		return;
	if (!WorldCollisionComponent)
		return;

	// (FirstHold | Hold) -> PhysicsState = Custom
	if (State == ECsInteractiveState::FirstHold ||
		State == ECsInteractiveState::Hold)
	{
		// Check 'CurrentState' = Custom
		if (!IsPhysicsState(ECsInteractivePhysicsState::Custom))
		{
			// Clear BitMask
			PhysicsState = 0;

			SetPhysicsState(ECsInteractivePhysicsState::Custom);
		}
		return;
	}
	ClearPhysicsState(ECsInteractivePhysicsState::Custom);

	// TODO: Check Airborne. This can be expensive
	if (CheckIsAirborne)
	{
	}
	// Check 'CurrentState' = Grounded
	const float LinearSpeed = WorldCollisionComponent->GetPhysicsLinearVelocity().Size();
	const float AngularSpeed = WorldCollisionComponent->GetPhysicsAngularVelocity().Size();
	
	if (LinearSpeed <= MinPhysicsLinearVelocityForMovement &&
		AngularSpeed <= MinPhysicsLinearVelocityForMovement)
	{
		SetPhysicsState(ECsInteractivePhysicsState::Grounded);
	}
}

void ACsInteractiveActor::OnTick_Overlap(const float DeltaSeconds){}

void ACsInteractiveActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult){}
void ACsInteractiveActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){}

bool ACsInteractiveActor::CanCollideWithComponent(UPrimitiveComponent* InComponent)
{
	return WorldCollisionComponent->GetCollisionResponseToChannel(InComponent->GetCollisionObjectType()) == ECollisionResponse::ECR_Block;
}

#pragma endregion Collision

// UI
#pragma region

void ACsInteractiveActor::CalculateScreenPosition()
{
	bool HasChanged = false;

	HasChanged |= WorldPosition.HasChanged();

	ACsPlayerController* Controller = UCsCommon::GetLocalPlayerController<ACsPlayerController>(GetWorld());

	HasChanged |= Controller->ViewRotation.HasChanged();
	HasChanged |= Controller->ViewLocation.HasChanged();

	if (!HasChanged)
		return;

	FVector2D OutScreenPosition	= FVector2D::ZeroVector;
	UGameplayStatics::ProjectWorldToScreen(Controller, WorldPosition.Value, OutScreenPosition, false);

	ScreenPosition = OutScreenPosition;
}

#pragma endregion UI