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

#include "Classes/Factories/BlueprintFactory.h"
// Data
//#include "Data/CsDataMapping.h"
//#include "Data/CsData.h"
#include "Managers/Data/CsDataRootSet.h"
// Setting
#include "Settings/CsDeveloperSettings.h"
// Property
#include "DetailCustomizations/CsRegisterDetailCustomization.h"


#include "Editor/UnrealEd/Public/Editor.h"

#include "Classes/Engine/UserDefinedEnum.h"

#include "Enum/CsEnumEditorUtils.h"

// Cache
#pragma region

namespace NCsEdEngineCached
{
	namespace Str
	{
		const FString OnObjectSaved_DataRootSet_DataTables = TEXT("UCsEdEngine::OnObjectSaved_DataRootSet_DataTables");
		const FString OnObjectSaved_DataRootSet_Payloads = TEXT("UCsEdEngine::OnObjectSaved_DataRootSet_Payloads");
	}
}

#pragma endregion Cache

// UEngine Interface
#pragma region

void UCsEdEngine::Init(IEngineLoop* InEngineLoop)
{
	Super::Init(InEngineLoop);

	FCsRegisterDetailCustomization::Register();

	bTickedHandle.Set(&bTicked);
	bTickedHandle.OnChange_Event.AddUObject(this, &UCsEdEngine::OnFirstTick);

	GEditor->OnBlueprintPreCompile().AddUObject(this, &UCsEdEngine::OnBlueprintPreCompile);

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

	bTickedHandle = true;

	OnBlueprintPreCompile_HandleEnums_Mutex.Unlock();
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

// Tick
#pragma region

void UCsEdEngine::OnFirstTick(const bool& Value)
{
	//PopulateUserDefinedEnums();
	//PopulateEnumMapsFromUserDefinedEnums();

	/*
	if (!DataMapping)
	{
		DataMapping = UCsLibrary_Asset::GetDataMapping();

		if (DataMapping)
			DataMapping->GenerateMaps();
	}
	*/
}

#pragma endregion Tick

void UCsEdEngine::OnBlueprintPreCompile(UBlueprint* Blueprint)
{
	if (!bTicked)
		return;

	//OnBlueprintPreCompile_HandleEnums();
}

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
			FCsDataRootSetContainer& Container = Settings->DataRootSet;
			UClass* Class					   = Container.Data.LoadSynchronous();
			UCsDataRootSet* DataRootSet		   = Class ? Class->GetDefaultObject<UCsDataRootSet>() : nullptr;

			// DataRootSet
			if (DataRootSet)
			{
				// DataTables
				if (UDataTable* DataTables = DataRootSet->DataTables)
				{
					if (FCsDataEntry_DataTable::StaticStruct() == DataTables->GetRowStruct())
					{
						OnObjectSaved_DataRootSet_DataTables(DataTables);
					}
				}
			}
		}
	}
}

#pragma endregion Save

// Enums
#pragma region

UCsEnumStructUserDefinedEnumMap* UCsEdEngine::GetEnumStructUserDefinedEnumMap()
{
	if (EnumStructUserDefinedEnumMap.IsValid() && EnumStructUserDefinedEnumMap.Get())
	{
		return EnumStructUserDefinedEnumMap.Get();
	}

	EnumStructUserDefinedEnumMap = UCsLibrary_Asset::GetEnumStructUserDefinedEnumMap();

	return EnumStructUserDefinedEnumMap.Get();
}

void UCsEdEngine::OnBlueprintPreCompile_HandleEnums()
{
	if (OnBlueprintPreCompile_HandleEnums_Mutex.IsLocked())
		return;

	OnBlueprintPreCompile_HandleEnums_Mutex.Lock();


	PopulateUserDefinedEnums();
	PopulateEnumMapsFromUserDefinedEnums();
}

void UCsEdEngine::PopulateUserDefinedEnums()
{
	PopulateUserDefinedEnum_InputAction();
}

void UCsEdEngine::PopulateUserDefinedEnum_InputAction()
{
	FCsEnumEditorUtils::SyncInputAction();
}

void UCsEdEngine::PopulateEnumMapsFromUserDefinedEnums()
{
	// DataType
	PopulateEnumMapFromUserDefinedEnum<EMCsDataType>(NCsUserDefinedEnum::FECsDataType);
	// DataCollection
	PopulateEnumMapFromUserDefinedEnum<EMCsDataCollectionType>(NCsUserDefinedEnum::FECsDataCollectionType);
	// Input
	{
		// InputAction
		PopulateEnumMapFromUserDefinedEnum<EMCsInputAction>(NCsUserDefinedEnum::FECsInputAction);
		// InputActionMap
		PopulateEnumMapFromUserDefinedEnum<EMCsInputActionMap>(NCsUserDefinedEnum::FECsInputActionMap);
		// GameEvent
		PopulateEnumMapFromUserDefinedEnum<EMCsGameEvent>(NCsUserDefinedEnum::FECsGameEvent);
	}
}

void UCsEdEngine::GetUserDefinedEnumNames(const FString& EnumName, const FECsUserDefinedEnum& EnumType, TArray<FString>& OutNames)
{
	if (UCsEnumStructUserDefinedEnumMap* Map = GetEnumStructUserDefinedEnumMap())
	{
		if (UUserDefinedEnum* Enum = Map->GetUserDefinedEnum(EnumType))
		{
			const int32 Count = Enum->NumEnums() - 1;

			for (int32 I = 0; I < Count; ++I)
			{
				OutNames.Add(Enum->GetDisplayNameTextByIndex(I).ToString());
			}
		}
		else
		{
			UE_LOG(LogCsEditor, Warning, TEXT("UCsEdEngine::GetUserDefinedEnumNames: Failed to find UserDefinedEnum: %s for EnumStruct: %s."), *(EnumType.Name), *EnumName);
		}
	}
}

#pragma endregion Enums

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

void UCsEdEngine::OnObjectSaved_DataRootSet_DataTables(UDataTable* DataTable)
{
	TArray<FName> RowNames = DataTable->GetRowNames();
	
	for (const FName& RowName : RowNames)
	{
		const FString& Context = NCsEdEngineCached::Str::OnObjectSaved_DataRootSet_DataTables;

		FCsDataEntry_DataTable* RowPtr = DataTable->FindRow<FCsDataEntry_DataTable>(RowName, Context);

		if (RowPtr->bPopulateOnSave)
		{
			RowPtr->Populate();

			RowPtr->bPopulateOnSave = false;
		}
	}
}

void UCsEdEngine::OnObjectSaved_DataRootSet_Payloads(UDataTable* DataTable)
{
	// Get Settings
	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	if (!Settings)
		return;

	// Get DataRootSet
	FCsDataRootSetContainer& Container = Settings->DataRootSet;
	UClass* Class					    = Container.Data.LoadSynchronous();
	UCsDataRootSet* DataRootSet			= Class ? Class->GetDefaultObject<UCsDataRootSet>() : nullptr;

	if (!DataRootSet)
		return;

	// See which Payloads to push to Datas | DataTables
	TArray<FName> RowNames = DataTable->GetRowNames();

	for (const FName& RowName : RowNames)
	{
		const FString& Context = NCsEdEngineCached::Str::OnObjectSaved_DataRootSet_Payloads;

		FCsPayload* RowPtr = DataTable->FindRow<FCsPayload>(RowName, Context);

		// Add the Payload to the Datas | DataTables
		if (RowPtr->bUpdateDataRootSetOnSave)
		{
			// DataTables
			TMap<TSoftObjectPtr<UDataTable>, TSet<FName>> RowNamesByDataTableMap;

			for (FCsPayload_DataTable& Payload_DataTable : RowPtr->DataTables)
			{
				TSoftObjectPtr<UDataTable>& DT = Payload_DataTable.DataTable;
				const FSoftObjectPath& Path	   = DT.ToSoftObjectPath();

				if (!Path.IsValid())
					continue;

				// Update the Name
				Payload_DataTable.Name = FName(*Path.GetAssetName());

				RowNamesByDataTableMap.Add(DT, Payload_DataTable.Rows);
			}

			// Add to Map of DataTables to Add to DataRootSet->DataTables
			DataRootSet->AddDataTables(RowNamesByDataTableMap);
		}
		RowPtr->bUpdateDataRootSetOnSave = false;
	}
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

					UCsLibrary_Load::GetReferencesReport(A, A->GetClass(), AssetNameAsString, Report);
					
					A->Destroy();
					break;
				}
			}
		}
	}
	// Object
	else
	{
		UCsLibrary_Load::GetReferencesReport(DOb, DOb->GetClass(), AssetNameAsString, Report);
	}
	Report.Print();
}

#pragma endregion References
