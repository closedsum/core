// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Load.h"
#include "CsCore.h"

// CVar
#include "CsCVars.h"
// Library
#include "Library/Load/CsLibrary_Load.h"
#include "Library/CsLibrary_Math.h"
// Data
#include "Data/CsGetDataRootSet.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"

namespace ECsLoadCached
{
	namespace Str
	{
		CSCORE_API const FString _Path = TEXT("_Path");
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
	CSCORE_API const int32 All = 15; // 1 + 2 + 4 + 8
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
	CSCORE_API const int32 All = 63; // 1 + 2 + 4 + 8 + 16 + 32
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

// ObjectPathDependencyGroup
#pragma region

namespace NCsObjectPathDependencyGroup
{
	namespace Ref
	{
		typedef EMCsObjectPathDependencyGroup EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Texture);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Material);
		CSCORE_API CS_ADD_TO_ENUM_MAP(StaticMesh);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Skeletal);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Sound);
		CSCORE_API CS_ADD_TO_ENUM_MAP(FX);
		CSCORE_API CS_ADD_TO_ENUM_MAP(AnimationAsset);
		CSCORE_API CS_ADD_TO_ENUM_MAP(AnimComposite);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Blueprint);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Sequencer);
		CSCORE_API CS_ADD_TO_ENUM_MAP(DataTable);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Other);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsObjectPathDependencyGroup_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsObjectPathDependencyGroup_MAX;
}

#pragma endregion ObjectPathDependencyGroup

// LoadAsyncOrder
#pragma region

namespace NCsLoadAsyncOrder
{
	namespace Ref
	{
		typedef EMCsLoadAsyncOrder EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(None);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstToLast, "First to Last");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Bulk);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsLoadAsyncOrder_MAX, "MAX");
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
	FCsLibraryLoad_GetObjectPaths Result;
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

#pragma endregion Payload

// DataEntry
#pragma region

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

		if (CS_CVAR_LOG_IS_SHOWING(LogPayloadPopulate))
		{
			UE_LOG(LogCs, Warning, TEXT("- Adding Path: %s [%s]."), *(Path.ToString()), *(PathAtId.Size.ToString()));
		}
	}

	// Get Paths for anything Data references
	FCsLibraryLoad_GetObjectPaths Result;
	
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
		FSetElementId Id = Paths.Set.Add(TempPath);
		FCsSoftObjectPath& PathAtId = Paths.Set[Id];

		PathAtId.Path = Path;

		if (Bytes > 0)
			PathAtId.Size.SetBytes(Bytes);

		if (CS_CVAR_LOG_IS_SHOWING(LogPayloadPopulate))
		{
			UE_LOG(LogCs, Warning, TEXT("---- [%d] [%s] %s @ %s."), I, *(PathAtId.Size.ToString()), *(Path.GetAssetName()), *(Path.GetAssetPathString()));
		}

		Size += PathAtId.Size;
		++I;
	}

	// Update internal structures for fast search / look up
	Paths.BuildFromSet();

	if (CS_CVAR_LOG_IS_SHOWING(LogPayloadPopulate))
	{
		UE_LOG(LogCs, Warning, TEXT("- Summary: Populated %d Paths [%s]."), Paths.Internal.Num(), *(Paths.Size.ToString()));
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
	FCsLibraryLoad_GetObjectPaths Result;
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

#endif // #if WITH_EDITOR

#pragma endregion FCsDataEntry_DataTable

#pragma endregion DataEntry