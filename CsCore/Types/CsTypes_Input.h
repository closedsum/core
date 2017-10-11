// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Input.generated.h"
#pragma once

// Input
#pragma region

UENUM()
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

namespace ECsInputDevice
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString MouseAndKeyboard = TCsString(TEXT("MouseAndKeyboard"), TEXT("mouseandkeyboard"));
		const TCsString Gamepad = TCsString(TEXT("Gamepad"), TEXT("gamepad"));
		const TCsString MotionController = TCsString(TEXT("MotionController"), TEXT("motioncontroller"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::MouseAndKeyboard) { return Str::MouseAndKeyboard.Value; }
		if (EType == Type::Gamepad) { return Str::Gamepad.Value; }
		if (EType == Type::MotionController) { return Str::MotionController.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::MouseAndKeyboard) { return Type::MouseAndKeyboard; }
		if (String == Str::Gamepad) { return Type::Gamepad; }
		if (String == Str::MotionController) { return Type::MotionController; }
		return Type::ECsInputDevice_MAX;
	}
}

#define ECS_INPUT_DEVICE_MAX (uint8)ECsInputDevice::ECsInputDevice_MAX
typedef ECsInputDevice::Type TCsInputDevice;

UENUM()
namespace ECsInputType
{
	enum Type
	{
		Action				UMETA(DisplayName = "Action"),
		Axis				UMETA(DisplayName = "Axis"),
		Trigger				UMETA(DisplayName = "Trigger"),
		Location			UMETA(DisplayName = "Location"),
		Rotation			UMETA(DisplayName = "Rotation"),
		ECsInputType_MAX	UMETA(Hidden),
	};
}

namespace ECsInputType
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Action = TCsString(TEXT("Action"), TEXT("action"));
		const TCsString Axis = TCsString(TEXT("Axis"), TEXT("axis"));
		const TCsString Trigger = TCsString(TEXT("Trigger"), TEXT("trigger"));
		const TCsString Location = TCsString(TEXT("Location"), TEXT("location"));
		const TCsString Rotation = TCsString(TEXT("Rotation"), TEXT("rotation"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Action) { return Str::Action.Value; }
		if (EType == Type::Axis) { return Str::Axis.Value; }
		if (EType == Type::Trigger) { return Str::Trigger.Value; }
		if (EType == Type::Location) { return Str::Location.Value; }
		if (EType == Type::Rotation) { return Str::Rotation.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Action) { return Type::Action; }
		if (String == Str::Axis) { return Type::Axis; }
		if (String == Str::Trigger) { return Type::Trigger; }
		if (String == Str::Location) { return Type::Location; }
		if (String == Str::Rotation) { return Type::Rotation; }
		return Type::ECsInputType_MAX;
	}
}

#define ECS_INPUT_TYPE_MAX (uint8)ECsInputType::ECsInputType_MAX
typedef ECsInputType::Type TCsInputType;

UENUM()
namespace ECsInputEvent
{
	enum Type
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
}

namespace ECsInputEvent
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString FirstPressed = TCsString(TEXT("FirstPressed"), TEXT("firstpressed"), TEXT("first pressed"));
		const TCsString Pressed = TCsString(TEXT("Pressed"), TEXT("pressed"), TEXT("pressed"));
		const TCsString FirstReleased = TCsString(TEXT("FirstReleased"), TEXT("firstreleased"), TEXT("first released"));
		const TCsString Released = TCsString(TEXT("Released"), TEXT("released"), TEXT("released"));
		const TCsString FirstMoved = TCsString(TEXT("FirstMoved"), TEXT("firstmoved"), TEXT("first moved"));
		const TCsString Moved = TCsString(TEXT("Moved"), TEXT("moved"), TEXT("moved"));
		const TCsString FirstStationary = TCsString(TEXT("FirstStationary"), TEXT("firststationary"), TEXT("first stationary"));
		const TCsString Stationary = TCsString(TEXT("Stationary"), TEXT("stationary"), TEXT("stationary"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::FirstPressed) { return Str::FirstPressed.Value; }
		if (EType == Type::Pressed) { return Str::Pressed.Value; }
		if (EType == Type::FirstReleased) { return Str::FirstReleased.Value; }
		if (EType == Type::Released) { return Str::Released.Value; }
		if (EType == Type::FirstMoved) { return Str::FirstMoved.Value; }
		if (EType == Type::Moved) { return Str::Moved.Value; }
		if (EType == Type::FirstStationary) { return Str::FirstStationary.Value; }
		if (EType == Type::Stationary) { return Str::Stationary.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::FirstPressed) { return Type::FirstPressed; }
		if (String == Str::Pressed) { return Type::Pressed; }
		if (String == Str::FirstReleased) { return Type::FirstReleased; }
		if (String == Str::Released) { return Type::Released; }
		if (String == Str::FirstMoved) { return Type::FirstMoved; }
		if (String == Str::Moved) { return Type::Moved; }
		if (String == Str::FirstStationary) { return Type::FirstStationary; }
		if (String == Str::Stationary) { return Type::Stationary; }
		return Type::ECsInputEvent_MAX;
	}
}

#define ECS_INPUT_EVENT_MAX (uint8)ECsInputEvent::ECsInputEvent_MAX
typedef TEnumAsByte<ECsInputEvent::Type> TCsInputEvent;

UENUM()
namespace ECsInputValue
{
	enum Type
	{
		Void				UMETA(DisplayName = "Void"),
		Float				UMETA(DisplayName = "Float"),
		Vector				UMETA(DisplayName = "Vector"),
		Rotator				UMETA(DisplayName = "Rotator"),
		ECsInputValue_MAX	UMETA(Hidden),
	};
}

namespace ECsInputValue
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Void = TCsString(TEXT("Void"), TEXT("void"));
		const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
		const TCsString Vector = TCsString(TEXT("Vector"), TEXT("vector"));
		const TCsString Rotator = TCsString(TEXT("Rotator"), TEXT("rotator"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Void) { return Str::Void.Value; }
		if (EType == Type::Float) { return Str::Float.Value; }
		if (EType == Type::Vector) { return Str::Vector.Value; }
		if (EType == Type::Rotator) { return Str::Rotator.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Void) { return Type::Void; }
		if (String == Str::Float) { return Type::Float; }
		if (String == Str::Vector) { return Type::Vector; }
		if (String == Str::Rotator) { return Type::Rotator; }
		return Type::ECsInputValue_MAX;
	}
}

#define ECS_INPUT_VALUE_MAX (uint8)ECsInputValue::ECsInputValue_MAX
typedef ECsInputValue::Type TCsInputValue;

namespace ECsInputActionMap
{
	enum BitMask : int32;
}

typedef ECsInputActionMap::BitMask TCsInputActionMap;

typedef FString(*TCsInputActionMapToString)(const int32&);
typedef TCsInputActionMap(*TCsStringToInputActionMap)(const FString&);

namespace ECsInputAction
{
	enum Type : uint8;
}

typedef ECsInputAction::Type TCsInputAction;

typedef FString(*TCsInputActionToString)(const TCsInputAction&);
typedef TCsInputAction(*TCsStringToInputAction)(const FString&);

#define CS_INVALID_INPUT_POOL_INDEX 65535

USTRUCT()
struct FCsInputInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TEnumAsByte<ECsInputType::Type> Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TEnumAsByte<ECsInputValue::Type> ValueType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TEnumAsByte<ECsInputEvent::Type> Event;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TEnumAsByte<ECsInputEvent::Type> Last_Event;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FRotator Rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float Duration;

	FCsInputInfo& operator=(const FCsInputInfo& B)
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

	bool operator==(const FCsInputInfo& B) const
	{
		return Type == B.Type && ValueType == B.ValueType && 
			   Event == B.Event && Last_Event == B.Last_Event &&
			   Value == B.Value && Location == B.Location && Rotation == B.Rotation &&
			   Duration == B.Duration;
	}

	bool operator!=(const FCsInputInfo& B) const
	{
		return !(*this == B);
	}

	void Set(const TCsInputEvent &inEvent, const float &inValue)
	{
		Event = inEvent;
		Value = inValue;
	}

	void Set(const TCsInputEvent &inEvent, const FVector &inLocation)
	{
		Event = inEvent;
		Location = inLocation;
	}

	void Set(const TCsInputEvent &inEvent, const FRotator &inRotation)
	{
		Event = inEvent;
		Rotation = inRotation;
	}
};

USTRUCT()
struct FRep_CsInput
{
	GENERATED_USTRUCT_BODY()

	ECsInputAction::Type Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TEnumAsByte<ECsInputEvent::Type> Event;

	FRep_CsInput& operator=(const FRep_CsInput& B)
	{
		Action = B.Action;
		Event  = B.Event;
		return *this;
	}

	bool operator==(const FRep_CsInput& B) const
	{
		return Action == B.Action && Event == B.Event;
	}

	bool operator!=(const FRep_CsInput& B) const
	{
		return !(*this == B);
	}

	void Init(const TCsInputAction &inAction, const TCsInputEvent &inEvent)
	{
		Action = inAction;
		Event = inEvent;
	}

	void Reset()
	{
		//Action = ECsInputAction::ECsInputAction_MAX;
		Event  = ECsInputEvent::ECsInputEvent_MAX;
	}
};

USTRUCT()
struct FCsInput
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Input")
	uint16 PoolIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool IsAllocated;

	ECsInputAction::Type Action;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Input")
	uint8 Action_Script;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FString ActionAsString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TEnumAsByte<ECsInputEvent::Type> Event;
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
		//Action	  = ECsInputAction::ECsInputAction_MAX;
		Event	  = ECsInputEvent::ECsInputEvent_MAX;
		Value	  = INFINITY;
		Location  = FVector::ZeroVector;
		Rotation  = FRotator::ZeroRotator;
	}

	FCsInput& operator=(const FRep_CsInput& B)
	{
		Action = B.Action;
		Event  = B.Event;
		return *this;
	}

	void Init(const uint16 &inPoolIndex)
	{
		PoolIndex = inPoolIndex;
	}

	void Set(const TCsInputAction &inAction, const TCsInputEvent &inEvent, const float &inValue, const FVector &inLocation, const FRotator &inRotation)
	{
		Action		  = inAction;
		Action_Script = (uint8)Action;
		Event		  = inEvent;
		Value		  = inValue;
		Location	  = inLocation;
		Rotation	  = inRotation;
	}

	void Set(const TCsInputAction &inAction, const TCsInputEvent &inEvent, const FVector &inLocation)
	{
		Set(inAction, inEvent, 0.0f, inLocation, FRotator::ZeroRotator);
	}

	void Set(const TCsInputAction &inAction, const TCsInputEvent &inEvent, const FRotator &inRotation)
	{
		Set(inAction, inEvent, 0.0f, FVector::ZeroVector, inRotation);
	}

	void Set(const TCsInputAction &inAction, const TCsInputEvent &inEvent, const float &inValue)
	{
		Set(inAction, inEvent, inValue, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void Set(const TCsInputAction &inAction, const TCsInputEvent &inEvent)
	{
		Set(inAction, inEvent, 0.0f, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void Allocate(const TCsInputAction &inAction, const TCsInputEvent &inEvent, const float &inValue, const FVector &inLocation, const FRotator &inRotation)
	{
		IsAllocated = true;
		Set(inAction, inEvent, inValue, inLocation, inRotation);
	}

	void Allocate(const TCsInputAction &inAction, const TCsInputEvent &inEvent, const FVector &inLocation)
	{
		Allocate(inAction, inEvent, 0.0f, inLocation, FRotator::ZeroRotator);
	}

	void Allocate(const TCsInputAction &inAction, const TCsInputEvent &inEvent, const FRotator &inRotation)
	{
		Allocate(inAction, inEvent, 0.0f, FVector::ZeroVector, inRotation);
	}

	void Allocate(const TCsInputAction &inAction, const TCsInputEvent &inEvent, const float &inValue)
	{
		Allocate(inAction, inEvent, inValue, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void Allocate(const TCsInputAction &inAction, const TCsInputEvent &inEvent)
	{
		Allocate(inAction, inEvent, 0.0f, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void Reset()
	{
		IsAllocated   = false;
		//Action	  = ECsInputAction::ECsInputAction_MAX;
		Action_Script = 255;
		Event		  = ECsInputEvent::ECsInputEvent_MAX;
		Value		  = INFINITY;
		Location	  = FVector::ZeroVector;
		Rotation	  = FRotator::ZeroRotator;
		Duration	  = 0.0f;
	}
};

USTRUCT()
struct FCsInputFrame
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

	FCsInputFrame& operator=(const FCsInputFrame& B)
	{
		Time = B.Time;
		RealTime = B.RealTime;
		DeltaTime = B.DeltaTime;
		Frame = B.Frame;


		Inputs.Reset();
		const uint16 Count = B.Inputs.Num();

		for (uint16 I = 0; I < Count; I++)
		{
			Inputs.Add(B.Inputs[I]);
		}
		return *this;
	}

	void Init(const float &inTime, const float &inRealTime, const float &inDeltaTime, const uint64 &inFrame)
	{
		Time	  = inTime;
		RealTime  = inRealTime;
		DeltaTime = inDeltaTime;
		Frame	  = inFrame;

		const uint16 Count = Inputs.Num();

		for (uint16 I = 0; I < Count; I++)
		{
			Inputs[I]->Reset();
		}
		Inputs.Reset();
	}

	FCsInput* GetInput(const TCsInputAction &Action)
	{
		const uint16 Count = Inputs.Num();

		for (uint16 I = 0; I < Count; I++)
		{
			if ((*(Inputs[I])).Action == Action)
				return Inputs[I];
		}
		return nullptr;
	}

	FCsInput* GetInput(const TCsInputAction &Action, const TCsInputEvent &Event)
	{
		if (FCsInput* Input = GetInput(Action))
			return Input->Event == Event ? Input : nullptr;
		return nullptr;
	}

	FCsInput* GetInput(const TCsInputAction &Action, const TArray<TCsInputEvent> &Events)
	{
		if (FCsInput* Input = GetInput(Action))
			return Events.Find(Input->Event) != INDEX_NONE ? Input : nullptr;
		return nullptr;
	}
};

USTRUCT()
struct FCsInputWord
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

	void AddAndInput(const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value, const FVector &Location, const FRotator &Rotation)
	{
		AndInputs.AddDefaulted();
		const int32 Index = AndInputs.Num() - 1;
		AndInputs[Index].Action = Action;
		AndInputs[Index].Event = Event;
		AndInputs[Index].Value = Value;
		AndInputs[Index].Location = Location;
		AndInputs[Index].Rotation = Rotation;
	}

	void AddAndInput(const TCsInputAction &Action, const TCsInputEvent &Event)
	{
		AddAndInput(Action, Event, 0.0f, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void AddAndInput(const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value)
	{
		AddAndInput(Action, Event, Value, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void AddAndInput(const TCsInputAction &Action, const TCsInputEvent &Event, const FVector &Location)
	{
		AddAndInput(Action, Event, 0.0f, Location, FRotator::ZeroRotator);
	}

	void AddAndInput(const TCsInputAction &Action, const TCsInputEvent &Event, const FRotator &Rotation)
	{
		AddAndInput(Action, Event, 0.0f, FVector::ZeroVector, Rotation);
	}

	void AddOrInput(const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value, const FVector &Location, const FRotator &Rotation)
	{
		OrInputs.AddDefaulted();
		const int32 Index = OrInputs.Num() - 1;
		OrInputs[Index].Action = Action;
		OrInputs[Index].Event = Event;
		OrInputs[Index].Value = Value;
		OrInputs[Index].Location = Location;
		OrInputs[Index].Rotation = Rotation;
	}

	void AddOrInput(const TCsInputAction &Action, const TCsInputEvent &Event)
	{
		AddOrInput(Action, Event, 0.0f, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void AddOrInput(const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value)
	{
		AddOrInput(Action, Event, Value, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	void AddOrInput(const TCsInputAction &Action, const TCsInputEvent &Event, const FVector &Location)
	{
		AddOrInput(Action, Event, 0.0f, Location, FRotator::ZeroRotator);
	}

	void AddOrInput(const TCsInputAction &Action, const TCsInputEvent &Event, const FRotator &Rotation)
	{
		AddOrInput(Action, Event, 0.0f, FVector::ZeroVector, Rotation);
	}

	void Reset()
	{
		Completed = false;
	}

	void ProcessInput(FCsInputFrame &InputFrame)
	{
		int32 And = 0;
		bool Or   = false;

		const int32 Count = InputFrame.Inputs.Num();

		for (int32 I = Count - 1; I >= 0; I--)
		{
			FCsInput* Input = InputFrame.Inputs[I];

			// Check And
			const int32 AndCount = AndInputs.Num();

			for (int32 J = And; J < AndCount; J++)
			{
				if (Input->Action == AndInputs[J].Action &&
					Input->Event == AndInputs[J].Event)
				{
					And++;
				}
			}
			// Check Or
			const int32 OrCount = OrInputs.Num();

			for (int32 J = 0; J < OrCount; J++)
			{
				Or |= Input->Action == OrInputs[J].Action && Input->Event == OrInputs[J].Event;

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

USTRUCT()
struct FCsInputPhrase
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

	void AddAndInputToWord(const int32 &Index, const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value = 0.0f, const FVector &Location = FVector::ZeroVector, const FRotator &Rotation = FRotator::ZeroRotator)
	{
		const int32 Count = Words.Num();

		if (Index >= Count)
		{
			for (int32 I = 0; I < Index - Count + 1; I++)
			{
				Words.AddDefaulted();
			}
		}
		Words[Index].AddAndInput(Action, Event, Value, Location, Rotation);
	}

	void AddOrInputToWord(const int32 &Index, const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value = 0.0f, const FVector &Location = FVector::ZeroVector, const FRotator &Rotation = FRotator::ZeroRotator)
	{
		const int32 Count = Words.Num();

		if (Index >= Count)
		{
			for (int32 I = 0; I < Index - Count + 1; I++)
			{
				Words.AddDefaulted();
			}
		}
		Words[Index].AddOrInput(Action, Event, Value, Location, Rotation);
	}

	void Reset()
	{
		const int32 Count = Words.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Words[I].Reset();
		}
		Completed = false;
		CompletedTime = 0.0f;
	}

	void ProcessInput(FCsInputFrame &InputFrame)
	{
		const float CurrentTime = InputFrame.Time;

		// Check if ALL Words are Completed
		const int32 Count = Words.Num();
		int32 Index		  = 0;

		if (UseInterval)
		{
			float ElapsedTime			= 0.0f;
			float EarliestCompletedTime = CurrentTime;

			for (Index = 0; Index < Count; Index++)
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
			for (Index = 0; Index < Count; Index++)
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

USTRUCT()
struct FCsInputSentence
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

	void Reset()
	{
		Active = true;

		const int32 Count = Phrases.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Phrases[I].Reset();
		}
		Completed = false;
	}

	void ProcessInput(FCsInputFrame &InputFrame)
	{
		const float CurrentTime = InputFrame.Time;

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

			for (Index = 0; Index < Count; Index++)
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
			for (Index = 0; Index < Count; Index++)
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

USTRUCT()
struct FCsInputActionMapping
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FString ActionName;

	TCsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FString KeyName;

	FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float Scale;

	FCsInputActionMapping& operator=(const FCsInputActionMapping& B)
	{
		ActionName = B.ActionName;
		Action = B.Action;
		KeyName = B.KeyName;
		Key = B.Key;
		Scale = B.Scale;
		return *this;
	}

	bool operator==(const FCsInputActionMapping& B) const
	{
		return ActionName == B.ActionName &&
			   Action == B.Action &&
			   KeyName == B.KeyName &&
			   Key == B.Key &&
			   Scale == B.Scale;
	}

	bool operator!=(const FCsInputActionMapping& B) const
	{
		return !(*this == B);
	}
};

USTRUCT()
struct FCsInputActionMappings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FCsInputActionMapping> Mappings;

	FCsInputActionMappings& operator=(const FCsInputActionMappings& B)
	{
		Mappings.Reset();

		const int32 Count = B.Mappings.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Mappings.AddDefaulted();
			Mappings[I] = B.Mappings[I];
		}
		return *this;
	}

	bool operator==(const FCsInputActionMappings& B) const
	{
		if (Mappings.Num() != B.Mappings.Num())
			return false;

		const int32 Count = Mappings.Num();

		for (int32 I = 0; I < Count; I++)
		{

		}
		return true;
	}

	bool operator!=(const FCsInputActionMappings& B) const
	{
		return !(*this == B);
	}
};

USTRUCT()
struct FCsInputProfile
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

	FCsInputActionMapping& GetMapping(const TCsInputDevice &Device, const TCsInputAction &Action)
	{
		FCsInputActionMappings& DeviceMapping   = DeviceMappings[(uint8)Device];
		TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

		const int32 Count = Mappings.Num();

		for (int32 I = 0; I < Count; I++)
		{
			const FCsInputActionMapping& Mapping = Mappings[I];

			if (Action == Mapping.Action)
				return DeviceMapping.Mappings[I];
		}
		return Mappings[CS_FIRST];
	}

	FKey GetKey(const TCsInputDevice &Device, const TCsInputAction &Action)
	{
		FCsInputActionMappings& DeviceMapping   = DeviceMappings[(uint8)Device];
		TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

		const int32 Count = Mappings.Num();

		for (int32 I = 0; I < Count; I++)
		{
			const FCsInputActionMapping& Mapping = Mappings[I];

			if (Action == Mapping.Action)
				return Mapping.Key;
		}
		return EKeys::Invalid;
	}

	void SetKey(const TCsInputDevice &Device, const TCsInputAction &Action, const FKey &Key)
	{
		FCsInputActionMappings& DeviceMapping   = DeviceMappings[(uint8)Device];
		TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

		const int32 Count = Mappings.Num();

		for (int32 I = 0; I < Count; I++)
		{
			FCsInputActionMapping& Mapping = Mappings[I];

			if (Action == Mapping.Action)
			{
				Mapping.KeyName = Key == EKeys::Invalid ? TEXT("") : Key.GetDisplayName().ToString();;
				Mapping.Key		= Key;
				break;
			}
		}
	}

	void AddMapping(const TCsInputDevice &Device, const FString &ActionName, const TCsInputAction &Action, const FString &KeyName, const FKey &Key)
	{
		FCsInputActionMappings& DeviceMapping   = DeviceMappings[(uint8)Device];
		TArray<FCsInputActionMapping>& Mappings = DeviceMapping.Mappings;

		const int32 Count = Mappings.Num();
		Mappings.AddDefaulted();
		FCsInputActionMapping& Mapping = Mappings[Count];
		Mapping.ActionName = ActionName;
		Mapping.Action	   = Action;
		Mapping.KeyName	   = KeyName;
		Mapping.Key		   = Key;
	}

	void Reset()
	{
		for (int32 I = 0; I < ECS_INPUT_DEVICE_MAX; I++)
		{
			DeviceMappings[I].Mappings.Reset();
		}
	}
};

#pragma endregion Input

// Game
#pragma region

namespace ECsGameEvent
{
	enum Type : uint8;
}

typedef ECsGameEvent::Type TCsGameEvent;

namespace ECsRep_GameEvent
{
	enum BitMask : int32;
}

#define CS_MAX_REP_GAME_EVENTS 32
typedef ECsRep_GameEvent::BitMask TCsRep_GameEvent;

USTRUCT()
struct FCsGameEventDefinition
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FCsInputSentence Sentence;

	TCsGameEvent Event;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	uint8 Event_Script;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FString EventAsString;
};

#define CS_GAME_EVENT_DEFINITION_START(Definitions, EVENT)	{ \
																Definitions.AddDefaulted(); \
																FCsGameEventDefinition& Def = Definitions[Definitions.Num() - 1]; \
																Def.Event = ECsGameEvent::EVENT; \
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

#define CS_GAME_EVENT_DEFINITION_SIMPLE(Definitions, GAMEEVENT, ACTION, EVENT)	{ \
																					Definitions.AddDefaulted(); \
																					FCsGameEventDefinition& Def = Definitions[Definitions.Num() - 1]; \
																					Def.Event = ECsGameEvent::GAMEEVENT; \
																					FCsInputSentence& Sentence = Def.Sentence; \
																					Sentence.Phrases.AddDefaulted(); \
																					FCsInputPhrase& Phrase = Sentence.Phrases[Sentence.Phrases.Num() - 1]; \
																					Phrase.Words.AddDefaulted(); \
																					FCsInputWord& Word = Phrase.Words[Phrase.Words.Num() - 1]; \
																					Word.AddOrInput(ECsInputAction::ACTION, ECsInputEvent::EVENT); \
																				}

#pragma endregion