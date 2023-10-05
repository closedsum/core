// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/ProgressBar/CsUserWidget_ProgressBarImpl.h"
#include "CsUI.h"

// Component
#include "Components/ProgressBar.h"

UCsUserWidget_ProgressBarImpl::UCsUserWidget_ProgressBarImpl(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	MyBar(nullptr)
{
}

#define InfoType NCsUserWidget::NProgressBar::FInfo
void UCsUserWidget_ProgressBarImpl::SetInfo(const InfoType& Info)
{
#undef InfoType

	MyBar->SetFillColorAndOpacity(Info.GetFillColorAndOpacity());
}

void UCsUserWidget_ProgressBarImpl::SetPercent(const float& Percent)
{
	MyBar->SetPercent(Percent);
}