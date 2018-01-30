// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/CsUserWidget.h"
#include "CsWidget_Inventory.generated.h"

UCLASS()
class CSCORE_API UCsWidget_Inventory : public UCsUserWidget
{
	GENERATED_UCLASS_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY()
	bool UseDynamicSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FVector2D Size;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FVector2D GridSize;

	virtual void SetupSize();

	UPROPERTY()
	bool UseDynamicRowAndColumnSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	uint8 RowSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	uint8 ColumnSize;

	virtual void SetupRowAndColumnSize();

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MyVerticalBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Header_Text;

	UPROPERTY(meta = (BindWidget))
	UGridPanel* MyGridPanel;

	UPROPERTY()
	bool bSpawnSlots;

	virtual void SetupSlots();

	UPROPERTY(BlueprintReadOnly)
	TArray<class UCsWidget_Inventory_Slot*> Slots;
};