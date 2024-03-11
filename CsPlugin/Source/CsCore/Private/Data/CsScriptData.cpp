// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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
	bool OutSuccess = false;
	return ICsScriptData::Execute_Script_IsValid(_getUObject(), LoadFlags, OutSuccess);
}

void ICsScriptData::Load(const int32& LoadFlags)
{
	bool OutSuccess = false;
	ICsScriptData::Execute_Script_Load(_getUObject(), LoadFlags, OutSuccess);
}

void ICsScriptData::Unload()
{
	bool OutSuccess = false;
	ICsScriptData::Execute_Script_Unload(_getUObject(), OutSuccess);
}

bool ICsScriptData::IsLoaded() const
{
	bool OutSuccess = false;
	return ICsScriptData::Execute_Script_IsLoaded(_getUObject(), OutSuccess);
}

#pragma endregion ICsScriptData
