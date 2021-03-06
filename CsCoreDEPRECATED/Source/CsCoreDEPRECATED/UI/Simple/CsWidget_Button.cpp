// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Simple/CsWidget_Button.h"
#include "CsCoreDEPRECATED.h"

namespace ECsWidgetButtonCached
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
	const FString& ButtonName   = ECsWidgetButtonCached::Str::Button;
	const FString& MyButtonName = ECsWidgetButtonCached::Str::MyButton;
	Button.Init(ButtonName, MyButtonName, GetName() + NCsCached::Str::Dot + ButtonName);
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