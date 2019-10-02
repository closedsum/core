// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsMenu.generated.h"

UINTERFACE(BlueprintType, MinimalApi, meta = (CannotImplementInterfaceInBlueprint))
class UCsMenu : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class ICsMenu
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Open() = 0;

	virtual bool IsOpened() = 0;

	virtual void Close() = 0;

	virtual bool IsClosed() = 0;
};