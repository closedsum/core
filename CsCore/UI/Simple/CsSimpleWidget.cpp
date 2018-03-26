// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Simple/CsSimpleWidget.h"
#include "CsCore.h"

#include "Runtime/UMG/Public/Blueprint/SlateBlueprintLibrary.h"
#include "Runtime/Engine/Public/UnrealEngine.h"

UCsSimpleWidget::UCsSimpleWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultVisibility = ESlateVisibility::HitTestInvisible;
}

void UCsSimpleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (HasNativeContructed)
		return;

	OnNativeConstruct();

	HasNativeContructed = true;
}

void UCsSimpleWidget::OnNativeConstruct() {}

void UCsSimpleWidget::Init(const FGeometry& MyGeometry)
{
	// TopLeft
	FVector2D PixelPosition;
	FVector2D ViewportPosition;

	USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(), MyGeometry.GetAbsolutePosition(), PixelPosition, ViewportPosition);
	Position = PixelPosition;
	// Size = BotRight - TopLeft
	Size = MyGeometry.GetAbsoluteSize(); 
}

void UCsSimpleWidget::Init(const int32 &Index){}
void UCsSimpleWidget::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime)
{
	// TODO: When the widget is part of a WidgetComponent, there is NO Slot
	if (!Slot)
		return;

	// Position
	if (Position.HasChanged())
	{
		UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(Slot);
		ParentSlot->SetPosition(Position.Get());
	}
	// Size
	if (Size.HasChanged())
	{
		//SetDesiredSizeInViewport(Size.Get());

		// Set Size of TextBlock
		UCanvasPanelSlot* ChildSlot = Cast<UCanvasPanelSlot>(GetChildSlot());
		ChildSlot->SetSize(Size.Get());
		// Set Size of Widget
		UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(Slot);
		ParentSlot->SetSize(Size.Get());
	}
	Position.Clear();
	Size.Clear();
}

void UCsSimpleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!HasInitFinished)
	{
		Init(MyGeometry);

		HasInitFinished = true;
	}

	OnNativeTick(MyGeometry, InDeltaTime);
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

UPanelSlot* UCsSimpleWidget::GetChildSlot() { return nullptr; }

void UCsSimpleWidget::SetPosition(const FVector2D &InPosition)
{
	Position = InPosition;
}

void UCsSimpleWidget::SetSize(const FVector2D &InSize)
{
	Size = InSize;
}