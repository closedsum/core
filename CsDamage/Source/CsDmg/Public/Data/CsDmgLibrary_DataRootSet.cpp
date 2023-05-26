// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsDmgLibrary_DataRootSet.h"

// Data
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsDmgGetDataRootSet.h"
#include "Data/CsDmgDataRootSet.h"

namespace NCsDamage
{
	namespace NDataRootSet
	{
		const FCsDmgDataRootSet* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext)
		{
			return NCsDataRootSet::FLibrary::GetSafe<FCsDmgDataRootSet, ICsDmgGetDataRootSet, &ICsDmgGetDataRootSet::GetCsDmgDataRootSet>(Context, WorldContext, &NCsDamage::FLog::Warning);
		}

		const FCsDmgDataRootSet& FLibrary::GetChecked(const FString& Context, const UGameInstance* GameInstance)
		{
			return NCsDataRootSet::FLibrary::GetChecked<FCsDmgDataRootSet, ICsDmgGetDataRootSet, &ICsDmgGetDataRootSet::GetCsDmgDataRootSet>(Context, GameInstance);
		}

		const FCsDmgDataRootSet& FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			return NCsDataRootSet::FLibrary::GetChecked<FCsDmgDataRootSet, ICsDmgGetDataRootSet, &ICsDmgGetDataRootSet::GetCsDmgDataRootSet>(Context, WorldContext);
		}

		#define MemberType FCsDmgDataRootSet::EMember

		UDataTable* FLibrary::GetSafeDataTable(const FString& Context, const UObject* WorldContext, const MemberType& Member)
		{
			if (const FCsDmgDataRootSet* DataRootSet = GetSafe(Context, WorldContext))
				return DataRootSet->GetSafeDataTable(Context, WorldContext, Member);
			return nullptr;
		}

		UDataTable* FLibrary::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member)
		{
			const FCsDmgDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableChecked(Context, WorldContext, Member);
		}

		const TSoftObjectPtr<UDataTable>& FLibrary::GetDataTableSoftObjectChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member)
		{
			const FCsDmgDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableSoftObjectChecked(Context, Member);
		}

		uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const FName& RowName)
		{
			const FCsDmgDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableRowChecked(Context, WorldContext, Member, RowName);
		}

		uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const UScriptStruct* RowStruct, const FName& RowName)
		{
			const FCsDmgDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableRowChecked(Context, WorldContext, Member, RowStruct, RowName);
		}

		bool FLibrary::GetSafeDataTablePath(const FString& Context, const UObject* WorldContext, const MemberType& Member, FString& OutPath, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			if (const FCsDmgDataRootSet* DataRootSet = GetSafe(Context, WorldContext))
			{
				TSoftObjectPtr<UDataTable> SoftObject;
				if (DataRootSet->GetSafeDataTableSoftObject(Context, Member, SoftObject, Log))
				{
					OutPath = SoftObject.ToString();
					int32 Index = INDEX_NONE;
					OutPath.FindLastChar('.', Index);
					OutPath = OutPath.Left(Index);
					return true;
				}
			}
			return false;
		}

		#undef MemberType
	}
}