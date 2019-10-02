// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UI/Interfaces/Menu/CsMenu.h"
#include "CsScriptMenu.generated.h"

UINTERFACE(Blueprintable, MinimalApi)
class UCsScriptMenu : public UCsMenu
{
	GENERATED_UINTERFACE_BODY()
};


class ICsScriptMenu : public ICsMenu
{
	GENERATED_IINTERFACE_BODY()

// ICsMenu
#pragma region

public:

	void Open();

	bool IsOpened();

	void Close();

	bool IsClosed();

#pragma endregion ICsMenu

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptMenu", meta = (DisplayName = "Open"))
	void Script_Open();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptMenu", meta = (DisplayName = "Is Opened"))
	bool Script_IsOpened();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptMenu", meta = (DisplayName = "Close"))
	void Script_Close();

	UFUNCTION(BlueprintImplementableEvent, Category = "ICsScriptMenu", meta = (DisplayName = "Is Closed"))
	bool Script_IsClosed();
};