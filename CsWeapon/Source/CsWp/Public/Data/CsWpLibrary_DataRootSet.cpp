// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsWpLibrary_DataRootSet.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
// Data
#include "Data/CsWpGetDataRootSet.h"

namespace NCsWeapon
{
	namespace NDataRootSet
	{
		const FCsWpDataRootSet* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext)
		{
			return NCsDataRootSet::FLibrary::GetSafe<FCsWpDataRootSet, ICsWpGetDataRootSet, &ICsWpGetDataRootSet::GetCsWpDataRootSet>(Context, WorldContext, &NCsWeapon::FLog::Warning);
		}

		const FCsWpDataRootSet& FLibrary::GetChecked(const FString& Context, const UGameInstance* GameInstance)
		{
			return NCsDataRootSet::FLibrary::GetChecked<FCsWpDataRootSet, ICsWpGetDataRootSet, &ICsWpGetDataRootSet::GetCsWpDataRootSet>(Context, GameInstance);
		}

		const FCsWpDataRootSet& FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			return NCsDataRootSet::FLibrary::GetChecked<FCsWpDataRootSet, ICsWpGetDataRootSet, &ICsWpGetDataRootSet::GetCsWpDataRootSet>(Context, WorldContext);
		}

		#define MemberType FCsWpDataRootSet::EMember

		UDataTable* FLibrary::GetSafeDataTable(const FString& Context, const UObject* WorldContext, const MemberType& Member)
		{
			if (const FCsWpDataRootSet* DataRootSet = GetSafe(Context, WorldContext))
				return DataRootSet->GetSafeDataTable(Context, WorldContext, Member);
			return nullptr;
		}

		UDataTable* FLibrary::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member)
		{
			const FCsWpDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableChecked(Context, WorldContext, Member);
		}

		const TSoftObjectPtr<UDataTable>& FLibrary::GetDataTableSoftObjectChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member)
		{
			const FCsWpDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableSoftObjectChecked(Context, Member);
		}

		uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const FName& RowName)
		{
			const FCsWpDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableRowChecked(Context, WorldContext, Member, RowName);
		}

		uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const UScriptStruct* RowStruct, const FName& RowName)
		{
			const FCsWpDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableRowChecked(Context, WorldContext, Member, RowStruct, RowName);
		}

		bool FLibrary::GetSafeDataTablePath(const FString& Context, const UObject* WorldContext, const MemberType& Member, FString& OutPath, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			if (const FCsWpDataRootSet* DataRootSet = GetSafe(Context, WorldContext))
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