// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsSeLibrary_DataRootSet.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
// Utility
#include "Utility/CsSeLog.h"
// Data
#include "Data/CsSeGetDataRootSet.h"

namespace NCsSeDataRootSet
{
	const FCsSeDataRootSet* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext)
	{
		return NCsDataRootSet::FLibrary::GetSafe<FCsSeDataRootSet, ICsSeGetDataRootSet, &ICsSeGetDataRootSet::GetCsSeDataRootSet>(Context, WorldContext, &NCsStatusEffect::FLog::Warning);
	}

	const FCsSeDataRootSet& FLibrary::GetChecked(const FString& Context, const UGameInstance* GameInstance)
	{
		return NCsDataRootSet::FLibrary::GetChecked<FCsSeDataRootSet, ICsSeGetDataRootSet, &ICsSeGetDataRootSet::GetCsSeDataRootSet>(Context, GameInstance);
	}

	const FCsSeDataRootSet& FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
	{
		return NCsDataRootSet::FLibrary::GetChecked<FCsSeDataRootSet, ICsSeGetDataRootSet, &ICsSeGetDataRootSet::GetCsSeDataRootSet>(Context, WorldContext);
	}

	#define MemberType FCsSeDataRootSet::EMember

	UDataTable* FLibrary::GetSafeDataTable(const FString& Context, const UObject* WorldContext, const MemberType& Member)
	{
		if (const FCsSeDataRootSet* DataRootSet = GetSafe(Context, WorldContext))
			return DataRootSet->GetSafeDataTable(Context, WorldContext, Member);
		return nullptr;
	}

	UDataTable* FLibrary::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member)
	{
		const FCsSeDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

		return DataRootSet.GetDataTableChecked(Context, WorldContext, Member);
	}

	const TSoftObjectPtr<UDataTable>& FLibrary::GetDataTableSoftObjectChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member)
	{
		const FCsSeDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

		return DataRootSet.GetDataTableSoftObjectChecked(Context, Member);
	}

	uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const FName& RowName)
	{
		const FCsSeDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

		return DataRootSet.GetDataTableRowChecked(Context, WorldContext, Member, RowName);
	}

	uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const UScriptStruct* RowStruct, const FName& RowName)
	{
		const FCsSeDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

		return DataRootSet.GetDataTableRowChecked(Context, WorldContext, Member, RowStruct, RowName);
	}

	#undef MemberType
}