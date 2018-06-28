// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Pawn/CsPawn.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "Coroutine/CsCoroutineScheduler.h"

// Data
#include "Data/CsDataMapping.h"
#include "Data/CsData_Character.h"
#include "Data/CsData_CharacterMeshSkin.h"
#include "Data/CsData_CharacterMaterialSkin.h"
// Managers
#include "Managers/Inventory/CsManager_Inventory.h"
#include "Managers/Sense/CsManager_Sense.h"
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

EMCsPawnRoutine* EMCsPawnRoutine::Instance;

EMCsPawnRoutine& EMCsPawnRoutine::Get()
{
	if (!Instance)
		Instance = new EMCsPawnRoutine();
	return *Instance;
}

namespace ECsPawnRoutine
{
	CSCORE_API const FECsPawnRoutine CheckLinkedToPlayerState_Internal = EMCsPawnRoutine::Get().Create(TEXT("CheckLinkedToPlayerState_Internal"));
	CSCORE_API const FECsPawnRoutine HandleRespawnTimer_Internal = EMCsPawnRoutine::Get().Create(TEXT("HandleRespawnTimer_Internal"));
}

#pragma endregion Enums

// Cache
#pragma region

namespace ECsPawnCached
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

	// TODO: Test placing actors in the level and see how this affects spawning weapons
	if (UCsCommon::IsPlayInEditor(GetWorld()) || UCsCommon::IsPlayInEditorPreview(GetWorld()))
		return;

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
	// Check PlayerState
	CheckLinkedToPlayerState();
}

void ACsPawn::Destroyed()
{
	Super::Destroyed();

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

	if (!IsPendingKill())
	{
		IsPlacedInWorld = GetWorld()->bStartup;
	}
}

void ACsPawn::PreTick(const float &DeltaSeconds)
{
	RecordRoot();
	RecordVelocityAndSpeed();
}

void ACsPawn::PostTick(const float &DeltaSeconds){}

void ACsPawn::OnTickActor_HandleCVars(const float &DeltaSeconds) {};

// Setup
#pragma region

void ACsPawn::CheckLinkedToPlayerState()
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsPawn::CheckLinkedToPlayerState_Internal;
	Payload->Actor			= this;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckActor;
	Payload->Add			= &ACsPawn::AddRoutine;
	Payload->Remove			= &ACsPawn::RemoveRoutine;
	Payload->Type			= ECsPawnRoutine::CheckLinkedToPlayerState_Internal.Value;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsPawnCached::Name::CheckLinkedToPlayerState_Internal;
	Payload->NameAsString	= ECsPawnCached::Str::CheckLinkedToPlayerState_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(ACsPawn, CheckLinkedToPlayerState_Internal)
{
	ACsPawn* p			   = r->GetActor<ACsPawn>();
	ACsPlayerStateBase* ps = Cast<ACsPlayerStateBase>(p->PlayerState);

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_WAIT_UNTIL(r, ps);

	ps->LinkedPawn = p;
	ps->OnLinkedPawnSet_Event.Broadcast(ps);

	CS_COROUTINE_END(r);
}

bool ACsPawn::IsOnBoardCompleted_Game()
{
	ACsPlayerStateBase* MyPlayerState = Cast<ACsPlayerStateBase>(PlayerState);

	if (!MyPlayerState)
		return false;
	return MyPlayerState->IsOnBoardCompleted_Game();
}

void ACsPawn::OnTick_HandleSetup() {}

#pragma endregion Setup

// State
#pragma region

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
	ACsPlayerStateBase* MyPlayerState = Cast<ACsPlayerStateBase>(PlayerState);

	OnApplyDamage_Result_Event.Broadcast(MyPlayerState->UniqueMappingId, Result);
#if WITH_EDITOR
	OnApplyDamage_Result_ScriptEvent.Broadcast(MyPlayerState->UniqueMappingId, *Result);
#endif // #if WITH_EDITOR
}

void ACsPawn::Die()
{
	bSpawnedAndActive = false;
}

	// Spawn
#pragma region

void ACsPawn::OnFirstSpawn(){}

void ACsPawn::HandleRespawnTimer()
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsPawn::HandleRespawnTimer_Internal;
	Payload->Actor			= this;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckActor;
	Payload->Add			= &ACsPawn::AddRoutine;
	Payload->Remove			= &ACsPawn::RemoveRoutine;
	Payload->Type			= ECsPawnRoutine::HandleRespawnTimer_Internal.Value;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsPawnCached::Name::HandleRespawnTimer_Internal;
	Payload->NameAsString	= ECsPawnCached::Str::HandleRespawnTimer_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(ACsPawn, HandleRespawnTimer_Internal)
{
	ACsPawn* p				 = r->GetActor<ACsPawn>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();
	UWorld* w				 = p->GetWorld();
	ACsPlayerStateBase* ps	 = Cast<ACsPlayerStateBase>(p->PlayerState);

	ACsData_Character* Data_Character = p->GetMyData_Character();

	const float CurrentTime = w->GetTimeSeconds();
	const float& StartTime  = r->startTime;
	const float RespawnTime = Data_Character->GetRespawnTime();

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime >= RespawnTime);

	p->OnHandleRespawnTimerFinished_Event.Broadcast(ps->UniqueMappingId);

	CS_COROUTINE_END(r);
}

void ACsPawn::OnHandleRespawnTimerFinished(const uint8 &MappingId) {}

#pragma endregion Spawn

#pragma endregion State

// Routines
#pragma region

/*static*/ void ACsPawn::AddRoutine(UObject* InPawn, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsPawn>(InPawn)->AddRoutine_Internal(Routine, Type);
}

bool ACsPawn::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const FECsPawnRoutine& RoutineType = EMCsPawnRoutine::Get()[Type];

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

/*static*/ void ACsPawn::RemoveRoutine(UObject* InPawn, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsPawn>(InPawn)->RemoveRoutine_Internal(Routine, Type);
}

bool ACsPawn::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const FECsPawnRoutine& RoutineType = EMCsPawnRoutine::Get()[Type];

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

TEnumAsByte<ECsViewType::Type> ACsPawn::GetCurrentViewType()
{
	return CurrentViewType;
}

void ACsPawn::RecordView() {}

#pragma endregion View

// Body / Root
#pragma region

void ACsPawn::RecordRoot()
{
	CurrentRootRotation = GetActorRotation();
	CurrentRootLocation = GetActorLocation();
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
	// TODO: Potentially optimize slightly by doing normal calculation manually

	// Velocity from CharacterMovement
	CurrentVelocity			= GetVelocity();
	CurrentVelocityDir		= CurrentVelocity.GetSafeNormal();
	CurrentVelocityXY.X		= CurrentVelocity.X;
	CurrentVelocityXY.Y		= CurrentVelocity.Y;
	CurrentVelocityDirXY	= CurrentVelocityXY.GetSafeNormal();
	CurrentVelocityZ.Z		= CurrentVelocity.Z;
	CurrentVelocityDirZ		= CurrentVelocityZ.GetSafeNormal();
	CurrentSpeed			= CurrentVelocity.Size();
	CurrentSpeedXY			= CurrentVelocityXY.Size();
	CurrentSpeedZ			= CurrentVelocityZ.Size();

	FRotator Rotation = CurrentVelocityDir.Rotation();

	FRotationMatrix Matrix = FRotationMatrix(Rotation);
	CurrentVelocityRight = Matrix.GetScaledAxis(EAxis::Y);
	
	Rotation = CurrentVelocityDirXY.Rotation();

	Matrix = FRotationMatrix(Rotation);
	CurrentVelocityRightXY = Matrix.GetScaledAxis(EAxis::Y);

	// Velocity from Capsule
	CurrentCapsuleVelocity		= GetCapsuleComponent()->GetComponentVelocity();
	CurrentCapsuleVelocityDir	= CurrentCapsuleVelocity.GetSafeNormal();
	CurrentCapsuleVelocityXY.X	= CurrentCapsuleVelocity.X;
	CurrentCapsuleVelocityXY.Y	= CurrentCapsuleVelocity.Y;
	CurrentCapsuleVelocityDirXY = CurrentCapsuleVelocityXY.GetSafeNormal();
	CurrentCapsuleVelocityZ.Z	= CurrentCapsuleVelocity.Z;
	CurrentCapsuleVelocityDirZ	= CurrentCapsuleVelocityZ.GetSafeNormal();
	CurrentCapsuleSpeed			= CurrentCapsuleVelocity.Size();
	CurrentCapsuleSpeedXY		= CurrentCapsuleVelocityXY.Size();
	CurrentCapsuleSpeedZ		= CurrentCapsuleVelocityZ.Size();

	Rotation = CurrentCapsuleVelocityDir.Rotation();

	Matrix = FRotationMatrix(Rotation);
	CurrentCapsuleVelocityRight = Matrix.GetScaledAxis(EAxis::Y);

	Rotation = CurrentCapsuleVelocityDirXY.Rotation();

	Matrix = FRotationMatrix(Rotation);
	CurrentCapsuleVelocityRightXY = Matrix.GetScaledAxis(EAxis::Y);
}

#pragma endregion Movement

// Data
#pragma region

ACsDataMapping* ACsPawn::GetDataMapping()
{
	return UCsCommon::GetDataMapping(GetWorld());
}

ACsData_Character* ACsPawn::GetMyData_Character()
{
	return MyData_Character.IsValid() ? MyData_Character.Get() : nullptr;
}

ACsData_CharacterMeshSkin* ACsPawn::GetMyData_CharacterMeshSkin()
{
	return MyData_CharacterMeshSkin.IsValid() ? MyData_CharacterMeshSkin.Get() : nullptr;
}

ACsData_CharacterMaterialSkin* ACsPawn::GetMyData_CharacterMaterialSkin()
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
	ACsPlayerStateBase* MyPlayerState = Cast<ACsPlayerStateBase>(PlayerState);

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

ACsData_Weapon* ACsPawn::GetData_Weapon(const FECsWeaponSlot &Slot)
{
	return Data_Weapons[Slot.Value].IsValid() ? Data_Weapons[Slot.Value].Get() : nullptr;
}

ACsData_Weapon* ACsPawn::GetCurrentData_Weapon()
{
	return GetData_Weapon(CurrentWeaponSlot);
}

ACsData_WeaponMaterialSkin* ACsPawn::GetData_WeaponMaterialSkin(const FECsWeaponSlot &Slot)
{
	return Data_WeaponMaterialSkins[Slot.Value].IsValid() ? Data_WeaponMaterialSkins[Slot.Value].Get() : nullptr;
}

ACsData_WeaponMaterialSkin* ACsPawn::GetCurrentData_WeaponMaterialSkin()
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
	ACsData_Character* Data_Character = GetMyData_Character();
	FCsSenseData* OtherData			  = Data_Character->GetSenseData();

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

#if WITH_EDITOR

void ACsPawn::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// SenseData.Radius, SenseData.Angle
	CS_PECP_FCS_SENSE_DATA_OVERRIDE(PropertyName, SenseData)

	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR