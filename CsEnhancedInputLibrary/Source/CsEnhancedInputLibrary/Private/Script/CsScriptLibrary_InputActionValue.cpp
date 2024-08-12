// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Script/CsScriptLibrary_InputActionValue.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "CsLibrary_InputActionValue.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_InputActionValue)

// Cached
#pragma region

namespace NCsScriptLibraryInputActionValue
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_InputActionValue, GetBool);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_InputActionValue, GetBoolChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_InputActionValue, GetFloat);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_InputActionValue, GetFloatChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_InputActionValue, GetVector2D);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_InputActionValue, GetVector2DChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_InputActionValue, GetVector);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_InputActionValue, GetVectorChecked);
		}
	}
}

#pragma endregion Cached

void(*UCsScriptLibrary_InputActionValue::LogError)(const FString&) = &NCsInput::NEnhanced::NLibrary::FLog::Error;

UCsScriptLibrary_InputActionValue::UCsScriptLibrary_InputActionValue(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryInputActionValue::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryInputActionValue::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

bool UCsScriptLibrary_InputActionValue::GetBool(const FString& Context, const FInputActionValue& Value)
{
	CONDITIONAL_SET_CTXT(GetBool);

	return CsInputActionValueLibrary::GetSafeBool(Ctxt, Value);
}

bool UCsScriptLibrary_InputActionValue::GetBoolChecked(const FString& Context, const FInputActionValue& Value, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetBoolChecked);

	OutSuccess = true;
	return CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_4(GetBoolChecked, GetSafeBool, Value);
}

float UCsScriptLibrary_InputActionValue::GetFloat(const FString& Context, const FInputActionValue& Value)
{
	CONDITIONAL_SET_CTXT(GetFloat);

	return CsInputActionValueLibrary::GetSafeFloat(Ctxt, Value);
}

float UCsScriptLibrary_InputActionValue::GetFloatChecked(const FString& Context, const FInputActionValue& Value, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetFloatChecked);

	OutSuccess = true;
	return CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_4(GetFloatChecked, GetSafeFloat, Value);
}

FVector2D UCsScriptLibrary_InputActionValue::GetVector2D(const FString& Context, const FInputActionValue& Value)
{
	CONDITIONAL_SET_CTXT(GetVector2D);

	return CsInputActionValueLibrary::GetSafeVector2D(Ctxt, Value);
}

FVector2D UCsScriptLibrary_InputActionValue::GetVector2DChecked(const FString& Context, const FInputActionValue& Value, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetVector2DChecked);

	OutSuccess = true;
	return CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_4(GetVector2DChecked, GetSafeVector2D, Value);
}

FVector UCsScriptLibrary_InputActionValue::GetVector(const FString& Context, const FInputActionValue& Value)
{
	CONDITIONAL_SET_CTXT(GetVector);

	return CsInputActionValueLibrary::GetSafeVector(Ctxt, Value);
}

FVector UCsScriptLibrary_InputActionValue::GetVectorChecked(const FString& Context, const FInputActionValue& Value, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetVectorChecked);

	OutSuccess = true;
	return CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_4(GetVectorChecked, GetSafeVector, Value);
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT