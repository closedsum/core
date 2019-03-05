// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"
#include "Runtime/InputCore/Classes/InputCoreTypes.h"

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
	CS_DECLARE_ENUM_MAP_BODY(EMCsInputDevice)
};

namespace NCsInputDevice
{
	namespace Ref
	{
		typedef ECsInputDevice Type;

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
	CS_DECLARE_ENUM_MAP_BODY(EMCsInputType)
};

namespace NCsInputType
{
	namespace Ref
	{
		typedef ECsInputType Type;

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
	CS_DECLARE_ENUM_MAP_BODY(EMCsInputEvent)
};

namespace NCsInputEvent
{
	namespace Ref
	{
		typedef ECsInputEvent Type;

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
	CS_DECLARE_ENUM_MAP_BODY(EMCsInputValue)
};

namespace NCsInputValue
{
	namespace Ref
	{
		typedef ECsInputValue Type;

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

	FORCEINLINE virtual FString ToString() const override { return FECsEnumMask_int32::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsInputActionMap& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsInputActionMap : public TCsEnumStructMaskMap<FECsInputActionMap, int32>
{
	CS_DECLARE_ENUM_STRUCT_MASK_MAP_BODY(EMCsInputActionMap)
};

#pragma endregion InputActionMap

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

	// InputAction
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsInputAction : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsInputAction)

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsInputAction& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsInputAction : public TCsEnumStructMap<FECsInputAction, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsInputAction)
};

#pragma endregion InputAction

#define CS_INVALID_INPUT_POOL_INDEX 65535

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputInfo
{
	GENERATED_USTRUCT_BODY()

private:

	bool bEvaluated;
	
public:

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
		return Type == B.Type && ValueType == B.ValueType && 
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

USTRUCT(BlueprintType)
struct CSCORE_API FCsInput
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Input")
	uint16 PoolIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool IsAllocated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool IsConsumed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Input")
	FECsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	ECsInputEvent Event;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FRotator Rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float Duration;

	FCsInput()
	{
		PoolIndex = CS_INVALID_INPUT_POOL_INDEX;
		Reset();
	}

	FORCEINLINE FCsInput& operator=(const FRep_CsInput& B)
	{
		Action = B.Action;
		Event  = B.Event;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsInput& B) const
	{
		if (IsAllocated != B.IsAllocated) { return false; }
		if (IsConsumed != B.IsConsumed) { return false; }
		if (Action != B.Action) { return false; }
		if (Event != B.Event) { return false; }
		if (Value != B.Value) { return false; }
		if (Location != B.Location) { return false; }
		if (Rotation != B.Rotation) { return false; }
		if (Duration != B.Duration) { return false; }
		return true;
	}

	FORCEINLINE bool operator!=(const FCsInput& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Init(const uint16& inPoolIndex)
	{
		PoolIndex = inPoolIndex;
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

	FORCEINLINE void Allocate(const FECsInputAction& inAction, const ECsInputEvent& inEvent, const float& inValue, const FVector& inLocation, const FRotator& inRotation)
	{
		IsAllocated = true;
		Set(inAction, inEvent, inValue, inLocation, inRotation);
	}

	FORCEINLINE void Allocate(const FECsInputAction& inAction, const ECsInputEvent& inEvent, const FVector& inLocation)
	{
		Allocate(inAction, inEvent, 0.0f, inLocation, FRotator::ZeroRotator);
	}

	FORCEINLINE void Allocate(const FECsInputAction& inAction, const ECsInputEvent& inEvent, const FRotator& inRotation)
	{
		Allocate(inAction, inEvent, 0.0f, FVector::ZeroVector, inRotation);
	}

	FORCEINLINE void Allocate(const FECsInputAction& inAction, const ECsInputEvent& inEvent, const float& inValue)
	{
		Allocate(inAction, inEvent, inValue, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	FORCEINLINE void Allocate(const FECsInputAction& inAction, const ECsInputEvent& inEvent)
	{
		Allocate(inAction, inEvent, 0.0f, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	FORCEINLINE void Reset()
	{
		IsAllocated   = false;
		IsConsumed	  = false;
		Action		  = EMCsInputAction::Get().GetMAX();
		Event		  = ECsInputEvent::ECsInputEvent_MAX;
		Value		  = INFINITY;
		Location	  = FVector::ZeroVector;
		Rotation	  = FRotator::ZeroRotator;
		Duration	  = 0.0f;
	}

	bool IsValid() const
	{
		return Action != EMCsInputAction::Get().GetMAX() && Event != ECsInputEvent::ECsInputEvent_MAX;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputFrame
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float RealTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float DeltaTime;

	UPROPERTY(EditAnywhere, Category = "Input")
	uint64 Frame;

	TArray<struct FCsInput*> Inputs;

	FORCEINLINE FCsInputFrame& operator=(const FCsInputFrame& B)
	{
		Time = B.Time;
		RealTime = B.RealTime;
		DeltaTime = B.DeltaTime;
		Frame = B.Frame;

		Inputs.Reset();

		for (FCsInput* Input : B.Inputs)
		{
			Inputs.Add(Input);
		}
		return *this;
	}

	FORCEINLINE void Init(const float& inTime, const float& inRealTime, const float& inDeltaTime, const uint64& inFrame)
	{
		Time	  = inTime;
		RealTime  = inRealTime;
		DeltaTime = inDeltaTime;
		Frame	  = inFrame;

		for (FCsInput* Input : Inputs)
		{
			Input->Reset();
		}
		Inputs.Reset();
	}

	FORCEINLINE FCsInput* GetInput(const FECsInputAction& Action)
	{
		for (FCsInput* Input : Inputs)
		{
			if (Input->Action == Action)
				return Input;
		}
		return nullptr;
	}

	FORCEINLINE FCsInput* GetInput(const FECsInputAction& Action, const ECsInputEvent& Event)
	{
		if (FCsInput* Input = GetInput(Action))
			return Input->Event == Event ? Input : nullptr;
		return nullptr;
	}

	FORCEINLINE FCsInput* GetInput(const FECsInputAction& Action, const TArray<ECsInputEvent>& Events)
	{
		if (FCsInput* Input = GetInput(Action))
			return Events.Find(Input->Event) != INDEX_NONE ? Input : nullptr;
		return nullptr;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputWord
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool bCompleted;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	float CompletedTime;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool bConsume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCsInput> AndInputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCsInput> OrInputs;

	FCsInputWord()
	{
		bCompleted = false;
		CompletedTime = 0.0f;
		bConsume = false;
	}

	FORCEINLINE FCsInputWord& operator=(const FCsInputWord& B)
	{
		bCompleted = B.bCompleted;
		CompletedTime = B.CompletedTime;
		bConsume = B.bConsume;

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

	FORCEINLINE void ProcessInput(FCsInputFrame& InputFrame)
	{
		int32 And = 0;
		bool Or   = false;

		const int32 Count = InputFrame.Inputs.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			FCsInput* Input = InputFrame.Inputs[I];

			// Check And
			const int32 AndCount = AndInputs.Num();

			for (int32 J = And; J < AndCount; ++J)
			{
				if (Input->Action == AndInputs[J].Action &&
					Input->Event == AndInputs[J].Event)
				{
					++And;
				}
			}
			// Check Or
			const int32 OrCount = OrInputs.Num();

			for (const FCsInput& OrInput : OrInputs)
			{
				Or |= Input->Action == OrInput.Action && Input->Event == OrInput.Event;

				if (Or)
					break;
			}
			
			bCompleted = (And > 0 && And == AndCount) || Or;

			if (bCompleted)
			{
				if (bConsume)
					InputFrame.Inputs.RemoveAt(I);
				CompletedTime = InputFrame.Time;
				break;
			}
		}
	}

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

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputPhrase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool bCompleted;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	float CompletedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bUseInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bUseFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0", UIMin = "0"))
	int32 Frames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCsInputWord> Words;

	FCsInputPhrase()
	{
		bCompleted = false;
		CompletedTime = 0.0f;
		bUseInterval = false;
		Interval = 0.0f;
		bUseFrames = false;
		Frames = 0;
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

	FORCEINLINE void ProcessInput(FCsInputFrame& InputFrame)
	{
		const float& CurrentTime = InputFrame.Time;

		// Check if ALL Words are Completed
		const int32 Count = Words.Num();
		int32 Index		  = 0;

		if (bUseInterval)
		{
			float ElapsedTime			= 0.0f;
			float EarliestCompletedTime = CurrentTime;

			for (Index = 0; Index < Count; ++Index)
			{
				if (Words[Index].bCompleted)
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

				if (Index < Count - 1 || !Words[Index].bCompleted)
					break;
			}
		}
		else
		{
			for (Index = 0; Index < Count; ++Index)
			{
				if (Words[Index].bCompleted)
					continue;

				Words[Index].ProcessInput(InputFrame);

				if (Index < Count - 1 || !Words[Index].bCompleted)
					break;
			}

			if (Index != Count)
				Reset();
		}
		// Check if Completed
		if (Index > 0 && Index == Count)
		{
			bCompleted = true;
			CompletedTime = CurrentTime;
		}
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

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputSentence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool bActive;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool bCompleted;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	float CompletedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bUseInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bUseFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0", UIMin = "0"))
	int32 Frames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCsInputPhrase> Phrases;

	FCsInputSentence()
	{
		bActive = true;
		bCompleted = false;
		CompletedTime = 0.0f;
		Cooldown = 0.0f;
		bUseInterval = false;
		Interval = 0.0f;
		bUseFrames = false;
		Frames = 0;
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

	FORCEINLINE void ProcessInput(FCsInputFrame& InputFrame)
	{
		const float& CurrentTime = InputFrame.Time;

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

		if (bUseInterval)
		{
			float ElapsedTime			= 0.0f;
			float EarliestCompletedTime = CurrentTime;

			for (Index = 0; Index < Count; ++Index)
			{
				if (Phrases[Index].bCompleted)
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

				if (Index < Count - 1 || !Phrases[Index].bCompleted)
					break;
			}
		}
		else
		{
			for (Index = 0; Index < Count; ++Index)
			{
				if (Phrases[Index].bCompleted)
					continue;

				Phrases[Index].ProcessInput(InputFrame);

				if (Index < Count - 1 || !Phrases[Index].bCompleted)
					break;
			}

			if (Index != Count)
				Reset();
		}
		// Check if Completed
		if (Count > 0 && Index == Count)
		{
			bCompleted = true;
			CompletedTime = CurrentTime;
			bActive = false;
		}
	}

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
		KeyName = ECsCached::Str::Empty;
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
				Mapping.KeyName = Key == EKeys::Invalid ? ECsCached::Str::Empty : Key.GetDisplayName().ToString();;
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

#pragma endregion Input

// Game
#pragma region

	// GameEvent
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsGameEvent : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsGameEvent)

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsGameEvent& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsGameEvent : public TCsEnumStructMap<FECsGameEvent, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsGameEvent)
};

#pragma endregion GameEvent

namespace ECsRep_GameEvent
{
	enum BitMask : int32;
}

#define CS_MAX_REP_GAME_EVENTS 32
typedef ECsRep_GameEvent::BitMask TCsRep_GameEvent;

USTRUCT(BlueprintType)
struct FCsGameEventInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FECsGameEvent Event;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FVector Location;

	FCsGameEventInfo()
	{
		Reset();
	}
	~FCsGameEventInfo(){}

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
		return Event != EMCsGameEvent::Get().GetMAX();
	}
};

USTRUCT(BlueprintType)
struct FCsGameEventDefinitionSimpleInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FECsInputAction Action;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	ECsInputEvent Event;

	FCsGameEventDefinitionSimpleInfo() :
		Event(ECsInputEvent::ECsInputEvent_MAX)
	{
		Action = EMCsInputAction::Get().GetMAX();
	}

	bool IsValid() const
	{
		return Action != EMCsInputAction::Get().GetMAX() && Event != ECsInputEvent::ECsInputEvent_MAX;
	}
};

USTRUCT(BlueprintType)
struct FCsGameEventDefinitionSimple
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FECsGameEvent GameEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FECsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
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

USTRUCT(BlueprintType)
struct FCsGameEventDefinition
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FECsGameEvent Event;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FCsInputSentence Sentence;

	FCsGameEventDefinition() :
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