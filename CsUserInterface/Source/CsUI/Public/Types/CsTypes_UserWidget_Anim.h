// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"
// DataTable
#include "Engine/DataTable.h"
// Log
#include "Utility/CsUILog.h"

#include "CsTypes_UserWidget_Anim.generated.h"

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

struct CSUI_API EMCsUserWidgetAnimPlayMode final : public TCsEnumMap<ECsUserWidgetAnimPlayMode>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsUserWidgetAnimPlayMode, ECsUserWidgetAnimPlayMode)
};

namespace NCsUserWidgetAnimPlayMode
{
	typedef ECsUserWidgetAnimPlayMode Type;

	namespace Ref
	{
		extern CSUI_API const Type Forward;
		extern CSUI_API const Type Reverse;
		extern CSUI_API const Type PingPong;
		extern CSUI_API const Type ECsUserWidgetAnimPlayMode_MAX;
	}

	extern CSUI_API const uint8 MAX;
}

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

			struct CSUI_API EMMode final : public TCsEnumMap<EMode>
			{
				CS_ENUM_MAP_BODY(EMMode, EMode)
			};

			namespace NMode
			{
				namespace Ref
				{
					typedef EMode Type;

					extern CSUI_API const Type Forward;
					extern CSUI_API const Type Reverse;
					extern CSUI_API const Type PingPong;
					extern CSUI_API const Type EMode_MAX;
				}
			}
		}
	}
}

#pragma endregion UserWidgetAnimPlayMode

// FCsUserWidgetAnimPlayParams
#pragma region

// NCsUserWidget::NAnim::NPlay::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsUserWidget, NAnim, NPlay, FParams)

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

#define ParamsType NCsUserWidget::NAnim::NPlay::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
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

			private:

				/** Name of the Animation. */
				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)

				/** The time in the animation from which to start playing, 
					relative to the start position. For looped animations, 
					this will only affect the first playback of the animation. */
				CS_DECLARE_MEMBER_WITH_PROXY(StartAtTime, float)

				/** The absolute time in the animation where to stop, 
					this is only considered in the last loop.
					0.0f to ignore EndAtTime. */
				CS_DECLARE_MEMBER_WITH_PROXY(EndAtTime, float)

				/** The number of times to loop this animation (0 to loop indefinitely) */
				CS_DECLARE_MEMBER_WITH_PROXY(NumLoopsToPlay, int32)

				/** Specifies the playback mode. */
				CS_DECLARE_MEMBER_WITH_PROXY(PlayMode, PlayModeType)

				/** The speed at which the animation should play. */
				CS_DECLARE_MEMBER_WITH_PROXY(PlaybackSpeed, float)

			public:

				FParams() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(StartAtTime, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(EndAtTime, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(NumLoopsToPlay, 1),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(PlayMode, PlayModeType::Forward),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(PlaybackSpeed, 1.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(Name);
					CS_CTOR_SET_MEMBER_PROXY(StartAtTime);
					CS_CTOR_SET_MEMBER_PROXY(EndAtTime);
					CS_CTOR_SET_MEMBER_PROXY(NumLoopsToPlay);
					CS_CTOR_SET_MEMBER_PROXY(PlayMode);
					CS_CTOR_SET_MEMBER_PROXY(PlaybackSpeed);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Name, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(StartAtTime, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(EndAtTime, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(NumLoopsToPlay, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(PlayMode, PlayModeType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(PlaybackSpeed, float)

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
				
				void Copy(const FParams& From)
				{
					SetName(From.GetName());
					SetStartAtTime(From.GetStartAtTime());
					SetEndAtTime(From.GetEndAtTime());
					SetNumLoopsToPlay(From.GetNumLoopsToPlay());
					SetPlayMode(From.GetPlayMode());
					SetPlaybackSpeed(From.GetPlaybackSpeed());
				}

				FORCEINLINE void Reset()
				{
					CS_RESET_MEMBER_WITH_PROXY(Name, NAME_None)
					CS_RESET_MEMBER_WITH_PROXY(StartAtTime, 0.0f)
					CS_RESET_MEMBER_WITH_PROXY(EndAtTime, 0.0f)
					CS_RESET_MEMBER_WITH_PROXY(NumLoopsToPlay, 1)
					CS_RESET_MEMBER_WITH_PROXY(PlayMode, PlayModeType::Forward)
					CS_RESET_MEMBER_WITH_PROXY(PlaybackSpeed, 1.0f)
				}

			#undef PlayModeType
			};
		}
	}
}

#pragma endregion FCsUserWidgetAnimPlayParams