// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Simple/CsSimpleWidget.h"
#include "CsCore.h"

#include "Runtime/Engine/Public/UnrealEngine.h"

UCsSimpleWidget::UCsSimpleWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultVisibility = ESlateVisibility::HitTestInvisible;
}

void UCsSimpleWidget::Init(){}
void UCsSimpleWidget::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime){}

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

void UCsSimpleWidget::SetSize(const FVector2D &InSize)
{
	Size = InSize;
}