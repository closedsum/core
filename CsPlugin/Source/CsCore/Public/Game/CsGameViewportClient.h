// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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