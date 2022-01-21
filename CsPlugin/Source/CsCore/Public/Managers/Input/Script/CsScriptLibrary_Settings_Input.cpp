// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/Script/CsScriptLibrary_Settings_Input.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Log
#include "Utility/CsLog.h"

// Cached
#pragma region

namespace NCsScriptLibrarySettingsInput
{ 
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Settings_Input, DoesMappingExist);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Settings_Input, DoesActionByMapExist);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Settings_Input, AddActionToMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Settings_Input, RemoveActionFromMap);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Settings_Input, ClearMapping);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Settings_Input::UCsScriptLibrary_Settings_Input(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_Settings_Input::DoesMappingExist(const FString& Context, const FECsInputActionMap& Map)
{
	using namespace NCsScriptLibrarySettingsInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::DoesMappingExist : Context;

	void(*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_ENUM_STRUCT_VALID(EMCsInputActionMap, FECsInputActionMap, Map)

	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();
	FCsSettings_Input& InputSettings = Settings->Input;

	FCsInputActionSet* SetPtr = InputSettings.InputActionMappings.Find(Map);

	return SetPtr != nullptr;
}

bool UCsScriptLibrary_Settings_Input::DoesActionByMapExist(const FString& Context, const FECsInputActionMap& Map, const FECsInputAction& Action)
{
	using namespace NCsScriptLibrarySettingsInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::DoesActionByMapExist : Context;

	void(*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_ENUM_STRUCT_VALID(EMCsInputActionMap, FECsInputActionMap, Map)

	CS_IS_ENUM_STRUCT_VALID(EMCsInputAction, FECsInputAction, Action)

	UCsDeveloperSettings* Settings   = GetMutableDefault<UCsDeveloperSettings>();
	FCsSettings_Input& InputSettings = Settings->Input;

	if (FCsInputActionSet* SetPtr = InputSettings.InputActionMappings.Find(Map))
	{
		return SetPtr->Actions.Contains(Action);
	}
	return false;
}

void UCsScriptLibrary_Settings_Input::AddActionToMap(const FString& Context, const FECsInputActionMap& Map, const FECsInputAction& Action)
{
	using namespace NCsScriptLibrarySettingsInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddActionToMap : Context;

	void(*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsInputActionMap, FECsInputActionMap, Map)

	CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsInputAction, FECsInputAction, Action)

	UCsDeveloperSettings* Settings	 = GetMutableDefault<UCsDeveloperSettings>();
	FCsSettings_Input& InputSettings = Settings->Input;

	FCsInputActionSet* SetPtr = InputSettings.InputActionMappings.Find(Map);

	if (!SetPtr)
	{
		SetPtr = &(InputSettings.InputActionMappings.Add(Map));
	}

	if (SetPtr->Actions.Contains(Action))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: UCsDeveloperSettings.Input.InputActionMapping[%s].Actions[%s] has ALREADY been set."), *Context, Map.ToChar(), Action.ToChar());
	}
	else
	{
		SetPtr->Actions.Add(Action);
	}
}

void UCsScriptLibrary_Settings_Input::RemoveActionFromMap(const FString& Context, const FECsInputActionMap& Map, const FECsInputAction& Action)
{
	using namespace NCsScriptLibrarySettingsInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::RemoveActionFromMap : Context;

	void(*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsInputActionMap, FECsInputActionMap, Map)

	CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsInputAction, FECsInputAction, Action)

	UCsDeveloperSettings* Settings	 = GetMutableDefault<UCsDeveloperSettings>();
	FCsSettings_Input& InputSettings = Settings->Input;

	if (FCsInputActionSet* SetPtr = InputSettings.InputActionMappings.Find(Map))
	{
		SetPtr->Actions.Remove(Action);
	}
}

void UCsScriptLibrary_Settings_Input::ClearMapping(const FString& Context, const FECsInputActionMap& Map)
{
	using namespace NCsScriptLibrarySettingsInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ClearMapping : Context;

	void(*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsInputActionMap, FECsInputActionMap, Map)

	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();
	FCsSettings_Input& InputSettings = Settings->Input;

	InputSettings.InputActionMappings.Remove(Map);
}