// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/GameEvent/CsGameEventDefinition.h"
#include "CsCore.h"

// FCsGameEventDefinition
#pragma region

FString FCsGameEventDefinition::PrintSummary() const
{
	// GameEvent
	//	Phrase [%d]
	//   Word [%d]
	//	  AndInputs [%d]
	//	  OrInputs [%d]

	FString Summary;

	if (!IsValid())
		return Summary;

	Summary += Event.GetName();
	Summary += TEXT("\n");
	// Phrases
	const TArray<FCsInputPhrase>& Phrases = Sentence.Phrases;
	const int32 PhraseCount				= Phrases.Num();

	for (int32 I = 0; I < PhraseCount; ++I)
	{
		Summary += FString::Printf(TEXT(" Phrase [%d]"), I);
		Summary += TEXT("\n");

		const FCsInputPhrase& Phrase = Phrases[I];

		// Words
		const TArray<FCsInputWord>& Words = Phrase.Words;
		const int32 WordCount			  = Words.Num();

		for (int32 J = 0; J < WordCount; ++J)
		{
			Summary += FString::Printf(TEXT("  Word [%d]"), J);
			Summary += TEXT("\n");

			const FCsInputWord& Word = Words[J];

			// AndInputs
			const TArray<FCsInputDescription>& AndInputs = Word.AndInputs;
			const int32 AndInputCount					 = AndInputs.Num();

			for (int32 K = 0; K < AndInputCount; ++K)
			{
				Summary += FString::Printf(TEXT("   AndInput [%d]"), K);
				Summary += TEXT("\n");

				const FCsInputDescription& Desc = AndInputs[K];

				// Action
				Summary += FString::Printf(TEXT("    Action: %s"), Desc.Action.ToChar());
				Summary += TEXT("\n");
				// Event
				if (Desc.bAnyEvent)
				{
					Summary += FString::Printf(TEXT("    Event: AnyEvent"));
				}
				else
				{
					Summary += FString::Printf(TEXT("    Event: %s"), EMCsInputEvent::Get().ToChar(Desc.Event));
				}
				Summary += TEXT("\n");
				// CompareValue
				const FCsInputCompareValue& CompareValue = Desc.CompareValue;
				bool ValidCompareValue = false;
				{
					// Value
					const float& Value				   = CompareValue.Value;
					const ECsInputValueRule& ValueRule = CompareValue.ValueRule;

					if (ValueRule != ECsInputValueRule::None)
					{
						Summary += FString::Printf(TEXT("    CompareValue: %s %f"), EMCsInputValueRule::Get().ToDisplayNameChar(ValueRule), Value);
						ValidCompareValue = true;
					}
					// Location
					const FVector3f& Location					 = CompareValue.Location;
					const ECsInputLocationRule& LocationRule = CompareValue.LocationRule;

					if (LocationRule != ECsInputLocationRule::None)
					{
						Summary += FString::Printf(TEXT("    CompareValue: %s %s"), EMCsInputLocationRule::Get().ToDisplayNameChar(LocationRule), *(Location.ToString()));
						ValidCompareValue = true;
					}
					// Rotation
					const FRotator3f& Rotation				 = CompareValue.Rotation;
					const ECsInputRotationRule& RotationRule = CompareValue.RotationRule;

					if (RotationRule != ECsInputRotationRule::None)
					{
						Summary += FString::Printf(TEXT("    CompareValue: %s %s"), EMCsInputRotationRule::Get().ToDisplayNameChar(RotationRule), *(Rotation.ToString()));
						ValidCompareValue = true;
					}
				}

				if (ValidCompareValue)
					Summary += TEXT("\n");

				// CompletedValue
				const FCsInputCompletedValue& CompletedValue = Desc.CompletedValue;
				{
					const ECsInputValue& ValueType					   = CompletedValue.ValueType;
					const ECsInputCompletedValueReturnType& ReturnType = CompletedValue.ReturnType;

					if (ValueType != ECsInputValue::Void &&
						ReturnType != ECsInputCompletedValueReturnType::PassThrough)
					{
						// Float
						if (ValueType == ECsInputValue::Float)
						{
							Summary += FString::Printf(TEXT("    CompletedValue: %f"), CompletedValue.Value);
						}
						// Location
						if (ValueType == ECsInputValue::Vector)
						{
							Summary += FString::Printf(TEXT("    CompletedValue: %s"), *(CompletedValue.Location.ToString()));
						}
						// Rotation
						if (ValueType == ECsInputValue::Rotator)
						{
							Summary += FString::Printf(TEXT("    CompletedValue: %s"), *(CompletedValue.Rotation.ToString()));
						}
					}
				}

				if (K < AndInputCount - 1)
					Summary += TEXT("\n");
			}

			if (AndInputCount > 1)
				Summary += TEXT("\n");

			// OrInputs
			const TArray<FCsInputDescription>& OrInputs = Word.OrInputs;
			const int32 OrInputCount					= OrInputs.Num();

			for (int32 K = 0; K < OrInputCount; ++K)
			{
				Summary += FString::Printf(TEXT("   OrInput [%d]"), K);
				Summary += TEXT("\n");

				const FCsInputDescription& Desc = OrInputs[K];

				// Action
				Summary += FString::Printf(TEXT("    Action: %s"), Desc.Action.ToChar());
				Summary += TEXT("\n");
				// Event
				if (Desc.bAnyEvent)
				{
					Summary += FString::Printf(TEXT("    Event: AnyEvent"));
				}
				else
				{
					Summary += FString::Printf(TEXT("    Event: %s"), EMCsInputEvent::Get().ToChar(Desc.Event));
				}
				Summary += TEXT("\n");
				// CompareValue
				const FCsInputCompareValue& CompareValue = Desc.CompareValue;
				bool ValidCompareValue = false;
				{
					// Value
					const float& Value				   = CompareValue.Value;
					const ECsInputValueRule& ValueRule = CompareValue.ValueRule;

					if (ValueRule != ECsInputValueRule::None)
					{
						Summary += FString::Printf(TEXT("    CompareValue: %s %f"), EMCsInputValueRule::Get().ToDisplayNameChar(ValueRule), Value);
						ValidCompareValue = true;
					}
					// Location
					const FVector3f& Location					 = CompareValue.Location;
					const ECsInputLocationRule& LocationRule = CompareValue.LocationRule;

					if (LocationRule != ECsInputLocationRule::None)
					{
						Summary += FString::Printf(TEXT("    CompareValue: %s %s"), EMCsInputLocationRule::Get().ToDisplayNameChar(LocationRule), *(Location.ToString()));
						ValidCompareValue = true;
					}
					// Rotation
					const FRotator3f& Rotation				 = CompareValue.Rotation;
					const ECsInputRotationRule& RotationRule = CompareValue.RotationRule;

					if (RotationRule != ECsInputRotationRule::None)
					{
						Summary += FString::Printf(TEXT("    CompareValue: %s %s"), EMCsInputRotationRule::Get().ToDisplayNameChar(RotationRule), *(Rotation.ToString()));
						ValidCompareValue = true;
					}
				}

				if (ValidCompareValue)
					Summary += TEXT("\n");

				// CompletedValue
				const FCsInputCompletedValue& CompletedValue = Desc.CompletedValue;
				{
					const ECsInputValue& ValueType					   = CompletedValue.ValueType;
					const ECsInputCompletedValueReturnType& ReturnType = CompletedValue.ReturnType;

					if (ValueType != ECsInputValue::Void &&
						ReturnType != ECsInputCompletedValueReturnType::PassThrough)
					{
						// Float
						if (ValueType == ECsInputValue::Float)
						{
							Summary += FString::Printf(TEXT("    CompletedValue: %f"), CompletedValue.Value);
						}
						// Location
						if (ValueType == ECsInputValue::Vector)
						{
							Summary += FString::Printf(TEXT("    CompletedValue: %s"), *(CompletedValue.Location.ToString()));
						}
						// Rotation
						if (ValueType == ECsInputValue::Rotator)
						{
							Summary += FString::Printf(TEXT("    CompletedValue: %s"), *(CompletedValue.Rotation.ToString()));
						}
					}
				}

				if (K < AndInputCount - 1)
					Summary += TEXT("\n");
			}

			if (J < WordCount - 1)
				Summary += TEXT("\n");
		}

		if (I < PhraseCount - 1)
			Summary += TEXT("\n");
	}
	return Summary;
}

#pragma endregion FCsGameEventDefinition

// FCsGameEventDefinitionActionOneOrWordNoCompletedValue
#pragma region

void FCsGameEventDefinitionActionOneOrWordNoCompletedValue::AddDefinition(TSet<FCsGameEventDefinition>& GameEventDefinitions, TMap<FECsGameEvent, FCsInputSentence>& InputSentenceByGameEventMap) const
{
	check(IsValid());
	// Check if a sentence has ALREADY been added to InputSentenceByGameEventMap.
	checkf(!InputSentenceByGameEventMap.Find(GameEvent), TEXT("GameEvent: %s is already Set in GameEventDefintions and InputSentenceByGameEventMap."), GameEvent.ToChar());

	// Sentence
	FCsInputSentence Sentence;
	Sentence.Reset();
	Sentence.Phrases.AddDefaulted();
		// Phrase
	FCsInputPhrase& Phrase = Sentence.Phrases.Last();
	Phrase.Words.AddDefaulted();
			// Word
	FCsInputWord& Word = Phrase.Words.Last();

	for (const FCsInputActionAndEvent& Pair : Words)
	{
		Word.OrInputs.AddDefaulted();
		// Description
		FCsInputDescription& Description = Word.OrInputs.Last();
		Description.Action = Pair.Action;
		Description.Event  = Pair.Event;
			// CompareValue
		FCsInputCompareValue& CompareValue = Description.CompareValue;
		CompareValue.ValueType = ECsInputValue::Void;
		CompareValue.ValueRule = ECsInputValueRule::None;
			// CompletedValue
		FCsInputCompletedValue& CompletedValue = Description.CompletedValue;
		CompletedValue.ValueType  = ECsInputValue::Void;
		CompletedValue.ReturnType = ECsInputCompletedValueReturnType::PassThrough;
	}

	FCsGameEventDefinition GameEventDefinition;
	GameEventDefinition.Event	 = GameEvent;
	GameEventDefinition.Sentence = Sentence;

	GameEventDefinitions.Add(GameEventDefinition);

	InputSentenceByGameEventMap.Add(GameEvent, Sentence);
}

FString FCsGameEventDefinitionActionOneOrWordNoCompletedValue::PrintSummary() const
{
	FString Summary;

	if (!IsValid())
		return Summary;

	// GameEvent
	//  Action Event
	//  Action Event
	//  ...
	Summary += GameEvent.GetName();
	Summary += TEXT("\n");

	const int32 Count = Words.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const FCsInputActionAndEvent& Word = Words[I];

		Summary += TEXT(" ") + Word.Action.GetName() + TEXT(" ") + EMCsInputEvent::Get().ToString(Word.Event);

		if (I < Count - 1)
			Summary += TEXT("\n");
	}

	return Summary;
}

#pragma endregion FCsGameEventDefinitionActionOneOrWordNoCompletedValue

// FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue
#pragma region

void FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue::AddDefinition(TSet<FCsGameEventDefinition>& GameEventDefinitions, TMap<FECsGameEvent, FCsInputSentence>& InputSentenceByGameEventMap) const
{
	check(IsValid());
	// Check if a sentence has ALREADY been added to InputSentenceByGameEventMap.
	checkf(!InputSentenceByGameEventMap.Find(GameEvent), TEXT("GameEvent: %s is already Set in GameEventDefintions and InputSentenceByGameEventMap."), GameEvent.ToChar());

	// Sentence
	FCsInputSentence Sentence;
	Sentence.Reset();
	Sentence.Phrases.AddDefaulted();
		// Phrase
	FCsInputPhrase& Phrase = Sentence.Phrases.Last();
	Phrase.Words.AddDefaulted();
			// Word
	FCsInputWord& Word = Phrase.Words.Last();

	for (const FECsInputAction& Action : Actions)
	{
		Word.OrInputs.AddDefaulted();
		// Description
		FCsInputDescription& Description = Word.OrInputs.Last();
		Description.Action = Action;
		Description.Event  = Event;
			// CompareValue
		FCsInputCompareValue& CompareValue = Description.CompareValue;
		CompareValue.ValueType = ECsInputValue::Void;
		CompareValue.ValueRule = ECsInputValueRule::None;
			// CompletedValue
		FCsInputCompletedValue& CompletedValue = Description.CompletedValue;
		CompletedValue.ValueType  = ECsInputValue::Void;
		CompletedValue.ReturnType = ECsInputCompletedValueReturnType::PassThrough;
	}

	FCsGameEventDefinition GameEventDefinition;
	GameEventDefinition.Event	 = GameEvent;
	GameEventDefinition.Sentence = Sentence;

	GameEventDefinitions.Add(GameEventDefinition);

	InputSentenceByGameEventMap.Add(GameEvent, Sentence);
}

FString FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue::PrintOneLineSummary() const
{
	FString Summary;

	if (!IsValid())
		return Summary;

	// GameEvent: [Action, Action, Action] Event
	Summary += GameEvent.GetName() + TEXT(": [");

	const int32 Count = Actions.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		Summary += Actions[I].GetName();

		if (I < Count - 1)
			Summary += TEXT(", ");
	}

	Summary += TEXT("] ") + EMCsInputEvent::Get().ToString(Event);

	return Summary;
}

#pragma endregion FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue

// FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue
#pragma region

void FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue::AddDefinition(TSet<FCsGameEventDefinition>& GameEventDefinitions, TMap<FECsGameEvent, FCsInputSentence>& InputSentenceByGameEventMap) const
{
	check(IsValid());
	// Check if a sentence has ALREADY been added to InputSentenceByGameEventMap.
	checkf(!InputSentenceByGameEventMap.Find(GameEvent), TEXT("GameEvent: %s is already Set in GameEventDefintions and InputSentenceByGameEventMap."), GameEvent.ToChar());

	// Sentence
	FCsInputSentence Sentence;
	Sentence.Reset();
	Sentence.Phrases.AddDefaulted();
	// Phrase
	FCsInputPhrase& Phrase = Sentence.Phrases.Last();
	Phrase.Words.AddDefaulted();
	// Word
	FCsInputWord& Word = Phrase.Words.Last();

	for (const FECsInputAction& Action : Actions)
	{
		Word.OrInputs.AddDefaulted();
		// Description
		FCsInputDescription& Description = Word.OrInputs.Last();
		Description.Action	  = Action;
		Description.bAnyEvent = true;
		// CompareValue
		FCsInputCompareValue& CompareValue = Description.CompareValue;
		CompareValue.ValueType = ECsInputValue::Float;
		CompareValue.ValueRule = ECsInputValueRule::None;
		// CompletedValue
		FCsInputCompletedValue& CompletedValue = Description.CompletedValue;
		CompletedValue.ValueType  = ECsInputValue::Float;
		CompletedValue.ReturnType = ECsInputCompletedValueReturnType::PassThrough;
	}

	FCsGameEventDefinition GameEventDefinition;
	GameEventDefinition.Event	 = GameEvent;
	GameEventDefinition.Sentence = Sentence;

	GameEventDefinitions.Add(GameEventDefinition);

	InputSentenceByGameEventMap.Add(GameEvent, Sentence);
}

FString FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue::PrintOneLineSummary() const
{
	FString Summary;

	if (!IsValid())
		return Summary;

	// GameEvent: [Action, Action, Action]
	Summary += GameEvent.GetName() + TEXT(": [");

	const int32 Count = Actions.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		Summary += Actions[I].GetName();

		if (I < Count - 1)
			Summary += TEXT(", ");
	}

	Summary += TEXT("]");

	return Summary;
}

#pragma endregion FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue