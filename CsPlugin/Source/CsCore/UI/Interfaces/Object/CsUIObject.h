// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsUIObject.generated.h"

UINTERFACE(BlueprintType, MinimalApi, meta = (CannotImplementInterfaceInBlueprint))
class UCsUIObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class ICsUIObject
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Show() = 0;
	
	virtual void Hide() = 0;

	virtual void Enable() = 0;

	virtual void Disable() = 0;
};