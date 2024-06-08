// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Input/Definition/CsTypes_InputDefinition.h"
#include "Managers/Input/GameEvent/CsGameEvent.h"

#include "CsGameEventDefinition.generated.h"

// FCsInputActionAndEvent
#pragma region

USTRUCT(BlueprintType)
struct CSINPUT_API FCsInputActionAndEvent
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Input|Game Event")
	FECsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Input|Game Event")
	ECsInputEvent Event;

	FCsInputActionAndEvent() :
		Action(),
		Event(ECsInputEvent::FirstPressed)
	{
	}

	FORCEINLINE bool operator==(const FCsInputActionAndEvent& B) const
	{
		return Action == B.Action && Event == B.Event;
	}

	FORCEINLINE bool operator!=(const FCsInputActionAndEvent& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion FCsInputActionAndEvent

// FCsGameEventDefinitionSimple
#pragma region

USTRUCT(BlueprintType)
struct CSINPUT_API FCsGameEventDefinitionSimple
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Input|Game Event")
	FECsGameEvent GameEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Input|Game Event")
	FECsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Input|Game Event")
	ECsInputEvent Event;

	FCsGameEventDefinitionSimple() :
		Event(ECsInputEvent::ECsInputEvent_MAX)
	{
		GameEvent = EMCsGameEvent::Get().GetMAX();
		Action = EMCsInputAction::Get().GetMAX();
	}

	FORCEINLINE bool operator==(const FCsGameEventDefinitionSimple& B) const
	{
		return GameEvent == B.GameEvent && Action == B.Action && Event == B.Event;
	}

	bool IsValid() const
	{
		return EMCsGameEvent::Get().IsValidEnum(GameEvent) && EMCsInputAction::Get().IsValidEnum(Action) && Event != ECsInputEvent::ECsInputEvent_MAX;
	}
};

FORCEINLINE uint32 GetTypeHash(const FCsGameEventDefinitionSimple& b)
{
	return GetTypeHash(b.GameEvent);
}

#pragma endregion FCsGameEventDefinitionSimple

// FCsGameEventDefinition
#pragma region

/**
*
*/
USTRUCT(BlueprintType)
struct CSINPUT_API FCsGameEventDefinition
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Input|Game Event")
	FECsGameEvent Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Input|Game Event")
	FCsInputSentence Sentence;

	FCsGameEventDefinition() :
		Event(),
		Sentence()
	{
		Event = EMCsGameEvent::Get().GetMAX();
	}

	FORCEINLINE bool operator==(const FCsGameEventDefinition& B) const
	{
		return Event == B.Event && Sentence == B.Sentence;
	}

	bool IsValid() const
	{
		return EMCsGameEvent::Get().IsValidEnum(Event) && Sentence.IsValid();
	}

	FString PrintSummary() const;
};

FORCEINLINE uint32 GetTypeHash(const FCsGameEventDefinition& b)
{
	return GetTypeHash(b.Event);
}

#pragma endregion FCsGameEventDefinition

// FCsGameEventDefinitionActionOneOrWordNoCompletedValue
#pragma region

/**
* This is a simplified GameEvent (FECsGameEvent) definition based on an 
* Action type action (FECsInputAction).
*  One Word with one or more "Or" Input Words.
*  No Completed Value
*	- No additional value is passed through when the definition is completed.
*	  Usually for Actions, there is NO value.
*/
USTRUCT(BlueprintType)
struct CSINPUT_API FCsGameEventDefinitionActionOneOrWordNoCompletedValue
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Input|Game Event")
	FECsGameEvent GameEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Input|Game Event")
	TArray<FCsInputActionAndEvent> Words;

	FCsGameEventDefinitionActionOneOrWordNoCompletedValue() :
		GameEvent(),
		Words()
	{
	}

	FORCEINLINE bool operator==(const FCsGameEventDefinitionActionOneOrWordNoCompletedValue& B) const
	{
		if (GameEvent != B.GameEvent)
			return false;

		if (Words.Num() != B.Words.Num())
			return false;

		const int32 Count = Words.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Words[I] != B.Words[I])
				return false;
		}
		return true;
	}

	FORCEINLINE bool operator!=(const FCsGameEventDefinitionActionOneOrWordNoCompletedValue& B) const
	{
		return !(*this == B);
	}

	bool IsValid() const
	{
		if (!EMCsGameEvent::Get().IsValidEnum(GameEvent))
			return false;

		for (const FCsInputActionAndEvent& Word : Words)
		{
			const FECsInputAction& Action = Word.Action;
			const ECsInputEvent& Event	  = Word.Event;

			if (!EMCsInputAction::Get().IsValidEnum(Action))
				return false;

			if (Event == ECsInputEvent::ECsInputEvent_MAX)
				return false;
		}

		return true;
	}

	void AddDefinition(TSet<FCsGameEventDefinition>& GameEventDefinitions, TMap<FECsGameEvent, FCsInputSentence>& InputSentenceByGameEventMap) const;

	FString PrintSummary() const;
};

FORCEINLINE uint32 GetTypeHash(const FCsGameEventDefinitionActionOneOrWordNoCompletedValue& b)
{
	return GetTypeHash(b.GameEvent);
}

#pragma endregion FCsGameEventDefinitionActionOneOrWordNoCompletedValue

// FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue
#pragma region

/**
* This is a simplified GameEvent (FECsGameEvent) definition based on an 
* Action type action (FECsInputAction).
*  One Word with one or more "Or" Input Words all with the SAME InputEvent
*  No Completed Value
*	- No additional value is passed through when the definition is completed.
*	  Usually for Actions, there is NO value.
*/
USTRUCT(BlueprintType)
struct CSINPUT_API FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Input|Game Event")
	FECsGameEvent GameEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Input|Game Event")
	TArray<FECsInputAction> Actions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Input|Game Event")
	ECsInputEvent Event;

	FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue() :
		GameEvent(),
		Actions(),
		Event()
	{
	}

	FORCEINLINE bool operator==(const FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue& B) const
	{
		if (GameEvent != B.GameEvent)
			return false;
		if (Event != B.Event)
			return false;

		if (Actions.Num() != B.Actions.Num())
			return false;

		const int32 Count = Actions.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Actions[I] != B.Actions[I])
				return false;
		}
		return true;
	}

	FORCEINLINE bool operator!=(const FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue& B) const
	{
		return !(*this == B);
	}

	bool IsValid() const
	{
		if (!EMCsGameEvent::Get().IsValidEnum(GameEvent))
			return false;

		for (const FECsInputAction& Action : Actions)
		{
			if (!EMCsInputAction::Get().IsValidEnum(Action))
				return false;
		}

		return Event != ECsInputEvent::ECsInputEvent_MAX;
	}

	void AddDefinition(TSet<FCsGameEventDefinition>& GameEventDefinitions, TMap<FECsGameEvent, FCsInputSentence>& InputSentenceByGameEventMap) const;

	FString PrintOneLineSummary() const;
};

FORCEINLINE uint32 GetTypeHash(const FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue& b)
{
	return GetTypeHash(b.GameEvent);
}

#pragma endregion FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue

// FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue
#pragma region

/**
* This is a simplified GameEvent (FECsGameEvent) definition based on an
* Axis type action (FECsInputAction).
*  One Word with one or more "Or" Input Words.
*  No Compare Value
*   - No value is used to determine whether the raw input value should be
*	  accepted.
*  Pass Through Value
*	- The raw input value "passes through" unaltered.
*/
USTRUCT(BlueprintType)
struct CSINPUT_API FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Input|Game Event")
	FECsGameEvent GameEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Input|Game Event")
	TArray<FECsInputAction> Actions;

	FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue() :
		GameEvent(),
		Actions()
	{
	}

	FORCEINLINE bool operator==(const FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue& B) const
	{
		if (GameEvent != B.GameEvent)
			return false;

		if (Actions.Num() != B.Actions.Num())
			return false;

		const int32 Count = Actions.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Actions[I] != B.Actions[I])
				return false;
		}
		return true;
	}

	FORCEINLINE bool operator!=(const FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue& B) const
	{
		return !(*this == B);
	}

	bool IsValid() const
	{
		if (!EMCsGameEvent::Get().IsValidEnum(GameEvent))
			return false;

		for (const FECsInputAction& Action : Actions)
		{
			if (!EMCsInputAction::Get().IsValidEnum(Action))
				return false;
		}
		return true;
	}

	void AddDefinition(TSet<FCsGameEventDefinition>& GameEventDefinitions, TMap<FECsGameEvent, FCsInputSentence>& InputSentenceByGameEventMap) const;

	FString PrintOneLineSummary() const;
};

FORCEINLINE uint32 GetTypeHash(const FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue& b)
{
	return GetTypeHash(b.GameEvent);
}

#pragma endregion FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue