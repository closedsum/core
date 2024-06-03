// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsDataSettings.h"
#include "CsData.h"

// Types
#include "CsMacro_Misc.h"

#if WITH_EDITOR
// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "Data/CsTypes_DataEntry.h" // TODO: TEMP
// Library
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsTypes_Settings_Enum.h"
#include "Settings/ProjectPackagingSettings.h"
// Interface
#include "Data/CsGetDataRootSet.h"
#include "Data/Tool/CsGetDataEntryTool.h"
// Editor
#include "PackageTools.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsDataSettings)

// Cached
#pragma region

namespace NCsDataSettings
{
	namespace NCached
	{
		namespace Str
		{
			// Data
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsDataSettings, PopulateAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsDataSettings, PostEditChangeChainProperty);
		}
	}
}

#pragma endregion Cached

UCsDataSettings::UCsDataSettings(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// Data
	DataRootSet(),
	Manager_Data(),
	Data(),
	bOnEditorStartup_LoadDataRootSet(false)
{
}

#if WITH_EDITOR

void UCsDataSettings::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	Super::PostEditChangeProperty(e);
}

void UCsDataSettings::PostEditChangeChainProperty(FPropertyChangedChainEvent& e)
{
	using namespace NCsDataSettings::NCached;

	const FString& Context = Str::PostEditChangeChainProperty;

	const FName PropertyFName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FString PropertyName	   = (e.Property != NULL) ? e.Property->GetName() : TEXT("");
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	//int32 Index;

	typedef NCsProperty::FLibrary PropertyLibrary;

	TSet<FString> PropertyNames;
	PropertyLibrary::GetPropertyNamesInChain(e, PropertyNames);

	typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;

	// Data
	{
		if (PropertyNames.Contains("DataRootSets"))
		{
			// bApply
			if (PropertyNames.Contains("bApply"))
			{
				UProjectPackagingSettings* PackageSettings = GetMutableDefault<UProjectPackagingSettings>();

				const int32 Count = (int32)ECsPlatform::ECsPlatform_MAX;

				int32 Index = INDEX_NONE;

				// Add to DirectoriesToAlwaysCook
				for (int32 I = 0; I < Count; ++I)
				{
					FCsSettings_DataRootSet& Set = DataRootSets[I];

					if (Set.bApply)
					{
						DataRootSet = DataRootSets[I].DataRootSet;

						if (PackageSettings->DirectoriesToAlwaysCook.Num() == CS_EMPTY)
						{
							PackageSettings->DirectoriesToAlwaysCook.AddDefaulted();
						}
						PackageSettings->DirectoriesToAlwaysCook[CS_FIRST] = DataRootSets[I].DirectoryToAlwaysCook;

						Index = I;
						break;
					}
				}
				// Add to DirectoriesToNeverCook

					// First remove all directories in DataRootSets
				for (int32 I = 0; I < Count; ++I)
				{
					const FDirectoryPath& D1 = DataRootSets[I].DirectoryToAlwaysCook;

					int32 Num = PackageSettings->DirectoriesToNeverCook.Num();

					for (int32 J = Num - 1; J >= 0; --J)
					{
						FDirectoryPath& D2 = PackageSettings->DirectoriesToNeverCook[J];

						if (D2.Path == D1.Path)
						{
							PackageSettings->DirectoriesToNeverCook.RemoveAt(J);
						}
					}
				}
					// Get all directories to add to DirectoriesToNeverCook
				TArray<int32> PathsToAdd;

				for (int32 I = 0; I < Count; ++I)
				{
					if (DataRootSets[I].bApply)
						continue;

					if (PathsToAdd.Num() == CS_EMPTY)
					{
						PathsToAdd.Add(I);
					}
					else
					{
						bool Add = true;

						for (const int32& J : PathsToAdd)
						{	
							const FString& P  = DataRootSets[Index].DirectoryToAlwaysCook.Path;
							const FString& P1 = DataRootSets[I].DirectoryToAlwaysCook.Path;
							const FString& P2 = DataRootSets[J].DirectoryToAlwaysCook.Path;

							if (P1 == P ||
								P1 == P2)
							{
								Add = false;
							}
						}

						if (Add)
							PathsToAdd.Add(I);
					}
				}
					// Add directors to DirectoriesToNeverCook
				for (const int32& I : PathsToAdd)
				{
					PackageSettings->DirectoriesToNeverCook.Add(DataRootSets[I].DirectoryToAlwaysCook);
				}
				DataRootSets[Index].bApply = false;
			}
			// bPopulateAll
			else
			if (PropertyName.Contains("bPopulateAll"))
			{
				typedef NCsData::NEntry::NTool::FImpl DataEntryToolType;

				ICsGetDataEntryTool* GetDataEntryTool = CS_INTERFACE_CAST_CHECKED(GEngine, UEngine, ICsGetDataEntryTool);
				DataEntryToolType* DataEntryTool	  = GetDataEntryTool->GetDataEntryTool();

				UProjectPackagingSettings* PackageSettings = GetMutableDefault<UProjectPackagingSettings>();

				const int32 Count = (int32)ECsPlatform::ECsPlatform_MAX;

				int32 Index = INDEX_NONE;

				for (int32 I = 0; I < Count; ++I)
				{
					FCsSettings_DataRootSet& Set = DataRootSets[I];

					if (Set.bPopulateAll)
					{
						Index = I;

						TSoftClassPtr<UObject> SoftClass  = Set.DataRootSet;
						UClass* Class					  = SoftClass.LoadSynchronous();
						UObject* O						  = Class ? Class->GetDefaultObject<UObject>() : nullptr;
						ICsGetDataRootSet* GetDataRootSet = O ? Cast<ICsGetDataRootSet>(O) : nullptr;

						if (GetDataRootSet)
						{
							const FCsDataRootSet& CsDataRootSet = GetDataRootSet->GetCsDataRootSet();

							TArray<UObject*> ObjectsToSave;

							// Datas
							if (UDataTable* Datas = CsDataRootSet.Datas)
							{
								const TMap<FName, uint8*>& RowMap = Datas->GetRowMap();

								for (const TPair<FName, uint8*>& Pair : RowMap)
								{
									const FName& RowName	  = Pair.Key;
									FCsDataEntry_Data* RowPtr = reinterpret_cast<FCsDataEntry_Data*>(Pair.Value);

									RowPtr->Name = RowName;

									DataEntryTool->Data_PopulateImpl(RowPtr);
								}
								Datas->MarkPackageDirty();
								ObjectsToSave.Add(Datas);
							}
							// ScriptDatas
							if (UDataTable* ScriptDatas = CsDataRootSet.ScriptDatas)
							{
								const TMap<FName, uint8*>& RowMap = ScriptDatas->GetRowMap();

								for (const TPair<FName, uint8*>& Pair : RowMap)
								{
									const FName& RowName			= Pair.Key;
									FCsDataEntry_ScriptData* RowPtr = reinterpret_cast<FCsDataEntry_ScriptData*>(Pair.Value);

									RowPtr->Name = RowName;

									DataEntryTool->ScriptData_PopulateImpl(RowPtr);
								}
								ScriptDatas->MarkPackageDirty();
								ObjectsToSave.Add(ScriptDatas);
							}
							// DataTables
							if (UDataTable* DataTables = CsDataRootSet.DataTables)
							{
								const TMap<FName, uint8*>& RowMap = DataTables->GetRowMap();

								for (const TPair<FName, uint8*>& Pair : RowMap)
								{
									const FName& RowName		   = Pair.Key;
									FCsDataEntry_DataTable* RowPtr = reinterpret_cast<FCsDataEntry_DataTable*>(Pair.Value);

									RowPtr->Name = RowName;

									DataEntryTool->DataTable_PopulateImpl(DataTables, RowName, RowPtr, true);
								}
								DataTables->MarkPackageDirty();
								ObjectsToSave.Add(DataTables);
							}
							UPackageTools::SavePackagesForObjects(ObjectsToSave);
						}
						break;
					}
				}

				if (Index > INDEX_NONE)
					DataRootSets[Index].bPopulateAll = false;
			}
			// bPopulateSubset
			else
			if (PropertyName.Contains("bPopulateSubset"))
			{
				typedef NCsData::NEntry::NTool::FImpl DataEntryToolType;

				ICsGetDataEntryTool* GetDataEntryTool = CS_INTERFACE_CAST_CHECKED(GEngine, UEngine, ICsGetDataEntryTool);
				DataEntryToolType* DataEntryTool	  = GetDataEntryTool->GetDataEntryTool();

				UProjectPackagingSettings* PackageSettings = GetMutableDefault<UProjectPackagingSettings>();

				const int32 Count = (int32)ECsPlatform::ECsPlatform_MAX;

				int32 Index = INDEX_NONE;

				for (int32 I = 0; I < Count; ++I)
				{
					FCsSettings_DataRootSet& Set = DataRootSets[I];

					if (Set.bPopulateSubset)
					{
						Index = I;

						TSoftClassPtr<UObject> SoftClass  = Set.DataRootSet;
						UClass* Class					  = SoftClass.LoadSynchronous();
						UObject* O						  = Class ? Class->GetDefaultObject<UObject>() : nullptr;
						ICsGetDataRootSet* GetDataRootSet = O ? Cast<ICsGetDataRootSet>(O) : nullptr;

						if (GetDataRootSet)
						{
							const FCsDataRootSet& CsDataRootSet = GetDataRootSet->GetCsDataRootSet();

							TArray<UObject*> ObjectsToSave;

							// Datas
							if (UDataTable* Datas = CsDataRootSet.Datas)
							{
								const TMap<FName, uint8*>& RowMap = Datas->GetRowMap();

								for (const TPair<FName, uint8*>& Pair : RowMap)
								{
									const FName& RowName = Pair.Key;

									if (Set.DataRowsToPopulate.Find(RowName))
									{
										FCsDataEntry_Data* RowPtr = reinterpret_cast<FCsDataEntry_Data*>(Pair.Value);

										RowPtr->Name = RowName;

										DataEntryTool->Data_PopulateImpl(RowPtr);
									}
								}
								Datas->MarkPackageDirty();
								ObjectsToSave.Add(Datas);
							}
							// ScriptDatas
							if (UDataTable* ScriptDatas = CsDataRootSet.ScriptDatas)
							{
								const TMap<FName, uint8*>& RowMap = ScriptDatas->GetRowMap();

								for (const TPair<FName, uint8*>& Pair : RowMap)
								{
									const FName& RowName = Pair.Key;

									if (Set.DataRowsToPopulate.Find(RowName))
									{
										FCsDataEntry_ScriptData* RowPtr = reinterpret_cast<FCsDataEntry_ScriptData*>(Pair.Value);

										RowPtr->Name = RowName;

										DataEntryTool->ScriptData_PopulateImpl(RowPtr);
									}
								}
								ScriptDatas->MarkPackageDirty();
								ObjectsToSave.Add(ScriptDatas);
							}
							// DataTables
							if (UDataTable* DataTables = CsDataRootSet.DataTables)
							{
								const TMap<FName, uint8*>& RowMap = DataTables->GetRowMap();

								for (const TPair<FName, uint8*>& Pair : RowMap)
								{
									const FName& RowName = Pair.Key;

									if (Set.DataTableRowsToPopulate.Find(RowName))
									{
										FCsDataEntry_DataTable* RowPtr = reinterpret_cast<FCsDataEntry_DataTable*>(Pair.Value);

										RowPtr->Name = RowName;

										DataEntryTool->DataTable_PopulateImpl(DataTables, RowName, RowPtr, true);
									}
								}
								DataTables->MarkPackageDirty();
								ObjectsToSave.Add(DataTables);
							}
							UPackageTools::SavePackagesForObjects(ObjectsToSave);
						}
						break;
					}
				}

				if (Index > INDEX_NONE)
					DataRootSets[Index].bPopulateSubset = false;
			}
		}
	}

	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR

// Data
#pragma region

UObject* UCsDataSettings::LoadDataRootSetChecked(const FString& Context)
{
	const FSoftObjectPath& SoftPath = DataRootSet.ToSoftObjectPath();

	checkf(SoftPath.IsValid(), TEXT("%s: DataRootSet's Path is NOT Valid."), *Context);

	UClass* Class = DataRootSet.LoadSynchronous();

	checkf(Class, TEXT("%s: Failed to load DataRootSet @ Path: %s."), *Context, *(SoftPath.ToString()));

	UObject* DOb = Class->GetDefaultObject();

	checkf(DOb, TEXT("%s: Failed to get Default Object from DataRootSet @ Path: %s with Class: %s."), *Context, *(SoftPath.ToString()), *(Class->GetName()));
	return DOb;
}

UObject* UCsDataSettings::SafeLoadDataRootSet(const FString& Context)
{
	const FSoftObjectPath& SoftPath = DataRootSet.ToSoftObjectPath();

	if (!SoftPath.IsValid())
	{
		UE_LOG(LogCsData, Warning, TEXT("%s: DataRootSet's Path is NOT Valid."), *Context);
		return nullptr;
	}

	UClass* Class = DataRootSet.LoadSynchronous();

	if (!Class)
	{
		UE_LOG(LogCsData, Warning, TEXT("%s: Failed to load DataRootSet @ Path: %s."), *Context, *(SoftPath.ToString()));
		return nullptr;
	}

	UObject* DOb = Class->GetDefaultObject();

	if (!DOb)
	{
		UE_LOG(LogCsData, Warning, TEXT("%s: Failed to get Default Object from DataRootSet @ Path: %s with Class: %s."), *Context, *(SoftPath.ToString()), *(Class->GetName()));
		return nullptr;
	}
	return DOb;
}

#if WITH_EDITOR
void UCsDataSettings::PopulateAll(const ECsPlatform & Platform)
{
	using namespace NCsDataSettings::NCached;

	const FString& Context = Str::PopulateAll;

	FCsSettings_DataRootSet& Set = DataRootSets[(int32)Platform];

	TSoftClassPtr<UObject> SoftClass  = Set.DataRootSet;
	UClass* Class					  = SoftClass.LoadSynchronous();
	UObject* O						  = Class ? Class->GetDefaultObject<UObject>() : nullptr;
	ICsGetDataRootSet* GetDataRootSet = O ? Cast<ICsGetDataRootSet>(O) : nullptr;

	if (GetDataRootSet)
	{
		typedef NCsData::NEntry::NTool::FImpl DataEntryToolType;

		const FCsDataRootSet& CsDataRootSet   = GetDataRootSet->GetCsDataRootSet();
		ICsGetDataEntryTool* GetDataEntryTool = CS_INTERFACE_CAST_CHECKED(GEngine, UEngine, ICsGetDataEntryTool);
		DataEntryToolType* DataEntryTool	  = GetDataEntryTool->GetDataEntryTool();

		TArray<UObject*> ObjectsToSave;

		// Datas
		if (UDataTable* Datas = CsDataRootSet.Datas)
		{
			const TMap<FName, uint8*>& RowMap = Datas->GetRowMap();

			for (const TPair<FName, uint8*>& Pair : RowMap)
			{
				const FName& RowName	  = Pair.Key;
				FCsDataEntry_Data* RowPtr = reinterpret_cast<FCsDataEntry_Data*>(Pair.Value);

				RowPtr->Name = RowName;

				DataEntryTool->Data_PopulateImpl(RowPtr);
			}
		}
		// ScriptDatas
		if (UDataTable* ScriptDatas = CsDataRootSet.ScriptDatas)
		{
			const TMap<FName, uint8*>& RowMap = ScriptDatas->GetRowMap();

			for (const TPair<FName, uint8*>& Pair : RowMap)
			{
				const FName& RowName			= Pair.Key;
				FCsDataEntry_ScriptData* RowPtr = reinterpret_cast<FCsDataEntry_ScriptData*>(Pair.Value);

				RowPtr->Name = RowName;

				DataEntryTool->ScriptData_PopulateImpl(RowPtr);
			}
		}
		// DataTables
		if (UDataTable* DataTables = CsDataRootSet.DataTables)
		{
			const TMap<FName, uint8*>& RowMap = DataTables->GetRowMap();

			for (const TPair<FName, uint8*>& Pair : RowMap)
			{
				const FName& RowName		   = Pair.Key;
				FCsDataEntry_DataTable* RowPtr = reinterpret_cast<FCsDataEntry_DataTable*>(Pair.Value);

				RowPtr->Name = RowName;

				DataEntryTool->DataTable_PopulateImpl(DataTables, RowName, RowPtr, true);
			}
		}
	}
}
#endif // #if WITH_EDITOR

#pragma endregion Data