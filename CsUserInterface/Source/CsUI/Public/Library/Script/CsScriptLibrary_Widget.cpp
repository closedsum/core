// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Script/CsScriptLibrary_Widget.h"
#include "CsUI.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Widget.h"

// Cached
#pragma region

namespace NCsScriptLibraryWidget
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, Create);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, LoadByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetScreenPositionBySlot);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetAbsoluteScreenPositionByCachedGeometry);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetPixelAndViewportPositionByCachedGeometry);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetWorldPositionBySlot);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetWorldPositionByCachedGeometry);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetAnimation);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetTextBlock);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetButton);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetImage);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetProgressBar);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetBorder);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Widget::UCsScriptLibrary_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UUserWidget* UCsScriptLibrary_Widget::Create(const FString& Context, UObject* Owner, TSubclassOf<UUserWidget> UserWidgetClass, const FName& WidgetName)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Create : Context;

	typedef NCsWidget::FLibrary WidgetLibrary;

	return WidgetLibrary::CreateSafe(Context, Owner, UserWidgetClass, WidgetName);
}

// Load
#pragma region

UClass* UCsScriptLibrary_Widget::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	typedef NCsWidget::FLibrary WidgetLibrary;

	return WidgetLibrary::SafeLoad(Ctxt, Path);
}

UClass* UCsScriptLibrary_Widget::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	typedef NCsWidget::FLibrary WidgetLibrary;

	return WidgetLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

// Position
#pragma region

	// Screen
#pragma region

FVector2D UCsScriptLibrary_Widget::GetScreenPositionBySlot(const FString& Context, UWidget* Widget)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetScreenPositionBySlot : Context;

	typedef NCsWidget::NPosition::NScreen::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeBySlot(Ctxt, Widget);
}

FVector2D UCsScriptLibrary_Widget::GetAbsoluteScreenPositionByCachedGeometry(const FString& Context, UWidget* Widget)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAbsoluteScreenPositionByCachedGeometry : Context;

	typedef NCsWidget::NPosition::NScreen::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeAbsoluteByCachedGeometry(Ctxt, Widget);
}

#pragma endregion Screen

// Viewport
#pragma region

void UCsScriptLibrary_Widget::GetPixelAndViewportPositionByCachedGeometry(const FString& Context, UWidget* Widget, FVector2D& OutPixelPosition, FVector2D& OutViewportPosition)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetPixelAndViewportPositionByCachedGeometry : Context;

	typedef NCsWidget::NPosition::NViewport::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeByCachedGeometry(Ctxt, Widget, OutPixelPosition, OutViewportPosition);
}

#pragma endregion Viewport

	// World
#pragma region

bool UCsScriptLibrary_Widget::GetWorldPositionBySlot(const FString& Context, UObject* WorldContextObject, const int32& ControllerId, UWidget* Widget, FVector& OutPosition, FVector& OutDirection)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetWorldPositionBySlot : Context;

	typedef NCsWidget::NPosition::NWorld::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeBySlot(Ctxt, WorldContextObject, ControllerId, Widget, OutPosition, OutDirection);
}

bool UCsScriptLibrary_Widget::GetWorldPositionByCachedGeometry(const FString& Context, UObject* WorldContextObject, const int32& ControllerId, UWidget* Widget, FVector& OutPosition, FVector& OutDirection)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetWorldPositionByCachedGeometry : Context;

	typedef NCsWidget::NPosition::NWorld::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeByCachedGeometry(Ctxt, WorldContextObject, ControllerId, Widget, OutPosition, OutDirection);
}

#pragma endregion World

#pragma endregion Position

// Animation
#pragma region

UWidgetAnimation* UCsScriptLibrary_Widget::GetAnimation(const FString& Context, UUserWidget* Widget, const FName& AnimName)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAnimation : Context;

	typedef NCsWidget::NAnimation::FLibrary WidgetAnimationLibrary;

	return WidgetAnimationLibrary::GetSafe(Ctxt, Widget, AnimName);
}

#pragma endregion Animation

// TextBlock
#pragma region

UTextBlock* UCsScriptLibrary_Widget::GetTextBlock(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetTextBlock : Context;

	typedef NCsWidget::NTextBlock::FLibrary WidgetTextBlockLibrary;

	return WidgetTextBlockLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#pragma endregion TextBlock

// Button
#pragma region

UButton* UCsScriptLibrary_Widget::GetButton(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetButton : Context;

	typedef NCsWidget::NButton::FLibrary WidgetButtonLibrary;

	return WidgetButtonLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#pragma endregion Button

// Image
#pragma region

UImage* UCsScriptLibrary_Widget::GetImage(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetImage : Context;

	typedef NCsWidget::NImage::FLibrary WidgetImageLibrary;

	return WidgetImageLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#pragma endregion Image

// ProgressBar
#pragma region

UProgressBar* UCsScriptLibrary_Widget::GetProgressBar(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetProgressBar : Context;

	typedef NCsWidget::NProgressBar::FLibrary WidgetProgressBarLibrary;

	return WidgetProgressBarLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#pragma endregion ProgressBar

// Border
#pragma region

UBorder* UCsScriptLibrary_Widget::GetBorder(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetBorder : Context;

	typedef NCsWidget::NBorder::FLibrary WidgetBorderLibrary;

	return WidgetBorderLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#pragma endregion Border