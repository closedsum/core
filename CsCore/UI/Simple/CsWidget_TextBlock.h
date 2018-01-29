// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsSimpleWidget.h"
#include "CsWidget_TextBlock.generated.h"

UCLASS()
class CSCORE_API UCsWidget_TextBlock : public UCsSimpleWidget
{
	GENERATED_UCLASS_BODY()

	virtual void NativeConstruct() override;
	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime) override;

	virtual void Show() override;
	virtual void Hide() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MyText;

	FCsWidget_Text Text;

	virtual void SetString(const FString &InString);
};