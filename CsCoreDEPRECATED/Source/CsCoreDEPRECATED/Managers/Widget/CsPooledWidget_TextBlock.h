// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Widget/CsPooledWidget.h"
#include "CsPooledWidget_TextBlock.generated.h"

UCLASS()
class CSCOREDEPRECATED_API UCsPooledWidget_TextBlock : public UCsPooledWidget
{
	GENERATED_UCLASS_BODY()

	virtual void NativeConstruct() override;
	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime) override;

	virtual void Allocate(FCsWidgetPayload* Payload) override;
	virtual void DeAllocate() override;

	virtual void Show() override;
	virtual void Hide() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MyText;

	FCsWidget_Text Text;

	virtual UPanelSlot* GetChildSlot() override;

	virtual void SetString(const FString &InString);
};