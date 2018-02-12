// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Crafting/CsWidget_Crafting.h"
#include "CsCore.h"

#include "UI/Crafting/CsWidget_Crafting_Grid.h"
#include "UI/Crafting/CsWidget_Crafting_Slot.h"

#include "Runtime/UMG/Public/Blueprint/SlateBlueprintLibrary.h"

UCsWidget_Crafting::UCsWidget_Crafting(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsWidget_Crafting::Init()
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