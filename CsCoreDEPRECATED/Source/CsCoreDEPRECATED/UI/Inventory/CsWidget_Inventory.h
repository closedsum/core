// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/CsUserWidget.h"
// Type
#include "Types/CsTypes_Item.h"
#include "Types/Property/Value/CsProperty_Vector2D.h"
#include "CsWidget_Inventory.generated.h"

class UCsWidget_Inventory_Grid;
class UCsWidget_Inventory_Slot;
class ACsManager_Inventory;

UCLASS()
class CSCOREDEPRECATED_API UCsWidget_Inventory : public UCsUserWidget
{
	GENERATED_UCLASS_BODY()

	virtual void OnNativeConstruct() override;
	virtual void Init() override;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MyVerticalBox;

	TCsFVector2D Position;
	TCsFVector2D Size;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Header_Text;

	UPROPERTY(meta = (BindWidget))
	UCsWidget_Inventory_Grid* MyGrid;

	UPROPERTY()
	uint8 Bag;

	UPROPERTY(meta = (BindWidget))
	UCsWidget_Inventory_Slot* Slot_Draggable;

	UPROPERTY()
	bool IsMovingSlot;

	TWeakObjectPtr<ACsManager_Inventory> MyManager_Inventory;

	UFUNCTION()
	class ACsManager_Inventory* GetMyManager_Inventory();

	void UpdateGrid();

	void OnAddItem(FCsItem* Item);
	void OnRemoveItem(FCsItem* Item);
	void OnHideItem(FCsItem* Item);
};