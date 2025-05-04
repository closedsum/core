// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Blackboard/Script/CsScriptLibrary_Blackboard.h"
#include "CsAI.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Blackboard/CsLibrary_Blackboard.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Blackboard)

// Cached
#pragma region

namespace NCsScriptLibraryBlackboard
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Blackboard, IsKeyType_Object);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Blackboard, IsKeyType_Vector);
			// Selector
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Blackboard, IsKeySelectorChecked_Object);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Blackboard::UCsScriptLibrary_Blackboard(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define BlackboardLibrary NCsBlackboard::FLibrary

bool UCsScriptLibrary_Blackboard::IsKeyType_Object(const FString& Context, UClass* KeyType)
{
	using namespace NCsScriptLibraryBlackboard::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsKeyType_Object : Context;

	return BlackboardLibrary::SafeIsKeyType_Object(Context, KeyType, nullptr);
}

bool UCsScriptLibrary_Blackboard::IsKeyType_Vector(const FString& Context, UClass* KeyType)
{
	using namespace NCsScriptLibraryBlackboard::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsKeyType_Vector : Context;

	return BlackboardLibrary::SafeIsKeyType_Vector(Context, KeyType, nullptr);
}


// Selector
#pragma region

bool UCsScriptLibrary_Blackboard::IsKeySelectorChecked_Object(const FString& Context, const FBlackboardKeySelector& Key)
{
	using namespace NCsScriptLibraryBlackboard::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsKeySelectorChecked_Object : Context;

	return CS_SCRIPT_GET_CHECKED(BlackboardLibrary::IsKeyChecked_Object(Ctxt, Key), BlackboardLibrary::SafeIsKey_Object(Ctxt, Key));
}

#pragma endregion Selector

#undef BlackboardLibrary