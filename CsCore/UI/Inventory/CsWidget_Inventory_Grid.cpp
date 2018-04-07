// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Inventory/CsWidget_Inventory_Grid.h"
#include "Types/CsTypes_UI.h"
#include "CsCore.h"

#include "UI/Inventory/CsWidget_Inventory_Slot.h"

#include "Runtime/Slate/Public/Widgets/Layout/SConstraintCanvas.h"

UCsWidget_Inventory_Grid::UCsWidget_Inventory_Grid(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Slots.Reset();
}

void UCsWidget_Inventory_Grid::OnNativeConstruct()
{
	Super::OnNativeConstruct();

	if (!bSpawnSlots)
	{
		Dimension.RowSpan	 = MyGridPanel->RowFill.Num();
		Dimension.ColumnSpan = MyGridPanel->ColumnFill.Num();
	}
}

void UCsWidget_Inventory_Grid::Init(const FGeometry& MyGeometry)
{
	Super::Init(MyGeometry);

	Setup();
}

void UCsWidget_Inventory_Grid::Show()
{
	Super::Show();

	const uint8 Count = Slots.Num();

	for (uint8 I = 0; I < Count; ++I)
	{
		Slots[I]->Show();
	}
}

void UCsWidget_Inventory_Grid::Hide()
{
	const uint8 Count = Slots.Num();

	for (uint8 I = 0; I < Count; ++I)
	{
		Slots[I]->Hide();
	}

	Super::Hide();
}

void UCsWidget_Inventory_Grid::SetupSize()
{
	if (UseDynamicSize)
	{
		
	}
	else
	{
	}
}

void UCsWidget_Inventory_Grid::SetupDimensions()
{
	if (UseDynamicDimensions)
	{
	}
	else
	{
		SlotSize = FVector2D(Size.Get().X / (float)Dimension.ColumnSpan, Size.Get().Y / (float)Dimension.RowSpan);
	}
}

void UCsWidget_Inventory_Grid::SetupSlots()
{
	if (bSpawnSlots)
	{

	}
}

void UCsWidget_Inventory_Grid::Setup()
{
	SetupSize();
	SetupDimensions();
	SetupSlots();

	SynchronizeProperties();
}