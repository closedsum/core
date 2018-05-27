// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Simple/CsWidget_Button.h"
#include "CsCore.h"

namespace ECsWidgetButtonCachedString
{
	namespace Str
	{
		const FString Button = TEXT("Button");
		const FString MyButton = TEXT("MyButton");
	}
}

UCsWidget_Button::UCsWidget_Button(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultVisibility = ESlateVisibility::Visible;
}

void UCsWidget_Button::OnNativeConstruct()
{
	Super::OnNativeConstruct();

	Button.Set(MyButton);
	const FString& ButtonName   = ECsWidgetButtonCachedString::Str::Button;
	const FString& MyButtonName = ECsWidgetButtonCachedString::Str::MyButton;
	Button.Init(ButtonName, MyButtonName, GetName() + ECsCached::Str::Dot + ButtonName);
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

UPanelSlot* UCsWidget_Button::GetChildSlot()
{
	return MyButton->Slot;
}