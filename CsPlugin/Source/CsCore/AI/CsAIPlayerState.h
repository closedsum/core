// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Player/CsPlayerStateBase.h"
#include "Managers/Input/CsTypes_Input.h"
#include "CsAIPlayerState.generated.h"


UCLASS()
class CSCORE_API ACsAIPlayerState : public ACsPlayerStateBase
{
	GENERATED_UCLASS_BODY()

	virtual AController* GetMyController() override;

// OnBoard
#pragma region
public:

	virtual void OnTick_OnBoard() override;

	// Requesting Player State on Client
#pragma region
public:

	virtual void ClientRecieveUniqueMappingId_AI_Internal(const uint8 &MappingId) override;

#pragma endregion Requesting Player State on Client

public:

	// Handshaking

	virtual void ServerSendOnBoardCompleted_AI_Internal(const uint8 &ClientMappingId, const uint8 &MappingId) override;

	virtual bool IsOnBoardCompleted_Game() override;

#pragma endregion OnBoard

// Snap Shot
#pragma region
public:

	UPROPERTY(BlueprintReadWrite, Category = "Snap Shot")
	TArray<FCsGameEventInfo> QueuedGameEventInfosForNextFrame;

	UFUNCTION(BlueprintCallable, Category = "Snap Shot")
	void AddQueuedGameEvent(const FECsGameEvent& Event);

	virtual void ProcessCurrentLocalSnapShot(const float &DeltaSeconds);

#pragma endregion Snap Shot
};