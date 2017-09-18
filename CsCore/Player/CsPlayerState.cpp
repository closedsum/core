// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsPlayerState.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Game/CsGameInstance.h"
#include "Game/CsGameState.h"
#include "Coroutine/CsCoroutineScheduler.h"

#include "Managers/CsManager_Loading.h"
#include "Data/CsDataMapping.h"

#include "Player/CsPlayerController.h"
#include "Player/CsPlayerPawn.h"

// UI
#include "UI/CsWidget_Fullscreen.h"

ACsPlayerState::ACsPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick				 = true;
	PrimaryActorTick.bStartWithTickEnabled		 = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;

	OnBoardState	= ECsPlayerStateOnBoardState::WaitingForGameState;
	UniqueMappingId = CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID;
}

void ACsPlayerState::PostActorCreated()
{
	Super::PostActorCreated();

	OnBoard();
}

AController* ACsPlayerState::GetMyController()
{
	if (MyController.IsValid() && MyController.Get())
		return MyController.Get();

	for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		AController* Controller = It->Get();

		if (Cast<ACsPlayerController>(Controller) &&
			Cast<ACsPlayerController>(Controller)->PlayerState == this)
		{
			MyController = Controller;
			break;
		}
	}
	return MyController.Get();
}

ACsPlayerPawn* ACsPlayerState::GetMyPawn()
{
	if (LinkedPawn.IsValid() && LinkedPawn.Get())
		return LinkedPawn.Get();

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		APawn* Pawn = It->Get();

		if (ACsPlayerPawn* P = Cast<ACsPlayerPawn>(Pawn))
		{
			LinkedPawn = P;
			break;
		}
	}
	return LinkedPawn.Get();
}

// Routines
#pragma region

/*static*/ void ACsPlayerState::AddRoutine(UObject* InGameState, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsPlayerState>(InGameState)->AddRoutine_Internal(Routine, Type);
}

bool ACsPlayerState::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const TCsPlayerStateRoutine RoutineType = (TCsPlayerStateRoutine)Type;

	// OnBoard_Internal
	if (RoutineType == ECsPlayerStateRoutine::OnBoard_Internal)
	{
		OnBoard_Internal_Routine = Routine;
		return true;
	}
	return false;
}

/*static*/ void ACsPlayerState::RemoveRoutine(UObject* InGameState, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<ACsGameState>(InGameState)->RemoveRoutine_Internal(Routine, Type);
}

bool ACsPlayerState::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const TCsPlayerStateRoutine RoutineType = (TCsPlayerStateRoutine)Type;

	// OnBoard_Internal
	if (RoutineType == ECsPlayerStateRoutine::OnBoard_Internal)
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

void ACsPlayerState::OnBoard()
{
	CsCoroutine Function		  = &ACsPlayerState::OnBoard_Internal;
	CsCoroutineStopCondition Stop = &UCsCommon::CoroutineStopCondition_CheckActor;
	CsAddRoutine Add			  = &ACsPlayerState::AddRoutine;
	CsRemoveRoutine Remove		  = &ACsPlayerState::RemoveRoutine;
	const uint8 Type			  = (uint8)ECsPlayerStateRoutine::OnBoard_Internal;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsRoutine* R					 = Scheduler->Allocate(Function, Stop, this, Add, Remove, Type, true, false);

	Scheduler->StartRoutine(R);
}

CS_COROUTINE(ACsPlayerState, OnBoard_Internal)
{
	ACsPlayerState* ps		 = Cast<ACsPlayerState>(r->GetActor());
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = ps->GetWorld();
	UCsGameInstance* gi		 = Cast<UCsGameInstance>(ps->GetGameInstance());

	ps->OnTick_OnBoard();

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_WAIT_UNTIL(r, ps->OnBoardState == ECsPlayerStateOnBoardState::Completed);

	{
		UCsWidget_Fullscreen* Widget = Cast<UCsWidget_Fullscreen>(gi->FullscreenWidget);
		Widget->Fullscreen.SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
	}

	CS_COROUTINE_END(r);
}

void ACsPlayerState::OnTick_OnBoard()
{
	// Waiting for GameState
	if (OnBoardState == ECsPlayerStateOnBoardState::WaitingForGameState)
	{
		if (ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>())
		{
			OnBoardState = ECsPlayerStateOnBoardState::WaitingForFinishLoadingCommonData;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerState::OnTick_OnBoard: State Change: WaitingForGameState -> WaitingForFinishLoadingCommonData"));
			}
		}
	}
	// Waiting for Finish Loading Common Data
	if (OnBoardState == ECsPlayerStateOnBoardState::WaitingForFinishLoadingCommonData)
	{
		ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

		if (GameState->OnBoardState > ECsGameStateOnBoardState::LoadCommonData)
		{
			OnBoardState = ECsPlayerStateOnBoardState::WaitingForLocalPlayerState;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: WaitingForFinishLoadingCommonData -> WaitingForLocalPlayerState"));
			}
		}
	}
	// Client
	{
		// Waiting for Local PlayerState
		if (OnBoardState == ECsPlayerStateOnBoardState::WaitingForLocalPlayerState)
		{
			if (ACsPlayerState* LocalPlayerState = UCsCommon::GetLocalPlayerState<ACsPlayerState>(GetWorld()))
			{
				OnBoardState = ECsPlayerStateOnBoardState::RequestLocalUniqueMappingId;

				if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UE_LOG(LogCs, Log, TEXT("ACsPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: WaitingForLocalPlayerState -> RequestUniqueMappingId"));
				}
			}
		}
		// Request Local Unique Mapping Id
		if (OnBoardState == ECsPlayerStateOnBoardState::RequestLocalUniqueMappingId)
		{
			ACsPlayerState* LocalPlayerState = UCsCommon::GetLocalPlayerState<ACsPlayerState>(GetWorld());

			if (LocalPlayerState->UniqueMappingId == CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID)
			{
				OnBoardState = ECsPlayerStateOnBoardState::WaitingForLocalUniqueMappingId;

				if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UE_LOG(LogCs, Log, TEXT("ACsPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RequestLocalUniqueMappingId -> WaitingForLocalUniqueMappingId"));
				}
				ServerRequestLocalUniqueMappingId(LocalPlayerState);
			}
			else
			{
				OnBoardState = ECsPlayerStateOnBoardState::RequestUniqueMappingId;

				if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UE_LOG(LogCs, Log, TEXT("ACsPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RequestLocalUniqueMappingId -> RequestUniqueMappingId"));
				}
			}
		}
		// Waiting for Local Unique Mapping Id
		if (OnBoardState == ECsPlayerStateOnBoardState::WaitingForLocalUniqueMappingId)
		{
		}
		// Received Local Unique Mapping Id
		if (OnBoardState == ECsPlayerStateOnBoardState::RecievedLocalUniqueMappingId)
		{
			OnBoardState = ECsPlayerStateOnBoardState::RequestUniqueMappingId;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RecievedLocalUniqueMappingId -> RequestUniqueMappingId"));
			}
		}
	}
	// Requesting Player State on Client
	{
		// Request Unique Mapping Id
		if (OnBoardState == ECsPlayerStateOnBoardState::RequestUniqueMappingId)
		{
			OnBoardState = ECsPlayerStateOnBoardState::WaitingForUniqueMappingId;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RequestUniqueMappingId -> WaitingForUniqueMappingId"));
			}
			ACsPlayerState* LocalPlayerState = UCsCommon::GetLocalPlayerState<ACsPlayerState>(GetWorld());

			ServerRequestUniqueMappingId(LocalPlayerState->UniqueMappingId, this);
		}
		// Waiting for Unique Mapping Id
		if (OnBoardState == ECsPlayerStateOnBoardState::WaitingForUniqueMappingId)
		{
		}
		// Received Unique Mapping Id
		if (OnBoardState == ECsPlayerStateOnBoardState::RecievedUniqueMappingId)
		{
			OnBoardState = ECsPlayerStateOnBoardState::RequestPlayerData;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RecievedUniqueMappingId -> RequestPlayerData"));
			}
		}
		// Request PlayerData
		if (OnBoardState == ECsPlayerStateOnBoardState::RequestPlayerData)
		{
			OnBoardState = ECsPlayerStateOnBoardState::WaitingForPlayerData;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RequestPlayerData -> WaitingForPlayerData"));
			}
			ACsPlayerState* LocalPlayerState = UCsCommon::GetLocalPlayerState<ACsPlayerState>(GetWorld());

			ServerRequestPlayerData(LocalPlayerState->UniqueMappingId, UniqueMappingId);
		}
		// Waiting for PlayerData
		if (OnBoardState == ECsPlayerStateOnBoardState::WaitingForPlayerData)
		{
		}
		// Received PlayerData
		if (OnBoardState == ECsPlayerStateOnBoardState::RecievedPlayerData)
		{
			OnBoardState = ECsPlayerStateOnBoardState::WaitingForGameStateOnBoardCompleted;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RecievedPlayerData -> WaitingForGameStateOnBoardCompleted"));
			}
		}
	}
	// Loading
	{
		// Waiting for GameState OnBoard to Complete
		if (OnBoardState == ECsPlayerStateOnBoardState::WaitingForGameStateOnBoardCompleted)
		{
			ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

			if (GameState->OnBoardState == ECsGameStateOnBoardState::Completed)
			{
				OnBoardState = ECsPlayerStateOnBoardState::BeginLoadingPlayerData;

				if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UE_LOG(LogCs, Log, TEXT("ACsPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: WaitingForGameStateOnBoardCompleted -> BeginLoadingPlayerData"));
				}
			}
		}
		// Begin Loading PlayerData
		if (OnBoardState == ECsPlayerStateOnBoardState::BeginLoadingPlayerData)
		{
			OnBoardState = ECsPlayerStateOnBoardState::WaitingForFinishLoadingPlayerData;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: BeginLoadingPlayerData -> WaitingForFinishLoadingPlayerData"));
			}
			LoadPlayerData();
		}
		// Waiting for Finish Loading PlayerData
		if (OnBoardState == ECsPlayerStateOnBoardState::WaitingForFinishLoadingPlayerData)
		{
		}
		// Finished Loading PlayerData
		if (OnBoardState == ECsPlayerStateOnBoardState::FinishedLoadingPlayerData)
		{
			OnBoardState = ECsPlayerStateOnBoardState::SendOnBoardCompleted;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: FinishedLoadingPlayerData -> SendOnBoardCompleted"));
			}
		}
	}
	// Handshaking
	{
		// Send Finished Replication and Loading
		if (OnBoardState == ECsPlayerStateOnBoardState::SendOnBoardCompleted)
		{
			OnBoardState = ECsPlayerStateOnBoardState::WaitingForOnBoardCompleted;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: SendOnBoardCompleted -> WaitingForOnBoardCompleted"));
			}
			ACsPlayerState* LocalPlayerState = UCsCommon::GetLocalPlayerState<ACsPlayerState>(GetWorld());

			ServerSendOnBoardCompleted(LocalPlayerState->UniqueMappingId, UniqueMappingId);
		}
		// Waiting for Finished Replication and Loading
		if (OnBoardState == ECsPlayerStateOnBoardState::WaitingForOnBoardCompleted)
		{
			if (IsOnBoardCompleted)
			{
				OnBoardState = ECsPlayerStateOnBoardState::Completed;
			}
		}
	}
}

bool ACsPlayerState::ServerRequestLocalUniqueMappingId_Validate(ACsPlayerState* ClientPlayerState)
{
	return true;
}

void ACsPlayerState::ServerRequestLocalUniqueMappingId_Implementation(ACsPlayerState* ClientPlayerState)
{
	// Check VALID ClientPlayerState
	if (!ClientPlayerState)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPlayerState::ServerRequestLocalUniqueMappingId: Client PlayerState is nullptr."));
		}
		return;
	}
	// Check Valid ClientMappingId
	if (ClientPlayerState->UniqueMappingId == CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPlayerState::ServerRequestLocalUniqueMappingId: %s's UniqueMappingId is INVALID."), *ClientPlayerState->PlayerName);
		}
		return;
	}
	if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ServerRequestLocalUniqueMappingId: %s is requesting UniqueMappingId: %d"), *ClientPlayerState->PlayerName, ClientPlayerState->UniqueMappingId);
	}
	ClientPlayerState->ClientRecieveLocalUniqueMappingId(ClientPlayerState->UniqueMappingId);
}

void ACsPlayerState::ClientRecieveLocalUniqueMappingId_Implementation(const uint8 &MappingId)
{
	UniqueMappingId = MappingId;

	ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

	GameState->PlayerStateMappings.Add(UniqueMappingId, this);

	if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ClientRecieveLocalUniqueMappingId: %s recieved UniqueMappingId: %d"), *PlayerName, MappingId);
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ClientRecieveLocalUniqueMappingId: State Change: WaitingForLocalUniqueMappingId -> RecievedLocalUniqueMappingId"));
	}
	OnBoardState = ECsPlayerStateOnBoardState::RecievedLocalUniqueMappingId;
}

bool ACsPlayerState::ServerRequestUniqueMappingId_Validate(const uint8 &ClientMappingId, ACsPlayerState* RequestingPlayerState)
{
	return true;
}

void ACsPlayerState::ServerRequestUniqueMappingId_Implementation(const uint8 &ClientMappingId, ACsPlayerState* RequestingPlayerState)
{
	// Check Valid ClientMappingId
	if (ClientMappingId == CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPlayerState::ServerRequestUniqueMappingId: ClientMappingId is INVALID."));
		}
		return;
	}

	ACsGameState* GameState			  = GetWorld()->GetGameState<ACsGameState>();
	ACsPlayerState* ClientPlayerState = GameState->GetPlayerState(ClientMappingId);

	// Check VALID ClientPlayerState
	if (!ClientPlayerState)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPlayerState::ServerRequestUniqueMappingId: Client PlayerState is nullptr."));
		}
		return;
	}
	// Check VALID RequestingPlayerState
	if (!RequestingPlayerState)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPlayerState::ServerRequestUniqueMappingId: %s is requesting PlayerState that is nullptr."), *ClientPlayerState->PlayerName);
		}
		return;
	}
	// Check VALID UniqueMappingId
	if (RequestingPlayerState->UniqueMappingId == CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPlayerState::ServerRequestUniqueMappingId: %s is requesting %s's UniqueMappingId is INVALID."), *ClientPlayerState->PlayerName, *RequestingPlayerState->PlayerName);
		}
		return;
	}

	if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ServerRequestUniqueMappingId: %s is requesting %s's UniqueMappingId: %d"), *ClientPlayerState->PlayerName, *RequestingPlayerState->PlayerName, RequestingPlayerState->UniqueMappingId);
	}
	ClientPlayerState->ClientRecieveUniqueMappingId(RequestingPlayerState, RequestingPlayerState->UniqueMappingId);
}

void ACsPlayerState::ClientRecieveUniqueMappingId_Implementation(ACsPlayerState* RequestingPlayerState, const uint8 &MappingId)
{
	RequestingPlayerState->UniqueMappingId = MappingId;

	ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

	GameState->PlayerStateMappings.Add(UniqueMappingId, RequestingPlayerState);

	if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ClientRecieveUniqueMappingId: %s recieved UniqueMappingId: %d"), *RequestingPlayerState->PlayerName, MappingId);
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ClientRecieveUniqueMappingId: State Change: WaitingForUniqueMappingId -> RecievedUniqueMappingId"));
	}
	RequestingPlayerState->OnBoardState = ECsPlayerStateOnBoardState::RecievedUniqueMappingId;
}

bool ACsPlayerState::ServerRequestPlayerData_Validate(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	return true;
}

void ACsPlayerState::ServerRequestPlayerData_Implementation(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	ServerRequestPlayerData_Internal(ClientMappingId, MappingId);
}

void ACsPlayerState::ServerRequestPlayerData_Internal(const uint8 &ClientMappingId, const uint8 &MappingId){}
void ACsPlayerState::GetLoadAssetsShortCodes(const TCsLoadAssetsType &AssetsType, TArray<FName> &OutShortCodes){}
void ACsPlayerState::LoadPlayerData(){}
void ACsPlayerState::OnFinishedLoadingPlayerData(const TArray<UObject*> &LoadedAssets, const float &LoadingTime){}

bool ACsPlayerState::ServerSendOnBoardCompleted_Validate(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	return true;
}

void ACsPlayerState::ServerSendOnBoardCompleted_Implementation(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

	GameState->SetPlayerStateMappingRelationshipFlag(ClientMappingId, MappingId);
}

void ACsPlayerState::MulticastSetIsOnBoardCompleted_Implementation()
{
	IsOnBoardCompleted = true;
}

void ACsPlayerState::MulticastUnSetIsOnBoardCompleted_Implementation()
{
	IsOnBoardCompleted = false;
}

bool ACsPlayerState::IsOnBoardCompleted_Game()
{
	if (!IsOnBoardCompleted)
		return false;

	ACsPlayerPawn* MyPawn = GetMyPawn();

	if (!MyPawn)
		return false;
	if (MyPawn->IsPendingKill())
		return false;
	if (Cast<ACsPlayerState>(MyPawn->PlayerState) != this)
		return false;

	if (ACsPlayerController* MyPlayerController = Cast<ACsPlayerController>(GetMyController()))
	{
		if (!MyPlayerController->PlayerState)
			return false;
		if (Cast<ACsPlayerState>(MyPlayerController->PlayerState) != this)
			return false;
	}
	return true;
}

#pragma endregion OnBoard