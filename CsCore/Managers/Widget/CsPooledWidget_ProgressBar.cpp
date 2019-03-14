// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Widget/CsPooledWidget_ProgressBar.h"
#include "CsCore.h"

// Cache
#pragma region

namespace ECsPooledWidgetProgressBarCached
{
	namespace Str
	{
		const FString Bar = TEXT("Bar");
	}
}

#pragma endregion Cache

UCsPooledWidget_ProgressBar::UCsPooledWidget_ProgressBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsPooledWidget_ProgressBar::NativeConstruct()
{
	Super::NativeConstruct();

	if (HasNativeContructed)
		return;

	Bar.Set(MyBar);
	const FString& MemberName = ECsPooledWidgetProgressBarCached::Str::Bar;
	Bar.Init(MemberName, MemberName, GetName() + NCsCached::Str::Dot + MemberName);

	HasNativeContructed = true;
}

void UCsPooledWidget_ProgressBar::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime)
{
	Super::OnNativeTick(MyGeometry, InDeltaTime);

	Bar.OnNativeTick(InDeltaTime);
}

void UCsPooledWidget_ProgressBar::Allocate(FCsWidgetPayload* Payload)
{
	Super::Allocate(Payload);

	Bar.SetPercent(1.0f);
}

void UCsPooledWidget_ProgressBar::DeAllocate()
{
	Super::DeAllocate();

	Bar.SetPercent(1.0f);
}

void UCsPooledWidget_ProgressBar::Show()
{
	Super::Show();

	Bar.SetIsEnabled(true);
	Bar.SetVisibility(DefaultVisibility);
}

void UCsPooledWidget_ProgressBar::Hide()
{
	Bar.SetVisibility(ESlateVisibility::Hidden);
	Bar.SetIsEnabled(false);

	Super::Hide();
}

void UCsPooledWidget_ProgressBar::SetPercent(const float &Value)
{
	Bar.SetPercent(Value);
}

UPanelSlot* UCsPooledWidget_ProgressBar::GetChildSlot()
{
	return MyBar->Slot;
}