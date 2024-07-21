// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsManager_Input_WithGameplayTag.generated.h"

UINTERFACE(Blueprintable)
class CSINPUTWITHGAMEPLAYTAG_API UCsManager_Input_WithGameplayTag : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSINPUTWITHGAMEPLAYTAG_API ICsManager_Input_WithGameplayTag
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Init() = 0;

	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) = 0;
};