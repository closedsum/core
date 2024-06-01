// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Time/CsManager_Time.h"

// Types
#include "InputCoreTypes.h"

#include "CsManager_TimeImpl.generated.h"

UCLASS()
class CSCORE_API UCsManager_TimeImpl : public UCsManager_Time
{
	GENERATED_UCLASS_BODY()

public:

	void SetupInputListener();

	void OnAnyKey_Pressed(const FKey& Key);
	void OnAnyKey_Released(const FKey& Key);
};