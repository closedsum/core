// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"

#include "CsInteractiveObject.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSINTERACTIVE_API UCsInteractiveObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSINTERACTIVE_API ICsInteractiveObject
{
	GENERATED_IINTERFACE_BODY()
};