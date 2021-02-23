// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Widget.h"
#include "CsUI.h"

// Library
#include "Library/CsLibrary_Property.h"
// Widget
#include "Blueprint/UserWidget.h"

namespace NCsWidget
{
	#define ParamsType NCsUserWidget::NAnim::NPlay::FParams
	void FLibrary::PlayAnimationChecked(const FString& Context, UUserWidget* Widget, const ParamsType& Params)
	{
	#undef ParamsType

		checkf(Widget, TEXT("%s: Widget is NULL."), *Context);

		check(Params.IsValidChecked(Context));

		typedef NCsProperty::FLibrary PropertyLibrary;

		UWidgetAnimation* Animation = PropertyLibrary::GetObjectPropertyValueChecked<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.Name);

		if (Params.EndAtTime > 0.0f)
			Widget->PlayAnimationTimeRange(Animation, Params.StartAtTime, Params.EndAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
		else
			Widget->PlayAnimation(Animation, Params.StartAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
	}

	void FLibrary::PlayAnimationChecked(const FString& Context, UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params)
	{
		checkf(Widget, TEXT("%s: Widget is NULL."), *Context);

		check(Params.IsValidChecked(Context));

		typedef NCsProperty::FLibrary PropertyLibrary;

		UWidgetAnimation* Animation = PropertyLibrary::GetObjectPropertyValueChecked<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.Name);

		if (Params.EndAtTime > 0.0f)
			Widget->PlayAnimationTimeRange(Animation, Params.StartAtTime, Params.EndAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
		else
			Widget->PlayAnimation(Animation, Params.StartAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
	}
}