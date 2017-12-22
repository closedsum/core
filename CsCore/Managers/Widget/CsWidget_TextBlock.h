// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Widget/CsSimpleWidget.h"
#include "CsWidget_TextBlock.generated.h"

UCLASS()
class CSCORE_API UCsWidget_TextBlock : public UCsSimpleWidget
{
	GENERATED_UCLASS_BODY()

	virtual void NativeConstruct() override;
	virtual void OnTick(const float &InDeltaTime) override;

	virtual void OnAddToCanvas() override;

	virtual void Show() override;
	virtual void Hide() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MyText;

	FCsWidget_Text Text;

	virtual void SetString(const FString &InString);
};