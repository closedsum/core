// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
#include "CsMacro_Namespace.h"
#include "Types/CsTypes_Interpolation.h"
// DataTable
#include "Engine/DataTable.h"
// Log
#include "Utility/CsUICoreLog.h"

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

struct CSUICORE_API EMCsUserWidgetAnimPlayMode final : public TCsEnumMap<ECsUserWidgetAnimPlayMode>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsUserWidgetAnimPlayMode, ECsUserWidgetAnimPlayMode)
};

namespace NCsUserWidgetAnimPlayMode
{
	typedef ECsUserWidgetAnimPlayMode Type;

	namespace Ref
	{
		extern CSUICORE_API const Type Forward;
		extern CSUICORE_API const Type Reverse;
		extern CSUICORE_API const Type PingPong;
		extern CSUICORE_API const Type ECsUserWidgetAnimPlayMode_MAX;
	}

	extern CSUICORE_API const uint8 MAX;
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

			struct CSUICORE_API EMMode final : public TCsEnumMap<EMode>
			{
				CS_ENUM_MAP_BODY(EMMode, EMode)
			};

			namespace NMode
			{
				namespace Ref
				{
					typedef EMode Type;

					extern CSUICORE_API const Type Forward;
					extern CSUICORE_API const Type Reverse;
					extern CSUICORE_API const Type PingPong;
					extern CSUICORE_API const Type EMode_MAX;
				}
			}
		}
	}
}

#pragma endregion UserWidgetAnimPlayMode

// FCsUserWidgetAnimPlayParams (TODO: Deprecate Name)
#pragma region

// NCsUserWidget::NAnim::NPlay::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsUserWidget, NAnim, NPlay, FParams)

/**
*/
USTRUCT(BlueprintType)
struct CSUICORE_API FCsUserWidgetAnimPlayParams : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the Animation. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FName Name;

	/** The time in the animation from which to start playing, 
		relative to the start position. For looped animations, 
		this will only affect the first playback of the animation. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (UIMin = "0.0", ClampMin = "0"))
	float StartAtTime;

	/** The absolute time in the animation where to stop, 
		this is only considered in the last loop.
		0.0f to ignore EndAtTime. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (UIMin = "0.0", ClampMin = "0"))
	float EndAtTime;

	/** The number of times to loop this animation (0 to loop indefinitely) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (UIMin = "0", ClampMin = "0"))
	int32 NumLoopsToPlay;

	/** Specifies the playback mode. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	ECsUserWidgetAnimPlayMode PlayMode;

	/** The speed at which the animation should play. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (UIMin = "0.0", ClampMin = "0"))
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
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::NCore::FLog::Warning) const;
};

#pragma endregion FCsUserWidgetAnimPlayParams

// FCsUserWidget_Anim_PlayParams
#pragma region

// NCsUserWidget::NAnim::NPlay::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsUserWidget, NAnim, NPlay, FParams)

/**
*/
USTRUCT(BlueprintType)
struct CSUICORE_API FCsUserWidget_Anim_PlayParams : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	/** Name of the Animation. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FName Name;

	/** The time in the animation from which to start playing, 
		relative to the start position. For looped animations, 
		this will only affect the first playback of the animation. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (UIMin = "0.0", ClampMin = "0"))
	float StartAtTime;

	/** The absolute time in the animation where to stop, 
		this is only considered in the last loop.
		0.0f to ignore EndAtTime. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (UIMin = "0.0", ClampMin = "0"))
	float EndAtTime;

	/** The number of times to loop this animation (0 to loop indefinitely) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (UIMin = "0", ClampMin = "0"))
	int32 NumLoopsToPlay;

	/** Specifies the playback mode. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	ECsUserWidgetAnimPlayMode PlayMode;

	/** The speed at which the animation should play. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (UIMin = "0.0", ClampMin = "0"))
	float PlaybackSpeed;

	FCsUserWidget_Anim_PlayParams() :
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
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::NCore::FLog::Warning) const;
};

namespace NCsUserWidget
{
	namespace NAnim
	{
		namespace NPlay
		{
			struct CSUICORE_API FParams
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
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::NCore::FLog::Warning) const;
				
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

#pragma endregion FCsUserWidget_Anim_PlayParams

// FCsUserWidget_Render_Scale_Anim_OneShot_ByScalarParams
#pragma region

class UUserWidget;

// NCsUserWidget::NRender::NScale::NAnim::NOneShot::FByScalarParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsUserWidget, NRender, NScale, NAnim, NOneShot, FByScalarParams)

/**
*/
USTRUCT(BlueprintType)
struct CSUICORE_API FCsUserWidget_Render_Scale_Anim_OneShot_ByScalarParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|UserWidget")
	UUserWidget* Widget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|UserWidget")
	ECsEasingType Easing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|UserWidget", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|UserWidget")
	float Start;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|UserWidget")
	float End;
	
	FCsUserWidget_Render_Scale_Anim_OneShot_ByScalarParams() :
		Widget(nullptr),
		Easing(ECsEasingType::Linear),
		Duration(0.0f),
		Start(0.0f),
		End(0.0f)
	{
	}

#define ParamsType NCsUserWidget::NRender::NScale::NAnim::NOneShot::FByScalarParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::NCore::FLog::Warning) const;
};

namespace NCsUserWidget
{
	namespace NRender
	{
		namespace NScale
		{
			namespace NAnim
			{
				namespace NOneShot
				{
					struct CSUICORE_API FByScalarParams
					{
					private:

						CS_DECLARE_MEMBER_WITH_PROXY(Widget, UUserWidget*)
						CS_DECLARE_MEMBER_WITH_PROXY(Easing, ECsEasingType)
						CS_DECLARE_MEMBER_WITH_PROXY(Duration, float)
						CS_DECLARE_MEMBER_WITH_PROXY(Start, float)
						CS_DECLARE_MEMBER_WITH_PROXY(End, float)

					public:

						FByScalarParams() :
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Widget, nullptr),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Easing, ECsEasingType::Linear),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Duration, 0.0f),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Start, 0.0f),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(End, 0.0f)
						{
							CS_CTOR_SET_MEMBER_PROXY(Widget);
							CS_CTOR_SET_MEMBER_PROXY(Easing);
							CS_CTOR_SET_MEMBER_PROXY(Duration);
							CS_CTOR_SET_MEMBER_PROXY(Start);
							CS_CTOR_SET_MEMBER_PROXY(End);
						}

						CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Widget, UUserWidget)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Easing, ECsEasingType)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Duration, float)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Start, float)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(End, float)

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::NCore::FLog::Warning) const;
					};
				}
			}
		}
	}
}

#pragma endregion FCsUserWidget_Render_Scale_Anim_OneShot_ByScalarParams