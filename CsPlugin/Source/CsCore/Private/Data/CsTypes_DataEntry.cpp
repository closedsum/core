// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsTypes_DataEntry.h"
#include "CsCore.h"

// Types
#include "CsMacro_Misc.h"
// CVar
#include "CsCVars_Core.h"
// Library
#include "Data/CsLibrary_Data.h"
	// Common
#include "Library/Load/CsLibrary_Load.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Data/CsSettings_Data.h"
// Data
#include "Data/CsGetDataRootSet.h"
#include "Data/CsTableRowBase_Data.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"

// DataEntryData
#pragma region

namespace NCsDataEntryData
{
	namespace NCached
	{
		namespace Str
		{
			const FString ConditionalAddLayout = TEXT("NCsDataEntryData::ConditionalAddLayout");

			const FString DataEntryData = TEXT("DataEntryData");
		}

		namespace Name
		{
			const FName Datas = FName("Datas");
		}
	}

	UDataTable* GetDataTable(const FString& Context)
	{
		using namespace NCsDataEntryData::NCached;

		typedef FCsPopulateEnumMapFromSettings EnumStructLibrary;

		return EnumStructLibrary::GetDataTable(Context, Name::Datas);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsDataEntryData::NCached;

		const FCsDataRootSet* DataRootSet = FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsDataRootSet, ICsGetDataRootSet, &ICsGetDataRootSet::GetCsDataRootSet>(Context, ContextRoot);

		if (!DataRootSet)
			return;

		typedef FCsPopulateEnumMapFromSettings::FFromDataTable::FPayload PayloadType;

		PayloadType Payload;
		Payload.ContextRoot				 = ContextRoot;
		Payload.DataTable				 = DataRootSet->GetDataTableChecked(Context, Name::Datas);
		Payload.EnumName				 = Str::DataEntryData;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &FCsLog::Warning;

		FCsPopulateEnumMapFromSettings::FromDataTable_RowAsName(Context, Payload);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsDataEntryData::Get().ClearUserDefinedEnums();

		FromDataTable(Context, ContextRoot);
	}

	#define LayoutLibrary NCsEnum::NStruct::NLayout::FLibrary

	void ConditionalAddLayout()
	{
		using namespace NCsDataEntryData::NCached;

		const FString& Context = Str::ConditionalAddLayout;

		FName EnumName;
		TArray<FName> Names;
		GetNames(EnumName, Names);
		LayoutLibrary::ConditionalAddLayout(EnumName, Names, GetDataTable(Context));
	}

	void AddPropertyChange()
	{
		ConditionalAddLayout();
		LayoutLibrary::AddPropertyChange(EMCsDataEntryData::Get().GetEnumFName(), FECsDataEntryData::StaticStruct());
	}

	#undef LayoutLibrary
}

#pragma endregion DataEntryData

// FCsDataEntry_Data
#pragma region

namespace NCsDataEntryData
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsDataEntry_Data, OnDataTableChanged);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsDataEntry_Data, Unload);
		}
	}
}

#define USING_NS_CACHED using namespace NCsDataEntryData::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsDataEntryData::NCached; \
	const FString& Context = Str::__FunctionName

// FTableRowBase Interface
#pragma region

void FCsDataEntry_Data::OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName)
{
	SET_CONTEXT(OnDataTableChanged);

	FCsSettings_Data_EnumStruct::Get().ECsDataEntryData.OnDataTableChanged(InDataTable, InRowName, Name, Data.GetAssetName());
}

#pragma endregion FTableRowBase Interface

// FCsTableRowBase_Data Interface
#pragma region

void FCsDataEntry_Data::Unload()
{
	SET_CONTEXT(Unload);

	if (IsValid(Data_Internal))
	{
		typedef NCsData::FLibrary DataLibrary;

		DataLibrary::UnloadChecked(Context, Data_Internal);
	}

	Data_Internal = nullptr;
	Data_Class = nullptr;
}

#pragma endregion FCsTableRowBase_Data Interface

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

UClass* FCsDataEntry_Data::SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) /*=&FCLog::Warning*/)
{
	return CS_SOFT_CLASS_PTR_LOAD(Data, UObject);
}

UObject* FCsDataEntry_Data::SafeLoadDefaultObject(const FString& Context, void(*Log)(const FString&) /*=&FCLog::Warning*/)
{
	if (UClass* Class = SafeLoadSoftClass(Context, Log))
	{
		if (UObject* DOb = Class->GetDefaultObject())
		{
			return DOb;
		}

		const FSoftObjectPath& Path = Data.ToSoftObjectPath();

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get DefaultObject for Data @ Path: %s with Class: %s."), *Context, *(Path.ToString()), *(Class->GetName())));
	}
	return nullptr;
}

#undef USING_NS_CACHED
#undef SET_CONTEXT

#pragma endregion FCsDataEntry_Data

// FCsDataEntry_ScriptData
#pragma region

namespace NCsDataEntryScriptData
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsDataEntry_ScriptData, Unload);
		}
	}
}

#define USING_NS_CACHED using namespace NCsDataEntryScriptData::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsDataEntryScriptData::NCached; \
	const FString& Context = Str::__FunctionName

// FCsTableRowBase_Data Interface
#pragma region

void FCsDataEntry_ScriptData::Unload()
{
	SET_CONTEXT(Unload);

	if (IsValid(Data_Internal))
	{
		typedef NCsData::FLibrary DataLibrary;

		DataLibrary::Script_UnloadChecked(Context, Data_Internal);
	}

	Data_Internal = nullptr;
	Data_Class = nullptr;
}

#pragma endregion FCsTableRowBase_Data Interface

#if WITH_EDITOR

void FCsDataEntry_ScriptData::Populate()
{
	Paths.Reset();

	if (!Data.ToSoftObjectPath().IsValid())
		return;

	UClass* Class = Data.LoadSynchronous();

	if (!Class)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsDataEntry_ScriptData::Populate: Failed to load Data at Path: %s"), *(Data.ToString()));
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

void FCsDataEntry_ScriptData::Populate(const TSet<FSoftObjectPath>& PathSet, const TArray<TSet<FSoftObjectPath>>& PathSetsByGroup)
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

#undef USING_NS_CACHED
#undef SET_CONTEXT

#pragma endregion FCsDataEntry_ScriptData

// FCsDataEntry_DataTable
#pragma region

namespace NCsDataEntryDataTable
{
	namespace NCached
	{
		namespace Str 
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsDataEntry_DataTable, Unload);
		}
	}
}

#define USING_NS_CACHED using namespace NCsDataEntryDataTable::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsDataEntryDataTable::NCached; \
	const FString& Context = Str::__FunctionName

// FCsTableRowBase_Data Interface
#pragma region

void FCsDataEntry_DataTable::Unload()
{
	SET_CONTEXT(Unload);

	typedef NCsObject::FLibrary ObjectLibrary;

	if (ObjectLibrary::IsValidObject(DataTable_Internal))
	{
		TArray<FCsTableRowBase_Data*> AllRows;
		DataTable_Internal->GetAllRows(Context, AllRows);

		for (FCsTableRowBase_Data* Row : AllRows)
		{
			Row->Unload();
		}
	}

	DataTable_Internal = nullptr;
}

#pragma endregion FCsTableRowBase_Data Interface

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
			PathsByGroup[(uint8)Group].Populate(Set, CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate));
		}
	}
}

#endif // #if WITH_EDITOR

#undef USING_NS_CACHED
#undef SET_CONTEXT

#pragma endregion FCsDataEntry_DataTable