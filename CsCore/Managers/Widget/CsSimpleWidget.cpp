// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Widget/CsSimpleWidget.h"
#include "CsCore.h"

UCsSimpleWidget::UCsSimpleWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultVisibility = ESlateVisibility::HitTestInvisible;
}

void UCsSimpleWidget::OnNativeTick(const FGeometry& MyGeometry, float InDeltaTime){}
void UCsSimpleWidget::OnTick(const float &InDeltaTime){}

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

void UCsSimpleWidget::OnAddToCanvas(){}

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

void UCsSimpleWidget::SetPosition(const FVector2D &InPosition)
{
	FVector2D Resolution = FVector2D(GSystemResolution.ResX, GSystemResolution.ResY);
	Position			 = (ParentCanvasSize / Resolution) * InPosition;
}

void UCsSimpleWidget::SetSize(const FVector2D &InSize)
{
	Size = InSize;
}