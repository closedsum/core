// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerMenu.generated.h"

class UCsManager_Menu;

UINTERFACE(Blueprintable)
class UCsGetManagerMenu : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetManagerMenu
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Menu* GetManager_Menu() const = 0;

	virtual void SetManager_Menu(UCsManager_Menu* InManager) = 0;
};