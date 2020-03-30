// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsButton.generated.h"

UINTERFACE(BlueprintType, MinimalApi, meta = (CannotImplementInterfaceInBlueprint))
class UCsButton : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class ICsButton
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Press() = 0;

	virtual void Release() = 0;
};