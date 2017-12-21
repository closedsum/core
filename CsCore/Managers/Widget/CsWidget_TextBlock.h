// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Widget/CsSimpleWidget.h"
#include "CsWidget_TextBlock.generated.h"

UCLASS()
class CSCORE_API UCsWidget_TextBlock : public UCsSimpleWidget
{
	GENERATED_UCLASS_BODY()

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void Show() override;
	virtual void Hide() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MyText;

	FCsWidget_Text Text;

	FCsPrimitiveType<FVector2D> Position;
	FCsPrimitiveType<FVector2D> Size;

	virtual void SetString(const FString &InString);

	virtual void SetPosition(const FVector2D &InPosition);
	virtual void SetSize(const FVector2D &InSize);
};