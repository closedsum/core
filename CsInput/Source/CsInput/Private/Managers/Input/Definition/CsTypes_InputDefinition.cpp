// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Definition/CsTypes_InputDefinition.h"

// Input
#include "Managers/Input/CsInputFrame.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_InputDefinition)

// InputValueRule
#pragma region

namespace NCsInputValueRule
{
	namespace Ref
	{
		typedef EMCsInputValueRule EnumMapType;

		CSINPUT_API CS_ADD_TO_ENUM_MAP(None);
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(Equal, "=");
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(NotEqual, "!=");
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(Greater, ">");
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(GreaterOrEqual, ">=");
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(Less, "<");
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(LessOrEqual, "<=");
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputValueRule_MAX, "MAX");
	}
}

#pragma endregion InputValueRule

// InputLocationRule
#pragma region

namespace NCsInputLocationRule
{
	namespace Ref
	{
		typedef EMCsInputLocationRule EnumMapType;

		CSINPUT_API CS_ADD_TO_ENUM_MAP(None);
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(Equal, "=");
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(NotEqual, "!=");
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputLocationRule_MAX, "MAX");
	}
}

#pragma endregion InputLocationRule

// InputRotationRule
#pragma region

namespace NCsInputRotationRule
{
	namespace Ref
	{
		typedef EMCsInputRotationRule EnumMapType;

		CSINPUT_API CS_ADD_TO_ENUM_MAP(None);
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(Equal, "=");
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(NotEqual, "!=");
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputRotationRule_MAX, "MAX");
	}
}

#pragma endregion InputRotationRule

// InputCompletedValueReturnType
#pragma region

namespace NCsInputCompletedValueReturnType
{
	namespace Ref
	{
		typedef EMCsInputCompletedValueReturnType EnumMapType;

		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(PassThrough, "Pass Through");
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Defined);
		CSINPUT_API CS_ADD_TO_ENUM_MAP(Average);
		CSINPUT_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputCompletedValueReturnType_MAX, "MAX");
	}
}

#pragma endregion InputCompletedValueReturnType

// FCsInputWord
#pragma region

void FCsInputWord::AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector3f& Location, const FRotator3f& Rotation)
{
	AndInputs.AddDefaulted();
	const int32 Index = AndInputs.Num() - 1;
	AndInputs[Index].Action = Action;
	AndInputs[Index].Event = Event;
	AndInputs[Index].CompareValue.Value = Value;
	AndInputs[Index].CompareValue.Location = Location;
	AndInputs[Index].CompareValue.Rotation = Rotation;
}

void FCsInputWord::AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event)
{
	AddAndInput(Action, Event, 0.0f, FVector3f::ZeroVector, FRotator3f::ZeroRotator);
}

void FCsInputWord::AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value)
{
	AddAndInput(Action, Event, Value, FVector3f::ZeroVector, FRotator3f::ZeroRotator);
}

void FCsInputWord::AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FVector3f& Location)
{
	AddAndInput(Action, Event, 0.0f, Location, FRotator3f::ZeroRotator);
}

void FCsInputWord::AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FRotator3f& Rotation)
{
	AddAndInput(Action, Event, 0.0f, FVector3f::ZeroVector, Rotation);
}

void FCsInputWord::AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector3f& Location, const FRotator3f& Rotation)
{
	OrInputs.AddDefaulted();
	const int32 Index = OrInputs.Num() - 1;
	OrInputs[Index].Action = Action;
	OrInputs[Index].Event = Event;
	OrInputs[Index].CompareValue.Value = Value;
	OrInputs[Index].CompareValue.Location = Location;
	OrInputs[Index].CompareValue.Rotation = Rotation;
}

void FCsInputWord::AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event)
{
	AddOrInput(Action, Event, 0.0f, FVector3f::ZeroVector, FRotator3f::ZeroRotator);
}

void FCsInputWord::AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value)
{
	AddOrInput(Action, Event, Value, FVector3f::ZeroVector, FRotator3f::ZeroRotator);
}

void FCsInputWord::AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FVector3f& Location)
{
	AddOrInput(Action, Event, 0.0f, Location, FRotator3f::ZeroRotator);
}

void FCsInputWord::AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FRotator3f& Rotation)
{
	AddOrInput(Action, Event, 0.0f, FVector3f::ZeroVector, Rotation);
}

void FCsInputWord::ProcessInput(FCsInputFrame* InputFrame)
{
	int32 And = 0;
	bool Or = false;

	const int32 Count = InputFrame->Inputs.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		FCsInput* Input = InputFrame->Inputs[I];

		// Check And
		const int32 AndCount = AndInputs.Num();

		for (int32 J = And; J < AndCount; ++J)
		{
			if (AndInputs[J].Pass(*Input))
			{
				++And;
			}
		}
		// Check Or
		const int32 OrCount = OrInputs.Num();

		for (FCsInputDescription& OrInput : OrInputs)
		{
			Or |= OrInput.Pass(*Input);

			if (Or)
				break;
		}

		const bool PassAnd = AndCount == 0 || (And > 0 && And == AndCount);
		const bool PassOr  = OrCount == 0 || Or;

		bCompleted = PassAnd && PassOr;

		if (bCompleted)
		{
			if (bConsume)
				InputFrame->Inputs.RemoveAt(I, 1, EAllowShrinking::No);
			CompletedTime = InputFrame->Time.Time;

			// Populate Completed Values
			
				// And
			for (const FCsInputDescription& AndInput : AndInputs)
			{
				if (AndInput.HasPassed())
					CompletedValues.Add(AndInput.CompletedValue);
			}
				// Or
			for (const FCsInputDescription& OrInput : OrInputs)
			{
				if (OrInput.HasPassed())
					CompletedValues.Add(OrInput.CompletedValue);
			}
			break;
		}
	}
}

#pragma endregion FCsInputWord

// FCsInputPhrase
#pragma region

void FCsInputPhrase::AddAndInputToWord(const int32& Index, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value /*=0.0f*/, const FVector3f& Location /*=FVector3f::ZeroVector*/, const FRotator3f& Rotation /*=FRotator3f::ZeroRotator*/)
{
	const int32 Count = Words.Num();

	if (Index >= Count)
	{
		for (int32 I = 0; I < Index - Count + 1; ++I)
		{
			Words.AddDefaulted();
		}
	}
	Words[Index].AddAndInput(Action, Event, Value, Location, Rotation);
}

void FCsInputPhrase::AddOrInputToWord(const int32& Index, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value /*=0.0f*/, const FVector3f& Location /*=FVector3f::ZeroVector*/, const FRotator3f& Rotation /*=FRotator3f::ZeroRotator*/)
{
	const int32 Count = Words.Num();

	if (Index >= Count)
	{
		for (int32 I = 0; I < Index - Count + 1; ++I)
		{
			Words.AddDefaulted();
		}
	}
	Words[Index].AddOrInput(Action, Event, Value, Location, Rotation);
}

void FCsInputPhrase::ProcessInput(FCsInputFrame* InputFrame)
{
	const float& CurrentTime = InputFrame->Time.Time;

	// Check if ALL Words are Completed
	const int32 Count = Words.Num();
	int32 Index		  = 0;

	if (bInterval)
	{
		float ElapsedTime			= 0.0f;
		float EarliestCompletedTime = CurrentTime;

		for (Index = 0; Index < Count; ++Index)
		{
			if (Words[Index].IsCompleted())
			{
				if (Words[Index].CompletedTime < EarliestCompletedTime)
					EarliestCompletedTime = Words[Index].CompletedTime;

				if (CurrentTime - EarliestCompletedTime > Interval)
				{
					Reset();

					Index = 0;
					break;
				}
			}

			Words[Index].ProcessInput(InputFrame);

			if (Index < Count - 1 || !Words[Index].IsCompleted())
				break;
		}
	}
	else
	{
		for (Index = 0; Index < Count; ++Index)
		{
			if (Words[Index].IsCompleted())
				continue;

			Words[Index].ProcessInput(InputFrame);

			if (Index < Count - 1 || !Words[Index].IsCompleted())
				break;
		}

		if (Index != Count)
			Reset();
	}
	// Check if Completed
	if (Index > 0 && Index == Count)
	{
		bCompleted	  = true;
		CompletedTime = CurrentTime;

		// Populate Completed Values
		for (const FCsInputWord& Word : Words)
		{
			CompletedValues.Append(Word.CompletedValues);
		}
	}
}

#pragma endregion FCsInputPhrase

// FCsInputSentence
#pragma region

void FCsInputSentence::ProcessInput(FCsInputFrame* InputFrame)
{
	const float& CurrentTime = InputFrame->Time.Time;

	// Check if Cooldown has Expired
	if (!bActive)
	{
		if (CurrentTime - CompletedTime >= Cooldown)
			Reset();
		else
			return;
	}
	// Check if ALL Phrases are Completed
	const int32 Count = Phrases.Num();
	int32 Index		  = 0;

	if (bInterval)
	{
		float ElapsedTime			= 0.0f;
		float EarliestCompletedTime = CurrentTime;

		for (Index = 0; Index < Count; ++Index)
		{
			if (Phrases[Index].IsCompleted())
			{
				if (Phrases[Index].CompletedTime < EarliestCompletedTime)
					EarliestCompletedTime = Phrases[Index].CompletedTime;

				if (CurrentTime - EarliestCompletedTime > Interval)
				{
					Reset();

					Index = 0;
					break;
				}
			}

			Phrases[Index].ProcessInput(InputFrame);

			if (Index < Count - 1 || !Phrases[Index].IsCompleted())
				break;
		}
	}
	else
	{
		for (Index = 0; Index < Count; ++Index)
		{
			if (Phrases[Index].IsCompleted())
				continue;

			Phrases[Index].ProcessInput(InputFrame);

			if (Index < Count - 1 || !Phrases[Index].IsCompleted())
				break;
		}

		if (Index != Count)
			Reset();
	}
	// Check if Completed
	if (Count > 0 && Index == Count)
	{
		bCompleted	  = true;
		CompletedTime = CurrentTime;
		bActive		  = false;

		// Populate Completed Values
		for (const FCsInputPhrase& Phrase : Phrases)
		{
			CompletedValues.Append(Phrase.CompletedValues);
		}
	}
}

#pragma endregion FCsInputSentence