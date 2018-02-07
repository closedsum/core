// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/CsUserWidget.h"
#include "CsWidget_Inventory.generated.h"

UCLASS()
class CSCORE_API UCsWidget_Inventory : public UCsUserWidget
{
	GENERATED_UCLASS_BODY()

	virtual void Init() override;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MyVerticalBox;

	TCsFVector2D Position;
	TCsFVector2D Size;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Header_Text;

	UPROPERTY(meta = (BindWidget))
	class UCsWidget_Inventory_Grid* MyGrid;

	UPROPERTY(meta = (BindWidget))
	class UCsWidget_Inventory_Slot* Slot_Draggable;

	UPROPERTY()
	bool IsMovingSlot;
};