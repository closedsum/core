// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsSimpleWidget.h"
#include "CsWidget_Button.generated.h"

UCLASS()
class CSCORE_API UCsWidget_Button : public UCsSimpleWidget
{
	GENERATED_UCLASS_BODY()

	virtual void OnNativeConstruct() override;
	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime) override;

	virtual void Show() override;
	virtual void Hide() override;

	UPROPERTY(meta = (BindWidget))
	UButton* MyButton;

	FCsWidget_Button Button;

	virtual UPanelSlot* GetChildSlot() override;
};