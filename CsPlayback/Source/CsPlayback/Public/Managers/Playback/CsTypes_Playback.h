// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsTypes_Input.h"
#include "Managers/Time/CsTypes_Time.h"

#include "CsTypes_Playback.generated.h"
#pragma once

// PlaybackEventRepeatedState
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsPlaybackEventRepeatedState : uint8
{
	None								UMETA(DisplayName = "None"),
	Start								UMETA(DisplayName = "Start"),
	End									UMETA(DisplayName = "End"),
	ECsPlaybackEventRepeatedState_MAX	UMETA(Hidden),
};

struct CSPLAYBACK_API EMCsPlaybackEventRepeatedState : public TCsEnumMap<ECsPlaybackEventRepeatedState>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPlaybackEventRepeatedState, ECsPlaybackEventRepeatedState)
};

namespace NCsPlaybackEventRepeatedState
{
	typedef ECsPlaybackEventRepeatedState Type;

	namespace Ref
	{
		extern CSPLAYBACK_API const Type None;
		extern CSPLAYBACK_API const Type Start;
		extern CSPLAYBACK_API const Type End;
		extern CSPLAYBACK_API const Type ECsPlaybackEventRepeatedState_MAX;
	}
}

#pragma endregion PlaybackEventRepeatedState

// FCsPlaybackByEvent
#pragma region

USTRUCT(BlueprintType)
struct CSPLAYBACK_API FCsPlaybackByEvent
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
	FECsGameEvent Event;

	UPROPERTY()
	float Value;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	ECsPlaybackEventRepeatedState RepeatedState;

	FCsPlaybackByEvent() :
		Event(),
		Value(0.0f),
		Location(FVector::ZeroVector),
		RepeatedState(ECsPlaybackEventRepeatedState::None)
	{
	}

	FORCEINLINE bool IsValid() const
	{
		return EMCsGameEvent::Get().IsValidEnum(Event);
	}

	void Reset()
	{
		Event = EMCsGameEvent::Get().GetMAX();
		Value = 0.0f;
		Location = FVector::ZeroVector;
		RepeatedState = ECsPlaybackEventRepeatedState::None;
	}
};

#pragma endregion FCsPlaybackByEvent

// FCsPlaybackByEventsByDeltaTime
#pragma region

USTRUCT(BlueprintType)
struct CSPLAYBACK_API FCsPlaybackByEventsByDeltaTime
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
	FCsDeltaTime DeltaTime;

	UPROPERTY()
	TArray<FCsPlaybackByEvent> Events;

	FCsPlaybackByEventsByDeltaTime() :
		DeltaTime(),
		Events()
	{
	}
};

#pragma endregion FCsPlaybackByEventsByDeltaTime

// FCsPlaybackByEvents
#pragma region

USTRUCT(BlueprintType)
struct CSPLAYBACK_API FCsPlaybackByEvents
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
	FString Username;

	UPROPERTY()
	FDateTime Date;

	UPROPERTY()
	FSoftObjectPath Level;

	UPROPERTY()
	TArray<FCsPlaybackByEventsByDeltaTime> Events;

	FCsPlaybackByEvents() :
		Username(),
		Date(1, 1, 1, 0, 0, 0, 0),
		Level(),
		Events()
	{
	}

	bool CopyFrom(const FCsPlaybackByEvents& From)
	{
		const int32 ToCount	  = Events.Num();
		const int32 FromCount = From.Events.Num();

		if (ToCount < FromCount)
		{
			for (int32 I = ToCount; I < FromCount; ++I)
			{
				Events.Add(From.Events[I]);
			}
			return true;
		}
		return false;
	}

	void Reset()
	{
		Events.Reset(Events.Max());
	}
};

#pragma endregion FCsPlaybackByEvents
