// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsSimpleWidget.h"
#include "CsWidget_Int32.generated.h"

UCLASS()
class CSCORE_API UCsWidget_Int32 : public UCsSimpleWidget
{
	GENERATED_UCLASS_BODY()

	virtual void OnNativeConstruct() override;
	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime) override;

	virtual void Show() override;
	virtual void Hide() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MyText;

	FCsWidget_Int32 Text;

	virtual UPanelSlot* GetChildSlot() override;

	virtual void SetValue(const int32 &Value);
};