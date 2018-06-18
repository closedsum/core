// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Widget/CsPooledWidget.h"
#include "CsPooledWidget_ProgressBar.generated.h"

UCLASS()
class CSCORE_API UCsPooledWidget_ProgressBar : public UCsPooledWidget
{
	GENERATED_UCLASS_BODY()

	virtual void NativeConstruct() override;
	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime) override;

	virtual void Allocate(const uint16& ActiveIndex, FCsWidgetPayload* Payload, UObject* InOwner, UObject* InParent) override;
	virtual void DeAllocate() override;

	virtual void Show() override;
	virtual void Hide() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* MyBar;

	FCsWidget_Bar Bar;

	virtual UPanelSlot* GetChildSlot() override;

	virtual void SetPercent(const float &Value);
};