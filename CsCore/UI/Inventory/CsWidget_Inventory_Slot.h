// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsWidget_ButtonAndText.h"
#include "Types/CsTypes_Item.h"
#include "CsWidget_Inventory_Slot.generated.h"

UCLASS()
class CSCORE_API UCsWidget_Inventory_Slot : public UCsWidget_ButtonAndText
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	uint8 Row;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	uint8 Column;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	FString DisplayName;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetDisplayName(const FString &InDisplayName);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateDisplayNameWithCurrentCount();

	TArray<FCsItem*> Items;

	void AddItem(FCsItem* Item);
	void RemoveItem(const FCsItem* const Item);
};