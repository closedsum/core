// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetCoordinatorStatusEffect.generated.h"

class UCsCoordinator_StatusEffect;

UINTERFACE(Blueprintable)
class CSSE_API UCsGetCoordinatorStatusEffect : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSSE_API ICsGetCoordinatorStatusEffect
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsCoordinator_StatusEffect* GetCoordinator_StatusEffect() const = 0;

	virtual void SetCoordinator_StatusEffect(UCsCoordinator_StatusEffect* InCoordinator) = 0;
};