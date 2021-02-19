// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Script/CsScriptLibrary_Widget.h"
#include "CsUI.h"

// Library
#include "Library/CsLibrary_Property.h"
// Widget
#include "Blueprint/UserWidget.h"

UCsScriptLibrary_Widget::UCsScriptLibrary_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UWidgetAnimation* UCsScriptLibrary_Widget::GetSafeAnimation(UUserWidget* Widget, const FName& AnimName)
{
	if (!Widget)
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsScriptLibrary_Widget::GetSafeAnimation: Widget is NULL."));
		return nullptr;
	}

	if (AnimName == NAME_None)
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsScriptLibrary_Widget::GetSafeAnimation: AnimName: None is NULL."));
		return nullptr;
	}

	typedef NCsProperty::FLibrary PropertyLibrary;

	UWidgetAnimation* Animation = PropertyLibrary::GetObjectPropertyValue<UWidgetAnimation>(Widget, Widget->GetClass(), AnimName);

	if (!Animation)
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsScriptLibrary_Widget::GetSafeAnimation: Failed to get animation with Name: %s from Widget: %s."), *(AnimName.ToString()), *(Widget->GetName()));
	}
	return Animation;
}