// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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