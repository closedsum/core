// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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

private:

	using InfoType = NCsUserWidget::NProgressBar::FInfo;

public:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* MyBar;

	void SetInfo(const InfoType& Info);

	void SetPercent(const float& Percent);
};