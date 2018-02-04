// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Inventory/CsWidget_Inventory_Slot.h"
#include "CsCore.h"

UCsWidget_Inventory_Slot::UCsWidget_Inventory_Slot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsWidget_Inventory_Slot::RemoveItem(const FCsItem* const Item)
{
	const int32 Count = Items.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		if (Item->UniqueId == Items[I]->UniqueId)
		{
			Items.RemoveAt(I);
			break;
		}
	}
}