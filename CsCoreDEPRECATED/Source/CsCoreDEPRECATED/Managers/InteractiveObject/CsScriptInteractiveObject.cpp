// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/InteractiveObject/CsScriptInteractiveObject.h"
#include "CsCoreDEPRECATED.h"

UCsScriptInteractiveObject::UCsScriptInteractiveObject(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// ICsInteractiveObject
#pragma region

void ICsScriptInteractiveObject::Freeze()
{
	ICsScriptInteractiveObject::Execute_Script_Freeze((UObject*)this);
}

void ICsScriptInteractiveObject::UnFreeze()
{
	ICsScriptInteractiveObject::Execute_Script_UnFreeze((UObject*)this);
}

void ICsScriptInteractiveObject::Hold()
{
	ICsScriptInteractiveObject::Execute_Script_Hold((UObject*)this);
}

void ICsScriptInteractiveObject::Release()
{
	ICsScriptInteractiveObject::Execute_Script_Release((UObject*)this);
}

void ICsScriptInteractiveObject::Touch()
{
	ICsScriptInteractiveObject::Execute_Script_Touch((UObject*)this);
}

void ICsScriptInteractiveObject::Hover()
{
	ICsScriptInteractiveObject::Execute_Script_Hover((UObject*)this);
}

void ICsScriptInteractiveObject::UnHover()
{
	ICsScriptInteractiveObject::Execute_Script_UnHover((UObject*)this);
}

void ICsScriptInteractiveObject::Collide()
{
	ICsScriptInteractiveObject::Execute_Script_Collide((UObject*)this);
}

void ICsScriptInteractiveObject::UnCollide()
{
	ICsScriptInteractiveObject::Execute_Script_UnCollide((UObject*)this);
}

void ICsScriptInteractiveObject::Remove()
{
	ICsScriptInteractiveObject::Execute_Script_Remove((UObject*)this);
}

#pragma endregion ICsInteractiveObject