// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"
#include "Runtime/InputCore/Classes/InputCoreTypes.h"

#include "CsTypes_Input.generated.h"
#pragma once

// Input
#pragma region

UENUM(BlueprintType)
namespace ECsInputDevice
{
	enum Type
	{
		MouseAndKeyboard	UMETA(DisplayName = "Mouse And Keyboard"),
		Gamepad				UMETA(DisplayName = "Gamepad"),
		MotionController	UMETA(DisplayName = "MotionController"),
		ECsInputDevice_MAX	UMETA(Hidden),
	};
}

struct CSCORE_API EMCsInputDevice : public TCsEnumMap<ECsInputDevice::Type>
{
protected:
	EMCsInputDevice() {}
	EMCsInputDevice(const EMCsInputDevice &) = delete;
	EMCsInputDevice(EMCsInputDevice &&) = delete;
public:
	~EMCsInputDevice() {}
private:
	static EMCsInputDevice* Instance;

public:
	static EMCsInputDevice& Get();
};

namespace ECsInputDevice
{
	namespace Ref
	{
		extern CSCORE_API const Type MouseAndKeyboard;
		extern CSCORE_API const Type Gamepad;
		extern CSCORE_API const Type MotionController;
		extern CSCORE_API const Type ECsInputDevice_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		return EMCsInputDevice::Get().ToString(EType);
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		return EMCsInputDevice::Get().ToType(String);
	}
}

#define ECS_INPUT_DEVICE_MAX (uint8)ECsInputDevice::ECsInputDevice_MAX
typedef ECsInputDevice::Type TCsInputDevice;

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
protected:
	EMCsInputType() {}
	EMCsInputType(const EMCsInputType &) = delete;
	EMCsInputType(EMCsInputType &&) = delete;
public:
	~EMCsInputType() {}
private:
	static EMCsInputType* Instance;

public:
	static EMCsInputType& Get();
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
protected:
	EMCsInputEvent() {}
	EMCsInputEvent(const EMCsInputEvent &) = delete;
	EMCsInputEvent(EMCsInputEvent &&) = delete;
public:
	~EMCsInputEvent() {}
private:
	static EMCsInputEvent* Instance;

public:
	static EMCsInputEvent& Get();
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
protected:
	EMCsInputValue() {}
	EMCsInputValue(const EMCsInputValue &) = delete;
	EMCsInputValue(EMCsInputValue &&) = delete;
public:
	~EMCsInputValue() {}
private:
	static EMCsInputValue* Instance;

public:
	static EMCsInputValue& Get();
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

namespace ECsInputActionMap
{
	enum BitMask : int32;
}

typedef ECsInputActionMap::BitMask TCsInputActionMap;

// InputActionMapMasktoString
typedef FString(*TCsInputActionMapMaskToString)(const int32&);
// StringToInputActionMap
typedef TCsInputActionMap(*TCsStringToInputActionMap)(const FString&);

#define CS_DECLARE_INPUT_ACTION_MAP	TCsInputActionMapMaskToString InputActionMapMaskToString; \
									TCsStringToInputActionMap StringToInputActionMap;

#define CS_DEFINE_INPUT_ACTION_MAP	InputActionMapMaskToString = &ECsInputActionMap::MaskToString; \
									StringToInputActionMap = &ECsInputActionMap::ToBitMask;

USTRUCT(BlueprintType)
struct CSCORE_API FECsInputActionMap : public FECsEnumMask_int32
{
	GENERATED_USTRUCT_BODY()

public:

	FECsInputActionMap() {}
	FECsInputActionMap(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnumMask_int32(InValue, InName, InDisplayName) {}
	FECsInputActionMap(const uint8 &InValue, const FString &InName) : FECsEnumMask_int32(InValue, InName) {}
	~FECsInputActionMap() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnumMask_int32::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsInputActionMap& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsInputActionMap : public TCsEnumStructMaskMap<FECsInputActionMap, int32>
{
protected:
	EMCsInputActionMap() {}
	EMCsInputActionMap(const EMCsInputActionMap &) = delete;
	EMCsInputActionMap(EMCsInputActionMap &&) = delete;
public:
	~EMCsInputActionMap() {}
private:
	static EMCsInputActionMap* Instance;

public:
	static EMCsInputActionMap& Get();
};

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

	FCsInputActionMapRule(const TCsInputActionMap& InClear, const TCsInputActionMap& InSet)
	{
		Clear = (int32)InClear;
		Set = (int32)InSet;
	}
	~FCsInputActionMapRule(){}
};

USTRUCT(BlueprintType)
struct CSCORE_API FECsInputAction : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsInputAction() {}
	FECsInputAction(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsInputAction(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsInputAction() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsInputAction& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsInputAction : public TCsEnumStructMap<FECsInputAction, uint8>
{
protected:
	EMCsInputAction() {}
	EMCsInputAction(const EMCsInputAction &) = delete;
	EMCsInputAction(EMCsInputAction &&) = delete;
public:
	~EMCsInputAction() {}
private:
	static EMCsInputAction* Instance;

public:
	static EMCsInputAction& Get();
};

#define CS_INVALID_INPUT_POOL_INDEX 65535

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputInfo
{
	GENERATED_USTRUCT_BODY()

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

	FCsInputInfo() {}
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

	FORCEINLINE void Set(const ECsInputEvent &inEvent, const float &inValue)
	{
		Event = inEvent;
		Value = inValue;
	}

	FORCEINLINE void Set(const ECsInputEvent &inEvent, const FVector &inLocation)
	{
		Event = inEvent;
		Location = inLocation;
	}

	FORCEINLINE void Set(const ECsInputEvent &inEvent, const FRotator &inRotation)
	{
		Event = inEvent;
		Rotation = inRotation;
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

	void Init(const FECsInputAction &inAction, const ECsInputEvent &inEvent)
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
		Action	  = EMCsInputAction::Get().GetMAX();
		Event	  = ECsInputEvent::ECsInputEvent_MAX;
		Value	  = INFINITY;
		Location  = FVector::ZeroVector;
		Rotation  = FRotator::ZeroRotator;
	}

	FORCEINLINE FCsInput& operator=(const FRep_CsInput& B)
	{
		Action = B.Action;
		Event  = B.Event;
		return *this;
	}

	FORCEINLINE void Init(const uint16 &inPoolIndex)
	{
		PoolIndex = inPoolIndex;
	}

	FORCEINLINE void Set(const FECsInputAction &inAction, const ECsInputEvent &inEvent, const float &inValue, const FVector &inLocation, const FRotator &inRotation)
	{
		Action		  = inAction;
		Event		  = inEvent;
		Value		  = inValue;
		Location	  = inLocation;
		Rotation	  = inRotation;
	}

	FORCEINLINE void Set(const FECsInputAction &inAction, const ECsInputEvent &inEvent, const FVector &inLocation)
	{
		Set(inAction, inEvent, 0.0f, inLocation, FRotator::ZeroRotator);
	}

	FORCEINLINE void Set(const FECsInputAction &inAction, const ECsInputEvent &inEvent, const FRotator &inRotation)
	{
		Set(inAction, inEvent, 0.0f, FVector::ZeroVector, inRotation);
	}

	FORCEINLINE void Set(const FECsInputAction &inAction, const ECsInputEvent &inEvent, const float &inValue)
	{
		Set(inAction, inEvent, inValue, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	FORCEINLINE void Set(const FECsInputAction &inAction, const ECsInputEvent &inEvent)
	{
		Set(inAction, inEvent, 0.0f, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	FORCEINLINE void Allocate(const FECsInputAction &inAction, const ECsInputEvent &inEvent, const float &inValue, const FVector &inLocation, const FRotator &inRotation)
	{
		IsAllocated = true;
		Set(inAction, inEvent, inValue, inLocation, inRotation);
	}

	FORCEINLINE void Allocate(const FECsInputAction &inAction, const ECsInputEvent &inEvent, const FVector &inLocation)
	{
		Allocate(inAction, inEvent, 0.0f, inLocation, FRotator::ZeroRotator);
	}

	FORCEINLINE void Allocate(const FECsInputAction &inAction, const ECsInputEvent &inEvent, const FRotator &inRotation)
	{
		Allocate(inAction, inEvent, 0.0f, FVector::ZeroVector, inRotation);
	}

	FORCEINLINE void Allocate(const FECsInputAction &inAction, const ECsInputEvent &inEvent, const float &inValue)
	{
		Allocate(inAction, inEvent, inValue, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	FORCEINLINE void Allocate(const FECsInputAction &inAction, const ECsInputEvent &inEvent)
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

	FORCEINLINE void Init(const float &inTime, const float &inRealTime, const float &inDeltaTime, const uint64 &inFrame)
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

	FORCEINLINE FCsInput* GetInput(const FECsInputAction &Action)
	{
		for (FCsInput* Input : Inputs)
		{
			if (Input->Action == Action)
				return Input;
		}
		return nullptr;
	}

	FORCEINLINE FCsInput* GetInput(const FECsInputAction &Action, const ECsInputEvent &Event)
	{
		if (FCsInput* Input = GetInput(Action))
			return Input->Event == Event ? Input : nullptr;
		return nullptr;
	}

	FORCEINLINE FCsInput* GetInput(const FECsInputAction &Action, const TArray<ECsInputEvent> &Events)
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
	bool Completed;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	float CompletedTime;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool Consume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCsInput> AndInputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCsInput> OrInputs;

	FCsInputWord()
	{
		Completed = false;
		CompletedTime = 0.0f;
		Consume = false;
	}

	void AddAndInput(const FECsInputAction &Action, const ECsInputEvent &Event, const float &Value, const FVector &Location, const FRotator &Rotation)
	{
		AndInputs.AddDefaulted();
		const int32 Index = AndInputs.Num() - 1;
		AndInputs[Index].Action = Action;
		AndInputs[Index].Event = Event;
		AndInputs[Index].Value = Value;
		AndInputs[Index].Location = Location;
		AndInputs[Index].Rotation = Rotation;
	}

	void AddAndInput(const FECsInputAction &Action, const ECsInputEvent &Event)
	{
		AddAndInput(Action, Event, 0.0f, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void AddAndInput(const FECsInputAction &Action, const ECsInputEvent &Event, const float &Value)
	{
		AddAndInput(Action, Event, Value, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void AddAndInput(const FECsInputAction &Action, const ECsInputEvent &Event, const FVector &Location)
	{
		AddAndInput(Action, Event, 0.0f, Location, FRotator::ZeroRotator);
	}

	void AddAndInput(const FECsInputAction &Action, const ECsInputEvent &Event, const FRotator &Rotation)
	{
		AddAndInput(Action, Event, 0.0f, FVector::ZeroVector, Rotation);
	}

	void AddOrInput(const FECsInputAction &Action, const ECsInputEvent &Event, const float &Value, const FVector &Location, const FRotator &Rotation)
	{
		OrInputs.AddDefaulted();
		const int32 Index = OrInputs.Num() - 1;
		OrInputs[Index].Action = Action;
		OrInputs[Index].Event = Event;
		OrInputs[Index].Value = Value;
		OrInputs[Index].Location = Location;
		OrInputs[Index].Rotation = Rotation;
	}

	void AddOrInput(const FECsInputAction &Action, const ECsInputEvent &Event)
	{
		AddOrInput(Action, Event, 0.0f, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void AddOrInput(const FECsInputAction &Action, const ECsInputEvent &Event, const float &Value)
	{
		AddOrInput(Action, Event, Value, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void AddOrInput(const FECsInputAction &Action, const ECsInputEvent &Event, const FVector &Location)
	{
		AddOrInput(Action, Event, 0.0f, Location, FRotator::ZeroRotator);
	}

	void AddOrInput(const FECsInputAction &Action, const ECsInputEvent &Event, const FRotator &Rotation)
	{
		AddOrInput(Action, Event, 0.0f, FVector::ZeroVector, Rotation);
	}

	FORCEINLINE void Reset()
	{
		Completed = false;
	}

	FORCEINLINE void ProcessInput(FCsInputFrame &InputFrame)
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
			
			Completed = (And > 0 && And == AndCount) || Or;

			if (Completed)
			{
				if (Consume)
					InputFrame.Inputs.RemoveAt(I);
				CompletedTime = InputFrame.Time;
				break;
			}
		}
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputPhrase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool Completed;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	float CompletedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool UseInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool UseFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0", UIMin = "0"))
	int32 Frames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCsInputWord> Words;

	FCsInputPhrase()
	{
		Completed = false;
		CompletedTime = 0.0f;
		UseInterval = false;
		Interval = 0.0f;
		UseFrames = false;
		Frames = 0;
	}

	void AddAndInputToWord(const int32 &Index, const FECsInputAction &Action, const ECsInputEvent &Event, const float &Value = 0.0f, const FVector &Location = FVector::ZeroVector, const FRotator &Rotation = FRotator::ZeroRotator)
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

	void AddOrInputToWord(const int32 &Index, const FECsInputAction &Action, const ECsInputEvent &Event, const float &Value = 0.0f, const FVector &Location = FVector::ZeroVector, const FRotator &Rotation = FRotator::ZeroRotator)
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
		Completed = false;
		CompletedTime = 0.0f;
	}

	FORCEINLINE void ProcessInput(FCsInputFrame &InputFrame)
	{
		const float& CurrentTime = InputFrame.Time;

		// Check if ALL Words are Completed
		const int32 Count = Words.Num();
		int32 Index		  = 0;

		if (UseInterval)
		{
			float ElapsedTime			= 0.0f;
			float EarliestCompletedTime = CurrentTime;

			for (Index = 0; Index < Count; ++Index)
			{
				if (Words[Index].Completed)
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

				if (Index < Count - 1 || !Words[Index].Completed)
					break;
			}
		}
		else
		{
			for (Index = 0; Index < Count; ++Index)
			{
				if (Words[Index].Completed)
					continue;

				Words[Index].ProcessInput(InputFrame);

				if (Index < Count - 1 || !Words[Index].Completed)
					break;
			}

			if (Index != Count)
				Reset();
		}
		// Check if Completed
		if (Index > 0 && Index == Count)
		{
			Completed = true;
			CompletedTime = CurrentTime;
		}
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputSentence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool Active;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool Completed;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	float CompletedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool UseInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool UseFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (ClampMin = "0", UIMin = "0"))
	int32 Frames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCsInputPhrase> Phrases;

	FCsInputSentence()
	{
		Active = true;
		Completed = false;
		CompletedTime = 0.0f;
		Cooldown = 0.0f;
		UseInterval = false;
		Interval = 0.0f;
		UseFrames = false;
		Frames = 0;
	}

	FORCEINLINE void Reset()
	{
		Active = true;

		for (FCsInputPhrase& Phrase : Phrases)
		{
			Phrase.Reset();
		}
		Completed = false;
	}

	FORCEINLINE void ProcessInput(FCsInputFrame &InputFrame)
	{
		const float& CurrentTime = InputFrame.Time;

		// Check if Cooldown has Expired
		if (!Active)
		{
			if (CurrentTime - CompletedTime >= Cooldown)
				Reset();
			else
				return;
		}
		// Check if ALL Phrases are Completed
		const int32 Count = Phrases.Num();
		int32 Index		  = 0;

		if (UseInterval)
		{
			float ElapsedTime			= 0.0f;
			float EarliestCompletedTime = CurrentTime;

			for (Index = 0; Index < Count; ++Index)
			{
				if (Phrases[Index].Completed)
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

				if (Index < Count - 1 || !Phrases[Index].Completed)
					break;
			}
		}
		else
		{
			for (Index = 0; Index < Count; ++Index)
			{
				if (Phrases[Index].Completed)
					continue;

				Phrases[Index].ProcessInput(InputFrame);

				if (Index < Count - 1 || !Phrases[Index].Completed)
					break;
			}

			if (Index != Count)
				Reset();
		}
		// Check if Completed
		if (Index == Count)
		{
			Completed = true;
			CompletedTime = CurrentTime;
			Active = false;
		}
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

	FORCEINLINE FCsInputActionMapping& GetMapping(const TCsInputDevice &Device, const FECsInputAction &Action)
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

	FORCEINLINE FKey GetKey(const TCsInputDevice &Device, const FECsInputAction &Action)
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

	FORCEINLINE void SetKey(const TCsInputDevice &Device, const FECsInputAction &Action, const FKey &Key)
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

	FORCEINLINE void AddMapping(const TCsInputDevice &Device, const FECsInputAction &Action, const FString &KeyName, const FKey &Key)
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

USTRUCT(BlueprintType)
struct CSCORE_API FECsGameEvent : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsGameEvent() {}
	FECsGameEvent(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsGameEvent(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsGameEvent() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsGameEvent& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsGameEvent : public TCsEnumStructMap<FECsGameEvent, uint8>
{
protected:
	EMCsGameEvent() {}
	EMCsGameEvent(const EMCsGameEvent &) = delete;
	EMCsGameEvent(EMCsGameEvent &&) = delete;
public:
	~EMCsGameEvent() {}
private:
	static EMCsGameEvent* Instance;

public:
	static EMCsGameEvent& Get();
};

namespace ECsRep_GameEvent
{
	enum BitMask : int32;
}

#define CS_MAX_REP_GAME_EVENTS 32
typedef ECsRep_GameEvent::BitMask TCsRep_GameEvent;

USTRUCT(BlueprintType)
struct FCsGameEventDefinition
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FCsInputSentence Sentence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FECsGameEvent Event;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	uint8 Event_Script;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FString EventAsString;
};

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