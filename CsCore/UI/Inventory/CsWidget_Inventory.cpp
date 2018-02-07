// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Inventory/CsWidget_Inventory.h"
#include "CsCore.h"

#include "UI/Inventory/CsWidget_Inventory_Grid.h"

#include "Runtime/UMG/Public/Blueprint/SlateBlueprintLibrary.h"

UCsWidget_Inventory::UCsWidget_Inventory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsWidget_Inventory::Init()
{
	const FGeometry& Geometry = MyVerticalBox->GetCachedGeometry();
	// TopLeft
	FVector2D PixelPosition;
	FVector2D ViewportPosition;

	USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(), Geometry.GetAbsolutePosition(), PixelPosition, ViewportPosition);
	Position = PixelPosition;
	// Size = BotRight - TopLeft
	Size = Geometry.LocalToAbsolute(Geometry.GetLocalSize()) - Position;
}