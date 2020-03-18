// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsPlayerState.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Game/CsGameState_DEPRECATED.h"

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

// Routines
#pragma region


bool ACsPlayerState::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	if (Super::AddRoutine_Internal(Routine, Type))
		return true;
	return false;
}

bool ACsPlayerState::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	if (Super::RemoveRoutine_Internal(Routine, Type))
		return true;
	return false;
}

#pragma endregion Routines

// OnBoard
#pragma region

void ACsPlayerState::ClientRecieveLocalUniqueMappingId_Internal(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState)
{
	UniqueMappingId = ClientMappingId;

	ACsGameState_DEPRECATED* GameState = GetWorld()->GetGameState<ACsGameState_DEPRECATED>();

	GameState->PlayerStateMappings.Add(UniqueMappingId, this);

	if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ClientRecieveLocalUniqueMappingId: %s recieved UniqueMappingId: %d"), *GetPlayerName(), ClientMappingId);
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ClientRecieveLocalUniqueMappingId: State Change: WaitingForLocalUniqueMappingId -> RecievedLocalUniqueMappingId"));
	}
	RequestingPlayerState->OnBoardState = ECsPlayerStateBaseOnBoardState::RecievedLocalUniqueMappingId;
}

	// Requesting Player State on Client
#pragma region

		// Player
#pragma region

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

	ACsGameState_DEPRECATED* GameState			  = GetWorld()->GetGameState<ACsGameState_DEPRECATED>();
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
			UE_LOG(LogCs, Warning, TEXT("ACsPlayerState::ServerRequestUniqueMappingId: %s is requesting PlayerState that is nullptr."), *ClientPlayerState->GetPlayerName());
		}
		return;
	}
	// Check VALID UniqueMappingId
	if (RequestingPlayerState->UniqueMappingId == CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPlayerState::ServerRequestUniqueMappingId: %s is requesting %s's UniqueMappingId is INVALID."), *ClientPlayerState->GetPlayerName(), *RequestingPlayerState->GetPlayerName());
		}
		return;
	}

	if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ServerRequestUniqueMappingId: %s is requesting %s's UniqueMappingId: %d"), *ClientPlayerState->GetPlayerName(), *RequestingPlayerState->GetPlayerName(), RequestingPlayerState->UniqueMappingId);
	}
	ClientPlayerState->ClientRecieveUniqueMappingId(RequestingPlayerState, RequestingPlayerState->UniqueMappingId);
}

void ACsPlayerState::ClientRecieveUniqueMappingId_Internal(const uint8 &MappingId)
{
	UniqueMappingId = MappingId;

	ACsGameState_DEPRECATED* GameState = GetWorld()->GetGameState<ACsGameState_DEPRECATED>();

	GameState->PlayerStateMappings.Add(MappingId, this);

	if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ClientRecieveUniqueMappingId: %s recieved UniqueMappingId: %d"), *GetPlayerName(), MappingId);
		UE_LOG(LogCs, Log, TEXT("ACsPlayerState::ClientRecieveUniqueMappingId: State Change: WaitingForUniqueMappingId -> RecievedUniqueMappingId"));
	}
	OnBoardState = ECsPlayerStateBaseOnBoardState::RecievedUniqueMappingId;
}

#pragma endregion Player
		
		// AI
#pragma region

void ACsPlayerState::ServerRequestUniqueMappingId_AI_Internal(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState)
{
	// Check Valid ClientMappingId
	if (ClientMappingId == CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsAIPlayerState::ServerRequestUniqueMappingId_AI: ClientMappingId is INVALID."));
		}
		return;
	}

	ACsGameState_DEPRECATED* GameState			  = GetWorld()->GetGameState<ACsGameState_DEPRECATED>();
	ACsPlayerState* ClientPlayerState = GameState->GetPlayerState(ClientMappingId);

	// Check VALID ClientPlayerState
	if (!ClientPlayerState)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsAIPlayerState::ServerRequestUniqueMappingId_AI: Client PlayerState is nullptr."));
		}
		return;
	}
	// Check VALID RequestingPlayerState
	if (!RequestingPlayerState)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsAIPlayerState::ServerRequestUniqueMappingId_AI: %s is requesting PlayerState that is nullptr."), *ClientPlayerState->GetPlayerName());
		}
		return;
	}
	// Check VALID UniqueMappingId
	if (RequestingPlayerState->UniqueMappingId == CS_INVALID_PLAYER_STATE_UNIQUE_MAPPING_ID)
	{
		if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsAIPlayerState::ServerRequestUniqueMappingId_AI: %s is requesting %s's UniqueMappingId is INVALID."), *ClientPlayerState->GetPlayerName(), *RequestingPlayerState->GetPlayerName());
		}
		ClientPlayerState->RequestUniqueMappingId_AI(RequestingPlayerState);
		return;
	}

	if (CsCVarLogPlayerStateOnBoard->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("ACsAIPlayerState::ServerRequestUniqueMappingId_AI: %s is requesting %s's UniqueMappingId: %d"), *ClientPlayerState->GetPlayerName(), *RequestingPlayerState->GetPlayerName(), RequestingPlayerState->UniqueMappingId);
	}
	ClientPlayerState->ClientRecieveUniqueMappingId_AI(RequestingPlayerState, RequestingPlayerState->UniqueMappingId);
}

#pragma endregion AI

#pragma endregion Requesting Player State on Client

void ACsPlayerState::ServerSendOnBoardCompleted_Internal(const uint8 &ClientMappingId, const uint8 &MappingId)
{
	ACsGameState_DEPRECATED* GameState = GetWorld()->GetGameState<ACsGameState_DEPRECATED>();

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
	if (MyPawn->GetPlayerState<ACsPlayerState>() != this)
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