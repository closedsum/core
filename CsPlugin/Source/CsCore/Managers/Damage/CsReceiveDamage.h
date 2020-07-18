// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsReceiveDamage.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSCORE_API UCsReceiveDamage : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

struct ICsDamageEvent;

/**
*/
class CSCORE_API ICsReceiveDamage
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Damage(const ICsDamageEvent* Event) = 0;
};