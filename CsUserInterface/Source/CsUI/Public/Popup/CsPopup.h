// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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