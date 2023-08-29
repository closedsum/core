// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsTypes_DataEntry.h"
#include "CsCore.h"

// CVar
#include "CsCVars.h"
// Library
#include "Library/Load/CsLibrary_Load.h"
// Data
#include "Data/CsGetDataRootSet.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"

// DataEntryData
#pragma region

namespace NCsDataEntryData
{
	namespace Str
	{
		const FString DataEntryData = TEXT("DataEntryData");
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsDataRootSet* DataRootSet = FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsDataRootSet, ICsGetDataRootSet, &ICsGetDataRootSet::GetCsDataRootSet>(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable_RowAsName<EMCsDataEntryData>(Context, ContextRoot, DataRootSet->Datas, Str::DataEntryData, &FCsLog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsDataEntryData::Get().ClearUserDefinedEnums();

		FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion DataEntryData

// FCsDataEntry_Data
#pragma region

#if WITH_EDITOR

void FCsDataEntry_Data::Populate()
{
	Paths.Reset();

	if (!Data.ToSoftObjectPath().IsValid())
		return;

	UClass* Class = Data.LoadSynchronous();

	if (!Class)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsDataEntry_Data::Populate: Failed to load Data at Path: %s"), *(Data.ToString()));
		return;
	}

	UObject* DOb = Class->GetDefaultObject();

	// Add Data Path
	FSoftObjectPath DataPath = Data.ToSoftObjectPath();
	{
		FSoftObjectPath Path = DataPath;

		FCsSoftObjectPath TempPath;
		TempPath.Path = Path;

		FSetElementId Id = Paths.Set.Add(TempPath);
		FCsSoftObjectPath& PathAtId = Paths.Set[Id];

		PathAtId.Path = Path;
		int32 Size = DOb->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);

		if (Size > 0)
			PathAtId.Size.SetBytes(Size);

		if (CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate))
		{
			UE_LOG(LogCs, Warning, TEXT("- Adding Path: %s [%s]."), *(Path.ToString()), *(PathAtId.Size.ToString()));
		}
	}

	// Get Paths for anything Data references
	NCsLoad::FGetObjectPaths Result;
	
	UCsLibrary_Load::GetObjectPaths(DOb, Class, Result);

	FCsResourceSize Size;
	int32 I = 0;

	for (const FSoftObjectPath& Path : Result.Paths)
	{
		// Load Object and get the Resource Size
		UObject* Object = Path.TryLoad();

		int32 Bytes = 0;

		if (Object)
		{
			Bytes = Object->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
		}
		else
		{
			if (CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate))
			{
				UE_LOG(LogCs, Warning, TEXT("--- Failed to load Path: %s @ %s."), *(Path.GetAssetName()), *(Path.GetAssetPathString()));
			}
			continue;
		}

		// Update the Paths
		FCsSoftObjectPath TempPath;
		TempPath.Path = Path;

		// Cumulative
		FSetElementId Id = Paths.Set.Add(TempPath);
		FCsSoftObjectPath& PathAtId = Paths.Set[Id];

		PathAtId.Path = Path;

		if (Bytes > 0)
			PathAtId.Size.SetBytes(Bytes);

		if (CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate))
		{
			UE_LOG(LogCs, Warning, TEXT("---- [%d] [%s] %s @ %s."), I, *(PathAtId.Size.ToString()), *(Path.GetAssetName()), *(Path.GetAssetPathString()));
		}

		Size += PathAtId.Size;
		++I;
	}

	// Update internal structures for fast search / look up
	Paths.BuildFromSet();

	if (CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate))
	{
		UE_LOG(LogCs, Warning, TEXT("- Summary: Populated %d Paths [%s]."), Paths.Internal.Num(), *(Paths.Size.ToString()));
	}
}

void FCsDataEntry_Data::Populate(const TSet<FSoftObjectPath>& PathSet, const TArray<TSet<FSoftObjectPath>>& PathSetsByGroup)
{
	Paths.Reset();

	if (PathSet.IsEmpty())
		return;

	if (!Data.ToSoftObjectPath().IsValid())
		return;

	UClass* Class = Data.LoadSynchronous();

	if (!Class)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsDataEntry_Data::Populate: Failed to load Data at Path: %s"), *(Data.ToString()));
		return;
	}

	UObject* DOb = Class->GetDefaultObject();

	// Add Data Path
	FSoftObjectPath DataPath = Data.ToSoftObjectPath();

	// Populate Paths
	{
		if (CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate))
		{
			UE_LOG(LogCs, Warning, TEXT("-- Populating Paths."));
		}

		Paths.Populate(DOb, DataPath, CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate));
		Paths.Populate(PathSet, CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate));
	}
	// Populate Paths by Group
	{
		if (CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate))
		{
			UE_LOG(LogCs, Warning, TEXT("-- Populating Paths by Group."));
		}

		typedef EMCsObjectPathDependencyGroup GroupMapType;
		typedef ECsObjectPathDependencyGroup GroupType;

		PathsByGroup[(uint8)GroupType::Blueprint].Populate(DOb, DataPath, CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate));

		for (const GroupType& Group : GroupMapType::Get())
		{
			if (CS_CVAR_LOG_IS_SHOWING(LogPayloadPopulate))
			{
				UE_LOG(LogCs, Warning, TEXT("--- %s."), GroupMapType::Get().ToChar(Group));
			}

			const TSet<FSoftObjectPath>& Set = PathSetsByGroup[(uint8)Group];
			FCsTArraySoftObjectPath& Arr	 = PathsByGroup[(uint8)Group];

			Arr.Populate(Set, CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate));
		}
	}
}

#endif // WITH_EDITOR

#pragma endregion FCsDataEntry_Data

// FCsDataEntry_DataTable
#pragma region

#if WITH_EDITOR

void FCsDataEntry_DataTable::Populate()
{
	Paths.Reset();

	if (!DataTable.ToSoftObjectPath().IsValid())
		return;

	UDataTable* DT = DataTable.LoadSynchronous();

	if (!DT)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsDataEntry_DataTable::Populate: Failed to load DataTable at Path: %s"), *(DataTable.ToString()));
		return;
	}

	const UScriptStruct* ScriptStruct = DT->GetRowStruct();
	UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
	UStruct* const Struct			  = Temp;
	
	const FString StructName    = Struct->GetName();
	const FString DataTableName = DT->GetName();

	if (CS_CVAR_LOG_IS_SHOWING(LogPayloadPopulate))
	{
		UE_LOG(LogCs, Warning, TEXT("FCsDataEntry_DataTable::Populate: %s."), *DataTableName);
	}

	// Add DataTable Path
	FSoftObjectPath DataTablePath = DataTable.ToSoftObjectPath();
	{
		FSoftObjectPath Path = DataTablePath;

		FCsSoftObjectPath TempPath;
		TempPath.Path = Path;

		FSetElementId Id		    = Paths.Set.Add(TempPath);
		FCsSoftObjectPath& PathAtId = Paths.Set[Id];
	
		PathAtId.Path = Path;
		int32 Size = DT->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);

		if (Size > 0)
			PathAtId.Size.SetBytes(Size);

		if (CS_CVAR_LOG_IS_SHOWING(LogPayloadPopulate))
		{
			UE_LOG(LogCs, Warning, TEXT("- Adding Path: %s [%s]."), *(Path.ToString()), *(PathAtId.Size.ToString()));
		}
	}

	TArray<FName> RowNames;

	// All Rows
	if (bAllRows)
	{
		RowNames = DT->GetRowNames();
	}
	// Specified Rows
	else
	{
		RowNames = Rows.Array();
	}

	// Get Paths for appropriate rows
	NCsLoad::FGetObjectPaths Result;
	TArray<FName> Keys;
	FCsResourceSize Size;

	if (CS_CVAR_LOG_IS_SHOWING(LogPayloadPopulate))
	{
		if (RowNames.Num() > CS_EMPTY)
		{
			UE_LOG(LogCs, Warning, TEXT("- Processing %d Rows."), RowNames.Num());
		}
	}

	for (const FName& RowName : RowNames)
	{
		FCsTArraySoftObjectPath& PathArray = PathsByRowMap.FindOrAdd(RowName);

		// Add DataTable Path
		{
			FCsSoftObjectPath TempPath;
			TempPath.Path = DataTablePath;

			FSetElementId IdAtRow = PathArray.Set.Add(TempPath);
			FCsSoftObjectPath& PathByRowAtId = PathArray.Set[IdAtRow];

			PathByRowAtId.Path = DataTablePath;
		}

		uint8* RowPtr = DT->FindRowUnchecked(RowName);

		const FString RowNameAsString = RowName.ToString();
		const FString OuterName		  = FString::Printf(TEXT("%s.%s"), *DataTableName, *RowNameAsString);

		Result.Reset();
		UCsLibrary_Load::GetObjectPaths(RowPtr, Struct, Result);

		const int32 Count = Result.Paths.Num();

		if (Count != CS_EMPTY)
		{
			// Log Paths (number and name)
			if (CS_CVAR_LOG_IS_SHOWING(LogPayloadPopulate))
			{
				UE_LOG(LogCs, Warning, TEXT("-- Row: %s: Found %d Paths."), *RowNameAsString, Count);
			}

			Size.Reset();

			int32 I = 0;

			for (const FSoftObjectPath& Path : Result.Paths)
			{
				// Load Object and get the Resource Size
				UObject* Object	= Path.TryLoad();

				int32 Bytes = 0;

				if (Object)
				{
					Bytes = Object->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
				}
				else
				{
					if (CS_CVAR_LOG_IS_SHOWING(LogPayloadPopulate))
					{
						UE_LOG(LogCs, Warning, TEXT("--- Failed to load Path: %s @ %s."), *(Path.GetAssetName()), *(Path.GetAssetPathString()));
					}
					continue;
				}
				
				// Update the Paths
				FCsSoftObjectPath TempPath;
				TempPath.Path = Path;
				
				// Cumulative
				FSetElementId Id			= Paths.Set.Add(TempPath);
				FCsSoftObjectPath& PathAtId = Paths.Set[Id];

				PathAtId.Path = Path;

				PathAtId.Size.SetBytes(Bytes);

				// Row
				FSetElementId IdAtRow			   = PathArray.Set.Add(TempPath);
				FCsSoftObjectPath& PathByRowAtId   = PathArray.Set[IdAtRow];

				PathByRowAtId.Path = Path;

				if (Bytes > 0)
					PathByRowAtId.Size.SetBytes(Bytes);

				if (CS_CVAR_LOG_IS_SHOWING(LogPayloadPopulate))
				{
					UE_LOG(LogCs, Warning, TEXT("---- [%d] [%s] %s @ %s."), I, *(PathAtId.Size.ToString()), *(Path.GetAssetName()), *(Path.GetAssetPathString()));
				}

				Size += PathAtId.Size;
				++I;
			}

			if (CS_CVAR_LOG_IS_SHOWING(LogPayloadPopulate))
			{
				UE_LOG(LogCs, Warning, TEXT("--- Total: %s."), *(Size.ToString()));
			}
		}
	}

	// Update internal structures for fast search / look up
	Paths.BuildFromSet();

	for (TPair<FName, FCsTArraySoftObjectPath>& Pair : PathsByRowMap)
	{
		Pair.Value.BuildFromSet();
	}

	if (CS_CVAR_LOG_IS_SHOWING(LogPayloadPopulate))
	{
		UE_LOG(LogCs, Warning, TEXT("- Summary: Populated %d Paths [%s]."), Paths.Internal.Num(), *(Paths.Size.ToString()));
	}
}

void FCsDataEntry_DataTable::PopulateRow(const FName& RowName, const TSet<FSoftObjectPath>& PathSet, const TArray<TSet<FSoftObjectPath>>& PathSetsByGroup)
{
	// Add DataTable Path
	FSoftObjectPath DataTablePath = DataTable.ToSoftObjectPath();

	UDataTable* DT = DataTable.LoadSynchronous();

	if (!DT)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsDataEntry_DataTable::Populate: Failed to load DataTable at Path: %s"), *(DataTable.ToString()));
		return;
	}

	// Populate Paths
	{
		if (CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate))
		{
			UE_LOG(LogCs, Warning, TEXT("-- Populating Paths."));
		}

		Paths.Populate(DT, DataTablePath, CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate));
		Paths.Populate(PathSet, CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate));
		PathsByRowMap[RowName].Populate(DT, DataTablePath, CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate));
		PathsByRowMap[RowName].Populate(PathSet, CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate));
	}
	// Populate Paths by Group
	{
		if (CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate))
		{
			UE_LOG(LogCs, Warning, TEXT("-- Populating Paths by Group."));
		}

		typedef EMCsObjectPathDependencyGroup GroupMapType;
		typedef ECsObjectPathDependencyGroup GroupType;

		FCsTArraySoftObjectPathByGroup& ArrGroup = PathsByGroupByRowMap[RowName];

		ArrGroup.PathsByGroup[(uint8)GroupType::DataTable].Populate(DT, DataTablePath, CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate));
		PathsByGroup[(uint8)GroupType::DataTable].Populate(DT, DataTablePath, CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate));

		for (const GroupType& Group : GroupMapType::Get())
		{
			if (CS_CVAR_LOG_IS_SHOWING(LogPayloadPopulate))
			{
				UE_LOG(LogCs, Warning, TEXT("--- %s."), GroupMapType::Get().ToChar(Group));
			} 

			const TSet<FSoftObjectPath>& Set = PathSetsByGroup[(uint8)Group];
			FCsTArraySoftObjectPath& Arr	 = ArrGroup.PathsByGroup[(uint8)Group];

			Arr.Populate(Set, CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate));
			PathsByGroup[(uint8)GroupType::DataTable].Populate(Set, CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate));
		}
	}
}

#endif // #if WITH_EDITOR

#pragma endregion FCsDataEntry_DataTable