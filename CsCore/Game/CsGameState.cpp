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

#include "Game/CsGameInstance.h"
#include "Javascript/CsJavascriptEntryPoint.h"
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

UENUM(BlueprintType)
namespace ECsGameStateRoutine
{
	enum Type
	{
		OnBoard_Internal		UMETA(DisplayName = "OnBoard_Internal"),
		ECsGameStateRoutine_MAX	UMETA(Hidden),
	};
}

namespace ECsGameStateRoutine
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString OnBoard_Internal = TCsString(TEXT("OnBoard_Internal"), TEXT("onboard_internal"), TEXT("onboard internal"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::OnBoard_Internal) { return Str::OnBoard_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::OnBoard_Internal) { return Type::OnBoard_Internal; }
		return Type::ECsGameStateRoutine_MAX;
	}
}

#define ECS_GAME_STATE_ROUTINE_MAX (uint8)ECsGameStateRoutine::ECsGameStateRoutine_MAX
typedef ECsGameStateRoutine::Type TCsGameStateRoutine;

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

#if WITH_EDITOR
	FEditorDelegates::PrePIEEnded.AddUObject(this, &ACsGameState::OnPrePIEEnded);
#endif // #if WITH_EDITOR
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

	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
	GameInstance->LevelState	  = ECsLevelState::Loaded;

	GameInstance->CurrentGameFrame = 0;
	GameInstance->OnTick_Event.Clear();
	GameInstance->OnTick_Event.AddUObject(this, &ACsGameState::OnTick_GameInstance);

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

void ACsGameState::OnTick_GameInstance(const float &DeltaSeconds)
{
	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());

	++(GameInstance->CurrentGameFrame);
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

	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::LoadGameData);

	gs->LoadGameData();

	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::LoadItems);

	gs->LoadItems();

	CS_COROUTINE_WAIT_UNTIL(r, gs->OnBoardState == ECsGameStateOnBoardState::LoadSceneData);

	gs->LoadSceneData();

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
void ACsGameState::SetupHUD(){}
void ACsGameState::LoadGameData(){}
void ACsGameState::OnFinishedLoadGameData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime){}
void ACsGameState::LoadItems() { OnBoardState = ECsGameStateOnBoardState::LoadSceneData; }
void ACsGameState::LoadSceneData(){ OnBoardState = ECsGameStateOnBoardState::SetupScene; }
void ACsGameState::OnFinishedLoadSceneData(const TArray<UObject*> &LoadedAssets, const float& LoadingTime){}
void ACsGameState::SetupScene(){}

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

#if WITH_EDITOR

void ACsGameState::OnPrePIEEnded(const bool IsSimulating){}

#endif // #if WITH_EDITOR