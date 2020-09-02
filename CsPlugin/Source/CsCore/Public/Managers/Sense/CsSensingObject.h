// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

	virtual FVector GetLocation() = 0;

	virtual FVector GetCustomLocation(const FName& InName) = 0;

	virtual FVector GetDirection() = 0;

	virtual FVector GetCustomDirection(const FName& InName) = 0;
};