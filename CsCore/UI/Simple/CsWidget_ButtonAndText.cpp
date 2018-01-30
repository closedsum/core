// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Simple/CsWidget_ButtonAndText.h"
#include "CsCore.h"

namespace ECsWidgetButtonAndTextCachedString
{
	namespace Str
	{
		const FString ButtonAndText = TEXT("ButtonAndText");
		const FString Button = TEXT("Button");
		const FString MyButton = TEXT("MyButton");
		const FString Text = TEXT("Text");
		const FString MyText = TEXT("MyText");
	}
}

UCsWidget_ButtonAndText::UCsWidget_ButtonAndText(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultVisibility = ESlateVisibility::Visible;
}

void UCsWidget_ButtonAndText::NativeConstruct()
{
	Super::NativeConstruct();

	if (HasNativeContructed)
		return;

	// Button
	ButtonAndText.Button.Set(MyButton);
	const FString& MemberName   = ECsWidgetButtonAndTextCachedString::Str::ButtonAndText;
	const FString& MyButtonName = ECsWidgetButtonAndTextCachedString::Str::MyButton;
	const FString& ButtonName   = ECsWidgetButtonAndTextCachedString::Str::Button;
	ButtonAndText.Button.Init(ButtonName, MyButtonName, GetName() + ECsCachedString::Str::Dot + MemberName);
	// Text
	ButtonAndText.Text.Set(MyText);
	const FString& MyTextName = ECsWidgetButtonAndTextCachedString::Str::MyText;
	const FString& TextName   = ECsWidgetButtonAndTextCachedString::Str::Text;
	ButtonAndText.Text.Init(TextName, MyTextName, GetName() + ECsCachedString::Str::Dot + MemberName);

	HasNativeContructed = true;
}

void UCsWidget_ButtonAndText::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime)
{
	Super::OnNativeTick(MyGeometry, InDeltaTime);

	ButtonAndText.OnNativeTick(InDeltaTime);
}

void UCsWidget_ButtonAndText::Show()
{
	Super::Show();

	ButtonAndText.SetIsEnabled(true);
	ButtonAndText.SetVisibility(DefaultVisibility);
	ButtonAndText.Button.SetVisibility(ESlateVisibility::Visible);
	ButtonAndText.Text.SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UCsWidget_ButtonAndText::Hide()
{
	ButtonAndText.SetVisibility(ESlateVisibility::Hidden);
	ButtonAndText.SetIsEnabled(false);

	Super::Hide();
}