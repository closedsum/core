// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Simple/CsWidget_ProgressBar.h"
#include "CsCore.h"

namespace ECsWidgetProgressBarCached
{
	namespace Str
	{
		const FString Bar = TEXT("Bar");
		const FString MyBar = TEXT("MyBar");
	}
}

UCsWidget_ProgressBar::UCsWidget_ProgressBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsWidget_ProgressBar::OnNativeConstruct()
{
	Super::OnNativeConstruct();

	Bar.Set(MyBar);
	const FString& BarName   = ECsWidgetProgressBarCached::Str::Bar;
	const FString& MyBarName = ECsWidgetProgressBarCached::Str::MyBar;
	Bar.Init(BarName, MyBarName, GetName() + ECsCached::Str::Dot + BarName);
}

void UCsWidget_ProgressBar::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime)
{
	Super::OnNativeTick(MyGeometry, InDeltaTime);

	Bar.OnNativeTick(InDeltaTime);
}

void UCsWidget_ProgressBar::Show()
{
	Super::Show();

	Bar.SetIsEnabled(true);
	Bar.SetVisibility(DefaultVisibility);
}

void UCsWidget_ProgressBar::Hide()
{
	Bar.SetVisibility(ESlateVisibility::Hidden);
	Bar.SetIsEnabled(false);

	Super::Hide();
}

UPanelSlot* UCsWidget_ProgressBar::GetChildSlot()
{
	return MyBar->Slot;
}

void UCsWidget_ProgressBar::SetPercent(const float &Value)
{
	Bar.SetPercent(Value);
}