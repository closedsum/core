// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsTypes_Payload.h"
#include "CsCore.h"

// CVar
#include "CsCVars.h"
// Library
#include "Library/Load/CsLibrary_Load.h"

// FCsPayload_Data
#pragma region

#if WITH_EDITOR

void FCsPayload_Data::Populate()
{
	Paths.Reset();

	if (!Data.IsValid())
	{
		//UE_LOG(LogCs, Warning, TEXT("FCsPayload_Data::Populate:"));
		return;
	}

	UClass* Class = Data.LoadSynchronous();

	if (!Class)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsPayload_Data::Populate:"));
		return;
	}
	
	UObject* Object = Class->GetDefaultObject();

	Name = Object->GetFName();

	const FString ClassName = Class->GetName();

	if (!Object)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsPayload_Data::Populate:"));
		return;
	}

	// Add Data Path
	{
		/*
		FSoftObjectPath ObjectPath = Data.ToSoftObjectPath();
		const FName AssetPathName  = ObjectPath.GetAssetPathName();

		FCsSoftObjectPath& Path = Paths.Map.FindOrAdd(AssetPathName);
	
		Path.Path  = ObjectPath;
		int32 Size = Object->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
		Path.Size.SetBytes(Size);
		*/
	}
}

#endif // #if WITH_EDITOR

#pragma endregion FCsPayload_Data

// FCsPayload_DataTable
#pragma region

#if WITH_EDITOR

void FCsPayload_DataTable::Populate()
{
	Paths.Reset();
	PathsByRowMap.Reset();

	if (!DataTable.IsValid())
		return;

	UDataTable* DT = DataTable.LoadSynchronous();

	if (!DT)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsPayload_DataTable::Populate: Failed to load DataTable at Path: %s"), *(DataTable.ToString()));
		return;
	}

	const UScriptStruct* ScriptStruct = DT->GetRowStruct();
	UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
	UStruct* const Struct			  = Temp;
	
	const FString StructName    = Struct->GetName();
	const FString DataTableName = DT->GetName();

	if (CS_CVAR_LOG_IS_SHOWING(LogPayloadPopulate))
	{
		UE_LOG(LogCs, Warning, TEXT("FCsPayload_DataTable::Populate: %s."), *DataTableName);
	}

	// Add DataTable Path
	{
		FSoftObjectPath Path = DataTable.ToSoftObjectPath();

		FCsSoftObjectPath TempPath;
		TempPath.Path = Path;

		FSetElementId Id		    = Paths.Set.Add(TempPath);
		FCsSoftObjectPath& PathAtId = Paths.Set[Id];
	
		PathAtId.Path  = Path;
		int32 Size = DT->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
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
				FCsTArraySoftObjectPath& PathArray = PathsByRowMap.FindOrAdd(RowName);
				FSetElementId IdAtRow			   = PathArray.Set.Add(TempPath);
				FCsSoftObjectPath& PathByRowAtId   = PathArray.Set[IdAtRow];

				PathByRowAtId.Path = Path;

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

#endif // #if WITH_EDITOR

#pragma endregion FCsPayload_DataTable

// FCsPayload
#pragma region

#if  WITH_EDITOR

void FCsPayload::Append(TMap<FName, UDataTable*>& InDataTableMap, const bool& AllRows /*=false*/)
{
	// Check if any DataTables have already been added
	for (TPair<FName, FCsPayload_DataTable>& Pair : DataTableMap)
	{
		FCsPayload_DataTable& Payload = Pair.Value;
		const FName& Name			  = Payload.Name;

		if (InDataTableMap.Find(Name))
		{
			Payload.bAllRows = AllRows;

			InDataTableMap.Remove(Name);
		}
	}

	// Add Payload information for each DataTable
	for (TPair<FName, UDataTable*>& Pair : InDataTableMap)
	{
		const FName& Name	  = Pair.Key;
		UDataTable* DataTable = Pair.Value;

		FCsPayload_DataTable& Payload  = DataTableMap.Add(Name);

		Payload.Name	  = Name;
		Payload.DataTable = DataTable;
		Payload.bAllRows  = AllRows;
	}
}

void FCsPayload::Append(const FCsPayload& Payload)
{
	// Datas
	for (const FCsPayload_Data& Data : Payload.Datas)
	{
		const FName& Name = Data.Name;

		if (DataMap.Find(Name))
			continue;

		DataMap.Add(Name, Data);
	}
	// DataTables
	for (const FCsPayload_DataTable& DataTable : Payload.DataTables)
	{
		const FName& Name = DataTable.Name;

		if (FCsPayload_DataTable* DataTablePtr = DataTableMap.Find(Name))
		{
			// Check if any DataTable container has bAllRows == true
			if (DataTable.bAllRows &&
				!DataTablePtr->bAllRows)
			{
				*DataTablePtr = DataTable;
			}
		}

		DataTableMap.Add(Name, DataTable);
	}
	// Paths
	Paths.Append(Payload.Paths);
}

void FCsPayload::Append(const TMap<FName, FCsPayload>& PayloadMap)
{
	for (const TPair<FName, FCsPayload>& Pair : PayloadMap)
	{
		Append(Pair.Value);
	}
}

#endif // #if WITH_EDITOR

#pragma endregion FCsPayload