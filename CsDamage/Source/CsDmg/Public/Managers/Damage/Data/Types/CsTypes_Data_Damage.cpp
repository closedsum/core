// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"

// Utility
#include "Utility/CsDmgLog.h"
#include "Utility/CsPopulateEnumMapFromSettings.h"
// Data
#include "Data/CsDmgGetDataRootSet.h"

// DamageData
#pragma region

namespace NCsDamageData
{
	namespace Str
	{
		const FString DamageData = TEXT("DamageData");
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsDmgDataRootSet* DataRootSet = FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsDmgDataRootSet, ICsDmgGetDataRootSet, &ICsDmgGetDataRootSet::GetCsDmgDataRootSet>(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsDamageData>(Context, ContextRoot, DataRootSet->Damages, Str::DamageData, &NCsDamage::FLog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsDamageData::Get().ClearUserDefinedEnums();

		FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion DamageData