// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Simple/CsWidget_Button.h"
#include "CsCore.h"

namespace ECsWidgetButtonCachedString
{
	namespace Str
	{
		const FString Button = TEXT("Button");
	}
}

UCsWidget_Button::UCsWidget_Button(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultVisibility = ESlateVisibility::Visible;
}

void UCsWidget_Button::NativeConstruct()
{
	Super::NativeConstruct();

	if (HasNativeContructed)
		return;

	Button.Set(MyButton);
	const FString& MemberName = ECsWidgetButtonCachedString::Str::Button;
	Button.Init(MemberName, MemberName, GetName() + ECsCachedString::Str::Dot + MemberName);

	HasNativeContructed = true;
}

void UCsWidget_Button::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime)
{
	Super::OnNativeTick(MyGeometry, InDeltaTime);

	Button.OnNativeTick(InDeltaTime);
}

void UCsWidget_Button::Show()
{
	Super::Show();

	Button.SetIsEnabled(true);
	Button.SetVisibility(DefaultVisibility);
}

void UCsWidget_Button::Hide()
{
	Button.SetVisibility(ESlateVisibility::Hidden);
	Button.SetIsEnabled(false);

	Super::Hide();
}