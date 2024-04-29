// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsPrjLibrary_DataRootSet.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
// Data
#include "Data/CsPrjGetDataRootSet.h"

namespace NCsProjectile
{
	namespace NDataRootSet
	{
		const FCsPrjDataRootSet* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext)
		{
			return NCsDataRootSet::FLibrary::GetSafe<FCsPrjDataRootSet, ICsPrjGetDataRootSet, &ICsPrjGetDataRootSet::GetCsPrjDataRootSet>(Context, WorldContext, &NCsProjectile::FLog::Warning);
		}

		const FCsPrjDataRootSet& FLibrary::GetChecked(const FString& Context, const UGameInstance* GameInstance)
		{
			return NCsDataRootSet::FLibrary::GetChecked<FCsPrjDataRootSet, ICsPrjGetDataRootSet, &ICsPrjGetDataRootSet::GetCsPrjDataRootSet>(Context, GameInstance);
		}

		const FCsPrjDataRootSet& FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			return NCsDataRootSet::FLibrary::GetChecked<FCsPrjDataRootSet, ICsPrjGetDataRootSet, &ICsPrjGetDataRootSet::GetCsPrjDataRootSet>(Context, WorldContext);
		}

		#define MemberType FCsPrjDataRootSet::EMember

		UDataTable* FLibrary::GetSafeDataTable(const FString& Context, const UObject* WorldContext, const MemberType& Member)
		{
			if (const FCsPrjDataRootSet* DataRootSet = GetSafe(Context, WorldContext))
				return DataRootSet->GetSafeDataTable(Context, WorldContext, Member);
			return nullptr;
		}

		UDataTable* FLibrary::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member)
		{
			const FCsPrjDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableChecked(Context, WorldContext, Member);
		}

		const TSoftObjectPtr<UDataTable>& FLibrary::GetDataTableSoftObjectChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member)
		{
			const FCsPrjDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableSoftObjectChecked(Context, Member);
		}

		uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const FName& RowName)
		{
			const FCsPrjDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableRowChecked(Context, WorldContext, Member, RowName);
		}

		uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const UScriptStruct* RowStruct, const FName& RowName)
		{
			const FCsPrjDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableRowChecked(Context, WorldContext, Member, RowStruct, RowName);
		}

		bool FLibrary::GetSafeDataTablePath(const FString& Context, const UObject* WorldContext, const MemberType& Member, FString& OutPath, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			if (const FCsPrjDataRootSet* DataRootSet = GetSafe(Context, WorldContext))
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