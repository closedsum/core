// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "CsScriptInteractiveObject.h"
#include "CsInteractive.h"

UCsScriptInteractiveObject::UCsScriptInteractiveObject(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// ICsInteractiveObject
#pragma region

void ICsScriptInteractiveObject::Freeze()
{
	ICsScriptInteractiveObject::Execute_Script_Freeze(_getUObject());
}

void ICsScriptInteractiveObject::UnFreeze()
{
	ICsScriptInteractiveObject::Execute_Script_UnFreeze(_getUObject());
}

void ICsScriptInteractiveObject::Hold()
{
	ICsScriptInteractiveObject::Execute_Script_Hold(_getUObject());
}

void ICsScriptInteractiveObject::Release()
{
	ICsScriptInteractiveObject::Execute_Script_Release(_getUObject());
}

void ICsScriptInteractiveObject::Touch()
{
	ICsScriptInteractiveObject::Execute_Script_Touch(_getUObject());
}

void ICsScriptInteractiveObject::Hover()
{
	ICsScriptInteractiveObject::Execute_Script_Hover(_getUObject());
}

void ICsScriptInteractiveObject::UnHover()
{
	ICsScriptInteractiveObject::Execute_Script_UnHover(_getUObject());
}

void ICsScriptInteractiveObject::Collide()
{
	ICsScriptInteractiveObject::Execute_Script_Collide(_getUObject());
}

void ICsScriptInteractiveObject::UnCollide()
{
	ICsScriptInteractiveObject::Execute_Script_UnCollide(_getUObject());
}

void ICsScriptInteractiveObject::Remove()
{
	ICsScriptInteractiveObject::Execute_Script_Remove(_getUObject());
}

#pragma endregion ICsInteractiveObject