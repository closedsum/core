// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "UI/Interfaces/Object/CsScriptUIObject.h"
#include "CsCore.h"

UCsScriptUIObject::UCsScriptUIObject(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// ICsUIObject
#pragma region

void ICsScriptUIObject::Show()
{
	ICsScriptUIObject::Execute_Script_Show((UObject*)this);
}

void ICsScriptUIObject::Hide()
{
	ICsScriptUIObject::Execute_Script_Hide((UObject*)this);
}

void ICsScriptUIObject::Enable()
{
	ICsScriptUIObject::Execute_Script_Enable((UObject*)this);
}

void ICsScriptUIObject::Disable()
{
	ICsScriptUIObject::Execute_Script_Disable((UObject*)this);
}

#pragma endregion ICsUIObject