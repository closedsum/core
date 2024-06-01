// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsDeveloperSettings.h"
#include "CsCore.h"

#if WITH_EDITOR
// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "Data/CsTypes_DataEntry.h" // TODO: TEMP
// Library
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/ProjectPackagingSettings.h"
// Interface
#include "Data/CsGetDataRootSet.h"
#include "Data/Tool/CsGetDataEntryTool.h"
#include "Types/Enum/Tool/CsGetEnumStructTool.h"
// UI
//#include "Framework/Application/SlateApplication.h"
// Editor
#include "PackageTools.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsDeveloperSettings)

// Cached
#pragma region

namespace NCsDeveloperSettings
{
	namespace NCached
	{
		namespace Str
		{
			// Data
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsDeveloperSettings, PopulateAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsDeveloperSettings, PostEditChangeChainProperty);

			CSCORE_API CS_DEFINE_CACHED_STRING(InputActionMap, "UCsDeveloperSettings::InputActionMap");
			CSCORE_API CS_DEFINE_CACHED_STRING(GameEvent, "UCsDeveloperSettings::GameEvent");
			CSCORE_API CS_DEFINE_CACHED_STRING(Sound, "UCsDeveloperSettings::Sound");
			CSCORE_API CS_DEFINE_CACHED_STRING(StaticMeshActor, "UCsDeveloperSettings::StaticMeshActor");
			CSCORE_API CS_DEFINE_CACHED_STRING(SkeletalMeshActor, "UCsDeveloperSettings::SkeletalMeshActor");
			CSCORE_API CS_DEFINE_CACHED_STRING(VertexAnimNotify, "UCsDeveloperSettings::VertexAnimNotify");
		}
	}
}

#pragma endregion Cached

UCsDeveloperSettings::UCsDeveloperSettings(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// Enum
	EnumStructlayoutHistoryMap(),
	bEnumStructLayoutResolveChanges(false),
	bForceEnumStructLayoutResolveChanges(false),
	// Data
	DataRootSet(),
	Manager_Data(),
	Data(),
	bOnEditorStartup_LoadDataRootSet(false),
	// Input
	InputSystem(ECsInputSystem::Default),
	Input(),
	EnhancedInput(),
	Manager_Input(),
	// Script
	bEnableScriptChecked(false)
{
}

// Data
#pragma region

UObject* UCsDeveloperSettings::LoadDataRootSetChecked(const FString& Context)
{
	const FSoftObjectPath& SoftPath = DataRootSet.ToSoftObjectPath();

	checkf(SoftPath.IsValid(), TEXT("%s: DataRootSet's Path is NOT Valid."), *Context);

	UClass* Class = DataRootSet.LoadSynchronous();

	checkf(Class, TEXT("%s: Failed to load DataRootSet @ Path: %s."), *Context, *(SoftPath.ToString()));

	UObject* DOb = Class->GetDefaultObject();

	checkf(DOb, TEXT("%s: Failed to get Default Object from DataRootSet @ Path: %s with Class: %s."), *Context, *(SoftPath.ToString()), *(Class->GetName()));
	return DOb;
}

UObject* UCsDeveloperSettings::SafeLoadDataRootSet(const FString& Context)
{
	const FSoftObjectPath& SoftPath = DataRootSet.ToSoftObjectPath();

	if (!SoftPath.IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("%s: DataRootSet's Path is NOT Valid."), *Context);
		return nullptr;
	}

	UClass* Class = DataRootSet.LoadSynchronous();

	if (!Class)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Failed to load DataRootSet @ Path: %s."), *Context, *(SoftPath.ToString()));
		return nullptr;
	}

	UObject* DOb = Class->GetDefaultObject();

	if (!DOb)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Failed to get Default Object from DataRootSet @ Path: %s with Class: %s."), *Context, *(SoftPath.ToString()), *(Class->GetName()));
		return nullptr;
	}
	return DOb;
}

#if WITH_EDITOR
void UCsDeveloperSettings::PopulateAll(const ECsPlatform & Platform)
{
	using namespace NCsDeveloperSettings::NCached;

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

// Script
#pragma region

#if WITH_EDITOR

void UCsDeveloperSettings::ApplyEnableScriptChecked()
{
	CsCVarEnableScriptChecked->Set(bEnableScriptChecked, ECVF_SetByConsole);
}

#endif // #if WITH_EDITOR

#pragma endregion Script

#if WITH_EDITOR

void UCsDeveloperSettings::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	// bEnumStructLayoutResolveChanges
	if (PropertyName == FName("bEnumStructLayoutResolveChanges"))
	{
		if (ICsGetEnumStructTool* GetEnumStructTool = Cast<ICsGetEnumStructTool>(GEngine))
		{
			GetEnumStructTool->GetEnumStructTool().ResolveLayoutChangesImpl(false);
		}
		bEnumStructLayoutResolveChanges = false;
	}
	// bForceEnumStructLayoutResolveChanges
	if (PropertyName == FName("bForceEnumStructLayoutResolveChanges"))
	{
		if (ICsGetEnumStructTool* GetEnumStructTool = Cast<ICsGetEnumStructTool>(GEngine))
		{
			GetEnumStructTool->GetEnumStructTool().ResolveLayoutChangesImpl(true);
		}
		bForceEnumStructLayoutResolveChanges = false;
	}
	// bEnableScriptChecked
	if (PropertyName == FName("bEnableScriptChecked"))
	{
		ApplyEnableScriptChecked();
	}
	Super::PostEditChangeProperty(e);
}

void UCsDeveloperSettings::PostEditChangeChainProperty(FPropertyChangedChainEvent& e)
{
	using namespace NCsDeveloperSettings::NCached;

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
	// Input
	{
		// ECsInputActionMap
		if (PropertyName == TEXT("ECsInputActionMap"))
		{
			EnumSettingsLibrary::PopulateArrayFromString(ECsInputActionMap_Internal, ECsInputActionMap, EMCsInputActionMap::Get().GetEnumName());
			TryUpdateDefaultConfigFile();
		}
		// ECsGameEvent
		if (PropertyName == TEXT("ECsGameEvent"))
		{
			EnumSettingsLibrary::PopulateArrayFromString(ECsGameEvent_Internal, ECsGameEvent, EMCsGameEvent::Get().GetEnumName());
			TryUpdateDefaultConfigFile();
		}
		// Input
		if (PropertyNames.Contains("Input"))
		{
			Input.OnPostEditChange(PropertyName, PropertyNames);
		}
	}
	// PIE
	{
		if (PropertyNames.Contains("PIE") &&
			PropertyNames.Contains("bSwapViewportDimensions"))
		{
			PIE.SwapViewportDimensions();
		}
		else
		if (PropertyNames.Contains("PIE_Mobile") &&
			PropertyNames.Contains("bSwapViewportDimensions"))
		{
			PIE_Mobile.SwapViewportDimensions();
		}
		else
		if (PropertyNames.Contains("Standalone") &&
			PropertyNames.Contains("bSwapViewportDimensions"))
		{
			Standalone.SwapViewportDimensions();
		}
		else
		if (PropertyNames.Contains("Standalone_Mobile") &&
			PropertyNames.Contains("bSwapViewportDimensions"))
		{
			Standalone_Mobile.SwapViewportDimensions();
		}
	}

	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR