// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsTypes_Input.h"
#include "CsCore.h"

// Settings
#include "Settings/CsDeveloperSettings.h"
#include "GameFramework/InputSettings.h"
// Input
#include "Managers/Input/CsInputFrame.h"

// InputDevice
#pragma region

namespace NCsInputDevice
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputDevice, MouseAndKeyboard, "Mouse and Keyboard");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputDevice, Gamepad);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputDevice, MotionController, "Motion Controller");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputDevice, ECsInputDevice_MAX, "MAX");
	}
}

#pragma endregion InputDevice

// InputType
#pragma region

namespace NCsInputType
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Action);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Axis);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Trigger);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Location);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Rotation);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputType, ECsInputType_MAX, "MAX");
	}
}

#pragma endregion InputType

// InputEvent
#pragma region

namespace NCsInputEvent
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, FirstPressed, "First Pressed");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputEvent, Pressed);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, FirstReleased, "First Released");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputEvent, Released);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, FirstMoved, "First Moved");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputEvent, Moved);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, FirstStationary, "First Stationary");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputEvent, Stationary);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, ECsInputEvent_MAX, "MAX");
	}
}

#pragma endregion InputEvent

// InputValue
#pragma region

namespace NCsInputValue
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputValue, Void);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputValue, Float);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputValue, Vector);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputValue, Rotator);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputValue, ECsInputValue_MAX, "MAX");
	}
}

#pragma endregion InputValue

// InputActionMap
#pragma region

namespace NCsInputActionMap
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>())
		{
#if WITH_EDITOR
			EMCsInputActionMap::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

			const TArray<FCsSettings_Enum>& Enums = Settings->GetSettingsEnum<FECsInputActionMap>();
			const FString EnumSettingsPath		  = Settings->GetSettingsEnumPath<FECsInputActionMap>();

			if (Enums.Num() > CS_EMPTY)
			{
				for (const FCsSettings_Enum& Enum : Enums)
				{
					const FString& Name		   = Enum.Name;
					const FString& DisplayName = Enum.DisplayName;

					if (Name.IsEmpty())
					{
						UE_LOG(LogCs, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
						return;
					}

					checkf(!EMCsInputActionMap::Get().IsValidEnum(Name), TEXT("%s: InputActionMap (Name): %s already exists (declared in native)."), *Context, *Name);

					if (!Enum.DisplayName.IsEmpty())
					{
						checkf(!EMCsInputActionMap::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: InputActionMap (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

						EMCsInputActionMap::Get().Create(Name, DisplayName, true);
					}
					else
					{
						EMCsInputActionMap::Get().Create(Name, true);
					}
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
			}
		}
	}
}

#pragma endregion InputActionMap

// InputAction
#pragma region

namespace NCsInputAction
{
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
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputValueRule, None);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputValueRule, Equal, "=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputValueRule, NotEqual, "!=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputValueRule, Greater, ">");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputValueRule, GreaterOrEqual, ">=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputValueRule, Less, "<");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputValueRule, LessOrEqual, "<=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputValueRule, ECsInputValueRule_MAX, "MAX");
	}
}

#pragma endregion InputValueRule

// InputLocationRule
#pragma region

namespace NCsInputLocationRule
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputLocationRule, None);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputLocationRule, Equal, "=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputLocationRule, NotEqual, "!=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputLocationRule, ECsInputLocationRule_MAX, "MAX");
	}
}

#pragma endregion InputLocationRule

// InputRotationRule
#pragma region

namespace NCsInputRotationRule
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputRotationRule, None);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputRotationRule, Equal, "=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputRotationRule, NotEqual, "!=");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputRotationRule, ECsInputRotationRule_MAX, "MAX");
	}
}

#pragma endregion InputRotationRule

// InputCompletedValueReturnType
#pragma region

namespace NCsInputCompletedValueReturnType
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputCompletedValueReturnType, PassThrough, "Pass Through");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputCompletedValueReturnType, Defined);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputCompletedValueReturnType, Average);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputCompletedValueReturnType, ECsInputCompletedValueReturnType_MAX, "MAX");
	}
}

#pragma endregion InputCompletedValueReturnType

// FCsInputWord
#pragma region

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

		bCompleted = (And > 0 && And == AndCount) || Or;

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
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>())
		{
#if WITH_EDITOR
			EMCsGameEvent::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

			const TArray<FCsSettings_Enum>& Enums = Settings->GetSettingsEnum<FECsGameEvent>();
			const FString EnumSettingsPath		  = Settings->GetSettingsEnumPath<FECsGameEvent>();

			if (Enums.Num() > CS_EMPTY)
			{
				for (const FCsSettings_Enum& Enum : Enums)
				{
					const FString& Name		   = Enum.Name;
					const FString& DisplayName = Enum.DisplayName;

					if (Name.IsEmpty())
					{
						UE_LOG(LogCs, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
						return;
					}

					checkf(!EMCsGameEvent::Get().IsValidEnum(Name), TEXT("%s: GameEvent (Name): %s already exists (declared in native)."), *Context, *Name);

					if (!Enum.DisplayName.IsEmpty())
					{
						checkf(!EMCsGameEvent::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: GameEvent (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

						EMCsGameEvent::Get().Create(Name, DisplayName, true);
					}
					else
					{
						EMCsGameEvent::Get().Create(Name, true);
					}
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
			}
		}
	}
}

#pragma endregion GameEvent