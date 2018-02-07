// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Widget/CsPooledWidget.h"
#include "CsCore.h"

#include "Runtime/Engine/Public/UnrealEngine.h"

UCsPooledWidget::UCsPooledWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsPooledWidget::Init(const FGeometry& MyGeometry)
{
	Super::Init(MyGeometry);
}

void UCsPooledWidget::Init(const int32 &Index)
{
	Cache.Set(Index, this);
}

void UCsPooledWidget::Allocate(const uint16& ActiveIndex, FCsPooledWidgetPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent)
{
	Cache.Init(ActiveIndex, Payload, Time, RealTime, Frame, InOwner, InParent);

	SetSize(Payload->Size);
	Show();
}

void UCsPooledWidget::DeAllocate()
{
	Cache.DeAllocate();

	Hide();
	SetPosition(FVector2D::ZeroVector);
	SetSize(FVector2D::UnitVector);
}

void UCsPooledWidget::OnAddToCanvas(){}

void UCsPooledWidget::SetPosition(const FVector2D &InPosition)
{
	FVector2D Resolution = FVector2D(GSystemResolution.ResX, GSystemResolution.ResY);
	Position			 = (ParentCanvasSize / Resolution) * InPosition;
}