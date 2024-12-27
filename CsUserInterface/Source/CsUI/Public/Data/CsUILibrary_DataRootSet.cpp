// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsUILibrary_DataRootSet.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
// Utility
#include "Utility/CsUILog.h"
// Data
#include "Data/CsUIGetDataRootSet.h"
#include "Data/CsUIDataRootSet.h"

namespace NCsUI
{
	namespace NDataRootSet
	{
		using MemberType = FCsUIDataRootSet::EMember;

		const FCsUIDataRootSet* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext)
		{
			return CsDataRootSetLibrary::GetSafe<FCsUIDataRootSet, ICsUIGetDataRootSet, &ICsUIGetDataRootSet::GetCsUIDataRootSet>(Context, WorldContext, &NCsUI::FLog::Warning);
		}

		const FCsUIDataRootSet& FLibrary::GetChecked(const FString& Context, const UGameInstance* GameInstance)
		{
			return CsDataRootSetLibrary::GetChecked<FCsUIDataRootSet, ICsUIGetDataRootSet, &ICsUIGetDataRootSet::GetCsUIDataRootSet>(Context, GameInstance);
		}

		const FCsUIDataRootSet& FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			return CsDataRootSetLibrary::GetChecked<FCsUIDataRootSet, ICsUIGetDataRootSet, &ICsUIGetDataRootSet::GetCsUIDataRootSet>(Context, WorldContext);
		}

		UDataTable* FLibrary::GetSafeDataTable(const FString& Context, const UObject* WorldContext, const MemberType& Member)
		{
			if (const FCsUIDataRootSet* DataRootSet = GetSafe(Context, WorldContext))
				return DataRootSet->GetSafeDataTable(Context, WorldContext, Member);
			return nullptr;
		}

		UDataTable* FLibrary::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member)
		{
			const FCsUIDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableChecked(Context, WorldContext, Member);
		}

		const TSoftObjectPtr<UDataTable>& FLibrary::GetDataTableSoftObjectChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member)
		{
			const FCsUIDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableSoftObjectChecked(Context, Member);
		}

		uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const FName& RowName)
		{
			const FCsUIDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableRowChecked(Context, WorldContext, Member, RowName);
		}

		uint8* FLibrary::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const MemberType& Member, const UScriptStruct* RowStruct, const FName& RowName)
		{
			const FCsUIDataRootSet& DataRootSet = GetChecked(Context, WorldContext);

			return DataRootSet.GetDataTableRowChecked(Context, WorldContext, Member, RowStruct, RowName);
		}

		bool FLibrary::GetSafeDataTablePath(const FString& Context, const UObject* WorldContext, const MemberType& Member, FString& OutPath, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
		{
			if (const FCsUIDataRootSet* DataRootSet = GetSafe(Context, WorldContext))
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
	}
}