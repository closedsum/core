// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsTypes_Data_Damage.h"

// Settings
#include "Settings/CsDeveloperSettings.h"
// Utility
#include "Utility/CsLog.h"
#include "Utility/CsPopulateEnumMapFromSettings.h"
// Data
#include "Data/CsGetDataRootSet.h"
#include "Managers/Damage/Data/Point/CsData_DamagePointProxy.h"

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
		const FCsDataRootSet* DataRootSet = FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsDataRootSet, ICsGetDataRootSet, &ICsGetDataRootSet::GetCsDataRootSet>(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsDamageData>(Context, ContextRoot, DataRootSet->Damages, Str::DamageData, &FCsLog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsDamageData::Get().ClearUserDefinedEnums();

		FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion DamageData

// FCsData_DamagePoint
#pragma region

void FCsData_DamagePoint::SetData(PointDataProxyType* Data)
{
	Data->SetValue(&Damage);
	Data->SetType(&Type);
}

#pragma endregion FCsData_DamagePoint