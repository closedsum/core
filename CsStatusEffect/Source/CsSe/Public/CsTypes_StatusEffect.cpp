// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_StatusEffect.h"
#include "CsSe.h"

// Utility
#include "Utility/CsSeLog.h"
#include "Utility/CsPopulateEnumMapFromSettings.h"
#include "Utility/CsSePopulateEnumMapFromSettings.h"
// Data
#include "Data/CsSeGetDataRootSet.h"

// StatusEffect
#pragma region

namespace NCsStatusEffect
{
	namespace Str
	{
		const FString StatusEffect = TEXT("StatusEffect");
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsSeDataRootSet* DataRootSet = FCsSePopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsStatusEffect>(Context, ContextRoot, DataRootSet->StatusEffects, Str::StatusEffect, &NCsStatusEffect::FLog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsStatusEffect::Get().ClearUserDefinedEnums();

		FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion StatusEffect

// StatusEffectEvent
#pragma region

namespace NCsStatusEffectEvent
{
	CSSE_API CS_CREATE_ENUM_STRUCT(Default);
	CSSE_API CS_CREATE_ENUM_STRUCT(Damage);
}

#pragma endregion StatusEffectEvent