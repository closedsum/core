// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_UserWidget_Anim.h"

// Library
#include "Library/CsLibrary_Valid.h"


// UserWidgetAnimPlayMode
#pragma region

namespace NCsUserWidgetAnimPlayMode
{
	namespace Ref
	{
		typedef EMCsUserWidgetAnimPlayMode EnumMapType;

		CSUI_API CS_ADD_TO_ENUM_MAP(Forward);
		CSUI_API CS_ADD_TO_ENUM_MAP(Reverse);
		CSUI_API CS_ADD_TO_ENUM_MAP(PingPong);
		CSUI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsUserWidgetAnimPlayMode_MAX, "MAX");
	}

	CSUI_API const uint8 MAX = (uint8)Type::ECsUserWidgetAnimPlayMode_MAX;
}

namespace NCsUserWidget
{
	namespace NAnim
	{
		namespace NPlay
		{
			namespace NMode
			{
				namespace Ref
				{
					typedef EMMode EnumMapType;

					CSUI_API CS_ADD_TO_ENUM_MAP(Forward);
					CSUI_API CS_ADD_TO_ENUM_MAP(Reverse);
					CSUI_API CS_ADD_TO_ENUM_MAP(PingPong);
					CSUI_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMode_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion FXDeallocateMethod

// FCsUserWidgetAnimPlayParams (TODO: Deprecate Name)
#pragma region

#define ParamsType NCsUserWidget::NAnim::NPlay::FParams

void FCsUserWidgetAnimPlayParams::CopyToParams(ParamsType* Params)
{
	Params->SetName(&Name);
	Params->SetStartAtTime(&StartAtTime);
	Params->SetEndAtTime(&EndAtTime);
	Params->SetNumLoopsToPlay(&NumLoopsToPlay);

	typedef NCsUserWidget::NAnim::NPlay::EMode PlayModeType;

	Params->SetPlayMode((PlayModeType*)(&PlayMode));
	Params->SetPlaybackSpeed(&PlaybackSpeed);
}

void FCsUserWidgetAnimPlayParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetName(Name);
	Params->SetStartAtTime(StartAtTime);
	Params->SetEndAtTime(EndAtTime);
	Params->SetNumLoopsToPlay(NumLoopsToPlay);

	typedef NCsUserWidget::NAnim::NPlay::EMode PlayModeType;

	Params->SetPlayMode((PlayModeType)PlayMode);
	Params->SetPlaybackSpeed(PlaybackSpeed);
}

#undef ParamsType

bool FCsUserWidgetAnimPlayParams::IsValidChecked(const FString& Context) const
{
	// Check Name is Valid
	CS_IS_NAME_NONE_CHECKED(Name)
	// Check StartAtTime is Valid
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(StartAtTime, 0.0f)
	// Check EndAtTime is Valid
	checkf(EndAtTime >= 0.0f && EndAtTime <= StartAtTime, TEXT("%s: EndAtTime: %f is NOT >= 0.0f and <= %f (StartAtTime)."), *Context, EndAtTime, StartAtTime);
	// Check NumLoopsToPlay is Valid
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(NumLoopsToPlay, 0)
	// Check PlayMode is Valid
	CS_IS_ENUM_VALID_CHECKED(EMCsUserWidgetAnimPlayMode, PlayMode)
	// Check PlaybackSpeed is Valid
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(PlaybackSpeed, 0.0f)
	return true;
}

bool FCsUserWidgetAnimPlayParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	// Check Name is Valid
	CS_IS_NAME_NONE(Name)
	// Check StartAtTime is Valid
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(StartAtTime, 0.0f)
	// Check EndAtTime is Valid
	if (EndAtTime < 0.0f || EndAtTime > StartAtTime)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: EndAtTime: %f is NOT >= 0.0f and <= %f (StartAtTime)."), *Context, EndAtTime, StartAtTime));
		return false;
	}
	// Check NumLoopsToPlay is Valid
	CS_IS_INT_GREATER_THAN_OR_EQUAL(NumLoopsToPlay, 0)
	// Check PlayMode is Valid
	CS_IS_ENUM_VALID(EMCsUserWidgetAnimPlayMode, ECsUserWidgetAnimPlayMode, PlayMode)
	// Check PlaybackSpeed is Valid
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(PlaybackSpeed, 0.0f)
	return true;
}

#pragma endregion FCsUserWidgetAnimPlayParams

// FCsUserWidget_Anim_PlayParams
#pragma region

#define ParamsType NCsUserWidget::NAnim::NPlay::FParams

void FCsUserWidget_Anim_PlayParams::CopyToParams(ParamsType* Params)
{
	Params->SetName(&Name);
	Params->SetStartAtTime(&StartAtTime);
	Params->SetEndAtTime(&EndAtTime);
	Params->SetNumLoopsToPlay(&NumLoopsToPlay);

	typedef NCsUserWidget::NAnim::NPlay::EMode PlayModeType;

	Params->SetPlayMode((PlayModeType*)(&PlayMode));
	Params->SetPlaybackSpeed(&PlaybackSpeed);
}

void FCsUserWidget_Anim_PlayParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetName(Name);
	Params->SetStartAtTime(StartAtTime);
	Params->SetEndAtTime(EndAtTime);
	Params->SetNumLoopsToPlay(NumLoopsToPlay);

	typedef NCsUserWidget::NAnim::NPlay::EMode PlayModeType;

	Params->SetPlayMode((PlayModeType)PlayMode);
	Params->SetPlaybackSpeed(PlaybackSpeed);
}

#undef ParamsType

bool FCsUserWidget_Anim_PlayParams::IsValidChecked(const FString& Context) const
{
	// Check Name is Valid
	CS_IS_NAME_NONE_CHECKED(Name)
	// Check StartAtTime is Valid
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(StartAtTime, 0.0f)
	// Check EndAtTime is Valid
	checkf(EndAtTime >= 0.0f && EndAtTime <= StartAtTime, TEXT("%s: EndAtTime: %f is NOT >= 0.0f and <= %f (StartAtTime)."), *Context, EndAtTime, StartAtTime);
	// Check NumLoopsToPlay is Valid
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(NumLoopsToPlay, 0)
	// Check PlayMode is Valid
	CS_IS_ENUM_VALID_CHECKED(EMCsUserWidgetAnimPlayMode, PlayMode)
	// Check PlaybackSpeed is Valid
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(PlaybackSpeed, 0.0f)
	return true;
}

bool FCsUserWidget_Anim_PlayParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	// Check Name is Valid
	CS_IS_NAME_NONE(Name)
	// Check StartAtTime is Valid
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(StartAtTime, 0.0f)
	// Check EndAtTime is Valid
	if (EndAtTime < 0.0f || EndAtTime > StartAtTime)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: EndAtTime: %f is NOT >= 0.0f and <= %f (StartAtTime)."), *Context, EndAtTime, StartAtTime));
		return false;
	}
	// Check NumLoopsToPlay is Valid
	CS_IS_INT_GREATER_THAN_OR_EQUAL(NumLoopsToPlay, 0)
	// Check PlayMode is Valid
	CS_IS_ENUM_VALID(EMCsUserWidgetAnimPlayMode, ECsUserWidgetAnimPlayMode, PlayMode)
	// Check PlaybackSpeed is Valid
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(PlaybackSpeed, 0.0f)
	return true;
}

namespace NCsUserWidget
{
	namespace NAnim
	{
		namespace NPlay
		{
			bool FParams::IsValidChecked(const FString& Context) const
			{
				CS_IS_NAME_NONE_CHECKED(GetName())
				// Check StartAtTime is Valid
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetStartAtTime(), 0.0f)
				// Check EndAtTime is Valid
				checkf(GetEndAtTime() >= 0.0f && GetEndAtTime() <= GetStartAtTime(), TEXT("%s: GetEndAtTime(): %f is NOT >= 0.0f and <= %f (GetStartAtTime())."), *Context, GetEndAtTime(), GetStartAtTime());
				// Check NumLoopsToPlay is Valid
				CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetNumLoopsToPlay(), 0)
				// Check PlayMode is Valid
				typedef NCsUserWidget::NAnim::NPlay::EMMode PlayModeMapType;
				typedef NCsUserWidget::NAnim::NPlay::EMode PlayModeType;

				CS_IS_ENUM_VALID_CHECKED(PlayModeMapType, GetPlayMode())
				// Check PlaybackSpeed is Valid
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetPlaybackSpeed(), 0.0f)
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
			{
			// Check Name is Valid
			CS_IS_NAME_NONE(GetName())
			// Check StartAtTime is Valid
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetStartAtTime(), 0.0f)
			// Check EndAtTime is Valid
			if (GetEndAtTime() < 0.0f || GetEndAtTime() > GetStartAtTime())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetEndAtTime(): %f is NOT >= 0.0f and <= %f (GetStartAtTime())."), *Context, GetEndAtTime(), GetStartAtTime()));
				return false;
			}
			// Check NumLoopsToPlay is Valid
			CS_IS_INT_GREATER_THAN_OR_EQUAL(GetNumLoopsToPlay(), 0)
			// Check PlayMode is Valid
			typedef NCsUserWidget::NAnim::NPlay::EMMode PlayModeMapType;
			typedef NCsUserWidget::NAnim::NPlay::EMode PlayModeType;

			CS_IS_ENUM_VALID(PlayModeMapType, PlayModeType, GetPlayMode())
			// Check PlaybackSpeed is Valid
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetPlaybackSpeed(), 0.0f)
			return true;
			}
		}
	}
}

#pragma endregion FCsUserWidget_Anim_PlayParams

// FCsUserWidget_Render_Scale_Anim_OneShot_ByScalarParams
#pragma region

#define ParamsType NCsUserWidget::NRender::NScale::NAnim::NOneShot::FByScalarParams

void FCsUserWidget_Render_Scale_Anim_OneShot_ByScalarParams::CopyToParams(ParamsType* Params)
{
	Params->SetWidget(&Widget);
	Params->SetEasing(&Easing);
	Params->SetDuration(&Duration);
	Params->SetStart(&Start);
	Params->SetEnd(&End);
}

void FCsUserWidget_Render_Scale_Anim_OneShot_ByScalarParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetWidget(Widget);
	Params->SetEasing(Easing);
	Params->SetDuration(Duration);
	Params->SetStart(Start);
	Params->SetEnd(End);
}

#undef ParamsType

bool FCsUserWidget_Render_Scale_Anim_OneShot_ByScalarParams::IsValidChecked(const FString& Context) const
{
	CS_IS_PTR_NULL_CHECKED(Widget)
	CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, Easing)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Duration, 0.0f)
	return true;
}

bool FCsUserWidget_Render_Scale_Anim_OneShot_ByScalarParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_PTR_NULL(Widget)
	CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, Easing)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Duration, 0.0f)
	return true;
}

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
					bool FByScalarParams::IsValidChecked(const FString& Context) const
					{
						CS_IS_PTR_NULL_CHECKED(GetWidget())
						CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, GetEasing())
						CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetDuration(), 0.0f)
						return true;
					}

					bool FByScalarParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
					{
						CS_IS_PTR_NULL(GetWidget())
						CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, GetEasing())
						CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetDuration(), 0.0f)
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsUserWidget_Render_Scale_Anim_OneShot_ByScalarParams