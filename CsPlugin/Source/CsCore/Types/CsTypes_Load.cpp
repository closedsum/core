// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Load.h"
#include "CsCore.h"
#include "CsCVars.h"

// Library
#include "Library/Load/CsLibrary_Load.h"
#include "Library/CsLibrary_Math.h"

#include "Sound/SoundCue.h"

namespace ECsLoadCached
{
	namespace Str
	{
		CSCORE_API const FString _Internal = TEXT("_Internal");
		CSCORE_API const FString _Class = TEXT("_Class");
		CSCORE_API const FString _SubclassOf = TEXT("_SubclassOf");
		CSCORE_API const FString _LoadFlags = TEXT("_LoadFlags");
		CSCORE_API const FString _1P_LoadFlags = TEXT("1P_LoadFlags");
		CSCORE_API const FString _3P_LoadFlags = TEXT("3P_LoadFlags");
		CSCORE_API const FString _3P_Low_LoadFlags = TEXT("3P_Low_LoadFlags");
		CSCORE_API const FString VR_LoadFlags = TEXT("VR_LoadFlags");
		CSCORE_API const FString _C = TEXT("_C");
	}
}

// LoadCodes
#pragma region

namespace NCsLoadCodes
{
	/*
	namespace Ref
	{
		CSCORE_API const Type Game = EMCsLoadFlags::Get().Add(Type::Game, TEXT("Game"));
		CSCORE_API const Type Game1P = EMCsLoadFlags::Get().Add(Type::Game1P, TEXT("Game1P"), TEXT("Game 1P"));
		CSCORE_API const Type Game3P = EMCsLoadFlags::Get().Add(Type::Game3P, TEXT("Game3P"), TEXT("Game 3P"));
		CSCORE_API const Type Game3PLow = EMCsLoadFlags::Get().Add(Type::Game3PLow, TEXT("Game3PLow"), TEXT("Game 3P Low"));
	}
	*/
	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 1;
}

#pragma endregion LoadCodes

// LoadFlags
#pragma region

namespace NCsLoadFlags
{
	namespace Ref
	{
		CSCORE_API const Type Game = EMCsLoadFlags::Get().Add(Type::Game, TEXT("Game"));
		CSCORE_API const Type Game1P = EMCsLoadFlags::Get().Add(Type::Game1P, TEXT("Game1P"), TEXT("Game 1P"));
		CSCORE_API const Type Game3P = EMCsLoadFlags::Get().Add(Type::Game3P, TEXT("Game3P"), TEXT("Game 3P"));
		CSCORE_API const Type Game3PLow = EMCsLoadFlags::Get().Add(Type::Game3PLow, TEXT("Game3PLow"), TEXT("Game 3P Low"));
		CSCORE_API const Type GameVR = EMCsLoadFlags::Get().Add(Type::GameVR, TEXT("GameVR"), TEXT("Game VR"));
		CSCORE_API const Type UI = EMCsLoadFlags::Get().Add(Type::UI, TEXT("UI"));
		//CSCORE_API const Type All = EMCsLoadFlags::Get().Add(Type::All, TEXT("All"));
	}

	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 1;
}

#pragma endregion LoadFlags

// LoadFlags_Editor
#pragma region

namespace NCsLoadFlags_Editor
{
	namespace Ref
	{
		CSCORE_API const Type Game = EMCsLoadFlags_Editor::Get().Add(Type::Game, TEXT("Game"));
		CSCORE_API const Type Game1P = EMCsLoadFlags_Editor::Get().Add(Type::Game1P, TEXT("Game1P"), TEXT("Game 1P"));
		CSCORE_API const Type Game3P = EMCsLoadFlags_Editor::Get().Add(Type::Game3P, TEXT("Game3P"), TEXT("Game 3P"));
		CSCORE_API const Type Game3PLow = EMCsLoadFlags_Editor::Get().Add(Type::Game3PLow, TEXT("Game3PLow"), TEXT("Game 3P Low"));
		CSCORE_API const Type GameVR = EMCsLoadFlags_Editor::Get().Add(Type::GameVR, TEXT("GameVR"), TEXT("Game VR"));
		CSCORE_API const Type UI = EMCsLoadFlags_Editor::Get().Add(Type::UI, TEXT("UI"));
		CSCORE_API const Type All = EMCsLoadFlags_Editor::Get().Add(Type::All, TEXT("All"));
		CSCORE_API const Type ECsLoadFlags_Editor_MAX = EMCsLoadFlags_Editor::Get().Add(Type::ECsLoadFlags_Editor_MAX, TEXT("ECsLoadFlags_Editor_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsLoadFlags_Editor_MAX;
}

#pragma endregion LoadFlags_Editor

// UnloadCodes
#pragma region

namespace NCsUnloadCodes
{
	/*
	namespace Ref
	{
	}
	*/
	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 1;
}

#pragma endregion UnloadCodes

// LoadAsyncOrder
#pragma region

namespace NCsLoadAsyncOrder
{
	namespace Ref
	{
		CSCORE_API const Type None = EMCsLoadAsyncOrder::Get().Add(Type::None, TEXT("None"));
		CSCORE_API const Type FirstToLast = EMCsLoadAsyncOrder::Get().Add(Type::FirstToLast, TEXT("FirstToLast"), TEXT("First to Last"));
		CSCORE_API const Type Bulk = EMCsLoadAsyncOrder::Get().Add(Type::Bulk, TEXT("Bulk"));
		CSCORE_API const Type ECsLoadAsyncOrder_MAX = EMCsLoadAsyncOrder::Get().Add(Type::ECsLoadAsyncOrder_MAX, TEXT("ECsLoadAsyncOrder_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsLoadAsyncOrder_MAX;
}

#pragma endregion LoadAsyncOrder

// Payload
#pragma region

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
		FSoftObjectPath ObjectPath = Data.ToSoftObjectPath();
		const FName AssetPathName  = ObjectPath.GetAssetPathName();

		FCsSoftObjectPath& Path = Paths.Map.FindOrAdd(AssetPathName);
	
		Path.Path  = ObjectPath;
		int32 Size = Object->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
		Path.Size.SetBytes(Size);
	}

	/*
	UCsLibrary_Load::GetUniqueObjectPaths(Object, Class, Paths_Internal);
	// Log Paths (number and name)
	const int32 Count = Paths_Internal.Num();
	if (Count > CS_SINGLETON)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsPayload_Data::Populate: Populating Paths with %d Paths from %s."), Count, *ClassName);
		for (int32 I = 1; I < Count; ++I)
		{
			const FSoftObjectPath& Path = Paths_Internal[I];
			UE_LOG(LogCs, Warning, TEXT("-- [%d] [%s] has %s."), I, *ClassName, *(Path.ToString()));
			Paths.Paths.AddDefaulted();
			FCsSoftObjectPath& P = Paths.Paths.Last();
			P.Path = Path;
			UObject* O = Path.TryLoad();
			if (!O)
			{
				// LOG
				continue;
			}
			int32 Size = O->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
			P.Size.SetBytes(Size);
		}
		Paths.CalculateSize();
		UE_LOG(LogCs, Warning, TEXT("FCsPayload_Data::Populate: Populated %d Paths from %s [%s]."), Paths_Internal.Num(), *ClassName, *(Paths.Size.ToString()));
	}
	*/
}

#endif // #if WITH_EDITOR

#pragma endregion FCsPayload_Data

	// FCsPayload_DataTable
#pragma region

#if WITH_EDITOR

void FCsPayload_DataTable::Populate()
{
	Paths.Reset();

	if (!DataTable.IsValid())
		return;

	UDataTable* DT = DataTable.LoadSynchronous();

	if (!DT)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsPayload_DataTable::Populate: Failed to load DataTable at Path: %s"), *(DataTable.ToString()));
		return;
	}

	Name = DT->GetFName();

	const UScriptStruct* ScriptStruct = DT->GetRowStruct();
	UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
	UStruct* const Struct			  = Temp;
	
	const FString StructName    = Struct->GetName();
	const FString DataTableName = DT->GetName();

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
	{
		UE_LOG(LogCs, Warning, TEXT("FCsPayload_DataTable::Populate: %s."), *DataTableName);
	}

	// Add DataTable Path
	{
		FSoftObjectPath ObjectPath = DataTable.ToSoftObjectPath();
		const FName AssetPathName  = ObjectPath.GetAssetPathName();

		FCsSoftObjectPath& Path = Paths.Map.FindOrAdd(AssetPathName);
	
		Path.Path  = ObjectPath;
		int32 Size = DT->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
		Path.Size.SetBytes(Size);

		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
		{
			UE_LOG(LogCs, Warning, TEXT("- Adding Path: %s [%s]."), *(ObjectPath.ToString()), *(Path.Size.ToString()));
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
		RowNames = Rows;
	}

	// Get Paths for appropriate rows
	TMap<FName, FSoftObjectPath> RowMap;
	TArray<FName> Keys;
	FCsResourceSize Size;


	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
	{
		if (RowNames.Num() > CS_EMPTY)
		{
			UE_LOG(LogCs, Warning, TEXT("- Processing %d Rows."), RowNames.Num());
		}
	}

	for (const FName& RowName : RowNames)
	{
		uint8* RowPtr = DT->FindRowUnchecked(RowName);

		RowMap.Reset();
		UCsLibrary_Load::GetObjectPaths(RowPtr, Struct, RowMap);

		const int32 Count = RowMap.Num();

		if (Count != CS_EMPTY)
		{
			// Log Paths (number and name)
			const FString RowNameAsString = RowName.ToString();

			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
			{
				UE_LOG(LogCs, Warning, TEXT("-- Row: %s: Found %d Paths."), *RowNameAsString, Count);
			}

			Size.Reset();

			int32 I = 0;

			for (const TPair<FName, FSoftObjectPath>& Pair : RowMap)
			{
				const FSoftObjectPath& ObjectPath = Pair.Value;
				const FName AssetPathName		  = ObjectPath.GetAssetPathName();

				FCsSoftObjectPath& Path = Paths.Map.FindOrAdd(AssetPathName);
				
				Path.Path = ObjectPath;

				UObject* Object	= ObjectPath.TryLoad();

				int32 Bytes = 0;

				if (Object)
				{
					Bytes = Object->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
				}
				else
				{
					if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
					{
						UE_LOG(LogCs, Warning, TEXT("--- Failed to load Path: %s."), *(ObjectPath.ToString()));
					}
				}

				Path.Size.SetBytes(Bytes);

				if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
				{
					UE_LOG(LogCs, Warning, TEXT("---- [%d] [%s] @ %s."), I, *(Path.Size.ToString()), *(ObjectPath.ToString()));
				}

				Size += Path.Size;
				++I;
			}

			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
			{
				UE_LOG(LogCs, Warning, TEXT("--- Total: %s."), *(Size.ToString()));
			}
		}
	}

	Paths.BuildFromMap();

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
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

#pragma endregion Payload

// DataEntry
#pragma region

	// FCsDataEntry_DataTable
#pragma region

#if WITH_EDITOR

void FCsDataEntry_DataTable::Populate()
{
	Paths.Reset();

	if (!DataTable.IsValid())
		return;

	UDataTable* DT = DataTable.LoadSynchronous();

	if (!DT)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsDataEntry_DataTable::Populate: Failed to load DataTable at Path: %s"), *(DataTable.ToString()));
		return;
	}

	Name = DT->GetFName();

	const UScriptStruct* ScriptStruct = DT->GetRowStruct();
	UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
	UStruct* const Struct			  = Temp;
	
	const FString StructName    = Struct->GetName();
	const FString DataTableName = DT->GetName();

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
	{
		UE_LOG(LogCs, Warning, TEXT("FCsDataEntry_DataTable::Populate: %s."), *DataTableName);
	}

	// Add DataTable Path
	{
		FSoftObjectPath ObjectPath = DataTable.ToSoftObjectPath();
		const FName AssetPathName  = ObjectPath.GetAssetPathName();

		FCsSoftObjectPath& Path = Paths.Map.FindOrAdd(AssetPathName);
	
		Path.Path  = ObjectPath;
		int32 Size = DT->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
		Path.Size.SetBytes(Size);

		if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
		{
			UE_LOG(LogCs, Warning, TEXT("- Adding Path: %s [%s]."), *(ObjectPath.ToString()), *(Path.Size.ToString()));
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
		RowNames = Rows;
	}

	// Get Paths for appropriate rows
	TMap<FName, FSoftObjectPath> RowMap;
	TArray<FName> Keys;
	FCsResourceSize Size;


	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
	{
		if (RowNames.Num() > CS_EMPTY)
		{
			UE_LOG(LogCs, Warning, TEXT("- Processing %d Rows."), RowNames.Num());
		}
	}

	for (const FName& RowName : RowNames)
	{
		uint8* RowPtr = DT->FindRowUnchecked(RowName);

		RowMap.Reset();
		UCsLibrary_Load::GetObjectPaths(RowPtr, Struct, RowMap);

		const int32 Count = RowMap.Num();

		if (Count != CS_EMPTY)
		{
			// Log Paths (number and name)
			const FString RowNameAsString = RowName.ToString();

			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
			{
				UE_LOG(LogCs, Warning, TEXT("-- Row: %s: Found %d Paths."), *RowNameAsString, Count);
			}

			Size.Reset();

			int32 I = 0;

			for (const TPair<FName, FSoftObjectPath>& Pair : RowMap)
			{
				const FSoftObjectPath& ObjectPath = Pair.Value;
				const FName AssetPathName		  = ObjectPath.GetAssetPathName();

				FCsSoftObjectPath& Path = Paths.Map.FindOrAdd(AssetPathName);
				
				Path.Path = ObjectPath;

				UObject* Object	= ObjectPath.TryLoad();

				int32 Bytes = 0;

				if (Object)
				{
					Bytes = Object->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
				}
				else
				{
					if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
					{
						UE_LOG(LogCs, Warning, TEXT("--- Failed to load Path: %s."), *(ObjectPath.ToString()));
					}
				}

				Path.Size.SetBytes(Bytes);

				if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
				{
					UE_LOG(LogCs, Warning, TEXT("---- [%d] [%s] @ %s."), I, *(Path.Size.ToString()), *(ObjectPath.ToString()));
				}

				Size += Path.Size;
				++I;
			}

			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
			{
				UE_LOG(LogCs, Warning, TEXT("--- Total: %s."), *(Size.ToString()));
			}
		}
	}

	Paths.BuildFromMap();

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogPayloadPopulate))
	{
		UE_LOG(LogCs, Warning, TEXT("- Summary: Populated %d Paths [%s]."), Paths.Internal.Num(), *(Paths.Size.ToString()));
	}
}

#endif // #if WITH_EDITOR

#pragma endregion FCsDataEntry_DataTable

#pragma endregion DataEntry