// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Inventory/CsWidget_Inventory.h"
#include "CsCore.h"

UCsWidget_Inventory::UCsWidget_Inventory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RowSize = 1;
	ColumnSize = 1;
}

void UCsWidget_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	if (HasNativeContructed)
		return;

	SetupSlots();

	// Grid Panel
	{
		// Update Fill Rules
		MyGridPawnel->RowFill.Reset();

		for (uint8 I = 0; I < RowSize; ++I)
		{
			MyGridPawnel->RowFill.Add(1.0f);
		}

		MyGridPawnel->ColumnFill.Reset();

		for (uint8 I = 0; I < ColumnSize; ++I)
		{

		}
	}

	MyGridPawnel->SynchronizeProperties();

	HasNativeContructed = true;
}

void UCsWidget_Inventory::SetupSlots()
{
	if (bSpawnSlots)
	{

	}
}