// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/CsAIPlayerState.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "Game/CsGameState.h"

#include "AI/CsAIController.h"
#include "AI/Pawn/CsAIPawn.h"

ACsAIPlayerState::ACsAIPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick				 = true;
	PrimaryActorTick.bStartWithTickEnabled		 = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;
}

AController* ACsAIPlayerState::GetMyController()
{
	if (MyController.IsValid() && MyController.Get())
		return MyController.Get();

	for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		AController* Controller = It->Get();

		if (Cast<ACsAIController>(Controller) &&
			Cast<ACsAIController>(Controller)->PlayerState == this)
		{
			MyController = Controller;
			break;
		}
	}
	return MyController.Get();
}

// OnBoard
#pragma region

void ACsAIPlayerState::OnTick_OnBoard()
{
	// Waiting for GameState
	if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForGameState)
	{
		if (ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>())
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::WaitingForFinishLoadingCommonData;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::OnTick_OnBoard: State Change: WaitingForGameState -> WaitingForFinishLoadingCommonData"));
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
				UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: WaitingForFinishLoadingCommonData -> WaitingForLocalPlayerState"));
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
					UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: WaitingForLocalPlayerState -> RequestUniqueMappingId"));
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
						UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RequestLocalUniqueMappingId -> WaitingForLocalUniqueMappingId"));
					}
					LocalPlayerState->ServerRequestLocalUniqueMappingId(LocalPlayerState, this);
				}
			}
			else
			{
				OnBoardState = ECsPlayerStateBaseOnBoardState::RequestUniqueMappingId;

				if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RequestLocalUniqueMappingId -> RequestUniqueMappingId"));
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
					UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RequestLocalUniqueMappingId -> RequestUniqueMappingId"));
				}
			}
		}
		// Received Local Unique Mapping Id
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::RecievedLocalUniqueMappingId)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::RequestUniqueMappingId;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RecievedLocalUniqueMappingId -> RequestUniqueMappingId"));
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
				UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RequestUniqueMappingId -> WaitingForUniqueMappingId"));
			}
			ACsPlayerStateBase* LocalPlayerState = UCsCommon::GetLocalPlayerState<ACsPlayerStateBase>(GetWorld());

			LocalPlayerState->ServerRequestUniqueMappingId_AI(LocalPlayerState->UniqueMappingId, this);
		}
		// Waiting for Unique Mapping Id
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForUniqueMappingId)
		{
		}
		// Received Unique Mapping Id
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::RecievedUniqueMappingId)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::RequestAIData;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RecievedUniqueMappingId -> RequestAIData"));
			}
		}
		// Request AIData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::RequestAIData)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::WaitingForAIData;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RequestAIData -> WaitingForAIData"));
			}
			ACsPlayerStateBase* LocalPlayerState = UCsCommon::GetLocalPlayerState<ACsPlayerStateBase>(GetWorld());

			LocalPlayerState->ServerRequestAIData(LocalPlayerState->UniqueMappingId, UniqueMappingId);
		}
		// Waiting for AIData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForAIData)
		{
		}
		// Received AIData
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::ReceivedAIData)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::WaitingForGameStateOnBoardCompleted;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: ReceivedAIData -> WaitingForGameStateOnBoardCompleted"));
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
				OnBoardState = ECsPlayerStateBaseOnBoardState::SendOnBoardCompleted;

				if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
				{
					UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: WaitingForGameStateOnBoardCompleted -> BeginLoadingPlayerData"));
				}
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
				UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: SendOnBoardCompleted -> WaitingForOnBoardCompleted"));
			}
			ACsPlayerStateBase* LocalPlayerState = UCsCommon::GetLocalPlayerState<ACsPlayerStateBase>(GetWorld());

			LocalPlayerState->ServerSendOnBoardCompleted_AI(LocalPlayerState->UniqueMappingId, UniqueMappingId);
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

void ACsAIPlayerState::ClientRecieveUniqueMappingId_AI_Internal(const uint8 &MappingId)
{
	UniqueMappingId = MappingId;

	ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

	GameState->AIPlayerStateMappings.Add(MappingId, this);

	if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::ClientRecieveUniqueMappingId_AI: %s recieved UniqueMappingId: %d"), *GetPlayerName(), MappingId);
		UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::ClientRecieveUniqueMappingId_AI: State Change: WaitingForUniqueMappingId -> RecievedUniqueMappingId"));
	}
	OnBoardState = ECsPlayerStateBaseOnBoardState::RecievedUniqueMappingId;
}

void ACsAIPlayerState::ServerSendOnBoardCompleted_AI_Internal(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

	GameState->SetAIPlayerStateMappingRelationshipFlag(ClientMappingId, MappingId);
}

bool ACsAIPlayerState::IsOnBoardCompleted_Game()
{
	if (!IsOnBoardCompleted)
		return false;

	ACsAIPawn* MyPawn = Cast<ACsAIPawn>(GetMyPawn());

	if (!MyPawn)
		return false;
	if (MyPawn->IsPendingKill())
		return false;
	if (MyPawn->GetPlayerState<ACsAIPlayerState>() != this)
		return false;

	if (ACsAIController* MyPlayerController = Cast<ACsAIController>(GetMyController()))
	{
		if (!MyPlayerController->PlayerState)
			return false;
		if (Cast<ACsAIPlayerState>(MyPlayerController->PlayerState) != this)
			return false;
	}
	return true;
}

#pragma endregion OnBoard

// Snap Shot
#pragma region

void ACsAIPlayerState::AddQueuedGameEvent(const FECsGameEvent& Event)
{
	QueuedGameEventInfosForNextFrame.AddDefaulted();
	QueuedGameEventInfosForNextFrame.Last().Event = Event;
}

void ACsAIPlayerState::ProcessCurrentLocalSnapShot(const float &DeltaSeconds){}

#pragma endregion Snap Shot