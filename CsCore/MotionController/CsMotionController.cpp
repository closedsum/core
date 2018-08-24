// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "MotionController/CsMotionController.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "Coroutine/CsCoroutineScheduler.h"
#include "MotionControllerComponent.h"
#include "../InputCore/Classes/InputCoreTypes.h"
#include "Managers/InteractiveActor/CsInteractiveActor.h"
#include "AI/Pawn/CsInteractiveAIPawn.h"
#include "Player/CsPlayerController.h"
// UI
#include "UI/Button/CsButtonComponent.h"

ACsMotionController::ACsMotionController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	DefaultRootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("DefaultRootComponent"));
	SetRootComponent(DefaultRootComponent);
	UCsCommon::InitComponent(DefaultRootComponent, nullptr, ECollisionChannel::ECC_Visibility, ECsViewType::ECsViewType_MAX);

	UseSkeletalMesh = true;
	UseStaticMesh   = false;

	AnchorComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("AnchorComponent"));
	UCsCommon::InitComponent(AnchorComponent, DefaultRootComponent, ECollisionChannel::ECC_Visibility, ECsViewType::ECsViewType_MAX);

	Hand = ECsControllerHand::Left;

	CollisionType = ECsInteractiveCollision::ECsInteractiveCollision_MAX;

	MaxTraceCount = CS_MOTION_CONTROLLER_INFINITE_TRACE_COUNT;
	MaxTraceRange = 30000.0f;

	State = ECsInteractiveState::None;
}

void ACsMotionController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	DefaultRootComponent->SetComponentTickEnabled(false);
	AnchorComponent->SetComponentTickEnabled(false);

	// SkeletalMesh
	if (UseSkeletalMesh)
	{
		SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(this, TEXT("SkeletalMeshComponent"));
		SkeletalMeshComponent->RegisterComponent();
		UCsCommon::InitComponent(SkeletalMeshComponent, nullptr, ECollisionChannel::ECC_Pawn, ECsViewType::ECsViewType_MAX);
	}
	// StaticMesh
	if (UseStaticMesh)
	{
		StaticMeshComponent = NewObject<UStaticMeshComponent>(this, TEXT("StaticMeshComponent"));
		StaticMeshComponent->RegisterComponent();
		UCsCommon::InitComponent(StaticMeshComponent, nullptr, ECollisionChannel::ECC_Pawn, ECsViewType::ECsViewType_MAX);
	}
}

void ACsMotionController::PostActorCreated()
{
	Super::PostActorCreated();

	Setup_OnCalcCamera();
}

UMotionControllerComponent* ACsMotionController::GetMotionControllerComponent()
{
	return MotionControllerComponent.IsValid() ? MotionControllerComponent.Get() : nullptr;
}

FVector ACsMotionController::GetLocation()
{
	return GetMotionControllerComponent()->GetComponentLocation();
}

void ACsMotionController::FellOutOfWorld(const class UDamageType& dmgType)
{
	UE_LOG(LogCs, Warning, TEXT("ACsMotionController::FellOutOfWorld: Warning. Motion Controller fell out of world"));
}

void ACsMotionController::OutsideWorldBounds()
{
	UE_LOG(LogCs, Warning, TEXT("ACsMotionController::OutsideWorldBounds: Warning. Motion Controller outside world bounds."));
}

class ACsMotionController* ACsMotionController::GetOtherHand()
{
	return OtherHand.IsValid() ? OtherHand.Get() : nullptr;
}

void ACsMotionController::OnTick(const float &DeltaSeconds)
{
	OnTick_HandleCVars(DeltaSeconds);

	if (State == ECsInteractiveState::Release)
		State = ECsInteractiveState::None;

	OnTick_Check_FirstTouch(DeltaSeconds);

	OnTick_Handle_FirstHoldAndHold(DeltaSeconds);
}

void ACsMotionController::OnTick_HandleCVars(const float &DeltaSeconds)
{
	if (CsCVarDrawMotionControllerMaxTouchSenseRange->GetInt() == CS_CVAR_DRAW)
	{
		DrawDebugSphere(GetWorld(), GetTouchSenseLocation(), MaxTouchSenseRange, 16, FColor::Green, false, DeltaSeconds + 0.01f, 0, 0.25f);
	}
}

void ACsMotionController::OnTick_Check_FirstTouch(const float &DeltaSeconds){}

void ACsMotionController::OnTick_Handle_FirstHoldAndHold(const float &DeltaSeconds)
{
	if (State != ECsInteractiveState::FirstHold &&
		State != ECsInteractiveState::Hold)
		return;

	if (State == ECsInteractiveState::FirstHold)
		State = ECsInteractiveState::Hold;

	TArray<FCsInteractedActorInfo> OnFirstHoldInfos;
	TArray<FCsInteractedActorInfo> OnHoldInfos;
	TArray<FCsInteractedActorInfo> OnFirstCollideInfos;
	TArray<FCsInteractedActorInfo> OnCollideInfos;
	TArray<FCsInteractedActorInfo> OnFirstUnCollideInfos;

	const int32 Count = CurrentInteractedActorInfos.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		AActor* Actor					 = CurrentInteractedActorInfos[I].GetActor();
		ACsInteractiveAIPawn* Pawn		 = Cast<ACsInteractiveAIPawn>(Actor);
		ACsInteractiveActor* Interactive = Cast<ACsInteractiveActor>(Actor);

		bool HasCollided = false;

		if (Interactive)
		{
			TArray<UPrimitiveComponent*> Components;
			Interactive->WorldCollisionComponent->GetOverlappingComponents(Components);

			const int32 ActorCount = Components.Num();

			for (int32 J = 0; J < ActorCount; J++)
			{
				// Ignore Collision with Self
				if (Components[J]->GetOwner() == Interactive)
					continue;
				// Collision against another InteractiveActor
				if (Interactive->CanCollideWithComponent(Components[J]))
				{
					HasCollided = true;
					break;
				}
			}
		}

		if (HasCollided)
		{
			// (FirstHold | Hold) -> FirstCollide
			if (CurrentInteractiveActorStates[I] != ECsInteractiveState::FirstCollide &&
				CurrentInteractiveActorStates[I] != ECsInteractiveState::Collide)
			{
				TArray<TEnumAsByte<ECsInteractiveState::Type>> States;
				States.Add(ECsInteractiveState::FirstHold);
				States.Add(ECsInteractiveState::Hold);

				if ((!Pawn && !Interactive) ||
					(Pawn && Pawn->CanChangeFromAnyState(States, ECsInteractiveState::FirstCollide)) ||
					(Interactive && Interactive->CanChangeFromAnyState(States, ECsInteractiveState::FirstCollide)))
				{
					CurrentInteractiveActorStates[I] = ECsInteractiveState::FirstCollide;

					OnFirstCollideInfos.AddDefaulted();
					OnFirstCollideInfos[OnFirstCollideInfos.Num() - 1] = CurrentInteractedActorInfos[I];
				}
			}
			// Collide
			else
			{
				CurrentInteractiveActorStates[I] = ECsInteractiveState::Collide;
				OnCollideInfos.AddDefaulted();
				OnCollideInfos[OnCollideInfos.Num() - 1] = CurrentInteractedActorInfos[I];
			}
		}
		else
		{
			// FirstHold -> Hold
			if (CurrentInteractiveActorStates[I] == ECsInteractiveState::FirstHold)
			{
				if ((!Pawn && !Interactive) ||
					(Pawn && Pawn->CanChangeState(ECsInteractiveState::FirstHold, ECsInteractiveState::Hold)) ||
					(Interactive && Interactive->CanChangeState(ECsInteractiveState::FirstHold, ECsInteractiveState::Hold)))
				{
					CurrentInteractiveActorStates[I] = ECsInteractiveState::Hold;
					OnHoldInfos.AddDefaulted();
					OnHoldInfos[OnHoldInfos.Num() - 1] = CurrentInteractedActorInfos[I];
				}
			}
			// (FirstCollide | Collide) -> FirstUnCollide
			else
			if (CurrentInteractiveActorStates[I] == ECsInteractiveState::FirstCollide ||
				CurrentInteractiveActorStates[I] == ECsInteractiveState::Collide)
			{
				TArray<TEnumAsByte<ECsInteractiveState::Type>> States;
				States.Add(ECsInteractiveState::FirstCollide);
				States.Add(ECsInteractiveState::Collide);

				if ((!Pawn && !Interactive) ||
					(Pawn && Pawn->CanChangeFromAnyState(States, ECsInteractiveState::FirstUnCollide)) ||
					(Interactive && Interactive->CanChangeFromAnyState(States, ECsInteractiveState::FirstUnCollide)))
				{
					CurrentInteractiveActorStates[I] = ECsInteractiveState::FirstUnCollide;
					OnFirstUnCollideInfos.AddDefaulted();
					OnFirstUnCollideInfos[OnFirstUnCollideInfos.Num() - 1] = CurrentInteractedActorInfos[I];
				}
			}
			// FirstUnCollide -> FirstHold
			else
			if (CurrentInteractiveActorStates[I] == ECsInteractiveState::FirstUnCollide)
			{
				if ((!Pawn && !Interactive) ||
					(Pawn && Pawn->CanChangeState(ECsInteractiveState::FirstUnCollide, ECsInteractiveState::FirstHold)) ||
					(Interactive && Interactive->CanChangeState(ECsInteractiveState::FirstUnCollide, ECsInteractiveState::FirstHold)))
				{
					CurrentInteractiveActorStates[I] = ECsInteractiveState::FirstHold;
					OnFirstHoldInfos.AddDefaulted();
					OnFirstHoldInfos[OnFirstHoldInfos.Num() - 1] = CurrentInteractedActorInfos[I];
				}
			}
			// Hold
			else
			{
				CurrentInteractiveActorStates[I] = ECsInteractiveState::Hold;
				OnHoldInfos.AddDefaulted();
				OnHoldInfos[OnHoldInfos.Num() - 1] = CurrentInteractedActorInfos[I];
			}
		}
	}

	OnFirstHold(OnFirstHoldInfos);
	OnHold(OnHoldInfos);
	OnFirstCollide(OnFirstCollideInfos);
	OnCollide(OnCollideInfos);
	OnFirstUnCollide(OnFirstUnCollideInfos);
}

void ACsMotionController::Init(class UMotionControllerComponent* InComponent, const TCsControllerHand &InHand)
{
	Hand					  = InHand;
	MotionControllerComponent = InComponent;

	AnchorComponent->AttachToComponent(GetMotionControllerComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	if (UseSkeletalMesh)
		SkeletalMeshComponent->AttachToComponent(GetMotionControllerComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	if (UseStaticMesh)
		StaticMeshComponent->AttachToComponent(GetMotionControllerComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Touch
#pragma region

FVector ACsMotionController::GetTouchSenseLocation()
{
	const FVector Location = GetLocation();
	const FVector Forward  = GetMotionControllerComponent()->GetForwardVector();
	return Location + TouchSenseOffset.X * Forward;
}

#pragma endregion Touch

// Collision
#pragma region

void ACsMotionController::SetCollisionType(const TCsInteractiveCollision &InCollisionType, const FCsCollisionPreset &InPreset)
{
	CollisionType   = InCollisionType;
	CollisionPreset = InPreset;

	// Box
	if (CollisionType == ECsInteractiveCollision::Box)
		SetCollisionType(InCollisionType, InPreset, FVector(1.0f));
	// Sphere
	if (CollisionType == ECsInteractiveCollision::Sphere)
		SetCollisionType(InCollisionType, InPreset, 1.0f);
	// Mesh
	if (CollisionType == ECsInteractiveCollision::Mesh)
	{
		if (UseSkeletalMesh)
			InteractiveCollisionComponent = SkeletalMeshComponent;
		if (UseStaticMesh)
			InteractiveCollisionComponent = StaticMeshComponent;

		InteractiveCollisionComponent->SetCollisionObjectType(CollisionPreset.ObjectType);
		InteractiveCollisionComponent->SetCollisionResponseToChannels(CollisionPreset.CollisionResponses);
		InteractiveCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACsMotionController::OnBeginOverlap);
	}
}

void ACsMotionController::SetCollisionType(const TCsInteractiveCollision &InCollisionType, const FCsCollisionPreset &InPreset, const FVector &BoxExtent)
{
	UBoxComponent* Box			  = NewObject<UBoxComponent>(this, TEXT("InteractiveCollisionComponent"));
	InteractiveCollisionComponent = Box;
	InteractiveCollisionComponent->RegisterComponent();

	CollisionPreset = InPreset;

	UCsCommon::InitComponent(InteractiveCollisionComponent, GetMotionControllerComponent(), CollisionPreset.ObjectType, ECsViewType::ECsViewType_MAX);

	Box->SetBoxExtent(BoxExtent);

	InteractiveCollisionComponent->SetCollisionResponseToChannels(CollisionPreset.CollisionResponses);
	InteractiveCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACsMotionController::OnBeginOverlap);
}

void ACsMotionController::SetCollisionType(const TCsInteractiveCollision &InCollisionType, const FCsCollisionPreset &InPreset, const float &SphereRadius)
{
	USphereComponent* Sphere	  = NewObject<USphereComponent>(this, TEXT("InteractiveCollisionComponent"));
	InteractiveCollisionComponent = Sphere;
	InteractiveCollisionComponent->RegisterComponent();

	CollisionPreset = InPreset;

	UCsCommon::InitComponent(InteractiveCollisionComponent, GetMotionControllerComponent(), CollisionPreset.ObjectType, ECsViewType::ECsViewType_MAX);

	Sphere->SetSphereRadius(SphereRadius);

	InteractiveCollisionComponent->SetCollisionResponseToChannels(CollisionPreset.CollisionResponses);
	InteractiveCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACsMotionController::OnBeginOverlap);
}

void ACsMotionController::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
}

#pragma endregion Collision

void ACsMotionController::UpdateLocation(const FVector &Location)
{
	//SetActorLocation(Location);
}

void ACsMotionController::UpdateRotation(const FRotator &Rotation)
{
	//SetActorRotation(Rotation);
}

void ACsMotionController::UpdateLocationAndRotation(const FVector &Location, const FRotator &Rotation)
{
	//SetActorLocationAndRotation(Location, Rotation);
}

// Routines
#pragma region

/*static*/ void ACsMotionController::AddRoutine(UObject* InMotionController, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsMotionController>(InMotionController)->AddRoutine_Internal(Routine, (TCsRoutineMotionController)Type);
}

void ACsMotionController::AddRoutine_Internal(struct FCsRoutine* Routine, const TCsRoutineMotionController &Type)
{
	// Setup_OnCalcCamera_Internal
	if (Type == ECsRoutineMotionController::Setup_OnCalcCamera_Internal)
	{
		Setup_OnCalcCamera_Internal_Routine = Routine;
		return;
	}
	checkf(0, TEXT("ACsMotionController::Setup_OnCalcCamera_Internal: Adding a Routine of unknown Type"));
}

/*static*/ void ACsMotionController::RemoveRoutine(UObject* InMotionController, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsMotionController>(InMotionController)->RemoveRoutine_Internal(Routine, (TCsRoutineMotionController)Type);
}

void ACsMotionController::RemoveRoutine_Internal(struct FCsRoutine* Routine, const TCsRoutineMotionController &Type)
{
	// Setup_OnCalcCamera_Internal
	if (Type == ECsRoutineMotionController::Setup_OnCalcCamera_Internal)
	{
		check(Setup_OnCalcCamera_Internal_Routine == Routine);
		Setup_OnCalcCamera_Internal_Routine = nullptr;
		return;
	}
	checkf(0, TEXT("ACsMotionController::Setup_OnCalcCamera_Internal: Removing a Routine of unknown Type"));
}

#pragma endregion Routines

// Camera
#pragma region

void ACsMotionController::Setup_OnCalcCamera()
{
	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	CsCoroutine Function		  = &ACsMotionController::Setup_OnCalcCamera_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckActor;
	CsAddRoutine Add			  = &ACsMotionController::AddRoutine;
	CsRemoveRoutine Remove		  = &ACsMotionController::RemoveRoutine;
	const uint8 Type			  = (uint8)ECsRoutineMotionController::Setup_OnCalcCamera_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Schedule, Function, Stop, this, Add, Remove, Type, true, false);

	Scheduler->StartRoutine(Schedule, R);
}

PT_THREAD(ACsMotionController::Setup_OnCalcCamera_Internal(struct FCsRoutine* r))
{
	ACsMotionController* mc  = Cast<ACsMotionController>(r->GetActor());
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();
	UWorld* w				 = mc->GetWorld();
	ACsPlayerController* pc  = UCsCommon::GetLocalPlayerController<ACsPlayerController>(w);

	CS_COROUTINE_BEGIN(r);

	// Wait until valid player controller
	CS_COROUTINE_WAIT_UNTIL(r, pc);

	// Wait until the Collision Type has been set
	CS_COROUTINE_WAIT_UNTIL(r, mc->CollisionType != ECsInteractiveCollision::ECsInteractiveCollision_MAX)

	if (mc->CollisionType = ECsInteractiveCollision::Trace)
	{
		pc->OnCalcCamera_Event.AddUObject(mc, &ACsMotionController::OnCalcCamera);
	}

	CS_COROUTINE_END(r);
}

void ACsMotionController::OnCalcCamera(const uint8 &MappingId, const float &DeltaTime, const struct FMinimalViewInfo &ViewInfo)
{
#if WITH_EDITOR
	if (Override_OnCalcCamera_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsMotionController::OnCalcCamera (%s): Using Override Function."), *GetName());
		}
		Override_OnCalcCamera_ScriptEvent.Broadcast(MappingId, Hand, DeltaTime, ViewInfo);
	}
#endif WITH_EDITOR

	OnCalcCamera_Trace(MappingId, DeltaTime, ViewInfo);
}

void ACsMotionController::OnCalcCamera_Trace(const uint8 &MappingId, const float &DeltaTime, const struct FMinimalViewInfo &ViewInfo)
{
	if (State == ECsInteractiveState::FirstHold ||
		State == ECsInteractiveState::Hold ||
		State == ECsInteractiveState::FirstCollide ||
		State == ECsInteractiveState::Collide)
	{
		return;
	}

	if (CsCVarDrawMotionControllerTrace->GetInt() == CS_CVAR_DRAW)
		DrawDebugLine(GetWorld(), GetMotionControllerComponent()->GetComponentLocation(), LastTraceHitLocation, FColor::Red, false, CsCVarMotionControllerTraceFrequencey->GetFloat(), 0, 3.0f);

	if (GetWorld()->GetTimeSeconds() - LastTrace_StartTime < CsCVarMotionControllerTraceFrequencey->GetFloat())
		return;

	LastTrace_StartTime = GetWorld()->GetTimeSeconds();

	const FVector Start		= GetMotionControllerComponent()->GetComponentLocation();
	const FRotator Rotation = GetMotionControllerComponent()->GetComponentRotation();
	const FVector Dir		= Rotation.Vector();
	const FVector End		= Start + MaxTraceRange * Dir;

	TArray<FHitResult> OutHits;

	static FName OnCalcCamera_Trace_Name(TEXT("ACsMotionController::OnCalcCamera_Trace"));
	FCollisionQueryParams Params(OnCalcCamera_Trace_Name, false);
	//Params.bTraceAsyncScene = true;

	TArray<AActor*> IgnoreActors;

	IgnoreActors.Add(this);
	IgnoreActors.Add(GetMotionControllerComponent()->GetOwner());
	Params.AddIgnoredActors(IgnoreActors);

	FCollisionObjectQueryParams ObjectParams;

	const uint8 CollisionCount = (uint8)ECollisionChannel::ECC_MAX;

	for (int32 I = 0; I < CollisionCount; ++I)
	{
		const ECollisionResponse Response = CollisionPreset.CollisionResponses.GetResponse((ECollisionChannel)I);

		if (Response == ECollisionResponse::ECR_Block ||
			Response == ECollisionResponse::ECR_Overlap)
			ObjectParams.AddObjectTypesToQuery((ECollisionChannel)I);
	}

	float ClosestDistanceSq = MaxTraceRange * MaxTraceRange;
	bool HasHitSomething	= GetWorld()->LineTraceMultiByObjectType(OutHits, Start, End, ObjectParams, Params);

	bool HasHitValidObject = false;
	LastTraceHitActor	   = nullptr;

	TArray<FCsInteractedActorInfo> Infos;

	// Find the closes object that was hit
	if (HasHitSomething)
	{
		int32 ClosestIndex   = INDEX_NONE;
		bool IgnoreActor	 = false;
		const int32 HitCount = MaxTraceCount == CS_MOTION_CONTROLLER_INFINITE_TRACE_COUNT ? OutHits.Num() : FMath::Min(MaxTraceCount, OutHits.Num());

		for (int32 Index = 0; Index < HitCount; Index++)
		{
			IgnoreActor = false;

			// Interactive Actor
			ACsInteractiveActor* HitActor = Cast<ACsInteractiveActor>(OutHits[Index].GetActor());
			// Interactive Pawn
			ACsInteractiveAIPawn* HitPawn = Cast<ACsInteractiveAIPawn>(OutHits[Index].GetActor());

			//if (!HitActor && !HitPawn)
			//	IgnoreActor = true;

			if (!IgnoreActor)
			{
				float DistanceSq = FVector::DistSquared(Start, OutHits[Index].Location);

				if (DistanceSq < ClosestDistanceSq && 0.0f < DistanceSq)
				{
					ClosestIndex	  = Index;
					ClosestDistanceSq = DistanceSq;
				}
			}
		}

		if (ClosestIndex != INDEX_NONE)
		{
			LastTraceHitLocation = OutHits[ClosestIndex].Location;

			// Interactive Actor
			if (ACsInteractiveActor* HitActor = Cast<ACsInteractiveActor>(OutHits[ClosestIndex].GetActor()))
			{
				if (HitActor->State != ECsInteractiveState::FirstFreeze &&
					HitActor->State != ECsInteractiveState::Freeze &&
					HitActor->State != ECsInteractiveState::FirstCollide &&
					HitActor->State != ECsInteractiveState::Collide)
				{
					Infos.AddDefaulted();
					const int32 Pos = Infos.Num() - 1;
					Infos[Pos].Instigator = this;
					Infos[Pos].Actor = HitActor;
					Infos[Pos].Component = OutHits[ClosestIndex].GetComponent();
					Infos[Pos].Location = OutHits[ClosestIndex].Location;
				}

				LastTraceHitActor = HitActor;
				HasHitValidObject = true;
			}
			// Interactive Pawn
			if (ACsInteractiveAIPawn* HitPawn = Cast<ACsInteractiveAIPawn>(OutHits[ClosestIndex].GetActor()))
			{
				Infos.AddDefaulted();
				const int32 Pos = Infos.Num() - 1;
				Infos[Pos].Instigator = this;
				Infos[Pos].Actor = HitPawn;
				Infos[Pos].Component = OutHits[ClosestIndex].GetComponent();
				Infos[Pos].Location = OutHits[ClosestIndex].Location;

				LastTraceHitActor = HitPawn;
				HasHitValidObject = true;
			}
		}
		else
		{
			LastTraceHitLocation = End;
		}
	}
	else
	{
		LastTraceHitLocation = End;
	}
	OnCalcCamera_Trace_UpdateComponents();
	OnInteraction(Infos);
}

void ACsMotionController::OnCalcCamera_Trace_UpdateComponents()
{
}

#pragma endregion Camera

// State
#pragma region

int32 ACsMotionController::GetCurrentInteractedActorInfosSize()
{
	return CurrentInteractedActorInfos.Num();
}

AActor* ACsMotionController::GetCurrentInteractedActor(const int32 &Index)
{
	if (Index < CurrentInteractedActorInfos.Num())
		return  CurrentInteractedActorInfos[Index].GetActor();

	UE_LOG(LogCs, Warning, TEXT("ACsMotionController::GetCurrentInteractiveActor: Index: %d is out of bounds. CurrentInteractedActorInfos.Num() = %d"), Index, CurrentInteractedActorInfos.Num());
	return nullptr;
}

void ACsMotionController::AddCurrentInteractedActor(AActor* Actor)
{
	CurrentInteractedActorInfos.AddDefaulted();
	const int32 Pos = CurrentInteractedActorInfos.Num() - 1;
	CurrentInteractedActorInfos[Pos].Instigator = this;
	CurrentInteractedActorInfos[Pos].Actor = Actor;
	CurrentInteractedActorInfos[Pos].Component = Actor->GetRootComponent();
}

void ACsMotionController::RemoveCurrentInteractedActorInfo(const int32 &Index)
{
	if (Index < CurrentInteractedActorInfos.Num())
	{
		CurrentInteractedActorInfos.RemoveAt(Index);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsMotionController::RemoveCurrentInteractiveActor: Index: %d is out of bounds. CurrentInteractedActorInfos.Num() = %d"), Index, CurrentInteractedActorInfos.Num());
	}
}

void ACsMotionController::ResetCurrentInteractedActorInfos()
{
	CurrentInteractedActorInfos.Reset();
}

void ACsMotionController::GetCurrentInteractiveActors(const TEnumAsByte<ECsInteractiveState::Type> &StateType, TArray<AActor*> &OutActors)
{
	const int32 Count = CurrentInteractiveActors.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (StateType == CurrentInteractiveActorStates[I])
		{
			if (AActor* Actor = CurrentInteractedActorInfos[I].GetActor())
				OutActors.Add(Actor);
		}
	}
}

void ACsMotionController::OnInteraction_Script(const TEnumAsByte<ECsInteractiveState::Type> &InState, const TArray<FCsInteractedActorInfo> &Infos)
{
	if (InState == ECsInteractiveState::FirstFreeze) { OnFirstFreeze(Infos); return; }
	if (InState == ECsInteractiveState::Freeze) { OnFreeze(Infos); return; }
	if (InState == ECsInteractiveState::FirstUnFreeze) { OnFirstUnFreeze(Infos); return; }
	if (InState == ECsInteractiveState::FirstHold) { OnFirstHold(Infos); return; }
	if (InState == ECsInteractiveState::Hold) { OnHold(Infos); return; }
	if (InState == ECsInteractiveState::Release) { OnRelease(Infos); return; }
	if (InState == ECsInteractiveState::FirstTouch) { OnFirstTouch(Infos); return; }
	if (InState == ECsInteractiveState::Touch) { OnTouch(Infos); return; }
	if (InState == ECsInteractiveState::FirstHover) { OnFirstHover(Infos); return; }
	if (InState == ECsInteractiveState::Hover) { OnHover(Infos); return; }
	if (InState == ECsInteractiveState::FirstUnHover) { OnFirstUnHover(Infos); return; }
	if (InState == ECsInteractiveState::FirstCollide) { OnFirstCollide(Infos); return; }
	if (InState == ECsInteractiveState::Collide) { OnCollide(Infos); return; }
	if (InState == ECsInteractiveState::FirstUnCollide) { OnFirstUnCollide(Infos); return; }
	if (InState == ECsInteractiveState::Remove) { OnRemove(Infos); return; }
}

void ACsMotionController::OnInteraction(const TArray<FCsInteractedActorInfo> &Infos)
{
	if (CurrentInteractedActorInfos.Num() == CS_EMPTY &&
		Infos.Num() == CS_EMPTY)
	{
		State = ECsInteractiveState::None;
		return;
	}

	const int32 CurrentActorCount = CurrentInteractedActorInfos.Num();
	const int32 InfoCount = Infos.Num();

	// Check for state change on CurrentInteractedActorInfos, resolve interacted actors

	if (InfoCount > CS_EMPTY)
	{
		TArray<FCsInteractedActorInfo> OnFirstTouchInfos;
		TArray<FCsInteractedActorInfo> OnTouchInfos;
		TArray<FCsInteractedActorInfo> OnFirstHoverInfos;
		TArray<FCsInteractedActorInfo> OnFirstUnHoverInfos;

		for (int32 I = 0; I < InfoCount; ++I)
		{
			// Append all actors to the end of the list. After checks, remove the front of the list
			CurrentInteractedActorInfos.Add(Infos[I]);
			
			AActor* Actor					 = Infos[I].GetActor();
			ACsInteractiveAIPawn* Pawn		 = Cast<ACsInteractiveAIPawn>(Actor);
			ACsInteractiveActor* Interactive = Cast<ACsInteractiveActor>(Actor);

			// Check if actually in Touch range rather than FirstHover
			if (Pawn)
			{
				if (Pawn->IsInTouchRange(this) && Pawn->CanBeTouched(this))
					CurrentInteractiveActorStates.Add(ECsInteractiveState::FirstTouch);
				else
					CurrentInteractiveActorStates.Add(ECsInteractiveState::FirstHover);
			}
			else
			{
				CurrentInteractiveActorStates.Add(ECsInteractiveState::FirstHover);
			}

			for (int32 J = 0; J < CurrentActorCount; J++)
			{
				// Check for state change
				if (Actor == CurrentInteractedActorInfos[J].GetActor())
				{
					CurrentInteractiveActorStates[CurrentActorCount + I] = CurrentInteractiveActorStates[J];

					// Check FirstTouch -> Touch
					if (CurrentInteractiveActorStates[J] == ECsInteractiveState::FirstTouch)
					{
						if (Pawn)
						{
							if (Pawn->IsInTouchRange(this) && Pawn->CanBeTouched(this))
							{
								CurrentInteractiveActorStates[J] = ECsInteractiveState::Touch;
								CurrentInteractiveActorStates[CurrentActorCount + I] = ECsInteractiveState::Touch;
							}
							// FirstTouch -> FirstHover
							else
							{
								if (!Interactive ||
									(Interactive && Interactive->CanChangeState(ECsInteractiveState::FirstTouch, ECsInteractiveState::FirstHover)))
								{
									CurrentInteractiveActorStates[J] = ECsInteractiveState::FirstHover;
									CurrentInteractiveActorStates[CurrentActorCount + I] = ECsInteractiveState::FirstHover;
								}
							}
						}
						// FirstTouch -> FirstHover
						else
						{
							if (!Interactive ||
								(Interactive && Interactive->CanChangeState(ECsInteractiveState::FirstTouch, ECsInteractiveState::FirstHover)))
							{
								CurrentInteractiveActorStates[J] = ECsInteractiveState::FirstHover;
								CurrentInteractiveActorStates[CurrentActorCount + I] = ECsInteractiveState::FirstHover;
							}
						}
					}
					// FirstHover -> Hover
					else
					if (CurrentInteractiveActorStates[J] == ECsInteractiveState::FirstHover)
					{
						if ((!Pawn && !Interactive) ||
							(Pawn && Pawn->CanChangeState(ECsInteractiveState::FirstHover, ECsInteractiveState::Hover)) ||
							(Interactive && Interactive->CanChangeState(ECsInteractiveState::FirstHover, ECsInteractiveState::Hover)))
						{
							CurrentInteractiveActorStates[J] = ECsInteractiveState::Hover;
							CurrentInteractiveActorStates[CurrentActorCount + I] = ECsInteractiveState::Hover;
						}
					}
				}
			}
		}

		// Remove from front of the list, resolve actors no longer being interacted with
		bool IsFirstUnHover = false;

		for (int32 I = CurrentActorCount - 1; I >= 0; --I)
		{
			bool Found = false;

			for (int32 J = 0; J < InfoCount; J++)
			{
				if (CurrentInteractedActorInfos[I].GetActor() == Infos[J].GetActor())
				{
					Found = true;
					break;
				}
			}

			if (!Found)
			{
				AActor* Actor					 = CurrentInteractedActorInfos[I].GetActor();
				ACsInteractiveAIPawn* Pawn		 = Cast<ACsInteractiveAIPawn>(Actor);
				ACsInteractiveActor* Interactive = Cast<ACsInteractiveActor>(Actor);

				// (FirstTouch | Touch) -> FirstUnHover (This should usually be FirstHover. But if it is NOT being interacted with, then UnHover)
				if (CurrentInteractiveActorStates[I] == ECsInteractiveState::FirstTouch ||
					CurrentInteractiveActorStates[I] == ECsInteractiveState::Touch)
				{
					TArray<TEnumAsByte<ECsInteractiveState::Type>> States;
					States.Add(ECsInteractiveState::FirstTouch);
					States.Add(ECsInteractiveState::Touch);

					if ((!Pawn && !Interactive) ||
						(Pawn && Pawn->CanChangeFromAnyState(States, ECsInteractiveState::FirstUnHover)) ||
						(Interactive && Interactive->CanChangeFromAnyState(States, ECsInteractiveState::FirstUnHover)))
					{
						IsFirstUnHover = true;
						OnFirstUnHoverInfos.AddDefaulted();
						OnFirstUnHoverInfos[OnFirstUnHoverInfos.Num() - 1] = CurrentInteractedActorInfos[I];
					}
				}
				// (FirstHover | Hover) -> FirstUnHover
				if (CurrentInteractiveActorStates[I] == ECsInteractiveState::FirstHover ||
					CurrentInteractiveActorStates[I] == ECsInteractiveState::Hover)
				{
					TArray<TEnumAsByte<ECsInteractiveState::Type>> States;
					States.Add(ECsInteractiveState::FirstHover);
					States.Add(ECsInteractiveState::Hover);

					if ((!Pawn && !Interactive) ||
						(Pawn && Pawn->CanChangeFromAnyState(States, ECsInteractiveState::FirstUnHover)) ||
						(Interactive && Interactive->CanChangeFromAnyState(States, ECsInteractiveState::FirstUnHover)))
					{
						IsFirstUnHover = true;
						OnFirstUnHoverInfos.AddDefaulted();
						OnFirstUnHoverInfos[OnFirstUnHoverInfos.Num() - 1] = CurrentInteractedActorInfos[I];
					}
				}
			}

			CurrentInteractedActorInfos.RemoveAt(I);
			CurrentInteractiveActorStates.RemoveAt(I);
		}

		// Final Resolve. Check for inputs / events based on interactive state

		bool IsFirstTouch = false; bool IsTouch = false;
		bool IsFirstHover = false; bool IsHover = false;

		for (int32 I = InfoCount - 1; I >= 0; --I)
		{
			AActor* Actor					 = CurrentInteractedActorInfos[I].GetActor();
			ACsInteractiveAIPawn* Pawn		 = Cast<ACsInteractiveAIPawn>(Actor);
			ACsInteractiveActor* Interactive = Cast<ACsInteractiveActor>(Actor);

			// ('CurrentState' | FirstHover | Hover | None) -> FirstTouch
			if (CurrentInteractiveActorStates[I] == ECsInteractiveState::FirstTouch)
			{
				TArray<TEnumAsByte<ECsInteractiveState::Type>> States;
				States.Add(ECsInteractiveState::FirstHover);
				States.Add(ECsInteractiveState::Hover);
				States.Add(ECsInteractiveState::None);

				if ((!Pawn && !Interactive) ||
					(Pawn && Pawn->CanChangeFromAnyState(States, ECsInteractiveState::FirstTouch)) ||
					(Interactive && Interactive->CanChangeFromAnyState(States, ECsInteractiveState::FirstTouch)))
				{
					IsFirstTouch = true;
					OnFirstTouchInfos.AddDefaulted();
					OnFirstTouchInfos[OnFirstTouchInfos.Num() - 1] = CurrentInteractedActorInfos[I];
				}
			}
			// FirstTouch -> Touch
			if (CurrentInteractiveActorStates[I] == ECsInteractiveState::Touch)
			{
				if ((!Pawn && !Interactive) ||
					(Pawn && Pawn->CanChangeState(ECsInteractiveState::FirstTouch, ECsInteractiveState::Touch)) ||
					(Interactive && Interactive->CanChangeState(ECsInteractiveState::FirstTouch, ECsInteractiveState::Touch)))
				{
					IsTouch = true;
					OnTouchInfos.AddDefaulted();
					OnTouchInfos[OnTouchInfos.Num() - 1] = CurrentInteractedActorInfos[I];
				}
			}
			// ('CurrentState' | None) -> FirstHover
			if (CurrentInteractiveActorStates[I] == ECsInteractiveState::FirstHover)
			{
				IsFirstHover = true;
				OnFirstHoverInfos.AddDefaulted();
				OnFirstHoverInfos[OnFirstHoverInfos.Num() - 1] = CurrentInteractedActorInfos[I];
			}
		}

		if (State != ECsInteractiveState::FirstHold && State != ECsInteractiveState::Hold &&
			State != ECsInteractiveState::FirstCollide && State != ECsInteractiveState::Collide)
		{
			if (IsTouch) { State = ECsInteractiveState::Touch; }
			else if (IsFirstTouch) { State = ECsInteractiveState::FirstTouch; }
			else if (IsHover) { State = ECsInteractiveState::Hover; }
			else if (IsFirstHover) { State = ECsInteractiveState::FirstHover; }
			else if (IsFirstUnHover) { State = ECsInteractiveState::FirstUnHover; }
		}

		OnFirstTouch(OnFirstTouchInfos);
		OnTouch(OnTouchInfos);
		OnFirstHover(OnFirstHoverInfos);
		OnFirstUnHover(OnFirstUnHoverInfos);
	}
	// No Interactions
	else
	{
		TArray<FCsInteractedActorInfo> OnFirstUnHoverInfos;
		TArray<FCsInteractedActorInfo> OnReleaseInfos;

		for (int32 I = 0; I < CurrentActorCount; ++I)
		{
			AActor* Actor = CurrentInteractedActorInfos[I].GetActor();

			if (!Actor)
				continue;

			// (FirstTouch | Touch | FirstHover | Hover) -> FirstUnHover
			if (CurrentInteractiveActorStates[I] == ECsInteractiveState::FirstTouch ||
				CurrentInteractiveActorStates[I] == ECsInteractiveState::Touch ||
				CurrentInteractiveActorStates[I] == ECsInteractiveState::FirstHover ||
				CurrentInteractiveActorStates[I] == ECsInteractiveState::Hover)
			{
				OnFirstUnHoverInfos.AddDefaulted();
				OnFirstUnHoverInfos[OnFirstUnHoverInfos.Num() - 1] = CurrentInteractedActorInfos[I];
			}
		}

		OnFirstUnHover(OnFirstUnHoverInfos);
		OnRelease(OnReleaseInfos);

		State = ECsInteractiveState::Release;

		CurrentInteractedActorInfos.Reset();
		CurrentInteractiveActorStates.Reset();
	}
}

void ACsMotionController::OnFirstFreeze(const TArray<FCsInteractedActorInfo> &Infos){}
void ACsMotionController::OnFreeze(const TArray<FCsInteractedActorInfo> &Infos){}
void ACsMotionController::OnFirstUnFreeze(const TArray<FCsInteractedActorInfo> &Infos){}

void ACsMotionController::OnFirstHold(const TArray<FCsInteractedActorInfo> &Infos)
{
	const int32 Count = Infos.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		// Interactive Actor
		if (ACsInteractiveActor* Actor = Cast<ACsInteractiveActor>(Infos[I].GetActor()))
			Actor->OnFirstHold(Infos[I]);
		// Interactive Pawn
		else
		if (ACsInteractiveAIPawn* Pawn = Cast<ACsInteractiveAIPawn>(Infos[I].GetActor()))
			Pawn->OnFirstHold(Infos[I]);
	}
}

void ACsMotionController::OnHold(const TArray<FCsInteractedActorInfo> &Infos)
{
	const int32 Count = Infos.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		// Interactive Actor
		if (ACsInteractiveActor* Actor = Cast<ACsInteractiveActor>(Infos[I].GetActor()))
			Actor->OnHold(Infos[I]);
		// Interactive Pawn
		else
		if (ACsInteractiveAIPawn* Pawn = Cast<ACsInteractiveAIPawn>(Infos[I].GetActor()))
			Pawn->OnHold(Infos[I]);
	}
}

void ACsMotionController::OnRelease(const TArray<FCsInteractedActorInfo> &Infos)
{
	const int32 Count = Infos.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		// Interactive Actor
		if (ACsInteractiveActor* Actor = Cast<ACsInteractiveActor>(Infos[I].GetActor()))
			Actor->OnRelease(Infos[I]);
		// Interactive Pawn
		else
		if (ACsInteractiveAIPawn* Pawn = Cast<ACsInteractiveAIPawn>(Infos[I].GetActor()))
			Pawn->OnRelease(Infos[I]);
	}
}

void ACsMotionController::OnFirstTouch(const TArray<FCsInteractedActorInfo> &Infos)
{
	const int32 Count = Infos.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		// Interactive Actor
		if (ACsInteractiveActor* Actor = Cast<ACsInteractiveActor>(Infos[I].GetActor()))
			Actor->OnFirstTouch(Infos[I]);
		// Interactive Pawn
		else
		if (ACsInteractiveAIPawn* Pawn = Cast<ACsInteractiveAIPawn>(Infos[I].GetActor()))
			Pawn->OnFirstTouch(Infos[I]);
	}
}

void ACsMotionController::OnTouch(const TArray<FCsInteractedActorInfo> &Infos)
{
	const int32 Count = Infos.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		// Interactive Actor
		if (ACsInteractiveActor* Actor = Cast<ACsInteractiveActor>(Infos[I].GetActor()))
			Actor->OnTouch(Infos[I]);
		// Interactive Pawn
		else
		if (ACsInteractiveAIPawn* Pawn = Cast<ACsInteractiveAIPawn>(Infos[I].GetActor()))
			Pawn->OnTouch(Infos[I]);
	}
}

void ACsMotionController::OnFirstHover(const TArray<FCsInteractedActorInfo> &Infos)
{
	const int32 Count = Infos.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		// Interactive Actor
		if (ACsInteractiveActor* Actor = Cast<ACsInteractiveActor>(Infos[I].GetActor()))
			Actor->OnFirstHover(Infos[I]);
		// Interactive Pawn
		else
		if (ACsInteractiveAIPawn* Pawn = Cast<ACsInteractiveAIPawn>(Infos[I].GetActor()))
			Pawn->OnFirstHover(Infos[I]);
	}
}

void ACsMotionController::OnHover(const TArray<FCsInteractedActorInfo> &Infos){}

void ACsMotionController::OnFirstUnHover(const TArray<FCsInteractedActorInfo> &Infos)
{
	const int32 Count = Infos.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		// Interactive Actor
		if (ACsInteractiveActor* Actor = Cast<ACsInteractiveActor>(Infos[I].GetActor()))
			Actor->OnFirstUnHover(Infos[I]);
		// Interactive Pawn
		else
		if (ACsInteractiveAIPawn* Pawn = Cast<ACsInteractiveAIPawn>(Infos[I].GetActor()))
			Pawn->OnFirstUnHover(Infos[I]);
	}
}

void ACsMotionController::OnFirstCollide(const TArray<FCsInteractedActorInfo> &Infos)
{
	const int32 Count = Infos.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		// Interactive Actor
		if (ACsInteractiveActor* Actor = Cast<ACsInteractiveActor>(Infos[I].GetActor()))
			Actor->OnFirstCollide(Infos[I]);
		// Interactive Pawn
		else
		if (ACsInteractiveAIPawn* Pawn = Cast<ACsInteractiveAIPawn>(Infos[I].GetActor()))
		Pawn->OnFirstCollide(Infos[I]);
	}
}

void ACsMotionController::OnCollide(const TArray<FCsInteractedActorInfo> &Infos){}
void ACsMotionController::OnFirstUnCollide(const TArray<FCsInteractedActorInfo> &Infos){}
void ACsMotionController::OnRemove(const TArray<FCsInteractedActorInfo> &Infos){}

bool ACsMotionController::IsInteractingWith(const TEnumAsByte<ECsInteractiveState::Type> &InState, AActor* InActor)
{
	AActor* FoundActor = nullptr;
	const int32 Count  = CurrentInteractedActorInfos.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		AActor* Actor = CurrentInteractedActorInfos[I].GetActor();

		if (Actor != InActor)
			continue;

		FoundActor = Actor;

		if (CurrentInteractiveActorStates[I] != InState)
			return false;
		break;
	}

	if (ACsInteractiveActor* InteractiveActor = Cast<ACsInteractiveActor>(FoundActor))
		return InteractiveActor->State == InState;
	return true;
}

bool ACsMotionController::IsInteractingWithAny(const TEnumAsByte<ECsInteractiveState::Type> &InState)
{
	TArray<AActor*> Actors;

	int32 Count = CurrentInteractedActorInfos.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (CurrentInteractiveActorStates[I] != InState)
			continue;

		AActor* Actor = CurrentInteractedActorInfos[I].GetActor();
		Actors.Add(Actor);
	}

	Count = Actors.Num();

	if (Count == CS_EMPTY)
		return false;

	for (int32 I = 0; I < Count; ++I)
	{
		if (ACsInteractiveActor* InteractiveActor = Cast<ACsInteractiveActor>(Actors[I]))
			return InteractiveActor->State == InState;
	}
	return true;
}

bool ACsMotionController::IsHolding(AActor* InActor)
{ 
	return IsInteractingWith(ECsInteractiveState::FirstHold, InActor) || IsInteractingWith(ECsInteractiveState::Hold, InActor);
}

bool ACsMotionController::IsHoldingAny()
{
	return IsInteractingWithAny(ECsInteractiveState::FirstHold) || IsInteractingWithAny(ECsInteractiveState::Hold);
}

bool ACsMotionController::IsHoveringOver(AActor* InActor)
{
	return IsInteractingWith(ECsInteractiveState::FirstHover, InActor) || IsInteractingWith(ECsInteractiveState::Hover, InActor);
}

bool ACsMotionController::IsHoveringOverAny()
{
	return IsInteractingWithAny(ECsInteractiveState::FirstHover) || IsInteractingWithAny(ECsInteractiveState::Hover);
}

#pragma endregion State

// Button State
#pragma region

void ACsMotionController::GetCurrentButtons(const ECsButtonState &StateType, TArray<USceneComponent*> &OutButtons)
{
	const int32 Count = CurrentButtons.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (StateType == CurrentButtonStates[I])
		{
			USceneComponent* Component = CurrentButtons[I].IsValid() ? CurrentButtons[I].Get() : nullptr;

			if (Component)
				OutButtons.Add(Component);
		}
	}
}

void ACsMotionController::OnButtonInteraction_Script(const ECsButtonState &InState, const TArray<USceneComponent*> Buttons)
{
	if (InState == ECsButtonState::FirstHover) { OnButtonFirstHover(Buttons); return; }
	if (InState == ECsButtonState::Hover) { OnButtonHover(Buttons); return; }
	if (InState == ECsButtonState::FirstUnHover) { OnButtonFirstUnHover(Buttons); return; }
	if (InState == ECsButtonState::FirstPressed) { OnButtonFirstPressed(Buttons); return; }
	if (InState == ECsButtonState::Pressed) { OnButtonPressed(Buttons); return; }
	if (InState == ECsButtonState::FirstReleased) { OnButtonFirstReleased(Buttons); return; }
}

void ACsMotionController::OnButtonInteraction(const TArray<USceneComponent*> &Buttons)
{
	if (CurrentButtons.Num() == CS_EMPTY &&
		Buttons.Num() == CS_EMPTY)
	{
		ButtonState = ECsButtonState::None;
		return;
	}

	const int32 CurrentButtonCount = CurrentButtons.Num();
	const int32 ButtonCount		   = Buttons.Num();

	// Check for state change on CurrentButtons, resolve interacted buttons

	if (ButtonCount > CS_EMPTY)
	{
		TArray<USceneComponent*> OnFirstHoverButtons;
		TArray<USceneComponent*> OnFirstUnHoverButtons;

		for (int32 I = 0; I < ButtonCount; ++I)
		{
			// Append all actors to the end of the list. After checks, remove the front of the list
			CurrentButtons.Add(Buttons[I]);

			UCsButtonComponent* Button = Cast<UCsButtonComponent>(Buttons[I]);

			CurrentButtonStates.Add(ECsButtonState::FirstHover);

			for (int32 J = 0; J < CurrentButtonCount; J++)
			{
				// Check for state change
				if (Buttons[I] == CurrentButtons[J])
				{
					CurrentButtonStates[CurrentButtonCount + I] = CurrentButtonStates[J];

					// FirstHover -> Hover
					if (CurrentButtonStates[J] == ECsButtonState::FirstHover)
					{
						if (!Button||
							(Button && Button->CanChangeState(ECsButtonState::FirstHover, ECsButtonState::Hover)))
						{
							CurrentButtonStates[J]						= ECsButtonState::Hover;
							CurrentButtonStates[CurrentButtonCount + I] = ECsButtonState::Hover;
						}
					}
				}
			}
		}

		// Remove from front of the list, resolve buttons no longer being interacted with
		bool IsFirstUnHover = false;

		for (int32 I = CurrentButtonCount - 1; I >= 0; --I)
		{
			bool Found = false;

			for (int32 J = 0; J < ButtonCount; J++)
			{
				if (CurrentButtons[I] == Buttons[J])
				{
					Found = true;
					break;
				}
			}

			if (!Found)
			{
				USceneComponent* Component = CurrentButtons[I].IsValid() ? CurrentButtons[I].Get() : nullptr;
				UCsButtonComponent* Button = Cast<UCsButtonComponent>(Component);

				// (FirstHover | Hover) -> FirstUnHover
				if (CurrentButtonStates[I] == ECsButtonState::FirstHover ||
					CurrentButtonStates[I] == ECsButtonState::Hover)
				{
					TArray<ECsButtonState> States;
					States.Add(ECsButtonState::FirstHover);
					States.Add(ECsButtonState::Hover);

					if (!Button ||
						(Button && Button->CanChangeFromAnyState(States, ECsButtonState::FirstUnHover)))
					{
						IsFirstUnHover = true;
						OnFirstUnHoverButtons.Add(Button);
					}
				}
			}

			CurrentButtons.RemoveAt(I);
			CurrentButtonStates.RemoveAt(I);
		}

		// Final Resolve. Check for inputs / events based on button state

		bool IsFirstHover = false; bool IsHover = false;

		for (int32 I = ButtonCount - 1; I >= 0; --I)
		{
			USceneComponent* Component = CurrentButtons[I].IsValid() ? CurrentButtons[I].Get() : nullptr;
			UCsButtonComponent* Button = Cast<UCsButtonComponent>(Component);

			// ('CurrentState' | None) -> FirstHover
			if (CurrentInteractiveActorStates[I] == ECsButtonState::FirstHover)
			{
				IsFirstHover = true;
				OnFirstHoverButtons.Add(Component);
			}
		}

		if (ButtonState != ECsButtonState::FirstPressed && ButtonState != ECsButtonState::Pressed)
		{
			if (IsHover) { ButtonState = ECsButtonState::Hover; }
			else if (IsFirstHover) { ButtonState = ECsButtonState::FirstHover; }
			else if (IsFirstUnHover) { ButtonState = ECsButtonState::FirstUnHover; }
		}

		OnButtonFirstHover(OnFirstHoverButtons);
		OnButtonFirstUnHover(OnFirstUnHoverButtons);
	}
	// No Interactions
	else
	{
		TArray<USceneComponent*> OnFirstUnHoverButtons;
		TArray<USceneComponent*> OnFirstReleasedButtons;

		for (int32 I = 0; I < CurrentButtonCount; ++I)
		{
			USceneComponent* Component = CurrentButtons[I].IsValid() ? CurrentButtons[I].Get() : nullptr;

			if (!Component)
				continue;

			// (FirstHover | Hover) -> FirstUnHover
			if (CurrentInteractiveActorStates[I] == ECsButtonState::FirstHover ||
				CurrentInteractiveActorStates[I] == ECsButtonState::Hover)
			{
				OnFirstUnHoverButtons.Add(Component);
			}
		}

		OnButtonFirstUnHover(OnFirstUnHoverButtons);
		OnButtonFirstReleased(OnFirstReleasedButtons);

		ButtonState = ECsButtonState::FirstReleased;

		CurrentButtons.Reset();
		CurrentButtonStates.Reset();
	}
}

void ACsMotionController::OnButtonFirstHover(const TArray<USceneComponent*> &Buttons)
{
	const int32 Count = Buttons.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (UCsButtonComponent* Button = Cast<UCsButtonComponent>(Buttons[I]))
			Button->OnFirstHover(this);
	}
}

void ACsMotionController::OnButtonHover(const TArray<USceneComponent*> &Buttons)
{
}

void ACsMotionController::OnButtonFirstUnHover(const TArray<USceneComponent*> &Buttons)
{
	const int32 Count = Buttons.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (UCsButtonComponent* Button = Cast<UCsButtonComponent>(Buttons[I]))
			Button->OnFirstUnHover(this);
	}
}

void ACsMotionController::OnButtonFirstPressed(const TArray<USceneComponent*> &Buttons)
{
	const int32 Count = Buttons.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (UCsButtonComponent* Button = Cast<UCsButtonComponent>(Buttons[I]))
			Button->OnFirstPressed(this);
	}
}

void ACsMotionController::OnButtonPressed(const TArray<USceneComponent*> &Buttons)
{
}

void ACsMotionController::OnButtonFirstReleased(const TArray<USceneComponent*> &Buttons)
{
}


bool ACsMotionController::IsInteractingWithButton(const ECsButtonState &InState, USceneComponent* InButton)
{
	USceneComponent* FoundButton = nullptr;
	const int32 Count			 = CurrentButtons.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		USceneComponent* Component = CurrentButtons[I].IsValid() ? CurrentButtons[I].Get() : nullptr;

		if (Component != InButton)
			continue;

		FoundButton = Component;

		if (CurrentButtonStates[I] != InState)
			return false;
		break;
	}

	if (UCsButtonComponent* Button = Cast<UCsButtonComponent>(FoundButton))
		return Button->State == InState;
	return true;
}

bool ACsMotionController::IsInteractingWithAnyButton(const ECsButtonState &InState)
{
	TArray<USceneComponent*> Components;

	int32 Count = CurrentButtons.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (CurrentButtonStates[I] != InState)
			continue;

		USceneComponent* Component = CurrentButtons[I].IsValid() ? CurrentButtons[I].Get() : nullptr;
		Components.Add(Component);
	}

	Count = Components.Num();

	if (Count == CS_EMPTY)
		return false;

	for (int32 I = 0; I < Count; ++I)
	{
		if (UCsButtonComponent* Button = Cast<UCsButtonComponent>(Components[I]))
			return Button->State == InState;
	}
	return true;
}

bool ACsMotionController::IsHoveringOverButton(USceneComponent* InButton)
{
	return IsInteractingWithButton(ECsButtonState::FirstHover, InButton) || IsInteractingWithButton(ECsButtonState::Hover, InButton);
}

bool ACsMotionController::IsHoveringOverAnyButton()
{
	return IsInteractingWithAnyButton(ECsButtonState::FirstHover) || IsInteractingWithAnyButton(ECsButtonState::Hover);
}

#pragma endregion Button State

void ACsMotionController::Show()
{
	SetActorHiddenInGame(false);

	USceneComponent* Component = GetRootComponent();

	UCsCommon::EnableComponent(Component, true);
	UCsCommon::EnableComponent(GetMotionControllerComponent(), true);
	UCsCommon::EnableComponent(AnchorComponent, true);

	if (UseSkeletalMesh)
		UCsCommon::EnableComponent(SkeletalMeshComponent, true);
	if (UseSkeletalMesh)
		UCsCommon::EnableComponent(SkeletalMeshComponent, true);

	if (CollisionType != ECsInteractiveCollision::Trace &&
		InteractiveCollisionComponent)
	{
		InteractiveCollisionComponent->SetCollisionResponseToChannels(CollisionPreset.CollisionResponses);
		InteractiveCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		InteractiveCollisionComponent->SetNotifyRigidBodyCollision(true);
		InteractiveCollisionComponent->SetComponentTickEnabled(true);
	}
	UpdateComponentTransforms();
}

void ACsMotionController::Hide()
{
	USceneComponent* Component = GetRootComponent();

	UCsCommon::DisableComponent(Component, false, true, true);
	UCsCommon::DisableComponent(GetMotionControllerComponent(), false, true, true);
	UCsCommon::DisableComponent(AnchorComponent, false, true, true);

	if (UseSkeletalMesh)
		UCsCommon::DisableComponent(SkeletalMeshComponent, false, true, true);
	if (UseSkeletalMesh)
		UCsCommon::DisableComponent(SkeletalMeshComponent, false, true, true);

	if (InteractiveCollisionComponent)
	{
		InteractiveCollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
		InteractiveCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		InteractiveCollisionComponent->SetNotifyRigidBodyCollision(false);
		InteractiveCollisionComponent->SetComponentTickEnabled(false);
	}
	SetActorHiddenInGame(true);
}