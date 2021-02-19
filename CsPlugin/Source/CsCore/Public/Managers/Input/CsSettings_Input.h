// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsTypes_Input.h"
#include "CsSettings_Input.generated.h"
#pragma once

// FCsSettings_Input
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Input
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsInputActionMap, FCsInputActionSet> InputActionMappings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<FCsGameEventDefinition> GameEventDefinitions;

	/** This is a simplified GameEvent (FECsGameEvent) definition based on an
		Action type action (FECsInputAction).
		 One Word with one or more "Or" Input Words.
		 No Completed Value
		 - No additional value is passed through when the definition is completed.
		  Usually for Actions, there is NO value. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "GameEventDefintions: Action - 1 Or Word, No Complete Value"))
	TSet<FCsGameEventDefinitionActionOneOrWordNoCompletedValue> GameEventDefinitions_ActionOneOrWordNoCompleteValue;

	/** This is a simplified GameEvent (FECsGameEvent) definition based on an
		Action type action (FECsInputAction).
		 One Word with one or more "Or" Input Words all with the SAME InputEvent.
		 No Completed Value
		 - No additional value is passed through when the definition is completed.
		  Usually for Actions, there is NO value. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "GameEventDefintions: Action - 1 Or Word, 1 InputEvent, No Complete Value"))
	TSet<FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue> GameEventDefinitions_ActionOneOrWordOneEventNoCompleteValue;

	/** This is a simplified GameEvent (FECsGameEvent) definition based on an
		Axis type action (FECsInputAction).
		 One Word with one or more "Or" Input Words.
		 No Compare Value
		  - No value is used to determine whether the raw input value should be
		    accepted.
		 Pass Through Value
		  - The raw input value "passes through" unaltered. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "GameEventDefintions: Axis - 1 Or Word, No Compare, Pass Through Value"))
	TSet<FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue> GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue;

	UPROPERTY(VisibleAnywhere)
	TArray<FString> GameEventDefinitionSummary;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,meta = (DisplayName = "GameEventPriorityList", MultiLine = true))
	FString GameEventPriorityList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FECsGameEvent> GameEventPriorityList_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsInputAction AnyKeyAction;

	FCsSettings_Input() :
		InputActionMappings(),
		GameEventDefinitions(),
		GameEventDefinitions_ActionOneOrWordNoCompleteValue(),
		GameEventDefinitions_ActionOneOrWordOneEventNoCompleteValue(),
		GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue(),
		GameEventPriorityList(),
		GameEventPriorityList_Internal(),
		AnyKeyAction()
	{
	}

	void PopulateGameEventDefintionSummary();

	void PopulateGameEventPriorityList();

	void OnPostEditChange(const FString& PropertyName, const TSet<FString>& PropertyNames);
};

#pragma endregion FCsSettings_Input