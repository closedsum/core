// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Pawn/CsPawn.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Library/CsLibrary_Common.h"
#include "Coroutine/CsCoroutineScheduler.h"

// Data
#include "Data/CsDataMapping.h"
#include "Data/CsData_Character.h"
#include "Data/CsData_CharacterMeshSkin.h"
#include "Data/CsData_CharacterMaterialSkin.h"
// Managers
#include "Managers/Inventory/CsManager_Inventory.h"
#include "Managers/Sense/CsManager_Sense_DEPRECATED.h"
#include "Managers/Trace/CsManager_Trace.h"
#include "Managers/Time/CsManager_Time.h"
// UI
#include "UI/State/CsHealthBarComponent.h"
// Game
#include "Game/CsGameInstance.h"
// Player
#include "Player/CsPlayerStateBase.h"
// Weapon
#include "Weapon/CsWeapon.h"

// Enums
#pragma region

	// PawnRoutine
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsPawnRoutine)

namespace ECsPawnRoutine
{
	CSCORE_API const FECsPawnRoutine CheckLinkedToPlayerState_Internal = EMCsPawnRoutine::Get().Create(TEXT("CheckLinkedToPlayerState_Internal"));
	CSCORE_API const FECsPawnRoutine HandleRespawnTimer_Internal = EMCsPawnRoutine::Get().Create(TEXT("HandleRespawnTimer_Internal"));
}

#pragma endregion Enums

// Cache
#pragma region

namespace NCsPawnCached
{
	namespace Name
	{
		// Functions
		const FName CheckLinkedToPlayerState_Internal = FName("ACsPawn::CheckLinkedToPlayerState_Internal");
		const FName HandleRespawnTimer_Internal = FName("ACsPawn::HandleRespawnTimer_Internal");
	};

	namespace Str
	{
		// Functions
		const FString CheckLinkedToPlayerState_Internal = TEXT("ACsPawn::CheckLinkedToPlayerState_Internal");
		const FString HandleRespawnTimer_Internal = TEXT("ACsPawn::HandleRespawnTimer_Internal");
	};
}

#pragma endregion Cache

ACsPawn::ACsPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentViewType = ECsViewType::ThirdPerson;

	WeaponClass = ACsWeapon::StaticClass();

	// State
	HealthHandle.Set(&Health);
	HealthHandle.OnChange_Event.AddUObject(this, &ACsPawn::OnChange_Health);

	bFirstSpawn = true;

	OnHandleRespawnTimerFinished_Event.AddUObject(this, &ACsPawn::OnHandleRespawnTimerFinished);
	// View
	bPerformViewTrace = false;

	ViewTraceInfo.bAsync = true;
	ViewTraceInfo.bForce = false;
	ViewTraceInfo.QueryParams.TraceTag = FName("PerformViewTrace");
	ViewTraceInfo.IgnoredActors.Add(this);
	ViewTraceInfo.ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	ViewTraceInfo.ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);
	ViewTraceInfo.ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	ViewTraceInfo.ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	ViewTraceInfo.Range	  = 30000.0f;
	ViewTraceInfo.RangeSq = ViewTraceInfo.Range * ViewTraceInfo.Range;
	// Movement
	CurrentJumpMovementState = ECsCharacterJumpMovementState::Grounded;
	// Data
	bCacheData = true;
	// Weapon
	CurrentWeaponSlotHandle.Set(&CurrentWeaponSlot);
	CurrentWeaponSlotHandle.OnChange_Event.AddUObject(this, &ACsPawn::OnChange_CurrentWeaponSlot);
}

void ACsPawn::OnConstructor(const FObjectInitializer& ObjectInitializer)
{
	if (bHealthBar)
	{
		HealthBarComponent = ObjectInitializer.CreateDefaultSubobject<UCsHealthBarComponent>(this, TEXT("HealthBarComponent"));
		HealthBarComponent->SetVisibility(false);
		HealthBarComponent->SetHiddenInGame(true);
		HealthBarComponent->SetCollisionObjectType(ECC_Visibility);
		HealthBarComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		HealthBarComponent->SetCastShadow(false);
		HealthBarComponent->SetMobility(EComponentMobility::Movable);
		HealthBarComponent->SetupAttachment(GetRootComponent());
		HealthBarComponent->Deactivate();
	}
}

void ACsPawn::PostActorCreated()
{
	Super::PostActorCreated();
}

void ACsPawn::Destroyed()
{
	Super::Destroyed();

#if WITH_EDITOR
	if (UCsLibrary_Common::IsPlayInEditor(GetWorld()) || UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
		return;
#endif // #if WITH_EDITOR

	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
	GameInstance->UnregisterUniqueObject(UniqueObjectId);

	for (int32 I = 0; I < MaxWeaponCount; I++)
	{
		if (!Weapons[I] && !Weapons[I]->IsPendingKill())
			Weapons[I]->Destroy();
	}

	if (!Manager_Sense && !Manager_Sense->IsPendingKill())
		Manager_Sense->Destroy();
}

void ACsPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// TODO: Test placing actors in the level and see how this affects spawning weapons
#if WITH_EDITOR
	if (UCsLibrary_Common::IsPlayInEditor(GetWorld()) || UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
		return;
#endif // #if WITH_EDITOR

	if (!IsPendingKill())
	{
		bPlacedInWorld = GetWorld()->bStartup;
	}

	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
	UniqueObjectId				  = GameInstance->RegisterUniqueObject(this);

	// Spawn Weapons
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	for (int32 I = 0; I < MaxWeaponCount; I++)
	{
		Weapons[I] = GetWorld()->SpawnActor<ACsWeapon>(WeaponClass, SpawnInfo);
		Weapons[I]->SetMyPawn(this);
	}

	CheckLinkedToPlayerState();
}

void ACsPawn::PreTick(const float &DeltaSeconds)
{
	RecordRoot();
	RecordVelocityAndSpeed();

	if (bTraceToGroundWhileJumping &&
		CurrentJumpMovementState != ECsCharacterJumpMovementState::Grounded)
	{
		const float& Interval = TraceToGroundWhileJumpingInfo.Interval;
		float& LastTime		  = TraceToGroundWhileJumpingInfo.LastTime;

		if (Interval == 0.0f ||
			GetWorld()->GetTimeSeconds() - LastTime >= Interval)
		{
			TraceToGroundWhileJumping();

			LastTime = GetWorld()->GetTimeSeconds();
		}
	}
}

void ACsPawn::PostTick(const float &DeltaSeconds){}

void ACsPawn::OnTickActor_HandleCVars(const float &DeltaSeconds) {};

// Setup
#pragma region

void ACsPawn::CheckLinkedToPlayerState()
{
	const FECsUpdateGroup& Group = NCsUpdateGroup::GameState;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(GetGameInstance());
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&ACsPawn::CheckLinkedToPlayerState_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetGameInstance())->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsPawnCached::Name::CheckLinkedToPlayerState_Internal);
	Payload->SetNameAsString(NCsPawnCached::Str::CheckLinkedToPlayerState_Internal);

	Scheduler->Start(Payload);
}

CS_COROUTINE(ACsPawn, CheckLinkedToPlayerState_Internal)
{
	ACsPawn* p			   = r->GetOwnerAsObject<ACsPawn>();
	ACsPlayerStateBase* ps = p->GetPlayerState<ACsPlayerStateBase>();

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_WAIT_UNTIL(r, ps);

	ps->LinkedPawn = p;
	ps->OnLinkedPawnSet_Event.Broadcast(ps);

	CS_COROUTINE_END(r);
}

bool ACsPawn::IsOnBoardCompleted_Game()
{
	ACsPlayerStateBase* MyPlayerState = GetPlayerState<ACsPlayerStateBase>();

	if (!MyPlayerState)
		return false;
	return MyPlayerState->IsOnBoardCompleted_Game();
}

void ACsPawn::OnTick_HandleSetup() {}

#pragma endregion Setup

// State
#pragma region

	// Spawn
#pragma region

void ACsPawn::OnFirstSpawn(){}

void ACsPawn::HandleRespawnTimer()
{
	const FECsUpdateGroup& Group = NCsUpdateGroup::GameState;

	UCsCoroutineScheduler* Scheduler			   = UCsCoroutineScheduler::Get(GetGameInstance());
	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&ACsPawn::HandleRespawnTimer_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetGameInstance())->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsPawnCached::Name::HandleRespawnTimer_Internal);
	Payload->SetNameAsString(NCsPawnCached::Str::HandleRespawnTimer_Internal);

	Scheduler->Start(Payload);
}

CS_COROUTINE(ACsPawn, HandleRespawnTimer_Internal)
{
	ACsPawn* p				 = r->GetOwnerAsObject<ACsPawn>();
	ACsPlayerStateBase* ps	 = p->GetPlayerState<ACsPlayerStateBase>();

	UCsData_Character* Data_Character = p->GetMyData_Character();

	const FCsDeltaTime& ElapsedTime = r->ElapsedTime;
	const float RespawnTime			= Data_Character->GetRespawnTime();

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_WAIT_UNTIL(r, ElapsedTime.Time >= RespawnTime);

	p->OnHandleRespawnTimerFinished_Event.Broadcast(ps->UniqueMappingId);

	CS_COROUTINE_END(r);
}

void ACsPawn::OnHandleRespawnTimerFinished(const uint8 &MappingId) {}

#pragma endregion Spawn

	// Health
#pragma region

void ACsPawn::SetHealth(const float& InHealth)
{
	Health = FMath::Max(0.0f, InHealth);

	HealthHandle.UpdateIsDirty();

	if (HealthHandle.HasChanged())
	{
		HealthHandle.Clear();
	}
}

void ACsPawn::OnChange_Health(const float &Value){}

#pragma endregion Health

	// Damage
#pragma region

void ACsPawn::ApplyDamage(FCsDamageEvent* Event)
{
	Health -= FMath::CeilToInt(Event->Damage);

	if (Health <= 0)
	{
		Health = 0.0f;
	}
}

void ACsPawn::OnApplyDamage_Result(FCsDamageResult* Result)
{
	ACsPlayerStateBase* MyPlayerState = GetPlayerState<ACsPlayerStateBase>();

	OnApplyDamage_Result_Event.Broadcast(MyPlayerState->UniqueMappingId, Result);
#if WITH_EDITOR
	OnApplyDamage_Result_ScriptEvent.Broadcast(MyPlayerState->UniqueMappingId, *Result);
#endif // #if WITH_EDITOR
}

#pragma endregion Damage

void ACsPawn::Die()
{
	bSpawnedAndActive = false;
}

#pragma endregion State

// Routines
#pragma region

/*static*/ void ACsPawn::AddRoutine(UObject* InPawn, struct FCsRoutine* Routine, const uint8 &InType)
{
	Cast<ACsPawn>(InPawn)->AddRoutine_Internal(Routine, InType);
}

bool ACsPawn::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType)
{
	const FECsPawnRoutine& RoutineType = EMCsPawnRoutine::Get()[InType];

	// CheckLinkedToPlayerState_Internal
	if (RoutineType == ECsPawnRoutine::CheckLinkedToPlayerState_Internal)
	{
		CheckLinkedToPlayerState_Internal_Routine = Routine;
		return true;
	}
	// HandleRespawnTimer_Internal
	if (RoutineType == ECsPawnRoutine::HandleRespawnTimer_Internal)
	{
		HandleRespawnTimer_Internal_Routine = Routine;
		return true;
	}
	return false;
}

/*static*/ void ACsPawn::RemoveRoutine(UObject* InPawn, struct FCsRoutine* Routine, const uint8 &InType)
{
	Cast<ACsPawn>(InPawn)->RemoveRoutine_Internal(Routine, InType);
}

bool ACsPawn::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType)
{
	const FECsPawnRoutine& RoutineType = EMCsPawnRoutine::Get()[InType];

	// CheckLinkedToPlayerState_Internal
	if (RoutineType == ECsPawnRoutine::CheckLinkedToPlayerState_Internal)
	{
		check(CheckLinkedToPlayerState_Internal_Routine == Routine);
		CheckLinkedToPlayerState_Internal_Routine = nullptr;
		return true;
	}
	// HandleRespawnTimer_Internal
	if (RoutineType == ECsPawnRoutine::HandleRespawnTimer_Internal)
	{
		check(HandleRespawnTimer_Internal_Routine == Routine);
		HandleRespawnTimer_Internal_Routine = nullptr;
		return true;
	}
	return false;
}

#pragma endregion Routines

// View
#pragma region

ECsViewType ACsPawn::GetCurrentViewType()
{
	return CurrentViewType;
}

void ACsPawn::PerformViewTrace()
{
	TArray<FHitResult>& OutHits = ViewTraceInfo.OutHits;
	OutHits.Reset();

	const FVector Start = CurrentViewLocation;
	const FVector Dir	= CurrentViewDir;
	const FVector End	= Start + ViewTraceInfo.Range * Dir;

	ViewTraceInfo.HitResult.Reset(0.0f, false);

	ACsManager_Trace* Manager_Trace = ACsManager_Trace::Get(GetWorld());
	FCsTraceRequest* Request		= Manager_Trace->AllocateRequest();

	Request->bForce		= ViewTraceInfo.bForce;
	Request->Caller		= this;
	Request->CallerId	= UniqueObjectId;
	Request->Start		= Start;
	Request->End		= End;
	Request->bAsync		= ViewTraceInfo.bAsync;
	Request->Type		= ECsTraceType::Line;
	Request->Method		= ECsTraceMethod::Multi;
	Request->Query		= ECsTraceQuery::ObjectType;
	UCsLibrary_Common::CopyCollisionObjectQueryParams(ViewTraceInfo.ObjectParams, Request->ObjectParams);

	TArray<AActor*> Actors;

	for (TWeakObjectPtr<AActor>& Actor : ViewTraceInfo.IgnoredActors)
	{
		Actors.Add(Actor.IsValid() ? Actor.Get() : nullptr);
	}
	Request->Params.AddIgnoredActors(Actors);

	Request->ReplacePending = !ViewTraceInfo.bForce;
	Request->PendingId		= ViewTraceInfo.RequestId;

	Request->OnResponse_Event.AddUObject(this, &ACsPawn::PerformViewTrace_Response);

	ViewTraceInfo.RequestId = Request->Id;

	FCsTraceResponse* Response = Manager_Trace->Trace(Request);

	if (ViewTraceInfo.bAsync)
		return;

	PerformViewTrace_Response(ViewTraceInfo.RequestId, Response);
}

void ACsPawn::PerformViewTrace_Response(const uint8 &RequestId, FCsTraceResponse* Response)
{
	const bool HitFound = Response->bResult;

	if (Response->OutHits.Num() > CS_EMPTY)
		UCsLibrary_Common::CopyHitResult(Response->OutHits[CS_FIRST], ViewTraceInfo.HitResult);

	Response->Reset();

	if (HitFound)
	{
		float ClosestDistanceSq = ViewTraceInfo.RangeSq;
		int32 ClosestIndex		= INDEX_NONE;
		bool IgnoreActor		= false;

		TArray<FHitResult>& OutHits = Response->OutHits;
		const int32 HitCount		= OutHits.Num();

		for (int32 Index = 0; Index < HitCount; ++Index)
		{
			IgnoreActor = false;

			if (!IgnoreActor)
			{
				float DistanceSq = FVector::DistSquared(OutHits[Index].TraceStart, OutHits[Index].Location);

				if (DistanceSq > 0.0f &&
					DistanceSq < ClosestDistanceSq)
				{
					ClosestIndex = Index;
					ClosestDistanceSq = DistanceSq;
				}
			}
		}

		if (ClosestIndex != INDEX_NONE)
		{
			ViewTraceInfo.HitLocation = OutHits[ClosestIndex].Location;

			UCsLibrary_Common::CopyHitResult(OutHits[ClosestIndex], ViewTraceInfo.HitResult);
		}
		else
		{
			const FVector Start		  = CurrentViewLocation;
			const FVector Dir		  = CurrentViewDir;
			const FVector End		  = Start + ViewTraceInfo.Range * Dir;
			ViewTraceInfo.HitLocation = End;
		}
	}
	else
	{
		const FVector Start		 = CurrentViewLocation;
		const FVector Dir		  = CurrentViewDir;
		const FVector End		  = Start + ViewTraceInfo.Range * Dir;
		ViewTraceInfo.HitLocation = End;
	}
}

void ACsPawn::RecordView() {}

#pragma endregion View

// Body / Root
#pragma region

void ACsPawn::RecordRoot()
{
	CurrentRootRotation = GetActorRotation();
	CurrentRootLocation = GetActorLocation();
	CurrentBodyLocation = CurrentRootLocation;
	CurrentFeetLocation = CurrentBodyLocation - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	CurrentRootDir		= CurrentRootRotation.Vector();
	CurrentRootDirXY	= FRotator(0.0f, CurrentRootRotation.Yaw, 0.0f).Vector();

	FRotator Rotation = CurrentRootRotation;

	FRotationMatrix Matrix = FRotationMatrix(Rotation);
	CurrentRootRight = Matrix.GetScaledAxis(EAxis::Y);

	Rotation = FRotator(0.0f, CurrentRootRotation.Yaw, 0.0f);

	Matrix = FRotationMatrix(Rotation);
	CurrentRootRightXY = Matrix.GetScaledAxis(EAxis::Y);
}

#pragma endregion Body / Root

// Movement
#pragma region

void ACsPawn::RecordVelocityAndSpeed()
{
	// Velocity from CharacterMovement
	CurrentVelocity			= GetVelocity();
	CurrentSpeed			= CurrentVelocity.Size();
	CurrentSpeedSq			= CurrentSpeed * CurrentSpeed;
	CurrentVelocityDir		= CurrentSpeed < SMALL_NUMBER ? FVector::ZeroVector : CurrentVelocity / CurrentSpeed;
	CurrentVelocityXY.X		= CurrentVelocity.X;
	CurrentVelocityXY.Y		= CurrentVelocity.Y;
	CurrentSpeedXY			= CurrentVelocityXY.Size();
	CurrentSpeedXYSq		= CurrentSpeedXY * CurrentSpeedXY;
	CurrentVelocityDirXY	= CurrentSpeedXY < SMALL_NUMBER ? FVector::ZeroVector : CurrentVelocityXY / CurrentSpeedXY;
	float Last_VelocityZ	= CurrentVelocityZ.Z;
	CurrentVelocityZ.Z		= CurrentVelocity.Z;

	// Check JumpMovementState
	{
		const EMovementMode Mode = GetCharacterMovement()->MovementMode;

		// Grounded -> Up (Jumping)
		if (CurrentJumpMovementState == ECsCharacterJumpMovementState::Grounded)
		{
			if (Mode == EMovementMode::MOVE_Falling &&
				CurrentVelocityZ.Z > 0.0f)
			{
				CurrentJumpMovementState = ECsCharacterJumpMovementState::Up;

				OnChange_CurrentJumpMovementState_Event.Broadcast(ECsCharacterJumpMovementState::Grounded, ECsCharacterJumpMovementState::Up);
#if WITH_EDITOR
				OnChange_CurrentJumpMovementState_ScriptEvent.Broadcast(ECsCharacterJumpMovementState::Grounded, ECsCharacterJumpMovementState::Up);
#endif // #if WITH_EDITOR
			}
		}
		// Up (Jumping) -> Down (Falling)
		else
		if (CurrentJumpMovementState == ECsCharacterJumpMovementState::Up)
		{
			if (Mode == EMovementMode::MOVE_Falling &&
				(Last_VelocityZ >= 0.0f && CurrentVelocityZ.Z < 0.0f))
			{
				// TimeTillGrounded
				CurrentJumpMovementState = ECsCharacterJumpMovementState::Down;

				OnChange_CurrentJumpMovementState_Event.Broadcast(ECsCharacterJumpMovementState::Up, ECsCharacterJumpMovementState::Down);
#if WITH_EDITOR
				OnChange_CurrentJumpMovementState_ScriptEvent.Broadcast(ECsCharacterJumpMovementState::Up, ECsCharacterJumpMovementState::Down);
#endif // #if WITH_EDITOR
			}
		}
		// Down (Falling) -> Grounded
		else
		if (CurrentJumpMovementState == ECsCharacterJumpMovementState::Down)
		{
			if (Mode == EMovementMode::MOVE_Walking)
			{
				CurrentJumpMovementState = ECsCharacterJumpMovementState::Grounded;

				OnChange_CurrentJumpMovementState_Event.Broadcast(ECsCharacterJumpMovementState::Down, ECsCharacterJumpMovementState::Grounded);
#if WITH_EDITOR
				OnChange_CurrentJumpMovementState_ScriptEvent.Broadcast(ECsCharacterJumpMovementState::Down, ECsCharacterJumpMovementState::Grounded);
#endif // #if WITH_EDITOR
				JumpingFallingInfo.Reset();
			}
		}

		if (Mode == EMovementMode::MOVE_Walking)
		{
			CurrentJumpMovementState = ECsCharacterJumpMovementState::Grounded;

			JumpingFallingInfo.Reset();
		}
	}

	CurrentSpeedZ			= CurrentVelocityZ.Size();
	CurrentSpeedZSq			= CurrentSpeedZ * CurrentSpeedZ;
	CurrentVelocityDirZ		= CurrentSpeedZ < SMALL_NUMBER ? FVector::ZeroVector : CurrentVelocityZ / CurrentSpeedZ;
	
	FRotator Rotation = CurrentVelocityDir.Rotation();

	FRotationMatrix Matrix = FRotationMatrix(Rotation);
	CurrentVelocityRight = Matrix.GetScaledAxis(EAxis::Y);
	
	Rotation = CurrentVelocityDirXY.Rotation();

	Matrix = FRotationMatrix(Rotation);
	CurrentVelocityRightXY = Matrix.GetScaledAxis(EAxis::Y);

	// Velocity from Capsule
	CurrentCapsuleVelocity		= GetCapsuleComponent()->GetComponentVelocity();
	CurrentCapsuleSpeed			= CurrentCapsuleVelocity.Size();
	CurrentCapsuleSpeedSq		= CurrentCapsuleSpeed * CurrentCapsuleSpeed;
	CurrentCapsuleVelocityDir	= CurrentCapsuleSpeed < SMALL_NUMBER ? FVector::ZeroVector : CurrentCapsuleVelocity / CurrentCapsuleSpeed;
	CurrentCapsuleVelocityXY.X	= CurrentCapsuleVelocity.X;
	CurrentCapsuleVelocityXY.Y	= CurrentCapsuleVelocity.Y;
	CurrentCapsuleSpeedXY		= CurrentCapsuleVelocityXY.Size();
	CurrentCapsuleSpeedXYSq		= CurrentCapsuleSpeedXY * CurrentCapsuleSpeedXY;
	CurrentCapsuleVelocityDirXY = CurrentCapsuleSpeedXY < SMALL_NUMBER ? FVector::ZeroVector : CurrentCapsuleVelocityXY / CurrentCapsuleSpeedXY;
	CurrentCapsuleVelocityZ.Z	= CurrentCapsuleVelocity.Z;
	CurrentCapsuleSpeedZ		= CurrentCapsuleVelocityZ.Size();
	CurrentCapsuleSpeedZSq		= CurrentCapsuleSpeedZ * CurrentCapsuleSpeedZ;
	CurrentCapsuleVelocityDirZ	= CurrentCapsuleSpeedZ < SMALL_NUMBER ? FVector::ZeroVector : CurrentCapsuleVelocityZ / CurrentCapsuleVelocityZ;
	
	Rotation = CurrentCapsuleVelocityDir.Rotation();

	Matrix = FRotationMatrix(Rotation);
	CurrentCapsuleVelocityRight = Matrix.GetScaledAxis(EAxis::Y);

	Rotation = CurrentCapsuleVelocityDirXY.Rotation();

	Matrix = FRotationMatrix(Rotation);
	CurrentCapsuleVelocityRightXY = Matrix.GetScaledAxis(EAxis::Y);
}

FVector ACsPawn::GetFeetLocation() const
{
	return GetActorLocation() - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}

void ACsPawn::TraceToGroundWhileJumping()
{
	ACsManager_Trace* Manager_Trace = ACsManager_Trace::Get(GetWorld());

	FCsTraceRequest* Request = Manager_Trace->AllocateRequest();

	Request->Caller	  = this;
	Request->CallerId = UniqueObjectId;
	Request->OnResponse_Event.AddUObject(this, &ACsPawn::Async_TraceToGroundWhileJumping_Response);


	Request->Start = CurrentFeetLocation;
	static const float RANGE = 3000.0f;
	Request->End = Request->Start + RANGE * CurrentVelocityDirZ;
	Request->bAsync = true;
	Request->Type = ECsTraceType::Line;
	Request->Method = ECsTraceMethod::Multi;
	Request->Query = ECsTraceQuery::ObjectType;

	Request->ObjectParams.AddObjectTypesToQuery(ECC_WorldStatic);
	Request->ObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	Request->Params.AddIgnoredActor(this);

	Request->ReplacePending = true;
	Request->PendingId = TraceToGroundWhileJumpingInfo.RequestId;

	Manager_Trace->Trace(Request);
}

void ACsPawn::Async_TraceToGroundWhileJumping_Response(const uint8 &RequestId, FCsTraceResponse* Response)
{
	TraceToGroundWhileJumpingInfo.RequestId = CS_INVALID_TRACE_REQUEST_ID;

	if (!Response->bResult)
		return;

	float Distance = MAX_FLT;

	for (FHitResult& Hit : Response->OutHits)
	{
		UPrimitiveComponent* Component = Hit.GetComponent();

		const FVector Location = Component->GetComponentLocation();

		const float NewDistance = (Location - CurrentFeetLocation).Size();

		if (NewDistance < Distance)
			Distance = NewDistance;
	}

	JumpingFallingInfo.DistanceToGround = Distance;

	// Calculate TimeTillGrounded
	// - Vf = Sqrt(Vo^2 + 2a(Xf - Xo))
	const float& Velocity0 = CurrentVelocityZ.Z;
	static const float GRAVITY = -980.0f;
	const float Velocity1 = -1.0f * FMath::Sqrt((Velocity0*Velocity0) + 2.0f * GRAVITY * JumpingFallingInfo.DistanceToGround);
	// - (Vf - Vo)/a = t
	JumpingFallingInfo.TimeTillGrounded = (Velocity1 - Velocity0) / GRAVITY;
}

#pragma endregion Movement

// Data
#pragma region

UCsDataMapping* ACsPawn::GetDataMapping()
{
	return UCsLibrary_Common::GetDataMapping(GetWorld());
}

UCsData_Character* ACsPawn::GetMyData_Character()
{
	return MyData_Character.IsValid() ? MyData_Character.Get() : nullptr;
}

UCsData_CharacterMeshSkin* ACsPawn::GetMyData_CharacterMeshSkin()
{
	return MyData_CharacterMeshSkin.IsValid() ? MyData_CharacterMeshSkin.Get() : nullptr;
}

UCsData_CharacterMaterialSkin* ACsPawn::GetMyData_CharacterMaterialSkin()
{
	return MyData_CharacterMaterialSkin.IsValid() ? MyData_CharacterMaterialSkin.Get() : nullptr;
}

void ACsPawn::SetDatas(){}
void ACsPawn::ApplyData_Character(){}
void ACsPawn::OnRespawn_ApplyData_Character(){}

#pragma endregion Data

// Weapons
#pragma region

void ACsPawn::OnChange_CurrentWeaponSlot(const FECsWeaponSlot &Slot)
{
	ACsPlayerStateBase* MyPlayerState = GetPlayerState<ACsPlayerStateBase>();

	OnChange_CurrentWeaponSlot_Event.Broadcast(MyPlayerState->UniqueMappingId, LastWeaponSlot, CurrentWeaponSlot);
#if WITH_EDITOR
	OnChange_CurrentWeaponSlot_ScriptEvent.Broadcast(MyPlayerState->UniqueMappingId, LastWeaponSlot, CurrentWeaponSlot);
#endif // #if WITH_EDITOR
}

ACsWeapon* ACsPawn::GetWeapon(const FECsWeaponSlot &Slot)
{
	return Weapons[Slot.Value];
}

ACsWeapon* ACsPawn::GetCurrentWeapon()
{
	return GetWeapon(CurrentWeaponSlot);
}

UCsData_Weapon* ACsPawn::GetData_Weapon(const FECsWeaponSlot &Slot)
{
	return Data_Weapons[Slot.Value].IsValid() ? Data_Weapons[Slot.Value].Get() : nullptr;
}

UCsData_Weapon* ACsPawn::GetCurrentData_Weapon()
{
	return GetData_Weapon(CurrentWeaponSlot);
}

UCsData_WeaponMaterialSkin* ACsPawn::GetData_WeaponMaterialSkin(const FECsWeaponSlot &Slot)
{
	return Data_WeaponMaterialSkins[Slot.Value].IsValid() ? Data_WeaponMaterialSkins[Slot.Value].Get() : nullptr;
}

UCsData_WeaponMaterialSkin* ACsPawn::GetCurrentData_WeaponMaterialSkin()
{
	return GetData_WeaponMaterialSkin(CurrentWeaponSlot);
}

void ACsPawn::ApplyData_Weapon(){}
void ACsPawn::OnRespawn_Setup_Weapon(){}

#pragma endregion Weapons

// Sense
#pragma region

void ACsPawn::ApplySenseData()
{
	UCsData_Character* Data_Character = GetMyData_Character();
	FCsSenseData_DEPRECATED* OtherData			  = Data_Character->GetSenseData();

	// Radius
	if (!SenseData.bOverride_Radius)
	{
		SenseData.Radius = OtherData->Radius;
		SenseData.RadiusSq = OtherData->RadiusSq;
	}

	Manager_Sense->bRadius  = SenseData.bOverride_Radius || OtherData->bRadius;
	Manager_Sense->Radius   = SenseData.Radius;
	Manager_Sense->RadiusSq = SenseData.RadiusSq;
	// Angle / Dot
	if (!SenseData.bOverride_Angle)
	{
		SenseData.Angle = OtherData->Angle;
		SenseData.Radians = OtherData->Radians;
		SenseData.Dot = OtherData->Dot;
	}

	Manager_Sense->ViewMinAngle	  = SenseData.Angle;
	Manager_Sense->ViewMinRadians = SenseData.Radians;
	Manager_Sense->ViewMinDot	  = SenseData.Dot;
	// Trace Intervals
	if (!SenseData.bOverride_TraceIntervals)
	{
		TArray<FECsSenseActorType> Keys;
		SenseData.TraceIntervals.GetKeys(Keys);

		for (const FECsSenseActorType& Key : Keys)
		{
			SenseData.TraceIntervals[Key] = OtherData->TraceIntervals[Key];
		}
	}

	TArray<FECsSenseActorType> Keys;
	SenseData.TraceIntervals.GetKeys(Keys);

	for (const FECsSenseActorType& Key : Keys)
	{
		Manager_Sense->TraceToActorIntervals[Key] = SenseData.TraceIntervals[Key];
	}
}

#pragma endregion Sense

// Managers
#pragma region

ACsManager_Inventory* ACsPawn::GetMyManager_Inventory() { return nullptr; }

#pragma endregion Managers

// Play In Preview Toggles
#pragma region

#if WITH_EDITORONLY_DATA

void ACsPawn::SetupInGameSimulation(){}

#endif // #if WITH_EDITORONLY_DATA

#pragma endregion Play In Preview Toggles

#if WITH_EDITOR

void ACsPawn::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// SenseData.Radius, SenseData.Angle
	CS_PECP_FCS_SENSE_DATA_OVERRIDE(PropertyName, SenseData)

	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR