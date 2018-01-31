// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsWidget_Grid.h"
#include "CsWidget_Inventory_Grid.generated.h"

UCLASS()
class CSCORE_API UCsWidget_Inventory_Grid : public UCsWidget_Grid
{
	GENERATED_UCLASS_BODY()

	virtual void Init() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void Show() override;
	virtual void Hide() override;

	bool UseDynamicSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FVector2D Size;

	virtual void SetupSize();

	bool UseDynamicRowAndColumnSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	uint8 RowSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	uint8 ColumnSize;

	virtual void SetupRowsAndColumns();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FVector2D SlotSize;

	bool bSpawnSlots;

	virtual void SetupSlots();

	UPROPERTY(BlueprintReadOnly)
	TArray<class UCsWidget_Inventory_Slot*> Slots;

	void Setup();
};