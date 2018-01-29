// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Types/CsTypes_Pool.h"
#include "Types/CsTypes_UI.h"
#include "CsSimpleWidget.generated.h"

UCLASS()
class CSCORE_API UCsSimpleWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()

	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime);

	UPROPERTY()
	bool HasNativeContructed;

	UPROPERTY(BlueprintReadWrite, Category = "Widget")
	ESlateVisibility DefaultVisibility;

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void Show();
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void Hide();
};