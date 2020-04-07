// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Components/ActorComponent.h"
#include "Managers/AI/Navigation/CsTypes_AI_Navigation.h"
#include "CsManager_AI_Navigation.generated.h"

#define CS_AI_NAV_MAX_REQUESTS_PROCESSED_PER_TICK 128

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsManagerAINavProjectPointTaskInfo
{
	GENERATED_USTRUCT_BODY()

	int32 MaxRequestsProcessedPerTick;

	uint64 CountLifetime;

	TMap<uint64, uint64> CountLifetimeByObjectId;

	int32 CountThisFrame;

	TMap<uint64, uint16> CountThisFrameByObjectId;

	FCsManagerAINavProjectPointTaskInfo() :
		MaxRequestsProcessedPerTick(CS_AI_NAV_MAX_REQUESTS_PROCESSED_PER_TICK),
		CountLifetime(0),
		CountLifetimeByObjectId(),
		CountThisFrame(0),
		CountThisFrameByObjectId()
	{
	}
};

UCLASS()
class CSCOREDEPRECATED_API UCsManager_AI_Navigation : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region
protected:

	virtual void OnRegister() override;

#pragma endregion UActorComponent Interface

// Singleton
#pragma region

public:

	static UCsManager_AI_Navigation* Get();
	static void Init(UCsManager_AI_Navigation* Manager);
	static void Shutdown();

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_AI_Navigation* s_Instance;
	static bool s_bShutdown;

#pragma endregion Singleton

public:

	virtual void OnTick(const float& DeltaSeconds);

// Project Point
#pragma region
public:

	FCsManagerAINavProjectPointTaskInfo ProjectPointTaskInfo;

	FCsAINavProjectPointResponse ProjectPoint(const FCsAINavProjectPointRequest& Request);

#pragma endregion Project Point

// Find Path
#pragma region
public:

	FCsAINavFindPathResponse FindPath(const FCsAINavFindPathRequest& Request);

#pragma endregion Find Path
};