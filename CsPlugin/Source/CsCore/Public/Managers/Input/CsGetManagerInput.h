// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerInput.generated.h"

class UCsManager_Input;

UINTERFACE(Blueprintable)
class UCsGetManagerInput : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetManagerInput
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Input* GetManager_Input() const = 0;

	virtual void SetManager_Input(UCsManager_Input* InManager) = 0;
};