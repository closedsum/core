// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "ICsMenu.generated.h"

UINTERFACE(BlueprintType)
class CSMENU_API UCsMenu : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSMENU_API ICsMenu
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Open() = 0;
	virtual void Close() = 0;
};