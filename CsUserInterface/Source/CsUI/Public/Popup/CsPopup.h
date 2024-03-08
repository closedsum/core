// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsPopup.generated.h"

UINTERFACE(BlueprintType)
class CSUI_API UCsPopup : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSUI_API ICsPopup
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Open() = 0;
	virtual void Close() = 0;
};