// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Widget/CsSimpleWidget.h"
#include "CsWidget_TextBlock.generated.h"

UCLASS()
class CSCORE_API UCsWidget_TextBlock : public UCsSimpleWidget
{
	GENERATED_UCLASS_BODY()

	virtual void NativeConstruct() override;
	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime) override;

	virtual void Allocate(const uint16& ActiveIndex, FCsSimpleWidgetPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent) override;
	virtual void DeAllocate() override;

	virtual void OnAddToCanvas() override;

	virtual void Show() override;
	virtual void Hide() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MyText;

	FCsWidget_Text Text;

	virtual void SetString(const FString &InString);
};