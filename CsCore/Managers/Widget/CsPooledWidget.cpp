// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Widget/CsPooledWidget.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

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

void UCsPooledWidget::Allocate(const uint16& ActiveIndex, FCsWidgetPayload* Payload, UObject* InOwner, UObject* InParent)
{
	Cache.Init(ActiveIndex, Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(GetWorld()), InOwner, InParent);

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

void UCsPooledWidget::OnAddToCanvas()
{
	UCanvasPanelSlot* ChildSlot  = Cast<UCanvasPanelSlot>(GetChildSlot());
	UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(Slot);
	ParentSlot->SetAlignment(ChildSlot->GetAlignment());
}

void UCsPooledWidget::SetPosition(const FVector2D &InPosition)
{
	FVector2D Resolution = FVector2D(GSystemResolution.ResX, GSystemResolution.ResY);
	Position			 = (ParentCanvasSize / Resolution) * InPosition;
}