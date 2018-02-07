// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Inventory/CsWidget_Inventory_Grid.h"
#include "Types/CsTypes_UI.h"
#include "CsCore.h"

#include "UI/Inventory/CsWidget_Inventory_Slot.h"

#include "Runtime/Slate/Public/Widgets/Layout/SConstraintCanvas.h"

UCsWidget_Inventory_Grid::UCsWidget_Inventory_Grid(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsWidget_Inventory_Grid::OnNativeConstruct()
{
	Super::OnNativeConstruct();

	if (!bSpawnSlots)
	{
		RowSize	   = MyGridPanel->RowFill.Num();
		ColumnSize = MyGridPanel->ColumnFill.Num();
	}
}

void UCsWidget_Inventory_Grid::Init(const FGeometry& MyGeometry)
{
	Setup();

	HasInitFinished = true;
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
		TSharedPtr<class SConstraintCanvas> ConstraintCanvas = Canvas->GetCanvasWidget();
		Size												 = ConstraintCanvas->GetDesiredSize();
	}
}

void UCsWidget_Inventory_Grid::SetupRowsAndColumns()
{
	if (UseDynamicRowAndColumnSize)
	{
	}
	else
	{
		SlotSize = FVector2D(Size.X / (float)ColumnSize, Size.Y / (float)RowSize);
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
	SetupRowsAndColumns();
	SetupSlots();

	SynchronizeProperties();
}