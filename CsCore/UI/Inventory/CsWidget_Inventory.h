// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/CsUserWidget.h"
#include "CsWidget_Inventory.generated.h"

UCLASS()
class CSCORE_API UCsWidget_Inventory : public UCsUserWidget
{
	GENERATED_UCLASS_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	uint8 RowSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	uint8 ColumnSize;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MyVerticalBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Header_Text;

	UPROPERTY(meta = (BindWidget))
	UGridPanel* MyGridPawnel;

	UPROPERTY()
	bool bSpawnSlots;

	virtual void SetupSlots();

	UPROPERTY(BlueprintReadOnly)
	TArray<class UCsWidget_Inventory_Slot*> Slots;
};