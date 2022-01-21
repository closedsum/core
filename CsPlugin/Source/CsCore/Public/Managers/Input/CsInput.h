// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Input/CsTypes_Input.h"
#include "Managers/Input/Action/CsInputAction.h"
#include "InputCoreTypes.h"

#include "CsInput.generated.h"

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

	UPROPERTY(BlueprintReadOnly)
	bool bDirty;

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
		Duration(0.0f),
		bDirty(false)
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

	FORCEINLINE const bool& IsDirty() const { return bDirty; }
	FORCEINLINE void MarkDirty() { bDirty = true; }
	FORCEINLINE void ClearDirty() { bDirty = false; }

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