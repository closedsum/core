// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Widget.h"
#include "CsUI.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
#include "Library/CsLibrary_Property.h"
// Widget
#include "Blueprint/UserWidget.h"
// Components
#include "Components/CanvasPanelSlot.h"

namespace NCsWidget
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::FLibrary, GetSafePositionBySlot);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::FLibrary, GetSafeAnimation);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::FLibrary, SafePlayAnimation);
			}
		}
	}

	// Position
	#pragma region

	FVector2D FLibrary::GetPositionBySlotChecked(const FString& Context, UUserWidget* Widget)
	{
		CS_IS_PTR_NULL_CHECKED(Widget)

		checkf(Widget->Slot, TEXT("%s: Widget: %s's Slot is NULL."), *Context, *(Widget->GetName()));

		UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(Widget->Slot);

		checkf(Slot, TEXT("%s: Widget: %s's Slot is NOT of type: UCavnasPanelSlot."), *Context, *(Widget->GetName()));

		return Slot->GetPosition();
	}

	FVector2D FLibrary::GetSafePositionBySlot(const FString& Context, UUserWidget* Widget, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
	{
		if (!Widget)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Widget is NULL."), *Context));
			return FVector2D(-1.0f);
		}

		if (!Widget->Slot)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Widget: %s's Slot is NULL."), *Context, *(Widget->GetName())));
			return FVector2D(-1.0f);
		}

		UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(Widget->Slot);

		if (!Slot)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Widget: %s's Slot is NOT of type: UCavnasPanelSlot."), *Context, *(Widget->GetName())));
			return FVector2D(-1.0f);
		}
		return Slot->GetPosition();
	}

	FVector2D FLibrary::GetSafePositionBySlot(UUserWidget* Widget)
	{
		using namespace NCsWidget::NLibrary::NCached;

		const FString& Context = Str::GetSafePositionBySlot;

		return GetSafePositionBySlot(Context, Widget, nullptr);
	}

	FVector2D FLibrary::GetAbsolutePositionByCachedGeometryChecked(const FString& Context, UUserWidget* Widget)
	{
		CS_IS_PTR_NULL_CHECKED(Widget)

		return Widget->GetCachedGeometry().GetAbsolutePosition();
	}

	#pragma endregion Position

	// Animation
	#pragma region

	UWidgetAnimation* FLibrary::GetAnimationChecked(const FString& Context, UUserWidget* Widget, const FName& AnimName)
	{
		CS_IS_PTR_NULL_CHECKED(Widget)

		typedef NCsProperty::FLibrary PropertyLibrary;

		return PropertyLibrary::GetObjectPropertyValueChecked<UWidgetAnimation>(Context, Widget, Widget->GetClass(), AnimName);
	}

	UWidgetAnimation* FLibrary::GetSafeAnimation(const FString& Context, UUserWidget* Widget, const FName& AnimName, void(*Log)(const FString&) /*=&NCsUI::FLog; :Warning*/)
	{
		CS_IS_PTR_NULL_RET_NULL(Widget)

		typedef NCsProperty::FLibrary PropertyLibrary;

		return PropertyLibrary::GetObjectPropertyValue<UWidgetAnimation>(Context, Widget, Widget->GetClass(), AnimName, Log);
	}

	UWidgetAnimation* FLibrary::GetSafeAnimation(UUserWidget* Widget, const FName& AnimName)
	{
		using namespace NCsWidget::NLibrary::NCached;

		const FString& Context = Str::GetSafeAnimation;

		return GetSafeAnimation(Context, Widget, AnimName, nullptr);
	}

	#define ParamsType NCsUserWidget::NAnim::NPlay::FParams

	void FLibrary::PlayAnimationChecked(const FString& Context, UUserWidget* Widget, const ParamsType& Params)
	{
		CS_IS_PTR_NULL_CHECKED(Widget)

		check(Params.IsValidChecked(Context));

		typedef NCsProperty::FLibrary PropertyLibrary;

		UWidgetAnimation* Animation = PropertyLibrary::GetObjectPropertyValueChecked<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.Name);

		if (Params.EndAtTime > 0.0f)
			Widget->PlayAnimationTimeRange(Animation, Params.StartAtTime, Params.EndAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
		else
			Widget->PlayAnimation(Animation, Params.StartAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
	}

	void FLibrary::SafePlayAnimation(const FString& Context, UUserWidget* Widget, const ParamsType& Params, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
	{
		CS_IS_PTR_NULL_EXIT(Widget)

		if (!Params.IsValid(Context, Log))
			return;

		typedef NCsProperty::FLibrary PropertyLibrary;

		UWidgetAnimation* Animation = PropertyLibrary::GetObjectPropertyValue<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.Name, Log);

		if (!Animation)
			return;

		if (Params.EndAtTime > 0.0f)
			Widget->PlayAnimationTimeRange(Animation, Params.StartAtTime, Params.EndAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
		else
			Widget->PlayAnimation(Animation, Params.StartAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
	}

	void FLibrary::SafePlayAnimation(UUserWidget* Widget, const ParamsType& Params)
	{
		using namespace NCsWidget::NLibrary::NCached;

		const FString& Context = Str::SafePlayAnimation;

		return SafePlayAnimation(Context, Widget, Params, nullptr);
	}

	#undef ParamsType

	void FLibrary::PlayAnimationChecked(const FString& Context, UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params)
	{
		CS_IS_PTR_NULL_CHECKED(Widget)

		check(Params.IsValidChecked(Context));

		typedef NCsProperty::FLibrary PropertyLibrary;

		UWidgetAnimation* Animation = PropertyLibrary::GetObjectPropertyValueChecked<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.Name);

		if (Params.EndAtTime > 0.0f)
			Widget->PlayAnimationTimeRange(Animation, Params.StartAtTime, Params.EndAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
		else
			Widget->PlayAnimation(Animation, Params.StartAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
	}

	void FLibrary::SafePlayAnimation(const FString& Context, UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
	{
		CS_IS_PTR_NULL_EXIT(Widget)

		if (!Params.IsValid(Context, Log))
			return;

		typedef NCsProperty::FLibrary PropertyLibrary;

		UWidgetAnimation* Animation = PropertyLibrary::GetObjectPropertyValue<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.Name, Log);

		if (!Animation)
			return;

		if (Params.EndAtTime > 0.0f)
			Widget->PlayAnimationTimeRange(Animation, Params.StartAtTime, Params.EndAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
		else
			Widget->PlayAnimation(Animation, Params.StartAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
	}

	void FLibrary::SafePlayAnimation(UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params)
	{
		using namespace NCsWidget::NLibrary::NCached;

		const FString& Context = Str::SafePlayAnimation;

		return SafePlayAnimation(Context, Widget, Params, nullptr);
	}

	#pragma endregion Animation
}