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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameEventDefinition, Add_ActionOneOrWordNoCompletedValue);
		}
	}
}

UCsScriptLibrary_GameEventDefinition::UCsScriptLibrary_GameEventDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_GameEventDefinition::Add(const FString& Context, const FCsGameEventDefinition& Definition)
{
	using namespace NCsScriptLibraryGameEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Add : Context;

	if (!Definition.IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Definition is NOT Valid."), *Ctxt);
		UE_LOG(LogCs, Warning, TEXT("%s"), *(Definition.PrintSummary()));
		return false;
	}

	UCsDeveloperSettings* Settings	 = GetMutableDefault<UCsDeveloperSettings>();
	FCsSettings_Input& InputSettings = Settings->Input;

	bool Found = false;

	for (FCsGameEventDefinition& Def : InputSettings.GameEventDefinitions)
	{
		if (Def.Event == Definition.Event)
		{
			Def = Definition;
			Found = true;

			UE_LOG(LogCs, Warning, TEXT("%s: Definition for Event: %s already exists. Overwriting definition."), *Ctxt, Definition.Event.ToChar());
			break;
		}
	}

	if (!Found)
		InputSettings.GameEventDefinitions.Add(Definition);
	return true;
}

bool UCsScriptLibrary_GameEventDefinition::Add_ActionOneOrWordNoCompletedValue(const FString& Context, const FCsGameEventDefinitionActionOneOrWordNoCompletedValue& Definition)
{
	using namespace NCsScriptLibraryGameEvent::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Add : Context;

	if (!Definition.IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Definition is NOT Valid."), *Ctxt);
		UE_LOG(LogCs, Warning, TEXT("%s"), *(Definition.PrintSummary()));
		return false;
	}

	UCsDeveloperSettings* Settings	 = GetMutableDefault<UCsDeveloperSettings>();
	FCsSettings_Input& InputSettings = Settings->Input;

	bool Found = false;

	typedef FCsGameEventDefinitionActionOneOrWordNoCompletedValue DefinitionType;

	for (DefinitionType& Def : InputSettings.GameEventDefinitions_ActionOneOrWordNoCompleteValue)
	{
		if (Def.GameEvent == Definition.GameEvent)
		{
			Def   = Definition;
			Found = true;

			UE_LOG(LogCs, Warning, TEXT("%s: Definition for Event: %s already exists. Overwriting definition."), *Ctxt, Definition.GameEvent.ToChar());
			break;
		}
	}

	if (!Found)
		InputSettings.GameEventDefinitions_ActionOneOrWordNoCompleteValue.Add(Definition);
	return true;
}