// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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