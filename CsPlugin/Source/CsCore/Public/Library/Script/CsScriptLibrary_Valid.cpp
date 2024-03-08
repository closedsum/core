// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Valid.h"
#include "CsCore.h"

// CVar
#include "Script/CsCVars_Script.h"

// Cached
#pragma region

namespace NCsScriptLibraryValid
{
	namespace NCached
	{
		namespace Str
		{
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Valid::UCsScriptLibrary_Valid(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_Valid::Script_checkf(const bool& Expression, const FString& Message)
{
#if !UE_BUILD_SHIPPING
	if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked))
	{
		checkf(Expression, TEXT("%s"), *Message);	
	}
	else
	{
		if (!Expression)
		{
			UE_LOG(LogCs, Error, TEXT("%s"), *Message);
		}
	}
	return Expression;
#else
	return true;
#endif // #if !UE_BUILD_SHIPPING
}

bool UCsScriptLibrary_Valid::Script_check(const bool& Expression)
{
#if !UE_BUILD_SHIPPING
	if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked))
	{
		check(Expression);	
	}
	else
	{
		if (!Expression)
		{
			UE_LOG(LogCs, Error, TEXT("check FAILED"));
		}
	}
	return Expression;
#else
	return true;
#endif // #if !UE_BUILD_SHIPPING
}