// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Inventory/CsWidget_Inventory.h"
#include "CsCore.h"

#include "UI/Inventory/CsWidget_Inventory_Grid.h"

UCsWidget_Inventory::UCsWidget_Inventory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsWidget_Inventory::Init()
{
	const FGeometry& Geometry = MyVerticalBox->GetCachedGeometry();
	// TopLeft
	Position = Geometry.LocalToAbsolute(FVector2D(0, 0));
	// Size = BotRight - TopLeft
	Size = Geometry.LocalToAbsolute(Geometry.GetLocalSize()) - Position;
}