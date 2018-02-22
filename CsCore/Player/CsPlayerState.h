// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Player/CsPlayerStateBase.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsPlayerState.generated.h"


UCLASS()
class CSCORE_API ACsPlayerState : public ACsPlayerStateBase
{
	GENERATED_UCLASS_BODY()

	virtual AController* GetMyController() override;

	virtual ACsPawn* GetMyPawn() override;

// OnBoard
#pragma region
public:

// Client

	virtual void ClientRecieveLocalUniqueMappingId_Internal(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState) override;

// Requesting Player State on Client

	virtual void ServerRequestUniqueMappingId_Internal(const uint8 &ClientMappingId, ACsPlayerStateBase* RequestingPlayerState) override;
	virtual void ClientRecieveUniqueMappingId_Internal(ACsPlayerStateBase* RequestingPlayerState, const uint8 &MappingId) override;

// Handshaking

	virtual void ServerSendOnBoardCompleted_Internal(const uint8 &ClientMappingId, const uint8 &MappingId) override;

	virtual bool IsOnBoardCompleted_Game() override;

#pragma endregion OnBoard
};