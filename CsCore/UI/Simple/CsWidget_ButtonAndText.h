// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsSimpleWidget.h"
#include "Managers/Input/CsTypes_Input.h"
#include "CsWidget_ButtonAndText.generated.h"

UCLASS()
class CSCORE_API UCsWidget_ButtonAndText : public UCsSimpleWidget
{
	GENERATED_UCLASS_BODY()

	virtual void OnNativeConstruct() override;
	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime) override;

	virtual void Show() override;
	virtual void Hide() override;

	UPROPERTY(meta = (BindWidget))
	UButton* MyButton;

	virtual UPanelSlot* GetChildSlot() override;

	UFUNCTION()
	virtual void MyButton_OnPressed();

	FECsInputAction InputAction_OnPressed;

	FVector MousePosition_OnPressed;

	UFUNCTION()
	virtual void MyButton_OnReleased();

	FVector MousePosition_OnReleased;

	UFUNCTION()
	virtual void MyButton_OnHovered();

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void SetImage(class UMaterialInstanceConstant* Material);

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MyText;

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void SetString(const FString& InString);

	FCsWidget_ButtonAndText ButtonAndText;
};