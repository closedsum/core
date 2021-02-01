// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsSettings_Input.h"
#include "CsCore.h"

// FCsSettings_Input
#pragma region

void FCsSettings_Input::PopulateGameEventDefintionSummary()
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

void FCsSettings_Input::PopulateGameEventPriorityList()
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

void FCsSettings_Input::OnPostEditChange(const FString& PropertyName, const TSet<FString>& PropertyNames)
{
	// GameEventDefinitionSummary
	if (PropertyName == TEXT("GameEventDefinitions") ||
		PropertyName == TEXT("GameEventDefinitions_ActionOneOrWordNoCompleteValue") ||
		PropertyName == TEXT("GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue"))
	{
		PopulateGameEventDefintionSummary();
	}
	// GameEventDefinitionSummary
	else
	if (PropertyNames.Contains("GameEventDefinitions") ||
		PropertyNames.Contains("GameEventDefinitions_ActionOneOrWordNoCompleteValue") ||
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

#pragma endregion FCsSettings_Input