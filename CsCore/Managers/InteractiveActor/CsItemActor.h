// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/InteractiveActor/CsInteractiveActor.h"
#include "Types/CsTypes_Item.h"
#include "CsItemActor.generated.h"

UCLASS()
class CSCORE_API ACsItemActor : public ACsInteractiveActor
{
	GENERATED_UCLASS_BODY()

	TArray<FCsItem*> Items;
};