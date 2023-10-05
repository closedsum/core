// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerWidgetActor.generated.h"

class UCsManager_WidgetActor;

UINTERFACE(Blueprintable)
class CSUI_API UCsGetManagerWidgetActor : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSUI_API ICsGetManagerWidgetActor
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_WidgetActor* GetManager_WidgetActor() const = 0;

	virtual void SetManager_WidgetActor(UCsManager_WidgetActor* InManager) = 0;
};