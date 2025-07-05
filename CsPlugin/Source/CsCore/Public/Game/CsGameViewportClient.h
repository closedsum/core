// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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
	virtual bool InputAxis(const FInputKeyEventArgs& EventArgs) override;

#pragma endregion FViewportClient Interface
};