// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "CsGetCoroutineScheduler.generated.h"

class UCsCoroutineScheduler;

UINTERFACE(Blueprintable)
class UCsGetCoroutineScheduler : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetCoroutineScheduler
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsCoroutineScheduler* GetCoroutineScheduler() const = 0;

	virtual void SetCoroutineScheduler(UCsCoroutineScheduler* InScheduler) = 0;
};