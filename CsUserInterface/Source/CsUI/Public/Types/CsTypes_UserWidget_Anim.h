// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_UserWidget_Anim.generated.h"
#pragma once

// UserWidgetAnimPlayMode
#pragma region

UENUM(BlueprintType)
enum class ECsUserWidgetAnimPlayMode : uint8
{
	Forward							UMETA(DisplayName = "Forward"),
	Reverse							UMETA(DisplayName = "Reverse"),
	PingPong						UMETA(DisplayName = "Ping Pong"),
	ECsUserWidgetAnimPlayMode_MAX	UMETA(Hidden),
};

namespace NCsUserWidget
{
	namespace NAnim
	{
		namespace NPlay
		{
			enum class EMode : uint8 
			{
				Forward,
				Reverse,
				PingPong,
				EMode_MAX
			};
		}
	}
}

#pragma endregion UserWidgetAnimPlayMode

// FCsUserWidgetAnimPlayParams
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidgetAnimPlayParams : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the Animation. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	/** The time in the animation from which to start playing, 
		relative to the start position. For looped animations, 
		this will only affect the first playback of the animation. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", ClampMin = "0"))
	float StartAtTime;

	/** The absolute time in the animation where to stop, 
		this is only considered in the last loop.
		0.0f to ignore EndAtTime. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", ClampMin = "0"))
	float EndAtTime;

	/** The number of times to loop this animation (0 to loop indefinitely) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0", ClampMin = "0"))
	int32 NumLoopsToPlay;

	/** Specifies the playback mode. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsUserWidgetAnimPlayMode PlayMode;

	/** The speed at which the animation should play. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", ClampMin = "0"))
	float PlaybackSpeed;

	FCsUserWidgetAnimPlayParams() :
		Name(NAME_None),
		StartAtTime(0.0f),
		EndAtTime(0.0f),
		NumLoopsToPlay(1),
		PlayMode(ECsUserWidgetAnimPlayMode::Forward),
		PlaybackSpeed(1.0f)
	{
	}

	bool IsValidChecked(const FString& Context) const;
};

namespace NCsUserWidget
{
	namespace NAnim
	{
		namespace NPlay
		{
			struct CSUI_API FParams
			{
			#define PlayModeType NCsUserWidget::NAnim::NPlay::EMode
			public:

				/** Name of the Animation. */
				FName Name;

				/** The time in the animation from which to start playing, 
					relative to the start position. For looped animations, 
					this will only affect the first playback of the animation. */
				float StartAtTime;

				/** The absolute time in the animation where to stop, 
					this is only considered in the last loop.
					0.0f to ignore EndAtTime. */
				float EndAtTime;

				/** The number of times to loop this animation (0 to loop indefinitely) */
				int32 NumLoopsToPlay;

				/** Specifies the playback mode. */
				PlayModeType PlayMode;

				/** The speed at which the animation should play. */
				float PlaybackSpeed;

				FParams() :
					Name(NAME_None),
					StartAtTime(0.0f),
					EndAtTime(0.0f),
					NumLoopsToPlay(1),
					PlayMode(PlayModeType::Forward),
					PlaybackSpeed(1.0f)
				{
				}

				bool IsValidChecked(const FString& Context) const;
				
			#undef PlayModeType
			};
		}
	}
}

#pragma endregion FCsUserWidgetAnimPlayParams