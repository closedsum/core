// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Script/CsScriptLibrary_Input.h"
#include "CsCore.h"

// Library
#include "Managers/Input/CsLibrary_Input.h"
#include "Library/CsLibrary_Player.h"
#include "Library/CsLibrary_Valid.h"
// Log
#include "Utility/CsLog.h"

namespace NCsScriptLibraryInput
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Input, IsKeyValidForDevice);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Input, IsKeyValidForMode);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Input, GetKeysByDevice);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Input, GetKey);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Input, AddActionMapping);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Input, AddAxisMapping);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Input, ReplaceActionMapping);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Input, IsActionAssociatedWithKey);
		}
	}
}

UCsScriptLibrary_Input::UCsScriptLibrary_Input(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Key
#pragma region

bool UCsScriptLibrary_Input::IsKeyValidForDevice(const FString& Context, const ECsInputDevice& Device, const FKey& Key)
{
	using namespace NCsScriptLibraryInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsKeyValidForDevice : Context;

	typedef NCsInput::NKey::FLibrary InputKeyLibrary;

	return InputKeyLibrary::IsValidForDevice(Ctxt, Device, Key);
}

bool UCsScriptLibrary_Input::IsKeyValidForMode(const FString& Context, const ECsInputMode& Mode, const FKey& Key)
{
	using namespace NCsScriptLibraryInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsKeyValidForMode : Context;

	typedef NCsInput::NKey::FLibrary InputKeyLibrary;

	return InputKeyLibrary::IsValidForMode(Ctxt, Mode, Key);
}

bool UCsScriptLibrary_Input::GetKeysByDevice(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device, TArray<FKey>& OutKeys)
{
	using namespace NCsScriptLibraryInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetKeysByDevice : Context;

	typedef NCsInput::NKey::FLibrary InputKeyLibrary;

	return InputKeyLibrary::GetSafe(Ctxt, Action, Device, OutKeys);
}

FKey UCsScriptLibrary_Input::GetKey(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device)
{
	using namespace NCsScriptLibraryInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetKey : Context;

	typedef NCsInput::NKey::FLibrary InputKeyLibrary;

	return InputKeyLibrary::GetSafe(Ctxt, Action, Device);
}

#pragma endregion Key

// Mapping
#pragma region

bool UCsScriptLibrary_Input::AddActionMapping(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FInputActionKeyMapping& KeyMapping)
{
	using namespace NCsScriptLibraryInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddActionMapping : Context;

	typedef NCsInput::NMapping::FLibrary InputMappingLibrary;

	return InputMappingLibrary::AddSafeAction(Ctxt, WorldContextObject, ControllerId, KeyMapping);
}

bool UCsScriptLibrary_Input::AddAxisMapping(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FInputAxisKeyMapping& KeyMapping)
{
	using namespace NCsScriptLibraryInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddAxisMapping : Context;

	typedef NCsInput::NMapping::FLibrary InputMappingLibrary;

	return InputMappingLibrary::AddSafeAxis(Ctxt, WorldContextObject, ControllerId, KeyMapping);
}

bool UCsScriptLibrary_Input::ReplaceActionMapping(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key, const float& Scale /*=0.0f*/)
{
	using namespace NCsScriptLibraryInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ReplaceActionMapping : Context;

	typedef NCsInput::NMapping::FLibrary InputMappingLibrary;

	return InputMappingLibrary::SafeReplaceAction(Ctxt, WorldContextObject, ControllerId, Device, Action, Key, Scale);
}

#pragma endregion Mapping

// Action
#pragma region

bool UCsScriptLibrary_Input::IsActionAssociatedWithKey(const FString& Context, const FECsInputAction& Action, const FKey& Key)
{
	using namespace NCsScriptLibraryInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsActionAssociatedWithKey : Context;

	typedef NCsInput::NAction::FLibrary InputActionLibrary;

	return InputActionLibrary::SafeIsAssociatedWith(Ctxt, Action, Key);
}

#pragma endregion Action

// Mode
#pragma region

bool UCsScriptLibrary_Input::TestBitflag_InputMode(const int32& Mask, const ECsInputMode& Mode)
{
	return CS_TEST_BLUEPRINT_BITFLAG(Mask, Mode);
}

#pragma endregion Mode