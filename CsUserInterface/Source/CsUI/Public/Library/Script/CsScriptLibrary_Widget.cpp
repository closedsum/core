// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetScreenPositionBySlot);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetAbsoluteScreenPositionByCachedGeometry);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetPixelAndViewportPositionByCachedGeometry);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetWorldPositionBySlot);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetWorldPositionByCachedGeometry);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetAnimation);
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

// Position
#pragma region

	// Screen
#pragma region

FVector2D UCsScriptLibrary_Widget::GetScreenPositionBySlot(const FString& Context, UUserWidget* Widget)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetScreenPositionBySlot : Context;

	typedef NCsWidget::NPosition::NScreen::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeBySlot(Ctxt, Widget);
}

FVector2D UCsScriptLibrary_Widget::GetAbsoluteScreenPositionByCachedGeometry(const FString& Context, UUserWidget* Widget)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAbsoluteScreenPositionByCachedGeometry : Context;

	typedef NCsWidget::NPosition::NScreen::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeAbsoluteByCachedGeometry(Ctxt, Widget);
}

#pragma endregion Screen

// Viewport
#pragma region

void UCsScriptLibrary_Widget::GetPixelAndViewportPositionByCachedGeometry(const FString& Context, UUserWidget* Widget, FVector2D& OutPixelPosition, FVector2D& OutViewportPosition)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetPixelAndViewportPositionByCachedGeometry : Context;

	typedef NCsWidget::NPosition::NViewport::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeByCachedGeometry(Ctxt, Widget, OutPixelPosition, OutViewportPosition);
}

#pragma endregion Viewport

	// World
#pragma region

bool UCsScriptLibrary_Widget::GetWorldPositionBySlot(const FString& Context, UObject* WorldContextObject, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetWorldPositionBySlot : Context;

	typedef NCsWidget::NPosition::NWorld::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeBySlot(Ctxt, WorldContextObject, ControllerId, Widget, OutPosition, OutDirection);
}

bool UCsScriptLibrary_Widget::GetWorldPositionByCachedGeometry(const FString& Context, UObject* WorldContextObject, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection)
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