// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerRunnable.generated.h"

class UCsManager_Runnable;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetManagerRunnable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetManagerRunnable
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Runnable* GetManager_Runnable() const = 0;

	virtual void SetManager_Runnable(UCsManager_Runnable* InManager) = 0;
};