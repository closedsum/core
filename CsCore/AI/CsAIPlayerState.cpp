// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/CsAIPlayerState.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "Game/CsGameState.h"

#include "Player/CsPlayerController.h"
#include "Player/CsPlayerState.h"
#include "Player/CsPlayerPawn.h"

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

		if (Cast<ACsPlayerController>(Controller) &&
			Cast<ACsPlayerController>(Controller)->PlayerState == this)
		{
			MyController = Controller;
			break;
		}
	}
	return MyController.Get();
}

ACsPawn* ACsAIPlayerState::GetMyPawn()
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

			LocalPlayerState->ServerRequestUniqueMappingId(LocalPlayerState->UniqueMappingId, this);
		}
		// Waiting for Unique Mapping Id
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::WaitingForUniqueMappingId)
		{
		}
		// Received Unique Mapping Id
		if (OnBoardState == ECsPlayerStateBaseOnBoardState::RecievedUniqueMappingId)
		{
			OnBoardState = ECsPlayerStateBaseOnBoardState::SendOnBoardCompleted;

			if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
			{
				UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::OnTick_HandleInitialReplicationAndLoading: State Change: RecievedUniqueMappingId -> RequestPlayerData"));
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

void ACsAIPlayerState::ServerRequestUniqueMappingId_Internal(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState)
{
	// Check Valid ClientMappingId
	if (ClientMappingId == CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsAIPlayerState::ServerRequestUniqueMappingId: ClientMappingId is INVALID."));
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
			UE_LOG(LogCs, Warning, TEXT("ACsAIPlayerState::ServerRequestUniqueMappingId: Client PlayerState is nullptr."));
		}
		return;
	}
	// Check VALID RequestingPlayerState
	if (!RequestingPlayerState)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsAIPlayerState::ServerRequestUniqueMappingId: %s is requesting PlayerState that is nullptr."), *ClientPlayerState->PlayerName);
		}
		return;
	}
	// Check VALID UniqueMappingId
	if (RequestingPlayerState->UniqueMappingId == CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsAIPlayerState::ServerRequestUniqueMappingId: %s is requesting %s's UniqueMappingId is INVALID."), *ClientPlayerState->PlayerName, *RequestingPlayerState->PlayerName);
		}
		return;
	}

	if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ServerRequestUniqueMappingId: %s is requesting %s's UniqueMappingId: %d"), *ClientPlayerState->PlayerName, *RequestingPlayerState->PlayerName, RequestingPlayerState->UniqueMappingId);
	}
	ClientPlayerState->ClientRecieveUniqueMappingId(RequestingPlayerState, RequestingPlayerState->UniqueMappingId);
}

void ACsAIPlayerState::ClientRecieveUniqueMappingId_Internal(ACsPlayerStateBase* RequestingPlayerState, const uint8 &MappingId)
{
	RequestingPlayerState->UniqueMappingId = MappingId;

	ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

	GameState->PlayerStateMappings.Add(MappingId, Cast<ACsPlayerState>(RequestingPlayerState));

	if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ClientRecieveUniqueMappingId: %s recieved UniqueMappingId: %d"), *RequestingPlayerState->PlayerName, MappingId);
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ClientRecieveUniqueMappingId: State Change: WaitingForUniqueMappingId -> RecievedUniqueMappingId"));
	}
	RequestingPlayerState->OnBoardState = ECsPlayerStateBaseOnBoardState::RecievedUniqueMappingId;
}

void ACsAIPlayerState::ServerSendOnBoardCompleted_Internal(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

	GameState->SetAIPlayerStateMappingRelationshipFlag(ClientMappingId, MappingId);
}

bool ACsAIPlayerState::IsOnBoardCompleted_Game()
{
	if (!IsOnBoardCompleted)
		return false;

	ACsPlayerPawn* MyPawn = Cast<ACsPlayerPawn>(GetMyPawn());

	if (!MyPawn)
		return false;
	if (MyPawn->IsPendingKill())
		return false;
	if (Cast<ACsAIPlayerState>(MyPawn->PlayerState) != this)
		return false;

	if (ACsPlayerController* MyPlayerController = Cast<ACsPlayerController>(GetMyController()))
	{
		if (!MyPlayerController->PlayerState)
			return false;
		if (Cast<ACsAIPlayerState>(MyPlayerController->PlayerState) != this)
			return false;
	}
	return true;
}

#pragma endregion OnBoard