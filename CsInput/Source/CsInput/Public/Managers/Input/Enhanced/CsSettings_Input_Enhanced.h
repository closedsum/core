// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Input/Action/CsInputActionMap.h"
#include "Managers/Input/GameEvent/CsGameEventDefinition.h"

#include "CsSettings_Input_Enhanced.generated.h"

// FCsSettings_Input
#pragma region

USTRUCT(BlueprintType)
struct CSINPUT_API FCsSettings_Input_Enhanced
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsInput|Input")
	TMap<FECsInputActionMap, FCsInputActionSet> InputActionMappings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Input")
	TSet<FCsGameEventDefinition> GameEventDefinitions;

	/** This is a simplified GameEvent (FECsGameEvent) definition based on an
		Action type action (FECsInputAction).
		 One Word with one or more "Or" Input Words.
		 No Completed Value
		 - No additional value is passed through when the definition is completed.
		  Usually for Actions, there is NO value. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Input", meta = (DisplayName = "GameEventDefintions: Action - 1 Or Word, No Complete Value"))
	TSet<FCsGameEventDefinitionActionOneOrWordNoCompletedValue> GameEventDefinitions_ActionOneOrWordNoCompleteValue;

	/** This is a simplified GameEvent (FECsGameEvent) definition based on an
		Action type action (FECsInputAction).
		 One Word with one or more "Or" Input Words all with the SAME InputEvent.
		 No Completed Value
		 - No additional value is passed through when the definition is completed.
		  Usually for Actions, there is NO value. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Input", meta = (DisplayName = "GameEventDefintions: Action - 1 Or Word, 1 InputEvent, No Complete Value"))
	TSet<FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue> GameEventDefinitions_ActionOneOrWordOneEventNoCompleteValue;

	/** This is a simplified GameEvent (FECsGameEvent) definition based on an
		Axis type action (FECsInputAction).
		 One Word with one or more "Or" Input Words.
		 No Compare Value
		  - No value is used to determine whether the raw input value should be
		    accepted.
		 Pass Through Value
		  - The raw input value "passes through" unaltered. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Input", meta = (DisplayName = "GameEventDefintions: Axis - 1 Or Word, No Compare, Pass Through Value"))
	TSet<FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue> GameEventDefinitions_AxisOneOrWordNoComparePassThroughValue;

	UPROPERTY(VisibleAnywhere, Category = "CsInput|Input")
	TArray<FString> GameEventDefinitionSummary;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Input", meta = (DisplayName = "GameEventPriorityList", MultiLine = true))
	FString GameEventPriorityList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Input")
	TArray<FECsGameEvent> GameEventPriorityList_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Input")
	FECsInputAction AnyKeyAction;

	FCsSettings_Input_Enhanced() :
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

	static const FCsSettings_Input_Enhanced& Get();
	static FCsSettings_Input_Enhanced& GetMutable();

	void PopulateGameEventDefintionSummary();

	void PopulateGameEventPriorityList();

	bool DoesExist(const FString& Context, const FECsGameEvent& Event) const;

private:
	
	template<typename DefinitionType>
	bool DoesExist_Internal(const FECsGameEvent& Event, const TSet<DefinitionType>& Definitions) const
	{
		for (const DefinitionType& Def : Definitions)
		{
			if (Event == Def.GameEvent)
			{
				return true;
			}
		}
		return false;
	}

public:

	void Remove(const FString& Context, const FECsGameEvent& Event);

private:

	template<typename DefinitionType>
	void Remove_Internal(const FECsGameEvent& Event, TSet<DefinitionType>& Definitions)
	{
		int32 Index = INDEX_NONE;

		for (DefinitionType& Def : Definitions)
		{
			if (Event == Def.GameEvent)
			{
				Index = Definitions.FindId(Def).AsInteger();
				break;
			}
		}

		FSetElementId Id = FSetElementId::FromInteger(Index);

		if (Id.IsValidId())
			Definitions.Remove(Id);
	}

public:

	void OnPostEditChange(const FString& PropertyName, const TSet<FString>& PropertyNames);
};

#pragma endregion FCsSettings_Input