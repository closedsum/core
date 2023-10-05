// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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