// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/ProgressBar/CsUserWidget_ProgressBarImpl.h"

// Component
#include "Components/ProgressBar.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsUserWidget_ProgressBarImpl)

UCsUserWidget_ProgressBarImpl::UCsUserWidget_ProgressBarImpl(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	MyBar(nullptr)
{
}

using InfoType = NCsUserWidget::NProgressBar::FInfo;

void UCsUserWidget_ProgressBarImpl::SetInfo(const InfoType& Info)
{
	MyBar->SetFillColorAndOpacity(Info.GetFillColorAndOpacity());
}

void UCsUserWidget_ProgressBarImpl::SetPercent(const float& Percent)
{
	MyBar->SetPercent(Percent);
}