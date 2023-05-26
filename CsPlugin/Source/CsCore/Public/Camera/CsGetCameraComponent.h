// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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