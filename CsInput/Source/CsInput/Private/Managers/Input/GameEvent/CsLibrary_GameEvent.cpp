// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/GameEvent/CsLibrary_GameEvent.h"

// Library
#include "Managers/Input/CsLibrary_Manager_Input.h"
#include "Managers/Input/CsLibrary_Input.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Input/CsManager_Input.h"
// Game Event
#include "Managers/Input/GameEvent/CsGameEventDefinition.h"

namespace NCsGameEvent
{
	bool FLibrary::SafeIsAssociatedWith(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsGameEvent& Event, const FKey& Key, void(*Log)(const FString&) /*=&NCsInput::FLog::Warning*/)
	{
		typedef NCsInput::NManager::FLibrary InputManagerLibrary;

		ICsManager_Input* Manager_Input = InputManagerLibrary::GetSafe(Context, WorldContext, ControllerId, Log);

		if (!Manager_Input)
			return false;

		CS_IS_ENUM_STRUCT_VALID(EMCsGameEvent, FECsGameEvent, Event)

		if (!Key.IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.ToString())));
			return false;
		}

		const FCsGameEventDefinition* Def = Manager_Input->GetGameEventDefinition(Event);

		if (!Def)
			return false;

		typedef NCsInput::NAction::FLibrary InputActionLibrary;

		const FCsInputSentence& Sentence = Def->Sentence;
		
		for (const FCsInputPhrase& Phrase : Sentence.Phrases)
		{
			for (const FCsInputWord& Word : Phrase.Words)
			{
				for (const FCsInputDescription& Desc : Word.OrInputs)
				{
					if (InputActionLibrary::SafeIsAssociatedWith(Context, Desc.Action, Key, Log))
						return true;
				}

				for (const FCsInputDescription& Desc : Word.AndInputs)
				{
					if (InputActionLibrary::SafeIsAssociatedWith(Context, Desc.Action, Key, Log))
						return true;
				}
			}
		}
		return false;
	}
}