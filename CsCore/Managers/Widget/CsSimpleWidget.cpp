// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Widget/CsSimpleWidget.h"
#include "CsCore.h"

UCsSimpleWidget::UCsSimpleWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultVisibility = ESlateVisibility::HitTestInvisible;
}

void UCsSimpleWidget::Init(const int32 &Index)
{
	Cache.Set(Index, this);
}

void UCsSimpleWidget::Allocate(const uint16& ActiveIndex, FCsSimpleWidgetPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent)
{
	Cache.Init(ActiveIndex, Payload, Time, RealTime, Frame, InOwner, InParent);

	Show();
}

void UCsSimpleWidget::DeAllocate()
{
	Cache.DeAllocate();

	Hide();
}

void UCsSimpleWidget::OnOwnerDeAllocate(const uint16 &PoolIndex, const uint16 &ActiveIndex, const uint8 &Type)
{
	DeAllocate();
}

void UCsSimpleWidget::Show()
{
	SetIsEnabled(true);
	SetVisibility(DefaultVisibility);
}

void UCsSimpleWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
	SetIsEnabled(false);
}