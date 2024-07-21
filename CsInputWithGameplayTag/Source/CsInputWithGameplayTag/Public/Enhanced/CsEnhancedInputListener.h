// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "InputAction.h"

#include "CsEnhancedInputListener.generated.h"

UCLASS()
class CSINPUTWITHGAMEPLAYTAG_API UCsEnhancedInputListener : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	void Init(const int32& Index);

private:

	int32 ActionIndex;

public:

	void OnAction(const FInputActionInstance& ActionInstance);

	DECLARE_DELEGATE_TwoParams(FOnAction, const int32& /*ActionIndex*/,const FInputActionInstance& /*ActionInstance*/);

	FOnAction OnAction_Event;
};