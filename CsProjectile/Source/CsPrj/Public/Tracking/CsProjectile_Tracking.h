// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsProjectile_Tracking.generated.h"

UINTERFACE(Blueprintable)
class CSPRJ_API UCsProjectile_Tracking : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSPRJ_API ICsProjectile_Tracking
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual bool Tracking_IsValid() const = 0;

	virtual bool Tracking_ReacquireDestination() = 0;

	virtual FVector Tracking_GetDestination() const = 0;
};