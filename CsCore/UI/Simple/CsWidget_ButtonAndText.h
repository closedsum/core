// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsSimpleWidget.h"
#include "CsWidget_ButtonAndText.generated.h"

UCLASS()
class CSCORE_API UCsWidget_ButtonAndText : public UCsSimpleWidget
{
	GENERATED_UCLASS_BODY()

	virtual void NativeConstruct() override;
	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime) override;

	virtual void Show() override;
	virtual void Hide() override;

	UPROPERTY(meta = (BindWidget))
	UButton* MyButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MyText;

	FCsWidget_ButtonAndText ButtonAndText;
};