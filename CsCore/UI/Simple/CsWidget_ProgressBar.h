// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsSimpleWidget.h"
#include "CsWidget_ProgressBar.generated.h"

UCLASS()
class CSCORE_API UCsWidget_ProgressBar : public UCsSimpleWidget
{
	GENERATED_UCLASS_BODY()

	virtual void OnNativeConstruct() override;
	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime) override;

	virtual void Show() override;
	virtual void Hide() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* MyBar;

	FCsWidget_Bar Bar;

	virtual UPanelSlot* GetChildSlot() override;

	void SetPercent(const float &Value);
};