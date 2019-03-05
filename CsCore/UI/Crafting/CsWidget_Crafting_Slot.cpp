// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Crafting/CsWidget_Crafting_Slot.h"
#include "CsCore.h"

// Cache
#pragma region

namespace ECsWidgeCraftingSlotCached
{
	namespace Str
	{
		const FString x = TEXT("x ");
	}
}

#pragma endregion Cache

UCsWidget_Crafting_Slot::UCsWidget_Crafting_Slot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUpdatePosition = false;
	bUpdateSize = false;

	Count = CS_EMPTY;
}

void UCsWidget_Crafting_Slot::UpdateDisplayNameWithCurrentCount()
{
	if (Count > CS_EMPTY)
	{ 
										//   FString::FromInt(Count) + TEXT("x ") + DisplayName
		const FString DisplayNameWithCount = FString::FromInt(Count) + ECsWidgeCraftingSlotCached::Str::x + DisplayName;

		SetString(DisplayNameWithCount);
	}
	else
	{
				//TEXT("")
		SetString(ECsCached::Str::Empty);
	}
}

void UCsWidget_Crafting_Slot::Empty()
{
	Count = CS_EMPTY;

	UpdateDisplayNameWithCurrentCount();
	SetImage(nullptr);
}