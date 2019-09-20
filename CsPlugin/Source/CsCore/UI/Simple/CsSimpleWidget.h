// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Managers/Pool/CsTypes_Pool.h"
#include "Types/CsTypes_UI.h"
#include "CsSimpleWidget.generated.h"

UCLASS()
class CSCORE_API UCsSimpleWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()

	virtual void NativeConstruct() override;
	virtual void OnNativeConstruct();

	UPROPERTY(Transient)
	bool HasNativeContructed;

	virtual void Init(const FGeometry& MyGeometry);
	virtual void Init(const int32& Index, const ECsSimpleWidgetType& InType);

	virtual void OnCreatePool();

	UPROPERTY(Transient)
	bool HasInitFinished;

	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "Widget")
	ESlateVisibility DefaultVisibility;

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void Show();
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void Hide();

	virtual UPanelSlot* GetChildSlot();

	TCsFVector2D Position;
	bool bUpdatePosition;

	virtual void SetPosition(const FVector2D &InPosition);

	TCsFVector2D Size;
	bool bUpdateSize;

	virtual void SetSize(const FVector2D &InSize);

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* Canvas;
};