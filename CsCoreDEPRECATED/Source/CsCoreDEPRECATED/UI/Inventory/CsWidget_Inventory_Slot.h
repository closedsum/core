// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsWidget_ButtonAndText.h"
#include "Types/CsTypes_Item.h"
#include "CsWidget_Inventory_Slot.generated.h"

class UCsData_Item;

UCLASS()
class CSCOREDEPRECATED_API UCsWidget_Inventory_Slot : public UCsWidget_ButtonAndText
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	uint8 Row;
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	uint8 Column;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateCurrentCount();

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	int32 Count;

	void AddItem(FCsItem* Item);
	void RemoveItem(const FCsItem* const Item);

	TWeakObjectPtr<UCsData_Item> MyData;

	UCsData_Item* GetMyData();

	void Empty();
};