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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetPositionBySlot);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetAbsolutePositionByCachedGeometry);
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

FVector2D UCsScriptLibrary_Widget::GetPositionBySlot(const FString& Context, UUserWidget* Widget)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetPositionBySlot : Context;

	typedef NCsWidget::NPosition::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeBySlot(Context, Widget);
}

FVector2D UCsScriptLibrary_Widget::GetAbsolutePositionByCachedGeometry(const FString& Context, UUserWidget* Widget)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAbsolutePositionByCachedGeometry : Context;

	typedef NCsWidget::NPosition::FLibrary WidgetPositionLibrary;

	return WidgetPositionLibrary::GetSafeAbsoluteByCachedGeometry(Context, Widget);
}

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