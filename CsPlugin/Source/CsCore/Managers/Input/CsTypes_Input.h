// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"
#include "Types/Enum/CsEnumMap.h"
#include "Types/Enum/CsEnumMask_int32.h"
#include "Types/Enum/CsEnumStructMaskMap.h"
// Types
#include "InputCoreTypes.h"

#include "CsTypes_Input.generated.h"
#pragma once

// Input
#pragma region

	// InputDevice
#pragma region

UENUM(BlueprintType)
enum class ECsInputDevice : uint8
{
	MouseAndKeyboard	UMETA(DisplayName = "Mouse And Keyboard"),
	Gamepad				UMETA(DisplayName = "Gamepad"),
	MotionController	UMETA(DisplayName = "MotionController"),
	ECsInputDevice_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsInputDevice : public TCsEnumMap<ECsInputDevice>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInputDevice, ECsInputDevice)
};

namespace NCsInputDevice
{
	typedef ECsInputDevice Type;

	namespace Ref
	{
		extern CSCORE_API const Type MouseAndKeyboard;
		extern CSCORE_API const Type Gamepad;
		extern CSCORE_API const Type MotionController;
		extern CSCORE_API const Type ECsInputDevice_MAX;
	}
}

#define ECS_INPUT_DEVICE_MAX (uint8)ECsInputDevice::ECsInputDevice_MAX

#pragma endregion InputDevice

	// InputType
#pragma region

UENUM(BlueprintType)
enum class ECsInputType : uint8
{
	Action				UMETA(DisplayName = "Action"),
	Axis				UMETA(DisplayName = "Axis"),
	Trigger				UMETA(DisplayName = "Trigger"),
	Location			UMETA(DisplayName = "Location"),
	Rotation			UMETA(DisplayName = "Rotation"),
	ECsInputType_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsInputType : public TCsEnumMap<ECsInputType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInputType, ECsInputType)
};

namespace NCsInputType
{
	typedef ECsInputType Type;

	namespace Ref
	{
		extern CSCORE_API const Type Action;
		extern CSCORE_API const Type Axis;
		extern CSCORE_API const Type Trigger;
		extern CSCORE_API const Type Location;
		extern CSCORE_API const Type Rotation;
		extern CSCORE_API const Type ECsInputType_MAX;
	}
}

#pragma endregion InputType

	// InputEvent
#pragma region

UENUM(BlueprintType)
enum class ECsInputEvent: uint8
{
	FirstPressed		UMETA(DisplayName = "First Pressed"),
	Pressed				UMETA(DisplayName = "Pressed"),
	FirstReleased		UMETA(DisplayName = "First Released"),
	Released			UMETA(DisplayName = "Released"),
	FirstMoved			UMETA(DisplayName = "First Moved"),
	Moved				UMETA(DisplayName = "Moved"),
	FirstStationary		UMETA(DisplayName = "First Stationary"),
	Stationary			UMETA(DisplayName = "Stationary"),
	ECsInputEvent_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsInputEvent : public TCsEnumMap<ECsInputEvent>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInputEvent, ECsInputEvent)
};

namespace NCsInputEvent
{
	typedef ECsInputEvent Type;

	namespace Ref
	{
		extern CSCORE_API const Type FirstPressed;
		extern CSCORE_API const Type Pressed;
		extern CSCORE_API const Type FirstReleased;
		extern CSCORE_API const Type Released;
		extern CSCORE_API const Type FirstMoved;
		extern CSCORE_API const Type Moved;
		extern CSCORE_API const Type FirstStationary;
		extern CSCORE_API const Type Stationary;
		extern CSCORE_API const Type ECsInputEvent_MAX;
	}
}

#pragma endregion InputEvent

	// InputValue
#pragma region

UENUM(BlueprintType)
enum class ECsInputValue : uint8
{
	Void				UMETA(DisplayName = "Void"),
	Float				UMETA(DisplayName = "Float"),
	Vector				UMETA(DisplayName = "Vector"),
	Rotator				UMETA(DisplayName = "Rotator"),
	ECsInputValue_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsInputValue : public TCsEnumMap<ECsInputValue>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInputValue, ECsInputValue)
};

namespace NCsInputValue
{
	typedef ECsInputValue Type;

	namespace Ref
	{
		extern CSCORE_API const Type Void;
		extern CSCORE_API const Type Float;
		extern CSCORE_API const Type Vector;
		extern CSCORE_API const Type Rotator;
		extern CSCORE_API const Type ECsInputValue_MAX;
	}
}

#pragma endregion InputValue

	// InputActionMap
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsInputActionMap : public FECsEnumMask_int32
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_MASK_INT32_BODY(FECsInputActionMap)
};

FORCEINLINE uint32 GetTypeHash(const FECsInputActionMap& b)
{
	return GetTypeHash(b.Name_Internal) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsInputActionMap : public TCsEnumStructMaskMap<FECsInputActionMap, int32>
{
	CS_ENUM_STRUCT_MASK_MAP_BODY(EMCsInputActionMap, FECsInputActionMap, int32)
};

namespace NCsInputActionMap
{
	typedef FECsInputActionMap Type;

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion InputActionMap

	// FCsInputActionMapRule
#pragma region

struct CSCORE_API FCsInputActionMapRule
{
	int32 Clear;
	int32 Set;

	FCsInputActionMapRule()
	{
		Clear = 0;
		Set = 0;
	}

	FCsInputActionMapRule(const int32& InClear, const int32& InSet)
	{
		Clear = InClear;
		Set = InSet;
	}

	FCsInputActionMapRule(const FECsInputActionMap& InClear, const FECsInputActionMap& InSet)
	{
		Clear = (int32)InClear;
		Set = (int32)InSet;
	}
	~FCsInputActionMapRule(){}
};

#pragma endregion FCsInputActionMapRule

	// InputAction
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsInputAction : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsInputAction)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsInputAction)

struct CSCORE_API EMCsInputAction : public TCsEnumStructMap<FECsInputAction, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsInputAction, FECsInputAction, uint8)
};

namespace NCsInputAction
{
	typedef FECsInputAction Type;

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion InputAction

	// FCsInputActionSet
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputActionSet
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TSet<FECsInputAction> Actions;

	FCsInputActionSet() :
		Actions()
	{

	}
};

#pragma endregion FCsInputActionSet

#define CS_INVALID_INPUT_POOL_INDEX 65535

	// FCsInputInfo
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputInfo
{
	GENERATED_USTRUCT_BODY()

private:

	bool bEvaluated;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FKey Key;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	int32 KeyIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	ECsInputType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	ECsInputValue ValueType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	ECsInputEvent Event;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	ECsInputEvent Last_Event;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FRotator Rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float Duration;

	FCsInputInfo() :
		bEvaluated(false),
		Key(EKeys::AnyKey),
		KeyIndex(INDEX_NONE),
		Type(ECsInputType::ECsInputType_MAX),
		ValueType(ECsInputValue::ECsInputValue_MAX),
		Event(ECsInputEvent::ECsInputEvent_MAX),
		Last_Event(ECsInputEvent::ECsInputEvent_MAX),
		Value(0.0f),
		Location(0.0f),
		Rotation(0.0f),
		Duration(0.0f)
	{
	}

	~FCsInputInfo(){}

	FORCEINLINE FCsInputInfo& operator=(const FCsInputInfo& B)
	{
		Key = B.Key;
		KeyIndex = B.KeyIndex;
		Type = B.Type;
		ValueType = B.ValueType;
		Event = B.Event;
		Last_Event = B.Last_Event;
		Value = B.Value;
		Location = B.Location;
		Rotation = B.Rotation;
		Duration = B.Duration;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsInputInfo& B) const
	{
		return Key == B.Key && KeyIndex == B.KeyIndex &&
			   Type == B.Type && ValueType == B.ValueType && 
			   Event == B.Event && Last_Event == B.Last_Event &&
			   Value == B.Value && Location == B.Location && Rotation == B.Rotation &&
			   Duration == B.Duration;
	}

	FORCEINLINE bool operator!=(const FCsInputInfo& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const ECsInputEvent& inEvent, const float& inValue)
	{
		Event = inEvent;
		Value = inValue;
	}

	FORCEINLINE void Set(const ECsInputEvent& inEvent, const FVector& inLocation)
	{
		Event = inEvent;
		Location = inLocation;
	}

	FORCEINLINE void Set(const ECsInputEvent& inEvent, const FRotator& inRotation)
	{
		Event = inEvent;
		Rotation = inRotation;
	}

	FORCEINLINE bool IsEvaluated()
	{
		return bEvaluated;
	}

	FORCEINLINE void StartEvaluation()
	{
		bEvaluated = true;
	}

	FORCEINLINE void EndEvaluation()
	{
		bEvaluated = false;
	}

	FORCEINLINE bool HasEventChanged()
	{
		return Event != Last_Event;
	}

	FORCEINLINE void FlushEvent()
	{
		Last_Event = Event;
	}
};

#pragma endregion FCsInputInfo

	// FRep_CsInput
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FRep_CsInput
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FECsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	ECsInputEvent Event;

	FORCEINLINE FRep_CsInput& operator=(const FRep_CsInput& B)
	{
		Action = B.Action;
		Event  = B.Event;
		return *this;
	}

	FORCEINLINE bool operator==(const FRep_CsInput& B) const
	{
		return Action == B.Action && Event == B.Event;
	}

	FORCEINLINE bool operator!=(const FRep_CsInput& B) const
	{
		return !(*this == B);
	}

	void Init(const FECsInputAction& inAction, const ECsInputEvent& inEvent)
	{
		Action = inAction;
		Event = inEvent;
	}

	void Reset()
	{
		Action = EMCsInputAction::Get().GetMAX();
		Event  = ECsInputEvent::ECsInputEvent_MAX;
	}
};

#pragma endregion FRep_CsInput

	// FCsInput
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsInput
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool bDeallocate;

	UPROPERTY(BlueprintReadOnly)
	bool bConsumed;

	UPROPERTY(BlueprintReadOnly)
	FECsInputAction Action;

	UPROPERTY(BlueprintReadOnly)
	ECsInputEvent Event;

	UPROPERTY(BlueprintReadOnly)
	float Value;
	
	UPROPERTY(BlueprintReadOnly)
	FVector Location;
	
	UPROPERTY(BlueprintReadOnly)
	FRotator Rotation;
	
	UPROPERTY(BlueprintReadOnly)
	float Duration;

	FCsInput() :
		bDeallocate(false),
		bConsumed(false),
		Action(),
		Event(ECsInputEvent::ECsInputEvent_MAX),
		Value(0.0f),
		Location(0.0f),
		Rotation(0.0f),
		Duration(0.0f)
	{
	}

	FORCEINLINE FCsInput& operator=(const FRep_CsInput& B)
	{
		Action = B.Action;
		Event  = B.Event;
		return *this;
	}


	FORCEINLINE bool operator==(const FCsInput& B) const
	{
		return Action == B.Action &&
				Event == B.Event &&
				Value == B.Value &&
				Location == B.Location &&
				Rotation == B.Rotation &&
				Duration == B.Duration;
	}

	FORCEINLINE bool operator!=(const FCsInput& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const FECsInputAction& inAction, const ECsInputEvent& inEvent, const float& inValue, const FVector& inLocation, const FRotator& inRotation)
	{
		Action		  = inAction;
		Event		  = inEvent;
		Value		  = inValue;
		Location	  = inLocation;
		Rotation	  = inRotation;
	}

	FORCEINLINE void Set(const FECsInputAction& inAction, const ECsInputEvent& inEvent, const FVector& inLocation)
	{
		Set(inAction, inEvent, 0.0f, inLocation, FRotator::ZeroRotator);
	}

	FORCEINLINE void Set(const FECsInputAction& inAction, const ECsInputEvent& inEvent, const FRotator& inRotation)
	{
		Set(inAction, inEvent, 0.0f, FVector::ZeroVector, inRotation);
	}

	FORCEINLINE void Set(const FECsInputAction& inAction, const ECsInputEvent& inEvent, const float& inValue)
	{
		Set(inAction, inEvent, inValue, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	FORCEINLINE void Set(const FECsInputAction& inAction, const ECsInputEvent& inEvent)
	{
		Set(inAction, inEvent, 0.0f, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	FORCEINLINE void QueueDeallocate()
	{
		bDeallocate = true;
	}

	FORCEINLINE bool ShouldDeallocate() const
	{
		return bDeallocate;
	}

	FORCEINLINE void Reset()
	{
		bDeallocate = false;
		bConsumed = false;
		Action	  = EMCsInputAction::Get().GetMAX();
		Event	  = ECsInputEvent::ECsInputEvent_MAX;
		Value	  = INFINITY;
		Location  = FVector::ZeroVector;
		Rotation  = FRotator::ZeroRotator;
		Duration  = 0.0f;
	}

	bool IsValid() const
	{
		return Action != EMCsInputAction::Get().GetMAX() && Event != ECsInputEvent::ECsInputEvent_MAX;
	}
};

#pragma endregion FCsInput

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

	UPROPERTY(BlueprintReadOnly)
	bool bCompleted;

	UPROPERTY(BlueprintReadOnly)
	float CompletedTime;

	UPROPERTY(BlueprintReadOnly)
	bool bConsume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCsInput> AndInputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCsInput> OrInputs;

	FCsInputWord() :
		bCompleted(false),
		CompletedTime(0.0f),
		bConsume(false),
		AndInputs(),
		OrInputs()
	{
	}

	FORCEINLINE FCsInputWord& operator=(const FCsInputWord& B)
	{
		bCompleted	  = B.bCompleted;
		CompletedTime = B.CompletedTime;
		bConsume	  = B.bConsume;

		AndInputs.Reset();

		for (const FCsInput& Input : B.AndInputs)
		{
			AndInputs.Add(Input);
		}

		OrInputs.Reset();

		for (const FCsInput& Input : B.OrInputs)
		{
			OrInputs.Add(Input);
		}
		return *this;
	}

	FORCEINLINE bool operator!=(const FCsInputWord& B) const
	{
		return !(*this == B);
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
		return true;
	}

	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector& Location, const FRotator& Rotation)
	{
		AndInputs.AddDefaulted();
		const int32 Index = AndInputs.Num() - 1;
		AndInputs[Index].Action = Action;
		AndInputs[Index].Event = Event;
		AndInputs[Index].Value = Value;
		AndInputs[Index].Location = Location;
		AndInputs[Index].Rotation = Rotation;
	}

	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event)
	{
		AddAndInput(Action, Event, 0.0f, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value)
	{
		AddAndInput(Action, Event, Value, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FVector& Location)
	{
		AddAndInput(Action, Event, 0.0f, Location, FRotator::ZeroRotator);
	}

	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FRotator& Rotation)
	{
		AddAndInput(Action, Event, 0.0f, FVector::ZeroVector, Rotation);
	}

	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector& Location, const FRotator& Rotation)
	{
		OrInputs.AddDefaulted();
		const int32 Index = OrInputs.Num() - 1;
		OrInputs[Index].Action = Action;
		OrInputs[Index].Event = Event;
		OrInputs[Index].Value = Value;
		OrInputs[Index].Location = Location;
		OrInputs[Index].Rotation = Rotation;
	}

	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event)
	{
		AddOrInput(Action, Event, 0.0f, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value)
	{
		AddOrInput(Action, Event, Value, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FVector& Location)
	{
		AddOrInput(Action, Event, 0.0f, Location, FRotator::ZeroRotator);
	}

	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FRotator& Rotation)
	{
		AddOrInput(Action, Event, 0.0f, FVector::ZeroVector, Rotation);
	}

	FORCEINLINE void Reset()
	{
		bCompleted = false;
	}

	void ProcessInput(FCsInputFrame* InputFrame);

	bool IsValid() const
	{
		if (AndInputs.Num() == CS_EMPTY &&
			OrInputs.Num() == CS_EMPTY) 
		{ 
			return false; 
		}

		for (const FCsInput& Input : AndInputs)
		{
			if (!Input.IsValid())
				return false;
		}

		for (const FCsInput& Input : OrInputs)
		{
			if (!Input.IsValid())
				return false;
		}
		return true;
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

	UPROPERTY(BlueprintReadOnly)
	bool bCompleted;

	UPROPERTY(BlueprintReadOnly)
	float CompletedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0"))
	int32 Frames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCsInputWord> Words;

	FCsInputPhrase() :
		bCompleted(false),
		CompletedTime(0.0f),
		bUseInterval(false),
		Interval(0.0f),
		bUseFrames(false),
		Frames(0),
		Words()
	{
	}

	FORCEINLINE FCsInputPhrase& operator=(const FCsInputPhrase& B)
	{
		bCompleted = B.bCompleted;
		CompletedTime = B.CompletedTime;
		bUseInterval = B.bUseInterval;
		Interval = B.Interval;
		bUseFrames = B.bUseFrames;
		Frames = B.Frames;

		Words.Reset();

		for (const FCsInputWord& Word : B.Words)
		{
			Words.Add(Word);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const FCsInputPhrase& B) const
	{
		if (bCompleted != B.bCompleted) { return false; }
		if (CompletedTime != B.CompletedTime) { return false; }
		if (bUseInterval != B.bUseInterval) { return false; }
		if (Interval != B.Interval) { return false; }
		if (bUseFrames != B.bUseFrames) { return false; }
		if (Frames != B.Frames) { return false; }

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

	FORCEINLINE bool operator!=(const FCsInputPhrase& B) const
	{
		return !(*this == B);
	}

	void AddAndInputToWord(const int32& Index, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value = 0.0f, const FVector& Location = FVector::ZeroVector, const FRotator& Rotation = FRotator::ZeroRotator)
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

	void AddOrInputToWord(const int32& Index, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value = 0.0f, const FVector& Location = FVector::ZeroVector, const FRotator& Rotation = FRotator::ZeroRotator)
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

	FORCEINLINE void Reset()
	{
		for (FCsInputWord& Word : Words)
		{
			Word.Reset();
		}
		bCompleted = false;
		CompletedTime = 0.0f;
	}

	void ProcessInput(FCsInputFrame* InputFrame);

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

	UPROPERTY(BlueprintReadOnly)
	bool bActive;

	UPROPERTY(BlueprintReadOnly)
	bool bCompleted;

	UPROPERTY(BlueprintReadOnly)
	float CompletedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0"))
	int32 Frames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCsInputPhrase> Phrases;

	FCsInputSentence() :
		bActive(true),
		bCompleted(false),
		CompletedTime(0.0f),
		Cooldown(0.0f),
		bUseInterval(false),
		Interval(0.0f),
		bUseFrames(false),
		Frames(0),
		Phrases()
	{
	}

	FORCEINLINE FCsInputSentence& operator=(const FCsInputSentence& B)
	{
		bActive = B.bActive;
		bCompleted = B.bCompleted;
		CompletedTime = B.CompletedTime;
		Cooldown = B.Cooldown;
		bUseInterval = B.bUseInterval;
		Interval = B.Interval;
		bUseFrames = B.bUseFrames;
		Frames = B.Frames;

		Phrases.Reset();

		for (const FCsInputPhrase& Phrase : B.Phrases)
		{
			Phrases.Add(Phrase);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const FCsInputSentence& B) const
	{
		if (bActive != B.bActive) { return false; }
		if (bCompleted != B.bActive) { return false; }
		if (CompletedTime != B.CompletedTime) { return false; }
		if (Cooldown != B.Cooldown) { return false; }
		if (bUseInterval != B.bUseInterval) { return false; }
		if (Interval != B.Interval) { return false; }
		if (bUseFrames != B.bUseFrames) { return false; }
		if (Frames != B.Frames) { return false; }

		if (Phrases.Num() != B.Phrases.Num())
			return false;

		const int32 Count = Phrases.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Phrases[I] != B.Phrases[I])
				return false;
		}
		return true;
	}

	FORCEINLINE bool operator!=(const FCsInputSentence& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		bActive = true;

		for (FCsInputPhrase& Phrase : Phrases)
		{
			Phrase.Reset();
		}
		bCompleted = false;
	}

	void ProcessInput(FCsInputFrame* InputFrame);

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
};

#pragma endregion FCsInputSentence

	// FCsInputActionMapping
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputActionMapping
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FECsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FString KeyName;

	FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float Scale;

	FCsInputActionMapping()
	{
		KeyName = NCsCached::Str::Empty;
		Scale = 1.0f;
	}

	FORCEINLINE FCsInputActionMapping& operator=(const FCsInputActionMapping& B)
	{
		Action = B.Action;
		KeyName = B.KeyName;
		Key = B.Key;
		Scale = B.Scale;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsInputActionMapping& B) const
	{
		return Action == B.Action &&
			   KeyName == B.KeyName &&
			   Key == B.Key &&
			   Scale == B.Scale;
	}

	FORCEINLINE bool operator!=(const FCsInputActionMapping& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion FCsInputActionMapping

	// FCsInputActionMappings
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputActionMappings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCsInputActionMapping> Mappings;

	FORCEINLINE FCsInputActionMappings& operator=(const FCsInputActionMappings& B)
	{
		Mappings.Reset();

		const int32 Count = B.Mappings.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			Mappings.AddDefaulted();
			Mappings[I] = B.Mappings[I];
		}
		return *this;
	}

	FORCEINLINE bool operator==(const FCsInputActionMappings& B) const
	{
		if (Mappings.Num() != B.Mappings.Num())
			return false;

		const int32 Count = Mappings.Num();

		for (int32 I = 0; I < Count; ++I)
		{

		}
		return true;
	}

	FORCEINLINE bool operator!=(const FCsInputActionMappings& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion FCsInputActionMappings

	// FCsInputProfile
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputProfile
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	uint8 Player;

	UPROPERTY(VisibleDefaultsOnly, Category = "Input")
	FCsInputActionMappings DeviceMappings[ECsInputDevice::ECsInputDevice_MAX];

	FCsInputProfile()
	{
		Player = 0;
	}

	FORCEINLINE FCsInputActionMapping& GetMapping(const ECsInputDevice& Device, const FECsInputAction& Action)
	{
		FCsInputActionMappings& DeviceMapping   = DeviceMappings[(uint8)Device];
		TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

		for (FCsInputActionMapping& Mapping : Mappings)
		{
			if (Action == Mapping.Action)
				return Mapping;
		}
		return Mappings[CS_FIRST];
	}

	FORCEINLINE FKey GetKey(const ECsInputDevice& Device, const FECsInputAction& Action)
	{
		FCsInputActionMappings& DeviceMapping   = DeviceMappings[(uint8)Device];
		TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

		for (FCsInputActionMapping& Mapping : Mappings)
		{
			if (Action == Mapping.Action)
				return Mapping.Key;
		}
		return EKeys::Invalid;
	}

	FORCEINLINE void SetKey(const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key)
	{
		FCsInputActionMappings& DeviceMapping   = DeviceMappings[(uint8)Device];
		TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

		for (FCsInputActionMapping& Mapping : Mappings)
		{
			if (Action == Mapping.Action)
			{
				Mapping.KeyName = Key == EKeys::Invalid ? NCsCached::Str::Empty : Key.GetDisplayName().ToString();;
				Mapping.Key		= Key;
				break;
			}
		}
	}

	FORCEINLINE void AddMapping(const ECsInputDevice& Device, const FECsInputAction& Action, const FString& KeyName, const FKey& Key)
	{
		FCsInputActionMappings& DeviceMapping   = DeviceMappings[(uint8)Device];
		TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

		const int32 Count = Mappings.Num();
		Mappings.AddDefaulted();
		FCsInputActionMapping& Mapping = Mappings[Count];
		Mapping.Action	   = Action;
		Mapping.KeyName	   = KeyName;
		Mapping.Key		   = Key;
	}

	FORCEINLINE void Reset()
	{
		for (int32 I = 0; I < ECS_INPUT_DEVICE_MAX; ++I)
		{
			DeviceMappings[I].Mappings.Reset();
		}
	}
};

#pragma endregion FCsInputProfile

#pragma endregion Input

// ControllerHand
#pragma region

UENUM(BlueprintType)
enum class ECsControllerHand : uint8
{
	Left					UMETA(DisplayName = "Left"),
	Right					UMETA(DisplayName = "Right"),
	ECsControllerHand_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsControllerHand : public TCsEnumMap<ECsControllerHand>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsControllerHand, ECsControllerHand)
};

namespace NCsControllerHand
{
	typedef ECsControllerHand Type;

	namespace Ref
	{
		extern CSCORE_API const Type Left;
		extern CSCORE_API const Type Right;
		extern CSCORE_API const Type ECsControllerHand_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion ControllerHand

// Game
#pragma region

	// GameEvent
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsGameEvent : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsGameEvent)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsGameEvent)

struct CSCORE_API EMCsGameEvent : public TCsEnumStructMap<FECsGameEvent, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsGameEvent, FECsGameEvent, uint8)
};

namespace NCsGameEvent
{
	typedef FECsGameEvent Type;

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion GameEvent

	// Rep_GameEvent
#pragma region

namespace ECsRep_GameEvent
{
	enum BitMask : int32;
}

#define CS_MAX_REP_GAME_EVENTS 32
typedef ECsRep_GameEvent::BitMask TCsRep_GameEvent;

#pragma endregion Rep_GameEvent

	// FCsGameEventInfo
#pragma region

/**
*
*/
USTRUCT(BlueprintType)
struct FCsGameEventInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsGameEvent Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	FCsGameEventInfo() :
		Event(),
		Value(0.0f),
		Location(0.0f)
	{
	}

	FORCEINLINE FCsGameEventInfo& operator=(const FCsGameEventInfo& B)
	{
		Event = B.Event;
		Value = B.Value;
		Location = B.Location;
		return *this;
	}

	FORCEINLINE void Reset()
	{
		Event = EMCsGameEvent::Get().GetMAX();
		Value = 0.0f;
		Location = FVector::ZeroVector;
	}

	FORCEINLINE bool IsValid() const
	{
		return Event.IsValid() && Event != EMCsGameEvent::Get().GetMAX();
	}
};

#pragma endregion FCsGameEventInfo

	// FCsGameEventDefinitionSimpleInfo
#pragma region

/**
*
*/
USTRUCT(BlueprintType)
struct FCsGameEventDefinitionSimpleInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsInputAction Action;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsInputEvent Event;

	FCsGameEventDefinitionSimpleInfo() :
		Action(),
		Event(ECsInputEvent::ECsInputEvent_MAX)
	{
		Action = EMCsInputAction::Get().GetMAX();
	}

	bool IsValid() const
	{
		return Action.IsValid() && Action != EMCsInputAction::Get().GetMAX() && Event != ECsInputEvent::ECsInputEvent_MAX;
	}
};

#pragma endregion FCsGameEventDefinitionSimpleInfo

	// FCsGameEventDefinitionSimple
#pragma region

USTRUCT(BlueprintType)
struct FCsGameEventDefinitionSimple
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsGameEvent GameEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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
		return GameEvent != EMCsGameEvent::Get().GetMAX() && Action != EMCsInputAction::Get().GetMAX() && Event != ECsInputEvent::ECsInputEvent_MAX;
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
struct FCsGameEventDefinition
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsGameEvent Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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
		return Event != EMCsGameEvent::Get().GetMAX() && Sentence.IsValid();
	}
};

FORCEINLINE uint32 GetTypeHash(const FCsGameEventDefinition& b)
{
	return GetTypeHash(b.Event);
}

#pragma endregion FCsGameEventDefinition

#define CS_GAME_EVENT_DEFINITION_START(Definitions, EVENT)	{ \
																Definitions.AddDefaulted(); \
																FCsGameEventDefinition& Def = Definitions[Definitions.Num() - 1]; \
																Def.Event = EVENT; \
																FCsInputSentence& Sentence = Def.Sentence;

#define CS_INPUT_PHRASE_ADD()	Sentence.Phrases.AddDefaulted(); \
								FCsInputPhrase& Phrase = Sentence.Phrases[Sentence.Phrases.Num() - 1];

#define CS_INPUT_WORD_START()	{ \
									Phrase.Words.AddDefaulted(); \
									FCsInputWord& Word = Phrase.Words[Phrase.Words.Num() - 1]; \

#define CS_INPUT_WORD_ADD_OR_INPUT(ACTION, EVENT)	Word.AddOrInput(ECsInputAction::ACTION, ECsInputEvent::EVENT);
#define CS_INPUT_WORD_ADD_OR_INPUT_VALUE(ACTION, EVENT, VALUE)	Word.AddOrInput(ECsInputAction::ACTION, ECsInputEvent::EVENT, VALUE);
#define CS_INPUT_WORD_ADD_OR_INPUT_LOCATION(ACTION, EVENT, LOCATION)	Word.AddOrInput(ECsInputAction::ACTION, ECsInputEvent::EVENT, LOCATION);
#define CS_INPUT_WORD_ADD_OR_INPUT_ROTATION(ACTION, EVENT, ROTATION)	Word.AddOrInput(ECsInputAction::ACTION, ECsInputEvent::EVENT, ROTATION);

#define CS_INPUT_WORD_ADD_AND_INPUT(ACTION, EVENT)	Word.AddAndInput(ECsInputAction::ACTION, ECsInputEvent::EVENT);
#define CS_INPUT_WORD_ADD_AND_INPUT_VALUE(ACTION, EVENT, VALUE)	Word.AddAndInput(ECsInputAction::ACTION, ECsInputEvent::EVENT, VALUE);
#define CS_INPUT_WORD_ADD_AND_INPUT_LOCATION(ACTION, EVENT, LOCATION)	Word.AddAndInput(ECsInputAction::ACTION, ECsInputEvent::EVENT, LOCATION);
#define CS_INPUT_WORD_ADD_AND_INPUT_ROTATION(ACTION, EVENT, ROTATION)	Word.AddAndInput(ECsInputAction::ACTION, ECsInputEvent::EVENT, ROTATION);

#define CS_INPUT_WORD_END()	}

#define CS_GAME_EVENT_DEFINITION_END() }

#define CS_GAME_EVENT_DEFINITION_SIMPLE(Definitions, GAMEEVENT, ACTION, EVENT)	CreateGameEventDefinitionSimple(Definitions, EMCsGameEvent::Get().GetEnum(FString(#GAMEEVENT)), EMCsInputAction::Get().GetEnum(FString(#ACTION)), ECsInputEvent::EVENT);

#pragma endregion