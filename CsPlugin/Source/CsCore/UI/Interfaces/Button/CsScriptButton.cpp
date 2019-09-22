// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "UI/Interfaces/Button/CsScriptButton.h"
#include "CsCore.h"

UCsScriptButton::UCsScriptButton(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// ICsButton
#pragma region

void ICsScriptButton::Press()
{
	ICsScriptButton::Execute_Script_Press((UObject*)this);
}

void ICsScriptButton::Release()
{
	ICsScriptButton::Execute_Script_Release((UObject*)this);
}

#pragma endregion ICsButton