// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsProjectile_Movement.generated.h"

UINTERFACE(Blueprintable)
class CSPRJ_API UCsProjectile_Movement : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSPRJ_API ICsProjectile_Movement
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Movement_SetLocation(const FVector& Location) = 0;

	virtual FVector Movement_GetLocation() const = 0;

	virtual void Movement_SetRotation(const FRotator& Rotation) = 0;

	virtual void Movement_SetVelocity(const FVector& Velocity) = 0;
};