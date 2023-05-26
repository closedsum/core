// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"

// Library
#include "Library/CsLibrary_Valid.h"
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

// FCsData_ECsDamageData
#pragma region

bool FCsData_ECsDamageData::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageData, Value);
	return true;
}

bool FCsData_ECsDamageData::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsDamageData, FECsDamageData, Value)
	return true;
}

#pragma endregion FCsData_ECsDamageData

// FCsData_DamagePtr
#pragma region

UObject* FCsData_DamagePtr::SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
{
	const FSoftObjectPath& Path = Data.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data is NOT Valid."), *Context))
		return nullptr;
	}

	UObject* O = Data.LoadSynchronous();

	if (!O)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load Data at Path: %s."), *Context, *(Path.ToString())))
	}
	return O;
}

#pragma endregion FCsData_DamagePtr