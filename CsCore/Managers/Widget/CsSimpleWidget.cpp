// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Widget/CsSimpleWidget.h"
#include "CsCore.h"

UCsSimpleWidget::UCsSimpleWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsSimpleWidget::Init(const int32 &Index)
{
	Cache.Set(Index, this);
}

void UCsSimpleWidget::Allocate(const uint16& ActiveIndex, FCsSimpleWidgetPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent)
{
	Cache.Init(ActiveIndex, Payload, Time, RealTime, Frame, InOwner, InParent);
}

void UCsSimpleWidget::DeAllocate()
{
	Cache.DeAllocate();
}