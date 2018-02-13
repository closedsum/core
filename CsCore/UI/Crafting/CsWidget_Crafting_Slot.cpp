// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Crafting/CsWidget_Crafting_Slot.h"
#include "CsCore.h"

// Cache
#pragma region

namespace ECsWidgeCraftingSlotCachedString
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
	Count = CS_EMPTY;
}

void UCsWidget_Crafting_Slot::UpdateDisplayNameWithCurrentCount()
{
	if (Count > CS_EMPTY)
	{ 
										//   FString::FromInt(Count) + TEXT("x ") + DisplayName
		const FString DisplayNameWithCount = FString::FromInt(Count) + ECsWidgeCraftingSlotCachedString::Str::x + DisplayName;

		SetString(DisplayNameWithCount);
	}
	else
	{
				//TEXT("")
		SetString(ECsCachedString::Str::Empty);
	}
}

void UCsWidget_Crafting_Slot::Empty()
{
	Count = CS_EMPTY;

	UpdateDisplayNameWithCurrentCount();
	SetImage(nullptr);
}