// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Inventory/CsWidget_Inventory_Slot.h"
#include "CsCore.h"

// Cache
#pragma region

namespace ECsWidgetInventorySlotCachedString
{
	namespace Str
	{
		const FString x = TEXT("x ");
	}
}

#pragma endregion Cache

UCsWidget_Inventory_Slot::UCsWidget_Inventory_Slot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsWidget_Inventory_Slot::SetDisplayName(const FString &InDisplayName)
{
	DisplayName = InDisplayName;

	UpdateDisplayNameWithCurrentCount();
}

void UCsWidget_Inventory_Slot::UpdateDisplayNameWithCurrentCount()
{
	const int32 Count				   = Items.Num();
									//   FString::FromInt(Count) + TEXT("x ") + DisplayName
	const FString DisplayNameWithCount = FString::FromInt(Count) + ECsWidgetInventorySlotCachedString::Str::x + DisplayName;

	SetString(DisplayNameWithCount);
}

void UCsWidget_Inventory_Slot::AddItem(FCsItem* Item)
{
	Items.Add(Item);
	UpdateDisplayNameWithCurrentCount();
}

void UCsWidget_Inventory_Slot::RemoveItem(const FCsItem* const Item)
{
	const int32 Count = Items.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		if (Item->UniqueId == Items[I]->UniqueId)
		{
			Items.RemoveAt(I);
			UpdateDisplayNameWithCurrentCount();
			break;
		}
	}
}