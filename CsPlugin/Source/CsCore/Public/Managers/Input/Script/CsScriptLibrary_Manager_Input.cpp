// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Script/CsScriptLibrary_Manager_Input.h"
#include "CsCore.h"

// CVar
#include "Script/CsCVars_Script.h"
// Library
#include "Managers/Input/CsLibrary_Manager_Input.h"
// Input
#include "Managers/Input/Event/CsManager_Input_Event.h"

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
			// ICsManager_Input_Event
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Input, BindToEvent_OnAnyKey_Pressed);
		}
	}
}

UCsScriptLibrary_Manager_Input::UCsScriptLibrary_Manager_Input(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


#define USING_NS_CACHED using namespace NCsScriptLibraryManagerInput::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerInput::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &FCsLog::Error
#define InputManagerLibrary NCsInput::NManager::FLibrary
#define FirstInputManagerLibrary NCsInput::NManager::NFirst::FLibrary
#define InputActionMapLibrary NCsInput::NManager::NInputActionMap::FLibrary

// Get
#pragma region

UObject* UCsScriptLibrary_Manager_Input::Get(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId)
{
	CONDITIONAL_SET_CTXT(Get);

	return InputManagerLibrary::GetSafeAsObject(Ctxt, WorldContextObject, ControllerId);
}

UObject* UCsScriptLibrary_Manager_Input::GetChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetChecked);

	return CS_SCRIPT_GET_CHECKED(InputManagerLibrary::GetAsObjectChecked(Ctxt, WorldContextObject, ControllerId), InputManagerLibrary::GetSafeAsObject(Ctxt, WorldContextObject, ControllerId, OutSuccess, LogError));
}

#pragma endregion Get

bool UCsScriptLibrary_Manager_Input::Init(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId)
{
	CONDITIONAL_SET_CTXT(Init);

	return InputManagerLibrary::SafeInit(Ctxt, WorldContextObject, ControllerId);
}

bool UCsScriptLibrary_Manager_Input::InitAll(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(InitAll);

	return InputManagerLibrary::SafeInit(Ctxt, WorldContextObject);
}

// InputActionMap
#pragma region

	// Set
#pragma region

bool UCsScriptLibrary_Manager_Input::SetFirstInputActionMap(const FString& Context, const UObject* WorldContextObject, const FECsInputActionMap& Map)
{
	CONDITIONAL_SET_CTXT(SetFirstInputActionMap);

	return InputActionMapLibrary::SetSafeFirst(Ctxt, WorldContextObject, Map);
}

bool UCsScriptLibrary_Manager_Input::SetInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FECsInputActionMap& Map)
{
	CONDITIONAL_SET_CTXT(SetInputActionMap);

	return InputActionMapLibrary::SetSafe(Ctxt, WorldContextObject, ControllerId, Map);
}

#pragma endregion Set

	// Clear
#pragma region

bool UCsScriptLibrary_Manager_Input::ClearFirstInputActionMap(const FString& Context, const UObject* WorldContextObject, const FECsInputActionMap& Map)
{
	CONDITIONAL_SET_CTXT(ClearFirstInputActionMap);

	return InputActionMapLibrary::SafeClearFirst(Ctxt, WorldContextObject, Map);
}

bool UCsScriptLibrary_Manager_Input::ClearInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FECsInputActionMap& Map)
{
	CONDITIONAL_SET_CTXT(ClearInputActionMap);

	return InputActionMapLibrary::SafeClear(Ctxt, WorldContextObject, ControllerId, Map);
}

#pragma endregion Clear

	// Reset
#pragma region

bool UCsScriptLibrary_Manager_Input::ResetFirstInputActionMap(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(ResetFirstInputActionMap);

	return InputActionMapLibrary::SafeResetFirst(Ctxt, WorldContextObject);
}

bool UCsScriptLibrary_Manager_Input::ResetInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId)
{
	CONDITIONAL_SET_CTXT(ResetInputActionMap);

	return InputActionMapLibrary::SafeReset(Ctxt, WorldContextObject, ControllerId);
}

bool UCsScriptLibrary_Manager_Input::ResetAllInputActionMap(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(ResetAllInputActionMap);

	return InputActionMapLibrary::SafeReset(Ctxt, WorldContextObject);
}

#pragma endregion Reset

#pragma endregion InputActionMap

// ICsManager_Input_Event
#pragma region

void UCsScriptLibrary_Manager_Input::BindToEvent_OnAnyKey_Pressed(const FString& Context, UObject* WorldContextObject, FCsManagerInput_ScriptPassable_OnAnyKey_Pressed Delegate)
{
	CONDITIONAL_SET_CTXT(BindToEvent_OnAnyKey_Pressed);

	if (ICsManager_Input_Event* Manager = FirstInputManagerLibrary::GetSafe_ICsManager_Input_Event(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, GetOnAnyKey_Pressed_ScriptEvent(), Delegate, LogCs)
	}
}

#pragma endregion ICsManager_Input_Event

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
#undef InputManagerLibrary
#undef FirstInputManagerLibrary
#undef InputActionMapLibrary