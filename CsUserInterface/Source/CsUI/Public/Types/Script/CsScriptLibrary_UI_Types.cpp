
// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/Script/CsScriptLibrary_UI_Types.h"
#include "CsUI.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "Types/CsTypes_Macro.h"

// Cached
#pragma region

namespace NCsScriptLibraryUITypes
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_UI_Types, FCsUserWidget_GetClass);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_UI_Types, FCsUserWidget_GetClassChecked);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_UI_Types::UCsScriptLibrary_UI_Types(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define LogError &NCsUI::FLog::Error

UClass* UCsScriptLibrary_UI_Types::FCsUserWidget_GetClass(const FString& Context, const FCsUserWidget& A)
{
	using namespace NCsScriptLibraryUITypes::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::FCsUserWidget_GetClass : Context;

	return A.GetSafeClass(Ctxt);
}

UClass* UCsScriptLibrary_UI_Types::FCsUserWidget_GetClassChecked(const FString& Context, const FCsUserWidget& A, bool& OutSuccess)
{
	using namespace NCsScriptLibraryUITypes::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::FCsUserWidget_GetClass : Context;

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(A.GetClassChecked(Ctxt), A.GetSafeClass(Ctxt, OutSuccess, LogError));
}

#undef LogError