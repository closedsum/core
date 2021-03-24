// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"

#include "CsMenu.generated.h"

UINTERFACE(BlueprintType)
class CSUI_API UCsMenu : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSUI_API ICsMenu
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Open() = 0;
	virtual void Close() = 0;
};