// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"

#include "CsGetCameraComponent.generated.h"

class UCameraComponent;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetCameraComponent : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetCameraComponent
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCameraComponent* GetCameraComponent() const = 0;
};