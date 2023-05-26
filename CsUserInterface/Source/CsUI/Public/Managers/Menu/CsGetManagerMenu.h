// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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