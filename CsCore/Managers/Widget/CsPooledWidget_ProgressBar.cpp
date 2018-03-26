// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Widget/CsPooledWidget_ProgressBar.h"
#include "CsCore.h"

// Cache
#pragma region

namespace ECsPooledWidgetProgressBarCachedString
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
	const FString& MemberName = ECsPooledWidgetProgressBarCachedString::Str::Bar;
	Bar.Init(MemberName, MemberName, GetName() + ECsCachedString::Str::Dot + MemberName);

	HasNativeContructed = true;
}

void UCsPooledWidget_ProgressBar::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime)
{
	Super::OnNativeTick(MyGeometry, InDeltaTime);

	Bar.OnNativeTick(InDeltaTime);
}

void UCsPooledWidget_ProgressBar::Allocate(const uint16& ActiveIndex, FCsPooledWidgetPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent)
{
	Super::Allocate(ActiveIndex, Payload, Time, RealTime, Frame, InOwner, InParent);

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