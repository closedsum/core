// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsWidget_Grid.h"
#include "CsWidget_Crafting_Grid.generated.h"

UCLASS()
class CSCORE_API UCsWidget_Crafting_Grid : public UCsWidget_Grid
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

	UPROPERTY(BlueprintReadOnly)
	TArray<class UCsWidget_Crafting_Slot*> Slots;

	void Setup();
	void Clear();
};