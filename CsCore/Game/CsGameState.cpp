// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsGameState.h"
#include "CsCore.h"
#include "CsCVars.h"

#include "Coroutine/CsCoroutineScheduler.h"
#include "CsLastTickActor.h"

#include "Game/CsGameInstance.h"

// Managers
#include "Managers/CsManager_Loading.h"
#include "Managers/Input/CsManager_Input.h"
#include "Managers/Runnable/CsManager_Runnable.h"
#include "Managers/WidgetActor/CsManager_WidgetActor.h"
#include "Managers/FX/CsManager_FX.h"
#include "Managers/Sound/CsManager_Sound.h"
#include "Managers/Projectile/CsManager_Projectile.h"
#include "Managers/Damage/CsManager_Damage.h"
#include "Managers/InteractiveActor/CsManager_InteractiveActor.h"
#include "Managers/Item/CsManager_Item.h"
#include "Managers/Inventory/CsManager_Inventory.h"
#include "Managers/Crafting/CsManager_Crafting.h"
#include "Managers/AI/CsManager_AI.h"
#include "Managers/Decals/CsManager_Decal.h"
#include "Managers/Trace/CsManager_Trace.h"
// Data
#include "Data/CsDataMapping.h"
// Player
#include "Player/CsPlayerController.h"
#include "Player/CsPlayerState.h"
#include "Player/CsPlayerPawn.h"
// A.I.
#include "AI/CsAIPlayerState.h"
// UI
#include "UI/CsUI.h"
#include "UI/CsWidget_Fullscreen.h"

#include "Javascript/CsJavascriptEntryPoint.h"

#if WITH_EDITOR
#include "Settings/LevelEditorPlaySettings.h"
#endif // #if WITH_EDITOR

// Cache
#pragma region

namespace ECsGameStateCachedName
{
	namespace Name
	{
		const FName OnBoard_Internal = FName("OnBoard_Internal");
	};
}

namespace ECsGameStateCachedString
{
	namespace Str
	{
		const FString OnBoard_Internal = TEXT("OnBoard_Internal");
		const FString DefaultPlayerProfileName = TEXT("Player0");
	};
}

#pragma endregion Cache

// Enums
#pragma region

#pragma endregion Enums

ACsGameState::ACsGameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CurrentPlayerStateUniqueMappingId = 0;
	CurrentAIPlayerStateUniqueMappingId = 0;

	JavascriptEntryPointClass = ACsJavascriptEntryPoint::StaticClass();

	NumberOfClients = 1;
}

void ACsGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//OnTick_HandleBroadcastingPlayerStateFullyReplicatedAndLoaded();
	//OnTick_HandleBroadcastingAIPlayerStateFullyReplicatedAndLoaded();
}

void ACsGameState::PostActorCreated()
{
	Super::PostActorCreated();

	if (GetWorld()->WorldType == EWorldType::Editor ||
		GetWorld()->WorldType == EWorldType::EditorPreview)
		return;

#if WITH_EDITOR
	FEditorDelegates::PrePIEEnded.Remove(OnPrePIEEndedDelegateHandle);
	OnPrePIEEndedDelegateHandle = FEditorDelegates::PrePIEEnded.AddUObject(this, &ACsGameState::OnPrePIEEnded);
#endif // #if WITH_EDITOR

	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
	GameInstance->LevelState	  = ECsLevelState::Loaded;
	GameInstance->CurrentGameFrame = 0;

	// Coroutine Scheduler
	UCsCoroutineScheduler::Get()->MyOwner = this;

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

	OnTick_Event.Clear();
	OnTick_ScriptEvent.Clear();

	// Manager WidgetActor
	if (Manager_WidgetActor && !Manager_WidgetActor->IsPendingKill())
	{
		Manager_WidgetActor->Destroy(true);
		Manager_WidgetActor = nullptr;

	}
	// Manager FX
	if (Manager_FX && !Manager_FX->IsPendingKill())
	{
		Manager_FX->Destroy(true);
		Manager_FX = nullptr;

	}
	// Manager Sound
	if (Manager_Sound && !Manager_Sound->IsPendingKill())
	{
		Manager_Sound->Destroy(true);
		Manager_Sound = nullptr;

	}
	// Manager Projectile
	if (Manager_Projectile && !Manager_Projectile->IsPendingKill())
	{
		Manager_Projectile->Destroy(true);
		Manager_Projectile = nullptr;

	}
	// Manager Damage
	if (Manager_Damage && !Manager_Damage->IsPendingKill())
	{
		Manager_Damage->Destroy(true);
		Manager_Damage = nullptr;

	}
	// Manager InteractiveActor
	if (Manager_InteractiveActor && !Manager_InteractiveActor->IsPendingKill())
	{
		Manager_InteractiveActor->Destroy(true);
		Manager_InteractiveActor = nullptr;

	}
	// Manager Item
	if (Manager_Item && !Manager_Item->IsPendingKill())
	{
		Manager_Item->Destroy(true);
		Manager_Item = nullptr;

	}
	// Manager Inventory
	if (Manager_Inventory && !Manager_Inventory->IsPendingKill())
	{
		Manager_Inventory->Destroy(true);
		Manager_Inventory = nullptr;

	}
	// Manager Crafting
	if (Manager_Crafting && !Manager_Crafting->IsPendingKill())
	{
		Manager_Crafting->Destroy(true);
		Manager_Crafting = nullptr;

	}
	// Manager AI
	if (Manager_AI && !Manager_AI->IsPendingKill())
	{
		Manager_AI->Destroy(true);
		Manager_AI = nullptr;

	}
	// Manager Decal
	if (Manager_Decal && !Manager_Decal->IsPendingKill())
	{
		Manager_Decal->Destroy(true);
		Manager_Decal = nullptr;

	}
	// Manager Trace
	if (Manager_Trace && !Manager_Trace->IsPendingKill())
	{
		Manager_Trace->Destroy(true);
		Manager_Trace = nullptr;

	}

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
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsGameState::OnBoard_Internal;
	Payload->Actor			= this;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckActor;
	Payload->Add			= &ACsGameState::AddRoutine;
	Payload->Remove			= &ACsGameState::RemoveRoutine;
	Payload->Type			= (uint8)ECsGameStateRoutine::OnBoard_Internal;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsGameStateCachedName::Name::OnBoard_Internal;
	Payload->NameAsString	= ECsGameStateCachedString::Str::OnBoard_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(ACsGameState, OnBoard_Internal)
{
	ACsGameState* gs		 = Cast<ACsGameState>(r->GetActor());
	UCsGameInstance* gi		 = Cast<UCsGameInstance>(gs->GetGameInstance());
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();
	UWorld* w				 = gs->GetWorld();
	
	ACsPlayerController* pc = UCsCommon::GetLocalPlayerController<ACsPlayerController>(w);
	ACsUI* hud				= pc ? Cast<ACsUI>(pc->MyHUD) : nullptr;

	ACsDataMapping* dataMapping = UCsCommon::GetDataMapping(w);

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_WAIT_UNTIL(r, gi->OnBoardState == ECsGameInstanceOnBoardState::Completed);

	gs->LoadCommonData();

	// Wait until Controller is VALID
	CS_COROUTINE_WAIT_UNTIL(r, pc);

	// Wait until HUD is VALID
	CS_COROUTINE_WAIT_UNTIL(r, hud);

	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::SetAssetReferencesCommonData);

#if WITH_EDITOR
	CS_COROUTINE_WAIT_UNTIL(r, !dataMapping->AsyncTaskMutex.IsLocked());
#endif // #if WITH_EDITOR

	gs->StartSetAssetReferencesCommonData();

	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::SetupHUD);

	gs->SetupHUD();

	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::LoadGameData);

	gs->LoadGameData();

	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::SetAssetReferencesGameData);

#if WITH_EDITOR
	CS_COROUTINE_WAIT_UNTIL(r, !dataMapping->AsyncTaskMutex.IsLocked());
#endif // #if WITH_EDITOR

	gs->StartSetAssetReferencesGameData();

	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::LoadItems);

	gs->LoadItems();

	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::LoadSceneData);

	gs->LoadSceneData();

	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::SetAssetReferencesSceneData);

#if WITH_EDITOR
	CS_COROUTINE_WAIT_UNTIL(r, !dataMapping->AsyncTaskMutex.IsLocked());
#endif // #if WITH_EDITOR

	gs->StartSetAssetReferencesSceneData();

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

	gs->OnBoard_Completed();

	CS_COROUTINE_END(r);
}

void ACsGameState::GetLoadAssetsShortCodes(const TCsLoadAssetsType &AssetsType, TArray<FName> &OutShortCodes){}

void ACsGameState::LoadCommonData(){}
void ACsGameState::OnFinishedLoadCommonData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime){}

void ACsGameState::StartSetAssetReferencesCommonData()
{
	if (UCsCommon::CanAsyncTask())
	{
		AsyncSetAssetReferencesCommonData();
	}
	else
	{
		SetAssetReferencesCommonData();
	}
}

void ACsGameState::AsyncSetAssetReferencesCommonData()
{
#if WITH_EDITOR
	UCsCommon::GetDataMapping(GetWorld())->AsyncTaskMutex.Lock();
#endif // #if WITH_EDITOR

	UCsManager_Runnable* Manager_Runnable = UCsManager_Runnable::Get();

	FCsRunnablePayload* Payload = Manager_Runnable->AllocatePayload();
	Payload->Owner				= this;
	Payload->ThreadPriority		= EThreadPriority::TPri_Normal;

	FCsRunnable_Delegate* Runnable = Manager_Runnable->Prep(Payload);
	Runnable->Delegate.AddUObject(this, &ACsGameState::SetAssetReferencesCommonData);
	Runnable->Start();
}

void ACsGameState::SetAssetReferencesCommonData() 
{ 
	ClearTransientLoadedAssets();

	OnBoardState = ECsGameStateOnBoardState::SetupHUD; 
}

void ACsGameState::SetupHUD(){}
void ACsGameState::LoadGameData(){}
void ACsGameState::OnFinishedLoadGameData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime){}

void ACsGameState::StartSetAssetReferencesGameData()
{
	if (UCsCommon::CanAsyncTask())
	{
		AsyncSetAssetReferencesGameData();
	}
	else
	{
		SetAssetReferencesGameData();
	}
}

void ACsGameState::AsyncSetAssetReferencesGameData()
{
#if WITH_EDITOR
	UCsCommon::GetDataMapping(GetWorld())->AsyncTaskMutex.Lock();
#endif // #if WITH_EDITOR

	UCsManager_Runnable* Manager_Runnable = UCsManager_Runnable::Get();

	FCsRunnablePayload* Payload = Manager_Runnable->AllocatePayload();
	Payload->Owner				= this;
	Payload->ThreadPriority		= EThreadPriority::TPri_Normal;

	FCsRunnable_Delegate* Runnable = Manager_Runnable->Prep(Payload);
	Runnable->Delegate.AddUObject(this, &ACsGameState::SetAssetReferencesGameData);
	Runnable->Start();
}

void ACsGameState::SetAssetReferencesGameData() 
{
	ClearTransientLoadedAssets();

	OnBoardState = ECsGameStateOnBoardState::LoadItems;
}

void ACsGameState::LoadItems() { OnBoardState = ECsGameStateOnBoardState::LoadSceneData; }
void ACsGameState::LoadSceneData(){ OnBoardState = ECsGameStateOnBoardState::SetAssetReferencesSceneData; }
void ACsGameState::OnFinishedLoadSceneData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime){}

void ACsGameState::StartSetAssetReferencesSceneData()
{
	if (UCsCommon::CanAsyncTask())
	{
		AsyncSetAssetReferencesSceneData();
	}
	else
	{
		SetAssetReferencesSceneData();
	}
}

void ACsGameState::AsyncSetAssetReferencesSceneData()
{
#if WITH_EDITOR
	UCsCommon::GetDataMapping(GetWorld())->AsyncTaskMutex.Lock();
#endif // #if WITH_EDITOR

	UCsManager_Runnable* Manager_Runnable = UCsManager_Runnable::Get();

	FCsRunnablePayload* Payload = Manager_Runnable->AllocatePayload();
	Payload->Owner = this;
	Payload->ThreadPriority = EThreadPriority::TPri_Normal;

	FCsRunnable_Delegate* Runnable = Manager_Runnable->Prep(Payload);
	Runnable->Delegate.AddUObject(this, &ACsGameState::SetAssetReferencesSceneData);
	Runnable->Start();
}

void ACsGameState::SetAssetReferencesSceneData() 
{
	ClearTransientLoadedAssets();

	OnBoardState = ECsGameStateOnBoardState::SetupScene;
}

void ACsGameState::SetupScene()
{
	OnBoardState = ECsGameStateOnBoardState::SetupLastTickActor;
}

void ACsGameState::OnBoard_Completed()
{
#if WITH_EDITOR
	const ULevelEditorPlaySettings* PlayInSettings = GetDefault<ULevelEditorPlaySettings>();

	if (PlayInSettings)
	{
		PlayInSettings->GetPlayNumberOfClients(NumberOfClients);
	}
#endif // #if WITH_EDITOR
}

void ACsGameState::SetTransientLoadedAssets(const TArray<UObject*> &LoadedAssets)
{
	const int32 Count = LoadedAssets.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		TransientLoadedAssets.Add(LoadedAssets[I]);
	}
}

void ACsGameState::ClearTransientLoadedAssets()
{
	TransientLoadedAssets.Reset();
#if WITH_EDITOR
	UCsCommon::GetDataMapping(GetWorld())->AsyncTaskMutex.Unlock();
#endif // #if WITH_EDITOR
}

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

	if (CsCVarLogGameStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsGameState::SetupLastTickActor: State Change: SetupLastTickActor -> %s"), *(ECsGameStateOnBoardState::ToString(OnBoardState)));
	}
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

	// Player
	if (ACsPlayerState* NewPlayerState = Cast<ACsPlayerState>(PlayerState))
		AddPlayerStateMapping(NewPlayerState);
	// AI
	if (ACsAIPlayerState* NewPlayerState = Cast<ACsAIPlayerState>(PlayerState))
		AddAIPlayerStateMapping(NewPlayerState);
}

void ACsGameState::AddPlayerStateMapping(ACsPlayerState* NewPlayerState)
{
	NewPlayerState->UniqueMappingId = CurrentPlayerStateUniqueMappingId;

	PlayerStateMappings.Add(NewPlayerState->UniqueMappingId, NewPlayerState);

	TArray<uint8> MappingKeys;
	const int32 NumMappingKeys = PlayerStateMappings.GetKeys(MappingKeys);

	PlayerStateMappingRelationships.Add(NewPlayerState->UniqueMappingId);

	TArray<uint8> RelationshipKeys;
	const int32 NumRelationshipKeys = PlayerStateMappingRelationships.GetKeys(RelationshipKeys);

	// Sanity check
	check(NumMappingKeys == NumRelationshipKeys);

	for (int32 I = 0; I < NumMappingKeys; ++I)
	{
		const uint8& Key = MappingKeys[I];

		// For a NEW entry, add ALL relationships
		if (Key == CurrentPlayerStateUniqueMappingId)
		{
			TArray<FCsPlayerStateMappingRelationship>* Relationships = PlayerStateMappingRelationships.Find(Key);

			for (int32 J = 0; J < NumMappingKeys; ++J)
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

	// Add to AIPlayerStateMappingRelationships

	TArray<uint8> AIRelationshipKeys;
	const int32 NumAIRelationshipKeys = AIPlayerStateMappingRelationships.GetKeys(AIRelationshipKeys);

	for (int32 I = 0; I < NumAIRelationshipKeys; ++I)
	{
		const uint8& Key = AIRelationshipKeys[I];

		TArray<FCsAIPlayerStateMappingRelationship>* Relationships = AIPlayerStateMappingRelationships.Find(Key);

		Relationships->AddDefaulted(1);

		FCsAIPlayerStateMappingRelationship& Relationship = (*Relationships)[I];
		Relationship.A = Key;
		Relationship.B = CurrentPlayerStateUniqueMappingId;
	}

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

	for (int32 I = 0; I < NumRelationshipKeys; ++I)
	{
		const uint8& Key = RelationshipKeys[I];

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
	TArray<FCsPlayerStateMappingRelationship>* Relationships = PlayerStateMappingRelationships.Find(MappingId);
	const int32 NumRelationships							 = Relationships->Num();

	for (int32 I = 0; I < NumRelationships; ++I)
	{
		FCsPlayerStateMappingRelationship& Relationship = (*Relationships)[I];

		if (Relationship.B == ClientMappingId)
		{
			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				ACsPlayerState* ClientPlayerState = GetPlayerState(ClientMappingId);
				ACsPlayerState* PlayerState		  = GetPlayerState(MappingId);

				const FString ClientName = ClientPlayerState ? ClientPlayerState->PlayerName : ECsCachedString::Str::INVALID;
				const FString OtherName  = PlayerState ? PlayerState->PlayerName : ECsCachedString::Str::INVALID;
				const FString Value		 = Relationship.HasBCompletedInitialReplicationAndLoadingForA ? ECsCachedString::Str::True : ECsCachedString::Str::False;

				UE_LOG(LogCs, Log, TEXT("ACsGameState::SetPlayerStateMappingRelationshipFlag: Relationship: %s(%d) <-> %s(%d) from %s to True."), *OtherName, MappingId, *ClientName, ClientMappingId, *Value);
			}
			Relationship.HasBCompletedInitialReplicationAndLoadingForA = true;
			break;
		}
	}
}

FString ACsGameState::GetLocalPlayerProfileName()
{
	return ECsGameStateCachedString::Str::DefaultPlayerProfileName;
}

#pragma endregion Player State

// A.I. Player State
#pragma region

void ACsGameState::AddAIPlayerStateMapping(ACsAIPlayerState* NewPlayerState)
{
	NewPlayerState->UniqueMappingId = CurrentAIPlayerStateUniqueMappingId;

	AIPlayerStateMappings.Add(NewPlayerState->UniqueMappingId, NewPlayerState);

	TArray<uint8> MappingKeys;
	const int32 NumMappingKeys = AIPlayerStateMappings.GetKeys(MappingKeys);

	AIPlayerStateMappingRelationships.Add(NewPlayerState->UniqueMappingId);

	// For a NEW entry, add ALL relationships
	TArray<uint8> PlayerStateKeys;
	const int32 NumPlayerStateKeys = PlayerStateMappings.GetKeys(PlayerStateKeys);

	TArray<FCsAIPlayerStateMappingRelationship>* Relationships = AIPlayerStateMappingRelationships.Find(CurrentAIPlayerStateUniqueMappingId);

	for (int32 I = 0; I < NumPlayerStateKeys; ++I)
	{
		Relationships->AddDefaulted(1);

		FCsAIPlayerStateMappingRelationship& Relationship = (*Relationships)[I];
		Relationship.A = CurrentAIPlayerStateUniqueMappingId;
		Relationship.B = PlayerStateKeys[I];
	}

	HasAIPlayerStateFullyReplicatedAndLoadedBroadcastFlags.Add(NewPlayerState->UniqueMappingId, false);

	CurrentAIPlayerStateUniqueMappingId++;
}

class ACsAIPlayerState* ACsGameState::GetAIPlayerState(const uint8 &MappingId)
{
	TWeakObjectPtr<ACsAIPlayerState>* PtrPlayerState = AIPlayerStateMappings.Find(MappingId);

	if (!PtrPlayerState)
		return nullptr;
	return (*PtrPlayerState).IsValid() ? (*PtrPlayerState).Get() : nullptr;
}

void ACsGameState::OnTick_HandleBroadcastingAIPlayerStateFullyReplicatedAndLoaded()
{
	TArray<uint8> RelationshipKeys;
	const int32 NumRelationshipKeys = AIPlayerStateMappingRelationships.GetKeys(RelationshipKeys);

	for (int32 I = 0; I < NumRelationshipKeys; ++I)
	{
		const uint8& Key = RelationshipKeys[I];

		ACsAIPlayerState* PlayerState = GetAIPlayerState(Key);

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

		bool* BroadcastFlag = HasAIPlayerStateFullyReplicatedAndLoadedBroadcastFlags.Find(Key);

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

void ACsGameState::SetAIPlayerStateMappingRelationshipFlag(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	TArray<FCsAIPlayerStateMappingRelationship>* Relationships = AIPlayerStateMappingRelationships.Find(MappingId);
	const int32 NumRelationships							   = Relationships->Num();

	for (int32 I = 0; I < NumRelationships; ++I)
	{
		FCsAIPlayerStateMappingRelationship& Relationship = (*Relationships)[I];

		if (Relationship.B == ClientMappingId)
		{
			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				ACsPlayerState* ClientPlayerState = GetPlayerState(ClientMappingId);
				ACsAIPlayerState* PlayerState	  = GetAIPlayerState(MappingId);

				const FString ClientName = ClientPlayerState ? ClientPlayerState->PlayerName : ECsCachedString::Str::INVALID;
				const FString OtherName  = PlayerState ? PlayerState->PlayerName : ECsCachedString::Str::INVALID;
				const FString Value		 = Relationship.HasBCompletedInitialReplicationAndLoadingForA ? ECsCachedString::Str::True : ECsCachedString::Str::False;

				UE_LOG(LogCs, Log, TEXT("ACsGameState::SetAIPlayerStateMappingRelationshipFlag: Relationship: %s(%d) <-> %s(%d) from %s to True."), *OtherName, MappingId, *ClientName, ClientMappingId, *Value);
			}
			Relationship.HasBCompletedInitialReplicationAndLoadingForA = true;
			break;
		}
	}
}

#pragma endregion A.I. Player State

void ACsGameState::StartLevelTransition()
{
	ACsPlayerController* MyController = UCsCommon::GetLocalPlayerController<ACsPlayerController>(GetWorld());
	UCsGameInstance* GameInstance	 = Cast<UCsGameInstance>(GetGameInstance());

	GameInstance->FullscreenWidget->SetUserFocus(MyController);

	MyController->bShowMouseCursor = false;

	GEngine->GameViewport->Viewport->ShowCursor(false);

	GameInstance->LevelState = ECsLevelState::BeginTransition;
}

void ACsGameState::ExitGame()
{
	Cast<UCsGameInstance>(GetGameInstance())->ExitGame();
}

#if WITH_EDITOR

void ACsGameState::OnPrePIEEnded(const bool IsSimulating){}

#endif // #if WITH_EDITOR