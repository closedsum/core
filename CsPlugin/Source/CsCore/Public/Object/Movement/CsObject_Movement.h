// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsObject_Movement.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsObject_Movement : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsObject_Movement
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual FVector3d Movement_GetCenterOfMassLocation3d() const = 0;
	virtual FVector3f Movement_GetCenterOfMassLocation3f() const = 0;

	virtual FVector3d Movement_GetBaseOnGroundLocation3d() const = 0;
	virtual FVector3f Movement_GetBaseOnGroundLocation3f() const = 0;
};