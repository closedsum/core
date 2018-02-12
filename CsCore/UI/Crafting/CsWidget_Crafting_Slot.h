// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsWidget_ButtonAndText.h"
#include "Types/CsTypes_Item.h"
#include "CsWidget_Crafting_Slot.generated.h"

UCLASS()
class CSCORE_API UCsWidget_Crafting_Slot : public UCsWidget_ButtonAndText
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	uint8 Row;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	uint8 Column;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateDisplayNameWithCurrentCount();

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	int32 Count;

	void Empty();
};