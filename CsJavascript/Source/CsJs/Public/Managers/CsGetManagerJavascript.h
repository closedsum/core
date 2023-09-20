// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerJavascript.generated.h"

class UCsManager_Javascript;

UINTERFACE(Blueprintable)
class CSJS_API UCsGetManagerJavascript : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSJS_API ICsGetManagerJavascript
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Javascript* GetManager_Javascript() const = 0;

	virtual void SetManager_Javascript(UCsManager_Javascript* InManager) = 0;
};