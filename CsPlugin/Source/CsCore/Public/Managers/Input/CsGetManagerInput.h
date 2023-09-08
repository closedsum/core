// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerInput.generated.h"

class UCsManager_Input;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetManagerInput : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetManagerInput
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Input* GetManager_Input() const = 0;

	virtual void SetManager_Input(UCsManager_Input* InManager) = 0;
};