// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerFX.generated.h"

class UCsManager_FX;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetManagerFX : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSCORE_API ICsGetManagerFX
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_FX* GetManager_FX() const = 0;

	virtual void SetManager_FX(UCsManager_FX* InManager) = 0;
};