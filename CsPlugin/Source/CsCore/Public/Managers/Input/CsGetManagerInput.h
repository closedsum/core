// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerInput.generated.h"

class ICsManager_Input;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetManagerInput : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetManagerInput
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual ICsManager_Input* GetManager_Input() const = 0;

	virtual void SetManager_Input(ICsManager_Input* InManager) = 0;
};