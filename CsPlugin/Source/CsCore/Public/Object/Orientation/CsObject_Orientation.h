// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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

	virtual FRotator3f Orientation_GetRotation() const = 0;

	virtual FVector3f Orientation_GetDirection() const = 0;

	virtual FVector3f Orientation_GetForward() const = 0;

	virtual FVector3f Orientation_GetRight() const = 0;
};