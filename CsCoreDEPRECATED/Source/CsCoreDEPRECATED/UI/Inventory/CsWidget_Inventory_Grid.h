// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsWidget_Grid.h"
#include "CsWidget_Inventory_Grid.generated.h"

UCLASS()
class CSCOREDEPRECATED_API UCsWidget_Inventory_Grid : public UCsWidget_Grid
{
	GENERATED_UCLASS_BODY()

	virtual void OnNativeConstruct() override;

	virtual void Init(const FGeometry& MyGeometry) override;

	virtual void Show() override;
	virtual void Hide() override;

	bool UseDynamicSize;

	virtual void SetupSize();

	bool UseDynamicDimensions;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	FCsUint8MatrixDimension Dimension;

	virtual void SetupDimensions();

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	FVector2D SlotSize;

	bool bSpawnSlots;

	virtual void SetupSlots();

	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<class UCsWidget_Inventory_Slot*> Slots;

	void Setup();
};