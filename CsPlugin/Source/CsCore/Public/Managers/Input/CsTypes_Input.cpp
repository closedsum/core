// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsTypes_Input.h"
#include "CsCore.h"

// Settings
#include "Settings/CsDeveloperSettings.h"
#include "GameFramework/InputSettings.h"
// Input
#include "Managers/Input/CsInputFrame.h"
// Utility
#include "Utility/CsLog.h"
#include "Utility/CsPopulateEnumMapFromSettings.h"

// InputDevice
#pragma region

namespace NCsInputDevice
{
	namespace Ref
	{
		typedef EMCsInputDevice EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(MouseAndKeyboard, "Mouse and Keyboard");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Gamepad);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(MotionController, "Motion Controller");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputDevice_MAX, "MAX");
	}
}

#pragma endregion InputDevice

// InputMode
#pragma region

namespace NCsInputMode
{
	namespace Ref
	{
		typedef EMCsInputMode EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Mouse);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Keyboard);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Gamepad);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Touch);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(MotionController, "Motion Controller");
	}

	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 31; // 1 + 2 + 4 + 8 + 16
}

#pragma endregion InputMode

// InputType
#pragma region

namespace NCsInputType
{
	namespace Ref
	{
		typedef EMCsInputType EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Action);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Axis);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Trigger);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Location);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Rotation);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputType_MAX, "MAX");
	}
}

#pragma endregion InputType

// InputEvent
#pragma region

namespace NCsInputEvent
{
	namespace Ref
	{
		typedef EMCsInputEvent EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstPressed, "First Pressed");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Pressed);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstReleased, "First Released");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Released);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstMoved, "First Moved");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Moved);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstStationary, "First Stationary");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Stationary);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputEvent_MAX, "MAX");
	}
}

#pragma endregion InputEvent

// InputValue
#pragma region

namespace NCsInputValue
{
	namespace Ref
	{
		typedef EMCsInputValue EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Void);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Float);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Vector);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Rotator);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputValue_MAX, "MAX");
	}
}

#pragma endregion InputValue

// InputActionMap
#pragma region

namespace NCsInputActionMap
{
	namespace Str
	{
		const FString InputActionMap = TEXT("InputActionMap");
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>())
		{
#if WITH_EDITOR
			EMCsInputActionMap::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

			FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsDeveloperSettings, EMCsInputActionMap, FECsInputActionMap>(Context, Str::InputActionMap, &FCsLog::Warning);
		}
	}
}

#pragma endregion InputActionMap

// InputAction
#pragma region

namespace NCsInputAction
{
	// Mouse
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MousePositionXY__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MouseLeftButton__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MouseRightButton__);
	// Touch
		// Action
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__Touch_0__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__Touch_1__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__Touch_2__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__Touch_3__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__Touch_4__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__Touch_5__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__Touch_6__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__Touch_7__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__Touch_8__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__Touch_9__);
		// Location
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_0__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_1__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_2__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_3__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_4__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_5__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_6__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_7__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_8__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_9__);

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UInputSettings* Settings = GetMutableDefault<UInputSettings>())
		{
#if WITH_EDITOR
			EMCsInputAction::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

			// Add ActionMappings
			for (const FInputActionKeyMapping& Mapping : Settings->GetActionMappings())
			{
				const FName& Name = Mapping.ActionName;

				if (!EMCsInputAction::Get().IsValidEnum(Name))
					EMCsInputAction::Get().Create(Name.ToString(), true);
			}
			// Add AxisMappings
			for (const FInputAxisKeyMapping& Mapping : Settings->GetAxisMappings())
			{
				const FName& Name = Mapping.AxisName;

				if (!EMCsInputAction::Get().IsValidEnum(Name))
					EMCsInputAction::Get().Create(Name.ToString(), true);
			}
		}
	}
}

#pragma endregion InputAction

// InputValueRule
#pragma region

namespace NCsInputValueRule
{
	namespace Ref
	{
		typedef EMCsInputValueRule EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(None);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(Equal, "=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(NotEqual, "!=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(Greater, ">");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(GreaterOrEqual, ">=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(Less, "<");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(LessOrEqual, "<=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputValueRule_MAX, "MAX");
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

		CSCORE_API CS_ADD_TO_ENUM_MAP(None);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(Equal, "=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(NotEqual, "!=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputLocationRule_MAX, "MAX");
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

		CSCORE_API CS_ADD_TO_ENUM_MAP(None);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(Equal, "=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(NotEqual, "!=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputRotationRule_MAX, "MAX");
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

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PassThrough, "Pass Through");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Defined);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Average);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInputCompletedValueReturnType_MAX, "MAX");
	}
}

#pragma endregion InputCompletedValueReturnType

// FCsInputWord
#pragma region

void FCsInputWord::AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector& Location, const FRotator& Rotation)
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
	AddAndInput(Action, Event, 0.0f, FVector::ZeroVector, FRotator::ZeroRotator);
}

void FCsInputWord::AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value)
{
	AddAndInput(Action, Event, Value, FVector::ZeroVector, FRotator::ZeroRotator);
}

void FCsInputWord::AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FVector& Location)
{
	AddAndInput(Action, Event, 0.0f, Location, FRotator::ZeroRotator);
}

void FCsInputWord::AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FRotator& Rotation)
{
	AddAndInput(Action, Event, 0.0f, FVector::ZeroVector, Rotation);
}

void FCsInputWord::AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector& Location, const FRotator& Rotation)
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
	AddOrInput(Action, Event, 0.0f, FVector::ZeroVector, FRotator::ZeroRotator);
}

void FCsInputWord::AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value)
{
	AddOrInput(Action, Event, Value, FVector::ZeroVector, FRotator::ZeroRotator);
}

void FCsInputWord::AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FVector& Location)
{
	AddOrInput(Action, Event, 0.0f, Location, FRotator::ZeroRotator);
}

void FCsInputWord::AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FRotator& Rotation)
{
	AddOrInput(Action, Event, 0.0f, FVector::ZeroVector, Rotation);
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
				InputFrame->Inputs.RemoveAt(I, 1, false);
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

void FCsInputPhrase::AddAndInputToWord(const int32& Index, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value /*=0.0f*/, const FVector& Location /*=FVector::ZeroVector*/, const FRotator& Rotation /*=FRotator::ZeroRotator*/)
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

void FCsInputPhrase::AddOrInputToWord(const int32& Index, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value /*=0.0f*/, const FVector& Location /*=FVector::ZeroVector*/, const FRotator& Rotation /*=FRotator::ZeroRotator*/)
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

// ControllerHand
#pragma region

namespace NCsControllerHand
{
	namespace Ref
	{
		CSCORE_API const Type Left = EMCsControllerHand::Get().Add(Type::Left, TEXT("Left"));
		CSCORE_API const Type Right = EMCsControllerHand::Get().Add(Type::Right, TEXT("Right"));
		CSCORE_API const Type ECsControllerHand_MAX = EMCsControllerHand::Get().Add(Type::ECsControllerHand_MAX, TEXT("ECsControllerHand_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsControllerHand_MAX;
}

#pragma endregion ControllerHand

// GameEvent
#pragma region

namespace NCsGameEvent
{
	namespace Str
	{
		const FString GameEvent = TEXT("GameEvent");
	}

	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MousePositionXY__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MouseLeftButtonPressed__);
	CSCORE_API CS_CREATE_ENUM_STRUCT(Default__MouseRightButtonPressed__);

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>())
		{
#if WITH_EDITOR
			EMCsGameEvent::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

			FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsDeveloperSettings, EMCsGameEvent, FECsGameEvent>(Context, Str::GameEvent, &FCsLog::Warning);
		}
	}
}

#pragma endregion GameEvent

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
					const FVector& Location					 = CompareValue.Location;
					const ECsInputLocationRule& LocationRule = CompareValue.LocationRule;

					if (LocationRule != ECsInputLocationRule::None)
					{
						Summary += FString::Printf(TEXT("    CompareValue: %s %s"), EMCsInputLocationRule::Get().ToDisplayNameChar(LocationRule), *(Location.ToString()));
						ValidCompareValue = true;
					}
					// Rotation
					const FRotator& Rotation				 = CompareValue.Rotation;
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
					const FVector& Location					 = CompareValue.Location;
					const ECsInputLocationRule& LocationRule = CompareValue.LocationRule;

					if (LocationRule != ECsInputLocationRule::None)
					{
						Summary += FString::Printf(TEXT("    CompareValue: %s %s"), EMCsInputLocationRule::Get().ToDisplayNameChar(LocationRule), *(Location.ToString()));
						ValidCompareValue = true;
					}
					// Rotation
					const FRotator& Rotation				 = CompareValue.Rotation;
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