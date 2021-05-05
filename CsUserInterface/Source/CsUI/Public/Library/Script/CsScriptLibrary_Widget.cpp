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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetScreenPositionBySlot);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetAbsoluteScreenPositionByCachedGeometry);
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

// Position
#pragma region

	// Screen
#pragma region

FVector2D UCsScriptLibrary_Widget::GetScreenPositionBySlot(const FString& Context, UUserWidget* Widget)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetScreenPositionBySlot : Context;

	typedef NCsWidget::NPosition::NScreen::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeBySlot(Context, Widget);
}

FVector2D UCsScriptLibrary_Widget::GetAbsoluteScreenPositionByCachedGeometry(const FString& Context, UUserWidget* Widget)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAbsoluteScreenPositionByCachedGeometry : Context;

	typedef NCsWidget::NPosition::NScreen::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeAbsoluteByCachedGeometry(Context, Widget);
}

#pragma endregion Screen

	// World
#pragma region

bool UCsScriptLibrary_Widget::GetWorldPositionBySlot(const FString& Context, UObject* WorldContextObject, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetWorldPositionBySlot : Context;

	typedef NCsWidget::NPosition::NWorld::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeBySlot(Context, WorldContextObject, ControllerId, Widget, OutPosition, OutDirection);
}

bool UCsScriptLibrary_Widget::GetWorldPositionByCachedGeometry(const FString& Context, UObject* WorldContextObject, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetWorldPositionByCachedGeometry : Context;

	typedef NCsWidget::NPosition::NWorld::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeByCachedGeometry(Context, WorldContextObject, ControllerId, Widget, OutPosition, OutDirection);
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

	return WidgetAnimationLibrary::GetSafe(Context, Widget, AnimName);
}

#pragma endregion Animation