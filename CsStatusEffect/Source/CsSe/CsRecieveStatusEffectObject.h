// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsRecieveStatusEffectObject.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSSE_API UCsRecieveStatusEffectObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

struct ICsStatusEffectEvent;

/**
*/
class CSSE_API ICsRecieveStatusEffectObject
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void ApplyStatusEffect(const ICsStatusEffectEvent* Event) = 0;
};