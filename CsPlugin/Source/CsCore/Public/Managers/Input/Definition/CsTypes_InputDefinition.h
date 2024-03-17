// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Input
#include "Types/CsTypes_Macro.h"
#include "Managers/Input/CsInput.h"

#include "CsTypes_InputDefinition.generated.h"

// InputValueRule
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsInputValueRule : uint8
{
	None					UMETA(DisplayName = "None"),
	Equal					UMETA(DisplayName = "=="),
	NotEqual				UMETA(DisplayName = "!="),
	Greater					UMETA(DisplayName = ">"),
	GreaterOrEqual			UMETA(DisplayName = ">="),
	Less					UMETA(DisplayName = "<"),
	LessOrEqual			    UMETA(DisplayName = "<="),
	ECsInputValueRule_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsInputValueRule : public TCsEnumMap<ECsInputValueRule>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInputValueRule, ECsInputValueRule)
};

namespace NCsInputValueRule
{
	typedef ECsInputValueRule Type;

	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type Equal;
		extern CSCORE_API const Type NotEqual;
		extern CSCORE_API const Type Greater;
		extern CSCORE_API const Type GreaterOrEqual;
		extern CSCORE_API const Type Less;
		extern CSCORE_API const Type LessOrEqual;
		extern CSCORE_API const Type ECsInputValueRule_MAX;
	}
}

#pragma endregion InputValueRule

// InputLocationRule
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsInputLocationRule : uint8
{
	None						UMETA(DisplayName = "None"),
	Equal						UMETA(DisplayName = "=="),
	NotEqual					UMETA(DisplayName = "!="),
	ECsInputLocationRule_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsInputLocationRule : public TCsEnumMap<ECsInputLocationRule>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInputLocationRule, ECsInputLocationRule)
};

namespace NCsInputLocationRule
{
	typedef ECsInputLocationRule Type;

	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type Equal;
		extern CSCORE_API const Type NotEqual;
		extern CSCORE_API const Type ECsInputLocationRule_MAX;
	}
}

#pragma endregion InputLocationRule

// InputRotationRule
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsInputRotationRule : uint8
{
	None						UMETA(DisplayName = "None"),
	Equal						UMETA(DisplayName = "=="),
	NotEqual					UMETA(DisplayName = "!="),
	ECsInputRotationRule_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsInputRotationRule : public TCsEnumMap<ECsInputRotationRule>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInputRotationRule, ECsInputRotationRule)
};

namespace NCsInputRotationRule
{
	typedef ECsInputRotationRule Type;

	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type Equal;
		extern CSCORE_API const Type NotEqual;
		extern CSCORE_API const Type ECsInputRotationRule_MAX;
	}
}

#pragma endregion InputRotationRule

// FCsInputCompareValue
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsInputCompareValue
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	ECsInputValue ValueType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	float Value;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	ECsInputValueRule ValueRule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	FVector3f Location;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	ECsInputLocationRule LocationRule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	FRotator3f Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	ECsInputRotationRule RotationRule;

	FCsInputCompareValue() :
		ValueType(ECsInputValue::Void),
		Value(0.0f),
		ValueRule(ECsInputValueRule::None),
		Location(0.0f),
		LocationRule(ECsInputLocationRule::None),
		Rotation(0.0f),
		RotationRule(ECsInputRotationRule::None)
	{
	}

	FORCEINLINE bool operator==(const FCsInputCompareValue& B) const
	{
		return  ValueType == B.ValueType &&
				Value == B.Value &&
				ValueRule == B.ValueRule &&
				Location == B.Location &&
				LocationRule == B.LocationRule &&
				Rotation == B.Rotation &&
				RotationRule == B.RotationRule;
	}

	FORCEINLINE bool operator!=(const FCsInputCompareValue& B) const
	{
		return !(*this == B);
	}

	bool Pass(const FCsInput& Input) const
	{
		// None | Void
		if (ValueType == ECsInputValue::Void)
			return true;
		// Value | Float
		if (ValueType == ECsInputValue::Float)
		{
			if (ValueRule != ECsInputValueRule::None)
			{
				// ==
				if (ValueRule == ECsInputValueRule::Equal)
					return Input.Value == Value;
				// !=
				if (ValueRule == ECsInputValueRule::NotEqual)
					return Input.Value != Value;
				// >
				if (ValueRule == ECsInputValueRule::Greater)
					return Input.Value > Value;
				// >=
				if (ValueRule == ECsInputValueRule::GreaterOrEqual)
					return Input.Value >= Value;
				// <
				if (ValueRule == ECsInputValueRule::Less)
					return Input.Value < Value;
				// <=
				if (ValueRule == ECsInputValueRule::LessOrEqual)
					return Input.Value <= Value;
			}
			return true;
		}
		// Location | Vector
		if (ValueType == ECsInputValue::Vector)
		{
			if (LocationRule != ECsInputLocationRule::None)
			{
				// ==
				if (LocationRule == ECsInputLocationRule::Equal)
					return Input.Location == Location;
				// !=
				if (LocationRule == ECsInputLocationRule::NotEqual)
					return Input.Location != Location;
			}
			return true;
		}
		// Rotation | Rotator
		if (ValueType == ECsInputValue::Rotator)
		{
			if (RotationRule != ECsInputRotationRule::None)
			{
				// ==
				if (RotationRule == ECsInputRotationRule::Equal)
					return Input.Rotation == Rotation;
				// !=
				if (RotationRule == ECsInputRotationRule::NotEqual)
					return Input.Rotation != Rotation;
			}
		}
		return true;
	}
};

#pragma endregion FCsInputCompareValue

// InputCompletedValueReturnType
#pragma region

/**
*/

UENUM(BlueprintType)
enum class ECsInputCompletedValueReturnType : uint8
{
	PassThrough								UMETA(DisplayName = "Pass Through"),
	Defined									UMETA(DisplayName = "Defined"),
	Average									UMETA(DisplayName = "Average"),
	ECsInputCompletedValueReturnType_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsInputCompletedValueReturnType : public TCsEnumMap<ECsInputCompletedValueReturnType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInputCompletedValueReturnType, ECsInputCompletedValueReturnType)
};

namespace NCsInputCompletedValueReturnType
{
	typedef ECsInputCompletedValueReturnType Type;

	namespace Ref
	{
		extern CSCORE_API const Type PassThrough;
		extern CSCORE_API const Type Defined;
		extern CSCORE_API const Type Average;
		extern CSCORE_API const Type ECsInputCompletedValueReturnType_MAX;
	}
}

#pragma endregion InputCompletedValueReturnType

// FCsInputCompletedValue
#pragma region

/**
*
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsInputCompletedValue
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition")
	ECsInputValue ValueType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition")
	ECsInputCompletedValueReturnType ReturnType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	float Value;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	FVector3f Location;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	FRotator3f Rotation;

	FCsInputCompletedValue() :
		ValueType(ECsInputValue::Void),
		ReturnType(ECsInputCompletedValueReturnType::PassThrough),
		Value(0.0f),
		Location(0.0f),
		Rotation(0.0f)
	{
	}

	FORCEINLINE bool operator==(const FCsInputCompletedValue& B) const
	{
		return  ValueType == B.ValueType &&
				ReturnType == B.ReturnType &&
				Value == B.Value &&
				Location == B.Location &&
				Rotation == B.Rotation;
	}

	FORCEINLINE bool operator!=(const FCsInputCompletedValue& B) const
	{
		return !(*this == B);
	}

	// TODO: FUTURE: For now only handle Pass Through
	void OnPass(const FCsInput& Input)
	{
		if (ValueType == ECsInputValue::Void)
			return;

		// Value | Float
		if (ValueType == ECsInputValue::Float)
		{
			// Pass Through
			if (ReturnType == ECsInputCompletedValueReturnType::PassThrough)
			{
				Value = Input.Value;
			}
		}
		// Location | Vector
		else
		if (ValueType == ECsInputValue::Vector)
		{
			// Pass Through
			if (ReturnType == ECsInputCompletedValueReturnType::PassThrough)
			{
				Location = Input.Location;
			}
		}
		// Rotation | Rotator
		else
		if (ValueType == ECsInputValue::Rotator)
		{
			// Pass Through
			if (ReturnType == ECsInputCompletedValueReturnType::PassThrough)
			{
				Rotation = Input.Rotation;
			}
		}
	}
};

#pragma endregion FCsInputCompletedValue

// FCsInputDescription
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsInputDescription
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input|Definition")
	bool bPass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	FECsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	ECsInputEvent Event;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	bool bAnyEvent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	FCsInputCompareValue CompareValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input|Definition")
	FCsInputCompletedValue CompletedValue;

	FCsInputDescription() :
		bPass(false),
		Action(),
		Event(ECsInputEvent::ECsInputEvent_MAX),
		bAnyEvent(false),
		CompareValue(),
		CompletedValue()
	{
	}

	FORCEINLINE bool operator==(const FCsInputDescription& B) const
	{
		return  Action == B.Action &&
				Event == B.Event &&
				bAnyEvent == B.bAnyEvent &&
				CompareValue == B.CompareValue &&
				CompletedValue == B.CompletedValue;
	}

	FORCEINLINE bool operator!=(const FCsInputDescription& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE bool IsValid() const
	{
		return EMCsInputAction::Get().IsValidEnum(Action) && (bAnyEvent || Event != ECsInputEvent::ECsInputEvent_MAX);
	}

	FORCEINLINE bool HasPassed() const { return bPass; }

	FORCEINLINE bool Pass(const FCsInput& Input)
	{
		bPass = false;

		if (Input.Action != Action)
			return bPass;

		if (!bAnyEvent && Input.Event != Event)
			return bPass;

		bPass = CompareValue.Pass(Input);

		if (bPass)
			CompletedValue.OnPass(Input);

		return bPass;
	}

	FORCEINLINE bool HasPassedWith(const ECsInputEvent& InEvent) const
	{
		return HasPassed() && InEvent == Event;
	}

	FORCEINLINE void Reset() { bPass = false; }
};

#pragma endregion FCsInputDescription

// FCsInputWord
#pragma region

struct FCsInputFrame;

/**
*
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsInputWord
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input|Definition")
	bool bCompleted;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input|Definition")
	float CompletedTime;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input|Definition")
	bool bConsume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition")
	TArray<FCsInputDescription> AndInputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition")
	TArray<FCsInputDescription> OrInputs;

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Input|Definition")
	TArray<FCsInputCompletedValue> CompletedValues;

	FCsInputWord() :
		bCompleted(false),
		CompletedTime(0.0f),
		bConsume(false),
		AndInputs(),
		OrInputs(),
		CompletedValues()
	{
	}

	FORCEINLINE bool operator==(const FCsInputWord& B) const
	{
		if (bCompleted != B.bCompleted) { return false; }
		if (CompletedTime != B.CompletedTime) { return false; }
		if (bConsume != B.bConsume) { return false; }

		if (AndInputs.Num() != B.AndInputs.Num())
			return false;

		const int32 AndCount = AndInputs.Num();

		for (int32 I = 0; I < AndCount; ++I)
		{
			if (AndInputs[I] != B.AndInputs[I])
				return false;
		}

		if (OrInputs.Num() != B.OrInputs.Num())
			return false;

		const int32 OrCount = OrInputs.Num();

		for (int32 I = 0; I < OrCount; ++I)
		{
			if (OrInputs[I] != B.OrInputs[I])
				return false;
		}

		if (CompletedValues.Num() != B.CompletedValues.Num())
			return false;

		const int32 CompletedCount = CompletedValues.Num();

		for (int32 I = 0; I < CompletedCount; ++I)
		{
			if (CompletedValues[I] != B.CompletedValues[I])
				return false;
		}
		return true;
	}
	
	FORCEINLINE bool operator!=(const FCsInputWord& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE bool IsCompleted() const { return bCompleted; }

	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector3f& Location, const FRotator3f& Rotation);
	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event);
	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value);
	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FVector3f& Location);
	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FRotator3f& Rotation);
	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector3f& Location, const FRotator3f& Rotation);
	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event);
	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value);
	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FVector3f& Location);
	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FRotator3f& Rotation);

	FORCEINLINE void Reset()
	{
		bCompleted = false;
		CompletedValues.Reset(CompletedValues.Max());
	}

	void ProcessInput(FCsInputFrame* InputFrame);

	FORCEINLINE bool IsValid() const
	{
		if (AndInputs.Num() == CS_EMPTY &&
			OrInputs.Num() == CS_EMPTY) 
		{ 
			return false; 
		}
		// And
		for (const FCsInputDescription& Input : AndInputs)
		{
			if (!Input.IsValid())
				return false;
		}
		// Or
		for (const FCsInputDescription& Input : OrInputs)
		{
			if (!Input.IsValid())
				return false;
		}
		return true;
	}

	FORCEINLINE bool HasPassedWith(const ECsInputEvent& Event) const
	{
		if (!bCompleted)
			return false;

		// And
		for (const FCsInputDescription& Input : AndInputs)
		{
			if (Input.HasPassedWith(Event))
				return true;
		}
		// Or
		for (const FCsInputDescription& Input : OrInputs)
		{
			if (Input.HasPassedWith(Event))
				return true;
		}
		return false;
	}
};

#pragma endregion FCsInputWord

// FCsInputPhrase
#pragma region

struct FCsInputFrame;

/**
*
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsInputPhrase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input|Definition")
	bool bCompleted;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input|Definition")
	float CompletedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition", meta = (ScriptName = "m_bInterval", InlineEditConditionToggle))
	bool bInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition", meta = (ScriptName = "m_Interval", editcondition = "bInterval", ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition", meta = (ScriptName = "m_bFrames", InlineEditConditionToggle))
	bool bFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition", meta = (ScriptName = "m_Frames", editcondition = "bFrames", ClampMin = "0", UIMin = "0"))
	int32 Frames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition")
	TArray<FCsInputWord> Words;

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Input|Definition")
	TArray<FCsInputCompletedValue> CompletedValues;

	FCsInputPhrase() :
		bCompleted(false),
		CompletedTime(0.0f),
		bInterval(false),
		Interval(0.0f),
		bFrames(false),
		Frames(0),
		Words(),
		CompletedValues()
	{
	}

	FORCEINLINE bool operator==(const FCsInputPhrase& B) const
	{
		if (bCompleted != B.bCompleted) { return false; }
		if (CompletedTime != B.CompletedTime) { return false; }
		if (bInterval != B.bInterval) { return false; }
		if (Interval != B.Interval) { return false; }
		if (bFrames != B.bFrames) { return false; }
		if (Frames != B.Frames) { return false; }

		if (Words.Num() != B.Words.Num())
			return false;

		const int32 WordCount = Words.Num();

		for (int32 I = 0; I < WordCount; ++I)
		{
			if (Words[I] != B.Words[I])
				return false;
		}

		if (CompletedValues.Num() != B.CompletedValues.Num())
			return false;

		const int32 CompletedCount = CompletedValues.Num();

		for (int32 I = 0; I < CompletedCount; ++I)
		{
			if (CompletedValues[I] != B.CompletedValues[I])
				return false;
		}
		return true;
	}

	FORCEINLINE bool operator!=(const FCsInputPhrase& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE bool IsCompleted() const { return bCompleted; }

	void AddAndInputToWord(const int32& Index, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value = 0.0f, const FVector3f& Location = FVector3f::ZeroVector, const FRotator3f& Rotation = FRotator3f::ZeroRotator);
	void AddOrInputToWord(const int32& Index, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value = 0.0f, const FVector3f& Location = FVector3f::ZeroVector, const FRotator3f& Rotation = FRotator3f::ZeroRotator);

	FORCEINLINE void Reset()
	{
		for (FCsInputWord& Word : Words)
		{
			Word.Reset();
		}
		bCompleted = false;
		CompletedTime = 0.0f;
		CompletedValues.Reset(CompletedValues.Max());
	}

	void ProcessInput(FCsInputFrame* InputFrame);

	FORCEINLINE bool HasPassedWith(const ECsInputEvent& Event) const
	{
		if (!bCompleted)
			return false;

		for (const FCsInputWord& Word : Words)
		{
			if (Word.HasPassedWith(Event))
				return true;
		}
		return false;
	}

	bool IsValid() const
	{
		if (Words.Num() == CS_EMPTY) { return false; }

		for (const FCsInputWord& Word : Words)
		{
			if (!Word.IsValid())
				return false;
		}
		return true;
	}
};

#pragma endregion FCsInputPhrase

// FCsInputSentence
#pragma region

struct FCsInputFrame;

/**
*
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsInputSentence
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input|Definition")
	bool bActive;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input|Definition")
	bool bCompleted;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input|Definition")
	float CompletedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition", meta = (ScriptName = "m_bInterval", InlineEditConditionToggle))
	bool bInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition", meta = (ScriptName = "m_Interval", editcondition = "bInterval", ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition", meta = (ScriptName = "m_bFrames", InlineEditConditionToggle))
	bool bFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition", meta = (ScriptName = "m_Frames", editcondition = "bFrames", ClampMin = "0", UIMin = "0"))
	int32 Frames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Definition")
	TArray<FCsInputPhrase> Phrases;

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Input|Definition")
	TArray<FCsInputCompletedValue> CompletedValues;

	FCsInputSentence() :
		bActive(true),
		bCompleted(false),
		CompletedTime(0.0f),
		Cooldown(0.0f),
		bInterval(false),
		Interval(0.0f),
		bFrames(false),
		Frames(0),
		Phrases(),
		CompletedValues()
	{
	}

	FORCEINLINE bool operator==(const FCsInputSentence& B) const
	{
		if (bActive != B.bActive) { return false; }
		if (bCompleted != B.bCompleted) { return false; }
		if (CompletedTime != B.CompletedTime) { return false; }
		if (Cooldown != B.Cooldown) { return false; }
		if (bInterval != B.bInterval) { return false; }
		if (Interval != B.Interval) { return false; }
		if (bFrames != B.bFrames) { return false; }
		if (Frames != B.Frames) { return false; }

		if (Phrases.Num() != B.Phrases.Num())
			return false;

		const int32 PhraseCount = Phrases.Num();

		for (int32 I = 0; I < PhraseCount; ++I)
		{
			if (Phrases[I] != B.Phrases[I])
				return false;
		}

		if (CompletedValues.Num() != B.CompletedValues.Num())
			return false;

		const int32 CompletedCount = CompletedValues.Num();

		for (int32 I = 0; I < CompletedCount; ++I)
		{
			if (CompletedValues[I] != B.CompletedValues[I])
				return false;
		}
		return true;
	}

	FORCEINLINE bool operator!=(const FCsInputSentence& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE bool IsCompleted() const { return bCompleted; }

	FORCEINLINE const TArray<FCsInputCompletedValue>& GetCompletedValues() const { return CompletedValues; }

	bool IsValid() const
	{
		if (Phrases.Num() == CS_EMPTY) { return false; }

		for (const FCsInputPhrase& Phrase : Phrases)
		{
			if (!Phrase.IsValid())
				return false;
		}
		return true;
	}

	void ProcessInput(FCsInputFrame* InputFrame);

	FORCEINLINE bool HasPassedWith(const ECsInputEvent& Event) const
	{
		if (!bCompleted)
			return false;

		for (const FCsInputPhrase& Phrase : Phrases)
		{
			if (Phrase.HasPassedWith(Event))
				return true;
		}
		return false;
	}

	FORCEINLINE void Reset()
	{
		bActive = true;
		bCompleted = false;

		for (FCsInputPhrase& Phrase : Phrases)
		{
			Phrase.Reset();
		}

		CompletedValues.Reset(CompletedValues.Max());
	}
};

#pragma endregion FCsInputSentence