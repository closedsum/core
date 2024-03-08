// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Enhanced/CsSettings_Input_Enhanced.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Log
#include "Utility/CsLog.h"

// FCsSettings_Input_Enhanced
#pragma region

const FCsSettings_Input_Enhanced& FCsSettings_Input_Enhanced::Get()
{
	return GetMutableDefault<UCsDeveloperSettings>()->EnhancedInput;
}

FCsSettings_Input_Enhanced& FCsSettings_Input_Enhanced::GetMutable()
{
	return GetMutableDefault<UCsDeveloperSettings>()->EnhancedInput;
}

void FCsSettings_Input_Enhanced::PopulateGameEventDefintionSummary()
{
	TArray<FString>& Summary = GameEventDefinitionSummary;

	Summary.Reset();

	// GameEventDefinitions
	for (const FCsGameEventDefinition& Def : GameEventDefinitions)
	{
		Summary.Add(Def.PrintSummary());
	}
	// GameEventDefinitions_ActionOneOrWordNoCompleteValue
	{
		typedef FCsGameEventDefinitionActionOneOrWordNoCompletedValue DefinitionType;

		for (const DefinitionType& Def : GameEventDefinitions_ActionOneOrWordNoCompleteValue)
		{
			Summary.Add(Def.PrintSummary());
		}
	}
	// GameEventDefinitions_ActionOneOrWordOneEventNoCompleteValue
	{
		typedef FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue DefinitionType;

		for (const DefinitionType& Def : GameEventDefinitions_ActionOneOrWordOneEventNoCompleteValue)
		{
			Summary.Add(Def.PrintOneLineSummary());
		}
	}
	// GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue
	{
		typedef FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue DefinitionType;

		for (const DefinitionType& Def : GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue)
		{
			Summary.Add(Def.PrintOneLineSummary());
		}
	}
}

void FCsSettings_Input_Enhanced::PopulateGameEventPriorityList()
{
	if (GameEventPriorityList.IsEmpty())
		return;

	TArray<FECsGameEvent> Temp;

	const TCHAR* Stream = *GameEventPriorityList;

	FString Line;
	FString Name;

	FParse::Line(&Stream, Line);

	int32 Count = 0;

	while (!Line.IsEmpty())
	{
		const FECsGameEvent& Event = EMCsGameEvent::Get().GetSafeEnum(Line);

		if (Event == EMCsGameEvent::Get().GetMAX())
		{
			UE_LOG(LogCs, Warning, TEXT("%s: Line %d: %s is NOT a Valid FECsGameEvent."), *(EMCsGameEvent::Get().GetEnumName()), Count, *Line);
			return;
		}
		Temp.Add(Event);

		FParse::Line(&Stream, Line);

		++Count;
	}

	GameEventPriorityList_Internal.Reset(Temp.Num());

	GameEventPriorityList_Internal = Temp;
}

bool FCsSettings_Input_Enhanced::DoesExist(const FString& Context, const FECsGameEvent& Event) const
{
	void(*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_ENUM_STRUCT_VALID(EMCsGameEvent, FECsGameEvent, Event)

	// GameEventDefinitions
	{
		typedef FCsGameEventDefinition DefinitionType;
		const TSet<DefinitionType>& Definitions = GameEventDefinitions;

		for (const DefinitionType& Def : Definitions)
		{
			if (Event == Def.Event)
			{
				return true;
			}
		}
	}
	// GameEventDefinitions_ActionOneOrWordNoCompleteValue
	{
		typedef FCsGameEventDefinitionActionOneOrWordNoCompletedValue DefinitionType;
		const TSet<DefinitionType>& Definitions = GameEventDefinitions_ActionOneOrWordNoCompleteValue;

		if (DoesExist_Internal<DefinitionType>(Event, Definitions))
			return true;
	}
	// GameEventDefinitions_ActionOneOrWordOneEventNoCompleteValue
	{
		typedef FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue DefinitionType;
		const TSet<DefinitionType>& Definitions = GameEventDefinitions_ActionOneOrWordOneEventNoCompleteValue;

		if (DoesExist_Internal<DefinitionType>(Event, Definitions))
			return true;
	}
	// GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue
	{
		typedef FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue DefinitionType;
		const TSet<DefinitionType>& Definitions = GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue;

		if (DoesExist_Internal<DefinitionType>(Event, Definitions))
			return true;
	}
	return false;
}

void FCsSettings_Input_Enhanced::Remove(const FString& Context, const FECsGameEvent& Event)
{
	void(*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsGameEvent, FECsGameEvent, Event)

	// GameEventDefinitions
	{
		typedef FCsGameEventDefinition DefinitionType;
		TSet<DefinitionType>& Definitions = GameEventDefinitions;

		int32 Index = INDEX_NONE;

		for (DefinitionType& Def : Definitions)
		{
			if (Event == Def.Event)
			{
				Index = Definitions.FindId(Def).AsInteger();
				break;
			}
		}

		FSetElementId Id = FSetElementId::FromInteger(Index);

		if (Id.IsValidId())
			Definitions.Remove(Id);
	}
	// GameEventDefinitions_ActionOneOrWordNoCompleteValue
	{
		typedef FCsGameEventDefinitionActionOneOrWordNoCompletedValue DefinitionType;
		TSet<DefinitionType>& Definitions = GameEventDefinitions_ActionOneOrWordNoCompleteValue;
		Remove_Internal<DefinitionType>(Event, Definitions);
	}
	// GameEventDefinitions_ActionOneOrWordOneEventNoCompleteValue
	{
		typedef FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue DefinitionType;
		TSet<DefinitionType>& Definitions = GameEventDefinitions_ActionOneOrWordOneEventNoCompleteValue;
		Remove_Internal<DefinitionType>(Event, Definitions);
	}
	// GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue
	{
		typedef FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue DefinitionType;
		TSet<DefinitionType>& Definitions = GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue;
		Remove_Internal<DefinitionType>(Event, Definitions);
	}
}

void FCsSettings_Input_Enhanced::OnPostEditChange(const FString& PropertyName, const TSet<FString>& PropertyNames)
{
	// GameEventDefinitionSummary
	if (PropertyName == TEXT("GameEventDefinitions") ||
		PropertyName == TEXT("GameEventDefinitions_ActionOneOrWordNoCompleteValue") ||
		PropertyName == TEXT("GameEventDefinitions_ActionOneOrWordOneEventNoCompleteValue") ||
		PropertyName == TEXT("GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue"))
	{
		PopulateGameEventDefintionSummary();
	}
	// GameEventDefinitionSummary
	else
	if (PropertyNames.Contains("GameEventDefinitions") ||
		PropertyNames.Contains("GameEventDefinitions_ActionOneOrWordNoCompleteValue") ||
		PropertyNames.Contains("GameEventDefinitions_ActionOneOrWordOneEventNoCompleteValue") ||
		PropertyNames.Contains("GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue"))
	{
		PopulateGameEventDefintionSummary();
	}
	// GameEventPriorityList_Internal
	else
	if (PropertyName == TEXT("GameEventPriorityList"))
	{
		PopulateGameEventPriorityList();
	}
}

#pragma endregion FCsSettings_Input_Enhanced