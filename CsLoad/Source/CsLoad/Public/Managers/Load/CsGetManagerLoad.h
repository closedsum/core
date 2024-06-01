// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerLoad.generated.h"

class UCsManager_Load;

UINTERFACE(Blueprintable)
class CSLOAD_API UCsGetManagerLoad : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSLOAD_API ICsGetManagerLoad
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Load* GetManager_Load() const = 0;

	virtual void SetManager_Load(UCsManager_Load* InManager) = 0;
};