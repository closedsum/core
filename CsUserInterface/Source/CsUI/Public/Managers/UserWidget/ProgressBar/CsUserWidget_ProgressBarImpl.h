// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Blueprint/UserWidget.h"
// Types
#include "Managers/UserWidget/ProgressBar/CsUserWidget_ProgressBarInfo.h"

#include "CsUserWidget_ProgressBarImpl.generated.h"

class UProgressBar;

UCLASS()
class CSUI_API UCsUserWidget_ProgressBarImpl : public UUserWidget
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* MyBar;

#define InfoType NCsUserWidget::NProgressBar::FInfo
	void SetInfo(const InfoType& Info);
#undef InfoType

	void SetPercent(const float& Percent);
};