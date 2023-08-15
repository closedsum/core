// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input")
	ECsInputType Type;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input")
	ECsInputValue ValueType;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input")
	ECsInputEvent Event;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input")
	ECsInputEvent Last_Event;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input")
	FKey Key;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input")
	float Value;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input")
	float Last_Value;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input")
	FVector3f Location;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input")
	FVector3f Last_Location;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input")
	FRotator3f Rotation;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input")
	float Duration;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input")
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

	FORCEINLINE void Set(const ECsInputEvent& InEvent, const FVector3f& InLocation)
	{
		Event = InEvent;
		Location = InLocation;
	}

	FORCEINLINE void Set(const ECsInputEvent& InEvent, const FRotator3f& InRotation)
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

	FORCEINLINE void ResetLocation() { Location = Last_Location = FVector3f::ZeroVector; }

	FORCEINLINE void ResetRotation() { Rotation = FRotator3f::ZeroRotator; }
};

#pragma endregion FCsInputInfo

// FRep_CsInput
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FRep_CsInput
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input")
	FECsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input")
	ECsInputEvent Event;

	FRep_CsInput() :
		Action(),
		Event()
	{
	}

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

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input")
	bool bDeallocate;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Input")
	bool bConsumed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input")
	FECsInputAction Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input")
	ECsInputEvent Event;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input")
	float Value;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input")
	FVector3f Location;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input")
	FRotator3f Rotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input")
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

	FORCEINLINE void Set(const FECsInputAction& inAction, const ECsInputEvent& inEvent, const float& inValue, const FVector3f& inLocation, const FRotator3f& inRotation)
	{
		Action		  = inAction;
		Event		  = inEvent;
		Value		  = inValue;
		Location	  = inLocation;
		Rotation	  = inRotation;
	}

	FORCEINLINE void Set(const FECsInputAction& inAction, const ECsInputEvent& inEvent, const FVector3f& inLocation)
	{
		Set(inAction, inEvent, 0.0f, inLocation, FRotator3f::ZeroRotator);
	}

	FORCEINLINE void Set(const FECsInputAction& inAction, const ECsInputEvent& inEvent, const FRotator3f& inRotation)
	{
		Set(inAction, inEvent, 0.0f, FVector3f::ZeroVector, inRotation);
	}

	FORCEINLINE void Set(const FECsInputAction& inAction, const ECsInputEvent& inEvent, const float& inValue)
	{
		Set(inAction, inEvent, inValue, FVector3f::ZeroVector, FRotator3f::ZeroRotator);
	}

	FORCEINLINE void Set(const FECsInputAction& inAction, const ECsInputEvent& inEvent)
	{
		Set(inAction, inEvent, 0.0f, FVector3f::ZeroVector, FRotator3f::ZeroRotator);
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
		Location  = FVector3f::ZeroVector;
		Rotation  = FRotator3f::ZeroRotator;
		Duration  = 0.0f;
	}

	FORCEINLINE bool IsValid() const
	{
		return EMCsInputAction::Get().IsValidEnum(Action) && Event != ECsInputEvent::ECsInputEvent_MAX;
	}
};

#pragma endregion FCsInput