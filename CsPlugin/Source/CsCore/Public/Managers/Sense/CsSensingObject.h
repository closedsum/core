// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"

#include "CsSensingObject.generated.h"

UINTERFACE(BlueprintType, MinimalApi, meta = (CannotImplementInterfaceInBlueprint))
class UCsSensingObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class ICsSensingObject
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual FVector3f GetLocation() = 0;

	virtual FVector3f GetCustomLocation(const FName& InName) = 0;

	virtual FVector3f GetDirection() = 0;

	virtual FVector3f GetCustomDirection(const FName& InName) = 0;
};