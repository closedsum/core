// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Inventory/CsWidget_Inventory.h"
#include "CsCore.h"

#include "UI/Inventory/CsWidget_Inventory_Slot.h"

UCsWidget_Inventory::UCsWidget_Inventory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UseDynamicSize = false;
	Size = FVector2D::UnitVector;
	UseDynamicRowAndColumnSize = false;
	RowSize = 1;
	ColumnSize = 1;
	bSpawnSlots = false;
}

void UCsWidget_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	if (HasNativeContructed)
		return;

	SetupSize();
	SetupRowAndColumnSize();
	SetupSlots();

	MyGridPanel->SynchronizeProperties();

	HasNativeContructed = true;
}

void UCsWidget_Inventory::SetupSize()
{
	if (UseDynamicSize)
	{
		// Set Size of VerticalBox
		UCanvasPanelSlot* ChildSlot = Cast<UCanvasPanelSlot>(MyVerticalBox->Slot);
		ChildSlot->SetSize(Size);
		// Set Size of Widget
		UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(Slot);
		ParentSlot->SetSize(Size);
		// Get Size of GridPanel
		UVerticalBoxSlot* GridSlot = Cast<UVerticalBoxSlot>(MyGridPanel->Slot);
		//GridSize				   = GridSlot->GetSize();
	}
	else
	{
		// Get Size of VerticalBox
		UCanvasPanelSlot* ChildSlot = Cast<UCanvasPanelSlot>(MyVerticalBox->Slot);
		Size						= ChildSlot->GetSize();	
		// Get Size of GridPanel
		UVerticalBoxSlot* GridSlot = Cast<UVerticalBoxSlot>(MyGridPanel->Slot);
		//GridSize				   = GridSlot->GetSize();
	}
}

void UCsWidget_Inventory::SetupRowAndColumnSize()
{
	if (UseDynamicRowAndColumnSize)
	{
		// Update Fill Rules
		MyGridPanel->RowFill.Reset();

		for (uint8 I = 0; I < RowSize; ++I)
		{
			MyGridPanel->RowFill.Add(1.0f);
		}

		MyGridPanel->ColumnFill.Reset();

		for (uint8 I = 0; I < ColumnSize; ++I)
		{
			MyGridPanel->ColumnFill.Add(1.0f);
		}
	}
	else
	{
		RowSize    = MyGridPanel->RowFill.Num();
		ColumnSize = MyGridPanel->ColumnFill.Num();
	}
}

void UCsWidget_Inventory::SetupSlots()
{
	if (bSpawnSlots)
	{
		const FVector2D WidgetSize = FVector2D(GridSize.X / (float)ColumnSize, GridSize.Y / (float)RowSize);
		const uint8 Count		   = RowSize * ColumnSize;

		for (uint8 I = 0; I < Count; ++I)
		{
			UCsWidget_Inventory_Slot* Widget = CreateWidget<UCsWidget_Inventory_Slot>(GetWorld(), UCsWidget_Inventory_Slot::StaticClass());
			
			Widget->SetSize(WidgetSize);
			Widget->Row	   = I / ColumnSize;
			Widget->Column = I % ColumnSize;

			// Set Size of Button
			UCanvasPanelSlot* ChildSlot = Cast<UCanvasPanelSlot>(Widget->MyButton->Slot);
			ChildSlot->SetSize(WidgetSize);
			// Set Size of Widget
			UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(Widget->Slot);
			ParentSlot->SetSize(WidgetSize);
		}
	}
}