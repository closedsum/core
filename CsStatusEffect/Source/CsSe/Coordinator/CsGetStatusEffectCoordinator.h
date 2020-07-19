// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetStatusEffectCoordinator.generated.h"

class UCsStatusEffectCoordinator;

UINTERFACE(Blueprintable)
class CSSE_API UCsGetStatusEffectCoordinator : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSSE_API ICsGetStatusEffectCoordinator
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsStatusEffectCoordinator* GetStatusEffectCoordinator() const = 0;

	virtual void SetStatusEffectCoordinator(UCsStatusEffectCoordinator* InCoordinator) = 0;
};