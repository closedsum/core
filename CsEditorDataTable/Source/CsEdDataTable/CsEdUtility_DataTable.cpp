// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsEdUtility_DataTable.h"
#include "CsEdDataTable.h"

// Types
#include "CsEdTypes_DataTable.h"
// Settings
#include "CsEdDataTableSettings.h"
// Source Control
#include "SourceControlHelpers.h"
// Asset Tools
#include "AssetToolsModule.h"
// Asset Registry
#include "AssetRegistryModule.h"
// Asset Manager Editor
#include "Toolkits/AssetEditorManager.h"
// Unreal Ed
#include "ObjectTools.h"
// Editor
#include "Editor.h"
// CoreUObject
#include "UObject/UObjectGlobals.h"
// Data
#include "Engine/DataTable.h"

// Cached
#pragma region

namespace NCsEdUtilityDataTableCached
{
	namespace Str
	{
		const FString OnOpened = TEXT("FCsEdUtility_DataTable::OnOpened");
		const FString OnLoaded = TEXT("FCsEdUtility_DataTable::OnLoaded");
	}

	namespace Name
	{
		const FName DataTable = FName("DataTable");
	}
}

#pragma endregion Cached

bool FCsEdUtility_DataTable::bPIE = false;

// Delegates
#pragma region

void FCsEdUtility_DataTable::BindDelegates()
{
	// Editor Delegates
	FEditorDelegates::BeginPIE.AddStatic(&FCsEdUtility_DataTable::OnBeginPIE);
	FEditorDelegates::EndPIE.AddStatic(&FCsEdUtility_DataTable::OnEndPIE);
	//FEditorDelegates::OnAssetsPreDelete.AddUObject(this, &URsEdEngine::OnAssetsPreDelete);

	// Asset Registry Delegates
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry			  = AssetRegistryModule.Get();

	AssetRegistry.OnAssetRenamed().AddStatic(&FCsEdUtility_DataTable::OnAssetRenamed);
	//AssetRegistry.OnAssetRemoved().AddUObject(this, &URsEdEngine::OnAssetRemoved);

	// Asset Editor Manager
	FAssetEditorManager::Get().OnAssetEditorOpened().AddStatic(&FCsEdUtility_DataTable::OnAssetEditorOpened);

	// Core Delegates
	FCoreUObjectDelegates::OnObjectSaved.AddStatic(&FCsEdUtility_DataTable::OnObjectSaved);
	FCoreUObjectDelegates::OnAssetLoaded.AddStatic(&FCsEdUtility_DataTable::OnAssetLoaded);
}

	// Editor Delegates
#pragma region

#pragma region

void FCsEdUtility_DataTable::OnBeginPIE(bool IsSimulating)
{
	bPIE = true;
}

void FCsEdUtility_DataTable::OnEndPIE(bool IsSimulating)
{
	bPIE = false;
}

#pragma endregion Editor Delegates

// Asset Registry Delegates
#pragma region

void FCsEdUtility_DataTable::OnAssetRenamed(const FAssetData& AssetData, const FString& OldObjectPath)
{
	// DataTable
	if (AssetData.AssetClass == NCsEdUtilityDataTableCached::Name::DataTable)
	{
		OnRenamed(AssetData.ObjectPath, OldObjectPath);
	}
}

void FCsEdUtility_DataTable::OnAssetRemoved(const FAssetData& AssetData)
{
	// DataTable
	if (AssetData.AssetClass == NCsEdUtilityDataTableCached::Name::DataTable)
	{
		FCsEdUtility_DataTable::OnDelete(AssetData.ObjectPath);
	}
}

#pragma endregion Asset Registry Delegates

#pragma endregion Delegates

// Asset Editor Manager
#pragma region

void FCsEdUtility_DataTable::OnAssetEditorOpened(UObject* Object)
{
	// DataTable
	if (UDataTable* DataTable = Cast<UDataTable>(Object))
	{
		OnOpened(DataTable);
	}
}

#pragma endregion Asset Editor Manager

// Core Delegates
#pragma region

void FCsEdUtility_DataTable::OnObjectSaved(UObject* Object)
{
	if (!Object)
		return;

	// DataTable
	if (UDataTable* DataTable = Cast<UDataTable>(Object))
	{
		// Settings
		if (UCsEdDataTableSettings* Settings = GetMutableDefault<UCsEdDataTableSettings>())
		{
			// Import / Export
			ExportToTextFile(DataTable);
		}
	}
}

void FCsEdUtility_DataTable::OnAssetLoaded(UObject* Object)
{
	if (!Object)
		return;

	if (bPIE)
		return;

	if (Object->HasAllFlags(EObjectFlags::RF_KeepForCooker))
		return;

	// DataTable
	if (UDataTable* DataTable = Cast<UDataTable>(Object))
	{
		OnLoaded(DataTable);
	}
}

#pragma endregion Core Delegates

bool FCsEdUtility_DataTable::ExportToTextFile(UDataTable* DataTable)
{
	if (UCsEdDataTableSettings* Settings = GetMutableDefault<UCsEdDataTableSettings>())
	{
		const FString DataTableName = DataTable->GetName();
		FString PathName			= DataTable->GetPathName();

		bool NameFound	  = false;
		bool PathMismatch = false;

		FCsDataTableImportExportInfo* InfoPtr = nullptr;

		for (FCsDataTableImportExportInfo& Info : Settings->ImportExportInfos)
		{
			// If the asset was renamed, check if the name of the actual asset
			// is the same as the DataTable
			if (Info.DataTable.GetAssetName() == DataTableName)
			{
				NameFound = true;
			}

			// Check if the Path is the same
			if (Info.DataTable.ToString() == PathName)
			{
				InfoPtr = &Info;
				break;
			}
			else
			{
				// If the SAME Name if found, but there is a Path Mismatch
				// assume this is the same asset and the Path changed.
				if (NameFound)
				{
					PathMismatch = true;
					InfoPtr		 = &Info;
				}
			}
		}

		// If the same DataTable name was found but there was a mismatch in the path, 
		// probably due to the asset moving or being renamed, try to resolve the path.
		if (NameFound &&
			PathMismatch)
		{
			UDataTable* DT = InfoPtr->DataTable.LoadSynchronous();

			if (DataTable != DT)
			{
				InfoPtr->DataTable = DataTable;
			}
		}

		if (InfoPtr)
		{
			PathName = PathName.Replace(*FString::Printf(TEXT(".%s"), *DataTableName), TEXT(""));
			PathName = PathName.Replace(TEXT("/Game/"), TEXT(""));

			const FString ProjectContentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
			const FString FullPath			= ProjectContentDir + PathName;
			const FString Ext				= InfoPtr->FileType == ECsDataTableFileType::json ? TEXT(".json") : TEXT(".csv");
			const FString FileName			= FullPath + Ext;

			const FString& OldFileName = InfoPtr->FileName;

			// If FileName has changed, delete the old File @ FileName if it exists
			if (!OldFileName.IsEmpty() &&
				FileName != OldFileName)
			{
				// Check if FileName exists
				if (IFileManager::Get().FileExists(*OldFileName))
				{
					// Check if FileName can be deleted via Source Control
					FSourceControlState State = SourceControlHelpers::QueryFileState(OldFileName);

					if (State.bCanDelete)
					{
						if (!SourceControlHelpers::MarkFileForDelete(OldFileName))
						{
							UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::ExportToTextFile: Failed to delete FileName: %s via Source Control."), *OldFileName);

							if (!IFileManager::Get().Delete(*OldFileName))
							{
								UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::ExportToTextFile: Failed to delete FileName: %s."), *OldFileName);
							}
						}
					}
					// If NO Source Control, delete FileName
					else
					{
						if (!IFileManager::Get().Delete(*OldFileName))
						{
							UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::ExportToTextFile: Failed to delete FileName: %s."), *OldFileName);
						}
					}
				}
			}

			bool Success = false;
				
			// json
			if (InfoPtr->FileType == ECsDataTableFileType::json)
				Success = FFileHelper::SaveStringToFile(DataTable->GetTableAsJSON(EDataTableExportFlags::UsePrettyPropertyNames | EDataTableExportFlags::UsePrettyEnumNames | EDataTableExportFlags::UseJsonObjectsForStructs), *FileName);
			// csv
			else
				Success = FFileHelper::SaveStringToFile(DataTable->GetTableAsCSV(EDataTableExportFlags::UsePrettyPropertyNames | EDataTableExportFlags::UsePrettyEnumNames), *FileName);

			if (Success)
			{
				// If Source Control is available, Check Out / Add FileName
				if (SourceControlHelpers::IsAvailable())
				{
					if (!SourceControlHelpers::CheckOutOrAddFile(FileName))
					{
						UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::ExportToTextFile: Failed to Check Out or Add FileName: %s."), *FileName);
					}
				}

				InfoPtr->FileName = FileName;
				Settings->UpdateDefaultConfigFile();
				return true;
			}
			else
			{
				UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::ExportToTextFile: Failed to save DataTable: %s to FileName: %s."), *DataTableName, *FileName);
			}
		}
	}
	else
	{
		UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::ExportToTextFile: Settings of type: UCsDeveloperSettings."));
	}
	return false;
}

void FCsEdUtility_DataTable::OnRenamed(const FName& ObjectPath, const FString& OldObjectPath)
{
	if (UCsEdDataTableSettings* Settings = GetMutableDefault<UCsEdDataTableSettings>())
	{
		FString PathName = ObjectPath.ToString();

		for (FCsDataTableImportExportInfo& Info : Settings->ImportExportInfos)
		{
			if (Info.DataTable.ToString() == OldObjectPath)
			{
				// Delete OldFileName
				FString OldPathName = OldObjectPath;

				FString DataTableName = Info.DataTable.GetAssetName();

				OldPathName = OldPathName.Replace(*FString::Printf(TEXT(".%s"), *DataTableName), TEXT(""));
				OldPathName = OldPathName.Replace(TEXT("/Game/"), TEXT(""));

				const FString ProjectContentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
				FString OldFullPath				= ProjectContentDir + OldPathName;
				const FString Ext				= Info.FileType == ECsDataTableFileType::json ? TEXT(".json") : TEXT(".csv");
				const FString OldFileName		= OldFullPath + Ext;

				// Check if OldFileName exists
				if (IFileManager::Get().FileExists(*OldFileName))
				{
					// Check if OldFileName can be deleted via Source Control
					FSourceControlState State = SourceControlHelpers::QueryFileState(OldFileName);

					if (State.bCanDelete)
					{
						if (!SourceControlHelpers::MarkFileForDelete(OldFileName))
						{
							UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::OnRenamed: Failed to delete FileName: %s via Source Control."), *OldFileName);

							if (!IFileManager::Get().Delete(*OldFileName))
							{
								UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::OnRenamed: Failed to delete FileName: %s."), *OldFileName);
							}
						}
					}
					// If NO Source Control, delete OldFileName
					else
					{
						if (!IFileManager::Get().Delete(*OldFileName))
						{
							UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::OnRenamed: Failed to delete FileName: %s."), *OldFileName);
						}
					}
				}

				// Set new Path
				Info.DataTable = FSoftObjectPath(PathName);

				DataTableName = Info.DataTable.GetAssetName();

				// Save FileName
				PathName = PathName.Replace(*FString::Printf(TEXT(".%s"), *DataTableName), TEXT(""));
				PathName = PathName.Replace(TEXT("/Game/"), TEXT(""));

				const FString FullPath = ProjectContentDir + PathName;
				const FString FileName = FullPath + Ext;

				bool Success = false;

				UDataTable* DataTable = Info.DataTable.LoadSynchronous();

				// json
				if (Info.FileType == ECsDataTableFileType::json)
					Success = FFileHelper::SaveStringToFile(DataTable->GetTableAsJSON(EDataTableExportFlags::UsePrettyPropertyNames | EDataTableExportFlags::UsePrettyEnumNames | EDataTableExportFlags::UseJsonObjectsForStructs), *FileName);
				// csv
				else
					Success = FFileHelper::SaveStringToFile(DataTable->GetTableAsCSV(EDataTableExportFlags::UsePrettyPropertyNames | EDataTableExportFlags::UsePrettyEnumNames), *FileName);

				if (Success)
				{
					// If Source Control is available, Check Out / Add FileName
					if (SourceControlHelpers::IsAvailable())
					{
						if (!SourceControlHelpers::CheckOutOrAddFile(FileName))
						{
							UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::OnRenamed: Failed to Check Out or Add FileName: %s."), *FileName);
						}
					}
					Info.FileName = FileName;
					Settings->UpdateDefaultConfigFile();
				}
				else
				{
					UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::OnRenamed: Failed to save DataTable: %s to FileName: %s."), *DataTableName, *FileName);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::OnRenamed: Settings of type: UCsDeveloperSettings."));
	}
}

void FCsEdUtility_DataTable::OnDelete(const FName& ObjectPath)
{
	if (UCsEdDataTableSettings* Settings = GetMutableDefault<UCsEdDataTableSettings>())
	{
		FString PathName = ObjectPath.ToString();

		FCsDataTableImportExportInfo* InfoPtr = nullptr;

		for (FCsDataTableImportExportInfo& Info : Settings->ImportExportInfos)
		{
			const FString DataTableName = Info.DataTable.GetAssetName();

			if (Info.DataTable.ToString() == PathName)
			{
				PathName = PathName.Replace(*FString::Printf(TEXT(".%s"), *DataTableName), TEXT(""));
				PathName = PathName.Replace(TEXT("/Game/"), TEXT(""));

				const FString ProjectContentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
				const FString FullPath			= ProjectContentDir + PathName;
				const FString Ext				= Info.FileType == ECsDataTableFileType::json ? TEXT(".json") : TEXT(".csv");
				const FString FileName			= FullPath + Ext;

				const FString& OtherFileName = Info.FileName;

				TArray<FString> FilesToDelete;
				
				FilesToDelete.Add(FileName);

				// If FileName != OtherFileName, delete both if they exist
				if (!OtherFileName.IsEmpty() &&
					FileName != OtherFileName)
				{
					FilesToDelete.Add(OtherFileName);
				}

				for (const FString& File : FilesToDelete)
				{
					// Check if FileName exists
					if (IFileManager::Get().FileExists(*File))
					{
						// Check if FileName can be deleted via Source Control
						FSourceControlState State = SourceControlHelpers::QueryFileState(File);

						if (State.bCanDelete)
						{
							if (!SourceControlHelpers::MarkFileForDelete(File))
							{
								UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::OnDelete: Failed to delete FileName: %s via Source Control."), *File);

								if (!IFileManager::Get().Delete(*File))
								{
									UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::OnDelete: Failed to delete FileName: %s."), *File);
								}
							}
						}
						// If NO Source Control, delete FileName
						else
						{
							if (!IFileManager::Get().Delete(*File))
							{
								UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::OnDelete: Failed to delete FileName: %s."), *File);
							}
						}
					}
				}

				InfoPtr = &Info;
				break;
			}
		}

		if (InfoPtr)
		{
			Settings->ImportExportInfos.Remove(*InfoPtr);
			Settings->UpdateDefaultConfigFile();
		}
	}
	else
	{
		UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::OnDelete: Settings of type: UCsDeveloperSettings."));
	}
}

void FCsEdUtility_DataTable::OnOpened(UDataTable* DataTable)
{
	LoadFromTextFile(NCsEdUtilityDataTableCached::Str::OnOpened, DataTable);
}

void FCsEdUtility_DataTable::OnLoaded(UDataTable* DataTable)
{
	LoadFromTextFile(NCsEdUtilityDataTableCached::Str::OnLoaded, DataTable);
}

void FCsEdUtility_DataTable::LoadFromTextFile(const FString& Context, UDataTable* DataTable)
{
	if (UCsEdDataTableSettings* Settings = GetMutableDefault<UCsEdDataTableSettings>())
	{
		const FString DataTableName = DataTable->GetName();
		FString PathName			= DataTable->GetPathName();

		for (FCsDataTableImportExportInfo& Info : Settings->ImportExportInfos)
		{
			// Check if the Path is the same
			if (Info.DataTable.ToString() == PathName)
			{
				FString Contents;

				if (FFileHelper::LoadFileToString(Contents, *Info.FileName))
				{
					// Duplicate the DataTable to see if it should actually be dirty
					const FString TempName		  = TEXT("__TEMP__") + DataTableName;
					UDataTable* OriginalDataTable = DuplicateObject<UDataTable>(DataTable, nullptr, FName(*TempName));

					if (!OriginalDataTable)
					{
						UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::%s: Failed to duplicated DataTable: %s."), *Context, *DataTableName);
					}

					// json
					if (Info.FileType == ECsDataTableFileType::json)
					{
						TArray<FString> Problems = DataTable->CreateTableFromJSONString(Contents);

						if (Problems.Num() > CS_EMPTY)
						{
							UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::%s: Problems with creating DataTable: %s from File: %s."), *Context, *DataTableName, *Info.FileName);

							for (const FString& Problem : Problems)
							{
								UE_LOG(LogCsEdDataTable, Warning, TEXT("- %s."), *Problem);
							}
						}
					}
					// csv
					else
					if (Info.FileType == ECsDataTableFileType::csv)
					{
						TArray<FString> Problems = DataTable->CreateTableFromCSVString(Contents);

						if (Problems.Num() > CS_EMPTY)
						{
							UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::%s: Problems with creating DataTable: %s from File: %s."), *Context, *DataTableName, *Info.FileName);

							for (const FString& Problem : Problems)
							{
								UE_LOG(LogCsEdDataTable, Warning, TEXT("- %s."), *Problem);
							}
						}
					}

					// If DataTable has NOT changed, UNDO the Dirty Flag
					if (AreContentsEqual(DataTable, OriginalDataTable))
					{
						if (UPackage* Package = DataTable->GetOutermost())
						{
							Package->SetDirtyFlag(false);
							Package->PackageMarkedDirtyEvent.Broadcast(Package, false);
						}
					}

					// Delete the TEMP DataTable
					if (OriginalDataTable)
						ObjectTools::DeleteSingleObject(OriginalDataTable, false);
				}
				else
				{
					UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::%s: Failed to load File: %s for DataTable: %s."), *Context, *Info.FileName, *DataTableName);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogCsEdDataTable, Warning, TEXT("FCsEdUtility_DataTable::%s: Settings of type: UCsDeveloperSettings."), *Context);
	}
}

bool FCsEdUtility_DataTable::AreContentsEqual(UDataTable* A, UDataTable* B)
{
	if (!A && !B)
		return true;

	if (!A || !B)
		return false;

	const TMap<FName, uint8*>& RowMapA = A->GetRowMap();
	const TMap<FName, uint8*>& RowMapB = B->GetRowMap();

	if (RowMapA.Num() != RowMapB.Num())
		return false;

	const UScriptStruct* RowStructA = A->GetRowStruct();
	const UScriptStruct* RowStructB = B->GetRowStruct();

	if (RowStructA != RowStructB)
		return false;

	struct FPropertyAndValue
	{
	public:

		UProperty * Property;
		void* Value;

		FPropertyAndValue() :
			Property(nullptr),
			Value(nullptr)
		{
		}
	};

	TArray<FPropertyAndValue> PropertyAndValuesA;
	TArray<FPropertyAndValue> PropertyAndValuesB;

	for (const TPair<FName, uint8*>& Pair : RowMapA)
	{
		const FName& RowNameA = Pair.Key;
		uint8* RowPtrA		  = Pair.Value;

		uint8* const* Ptr = RowMapB.Find(RowNameA);

		if (!Ptr)
			return false;

		uint8* RowPtrB = *Ptr;

		// Get list of all Properties and Values for Row A
		PropertyAndValuesA.Reset(PropertyAndValuesA.Max());
	
		for (TPropertyValueIterator<UProperty> It(RowStructA, RowPtrA); It; ++It)
		{
			PropertyAndValuesA.AddDefaulted();
			FPropertyAndValue& Last = PropertyAndValuesA.Last();

			Last.Property = It.Key();
			Last.Value	  = const_cast<void*>(It.Value());
		}

		// Get list of all Properties and Values for Row B
		PropertyAndValuesB.Reset(PropertyAndValuesB.Max());

		for (TPropertyValueIterator<UProperty> It(RowStructA, RowPtrB); It; ++It)
		{
			PropertyAndValuesB.AddDefaulted();
			FPropertyAndValue& Last = PropertyAndValuesB.Last();

			Last.Property = It.Key();
			Last.Value	  = const_cast<void*>(It.Value());
		}

		// Check if the Values between Row A and Row B are the same
		const int32 Count = PropertyAndValuesA.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			UProperty* Property = PropertyAndValuesA[I].Property;
			void* ValueA		= PropertyAndValuesA[I].Value;
			void* ValueB		= PropertyAndValuesB[I].Value;

			if (!Property->Identical(ValueA, ValueB))
				return false;
		}
	}
	return true;
}