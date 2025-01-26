// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsObject_Orientation.generated.h"

UINTERFACE(Blueprintable)
class CSTYPES_API UCsObject_Orientation : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSTYPES_API ICsObject_Orientation
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual FRotator3d Orientation_GetRotation3d() const = 0;
	virtual FRotator3f Orientation_GetRotation3f() const = 0;

	virtual FVector3d Orientation_GetDirection3d() const = 0;
	virtual FVector3f Orientation_GetDirection3f() const = 0;

	virtual FVector3d Orientation_GetForward3d() const = 0;
	virtual FVector3f Orientation_GetForward3f() const = 0;

	virtual FVector3d Orientation_GetRight3d() const = 0;
	virtual FVector3f Orientation_GetRight3f() const = 0;
};