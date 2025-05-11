// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Blackboard/Script/CsScriptLibrary_Blackboard.h"

// CVar
#include "Script/CsCVars_Script.h"
// Library
#include "Blackboard/CsLibrary_Blackboard.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Blackboard)

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsScriptLibrary_Blackboard)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Blackboard, IsKeyType_Object)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Blackboard, IsKeyType_Vector)
	// Selector
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Blackboard, IsKeySelectorChecked_Object)
CS_END_CACHED_FUNCTION_NAME

#pragma endregion Cached

UCsScriptLibrary_Blackboard::UCsScriptLibrary_Blackboard(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_Blackboard::IsKeyType_Object(const FString& Context, UClass* KeyType)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(IsKeyType_Object);

	return CsBlackboardLibrary::SafeIsKeyType_Object(Context, KeyType, nullptr);
}

bool UCsScriptLibrary_Blackboard::IsKeyType_Vector(const FString& Context, UClass* KeyType)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(IsKeyType_Vector);

	return CsBlackboardLibrary::SafeIsKeyType_Vector(Context, KeyType, nullptr);
}


// Selector
#pragma region

bool UCsScriptLibrary_Blackboard::IsKeySelectorChecked_Object(const FString& Context, const FBlackboardKeySelector& Key)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(IsKeySelectorChecked_Object);

	return CS_SCRIPT_GET_CHECKED(CsBlackboardLibrary::IsKeyChecked_Object(Ctxt, Key), CsBlackboardLibrary::SafeIsKey_Object(Ctxt, Key));
}

#pragma endregion Selector