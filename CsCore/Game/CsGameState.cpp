// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsGameState.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Coroutine/CsCoroutineScheduler.h"
#include "CsLastTickActor.h"
// Managers
#include "Managers/CsManager_Loading.h"
#include "Managers/Input/CsManager_Input.h"

#include "Game/CsGameInstance.h"
#include "Javascript/CsJavascriptEntryPoint.h"
#include "Data/CsDataMapping.h"

#include "Player/CsPlayerController.h"
#include "Player/CsPlayerState.h"
#include "Player/CsPlayerPawn.h"

// UI
#include "UI/CsUI.h"
#include "UI/CsWidget_Fullscreen.h"

ACsGameState::ACsGameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	JavascriptEntryPointClass = ACsJavascriptEntryPoint::StaticClass();
}

void ACsGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	OnTick_HandleBroadcastingPlayerStateFullyReplicatedAndLoaded();
}

void ACsGameState::PostActorCreated()
{
	Super::PostActorCreated();

	if (GetWorld()->WorldType == EWorldType::Editor ||
		GetWorld()->WorldType == EWorldType::EditorPreview)
		return;

	// Coroutine Scheduler
	UCsCoroutineScheduler::Get()->MyOwner = this;
	OnTick_Event.AddUObject(UCsCoroutineScheduler::Get(), &UCsCoroutineScheduler::OnTick_Update);

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	// LastTickActor
	LastTickActor = GetWorld()->SpawnActor<ACsLastTickActor>(ACsLastTickActor::StaticClass(), FTransform::Identity, SpawnInfo);
	LastTickActor->Role = ROLE_None;
	GetWorld()->RemoveNetworkActor(LastTickActor);
}

void ACsGameState::SeamlessTravelTransitionCheckpoint(bool bToTransitionMap)
{
	Super::SeamlessTravelTransitionCheckpoint(bToTransitionMap);

	//UCsCoroutineScheduler::Get()->EndAll();
	//UCsCoroutineScheduler::Get()->CalcCamera_EndAll();
	UCsCoroutineScheduler::Get()->MyOwner = nullptr;

	if (LastTickActor && !LastTickActor->IsPendingKill())
	{
		LastTickActor->Destroy(true);
		LastTickActor = nullptr;
	}

#if WITH_EDITOR
	if (JavascriptEntryPoint && !JavascriptEntryPoint->IsPendingKill())
	{
		JavascriptEntryPoint->Destroy(true);
		JavascriptEntryPoint = nullptr;
	}
#endif // #if WITH_EDITOR
}

// Routines
#pragma region

/*static*/ void ACsGameState::AddRoutine(UObject* InGameState, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsGameState>(InGameState)->AddRoutine_Internal(Routine, Type);
}

bool ACsGameState::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const TCsGameStateRoutine RoutineType = (TCsGameStateRoutine)Type;

	// OnBoard_Internal
	if (RoutineType == ECsGameStateRoutine::OnBoard_Internal)
	{
		OnBoard_Internal_Routine = Routine;
		return true;
	}
	return false;
}

/*static*/ void ACsGameState::RemoveRoutine(UObject* InGameState, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsGameState>(InGameState)->RemoveRoutine_Internal(Routine, Type);
}

bool ACsGameState::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const TCsGameStateRoutine RoutineType = (TCsGameStateRoutine)Type;

	// OnBoard_Internal
	if (RoutineType == ECsGameStateRoutine::OnBoard_Internal)
	{
		check(OnBoard_Internal_Routine == Routine);
		OnBoard_Internal_Routine = nullptr;
		return true;
	}
	return false;
}

#pragma endregion Routines

// OnBoard
#pragma region

void ACsGameState::OnBoard()
{
	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	CsCoroutine Function		  = &ACsGameState::OnBoard_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckActor;
	CsAddRoutine Add			  = &ACsGameState::AddRoutine;
	CsRemoveRoutine Remove		  = &ACsGameState::RemoveRoutine;
	const uint8 Type			  = (uint8)ECsGameStateRoutine::OnBoard_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Schedule, Function, Stop, this, Add, Remove, Type, true, false);

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(ACsGameState, OnBoard_Internal)
{
	ACsGameState* gs		 = Cast<ACsGameState>(r->GetActor());
	UCsGameInstance* gi		 = Cast<UCsGameInstance>(gs->GetGameInstance());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = gs->GetWorld();

	ACsPlayerController* pc = UCsCommon::GetLocalPlayerController<ACsPlayerController>(w);
	ACsUI* hud				= pc ? Cast<ACsUI>(pc->MyHUD) : nullptr;

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_WAIT_UNTIL(r, gi->OnBoardState == ECsGameInstanceOnBoardState::Completed);

	gs->LoadCommonData();

	// Wait until Controller is VALID
	CS_COROUTINE_WAIT_UNTIL(r, pc);

	// Wait until HUD is VALID
	CS_COROUTINE_WAIT_UNTIL(r, hud);

	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::SetupHUD);

	gs->SetupHUD();

	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::LoadData);

	gs->LoadData();

	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::SetupScene);

	gs->SetupScene();

	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::SetupLastTickActor);

	gs->SetupLastTickActor();

#if WITH_EDITOR
	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::SetupJavascriptEntryPoint);

	gs->SetupJavascriptEntryPoint();

	CS_COROUTINE_WAIT_UNTIL(r, gs->JavascriptEntryPoint->HasCompletedSetup);

	gs->OnBoardState = ECsGameStateOnBoardState::Completed;
#else
	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::Completed);
#endif // #if WITH_EDITOR

	CS_COROUTINE_END(r);
}

void ACsGameState::LoadCommonData(){}
void ACsGameState::OnFinishedLoadCommonData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime){}
void ACsGameState::SetupHUD(){}
void ACsGameState::LoadData(){}
void ACsGameState::OnFinishedLoadData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime){}
void ACsGameState::SetupScene(){}

#pragma endregion OnBoard

// LastTickActor
#pragma region

void ACsGameState::SetupLastTickActor()
{
	SetupLastTickActor_BindEvents();

#if WITH_EDITOR
	OnBoardState = ECsGameStateOnBoardState::SetupJavascriptEntryPoint;
#else
	OnBoardState = ECsGameStateOnBoardState::Completed;
#endif // #if WITH_EDITOR
}

void ACsGameState::SetupLastTickActor_BindEvents() {}

#pragma endregion LastTickActor

// Javascript
#pragma region

#if WITH_EDITOR

void ACsGameState::SetupJavascriptEntryPoint()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	JavascriptEntryPoint = GetWorld()->SpawnActor<ACsJavascriptEntryPoint>(JavascriptEntryPointClass, SpawnInfo);
	JavascriptEntryPoint->Setup();
}

#endif // #if WITH_EDITOR

#pragma endregion Javascript

// Match State
#pragma region

float ACsGameState::GetElapsedGameTime()
{
	return GetWorld()->TimeSeconds - MatchInProgressStartTime;
}

uint64 ACsGameState::GetElapsedGameTimeMilliseconds()
{
	return UCsCommon::GetWorldTimeMilliseconds(GetWorld()) - MatchInProgressStartTimeMilliseconds;
}

#pragma endregion Match State

// Player State
#pragma region

void ACsGameState::AddPlayerState(class APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);

	if (Role < ROLE_Authority)
		return;

	ACsPlayerState* NewPlayerState = Cast<ACsPlayerState>(PlayerState);

	if (!NewPlayerState)
		return;

	NewPlayerState->UniqueMappingId = CurrentPlayerStateUniqueMappingId;

	PlayerStateMappings.Add(NewPlayerState->UniqueMappingId, NewPlayerState);

	TArray<uint8> MappingKeys;
	const int32 NumMappingKeys = PlayerStateMappings.GetKeys(MappingKeys);

	PlayerStateMappingRelationships.Add(NewPlayerState->UniqueMappingId);

	TArray<uint8> RelationshipKeys;
	const int32 NumRelationshipKeys = PlayerStateMappingRelationships.GetKeys(RelationshipKeys);

	// Sanity check
	check(NumMappingKeys == NumRelationshipKeys);

	for (int32 I = 0; I < NumMappingKeys; I++)
	{
		const uint8 Key = MappingKeys[I];

		// For a NEW entry, add ALL relationships
		if (Key == CurrentPlayerStateUniqueMappingId)
		{
			TArray<FCsPlayerStateMappingRelationship>* Relationships = PlayerStateMappingRelationships.Find(Key);

			for (int32 J = 0; J < NumMappingKeys; J++)
			{
				Relationships->AddDefaulted(1);

				FCsPlayerStateMappingRelationship& Relationship = (*Relationships)[J];
				Relationship.A = CurrentPlayerStateUniqueMappingId;
				Relationship.B = MappingKeys[J];
			}
		}
		// For EXISTING entry, just add Key to the relationship
		else
		{
			TArray<FCsPlayerStateMappingRelationship>* Relationships = PlayerStateMappingRelationships.Find(Key);
			Relationships->AddDefaulted(1);

			const uint8 Size = Relationships->Num();

			FCsPlayerStateMappingRelationship& Relationship = (*Relationships)[Size - 1];
			Relationship.A = Key;
			Relationship.B = CurrentPlayerStateUniqueMappingId;
		}
	}
	HasPlayerStateFullyReplicatedAndLoadedBroadcastFlags.Add(NewPlayerState->UniqueMappingId, false);

	CurrentPlayerStateUniqueMappingId++;
}

void ACsGameState::RemovePlayerState(class APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);
}

class ACsPlayerState* ACsGameState::GetPlayerState(const uint8 &MappingId)
{
	TWeakObjectPtr<ACsPlayerState>* PtrPlayerState = PlayerStateMappings.Find(MappingId);

	if (!PtrPlayerState)
		return nullptr;
	return (*PtrPlayerState).IsValid() ? (*PtrPlayerState).Get() : nullptr;
}

void ACsGameState::OnTick_HandleBroadcastingPlayerStateFullyReplicatedAndLoaded()
{
	TArray<uint8> RelationshipKeys;
	const int32 NumRelationshipKeys = PlayerStateMappingRelationships.GetKeys(RelationshipKeys);

	for (int32 I = 0; I < NumRelationshipKeys; I++)
	{
		const uint8 Key = RelationshipKeys[I];

		ACsPlayerState* PlayerState = GetPlayerState(Key);

		// Check if PlayerState is still VALID (i.e. Player could have Disconnected)
		if (!PlayerState)
			continue;

		TArray<FCsPlayerStateMappingRelationship>* Relationships = PlayerStateMappingRelationships.Find(Key);
		const int32 NumRelationships							 = Relationships->Num();

		bool ShouldBroadcast = true;

		for (int32 J = 0; J < NumRelationships; J++)
		{
			FCsPlayerStateMappingRelationship& Relationship = (*Relationships)[J];

			// If PlayerState is NOT VALID, Skip
			if (!GetPlayerState(Relationship.B))
				continue;

			ShouldBroadcast &= Relationship.HasBCompletedInitialReplicationAndLoadingForA;
		}

		bool* BroadcastFlag = HasPlayerStateFullyReplicatedAndLoadedBroadcastFlags.Find(Key);

		// If SHOULD Broadcast and Has NOT Broadcasted before, BROADCAST
		if (ShouldBroadcast && !(*BroadcastFlag))
		{
			*BroadcastFlag = true;

			PlayerState->MulticastSetIsOnBoardCompleted();

		}
		// If Should NOT Broadcast and HAS Broadcasted before, SET BroadcastFlag to FALSE

		// TODO: See if this is necessary
		/*
		if (!ShouldBroadcast && *BroadcastFlag)
		{
		*BroadcastFlag = false;

		PlayerState->MulticastUnSetIsOnBoardCompleted();
		}
		*/
	}
}

void ACsGameState::SetPlayerStateMappingRelationshipFlag(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	TArray<FCsPlayerStateMappingRelationship>* Relationships = PlayerStateMappingRelationships.Find(ClientMappingId);
	const int32 NumRelationships							 = Relationships->Num();

	for (int32 I = 0; I < NumRelationships; I++)
	{
		FCsPlayerStateMappingRelationship& Relationship = (*Relationships)[I];

		if (Relationship.B == MappingId)
		{
			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				ACsPlayerState* ClientPlayerState = GetPlayerState(ClientMappingId);
				ACsPlayerState* PlayerState		  = GetPlayerState(MappingId);

				const FString ClientName = ClientPlayerState ? ClientPlayerState->PlayerName : TEXT("INVALID");
				const FString OtherName  = PlayerState ? PlayerState->PlayerName : TEXT("INVALID");
				const FString Value		 = Relationship.HasBCompletedInitialReplicationAndLoadingForA ? TEXT("True") : TEXT("False");

				UE_LOG(LogCs, Log, TEXT("ACsGameState::SetPlayerStateMappingRelationshipFlag: Relationship: %s(%d) <-> %s(%d) from %s to True."), *ClientName, ClientMappingId, *OtherName, MappingId, *Value);
			}
			Relationship.HasBCompletedInitialReplicationAndLoadingForA = true;
			break;
		}
	}
}

#pragma endregion Player State