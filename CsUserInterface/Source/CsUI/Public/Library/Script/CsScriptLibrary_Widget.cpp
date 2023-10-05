// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Widget.h"
#include "CsUI.h"

// CVar
#include "Script/CsCVars_Script.h"
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
			// Load
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, LoadByStringPath);
			// Render
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, Render_Opacity_Ease);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, Render_Scale_Ease);
			// Position
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetScreenPositionBySlot);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetAbsoluteScreenPositionByCachedGeometry);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetPixelAndViewportPositionByCachedGeometry);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetWorldPositionBySlot);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetWorldPositionByCachedGeometry);
			// Animation
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetAnimation);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetAnimationChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, PlayAnimation);
			// TextBlock
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetTextBlock);
			// Button
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetButton);
			// Image
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetImage);
			// ProgressBar
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetProgressBar);
			// Border
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetBorder);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Widget::UCsScriptLibrary_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define LogError &NCsUI::FLog::Error
#define WidgetLibrary NCsWidget::FLibrary

UUserWidget* UCsScriptLibrary_Widget::Create(const FString& Context, UObject* Owner, TSubclassOf<UUserWidget> UserWidgetClass, const FName& WidgetName)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Create : Context;

	return WidgetLibrary::CreateSafe(Context, Owner, UserWidgetClass, WidgetName);
}

// Load
#pragma region

UClass* UCsScriptLibrary_Widget::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	return WidgetLibrary::SafeLoad(Ctxt, Path);
}

UClass* UCsScriptLibrary_Widget::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	return WidgetLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

// Render
#pragma region

#define WidgetRenderLibrary NCsWidget::NRender::FLibrary

bool UCsScriptLibrary_Widget::Render_Opacity_Ease(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Render_Opacity_Ease : Context;

	return WidgetRenderLibrary::Opacity_SafeEase(Context, Widget, Easing, Start, End, Alpha);
}

bool UCsScriptLibrary_Widget::Render_Scale_Ease(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Render_Scale_Ease : Context;

	return WidgetRenderLibrary::Scale_SafeEase(Context, Widget, Easing, Start, End, Alpha);
}

#undef WidgetRenderLibrary

#pragma endregion Render

// Position
#pragma region

	// Screen
#pragma region

#define WidgetPositionLibrary NCsWidget::NPosition::NScreen::FLibrary 

FVector2f UCsScriptLibrary_Widget::GetScreenPositionBySlot(const FString& Context, UWidget* Widget)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetScreenPositionBySlot : Context;

	return WidgetPositionLibrary::GetSafeBySlot2f(Ctxt, Widget);
}

FVector2f UCsScriptLibrary_Widget::GetAbsoluteScreenPositionByCachedGeometry(const FString& Context, UWidget* Widget)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAbsoluteScreenPositionByCachedGeometry : Context;

	return WidgetPositionLibrary::GetSafeAbsoluteByCachedGeometry2f(Ctxt, Widget);
}

#undef WidgetPositionLibrary

#pragma endregion Screen

	// Viewport
#pragma region

#define WidgetPositionLibrary NCsWidget::NPosition::NViewport::FLibrary

void UCsScriptLibrary_Widget::GetPixelAndViewportPositionByCachedGeometry(const FString& Context, UWidget* Widget, FVector2f& OutPixelPosition, FVector2f& OutViewportPosition)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetPixelAndViewportPositionByCachedGeometry : Context;

	return WidgetPositionLibrary::GetSafeByCachedGeometry(Ctxt, Widget, OutPixelPosition, OutViewportPosition);
}

#undef WidgetPositionLibrary

#pragma endregion Viewport

	// World
#pragma region

#define WidgetPositionLibrary NCsWidget::NPosition::NWorld::FLibrary

bool UCsScriptLibrary_Widget::GetWorldPositionBySlot(const FString& Context, UObject* WorldContextObject, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetWorldPositionBySlot : Context;

	return WidgetPositionLibrary::GetSafeBySlot(Ctxt, WorldContextObject, ControllerId, Widget, OutPosition, OutDirection);
}

bool UCsScriptLibrary_Widget::GetWorldPositionByCachedGeometry(const FString& Context, UObject* WorldContextObject, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetWorldPositionByCachedGeometry : Context;

	return WidgetPositionLibrary::GetSafeByCachedGeometry(Ctxt, WorldContextObject, ControllerId, Widget, OutPosition, OutDirection);
}

#undef WidgetPositionLibrary

#pragma endregion World

#pragma endregion Position

// Animation
#pragma region

#define WidgetAnimationLibrary NCsWidget::NAnimation::FLibrary

UWidgetAnimation* UCsScriptLibrary_Widget::GetAnimation(const FString& Context, UUserWidget* Widget, const FName& AnimName)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAnimation : Context;

	return WidgetAnimationLibrary::GetSafe(Ctxt, Widget, AnimName);
}

UWidgetAnimation* UCsScriptLibrary_Widget::GetAnimationChecked(const FString& Context, UUserWidget* Widget, const FName& AnimName, bool& OutSuccess)
{	
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAnimationChecked : Context;

	return CS_SCRIPT_GET_CHECKED(WidgetAnimationLibrary::GetChecked(Ctxt, Widget, AnimName), WidgetAnimationLibrary::GetSafe(Ctxt, Widget, AnimName, LogError));
}

bool UCsScriptLibrary_Widget::PlayAnimation(const FString& Context, UUserWidget* Widget, const FCsUserWidget_Anim_PlayParams& Params)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::PlayAnimation : Context;

	return WidgetAnimationLibrary::SafePlay(Ctxt, Widget, Params);
}

#undef WidgetAnimationLibrary

#pragma endregion Animation

// TextBlock
#pragma region

#define WidgetTextBlockLibrary NCsWidget::NTextBlock::FLibrary

UTextBlock* UCsScriptLibrary_Widget::GetTextBlock(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetTextBlock : Context;

	return WidgetTextBlockLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#undef WidgetTextBlockLibrary

#pragma endregion TextBlock

// Button
#pragma region

#define WidgetButtonLibrary NCsWidget::NButton::FLibrary

UButton* UCsScriptLibrary_Widget::GetButton(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetButton : Context;

	return WidgetButtonLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#undef WidgetButtonLibrary

#pragma endregion Button

// Image
#pragma region

#define WidgetImageLibrary NCsWidget::NImage::FLibrary

UImage* UCsScriptLibrary_Widget::GetImage(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetImage : Context;

	return WidgetImageLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#undef WidgetImageLibrary

#pragma endregion Image

// ProgressBar
#pragma region

#define WidgetProgressBarLibrary NCsWidget::NProgressBar::FLibrary

UProgressBar* UCsScriptLibrary_Widget::GetProgressBar(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetProgressBar : Context;

	return WidgetProgressBarLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#undef WidgetProgressBarLibrary

#pragma endregion ProgressBar

// Border
#pragma region

#define WidgetBorderLibrary NCsWidget::NBorder::FLibrary 

UBorder* UCsScriptLibrary_Widget::GetBorder(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	using namespace NCsScriptLibraryWidget::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetBorder : Context;

	return WidgetBorderLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#undef WidgetBorderLibrary

#pragma endregion Border

#undef LogError
#undef WidgetLibrary