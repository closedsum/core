// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsSimpleWidget.h"
#include "CsWidget_Grid.generated.h"

UCLASS()
class CSCORE_API UCsWidget_Grid : public UCsSimpleWidget
{
	GENERATED_UCLASS_BODY()

	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime) override;

	virtual void Show() override;
	virtual void Hide() override;

	UPROPERTY(meta = (BindWidget))
	UGridPanel* MyGridPanel;

	virtual UPanelSlot* GetChildSlot() override;
};