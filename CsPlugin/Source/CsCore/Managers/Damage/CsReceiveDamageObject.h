// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsReceiveDamageObject.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSCORE_API UCsReceiveDamageObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

struct ICsDamageEvent;

/**
*/
class CSCORE_API ICsReceiveDamageObject
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Damage(const ICsDamageEvent* Event) = 0;
};