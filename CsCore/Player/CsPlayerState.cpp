// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsPlayerState.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Game/CsGameState.h"

#include "Player/CsPlayerController.h"
#include "Player/CsPlayerPawn.h"

ACsPlayerState::ACsPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick				 = true;
	PrimaryActorTick.bStartWithTickEnabled		 = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;
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

ACsPawn* ACsPlayerState::GetMyPawn()
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

void ACsPlayerState::ClientRecieveLocalUniqueMappingId_Internal(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState)
{
	UniqueMappingId = ClientMappingId;

	ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

	GameState->PlayerStateMappings.Add(UniqueMappingId, this);

	if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ClientRecieveLocalUniqueMappingId: %s recieved UniqueMappingId: %d"), *PlayerName, ClientMappingId);
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ClientRecieveLocalUniqueMappingId: State Change: WaitingForLocalUniqueMappingId -> RecievedLocalUniqueMappingId"));
	}
	RequestingPlayerState->OnBoardState = ECsPlayerStateBaseOnBoardState::RecievedLocalUniqueMappingId;
}

void ACsPlayerState::ServerRequestUniqueMappingId_Internal(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState)
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

void ACsPlayerState::ClientRecieveUniqueMappingId_Internal(const uint8 &MappingId)
{
	UniqueMappingId = MappingId;

	ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

	GameState->PlayerStateMappings.Add(MappingId, this);

	if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ClientRecieveUniqueMappingId: %s recieved UniqueMappingId: %d"), *PlayerName, MappingId);
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ClientRecieveUniqueMappingId: State Change: WaitingForUniqueMappingId -> RecievedUniqueMappingId"));
	}
	OnBoardState = ECsPlayerStateBaseOnBoardState::RecievedUniqueMappingId;
}

void ACsPlayerState::ServerSendOnBoardCompleted_Internal(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

	GameState->SetPlayerStateMappingRelationshipFlag(ClientMappingId, MappingId);
}

bool ACsPlayerState::IsOnBoardCompleted_Game()
{
	if (!IsOnBoardCompleted)
		return false;

	ACsPlayerPawn* MyPawn = Cast<ACsPlayerPawn>(GetMyPawn());

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