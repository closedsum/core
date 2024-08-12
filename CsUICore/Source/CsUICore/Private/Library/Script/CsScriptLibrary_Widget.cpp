// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Widget.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Widget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Widget)

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
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget, GetSoftClassAsStringByPath);
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

void(*UCsScriptLibrary_Widget::LogError)(const FString&) = &NCsUI::NCore::FLog::Error;

UCsScriptLibrary_Widget::UCsScriptLibrary_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryWidget::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryWidget::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

UUserWidget* UCsScriptLibrary_Widget::Create(const FString& Context, UObject* Owner, TSubclassOf<UUserWidget> UserWidgetClass, const FName& WidgetName)
{
	CONDITIONAL_SET_CTXT(Create);

	return CsWidgetLibrary::CreateSafe(Context, Owner, UserWidgetClass, WidgetName);
}

// Load
#pragma region

UClass* UCsScriptLibrary_Widget::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(LoadBySoftObjectPath);

	return CsWidgetLibrary::SafeLoad(Ctxt, Path);
}

UClass* UCsScriptLibrary_Widget::LoadByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadByStringPath);

	return CsWidgetLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

// Get
#pragma region

UUserWidget* UCsScriptLibrary_Widget::GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetByPath);

	return CsWidgetLibrary::GetSafe(Ctxt, Object, Path, OutSuccess);
}

bool UCsScriptLibrary_Widget::GetSoftClassAsStringByPath(const FString& Context, UObject* Object, const FString& Path, FString& OutPathAsString, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetSoftClassAsStringByPath);

	return CsWidgetLibrary::GetSafe(Ctxt, Object, Path, OutPathAsString, OutSuccess);
}

#pragma endregion Get

// Render
#pragma region

#define WidgetRenderLibrary NCsWidget::NRender::FLibrary

bool UCsScriptLibrary_Widget::Render_Opacity_Ease(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha)
{
	CONDITIONAL_SET_CTXT(Render_Opacity_Ease);

	return WidgetRenderLibrary::Opacity_SafeEase(Ctxt, Widget, Easing, Start, End, Alpha);
}

bool UCsScriptLibrary_Widget::Render_Scale_Ease(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha)
{
	CONDITIONAL_SET_CTXT(Render_Scale_Ease);

	return WidgetRenderLibrary::Scale_SafeEase(Ctxt, Widget, Easing, Start, End, Alpha);
}

#undef WidgetRenderLibrary

#pragma endregion Render

// Position
#pragma region

	// Screen
#pragma region

FVector2f UCsScriptLibrary_Widget::GetScreenPositionBySlot(const FString& Context, UWidget* Widget)
{
	CONDITIONAL_SET_CTXT(GetScreenPositionBySlot);

	return CsWidgetScreenPositionLibrary::GetSafeBySlot2f(Ctxt, Widget);
}

FVector2f UCsScriptLibrary_Widget::GetAbsoluteScreenPositionByCachedGeometry(const FString& Context, UWidget* Widget)
{
	CONDITIONAL_SET_CTXT(GetAbsoluteScreenPositionByCachedGeometry);

	return CsWidgetScreenPositionLibrary::GetSafeAbsoluteByCachedGeometry2f(Ctxt, Widget);
}

#pragma endregion Screen

	// Viewport
#pragma region

void UCsScriptLibrary_Widget::GetPixelAndViewportPositionByCachedGeometry(const FString& Context, UWidget* Widget, FVector2f& OutPixelPosition, FVector2f& OutViewportPosition)
{
	CONDITIONAL_SET_CTXT(GetPixelAndViewportPositionByCachedGeometry);

	return CsWidgetViewportPositionLibrary::GetSafeByCachedGeometry(Ctxt, Widget, OutPixelPosition, OutViewportPosition);
}

#pragma endregion Viewport

	// World
#pragma region

bool UCsScriptLibrary_Widget::GetWorldPositionBySlot(const FString& Context, UObject* WorldContextObject, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection)
{
	CONDITIONAL_SET_CTXT(GetWorldPositionBySlot);

	return CsWidgetWorldPositionLibrary::GetSafeBySlot(Ctxt, WorldContextObject, ControllerId, Widget, OutPosition, OutDirection);
}

bool UCsScriptLibrary_Widget::GetWorldPositionByCachedGeometry(const FString& Context, UObject* WorldContextObject, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection)
{
	CONDITIONAL_SET_CTXT(GetWorldPositionByCachedGeometry);

	return CsWidgetWorldPositionLibrary::GetSafeByCachedGeometry(Ctxt, WorldContextObject, ControllerId, Widget, OutPosition, OutDirection);
}

#pragma endregion World

#pragma endregion Position

// Animation
#pragma region

UWidgetAnimation* UCsScriptLibrary_Widget::GetAnimation(const FString& Context, UUserWidget* Widget, const FName& AnimName)
{
	CONDITIONAL_SET_CTXT(GetAnimation);

	return CsWidgetAnimationLibrary::GetSafe(Ctxt, Widget, AnimName);
}

UWidgetAnimation* UCsScriptLibrary_Widget::GetAnimationChecked(const FString& Context, UUserWidget* Widget, const FName& AnimName, bool& OutSuccess)
{	
	CONDITIONAL_SET_CTXT(GetAnimationChecked);

	return CS_SCRIPT_GET_CHECKED(CsWidgetAnimationLibrary::GetChecked(Ctxt, Widget, AnimName), CsWidgetAnimationLibrary::GetSafe(Ctxt, Widget, AnimName, LogError));
}

bool UCsScriptLibrary_Widget::PlayAnimation(const FString& Context, UUserWidget* Widget, const FCsUserWidget_Anim_PlayParams& Params)
{
	CONDITIONAL_SET_CTXT(PlayAnimation);

	return CsWidgetAnimationLibrary::SafePlay(Ctxt, Widget, Params);
}

#pragma endregion Animation

// TextBlock
#pragma region

UTextBlock* UCsScriptLibrary_Widget::GetTextBlock(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	CONDITIONAL_SET_CTXT(GetTextBlock);

	return CsWidgetTextBlockLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#pragma endregion TextBlock

// Button
#pragma region

UButton* UCsScriptLibrary_Widget::GetButton(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	CONDITIONAL_SET_CTXT(GetButton);

	return CSWidgetButtonLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#pragma endregion Button

// Image
#pragma region

UImage* UCsScriptLibrary_Widget::GetImage(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	CONDITIONAL_SET_CTXT(GetImage);

	return CsWidgetImageLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#pragma endregion Image

// ProgressBar
#pragma region

UProgressBar* UCsScriptLibrary_Widget::GetProgressBar(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	CONDITIONAL_SET_CTXT(GetProgressBar);

	return CsWidgetProgressBarLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#pragma endregion ProgressBar

// Border
#pragma region

UBorder* UCsScriptLibrary_Widget::GetBorder(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
{
	CONDITIONAL_SET_CTXT(GetBorder);

	return CsWidgetBorderLibrary::GetSafe(Ctxt, Widget, PropertyName);
}

#pragma endregion Border

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT

// Cached
#pragma region

namespace NCsScriptLibraryWidgetAnimation
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Widget_Animation, HasFinished);
		}
	}
}

#pragma endregion Cached

void(*UCsScriptLibrary_Widget_Animation::LogError)(const FString&) = &NCsUI::NCore::FLog::Error;

UCsScriptLibrary_Widget_Animation::UCsScriptLibrary_Widget_Animation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryWidgetAnimation::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryWidgetAnimation::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

bool UCsScriptLibrary_Widget_Animation::HasFinished(const FString& Context, const UUserWidget* Widget, const UWidgetAnimation* Animation)
{
	CONDITIONAL_SET_CTXT(HasFinished);

	return CsWidgetAnimationLibrary::SafeHasFinished(Ctxt, Widget, Animation);
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT