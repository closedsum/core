// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

// Types
#include "Types/CsTypes_Primitive.h"
#include "Types/Enum/CsEnumMap.h"
#include "Types/Enum/CsEnumMask_int32.h"
#include "Types/Enum/CsEnumStructMaskMap.h"
#include "Types/Enum/CsEnumFlagMap.h"
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

	// InputMode
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsInputMode : uint8
{
	Mouse				UMETA(DisplayName = "Mouse"),				// 0
	Keyboard			UMETA(DisplayName = "Keyboard"),			// 1
	Gamepad				UMETA(DisplayName = "Gamepad"),				// 2
	Touch				UMETA(DisplayName = "Touch"),				// 3
	MotionController	UMETA(DisplayName = "Motion Controller"),	// 4
};

struct CSCORE_API EMCsInputMode : public TCsEnumFlagMap<ECsInputMode>
{
	CS_ENUM_FLAG_MAP_BODY(EMCsInputMode, ECsInputMode)
};

namespace NCsInputMode
{
	typedef ECsInputMode Type;

	namespace Ref
	{
		extern CSCORE_API const Type Mouse;
		extern CSCORE_API const Type Keyboard;
		extern CSCORE_API const Type Gamepad;
		extern CSCORE_API const Type Touch;
		extern CSCORE_API const Type MotionController;
	}

	extern CSCORE_API const int32 None;
	extern CSCORE_API const int32 All;
}

#define CS_INPUT_MODE_NONE 0

#pragma endregion InputMode

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
	typedef EMCsInputActionMap EnumMapType;

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
	typedef EMCsInputAction EnumMapType;

	// Mouse
	extern CSCORE_API const Type Default__MousePositionXY__;
	extern CSCORE_API const Type Default__MouseLeftButton__;
	extern CSCORE_API const Type Default__MouseRightButton__;
	// Touch
		// Action
	extern CSCORE_API const Type Default__Touch_0__;
	extern CSCORE_API const Type Default__Touch_1__;
	extern CSCORE_API const Type Default__Touch_2__;
	extern CSCORE_API const Type Default__Touch_3__;
	extern CSCORE_API const Type Default__Touch_4__;
	extern CSCORE_API const Type Default__Touch_5__;
	extern CSCORE_API const Type Default__Touch_6__;
	extern CSCORE_API const Type Default__Touch_7__;
	extern CSCORE_API const Type Default__Touch_8__;
	extern CSCORE_API const Type Default__Touch_9__;
		// Location
	extern CSCORE_API const Type Default__TouchPositionXY_0__;
	extern CSCORE_API const Type Default__TouchPositionXY_1__;
	extern CSCORE_API const Type Default__TouchPositionXY_2__;
	extern CSCORE_API const Type Default__TouchPositionXY_3__;
	extern CSCORE_API const Type Default__TouchPositionXY_4__;
	extern CSCORE_API const Type Default__TouchPositionXY_5__;
	extern CSCORE_API const Type Default__TouchPositionXY_6__;
	extern CSCORE_API const Type Default__TouchPositionXY_7__;
	extern CSCORE_API const Type Default__TouchPositionXY_8__;
	extern CSCORE_API const Type Default__TouchPositionXY_9__;

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion InputAction

	// FCsInputActionSet
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputActionSet
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSet<FECsInputAction> Actions;

	FCsInputActionSet() :
		Actions()
	{
	}

	void ConditionalRebuild()
	{
		TArray<FECsInputAction> ToRemove;
		TArray<FECsInputAction> ToAdd;

		for (const FECsInputAction& Action : Actions)
		{
			const FECsInputAction& ByName = EMCsInputAction::Get().GetEnum(Action.GetFName());
			const FECsInputAction& ByValue = EMCsInputAction::Get().GetEnum(Action.GetValue());

			if (ByValue != Action)
			{
				ToRemove.Add(Action);
				ToAdd.Add(ByName);
			}
		}

		for (const FECsInputAction& Action : ToRemove)
		{
			Actions.Remove(Action);
		}

		for (const FECsInputAction& Action : ToAdd)
		{
			Actions.Add(Action);
		}
	}
};

#pragma endregion FCsInputActionSet

	// FCsInputActionAndEvent
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsInputActionAndEvent
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
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

	// FCsInputInfo
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsInputInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	ECsInputType Type;

	UPROPERTY(BlueprintReadOnly)
	ECsInputValue ValueType;

	UPROPERTY(BlueprintReadOnly)
	ECsInputEvent Event;

	UPROPERTY(BlueprintReadOnly)
	ECsInputEvent Last_Event;

	UPROPERTY(BlueprintReadOnly)
	FKey Key;

	UPROPERTY(BlueprintReadOnly)
	float Value;

	UPROPERTY(BlueprintReadOnly)
	float Last_Value;

	UPROPERTY(BlueprintReadOnly)
	FVector Location;

	UPROPERTY(BlueprintReadOnly)
	FVector Last_Location;

	UPROPERTY(BlueprintReadOnly)
	FRotator Rotation;

	UPROPERTY(BlueprintReadOnly)
	float Duration;

	FCsInputInfo() :
		Type(ECsInputType::ECsInputType_MAX),
		ValueType(ECsInputValue::ECsInputValue_MAX),
		Event(ECsInputEvent::ECsInputEvent_MAX),
		Last_Event(ECsInputEvent::ECsInputEvent_MAX),
		Key(EKeys::AnyKey),
		Value(0.0f),
		Last_Value(0.0f),
		Location(0.0f),
		Last_Location(0.0f),
		Rotation(0.0f),
		Duration(0.0f)
	{
	}

	FORCEINLINE void Set(const ECsInputEvent& InEvent, const float& InValue)
	{
		Event = InEvent;
		Value = InValue;
	}

	FORCEINLINE void Set(const ECsInputEvent& InEvent, const FVector& InLocation)
	{
		Event = InEvent;
		Location = InLocation;
	}

	FORCEINLINE void Set(const ECsInputEvent& InEvent, const FRotator& InRotation)
	{
		Event = InEvent;
		Rotation = InRotation;
	}

	FORCEINLINE bool HasEventChanged() const
	{
		return Event != Last_Event;
	}

	FORCEINLINE void FlushEvent()
	{
		Last_Event = Event;
	}

	FORCEINLINE bool IsValid() const
	{
		return Type != ECsInputType::ECsInputType_MAX && ValueType != ECsInputValue::ECsInputValue_MAX;
	}

	FORCEINLINE void ResetValue(){ Value = Last_Value = 0.0f; }

	FORCEINLINE void ResetLocation() { Location = Last_Location = FVector::ZeroVector; }

	FORCEINLINE void ResetRotation() { Rotation = FRotator::ZeroRotator; }
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsInputEvent Event;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Value;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Location;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator Rotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
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

	FORCEINLINE bool IsValid() const
	{
		return EMCsInputAction::Get().IsValidEnum(Action) && Event != ECsInputEvent::ECsInputEvent_MAX;
	}
};

#pragma endregion FCsInput

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsInputValue ValueType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Value;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsInputValueRule ValueRule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Location;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsInputLocationRule LocationRule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsInputValue ValueType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsInputCompletedValueReturnType ReturnType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Value;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Location;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator Rotation;

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

	UPROPERTY(BlueprintReadOnly)
	bool bPass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsInputEvent Event;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bAnyEvent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsInputCompareValue CompareValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
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

	UPROPERTY(BlueprintReadOnly)
	bool bCompleted;

	UPROPERTY(BlueprintReadOnly)
	float CompletedTime;

	UPROPERTY(BlueprintReadOnly)
	bool bConsume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCsInputDescription> AndInputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCsInputDescription> OrInputs;

	UPROPERTY(BlueprintReadWrite)
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

	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector& Location, const FRotator& Rotation);
	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event);
	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value);
	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FVector& Location);
	void AddAndInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FRotator& Rotation);
	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector& Location, const FRotator& Rotation);
	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event);
	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value);
	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FVector& Location);
	void AddOrInput(const FECsInputAction& Action, const ECsInputEvent& Event, const FRotator& Rotation);

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

	UPROPERTY(BlueprintReadOnly)
	bool bCompleted;

	UPROPERTY(BlueprintReadOnly)
	float CompletedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (editcondition = "bInterval", ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (editcondition = "bFrames", ClampMin = "0", UIMin = "0"))
	int32 Frames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCsInputWord> Words;

	UPROPERTY(BlueprintReadWrite)
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

	void AddAndInputToWord(const int32& Index, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value = 0.0f, const FVector& Location = FVector::ZeroVector, const FRotator& Rotation = FRotator::ZeroRotator);
	void AddOrInputToWord(const int32& Index, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value = 0.0f, const FVector& Location = FVector::ZeroVector, const FRotator& Rotation = FRotator::ZeroRotator);

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

	UPROPERTY(BlueprintReadOnly)
	bool bActive;

	UPROPERTY(BlueprintReadOnly)
	bool bCompleted;

	UPROPERTY(BlueprintReadOnly)
	float CompletedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (editcondition = "bInterval", ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InlineEditConditionToggle))
	bool bFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (editcondition = "bFrames", ClampMin = "0", UIMin = "0"))
	int32 Frames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCsInputPhrase> Phrases;

	UPROPERTY(BlueprintReadWrite)
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
		if (bCompleted != B.bActive) { return false; }
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
	FCsInputActionMappings DeviceMappings[(uint8)ECsInputDevice::ECsInputDevice_MAX];

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
	typedef EMCsGameEvent EnumMapType;

	extern CSCORE_API const Type Default__MousePositionXY__;
	extern CSCORE_API const Type Default__MouseLeftButtonPressed__;
	extern CSCORE_API const Type Default__MouseRightButtonPressed__;

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

struct FCsGameEventDefinition;

/**
*
*/
USTRUCT(BlueprintType)
struct FCsGameEventInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsGameEvent Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

private:

	FCsGameEventDefinition* Definition;

public:

	FCsGameEventInfo() :
		Event(),
		Value(0.0f),
		Location(0.0f),
		Definition(nullptr)
	{
	}

	FORCEINLINE FCsGameEventInfo& operator=(const FCsGameEventInfo& B)
	{
		Event = B.Event;
		Value = B.Value;
		Location = B.Location;
		return *this;
	}

	FORCEINLINE void SetDefinition(FCsGameEventDefinition* InDefinition){ Definition = InDefinition; }
	FORCEINLINE const FCsGameEventDefinition* GetDefinition() const { return Definition; }

	FORCEINLINE void Reset()
	{
		Event = EMCsGameEvent::Get().GetMAX();
		Value = 0.0f;
		Location = FVector::ZeroVector;
		Definition = nullptr;
	}

	FORCEINLINE bool IsValid() const
	{
		return EMCsGameEvent::Get().IsValidEnum(Event);
	}

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		checkf(IsValid(), TEXT("%s: Info is NOT Valid."), *Context);
		return true;
	}

	void ApplyInputCompletedValue(const FCsInputCompletedValue& CompletedValue)
	{
		// Value | Float
		if (CompletedValue.ValueType == ECsInputValue::Float)
			Value = CompletedValue.Value;
		// Location | Vector
		if (CompletedValue.ValueType == ECsInputValue::Vector)
			Location = CompletedValue.Location;
	}
};

#pragma endregion FCsGameEventInfo

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
struct FCsGameEventDefinitionActionOneOrWordNoCompletedValue
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsGameEvent GameEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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
struct FCsGameEventDefinitionActionOneOrWordOneEventNoCompletedValue
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsGameEvent GameEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FECsInputAction> Actions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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
struct FCsGameEventDefinitionAxisOneOrWordNoComparePassThroughValue
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsGameEvent GameEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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