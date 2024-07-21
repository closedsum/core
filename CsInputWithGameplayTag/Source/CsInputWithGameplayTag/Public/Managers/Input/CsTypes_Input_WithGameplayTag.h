// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Math.h"
#include "Types/Enum/CsEnumMap.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"

#include "CsTypes_Input_WithGameplayTag.generated.h"

// InputActionEvent
#pragma region

UENUM(BlueprintType)
enum class ECsInputActionEvent: uint8
{
	FirstPressed			UMETA(DisplayName = "First Pressed"),
	Pressed					UMETA(DisplayName = "Pressed"),
	FirstReleased			UMETA(DisplayName = "First Released"),
	Released				UMETA(DisplayName = "Released"),
	FirstMoved				UMETA(DisplayName = "First Moved"),
	Moved					UMETA(DisplayName = "Moved"),
	FirstStationary			UMETA(DisplayName = "First Stationary"),
	Stationary				UMETA(DisplayName = "Stationary"),
	ECsInputActionEvent_MAX	UMETA(Hidden),
};

struct CSINPUTWITHGAMEPLAYTAG_API EMCsInputActionEvent : public TCsEnumMap<ECsInputActionEvent>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInputActionEvent, ECsInputActionEvent)
};

namespace NCsInputActionEvent
{
	typedef ECsInputActionEvent Type;

	namespace Ref
	{
		extern CSINPUTWITHGAMEPLAYTAG_API const Type FirstPressed;
		extern CSINPUTWITHGAMEPLAYTAG_API const Type Pressed;
		extern CSINPUTWITHGAMEPLAYTAG_API const Type FirstReleased;
		extern CSINPUTWITHGAMEPLAYTAG_API const Type Released;
		extern CSINPUTWITHGAMEPLAYTAG_API const Type FirstMoved;
		extern CSINPUTWITHGAMEPLAYTAG_API const Type Moved;
		extern CSINPUTWITHGAMEPLAYTAG_API const Type FirstStationary;
		extern CSINPUTWITHGAMEPLAYTAG_API const Type Stationary;
		extern CSINPUTWITHGAMEPLAYTAG_API const Type ECsInputActionEvent_MAX;
	}

	namespace Mask
	{
		extern CSINPUTWITHGAMEPLAYTAG_API const uint32 Boolean;
		extern CSINPUTWITHGAMEPLAYTAG_API const uint32 FirstPressedOrPressed;
		extern CSINPUTWITHGAMEPLAYTAG_API const uint32 FirstReleasedOrReleased;
		extern CSINPUTWITHGAMEPLAYTAG_API const uint32 NonBoolean;
		extern CSINPUTWITHGAMEPLAYTAG_API const uint32 FirstMovedOrMoved;
		extern CSINPUTWITHGAMEPLAYTAG_API const uint32 FirstStationaryOrStationary;
	}

	FORCEINLINE uint32 ToMask(const TSet<ECsInputActionEvent>& Events)
	{
		uint32 Mask = 0;

		for (const ECsInputActionEvent& Event : Events)
		{
			CS_SET_BLUEPRINT_BITFLAG(Mask, Event);
		}
		return Mask;
	}

	FORCEINLINE bool IsFirstPressedOrPressed(const ECsInputActionEvent& Event)
	{
		return CS_TEST_BLUEPRINT_BITFLAG(NCsInputActionEvent::Mask::FirstPressedOrPressed, Event);
	}

	FORCEINLINE bool IsFirstReleasedOrReleased(const ECsInputActionEvent& Event)
	{
		return CS_TEST_BLUEPRINT_BITFLAG(NCsInputActionEvent::Mask::FirstReleasedOrReleased, Event);
	}

	FORCEINLINE bool IsFirstMovedOrMoved(const ECsInputActionEvent& Event)
	{
		return CS_TEST_BLUEPRINT_BITFLAG(NCsInputActionEvent::Mask::FirstMovedOrMoved, Event);
	}

	FORCEINLINE bool IsFirstStationaryOrStationary(const ECsInputActionEvent& Event)
	{
		return CS_TEST_BLUEPRINT_BITFLAG(NCsInputActionEvent::Mask::FirstStationaryOrStationary, Event);
	}
}

#pragma endregion InputActionEvent

USTRUCT(BlueprintType)
struct CSINPUTWITHGAMEPLAYTAG_API FCsInput_WithGameplayTag_Event
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsInput|WithGameplayTag|Event")
	int32 MappingIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsInput|WithGameplayTag|Event")
	int32 ActionIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsInput|WithGameplayTag|Event")
	FGameplayTag Tag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsInput|WithGameplayTag|Event")
	ECsInputActionEvent Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsInput|WithGameplayTag|Event")
	FInputActionValue Value;

	FCsInput_WithGameplayTag_Event() :
		MappingIndex(INDEX_NONE),
		ActionIndex(INDEX_NONE),
		Tag(),
		Event(ECsInputActionEvent::FirstPressed),
		Value()
	{
	}
};

namespace NCsInput
{
	namespace NWithGameplayTag
	{
		struct CSINPUTWITHGAMEPLAYTAG_API FEvent
		{
		public:

			int32 MappingIndex;

			int32 ActionIndex;

			FGameplayTag Tag;

			ECsInputActionEvent Event;

			FInputActionValue Value;

			FEvent() :
				MappingIndex(INDEX_NONE),
				ActionIndex(INDEX_NONE),
				Tag(),
				Event(ECsInputActionEvent::FirstPressed),
				Value()
			{
			}

			static FEvent Make(const FCsInput_WithGameplayTag_Event& B)
			{
				FEvent A;
				A.MappingIndex = B.MappingIndex;
				A.ActionIndex  = B.ActionIndex;
				A.Tag		   = B.Tag;
				A.Event		   = B.Event;
				A.Value		   = B.Value;
				return A;
			}

			static FCsInput_WithGameplayTag_Event Make(const FEvent& B)
			{
				FCsInput_WithGameplayTag_Event A;
				A.MappingIndex = B.MappingIndex;
				A.ActionIndex  = B.ActionIndex;
				A.Tag		   = B.Tag;
				A.Event		   = B.Event;
				A.Value		   = B.Value;
				return A;
			}

			FORCEINLINE bool IsBool() const { return Value.GetValueType() == EInputActionValueType::Boolean; }
			FORCEINLINE bool GetBool() const
			{
				check(IsBool());
				return Value.Get<bool>();
			}

			FORCEINLINE bool IsValid() const
			{
				return MappingIndex != INDEX_NONE;
			}

			FORCEINLINE void Reset()
			{
				MappingIndex = INDEX_NONE;
				ActionIndex = INDEX_NONE;
				Tag = FGameplayTag::EmptyTag;
				Event = ECsInputActionEvent::ECsInputActionEvent_MAX;
				Value.Reset();
			}
		};
	}
}

