// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Player/CsPlayerStateBase.h"
#include "Types/CsTypes.h"
#include "CsAIPlayerState.generated.h"


UCLASS()
class CSCORE_API ACsAIPlayerState : public ACsPlayerStateBase
{
	GENERATED_UCLASS_BODY()

	virtual AController* GetMyController() override;

	virtual ACsPawn* GetMyPawn() override;

// OnBoard
#pragma region
public:

	virtual void OnTick_OnBoard() override;

	// Requesting Player State on Client
#pragma region

	virtual void ClientRecieveUniqueMappingId_AI_Internal(const uint8 &MappingId) override;

#pragma endregion Requesting Player State on Client

// Handshaking

	virtual void ServerSendOnBoardCompleted_AI_Internal(const uint8 &ClientMappingId, const uint8 &MappingId) override;

	virtual bool IsOnBoardCompleted_Game() override;

#pragma endregion OnBoard
};