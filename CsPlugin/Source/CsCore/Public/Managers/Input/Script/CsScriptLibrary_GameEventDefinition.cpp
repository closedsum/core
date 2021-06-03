// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/Script/CsScriptLibrary_GameEventDefinition.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Log
#include "Utility/CsLog.h"

namespace NCsScriptLibraryGameEvent
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameEventDefinition, Add);
		}
	}
}

UCsScriptLibrary_GameEventDefinition::UCsScriptLibrary_GameEventDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_GameEventDefinition::Add(const FString& Context, const FECsGameEvent& Event, const FCsGameEventDefinition& Definition)
{
	using namespace NCsScriptLibraryGameEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Add : Context;

	UCsDeveloperSettings* Settings	 = GetMutableDefault<UCsDeveloperSettings>();
	FCsSettings_Input& InputSettings = Settings->Input;


	return false;
}