// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/Script/CsScriptLibrary_Input.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Player.h"
#include "Library/CsLibrary_Valid.h"
// Input
#include "GameFramework/PlayerInput.h"
// Log
#include "Utility/CsLog.h"

namespace NCsScriptLibraryInput
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Input, AddActionMapping);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Input, AddAxisMapping);
		}
	}
}

UCsScriptLibrary_Input::UCsScriptLibrary_Input(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_Input::AddActionMapping(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FInputActionKeyMapping& KeyMapping)
{
	using namespace NCsScriptLibraryInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddActionMapping : Context;

	typedef NCsPlayer::NInput::FLibrary PlayerInputLibrary;

	UPlayerInput* PlayerInput = PlayerInputLibrary::GetSafe(Ctxt, WorldContextObject, ControllerId);

	if (!PlayerInput)
		return false;

	void(*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_NAME_NONE(KeyMapping.ActionName)

	const FKey& Key = KeyMapping.Key;

	if (Key.IsValid())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeyMapping.Key: %s is NOT Valid."), *Ctxt, *(Key.ToString())));
		return false;
	}

	PlayerInput->AddActionMapping(KeyMapping);
	return true;
}

bool UCsScriptLibrary_Input::AddAxisMapping(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FInputAxisKeyMapping& KeyMapping)
{
	using namespace NCsScriptLibraryInput::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddAxisMapping : Context;

	typedef NCsPlayer::NInput::FLibrary PlayerInputLibrary;

	UPlayerInput* PlayerInput = PlayerInputLibrary::GetSafe(Ctxt, WorldContextObject, ControllerId);

	if (!PlayerInput)
		return false;

	void(*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_NAME_NONE(KeyMapping.AxisName)

	const FKey& Key = KeyMapping.Key;

	if (Key.IsValid())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: KeyMapping.Key: %s is NOT Valid."), *Ctxt, *(Key.ToString())));
		return false;
	}

	CS_IS_FLOAT_NOT_EQUAL(KeyMapping.Scale, 0.0f)

	PlayerInput->AddAxisMapping(KeyMapping);
	return true;
}