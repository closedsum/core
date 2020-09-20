// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsEdEngine.h"
#include "CsEditor.h"
#include "CsCVars.h"

// Type
#include "Types/CsTypes_Load.h"
#include "Managers/Input/CsTypes_Input.h"
#include "Library/Load/CsTypes_Library_Load.h"
// Enum
#include "Types/Enum/CsEnumStructUserDefinedEnumMap.h"
// Library
#include "Library/CsLibrary_Common.h"
#include "Library/CsLibrary_Asset.h"
#include "Library/CsLibrary_String.h"
#include "Library/Load/CsLibrary_Load.h"
// Asset Registry
#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"

#include "Factories/BlueprintFactory.h"
// Data
//#include "Data/CsDataMapping.h"
//#include "Data/CsData.h"
#include "Data/CsGetDataRootSet.h"
// Setting
#include "Settings/CsDeveloperSettings.h"
// Property
#include "DetailCustomizations/CsRegisterDetailCustomization.h"
// Level
#include "Level/CsLevelScriptActor.h"


#include "Editor/UnrealEd/Public/Editor.h"

#include "Engine/UserDefinedEnum.h"

// Cache
#pragma region

namespace NCsEdEngineCached
{
	namespace Str
	{
		const FString OnObjectSaved_Update_DataRootSet_DataTables = TEXT("UCsEdEngine::OnObjectSaved_Update_DataRootSet_DataTables");
		const FString OnObjectSaved_Update_DataRootSet_Payloads = TEXT("UCsEdEngine::OnObjectSaved_Update_DataRootSet_Payloads");
		const FString OnObjectSaved_Update_DataRootSet_Payload = TEXT("UCsEdEngine::OnObjectSaved_Update_DataRootSet_Payload");
	}
}

#pragma endregion Cache

// UEngine Interface
#pragma region

void UCsEdEngine::Init(IEngineLoop* InEngineLoop)
{
	Super::Init(InEngineLoop);

	FCsRegisterDetailCustomization::Register();

	FEditorDelegates::BeginPIE.AddUObject(this, &UCsEdEngine::OnBeginPIE);
	FCoreUObjectDelegates::OnObjectSaved.AddUObject(this, &UCsEdEngine::OnObjectSaved);
}

void UCsEdEngine::PreExit()
{
	Super::PreExit();
}

void UCsEdEngine::Tick(float DeltaSeconds, bool bIdleMode)
{
	Super::Tick(DeltaSeconds, bIdleMode);
}

#pragma endregion UEngine Interface

// FExec Interface
#pragma region

bool UCsEdEngine::Exec(UWorld* InWorld, const TCHAR* Stream, FOutputDevice& Ar)
{
	if (Super::Exec(InWorld, Stream, Ar))
		return true;

	// Data
	{
		if (Check_MarkDatasDirty(Stream))
			return true;
	}
	// References
	{
		if (Check_PrintBlueprintReferencesReport(Stream))
			return true;
	}
	return true;
}

#pragma endregion FExec Interface

void UCsEdEngine::OnBeginPIE(bool IsSimulating)
{
	FCsCVarLogMap::Get().ResetDirty();
	//FCsCVarToggleMap::Get().ResetDirty();
}

// Save
#pragma region

void UCsEdEngine::OnObjectSaved(UObject* Object)
{
	if (!Object)
		return;

	// DataTable
	if (UDataTable* DataTable = Cast<UDataTable>(Object))
	{
		// Settings
		if (UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>())
		{
			TSoftClassPtr<UObject> SoftClass  = Settings->DataRootSet;
			UClass* Class					  = SoftClass.LoadSynchronous();
			UObject* O						  = Class ? Class->GetDefaultObject<UObject>() : nullptr;
			ICsGetDataRootSet* GetDataRootSet = O ? Cast<ICsGetDataRootSet>(O) : nullptr;

			// DataRootSet
			if (GetDataRootSet)
			{
				const FCsDataRootSet& DataRootSet = GetDataRootSet->GetCsDataRootSet();

				// Datas
				if (DataTable == DataRootSet.Datas)
				{
					if (FCsDataEntry_Data::StaticStruct() == DataTable->GetRowStruct())
					{
						OnObjectSaved_Update_DataRootSet_Datas(DataTable);
					}
					else
					{
						UE_LOG(LogCsEditor, Warning, TEXT("UCsEdEngine::OnObjectSaved: DataRootSet: %s DataTables: %s RowStruct: %s != FCsDataEntry_Data."), *(O->GetName()), *(DataTable->GetName()), *(DataTable->GetRowStruct()->GetName()));
					}
				}
				// DataTables
				if (DataTable == DataRootSet.DataTables)
				{
					if (FCsDataEntry_DataTable::StaticStruct() == DataTable->GetRowStruct())
					{
						OnObjectSaved_Update_DataRootSet_DataTables(DataTable);
					}
					else
					{
						UE_LOG(LogCsEditor, Warning, TEXT("UCsEdEngine::OnObjectSaved: DataRootSet: %s DataTables: %s RowStruct: %s != FCsDataEntry_DataTable."), *(O->GetName()), *(DataTable->GetName()), *(DataTable->GetRowStruct()->GetName()));
					}
				}
				// Payloads
				if (DataTable == DataRootSet.Payloads)
				{
					if (FCsPayload::StaticStruct() == DataTable->GetRowStruct())
					{
						OnObjectSaved_Update_DataRootSet_Payloads(DataTable);
					}
					else
					{
						UE_LOG(LogCsEditor, Warning, TEXT("UCsEdEngine::OnObjectSaved: DataRootSet: %s Payloads: %s RowStruct: %s != FCsPayload."), *(O->GetName()), *(DataTable->GetName()), *(DataTable->GetRowStruct()->GetName()));
					}
				}
			}
		}
	}
	// LevelScriptActor
	if (ACsLevelScriptActor* LevelScriptActor = Cast<ACsLevelScriptActor>(Object))
	{
		OnObjectSaved_Update_DataRootSet_Payload(LevelScriptActor->Payload);
	}
}

#pragma endregion Save

// Stream
#pragma region

bool UCsEdEngine::Stream_GetString(const TCHAR*& Str, const FString& StringType, FString& OutString, const FString& Check, const FString& Format)
{
	OutString = UCsLibrary_Common::Stream_GetString(Str, false);

	if (OutString == TEXT(""))
	{
		UE_LOG(LogCsEditor, Warning, TEXT("Check_%s: No %s set."), *Check, *StringType);
		UE_LOG(LogCsEditor, Warning, TEXT("Check_%s: The correct format is %s"), *Check, *Format);
		return false;
	}
	return true;
}

#pragma endregion

// Data
#pragma region

bool UCsEdEngine::Check_MarkDatasDirty(const TCHAR* Stream)
{
	const FString Command	 = TEXT("MarkDatasDirty");
	const FString Parameters = TEXT("[assetType=optional]");
	const FString Format	 = Command + TEXT(" ") + Parameters;

	if (FParse::Command(&Stream, *Command))
	{
		// AssetType
		const FString AssetTypeAsString = UCsLibrary_Common::Stream_GetString(Stream, false);
		const FECsAssetType AssetType   = EMCsAssetType::Get().GetSafeEnum(AssetTypeAsString);

		MarkDatasDirty(AssetType);
		return true;
	}
	return false;
}

void UCsEdEngine::MarkDatasDirty(const FECsAssetType& AssetType)
{
	/*
	TArray<ACsData*> Datas;

	UClass* Class = (*GetAssetTypeStaticClass)(AssetType);

	UCsLibrary_Asset::GetBlueprintDefaultObjects<ACsData>(TEXT("bp_"), ECsStringCompare::StartsWith, Datas, Class);

	const int32 Count = Datas.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		ACsData* Data = Datas[I];

		Data->MarkPackageDirty();

		const FString Name = TEXT(".") + Data->GetName();
		FString Path	   = Data->GetPathName();
		Path.RemoveFromEnd(Name);

		UE_LOG(LogCsEditor, Log, TEXT("MarkAllDatasDirty: %s is marked DIRTY."), *Path);
	}
	*/
}

#pragma endregion Data

// DataRootSet
#pragma region

void UCsEdEngine::OnObjectSaved_Update_DataRootSet_Datas(UDataTable* DataTable)
{
	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& RowName	  = Pair.Key;
		FCsDataEntry_Data* RowPtr = reinterpret_cast<FCsDataEntry_Data*>(Pair.Value);

		RowPtr->Name = RowName;

		if (RowPtr->bPopulateOnSave)
		{
			RowPtr->Populate();

			RowPtr->bPopulateOnSave = false;
		}
	}
}

void UCsEdEngine::OnObjectSaved_Update_DataRootSet_DataTables(UDataTable* DataTable)
{
	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();
	
	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& RowName		   = Pair.Key;
		FCsDataEntry_DataTable* RowPtr = reinterpret_cast<FCsDataEntry_DataTable*>(Pair.Value);

		RowPtr->Name = RowName;

		if (RowPtr->bPopulateOnSave)
		{
			RowPtr->Populate();

			RowPtr->bPopulateOnSave = false;
		}
	}
}

void UCsEdEngine::OnObjectSaved_Update_DataRootSet_Payloads(UDataTable* DataTable)
{
	// Get Settings
	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	if (!Settings)
		return;

	// Get DataRootSet
	TSoftClassPtr<UObject> SoftObject	= Settings->DataRootSet;
	UClass* Class						= SoftObject.LoadSynchronous();
	UObject* Object						= Class ? Class->GetDefaultObject<UObject>() : nullptr;
	ICsGetDataRootSet* GetDataRootSet	= Object ? Cast<ICsGetDataRootSet>(Object) : nullptr;

	if (!GetDataRootSet)
		return;

	// See which Payloads to push to Datas | DataTables
	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& RowName = Pair.Key;
		FCsPayload* RowPtr	 = reinterpret_cast<FCsPayload*>(Pair.Value);

		OnObjectSaved_Update_DataRootSet_Payload(*RowPtr);
	}
}

void UCsEdEngine::OnObjectSaved_Update_DataRootSet_Payload(FCsPayload& Payload)
{
	using namespace NCsEdEngineCached;

	const FString& Context = Str::OnObjectSaved_Update_DataRootSet_Payload;

	// Get Settings
	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	if (!Settings)
		return;

	// Get DataRootSet
	TSoftClassPtr<UObject> SoftObject	= Settings->DataRootSet;
	UClass* Class						= SoftObject.LoadSynchronous();
	UObject* Object						= Class ? Class->GetDefaultObject<UObject>() : nullptr;
	ICsGetDataRootSet* GetDataRootSet	= Object ? Cast<ICsGetDataRootSet>(Object) : nullptr;

	if (!GetDataRootSet)
		return;

	// Add / Update the Payload to the Datas | DataTables
	if (Payload.bUpdateDataRootSetOnSave)
	{
		FCsDataRootSet& DataRootSet = const_cast<FCsDataRootSet&>(GetDataRootSet->GetCsDataRootSet());

		// Datas

		// DataTables
		if (UDataTable* DataTables = DataRootSet.DataTables)
		{
			for (FCsPayload_DataTable& Payload_DataTable : Payload.DataTables)
			{
				// Check Name is Valid
				const FName& Name = Payload_DataTable.Name;

				if (Name == NAME_None)
				{
					UE_LOG(LogCsEditor, Warning, TEXT("%s: Name is NOT Valid."), *Context);
					continue;
				}

				// Check for Valid Path
				TSoftObjectPtr<UDataTable>& DT = Payload_DataTable.DataTable;
				const FSoftObjectPath& Path	   = DT.ToSoftObjectPath();

				if (!Path.IsValid())
				{
					UE_LOG(LogCsEditor, Warning, TEXT("%s: Path is NOT Valid for Name: %s."), *Context, *(Name.ToString()));
					continue;
				}

				// Add to Map of DataTables to Add to DataRootSet->DataTables
				if (Payload_DataTable.bAllRows)
					DataRootSet.AddDataTable(Name, DT);
				else
					DataRootSet.AddDataTable(Name, DT, Payload_DataTable.Rows);
			}
		}
	}
	Payload.bUpdateDataRootSetOnSave = false;
}

#pragma endregion DataRootSet

// References
#pragma region

bool UCsEdEngine::Check_PrintBlueprintReferencesReport(const TCHAR* Stream)
{
	const FString Command	 = TEXT("PrintReferencesReport");
	const FString Parameters = TEXT("[assetname]");
	const FString Format	 = Command + TEXT(" ") + Parameters;

	if (FParse::Command(&Stream, *Command))
	{
		const FName AssetName = UCsLibrary_String::Stream_GetName(Stream);

		if (AssetName == NAME_None)
		{
			return false;
		}

		PrintBlueprintReferencesReport(AssetName);
		return true;
	}
	return false;
}

void UCsEdEngine::PrintBlueprintReferencesReport(const FName& AssetName)
{
	UBlueprint* Bp = UCsLibrary_Asset::FindObjectByClass<UBlueprint>(FName("Blueprint"), AssetName, ECsFindObjectByClassRule::Exact);

	const FString AssetNameAsString = AssetName.ToString();

	if (!Bp)
	{
		UE_LOG(LogCsEditor, Warning, TEXT("UCsEdEngine::PrintBlueprintReferencesReport: Failed to find Blueprint with name: %s."), *AssetNameAsString);
		return;
	}

	const FString Path = Bp->GetPathName();

	UClass* Class = Bp->GeneratedClass.Get();
	
	if (!Class)
	{
		UE_LOG(LogCsEditor, Warning, TEXT("UCsEdEngine::PrintBlueprintReferencesReport: Failed to find Class for Blueprint: %s @ %s."), *AssetNameAsString, *Path);
		return;
	}

	UObject* DOb = Class->GetDefaultObject();

	if (!DOb)
	{
		UE_LOG(LogCsEditor, Warning, TEXT("UCsEdEngine::PrintBlueprintReferencesReport: Failed to find Default Object for Blueprint: %s @ %s."), *AssetNameAsString, *Path);
		return;
	}

	FCsLibraryLoad_GetReferencesReport Report;
	Report.Name = AssetNameAsString;
	Report.Path = Path;
	
	// If Actor, Spawn Actor in World
	if (Class->IsChildOf(AActor::StaticClass()))
	{
		if (GEditor)
		{
			const TArray<FEditorViewportClient*>& Clients = GEditor->GetAllViewportClients();

			for (FEditorViewportClient* Client : Clients)
			{
				UWorld* World = Client->GetWorld();

				if (World &&
					World->WorldType == EWorldType::Editor)
				{
					AActor* A = World->SpawnActor(Class);

					FCsLibraryLoad_GetObjectPaths OutPaths;
					OutPaths.SetRootName(AssetNameAsString);

					//UCsLibrary_Load::GetObjectPaths(Cast<UObject>(A), Class, OutPaths);

					OutPaths.Print();
					A->Destroy();
					break;
				}
			}
		}
	}
	// Object
	else
	{
		FCsLibraryLoad_GetObjectPaths OutPaths;
		OutPaths.SetRootName(AssetNameAsString);

		//UCsLibrary_Load::GetObjectPaths(DOb, DOb->GetClass(), OutPaths);
	}
}

#pragma endregion References
