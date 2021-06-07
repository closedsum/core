// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/Script/CsScriptLibrary_Manager_Input.h"
#include "CsCore.h"

// Library
#include "Managers/Input/CsLibrary_Manager_Input.h"

namespace NCsScriptLibraryManagerInput
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, Init);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, SetFirstInputActionMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, SetInputActionMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, ClearFirstInputActionMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, ClearInputActionMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, ResetFirstInputActionMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, ResetInputActionMap);
		}
	}
}

UCsScriptLibrary_Manager_Input::UCsScriptLibrary_Manager_Input(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_Manager_Input::Init(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFirstInputActionMap : Context;

	typedef NCsInput::NManager::FLibrary InputManagerLibrary;

	return InputManagerLibrary::SafeInit(Context, WorldContextObject, ControllerId);
}

// InputActionMap
#pragma region

	// Set
#pragma region

void UCsScriptLibrary_Manager_Input::SetFirstInputActionMap(const FString& Context, const UObject* WorldContextObject, const FECsInputActionMap& Map)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFirstInputActionMap : Context;

	typedef NCsInput::NManager::NInputActionMap::FLibrary InputActionMapLibrary;

	InputActionMapLibrary::SetSafeFirst(Ctxt, WorldContextObject, Map);
}

void UCsScriptLibrary_Manager_Input::SetInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FECsInputActionMap& Map)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetInputActionMap : Context;

	typedef NCsInput::NManager::NInputActionMap::FLibrary InputActionMapLibrary;

	InputActionMapLibrary::SetSafe(Ctxt, WorldContextObject, ControllerId, Map);
}

#pragma endregion Set

// Clear
#pragma region

void UCsScriptLibrary_Manager_Input::ClearFirstInputActionMap(const FString& Context, const UObject* WorldContextObject, const FECsInputActionMap& Map)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ClearFirstInputActionMap : Context;

	typedef NCsInput::NManager::NInputActionMap::FLibrary InputActionMapLibrary;

	InputActionMapLibrary::SafeClearFirst(Ctxt, WorldContextObject, Map);
}

void UCsScriptLibrary_Manager_Input::ClearInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FECsInputActionMap& Map)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ClearInputActionMap : Context;

	typedef NCsInput::NManager::NInputActionMap::FLibrary InputActionMapLibrary;

	InputActionMapLibrary::SafeClear(Ctxt, WorldContextObject, ControllerId, Map);
}

#pragma endregion Clear

// Reset
#pragma region

void UCsScriptLibrary_Manager_Input::ResetFirstInputActionMap(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ResetFirstInputActionMap : Context;

	typedef NCsInput::NManager::NInputActionMap::FLibrary InputActionMapLibrary;

	InputActionMapLibrary::SafeResetFirst(Ctxt, WorldContextObject);
}

void UCsScriptLibrary_Manager_Input::ResetInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId)
{
	using namespace NCsScriptLibraryManagerInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ResetInputActionMap : Context;

	typedef NCsInput::NManager::NInputActionMap::FLibrary InputActionMapLibrary;

	InputActionMapLibrary::SafeReset(Ctxt, WorldContextObject, ControllerId);
}

#pragma endregion Reset

#pragma endregion InputActionMap