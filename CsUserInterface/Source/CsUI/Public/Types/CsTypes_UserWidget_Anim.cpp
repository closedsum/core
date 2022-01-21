// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_UserWidget_Anim.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"

// FCsUserWidgetAnimPlayParams
#pragma region

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
	checkf(PlayMode != ECsUserWidgetAnimPlayMode::ECsUserWidgetAnimPlayMode_MAX, TEXT("%s: PlayMode: ECsUserWidgetAnimPlayMode_MAX is NOT Valid."), *Context);
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
	if (PlayMode == ECsUserWidgetAnimPlayMode::ECsUserWidgetAnimPlayMode_MAX)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: PlayMode: ECsUserWidgetAnimPlayMode_MAX is NOT Valid."), *Context));
		return false;
	}
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
				CS_IS_NAME_NONE_CHECKED(Name)
				// Check StartAtTime is Valid
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(StartAtTime, 0.0f)
				// Check EndAtTime is Valid
				checkf(EndAtTime >= 0.0f && EndAtTime <= StartAtTime, TEXT("%s: EndAtTime: %f is NOT >= 0.0f and <= %f (StartAtTime)."), *Context, EndAtTime, StartAtTime);
				// Check NumLoopsToPlay is Valid
				CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(NumLoopsToPlay, 0)
				// Check PlayMode is Valid
				typedef NCsUserWidget::NAnim::NPlay::EMode PlaydModeType;

				checkf(PlayMode != PlaydModeType::EMode_MAX, TEXT("%s: PlayMode: EMode_MAX is NOT Valid."), *Context);
				// Check PlaybackSpeed is Valid
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(PlaybackSpeed, 0.0f)
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
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
			typedef NCsUserWidget::NAnim::NPlay::EMode PlaydModeType;

			if (PlayMode == PlaydModeType::EMode_MAX)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: PlayMode: EMode_MAX is NOT Valid."), *Context));
				return false;
			}
			// Check PlaybackSpeed is Valid
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(PlaybackSpeed, 0.0f)
			return true;
			}
		}
	}
}

#pragma endregion FCsUserWidgetAnimPlayParams