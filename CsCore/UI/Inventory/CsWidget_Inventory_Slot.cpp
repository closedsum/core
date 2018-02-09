// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Inventory/CsWidget_Inventory_Slot.h"
#include "CsCore.h"

// Data
#include "Data/CsData_Item.h"

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
	Count = CS_EMPTY;
	MyData.Reset();
	MyData = nullptr;
}

void UCsWidget_Inventory_Slot::UpdateDisplayNameWithCurrentCount()
{
	if (Count > CS_EMPTY)
	{ 
		const FString DisplayName = GetMyData()->GetDisplayName();
										//   FString::FromInt(Count) + TEXT("x ") + DisplayName
		const FString DisplayNameWithCount = FString::FromInt(Count) + ECsWidgetInventorySlotCachedString::Str::x + DisplayName;

		SetString(DisplayNameWithCount);
	}
	else
	{
				//TEXT("")
		SetString(ECsCachedString::Str::Empty);
	}
	
}

void UCsWidget_Inventory_Slot::AddItem(FCsItem* Item)
{
	Count++;
	UpdateDisplayNameWithCurrentCount();
}

void UCsWidget_Inventory_Slot::RemoveItem(const FCsItem* const Item)
{
	Count = FMath::Max(0, Count - 1);

	if (Count == CS_EMPTY)
	{
		MyData.Reset();
		MyData = nullptr;
	}
	UpdateDisplayNameWithCurrentCount();
}

class ACsData_Item* UCsWidget_Inventory_Slot::GetMyData()
{
	return MyData.IsValid() ? MyData.Get() : nullptr;
}

void UCsWidget_Inventory_Slot::Empty()
{
	Count = CS_EMPTY;
	MyData.Reset();
	MyData = nullptr;

	UpdateDisplayNameWithCurrentCount();
}