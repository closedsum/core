// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_UserWidget_Anim.h"

// FCsUserWidgetAnimPlayParams
#pragma region

bool FCsUserWidgetAnimPlayParams::IsValidChecked(const FString& Context) const
{
	// Check Name is Valid
	checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);
	// Check StartAtTime is Valid
	checkf(StartAtTime >= 0.0f, TEXT("%s: StartAtTime: %f is NOT >= 0.0f"), *Context, StartAtTime);
	// Check EndAtTime is Valid
	checkf(EndAtTime >= 0.0f && EndAtTime <= StartAtTime, TEXT("%s: EndAtTime: %f is NOT >= 0.0f and <= %f (StartAtTime)."), *Context, EndAtTime, StartAtTime);
	// Check NumLoopsToPlay is Valid
	checkf(NumLoopsToPlay >= 0, TEXT("%s: NumLoopsToPlay: %d is NOT >= 0."), *Context, NumLoopsToPlay);
	// Check PlayMode is Valid
	checkf(PlayMode != ECsUserWidgetAnimPlayMode::ECsUserWidgetAnimPlayMode_MAX, TEXT("%s: PlayMode: ECsUserWidgetAnimPlayMode_MAX is NOT Valid."), *Context);
	// Check PlaybackSpeed is Valid
	checkf(PlaybackSpeed >= 0.0f, TEXT("%s: PlaybackSpeed: %f is NOT >= 0.0f."), *Context, PlaybackSpeed);
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
				// Check Name is Valid
				checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);
				// Check StartAtTime is Valid
				checkf(StartAtTime >= 0.0f, TEXT("%s: StartAtTime: %f is NOT >= 0.0f"), *Context, StartAtTime);
				// Check EndAtTime is Valid
				checkf(EndAtTime >= 0.0f && EndAtTime <= StartAtTime, TEXT("%s: EndAtTime: %f is NOT >= 0.0f and <= %f (StartAtTime)."), *Context, EndAtTime, StartAtTime);
				// Check NumLoopsToPlay is Valid
				checkf(NumLoopsToPlay >= 0, TEXT("%s: NumLoopsToPlay: %d is NOT >= 0."), *Context, NumLoopsToPlay);
				// Check PlayMode is Valid
				typedef NCsUserWidget::NAnim::NPlay::EMode PlaydModeType;

				checkf(PlayMode != PlaydModeType::EMode_MAX, TEXT("%s: PlayMode: EMode_MAX is NOT Valid."), *Context);
				// Check PlaybackSpeed is Valid
				checkf(PlaybackSpeed >= 0.0f, TEXT("%s: PlaybackSpeed: %f is NOT >= 0.0f."), *Context, PlaybackSpeed);
				return true;
			}
		}
	}
}

#pragma endregion FCsUserWidgetAnimPlayParams