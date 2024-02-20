// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "GameFramework/Actor.h"

#include "CsLevel_Streaming_EventHandler.generated.h"

class ULevelStreaming;

/**
*/
UCLASS()
class CSCORE_API ACsLevel_Streaming_EventHandler : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	TWeakObjectPtr<ULevelStreaming> Level;

	ULevelStreaming* GetLevel() const;

	UFUNCTION()
	void OnLevelLoaded();

	UFUNCTION()
	void OnLevelUnloaded();

	UFUNCTION()
	void OnLevelShown();

	UFUNCTION()
	void OnLevelHidden();
};