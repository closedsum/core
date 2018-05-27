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
	bUpdatePosition = false;
	bUpdateSize = false;

	Count = CS_EMPTY;
	MyData.Reset();
	MyData = nullptr;
}

void UCsWidget_Inventory_Slot::UpdateCurrentCount()
{
	if (Count > 1)
	{ 
		SetString(FString::FromInt(Count));
	}
	else
	{
				//TEXT("")
		SetString(ECsCached::Str::Empty);
	}
	
}

void UCsWidget_Inventory_Slot::AddItem(FCsItem* Item)
{
	if (Count == CS_EMPTY)
	{
		MyData = Item->GetData();

		SetImage(MyData->GetMaterial());
	}

	++Count;
	UpdateCurrentCount();
}

void UCsWidget_Inventory_Slot::RemoveItem(const FCsItem* const Item)
{
	Count = FMath::Max(0, Count - 1);

	if (Count == CS_EMPTY)
	{
		MyData.Reset();
		MyData = nullptr;

		SetImage(nullptr);
	}
	UpdateCurrentCount();
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

	UpdateCurrentCount();
	SetImage(nullptr);
}