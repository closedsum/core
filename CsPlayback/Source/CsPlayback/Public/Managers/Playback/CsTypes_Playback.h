// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Managers/Input/CsTypes_Input.h"
#include "Managers/Time/CsTypes_Time.h"
#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"
// GameEvent
#include "Managers/Input/GameEvent/CsGameEvent.h"
// Log
#include "Utility/CsPlaybackLog.h"

#include "CsTypes_Playback.generated.h"
#pragma once

// NCsPlayback::EState
#pragma region

namespace NCsPlayback
{
	enum class EState : uint8
	{
		None,
		PreparePlayback,
		QueuePlayback,
		Playback,
		Record,
		EState_MAX
	};

	struct CSPLAYBACK_API EMState : public TCsEnumMap<EState>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMState, EState)
	};

	namespace NState
	{
		namespace Ref
		{
			typedef EState Type;

			extern CSPLAYBACK_API const Type None;
			extern CSPLAYBACK_API const Type Playback;
			extern CSPLAYBACK_API const Type Record;
			extern CSPLAYBACK_API const Type EState_MAX;
		}
	}
}

#pragma endregion NCsPlayback::EState

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

	static const FCsPlaybackByEvent Invalid;

public:

	UPROPERTY()
	FECsGameEventCoordinatorGroup Group;

	UPROPERTY()
	FECsGameEvent Event;

	UPROPERTY()
	float Value;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	ECsPlaybackEventRepeatedState RepeatedState;

	FCsPlaybackByEvent() :
		Group(),
		Event(),
		Value(0.0f),
		Location(FVector::ZeroVector),
		RepeatedState(ECsPlaybackEventRepeatedState::None)
	{
	}

	FORCEINLINE bool operator==(const FCsPlaybackByEvent& B) const
	{
		return Group == B.Group && Event == B.Event && Value == B.Value && Location == B.Location;
	}

	FORCEINLINE bool operator!=(const FCsPlaybackByEvent& B) const
	{
		return !(*this == B);
	}

	friend uint32 GetTypeHash(const FCsPlaybackByEvent& B)
	{
		return GetTypeHash(B.Group) ^ GetTypeHash(B.Event) ^ GetTypeHash(B.Value) ^ GetTypeHash(B.Location);
	}

	FORCEINLINE bool IsValid() const
	{
		return EMCsGameEvent::Get().IsValidEnum(Event);
	}

	void Reset()
	{
		Group = EMCsGameEventCoordinatorGroup::Get().GetMAX();
		Event = EMCsGameEvent::Get().GetMAX();
		Value = 0.0f;
		Location = FVector::ZeroVector;
		RepeatedState = ECsPlaybackEventRepeatedState::None;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("Group: %s"), Group.ToChar()) + TEXT("\n") +
			   FString::Printf(TEXT("Event: %s"), *(Event.ToString())) + TEXT("\n") +
			   FString::Printf(TEXT("Value: %f"), Value) + TEXT("\n") +
			   FString::Printf(TEXT("Location: %s"), *(Location.ToCompactString())) + TEXT("\n") +
			   FString::Printf(TEXT("RepeatedState: %s"), EMCsPlaybackEventRepeatedState::Get().ToChar(RepeatedState));
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

	/** File holding any GameState information that needs to be apart of the Playback. */
	UPROPERTY()
	FString GameStateFile;

	/** The next file to process after this Playback finishes. There is more "time" instability
		when transitioning / loading between levels. For now, its best to story Playbacks on a 
		per level basis. */
	UPROPERTY()
	FString NextFile;

	FCsPlaybackByEvents() :
		Username(),
		Date(1, 1, 1, 0, 0, 0, 0),
		Level(),
		Events(),
		GameStateFile(),
		NextFile()
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
				Events.AddDefaulted();
				Events[I].DeltaTime = From.Events[I].DeltaTime;

				Events[I].Events.Reset(From.Events[I].Events.Num());

				for (const FCsPlaybackByEvent& Event : From.Events[I].Events)
				{
					Events[I].Events.Add(Event);
				}
			}
			return true;
		}
		return false;
	}

	bool ShouldCopyFrom(const FCsPlaybackByEvents& From) const
	{
		return Events.Num() < From.Events.Num();
	}

	void Reset()
	{
		Events.Reset(Events.Max());
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsPlayback::FLog::Warning) const;
};

#pragma endregion FCsPlaybackByEvents
