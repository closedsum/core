// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/Pawn/CsAIPawn.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Coroutine/CsCoroutineScheduler.h"

#include "AI/CsAIController.h"
#include "AI/CsAIPlayerState.h"

// Data
#include "Data/CsData_Character.h"
// Managers
#include "Managers/Trace/CsManager_Trace.h"
// Game
#include "Game/CsGameState.h"
// Player
#include "Player/CsPlayerState.h"
#include "Player/CsPlayerPawn.h"
// Weapon
#include "Weapon/CsWeapon.h"
// UI
//#include "Components/CsWidgetComponent.h"
//#include "UI/Simple/CsWidget_ProgressBar.h"

ACsAIPawn::ACsAIPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationYaw = true;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI	  = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACsAIController::StaticClass();
}

void ACsAIPawn::Init(const int32 &Index, const FECsAIType &InType)
{
	PoolIndex	= Index;
	Type		= InType;

	Cache.Set(Index, this);
}

void ACsAIPawn::OnCreatePool()
{
	SetActorHiddenInGame(true);
}

void ACsAIPawn::OnPostCreatePool(){}

void ACsAIPawn::Allocate(const int32 &ActiveIndex, FCsAIPawnPayload* Payload)
{
	Cache.Init(ActiveIndex, Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(GetWorld()));

	Allocate_Internal(Payload);
}

void ACsAIPawn::Allocate_Internal(FCsAIPawnPayload* Payload)
{
	if (Payload->TeleportLocation || Payload->TeleportRotation)
	{
		SpawnLocation = Payload->TeleportLocation ? Payload->Location : GetActorLocation();
		SpawnRotation = Payload->TeleportRotation ? Payload->Rotation : GetActorRotation();

		TeleportTo(SpawnLocation, SpawnRotation, false, false);
	}
	SetActorHiddenInGame(false);
}

void ACsAIPawn::DeAllocate()
{
	Cache.Reset();

	SetActorHiddenInGame(true);
}

void ACsAIPawn::OnTick_HandleCVars(const float &DeltaSeconds){}

// View
#pragma region

void ACsAIPawn::PerformViewTrace_Response(const uint8 &RequestId, FCsTraceResponse* Response)
{
	Super::PerformViewTrace_Response(RequestId, Response);
	
	if (CsCVarDrawAIViewTraceHitLocation->GetInt() == CS_CVAR_DRAW)
	{
		DrawDebugSphere(GetWorld(), ViewTraceInfo.HitLocation, 32.0f, 16, FColor::Green, false, GetWorld()->GetDeltaSeconds() + 0.0005f, 0, 1.0f);
	}
}

#pragma endregion View

// Behavior Tree
#pragma region

void ACsAIPawn::SetTargetActor(AActor* Target)
{
	MyTargetActor = Target;
}

void ACsAIPawn::SetTargetLocation(const FVector &Target)
{
	MyTargetLocation = Target;
}

	// LookAt
#pragma region

FRotator ACsAIPawn::GetFinalLookAtRotation(AActor* Target, const FName &Bone) { return FRotator(CurrentAimPitch, CurrentAimYaw, 0.0f); }
FRotator ACsAIPawn::GetFinalLookAtRotation(const FVector &Target){ return FRotator(CurrentAimPitch, CurrentAimYaw, 0.0f); }
void ACsAIPawn::LookAtLocation(const FVector &Target, const float &LookRate, const float &LookTime){}
void ACsAIPawn::LookAtActor(AActor* Target, const FName &Bone, const float &LookRate, const float &LookTime){}
void ACsAIPawn::StopLookAt(const float &BlendOutRate){}

#pragma endregion LookAt

	// AimAt
#pragma region

void ACsAIPawn::AimAtLocation(const FVector &Target){}
void ACsAIPawn::AimAtActor(AActor* Target, const FName &Bone){}
void ACsAIPawn::StopAimAt(){}

#pragma endregion AimAt

	// Shoot
#pragma region

void ACsAIPawn::StartShoot(){}
void ACsAIPawn::StartShoot(const int32 &Count){}
void ACsAIPawn::StartShoot(const float &Duration){}

void ACsAIPawn::StartShootForCount(const int32 &Count)
{
	StartShoot(Count);
}

void ACsAIPawn::StartShootForDuration(const float &Duration)
{
	StartShoot(Duration);
}

void ACsAIPawn::StopShoot(){}

bool ACsAIPawn::IsShooting()
{
	ACsWeapon* CurrentWeapon = GetCurrentWeapon();

	const int32& Count = EMCsWeaponFireMode::Get().Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(I);

		if (CurrentWeapon->IsFirePressed[FireMode])
			return true;
	}
	return false;
}

#pragma endregion Shoot

#pragma endregion Behavior Tree

// State
#pragma region

void ACsAIPawn::OnChange_Health(const float &Value)
{
	ACsAIPlayerState* MyPlayerState = Cast<ACsAIPlayerState>(PlayerState);

	OnChange_Health_Event.Broadcast(MyPlayerState->UniqueMappingId, Health, MaxHealth);
#if WITH_EDITOR
	OnChange_Health_ScriptEvent.Broadcast(MyPlayerState->UniqueMappingId, Health, MaxHealth);
#endif // #if WITH_EDITOR
}

#pragma endregion State