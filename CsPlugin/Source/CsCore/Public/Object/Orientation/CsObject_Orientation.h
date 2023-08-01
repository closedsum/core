// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsObject_Orientation.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsObject_Orientation : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsObject_Orientation
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual FRotator Orientation_GetRotation() const = 0;

	virtual FVector Orientation_GetDirection() const = 0;

	virtual FVector Orientation_GetForward() const = 0;

	virtual FVector Orientation_GetRight() const = 0;
};