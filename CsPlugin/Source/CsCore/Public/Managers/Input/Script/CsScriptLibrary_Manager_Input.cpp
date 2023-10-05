// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Script/CsScriptLibrary_Manager_Input.h"
#include "CsCore.h"

// CVar
#include "Script/CsCVars_Script.h"
// Library
#include "Managers/Input/CsLibrary_Manager_Input.h"

namespace NCsScriptLibraryManagerInput
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, Get);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, GetChecked);
			// Init
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, Init);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, InitAll);
			// InputActionMap
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, SetFirstInputActionMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, SetInputActionMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, ClearFirstInputActionMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, ClearInputActionMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, ResetFirstInputActionMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, ResetInputActionMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, ResetAllInputActionMap);
		}
	}
}

UCsScriptLibrary_Manager_Input::UCsScriptLibrary_Manager_Input(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define LogError &FCsLog::Error
#define InputManagerLibrary NCsInput::NManager::FLibrary
#define InputActionMapLibrary NCsInput::NManager::NInputActionMap::FLibrary

// Get
#pragma region

UCsManager_Input* UCsScriptLibrary_Manager_Input::Get(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Get : Context;

	return InputManagerLibrary::GetSafe(Ctxt, WorldContextObject, ControllerId);
}

UCsManager_Input* UCsScriptLibrary_Manager_Input::GetChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, bool& OutSuccess)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Get : Context;

	return CS_SCRIPT_GET_CHECKED(InputManagerLibrary::GetChecked(Ctxt, WorldContextObject, ControllerId), InputManagerLibrary::GetSafe(Ctxt, WorldContextObject, ControllerId, OutSuccess, LogError));
}

#pragma endregion Get

bool UCsScriptLibrary_Manager_Input::Init(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Init : Context;

	return InputManagerLibrary::SafeInit(Ctxt, WorldContextObject, ControllerId);
}

bool UCsScriptLibrary_Manager_Input::InitAll(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::InitAll : Context;

	return InputManagerLibrary::SafeInit(Ctxt, WorldContextObject);
}

// InputActionMap
#pragma region

	// Set
#pragma region

bool UCsScriptLibrary_Manager_Input::SetFirstInputActionMap(const FString& Context, const UObject* WorldContextObject, const FECsInputActionMap& Map)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFirstInputActionMap : Context;

	return InputActionMapLibrary::SetSafeFirst(Ctxt, WorldContextObject, Map);
}

bool UCsScriptLibrary_Manager_Input::SetInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FECsInputActionMap& Map)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetInputActionMap : Context;

	return InputActionMapLibrary::SetSafe(Ctxt, WorldContextObject, ControllerId, Map);
}

#pragma endregion Set

	// Clear
#pragma region

bool UCsScriptLibrary_Manager_Input::ClearFirstInputActionMap(const FString& Context, const UObject* WorldContextObject, const FECsInputActionMap& Map)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ClearFirstInputActionMap : Context;

	return InputActionMapLibrary::SafeClearFirst(Ctxt, WorldContextObject, Map);
}

bool UCsScriptLibrary_Manager_Input::ClearInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FECsInputActionMap& Map)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ClearInputActionMap : Context;

	return InputActionMapLibrary::SafeClear(Ctxt, WorldContextObject, ControllerId, Map);
}

#pragma endregion Clear

	// Reset
#pragma region

bool UCsScriptLibrary_Manager_Input::ResetFirstInputActionMap(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ResetFirstInputActionMap : Context;

	return InputActionMapLibrary::SafeResetFirst(Ctxt, WorldContextObject);
}

bool UCsScriptLibrary_Manager_Input::ResetInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ResetInputActionMap : Context;

	return InputActionMapLibrary::SafeReset(Ctxt, WorldContextObject, ControllerId);
}

bool UCsScriptLibrary_Manager_Input::ResetAllInputActionMap(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ResetAllInputActionMap : Context;

	return InputActionMapLibrary::SafeReset(Ctxt, WorldContextObject);
}

#pragma endregion Reset

#pragma endregion InputActionMap

#undef LogError
#undef InputManagerLibrary
#undef InputActionMapLibrary