// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsEdEngine.h"
#include "CsEditor.h"
#include "CsCVars.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
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
// Managers
#include "Managers/Time/CsManager_Time.h"
// Asset Registry
#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"

#include "Factories/BlueprintFactory.h"
// Data
#include "Data/CsGetDataRootSet.h"
// Setting
#include "Settings/CsDeveloperSettings.h"
#include "Settings/ProjectPackagingSettings.h"
#include "Settings/LevelEditorPlaySettings.h"
// Property
#include "DetailCustomizations/CsRegisterDetailCustomization.h"
// Level
#include "Level/CsLevelScriptActor.h"


#include "Editor/UnrealEd/Public/Editor.h"

#include "Engine/UserDefinedEnum.h"

// Cache
#pragma region

namespace NCsEdEngine
{
	namespace NCached
	{
		namespace Str
		{
			const FString StandaloneFromEditor = TEXT("StandaloneFromEditor");

			const FString OnObjectSaved_Update_DataRootSet_DataTables = TEXT("UCsEdEngine::OnObjectSaved_Update_DataRootSet_DataTables");
			const FString OnObjectSaved_Update_DataRootSet_Payloads = TEXT("UCsEdEngine::OnObjectSaved_Update_DataRootSet_Payloads");
			const FString OnObjectSaved_Update_DataRootSet_Payload = TEXT("UCsEdEngine::OnObjectSaved_Update_DataRootSet_Payload");
		}

		namespace Name
		{
			const FName LastExecutedPlayModeType = FName("LastExecutedPlayModeType");
		}
	}

	namespace NStandalone
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsEdEngine::FStandalone, Monitor_Internal);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsEdEngine::FStandalone, Monitor_Internal);
			}
		}
	}
}

#pragma endregion Cache

// UEngine Interface
#pragma region

void UCsEdEngine::Init(IEngineLoop* InEngineLoop)
{
	Super::Init(InEngineLoop);

	Standalone.Outer = this;

	FCsRegisterDetailCustomization::Register();

	FEditorDelegates::BeginPIE.AddUObject(this, &UCsEdEngine::OnBeginPIE);
	FEditorDelegates::EndPIE.AddUObject(this, &UCsEdEngine::OnEndPIE);
	FEditorDelegates::BeginStandaloneLocalPlay.AddUObject(this, &UCsEdEngine::OnStandaloneLocalPlayEvent);
	FCoreUObjectDelegates::OnObjectSaved.AddUObject(this, &UCsEdEngine::OnObjectSaved);
	FCoreUObjectDelegates::OnObjectPropertyChanged.AddUObject(this, &UCsEdEngine::OnObjectPropertyChanged);

	OnWorldContextDestroyed().AddUObject(this, &UCsEdEngine::OnWorldContextDestroyed_Internal);

	ConstructManagerSingleton();

	UCsManager_Time::Init(this);
	UCsCoroutineScheduler::Init(this);
}

void UCsEdEngine::PreExit()
{
	Super::PreExit();

	UCsManager_Time::Shutdown(this);
	UCsCoroutineScheduler::Shutdown(this);
}

void UCsEdEngine::Tick(float DeltaSeconds, bool bIdleMode)
{
	Super::Tick(DeltaSeconds, bIdleMode);

	const FECsUpdateGroup& Group = NCsUpdateGroup::EditorEngine;

	UCsManager_Time::Get(this)->Update(Group, DeltaSeconds);

	const FCsDeltaTime& DeltaTime = UCsManager_Time::Get(this)->GetScaledDeltaTime(Group);

	UCsCoroutineScheduler::Get(this)->Update(Group, DeltaTime);
}

#pragma endregion UEngine Interface

// UEditorEngine Interface
#pragma region

void UCsEdEngine::LaunchNewProcess(const FRequestPlaySessionParams& InParams, const int32 InInstanceNum, EPlayNetMode NetMode, bool bIsDedicatedServer)
{
	using namespace NCsEdEngine::NCached;

	// if "-StandaloneFromEditor" does NOT exist, add it.
	FRequestPlaySessionParams& Params   = const_cast<FRequestPlaySessionParams&>(InParams);
	TOptional<FString>& OpCmdParams		= Params.AdditionalStandaloneCommandLineParameters;

	if (!OpCmdParams.IsSet())
		OpCmdParams = TEXT("");

	if (OpCmdParams.IsSet())
	{
		FString& CmdParams = OpCmdParams.GetValue();

		if (!CmdParams.Contains(Str::StandaloneFromEditor))
		{
			CmdParams += (CmdParams.IsEmpty() ? TEXT("-") : TEXT(" -")) + Str::StandaloneFromEditor;
		}
	}

	Standalone.bActive = true;

	// If Mobile, set the appropriate DataRootSet
	if (Params.SessionPreviewTypeOverride.IsSet() &&
		Params.SessionPreviewTypeOverride == EPlaySessionPreviewType::MobilePreview)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		Settings->DataRootSet = Settings->GetDataRootSet(ECsPlatform::Android);

		FPropertyChangedEvent PropChangeEvent(UCsDeveloperSettings::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UCsDeveloperSettings, DataRootSet)));
		Settings->PostEditChangeProperty(PropChangeEvent);
		Settings->UpdateDefaultConfigFile();

		UProjectPackagingSettings* PackageSettings = GetMutableDefault< UProjectPackagingSettings>();

		if (PackageSettings->DirectoriesToAlwaysCook.Num() == CS_EMPTY)
		{
			PackageSettings->DirectoriesToAlwaysCook.AddDefaulted();
		}

		PackageSettings->DirectoriesToAlwaysCook[CS_FIRST] = Settings->GetDirectoryToAlwaysCook(ECsPlatform::Android);
		PackageSettings->UpdateDefaultConfigFile();
	}
	
	Super::LaunchNewProcess(InParams, InInstanceNum, NetMode, bIsDedicatedServer);

	Standalone.Monitor();
}

#pragma endregion UUEditorEngine Interface

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
	if (Check_GetObjectPaths(Stream))
		return true;
	if (Check_LoadObject(Stream))
		return true;
	return true;
}

#pragma endregion FExec Interface

// PIE
#pragma region

void UCsEdEngine::OnBeginPIE(bool IsSimulating)
{
	FCsCVarLogMap::Get().ResetDirty();
	FCsCVarToggleMap::Get().ResetDirty();
	FCsCVarDrawMap::Get().ResetDirty();

	UCsDeveloperSettings* ModuleSettings   = GetMutableDefault<UCsDeveloperSettings>();
	ULevelEditorPlaySettings* PlaySettings = GetMutableDefault<ULevelEditorPlaySettings>();

	const EPlayModeType PlayMode = PlaySettings->LastExecutedPlayModeType;
}

void UCsEdEngine::OnEndPIE(bool IsSimulating)
{
	UCsDeveloperSettings* ModuleSettings   = GetMutableDefault<UCsDeveloperSettings>();
	ULevelEditorPlaySettings* PlaySettings = GetMutableDefault<ULevelEditorPlaySettings>();

	const EPlayModeType PlayMode = PlaySettings->LastExecutedPlayModeType;

	// PIE
	if (PlayMode == EPlayModeType::PlayMode_InEditorFloating)
	{
		// Mobile
		if (ModuleSettings->bPIE_Mobile)
		{
			ModuleSettings->DataRootSet = ModuleSettings->GetDataRootSet(ECsPlatform::Windows);

			FPropertyChangedEvent PropChangeEvent(UCsDeveloperSettings::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UCsDeveloperSettings, DataRootSet)));
			ModuleSettings->PostEditChangeProperty(PropChangeEvent);
			ModuleSettings->UpdateDefaultConfigFile();
		}
	}
	OnEndPIE_ScriptEvent.Broadcast(IsSimulating);
	OnEndPIE_Last_ScriptEvent.Broadcast(IsSimulating);

	CreatedObjects.DestroyAndRemoveNullPendingKillOrOrphaned();
}

#pragma endregion PIE

// World
#pragma region

void UCsEdEngine::OnWorldContextDestroyed_Internal(FWorldContext& WorldContext)
{
	CreatedObjects.DestroyByWorld(WorldContext.World());
}

#pragma endregion World

// PropertyChange
#pragma region

void UCsEdEngine::OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& e)
{
	using namespace NCsEdEngine::NCached;

	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	UCsDeveloperSettings* ModuleSettings   = GetMutableDefault<UCsDeveloperSettings>();
	ULevelEditorPlaySettings* PlaySettings = GetMutableDefault<ULevelEditorPlaySettings>();

	// "Capture" Play button press in editor and alter settings
	if (Object == PlaySettings)
	{
		if (PropertyName == Name::LastExecutedPlayModeType)
		{
			if (ModuleSettings->bOverridePIESettings)
			{
				const EPlayModeType PlayMode = PlaySettings->LastExecutedPlayModeType;

				// PIE
				if (PlayMode == EPlayModeType::PlayMode_InEditorFloating)
				{
					// Mobile
					if (ModuleSettings->bPIE_Mobile)
					{
						ModuleSettings->DataRootSet = ModuleSettings->GetDataRootSet(ECsPlatform::Android);

						FPropertyChangedEvent PropChangeEvent(UCsDeveloperSettings::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UCsDeveloperSettings, DataRootSet)));
						ModuleSettings->PostEditChangeProperty(PropChangeEvent);
						ModuleSettings->UpdateDefaultConfigFile();

						PlaySettings->NewWindowWidth  = ModuleSettings->PIE_Mobile.NewWindowWidth;
						PlaySettings->NewWindowHeight = ModuleSettings->PIE_Mobile.NewWindowHeight;
					}
					else
					{
						PlaySettings->NewWindowWidth  = ModuleSettings->PIE.NewWindowWidth;
						PlaySettings->NewWindowHeight = ModuleSettings->PIE.NewWindowHeight;
					}
				}
				// Standalone Mobile
				else
				if (PlayMode == EPlayModeType::PlayMode_InMobilePreview)
				{
					PlaySettings->NewWindowWidth  = ModuleSettings->Standalone_Mobile.NewWindowWidth;
					PlaySettings->NewWindowHeight = ModuleSettings->Standalone_Mobile.NewWindowHeight;
				}
				// Standalone
				else
				if (PlayMode == EPlayModeType::PlayMode_InNewProcess)
				{
					PlaySettings->NewWindowWidth  = ModuleSettings->Standalone.NewWindowWidth;
					PlaySettings->NewWindowHeight = ModuleSettings->Standalone.NewWindowHeight;
				}
			}
		}
	}
}

#pragma endregion PropertyChange

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
			TSet<TSoftClassPtr<UObject>> DataRootSets;

			const int32 Count = (int32)ECsPlatform::ECsPlatform_MAX;

			for (int32 I = 0; I < Count; ++I)
			{
				DataRootSets.Add(Settings->DataRootSets[I].DataRootSet);
			}

			for (TSoftClassPtr<UObject> SoftClass : DataRootSets)
			{
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
	using namespace NCsEdEngine::NCached;

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
		typedef NCsString::FLibrary StringLibrary;

		const FName AssetName = StringLibrary::Stream_GetName(Stream);

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

// Asset
#pragma region

bool UCsEdEngine::Check_GetObjectPaths(const TCHAR* Stream)
{
	const FString Command	 = TEXT("GetObjectPaths");
	const FString Parameters = TEXT("[path]");
	const FString Format	 = Command + TEXT(" ") + Parameters;

	if (FParse::Command(&Stream, *Command))
	{
		const FString AssetPath = UCsLibrary_Common::Stream_GetString(Stream, false);

		if (!AssetPath.IsEmpty())
		{
			GetObjectPaths(AssetPath);
			return true;
		}
	}
	return false;
}

void UCsEdEngine::GetObjectPaths(const FString& AssetPath)
{
	FSoftObjectPath Path(AssetPath);

	if (UObject* Object = Path.TryLoad())
	{
		FCsLibraryLoad_GetObjectPaths Result;

		UCsLibrary_Load::GetObjectPaths(Object, Object->GetClass(), Result);

		Result.Print();
	}
}

bool UCsEdEngine::Check_LoadObject(const TCHAR* Stream)
{
	const FString Command	 = TEXT("LoadObject");
	const FString Parameters = TEXT("[path]");
	const FString Format	 = Command + TEXT(" ") + Parameters;

	if (FParse::Command(&Stream, *Command))
	{
		const FString AssetPath = UCsLibrary_Common::Stream_GetString(Stream, false);

		if (!AssetPath.IsEmpty())
		{
			LoadObject(AssetPath);
			return true;
		}
	}
	return false;
}

void UCsEdEngine::LoadObject(const FString& AssetPath)
{
	FSoftObjectPath Path(AssetPath);

	if (UObject* Object = Path.TryLoad())
	{
		UCsLibrary_Load::LoadStruct(Object, Object->GetClass(), NCsLoadFlags::All, NCsLoadCodes::All);
	}
}

#pragma endregion Asset

// Standalone
#pragma region

void UCsEdEngine::FStandalone::Monitor()
{
	using namespace NCsEdEngine::NStandalone::NCached;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::EditorEngine;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(Outer);

	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE Monitor_Internal

	Payload->CoroutineImpl.BindRaw(this, &UCsEdEngine::FStandalone::COROUTINE);
	Payload->StartTime = UCsManager_Time::Get(Outer)->GetTime(UpdateGroup);
	Payload->Owner.SetObject(Outer);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	Scheduler->Start(Payload);
}

char UCsEdEngine::FStandalone::Monitor_Internal(FCsRoutine* R)
{
	CS_COROUTINE_BEGIN(R);

	CS_COROUTINE_WAIT_UNTIL(R, !FPlatformProcess::IsApplicationRunning(ProcessID));

	// Set DataRootSet back to Windows
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();
		Settings->DataRootSet		   = Settings->GetDataRootSet(ECsPlatform::Windows);

		FPropertyChangedEvent PropChangeEvent(UCsDeveloperSettings::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UCsDeveloperSettings, DataRootSet)));
		Settings->PostEditChangeProperty(PropChangeEvent);
		Settings->UpdateDefaultConfigFile();

		UProjectPackagingSettings* PackageSettings		   = GetMutableDefault< UProjectPackagingSettings>();
		PackageSettings->DirectoriesToAlwaysCook[CS_FIRST] = Settings->GetDirectoryToAlwaysCook(ECsPlatform::Windows);
		PackageSettings->UpdateDefaultConfigFile();
	}
	Reset();

	CS_COROUTINE_END(R);
}

void UCsEdEngine::OnStandaloneLocalPlayEvent(uint32 ProcessID)
{
	if (Standalone.bActive)
	{
		Standalone.ProcessID = ProcessID;
	}
}

#pragma endregion Standalone