// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsPlayerStateBase.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "Coroutine/CsCoroutineScheduler.h"

// Managers
#include "Managers/CsManager_Loading.h"
#include "Managers/Runnable/CsManager_Runnable.h"
// Data
#include "Data/CsDataMapping.h"

#include "Pawn/CsPawn.h"

#include "Game/CsGameInstance.h"
#include "Game/CsGameState.h"

// UI
#include "UI/CsWidget_Fullscreen.h"

#if WITH_EDITOR
#include "Editor/UnrealEd/Public/Editor.h"
#endif // #if WITH_EDITOR

// Enums
#pragma region

EMCsPlayerStateBaseRoutine* EMCsPlayerStateBaseRoutine::Instance;

EMCsPlayerStateBaseRoutine& EMCsPlayerStateBaseRoutine::Get()
{
	if (!Instance)
		Instance = new EMCsPlayerStateBaseRoutine();
	return *Instance;
}

namespace ECsPlayerStateBaseRoutine
{
	CSCORE_API const FECsPlayerStateBaseRoutine OnBoard_Internal = EMCsPlayerStateBaseRoutine::Get().Create(TEXT("OnBoard_Internal"));
	CSCORE_API const FECsPlayerStateBaseRoutine RequestUniqueMappingId_AI_Internal = EMCsPlayerStateBaseRoutine::Get().Create(TEXT("RequestUniqueMappingId_AI_Internal"));
}

EMCsPlayerStateBaseOnBoardState* EMCsPlayerStateBaseOnBoardState::Instance;

EMCsPlayerStateBaseOnBoardState& EMCsPlayerStateBaseOnBoardState::Get()
{
	if (!Instance)
		Instance = new EMCsPlayerStateBaseOnBoardState();
	return *Instance;
}

namespace ECsPlayerStateBaseOnBoardState
{
	namespace Ref
	{
		CSCORE_API const Type WaitingForGameState = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::WaitingForGameState, TEXT("WaitingForGameState"), TEXT("Waiting for GameState"));
		CSCORE_API const Type WaitingForFinishLoadingCommonData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::WaitingForFinishLoadingCommonData, TEXT("WaitingForFinishLoadingCommonData"), TEXT("Waiting for Finish Loading Common Data"));
		CSCORE_API const Type WaitingForLocalPlayerState = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::WaitingForLocalPlayerState, TEXT("WaitingForLocalPlayerState"), TEXT("Waiting for Local PlayerState"));
		// Client
		CSCORE_API const Type RequestLocalUniqueMappingId = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::RequestLocalUniqueMappingId, TEXT("RequestLocalUniqueMappingId"), TEXT("Request Local UniqueMappingId"));
		CSCORE_API const Type WaitingForLocalUniqueMappingId = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::WaitingForLocalUniqueMappingId, TEXT("WaitingForLocalUniqueMappingId"), TEXT("Waiting for Local UniqueMappingId"));
		CSCORE_API const Type RecievedLocalUniqueMappingId = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::RecievedLocalUniqueMappingId, TEXT("RecievedLocalUniqueMappingId"), TEXT("Recieved Local UniqueMappingId"));
		// Requesting Player State on Client
		CSCORE_API const Type RequestUniqueMappingId = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::RequestUniqueMappingId, TEXT("RequestUniqueMappingId"), TEXT("Request UniqueMappingId"));
		CSCORE_API const Type WaitingForUniqueMappingId = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::WaitingForUniqueMappingId, TEXT("WaitingForUniqueMappingId"), TEXT("Waiting for UniqueMappingId"));
		CSCORE_API const Type RecievedUniqueMappingId = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::RecievedUniqueMappingId, TEXT("RecievedUniqueMappingId"), TEXT("Recieved UniqueMappingId"));
		// Player
		CSCORE_API const Type RequestPlayerData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::RequestPlayerData, TEXT("RequestPlayerData"), TEXT("Request Player Data"));
		CSCORE_API const Type WaitingForPlayerData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::WaitingForPlayerData, TEXT("WaitingForPlayerData"), TEXT("Waiting for Player Data"));
		CSCORE_API const Type ReceivedPlayerData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::ReceivedPlayerData, TEXT("ReceivedPlayerData"), TEXT("Received Player Data"));
		// AI
		CSCORE_API const Type RequestAIData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::RequestAIData, TEXT("RequestAIData"), TEXT("Request AI Data"));
		CSCORE_API const Type WaitingForAIData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::WaitingForAIData, TEXT("WaitingForAIData"), TEXT("Waiting for AI Data"));
		CSCORE_API const Type ReceivedAIData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::ReceivedAIData, TEXT("ReceivedAIData"), TEXT("Received AI Data"));
		// Loading
		CSCORE_API const Type BeginLoadingPlayerData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::BeginLoadingPlayerData, TEXT("BeginLoadingPlayerData"), TEXT("Begin Loading Player Data"));
		CSCORE_API const Type WaitingForFinishLoadingPlayerData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::WaitingForFinishLoadingPlayerData, TEXT("WaitingForFinishLoadingPlayerData"), TEXT("Waiting for Finish Loading Player Data"));
		CSCORE_API const Type FinishedLoadingPlayerData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::FinishedLoadingPlayerData, TEXT("FinishedLoadingPlayerData"), TEXT("Finished Loading Player Data"));
		CSCORE_API const Type SetAssetReferencesPlayerData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::SetAssetReferencesPlayerData, TEXT("SetAssetReferencesPlayerData"), TEXT("Set Asset Referencess Player Data"));
		CSCORE_API const Type WaitingForSetAssetReferencesPlayerData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::WaitingForSetAssetReferencesPlayerData, TEXT("WaitingForSetAssetReferencesPlayerData"), TEXT("Waiting for Set Asset Referencess Player Data"));
		CSCORE_API const Type FinishedSetAssetReferencesPlayerData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::FinishedSetAssetReferencesPlayerData, TEXT("FinishedSetAssetReferencesPlayerData"), TEXT("Finished Set Asset Referencess Player Data"));
		// Setup
		CSCORE_API const Type BeginApplyingPlayerData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::BeginApplyingPlayerData, TEXT("BeginApplyingPlayerData"), TEXT("Begin Applying Player Data"));
		CSCORE_API const Type WaitingForFinishApplyingPlayerData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::WaitingForFinishApplyingPlayerData, TEXT("WaitingForFinishApplyingPlayerData"), TEXT("Waiting for Finish Applying Player Data"));
		CSCORE_API const Type FinishedApplyingPlayerData = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::FinishedApplyingPlayerData, TEXT("FinishedApplyingPlayerData"), TEXT("Finished Applying Player Data"));
		// Handshaking
		CSCORE_API const Type SendOnBoardCompleted = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::SendOnBoardCompleted, TEXT("SendOnBoardCompleted"), TEXT("Send OnBoard Completed"));
		CSCORE_API const Type WaitingForOnBoardCompleted = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::WaitingForOnBoardCompleted, TEXT("WaitingForOnBoardCompleted"), TEXT("Waiting for OnBoard Completed"));
		CSCORE_API const Type Completed = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::Completed, TEXT("Completed"));
		CSCORE_API const Type ECsPlayerStateBaseOnBoardState_MAX = EMCsPlayerStateBaseOnBoardState::Get().Add(Type::ECsPlayerStateBaseOnBoardState_MAX, TEXT("ECsPlayerStateBaseOnBoardState_MAX"), TEXT("MAX"));
	}
}

#pragma endregion Enums

// Cache
#pragma region

namespace ECsPlayerStateBaseCached
{
	namespace Name
	{
		// Functions
		const FName OnBoard_Internal = FName("ACsPlayerStateBase::OnBoard_Internal");
		const FName RequestUniqueMappingId_AI_Internal = FName("ACsPlayerStateBase::RequestUniqueMappingId_AI_Internal");
	};

	namespace Str
	{
		// Functions
		const FString OnBoard_Internal = TEXT("ACsPlayerStateBase::OnBoard_Internal");
		const FString RequestUniqueMappingId_AI_Internal = TEXT("ACsPlayerStateBase::RequestUniqueMappingId_AI_Internal");
	};
}

#pragma endregion Cache

ACsPlayerStateBase::ACsPlayerStateBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick				 = true;
	PrimaryActorTick.bStartWithTickEnabled		 = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;

	OnBoardState	= ECsPlayerStateBaseOnBoardState::WaitingForGameState;
	UniqueMappingId = CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID;
}

void ACsPlayerStateBase::PostActorCreated()
{
	Super::PostActorCreated();

#if WITH_EDITOR
	FEditorDelegates::PrePIEEnded.Remove(OnPrePIEEndedDelegateHandle);
	OnPrePIEEndedDelegateHandle = FEditorDelegates::PrePIEEnded.AddUObject(this, &ACsPlayerStateBase::OnPrePIEEnded);
#endif // #if WITH_EDITOR

	OnBoard();
}

AController* ACsPlayerStateBase::GetMyController()
{
	if (MyController.IsValid() && MyController.Get())
		return MyController.Get();
	return nullptr;
}

ACsPawn* ACsPlayerStateBase::GetMyPawn()
{
	if (LinkedPawn.IsValid() && LinkedPawn.Get())
		return LinkedPawn.Get();

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		APawn* Pawn = It->Get();

		if (Pawn->GetPlayerState() == this)
		{
			LinkedPawn = Cast<ACsPawn>(Pawn);
			break;
		}
	}
	return LinkedPawn.Get();
}

// Routines
#pragma region

/*static*/ void ACsPlayerStateBase::AddRoutine(UObject* InPlayerState, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsPlayerStateBase>(InPlayerState)->AddRoutine_Internal(Routine, Type);
}

bool ACsPlayerStateBase::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const FECsPlayerStateBaseRoutine& RoutineType = EMCsPlayerStateBaseRoutine::Get()[Type];

	// OnBoard_Internal
	if (RoutineType == ECsPlayerStateBaseRoutine::OnBoard_Internal)
	{
		OnBoard_Internal_Routine = Routine;
		return true;
	}
	// TODO: This may cause issues with more than 1 AI
	// RequestUniqueMappingId_AI_Internal
	if (RoutineType == ECsPlayerStateBaseRoutine::RequestUniqueMappingId_AI_Internal)
	{
		RequestUniqueMappingId_AI_Internal_Routine = Routine;
		return true;
	}
	return false;
}

/*static*/ void ACsPlayerStateBase::RemoveRoutine(UObject* InPlayerState, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsPlayerStateBase>(InPlayerState)->RemoveRoutine_Internal(Routine, Type);
}

bool ACsPlayerStateBase::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const FECsPlayerStateBaseRoutine& RoutineType = EMCsPlayerStateBaseRoutine::Get()[Type];

	// OnBoard_Internal
	if (RoutineType == ECsPlayerStateBaseRoutine::OnBoard_Internal)
	{
		check(OnBoard_Internal_Routine == Routine);
		OnBoard_Internal_Routine = nullptr;
		return true;
	}
	// TODO: This may cause issues with more than 1 AI
	// RequestUniqueMappingId_AI_Internal
	if (RoutineType == ECsPlayerStateBaseRoutine::RequestUniqueMappingId_AI_Internal)
	{
		check(RequestUniqueMappingId_AI_Internal_Routine == Routine);
		RequestUniqueMappingId_AI_Internal_Routine = nullptr;
		return true;
	}
	return false;
}

#pragma endregion Routines

// OnBoard
#pragma region

void ACsPlayerStateBase::OnBoard()
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsPlayerStateBase::OnBoard_Internal;
	Payload->Actor			= this;
	Payload->Stop.Add(&UCsCommon::CoroutineStopCondition_CheckActor);
	Payload->Add			= &ACsPlayerStateBase::AddRoutine;
	Payload->Remove			= &ACsPlayerStateBase::RemoveRoutine;
	Payload->Type			= ECsPlayerStateBaseRoutine::OnBoard_Internal.Value;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsPlayerStateBaseCached::Name::OnBoard_Internal;
	Payload->NameAsString	= ECsPlayerStateBaseCached::Str::OnBoard_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(ACsPlayerStateBase, OnBoard_Internal)
{
	ACsPlayerStateBase* ps	 = r->GetActor<ACsPlayerStateBase>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	ps->OnTick_OnBoard();

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_WAIT_UNTIL(r, ps->OnBoardState == ECsPlayerStateBaseOnBoardState::Completed);

	ps->OnBoard_Completed();

	CS_COROUTINE_END(r);
}

void ACsPlayerStateBase::OnTick_OnBoard()
{
	// Waiting for GameState
	if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForGameState)
	{
		if (ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>())
		{
			OnLinkedPawnSet_Event.AddUObject(GameState, &ACsGameState::OnPlayerStateBaseLinkedToPawn);

			OnBoardState = ECsPlayerStateBaseOnBoardState::WaitingForFinishLoadingCommonData;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_OnBoard: State Change: WaitingForGameState -> WaitingForFinishLoadingCommonData"));
			}
		}
	}
	// Waiting for Finish Loading Common Data
	if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForFinishLoadingCommonData)
	{
		ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

		if (GameState->OnBoardState > ECsGameStateOnBoardState::LoadCommonData)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::WaitingForLocalPlayerState;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: WaitingForFinishLoadingCommonData -> WaitingForLocalPlayerState"));
			}
		}
	}
	// Client
	{
		// Waiting for Local PlayerState
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForLocalPlayerState)
		{
			if (ACsPlayerStateBase* LocalPlayerState = UCsCommon::GetLocalPlayerState<ACsPlayerStateBase>(GetWorld()))
			{
				OnBoardState = ECsPlayerStateBaseOnBoardState::RequestLocalUniqueMappingId;

				if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: WaitingForLocalPlayerState -> RequestUniqueMappingId"));
				}
			}
		}
		// Request Local Unique Mapping Id
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::RequestLocalUniqueMappingId)
		{
			ACsPlayerStateBase* LocalPlayerState = UCsCommon::GetLocalPlayerState<ACsPlayerStateBase>(GetWorld());

			if (LocalPlayerState->UniqueMappingId == CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID)
			{
				OnBoardState = ECsPlayerStateBaseOnBoardState::WaitingForLocalUniqueMappingId;

				// Only Request ONCE from Server
				ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

				if (!GameState->bServerRequestLocalUniqueMappingId)
				{
					GameState->bServerRequestLocalUniqueMappingId = true;

					if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
					{
						UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: RequestLocalUniqueMappingId -> WaitingForLocalUniqueMappingId"));
					}
					LocalPlayerState->ServerRequestLocalUniqueMappingId(LocalPlayerState, this);
				}
			}
			else
			{
				OnBoardState = ECsPlayerStateBaseOnBoardState::RequestUniqueMappingId;

				if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: RequestLocalUniqueMappingId -> RequestUniqueMappingId"));
				}
			}
		}
		// Waiting for Local Unique Mapping Id
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForLocalUniqueMappingId)
		{
			ACsPlayerStateBase* LocalPlayerState = UCsCommon::GetLocalPlayerState<ACsPlayerStateBase>(GetWorld());

			if (LocalPlayerState->UniqueMappingId < CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID)
			{
				OnBoardState = ECsPlayerStateBaseOnBoardState::RequestUniqueMappingId;

				if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: RequestLocalUniqueMappingId -> RequestUniqueMappingId"));
				}
			}
		}
		// Received Local Unique Mapping Id
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::RecievedLocalUniqueMappingId)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::RequestUniqueMappingId;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: RecievedLocalUniqueMappingId -> RequestUniqueMappingId"));
			}
		}
	}
	// Requesting Player State on Client
	{
		// Request Unique Mapping Id
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::RequestUniqueMappingId)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::WaitingForUniqueMappingId;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: RequestUniqueMappingId -> WaitingForUniqueMappingId"));
			}
			ACsPlayerStateBase* LocalPlayerState = UCsCommon::GetLocalPlayerState<ACsPlayerStateBase>(GetWorld());

			LocalPlayerState->ServerRequestUniqueMappingId(LocalPlayerState->UniqueMappingId, this);
		}
		// Waiting for Unique Mapping Id
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForUniqueMappingId)
		{
		}
		// Received Unique Mapping Id
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::RecievedUniqueMappingId)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::RequestPlayerData;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: RecievedUniqueMappingId -> RequestPlayerData"));
			}
		}
		// Request PlayerData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::RequestPlayerData)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::WaitingForPlayerData;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: RequestPlayerData -> WaitingForPlayerData"));
			}
			ACsPlayerStateBase* LocalPlayerState = UCsCommon::GetLocalPlayerState<ACsPlayerStateBase>(GetWorld());

			LocalPlayerState->ServerRequestPlayerData(LocalPlayerState->UniqueMappingId, UniqueMappingId);
		}
		// Waiting for PlayerData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForPlayerData)
		{
		}
		// Received PlayerData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::ReceivedPlayerData)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::WaitingForGameStateOnBoardCompleted;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: ReceivedPlayerData -> WaitingForGameStateOnBoardCompleted"));
			}
		}
	}
	// Loading
	{
		// Waiting for GameState OnBoard to Complete
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForGameStateOnBoardCompleted)
		{
			ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

			if (GameState->OnBoardState == ECsGameStateOnBoardState::Completed)
			{
				OnBoardState = ECsPlayerStateBaseOnBoardState::BeginLoadingPlayerData;

				if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: WaitingForGameStateOnBoardCompleted -> BeginLoadingPlayerData"));
				}
			}
		}
		// Begin Loading PlayerData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::BeginLoadingPlayerData)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::WaitingForFinishLoadingPlayerData;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: BeginLoadingPlayerData -> WaitingForFinishLoadingPlayerData"));
			}
			LoadPlayerData();
		}
		// Waiting for Finish Loading PlayerData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForFinishLoadingPlayerData)
		{
		}
		// Finished Loading PlayerData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::FinishedLoadingPlayerData)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::SetAssetReferencesPlayerData;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: FinishedLoadingPlayerData -> SetAssetReferencesPlayerData"));
			}
		}
		// Set Asset References PlayerData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::SetAssetReferencesPlayerData)
		{
			if (!UCsCommon::GetDataMapping(GetWorld())->AsyncTaskMutex.IsLocked())
			{
				OnBoardState = ECsPlayerStateBaseOnBoardState::WaitingForSetAssetReferencesPlayerData;

				if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: SetAssetReferencesPlayerData -> WaitingForSetAssetReferencesPlayerData"));
				}
				StartSetAssetReferencesPlayerData();
			}
		}
		// Waiting for Set Asset References PlayerData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForSetAssetReferencesPlayerData)
		{
		}
		// Finished Set Asset References PlayerData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::FinishedSetAssetReferencesPlayerData)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::BeginApplyingPlayerData;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: FinishedSetAssetReferencesPlayerData -> BeginApplyingPlayerData"));
			}
		}
	}
	// Setup
	{
		// Begin Applying PlayerData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::BeginApplyingPlayerData)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::WaitingForFinishApplyingPlayerData;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: BeginApplyingPlayerData -> WaitingForFinishApplyingPlayerData"));
			}
			SetupPlayerData();
		}
		// Waiting for Finish Applying PlayerData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForFinishApplyingPlayerData)
		{
		}
		// Finished Applying PlayerData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::FinishedApplyingPlayerData)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::SendOnBoardCompleted;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: FinishedApplyingPlayerData -> SendOnBoardCompleted"));
			}
		}
	}
	// Handshaking
	{
		// Send Finished Replication and Loading
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::SendOnBoardCompleted)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::WaitingForOnBoardCompleted;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::OnTick_HandleInitialReplicationAndLoading: State Change: SendOnBoardCompleted -> WaitingForOnBoardCompleted"));
			}
			ACsPlayerStateBase* LocalPlayerState = UCsCommon::GetLocalPlayerState<ACsPlayerStateBase>(GetWorld());

			LocalPlayerState->ServerSendOnBoardCompleted(LocalPlayerState->UniqueMappingId, UniqueMappingId);
		}
		// Waiting for Finished Replication and Loading
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForOnBoardCompleted)
		{
			IsOnBoardCompleted = true;
			OnBoardState	   = ECsPlayerStateBaseOnBoardState::Completed;
			/*
			if (IsOnBoardCompleted)
			{
				OnBoardState = ECsPlayerStateBaseOnBoardState::Completed;
			}
			*/
		}
	}
}

bool ACsPlayerStateBase::ServerRequestLocalUniqueMappingId_Validate(ACsPlayerStateBase* ClientPlayerState, ACsPlayerStateBase* RequestingPlayerState)
{
	return true;
}

void ACsPlayerStateBase::ServerRequestLocalUniqueMappingId_Implementation(ACsPlayerStateBase* ClientPlayerState, ACsPlayerStateBase* RequestingPlayerState)
{
	// Check VALID ClientPlayerState
	if (!ClientPlayerState)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPlayerStateBase::ServerRequestLocalUniqueMappingId: Client PlayerState is nullptr."));
		}
		return;
	}
	// Check Valid ClientMappingId
	if (ClientPlayerState->UniqueMappingId == CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPlayerStateBase::ServerRequestLocalUniqueMappingId: %s's UniqueMappingId is INVALID."), *ClientPlayerState->GetPlayerName());
		}
		return;
	}
	if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsPlayerStateBase::ServerRequestLocalUniqueMappingId: %s is requesting UniqueMappingId: %d"), *ClientPlayerState->GetPlayerName(), ClientPlayerState->UniqueMappingId);
	}
	ClientPlayerState->ClientRecieveLocalUniqueMappingId(ClientPlayerState->UniqueMappingId, RequestingPlayerState);
}

void ACsPlayerStateBase::ClientRecieveLocalUniqueMappingId_Implementation(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState)
{
	ClientRecieveLocalUniqueMappingId_Internal(ClientMappingId, RequestingPlayerState);
}

void ACsPlayerStateBase::ClientRecieveLocalUniqueMappingId_Internal(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState){}

	// Requesting Player State on Client
#pragma region

		// Player
#pragma region

bool ACsPlayerStateBase::ServerRequestUniqueMappingId_Validate(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState)
{
	return true;
}

void ACsPlayerStateBase::ServerRequestUniqueMappingId_Implementation(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState)
{
	ServerRequestUniqueMappingId_Internal(ClientMappingId, RequestingPlayerState);
}

void ACsPlayerStateBase::ServerRequestUniqueMappingId_Internal(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState){}

void ACsPlayerStateBase::ClientRecieveUniqueMappingId_Implementation(ACsPlayerStateBase* RequestingPlayerState, const uint8 &MappingId)
{
	RequestingPlayerState->ClientRecieveUniqueMappingId_Internal(MappingId);
}

void ACsPlayerStateBase::ClientRecieveUniqueMappingId_Internal(const uint8 &MappingId){}

bool ACsPlayerStateBase::ServerRequestPlayerData_Validate(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	return true;
}

void ACsPlayerStateBase::ServerRequestPlayerData_Implementation(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	ServerRequestPlayerData_Internal(ClientMappingId, MappingId);
}

void ACsPlayerStateBase::ServerRequestPlayerData_Internal(const uint8 &ClientMappingId, const uint8 &MappingId){}

#pragma endregion Player

		// AI
#pragma region

bool ACsPlayerStateBase::ServerRequestUniqueMappingId_AI_Validate(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState)
{
	return true;
}

void ACsPlayerStateBase::ServerRequestUniqueMappingId_AI_Implementation(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState)
{
	ServerRequestUniqueMappingId_AI_Internal(ClientMappingId, RequestingPlayerState);
}

void ACsPlayerStateBase::ServerRequestUniqueMappingId_AI_Internal(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState) {}

void ACsPlayerStateBase::RequestUniqueMappingId_AI(ACsPlayerStateBase* RequestingPlayerState)
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	Payload->Schedule		 = Schedule;
	Payload->Function		 = &ACsPlayerStateBase::RequestUniqueMappingId_AI_Internal;
	Payload->Actor			 = this;
	Payload->Stop.Add(&UCsCommon::CoroutineStopCondition_CheckActor);
	Payload->Add			 = &ACsPlayerStateBase::AddRoutine;
	Payload->Remove			 = &ACsPlayerStateBase::RemoveRoutine;
	Payload->Type			 = ECsPlayerStateBaseRoutine::RequestUniqueMappingId_AI_Internal.Value;
	Payload->DoInit			 = true;
	Payload->PerformFirstRun = false;
	Payload->Name			 = ECsPlayerStateBaseCached::Name::RequestUniqueMappingId_AI_Internal;
	Payload->NameAsString	 = ECsPlayerStateBaseCached::Str::RequestUniqueMappingId_AI_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	R->objects[0] = this;
	R->objects[1] = RequestingPlayerState;

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(ACsPlayerStateBase, RequestUniqueMappingId_AI_Internal)
{
	ACsPlayerStateBase* ps   = r->GetActor<ACsPlayerStateBase>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();
	UWorld* w				 = ps->GetWorld();

	ACsPlayerStateBase* ClientPlayerState	  = r->GetObjectAt<ACsPlayerStateBase>(0);
	ACsPlayerStateBase* RequestingPlayerState = r->GetObjectAt<ACsPlayerStateBase>(1);

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_WAIT_UNTIL(r, RequestingPlayerState->UniqueMappingId != CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID);
	
	ClientPlayerState->ClientRecieveUniqueMappingId_AI(RequestingPlayerState, RequestingPlayerState->UniqueMappingId);

	CS_COROUTINE_END(r);
}

void ACsPlayerStateBase::ClientRecieveUniqueMappingId_AI_Implementation(ACsPlayerStateBase* RequestingPlayerState, const uint8 &MappingId)
{
	RequestingPlayerState->ClientRecieveUniqueMappingId_AI_Internal(MappingId);
}

void ACsPlayerStateBase::ClientRecieveUniqueMappingId_AI_Internal(const uint8 &MappingId) {}

bool ACsPlayerStateBase::ServerRequestAIData_Validate(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	return true;
}

void ACsPlayerStateBase::ServerRequestAIData_Implementation(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	ServerRequestAIData_Internal(ClientMappingId, MappingId);
}

void ACsPlayerStateBase::ServerRequestAIData_Internal(const uint8 &ClientMappingId, const uint8 &MappingId) {}

#pragma endregion AI

#pragma endregion Requesting Player State on Client

void ACsPlayerStateBase::GetLoadAssetsShortCodes(const FECsLoadAssetsType &AssetsType, TArray<FName> &OutShortCodes){}
void ACsPlayerStateBase::LoadPlayerData(){}

void ACsPlayerStateBase::StartSetAssetReferencesPlayerData() 
{
	if (UCsCommon::CanAsyncTask())
	{
		AsyncSetAssetReferencesPlayerData();
	}
	else
	{
		SetAssetReferencesPlayerData();
	}
}

void ACsPlayerStateBase::AsyncSetAssetReferencesPlayerData() 
{
	UCsCommon::GetDataMapping(GetWorld())->AsyncTaskMutex.Lock();

	UCsManager_Runnable* Manager_Runnable = UCsManager_Runnable::Get();

	FCsRunnablePayload* Payload = Manager_Runnable->AllocatePayload();
	Payload->Owner				= this;
	Payload->ThreadPriority		= EThreadPriority::TPri_Normal;

	FCsRunnable_Delegate* Runnable = Manager_Runnable->Prep(Payload);
	Runnable->Delegate.AddUObject(this, &ACsPlayerStateBase::SetAssetReferencesPlayerData);
	Runnable->Start();
}

void ACsPlayerStateBase::SetAssetReferencesPlayerData() 
{
	ClearTransientLoadedAssets();

	OnBoardState = ECsPlayerStateBaseOnBoardState::FinishedSetAssetReferencesPlayerData; 
}

void ACsPlayerStateBase::OnFinishedLoadingPlayerData(const TArray<UObject*> &LoadedAssets, const float &LoadingTime){}
void ACsPlayerStateBase::SetupPlayerData() { OnBoardState = ECsPlayerStateBaseOnBoardState::FinishedApplyingPlayerData; }

bool ACsPlayerStateBase::ServerSendOnBoardCompleted_Validate(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	return true;
}

void ACsPlayerStateBase::ServerSendOnBoardCompleted_Implementation(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	ServerSendOnBoardCompleted_Internal(ClientMappingId, MappingId);
}

void ACsPlayerStateBase::ServerSendOnBoardCompleted_Internal(const uint8 &ClientMappingId, const uint8 &MappingId){}

bool ACsPlayerStateBase::ServerSendOnBoardCompleted_AI_Validate(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	return true;
}

void ACsPlayerStateBase::ServerSendOnBoardCompleted_AI_Implementation(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	ServerSendOnBoardCompleted_AI_Internal(ClientMappingId, MappingId);
}

void ACsPlayerStateBase::ServerSendOnBoardCompleted_AI_Internal(const uint8 &ClientMappingId, const uint8 &MappingId) {}

void ACsPlayerStateBase::MulticastSetIsOnBoardCompleted_Implementation()
{
	IsOnBoardCompleted = true;
}

void ACsPlayerStateBase::MulticastUnSetIsOnBoardCompleted_Implementation()
{
	IsOnBoardCompleted = false;
}

void ACsPlayerStateBase::ClearFullscreenWidget()
{
	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
	UCsWidget_Fullscreen* Widget  = Cast<UCsWidget_Fullscreen>(GameInstance->FullscreenWidget);
	Widget->Fullscreen.SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
}

void ACsPlayerStateBase::OnBoard_Completed() 
{
	if (this == UCsCommon::GetLocalPlayerState<ACsPlayerStateBase>(GetWorld()))
	{
		// Clear FullscreenWidget
		UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
		UCsWidget_Fullscreen* Widget  = Cast<UCsWidget_Fullscreen>(GameInstance->FullscreenWidget);
		Widget->Fullscreen.SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
	}
}

bool ACsPlayerStateBase::IsOnBoardCompleted_Game()
{
	if (!IsOnBoardCompleted)
		return false;

	ACsPawn* MyPawn = GetMyPawn();

	if (!MyPawn)
		return false;
	if (MyPawn->IsPendingKill())
		return false;
	if (MyPawn->GetPlayerState<ACsPlayerStateBase>() != this)
		return false;
	return true;
}

void ACsPlayerStateBase::SetTransientLoadedAssets(const TArray<UObject*> &LoadedAssets)
{
	const int32 Count = LoadedAssets.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		TransientLoadedAssets.Add(LoadedAssets[I]);
	}
}

void ACsPlayerStateBase::ClearTransientLoadedAssets()
{
	TransientLoadedAssets.Reset();
	UCsCommon::GetDataMapping(GetWorld())->AsyncTaskMutex.Unlock();
}

#pragma endregion OnBoard

#if WITH_EDITOR

void ACsPlayerStateBase::OnPrePIEEnded(const bool bIsSimulating){}

#endif // #if WITH_EDITOR