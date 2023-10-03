// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsScriptData.h"
#include "CsCore.h"

UCsScriptData::UCsScriptData(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// ICsScriptData
#pragma region

bool ICsScriptData::IsValid(const int32& LoadFlags)
{
	return ICsScriptData::Execute_Script_IsValid(_getUObject(), LoadFlags);
}

void ICsScriptData::Load(const int32& LoadFlags)
{
	ICsScriptData::Execute_Script_Load(_getUObject(), LoadFlags);
}

void ICsScriptData::Unload()
{
	ICsScriptData::Execute_Script_Unload(_getUObject());
}

bool ICsScriptData::IsLoaded() const
{
	return ICsScriptData::Execute_Script_IsLoaded(_getUObject());
}

#pragma endregion ICsScriptData
