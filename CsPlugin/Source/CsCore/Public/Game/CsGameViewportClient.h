// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/GameViewportClient.h"
#include "CsGameViewportClient.generated.h"

UCLASS()
class CSCORE_API UCsGameViewportClient : public UGameViewportClient
{
	GENERATED_UCLASS_BODY()

// FViewportClient Interface
#pragma region
public:

	virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;
	virtual bool InputAxis(FViewport* InViewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples = 1, bool bGamepad = false) override;

#pragma endregion FViewportClient Interface
};