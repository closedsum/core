// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "UI/Interfaces/Menu/CsScriptMenu.h"
#include "CsCore.h"

UCsScriptMenu::UCsScriptMenu(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// ICsMenu
#pragma region

void ICsScriptMenu::Open()
{
	ICsScriptMenu::Execute_Script_Open((UObject*)this);
}

bool ICsScriptMenu::IsOpened()
{
	return ICsScriptMenu::Execute_Script_IsOpened((UObject*)this);
}

void ICsScriptMenu::Close()
{
	ICsScriptMenu::Execute_Script_Close((UObject*)this);
}

bool ICsScriptMenu::IsClosed()
{
	return ICsScriptMenu::Execute_Script_IsClosed((UObject*)this);
}

#pragma endregion ICsMenu