// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/CsUserWidget.h"
#include "CsCore.h"

UCsUserWidget::UCsUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsUserWidget::Init()
{
	HasInitFinished = true;
}

void UCsUserWidget::Show()
{
	SetIsEnabled(true);
	SetVisibility(ESlateVisibility::Visible);
}

void UCsUserWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
	SetIsEnabled(false);
}