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

#include "UI/State/CsHealthBarComponent.h"

#include "Game/CsGameInstance.h"
#include "Player/CsPlayerStateBase.h"
#include "Weapon/CsWeapon.h"

// Cache
#pragma region

namespace ECsPawnCached
{
	namespace Name
	{
		// Functions
		const FName HandleRespawnTimer_Internal = FName("ACsPawn::HandleRespawnTimer_Internal");
	};

	namespace Str
	{
		// Functions
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
	UniqueObjectId				  = GameInstance->GetUniqueObjectId();

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	for (int32 I = 0; I < MaxWeaponCount; I++)
	{
		Weapons[I] = GetWorld()->SpawnActor<ACsWeapon>(WeaponClass, SpawnInfo);
		Weapons[I]->SetMyPawn(this);
	}
}

void ACsPawn::Destroyed()
{
	Super::Destroyed();

	for (int32 I = 0; I < MaxWeaponCount; I++)
	{
		if (!Weapons[I] && !Weapons[I]->IsPendingKill())
			Weapons[I]->Destroy();
	}
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

bool ACsPawn::IsOnBoardCompleted_Game()
{
	ACsPlayerStateBase* MyPlayerState = Cast<ACsPlayerStateBase>(PlayerState);

	if (!MyPlayerState)
		return false;
	return MyPlayerState->IsOnBoardCompleted_Game();
}

void ACsPawn::OnTick_HandleSetup() {}

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

void ACsPawn::Die(){}

	// Spawn
#pragma region

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
	Payload->Type			= (uint8)ECsPawnRoutine::HandleRespawnTimer_Internal;
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
	const TCsPawnRoutine RoutineType = (TCsPawnRoutine)Type;

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
	const TCsPawnRoutine RoutineType = (TCsPawnRoutine)Type;

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

// Managers
#pragma region

ACsManager_Inventory* ACsPawn::GetMyManager_Inventory() { return nullptr; }

#pragma endregion Managers