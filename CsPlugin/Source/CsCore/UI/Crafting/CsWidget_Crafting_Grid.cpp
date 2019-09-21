// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Crafting/CsWidget_Crafting_Grid.h"
#include "CsCore.h"

#include "UI/CsTypes_UI.h"

#include "UI/Crafting/CsWidget_Crafting_Slot.h"

#include "Runtime/Slate/Public/Widgets/Layout/SConstraintCanvas.h"

UCsWidget_Crafting_Grid::UCsWidget_Crafting_Grid(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUpdatePosition = false;
	bUpdateSize = false;
}

void UCsWidget_Crafting_Grid::OnNativeConstruct()
{
	Super::OnNativeConstruct();

	if (!bSpawnSlots)
	{
		Dimension.RowSpan	 = MyGridPanel->RowFill.Num();
		Dimension.ColumnSpan = MyGridPanel->ColumnFill.Num();
	}
}

void UCsWidget_Crafting_Grid::Init(const FGeometry& MyGeometry)
{
	Super::Init(MyGeometry);

	Setup();
}

void UCsWidget_Crafting_Grid::Show()
{
	Super::Show();

	const uint8 Count = Slots.Num();

	for (uint8 I = 0; I < Count; ++I)
	{
		Slots[I]->Show();
	}
}

void UCsWidget_Crafting_Grid::Hide()
{
	const uint8 Count = Slots.Num();

	for (uint8 I = 0; I < Count; ++I)
	{
		Slots[I]->Hide();
	}

	Super::Hide();
}

void UCsWidget_Crafting_Grid::SetupSize()
{
	if (UseDynamicSize)
	{
		
	}
	else
	{
	}
}

void UCsWidget_Crafting_Grid::SetupDimensions()
{
	if (UseDynamicDimensions)
	{
	}
	else
	{
		SlotSize = FVector2D(Size.Get().X / (float)Dimension.ColumnSpan, Size.Get().Y / (float)Dimension.RowSpan);
	}
}

void UCsWidget_Crafting_Grid::SetupSlots()
{
	if (bSpawnSlots)
	{

	}
}

void UCsWidget_Crafting_Grid::Setup()
{
	SetupSize();
	SetupDimensions();
	SetupSlots();

	SynchronizeProperties();
}

void UCsWidget_Crafting_Grid::Clear()
{
	const int32 Count = Slots.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		Slots[I]->Empty();
	}
}