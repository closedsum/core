// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerUserWidget.generated.h"

class UCsManager_UserWidget;

UINTERFACE(Blueprintable)
class CSUI_API UCsGetManagerUserWidget : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSUI_API ICsGetManagerUserWidget
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_UserWidget* GetManager_UserWidget() const = 0;

	virtual void SetManager_UserWidget(UCsManager_UserWidget* InManager) = 0;
};