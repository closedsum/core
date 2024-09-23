// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetJavascriptInstance.generated.h"

class FJavascriptInstance;

UINTERFACE(Blueprintable)
class CSJS_API UCsGetJavascriptInstance : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSJS_API ICsGetJavascriptInstance
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual TSharedPtr<FJavascriptInstance>& GetJavascriptInstance() = 0;
};