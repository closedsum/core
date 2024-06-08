// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsEdEngine.h"
#include "CsEditor.h"

#include "CsCVars_Core.h"
#include "CsCVars_Data.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Type
#include "Data/CsTypes_DataEntry.h"
// Library
	// Data
#include "Data/CsLibrary_Data.h"
	// Common
#include "Library/Load/CsLibrary_Load.h"
#include "Library/CsLibrary_Blueprint.h"
#include "Asset/CsLibrary_Asset.h"
#include "Library/CsLibrary_String.h"
#include "Library/CsLibrary_Property.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Asset Registry
#include "AssetRegistry/AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
// Data
#include "Data/CsGetDataRootSet.h"
// Setting
#include "Settings/Tool/CsSettingsTool.h"
#include "Settings/CsUserSettings.h"
#include "Settings/CsDeveloperSettings.h"
#include "Settings/CsDataSettings.h"
#include "Settings/ProjectPackagingSettings.h"
#include "Settings/LevelEditorPlaySettings.h"
// Property
#include "DetailCustomizations/CsRegisterDetailCustomization.h"
// Level
#include "Level/CsLevelScriptActor.h"
#include "Level/Editor/Tool/CsLevelEditorTool.h"
// Asset
#include "Asset/Tool/CsAssetTool.h"
// Object
#include "Object/Environment/Tool/CsObjectEnvironmentTool.h"
// UI
#include "Framework/Application/SlateApplication.h"
// Enum
#include "Types/Enum/Tool/CsEnumStructLayoutTool.h"
// Utility
#include "Utility/CsLibrary_EnumStruct.h"
#include "Utility/CsLibrary_EnumStructImpl.h"
// Editor
#include "Editor.h"
#include "LevelEditor.h"
#include "PackageTools.h"
// Module
#include "Modules/ModuleManager.h"
// SourceControl
#include "SourceControlHelpers.h"

// Cache
#pragma region

namespace NCsEdEngine
{
	namespace NCached
	{
		namespace Str
		{
			const FString StandaloneFromEditor = TEXT("StandaloneFromEditor");
			const FString StandaloneMobileFromEditor = TEXT("StandaloneMobileFromEditor");

			// Init
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsEdEngine, PostInit);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsEdEngine, PostInit_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsEdEngine, OnPostInit);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsEdEngine, OnEndPIE_NextFrame_Internal);

			// GetDataEntryTool
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsEdEngine, DataEntry_DataTable_PopulateImpl);
			// Save
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsEdEngine, OnObjectPreSave);
			const FString OnObjectPreSave_Update_DataRootSet_Datas = TEXT("UCsEdEngine::OnObjectPreSave_Update_DataRootSet_Datas");
			const FString OnObjectPreSave_Update_DataRootSet_ScriptDatas = TEXT("UCsEdEngine::OnObjectPreSave_Update_DataRootSet_ScriptDatas");
			const FString OnObjectPreSave_Update_DataRootSet_DataTables = TEXT("UCsEdEngine::OnObjectPreSave_Update_DataRootSet_DataTables");
			const FString OnObjectPreSave_Update_DataRootSet_Payloads = TEXT("UCsEdEngine::OnObjectPreSave_Update_DataRootSet_Payloads");
			const FString OnObjectPreSave_Update_DataRootSet_Payload = TEXT("UCsEdEngine::OnObjectPreSave_Update_DataRootSet_Payload");
		}

		namespace Name
		{
			const FName LastExecutedPlayModeType = FName("LastExecutedPlayModeType");
			const FName Data = FName("Data");

			// Init
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsEdEngine, PostInit_Internal);

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsEdEngine, OnEndPIE_NextFrame_Internal);
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

#define USING_NS_CACHED using namespace NCsEdEngine::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsEdEngine::NCached; \
	const FString& Context = Str::__FunctionName

// UEngine Interface
#pragma region

void UCsEdEngine::Init(IEngineLoop* InEngineLoop)
{
	Super::Init(InEngineLoop);

	PlayMode = ECsPlayMode::ECsPlayMode_MAX;
	Standalone.Outer = this;

	FCsRegisterDetailCustomization::Register();

	ConstructManagerSingleton();

	UCsManager_Time::Init(this);
	UCsCoroutineScheduler::Init(this);

	NCsEnum::NStruct::NLayout::FLibrary::ConditionalAddLayout = &NCsEnum::NStruct::NLayout::NImpl::FLibrary::ConditionalAddLayout;
	NCsEnum::NStruct::NLayout::FLibrary::AddPropertyChange = &NCsEnum::NStruct::NLayout::NImpl::FLibrary::AddPropertyChange;

	PostInit();
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

	// Check Opened Assets
	{
		const int32 Count = OpenedAssets.Num();

		// HACK: Capture event for when an Asset Editor is closed for an Asset
		//		 Event OnAssetEditorRequestClose() from UAssetEditorSubsystem doesn't seem to always be called
		//		 depending on the Editor.
		for (int32 I = Count - 1; I >= 0; --I)
		{
			TWeakObjectPtr<UObject>& OpenedAsset = OpenedAssets[I];
			UObject* Asset						 = OpenedAsset.IsValid() ? OpenedAsset.Get() : nullptr;
			
			if (IsValid(Asset))
			{
				TArray<IAssetEditorInstance*> Instances = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorsForAsset(Asset);

				if (Instances.Num() == CS_EMPTY)
				{
					OnAssetEditorRequestClose(Asset, EAssetEditorCloseReason::CloseAllEditorsForAsset);
					OpenedAssets.RemoveAt(I, 1, false);
				}
			}
			// TODO: Potentially need a Unique ID to broadcast OnAssetEditorRequestClose
			else
			{
				OpenedAssets.RemoveAt(I, 1, false);
			}
		}
	}
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

	UCsDeveloperSettings* ModuleSettings = GetMutableDefault<UCsDeveloperSettings>();
	UCsDataSettings* DataSettings        = GetMutableDefault<UCsDataSettings>();

	// If Mobile, set the appropriate DataRootSet
	if (Params.SessionPreviewTypeOverride.IsSet() &&
		(Params.SessionPreviewTypeOverride == EPlaySessionPreviewType::MobilePreview ||
		 (Params.SessionPreviewTypeOverride == EPlaySessionPreviewType::VulkanPreview &&
		  ModuleSettings->bPIE_VulkanPreviewMobile)))
	{
		FString& CmdParams = OpCmdParams.GetValue();

		if (!CmdParams.Contains(Str::StandaloneMobileFromEditor))
		{
			CmdParams += TEXT(" -") + Str::StandaloneMobileFromEditor;
		}

		DataSettings->DataRootSet = DataSettings->GetDataRootSet(ECsPlatform::Android);

		FPropertyChangedEvent PropChangeEvent(UCsDataSettings::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UCsDataSettings, DataRootSet)));
		DataSettings->PostEditChangeProperty(PropChangeEvent);
		DataSettings->TryUpdateDefaultConfigFile();

		UProjectPackagingSettings* PackageSettings = GetMutableDefault< UProjectPackagingSettings>();

		if (PackageSettings->DirectoriesToAlwaysCook.Num() == CS_EMPTY)
		{
			PackageSettings->DirectoriesToAlwaysCook.AddDefaulted();
		}

		PackageSettings->DirectoriesToAlwaysCook[CS_FIRST] = DataSettings->GetDirectoryToAlwaysCook(ECsPlatform::Android);
		PackageSettings->TryUpdateDefaultConfigFile();
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

	if (Check_LoadObject(Stream))
		return true;
	return false;
}

#pragma endregion FExec Interface

// Init
#pragma region

void UCsEdEngine::PostInit()
{
	SET_CONTEXT(PostInit);

	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::EditorEngine;
	UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(this);
	PayloadType* Payload			   = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE PostInit_Internal

	Payload->CoroutineImpl.BindUObject(this, &UCsEdEngine::COROUTINE);
	Payload->StartTime = UCsManager_Time::Get(this)->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	Scheduler->Start(Payload);
}

char UCsEdEngine::PostInit_Internal(FCsRoutine* R)
{
	FAssetRegistryModule* AssetRegistry = FModuleManager::GetModulePtr<FAssetRegistryModule>(FName(TEXT("AssetRegistry")));

	CS_COROUTINE_BEGIN(R);

	CS_COROUTINE_WAIT_UNTIL(R, AssetRegistry);

	AssetRegistry->Get().OnFilesLoaded().AddUObject(this, &UCsEdEngine::SetPostInit);

	CS_COROUTINE_WAIT_UNTIL(R, bPostInit);

	AssetRegistry->Get().OnFilesLoaded().RemoveAll(this);

	OnPostInit();

	CS_COROUTINE_END(R);
}

void UCsEdEngine::OnPostInit()
{
	SET_CONTEXT(OnPostInit);

	FEditorDelegates::BeginPIE.AddUObject(this, &UCsEdEngine::OnBeginPIE);
	FEditorDelegates::EndPIE.AddUObject(this, &UCsEdEngine::OnEndPIE);
	FEditorDelegates::BeginStandaloneLocalPlay.AddUObject(this, &UCsEdEngine::OnStandaloneLocalPlayEvent);
	FCoreUObjectDelegates::OnObjectPreSave.AddUObject(this, &UCsEdEngine::OnObjectPreSave);
	FCoreUObjectDelegates::OnObjectPropertyChanged.AddUObject(this, &UCsEdEngine::OnObjectPropertyChanged);

	OnWorldContextDestroyed().AddUObject(this, &UCsEdEngine::OnWorldContextDestroyed_Internal);

	// CVars
	GetMutableDefault<UCsDeveloperSettings>()->ApplyEnableScriptChecked();

	DataEntryTool.Data_PopulateImpl = &UCsEdEngine::DataEntry_Data_PopulateImpl;
	DataEntryTool.ScriptData_PopulateImpl = &UCsEdEngine::DataEntry_ScriptData_PopulateImpl;
	DataEntryTool.DataTable_PopulateImpl = &UCsEdEngine::DataEntry_DataTable_PopulateImpl;

	SlateApplicationTool.ApplyApplicationScaleImpl = &UCsEdEngine::ApplyApplicationScaleImpl;

	UCsUserSettings* UserSettings = GetMutableDefault<UCsUserSettings>();

	UserSettings->ApplyEditorUI_ApplicationScale();

	AssetTool.GetOpenedAssetsImpl = &NCsAsset::FTool::GetOpenedAssets;
	AssetTool.IsAssetOpenedImpl = &NCsAsset::FTool::IsAssetOpened;
	AssetTool.IsAssetWithClassDefaultOpenedImpl = &NCsAsset::FTool::IsAssetWithClassDefaultOpened;
	
	EnumStructTool.Init(this);
	EnumStructTool.ResolveLayoutChangesImpl = &UCsEdEngine::EnumStruct_ResolveLayoutChanges_Internal;

	SourceControlTool.CheckOutFileImpl = &USourceControlHelpers::CheckOutFile;

	LevelEditorTool.GetActorsImpl = &NCsLevel::NEditor::FTool::GetActors;
	LevelEditorTool.GetActorsByClassImpl = &NCsLevel::NEditor::FTool::GetActorsByClass;
	LevelEditorTool.GetActorsByInterfaceImpl = &NCsLevel::NEditor::FTool::GetActorsByInterface;
	LevelEditorTool.GetSelectedActorsImpl = &NCsLevel::NEditor::FTool::GetSelectedActors;

	ObjectEnvironmentTool.GetDetailsImpl = &NCsObject::NEnvironment::FTool::GetDetails;

	typedef NCsSettings::FTool SettingsTool;

	SettingsTool::ToggleProjectSettings();

	// ICsAsset_Event
	GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OnAssetOpenedInEditor().AddUObject(this, &UCsEdEngine::OnAssetOpenedInEditor);
	GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OnAssetEditorRequestClose().AddUObject(this, &UCsEdEngine::OnAssetEditorRequestClose);
	// ICsLevelEditor_Event
	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.OnActorSelectionChanged().AddUObject(this, &UCsEdEngine::OnActorSelectionChanged);

	IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("gc.TimeBetweenPurgingPendingKillObjects"));
	CVar->Set(UserSettings->GCInterval, ECVF_SetByCode);
}

#pragma endregion Init

// PIE_Event
#pragma region

void UCsEdEngine::OnBeginPIE(bool IsSimulating)
{
	FCsCVarLogMap::Get().ResetDirty();
	FCsCVarToggleMap::Get().ResetDirty();
	FCsCVarDrawMap::Get().ResetDirty();

	PIEInfo.SetBeginning();

	NCsPIE::FDelegates::OnBegin_Event.Broadcast(IsSimulating);
	PIE_OnBegin_ScriptEvent.Broadcast(IsSimulating);

	PIEInfo.SetActive();
}

void UCsEdEngine::OnEndPIE(bool IsSimulating)
{
	PIEInfo.SetEnding();

	UCsDeveloperSettings* ModuleSettings   = GetMutableDefault<UCsDeveloperSettings>();
	UCsDataSettings* DataSettings		   = GetMutableDefault<UCsDataSettings>();
	ULevelEditorPlaySettings* PlaySettings = GetMutableDefault<ULevelEditorPlaySettings>();

	const EPlayModeType PlayModeType = PlaySettings->LastExecutedPlayModeType;

	// PIE
	if (PlayModeType == EPlayModeType::PlayMode_InEditorFloating)
	{
		// Mobile
		if (ModuleSettings->bPIE_Mobile)
		{
			DataSettings->DataRootSet = DataSettings->GetDataRootSet(ECsPlatform::Windows);

			FPropertyChangedEvent PropChangeEvent(UCsDataSettings::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UCsDataSettings, DataRootSet)));
			DataSettings->PostEditChangeProperty(PropChangeEvent);
			DataSettings->TryUpdateDefaultConfigFile();
		}
	}
	NCsPIE::FDelegates::OnEnd_Event.Broadcast(IsSimulating);
	PIE_OnEnd_ScriptEvent.Broadcast(IsSimulating);
	OnEndPIE_ScriptEvent.Broadcast(IsSimulating);
	NCsPIE::FDelegates::OnEnd_Last_Event.Broadcast(IsSimulating);
	PIE_OnEnd_Last_ScriptEvent.Broadcast(IsSimulating);
	OnEndPIE_Last_ScriptEvent.Broadcast(IsSimulating);

	CreatedObjects.DestroyAndRemoveNullPendingKillOrOrphaned();

	UCsUserSettings* UserSettings = GetMutableDefault<UCsUserSettings>();

	if (UserSettings->bForceGCOnEndPIE)
		ForceGarbageCollection(true);

	OnEndPIE_NextFrame(IsSimulating);
}

void UCsEdEngine::OnEndPIE_NextFrame(bool IsSimulating)
{
	using namespace NCsEdEngine::NCached;

	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::EditorEngine;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(this);

	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE OnEndPIE_NextFrame_Internal

	Payload->CoroutineImpl.BindUObject(this, &UCsEdEngine::COROUTINE);
	Payload->StartTime = UCsManager_Time::Get(this)->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	static const int32 IS_SIMULATING = 0;

	Payload->SetValue_Flag(IS_SIMULATING, IsSimulating);

	Scheduler->Start(Payload);
}

char UCsEdEngine::OnEndPIE_NextFrame_Internal(FCsRoutine* R)
{
	static const int32 IS_SIMULATING = 0;
	const bool& IsSimulating = R->GetValue_Flag(IS_SIMULATING);

	CS_COROUTINE_BEGIN(R)

	CS_COROUTINE_YIELD(R)

	OnEndPlayMapPIE(IsSimulating);

	NCsPIE::FDelegates::OnEnd_NextFrame_Event.Broadcast(IsSimulating);
	PIE_OnEnd_NextFrame_ScriptEvent.Broadcast(IsSimulating);

	PIEInfo.SetNone();
	
	CS_COROUTINE_END(R)
}

void UCsEdEngine::OnEndPlayMapPIE(bool IsSimulating)
{
	PlayMode = ECsPlayMode::ECsPlayMode_MAX;

	NCsPIE::FDelegates::OnEndPlayMap_Event.Broadcast(IsSimulating);
	PIE_OnEndPlayMap_ScriptEvent.Broadcast(IsSimulating);
}

#pragma endregion PIE_Event

// World
#pragma region

void UCsEdEngine::OnWorldContextDestroyed_Internal(FWorldContext& WorldContext)
{
	CreatedObjects.DestroyByWorld(WorldContext.World());
}

#pragma endregion World

// GetDataEntryTool
#pragma region

void UCsEdEngine::DataEntry_Data_PopulateImpl(FCsDataEntry_Data* Entry)
{
	typedef NCsAsset::NDependency::NSoftPath::FLibrary DependencyLibrary;
	typedef NCsAsset::NDependency::NSoftPath::FLibrary::FGet::FResult ResultType;

	ResultType Result;
	DependencyLibrary::Get(Entry, FCsDataEntry_Data::StaticStruct(), 7, Result);

	Entry->Populate(Result.PathSet, Result.PathSetsByGroup);
}

void UCsEdEngine::DataEntry_ScriptData_PopulateImpl(FCsDataEntry_ScriptData* Entry)
{
	typedef NCsAsset::NDependency::NSoftPath::FLibrary DependencyLibrary;
	typedef NCsAsset::NDependency::NSoftPath::FLibrary::FGet::FResult ResultType;

	ResultType Result;
	DependencyLibrary::Get(Entry, FCsDataEntry_ScriptData::StaticStruct(), 7, Result);

	Entry->Populate(Result.PathSet, Result.PathSetsByGroup);
}

void UCsEdEngine::DataEntry_DataTable_PopulateImpl(UObject* DataTable, const FName& RowName, FCsDataEntry_DataTable* Entry, const bool& AllRows)
{
	using namespace NCsEdEngine::NCached;

	const FString& Context = Str::DataEntry_DataTable_PopulateImpl;

	FSoftObjectPath DataTablePath = Entry->DataTable.ToSoftObjectPath();

	if (!DataTablePath.IsValid())
	{
		UE_LOG(LogCsEditor, Warning, TEXT("%s: %s.%s.DataTable is NOT Valid."), *Context, *(DataTable->GetName()), *(RowName.ToString()));
		return;
	}

	UDataTable* DT = Entry->DataTable.LoadSynchronous();

	if (!DT)
	{
		UE_LOG(LogCsEditor, Warning, TEXT("%s: Failed to load %s.%s at Path: %s"), *Context, *(DataTable->GetName()), *(RowName.ToString()), *(Entry->DataTable.ToString()));
		return;
	}

	Entry->ClearPaths();

	if (CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate))
	{
		UE_LOG(LogCsEditor, Warning, TEXT("%s: Populating: %s."), *Context, *(DT->GetName()));
	}

	TArray<FName> RowNames;

	// All Rows
	if (AllRows || Entry->bAllRows)
	{
		RowNames = DT->GetRowNames();
	}
	// Specified Rows
	else
	{
		RowNames = Entry->Rows.Array();
	}

	if (CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate))
	{
		if (RowNames.Num() > CS_EMPTY)
		{
			UE_LOG(LogCsEditor, Warning, TEXT("- Processing %d Rows."), RowNames.Num());
		}
	}

	Entry->SetupRows(RowNames);

	for (const FName& Name : RowNames)
	{
		const UScriptStruct* ScriptStruct = DT->GetRowStruct();
		UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
		UStruct* const Struct			  = Temp;

		typedef NCsAsset::NDependency::NSoftPath::FLibrary DependencyLibrary;
		typedef NCsAsset::NDependency::NSoftPath::FLibrary::FGet::FResult ResultType;

		ResultType Result;
		DependencyLibrary::Get(DT->FindRowUnchecked(Name), Temp, 7, Result);

		Entry->PopulateRow(Name, Result.PathSet, Result.PathSetsByGroup);
	}
}

#pragma endregion GetDataEntryTool

// GetSlateApplicationTool
#pragma region

void UCsEdEngine::ApplyApplicationScaleImpl(const float& ApplicationScale)
{
	FSlateApplication::Get().SetApplicationScale(ApplicationScale);
}

#pragma endregion GetSlateApplicationTool

// GetEnumStructTool
#pragma region

void UCsEdEngine::EnumStruct_ResolveLayoutChanges(bool bForce)
{
	TMap<FName, UStruct*> StructMap;

	NCsEnum::NStruct::NLayout::FTool::DetermineChanges(StructMap);
	NCsEnum::NStruct::NLayout::FTool::ResolveChanges(StructMap, bForce);
}

/*static*/ void UCsEdEngine::EnumStruct_ResolveLayoutChanges_Internal(bool bForce)
{
	Cast<UCsEdEngine>(GEngine)->EnumStruct_ResolveLayoutChanges(bForce);
}

#pragma endregion GetEnumStructTool

// Asset_Event
#pragma region

void UCsEdEngine::OnAssetOpenedInEditor(UObject* Asset, IAssetEditorInstance* EditorInstance)
{
	Asset_OnOpenedInEditor_Event.Broadcast(Asset);

	bool AddAsset = true;

	for (const TWeakObjectPtr<UObject> O : OpenedAssets)
	{
		UObject* OpenedAsset = O.IsValid() ? O.Get() : nullptr;

		if (IsValid(OpenedAsset) &&
			OpenedAsset == Asset)
		{
			AddAsset = false;
		}
	}

	if (AddAsset)
	{
		Asset_OnUniqueOpenedInEditor_Event.Broadcast(Asset);
		OpenedAssets.Add(Asset);
	}
}

void UCsEdEngine::OnAssetEditorRequestClose(UObject* Asset, EAssetEditorCloseReason Reason)
{
	typedef NCsAsset::NEditor::NClose::EReason ReasonType;

	AssetEditor_OnRequest_Close_Event.Broadcast(Asset, (ReasonType)Reason);
	AssetEditor_OnRequest_Close_ScriptEvent.Broadcast(Asset, (ECsAssetEditorCloseReason)Reason);
}

#pragma endregion Asset_Event

// LevelEditor_Event
#pragma region

void UCsEdEngine::OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh)
{
	OnActorSelectionChanged_Event.Broadcast(NewSelection, bForceRefresh);
	OnActorSelectionChanged_ScriptEvent.Broadcast(NewSelection, bForceRefresh);
}

#pragma endregion LevelEditor_Event

// PropertyChange
#pragma region

void UCsEdEngine::OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& e)
{
	using namespace NCsEdEngine::NCached;

	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	UCsDeveloperSettings* ModuleSettings   = GetMutableDefault<UCsDeveloperSettings>();
	UCsDataSettings* DataSettings		   = GetMutableDefault<UCsDataSettings>();
	ULevelEditorPlaySettings* PlaySettings = GetMutableDefault<ULevelEditorPlaySettings>();

	// "Capture" Play button press in editor and alter settings
	if (Object == PlaySettings)
	{
		if (PropertyName == Name::LastExecutedPlayModeType)
		{
			const EPlayModeType PlayModeType = PlaySettings->LastExecutedPlayModeType;
			PlayMode						 = (ECsPlayMode)PlayModeType;

			if (ModuleSettings->bOverridePIESettings)
			{
				// PIE
				if (PlayMode == ECsPlayMode::InEditorFloating)
				{
					// Mobile
					if (ModuleSettings->bPIE_Mobile)
					{
						DataSettings->DataRootSet = DataSettings->GetDataRootSet(ECsPlatform::Android);

						FPropertyChangedEvent PropChangeEvent(UCsDataSettings::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UCsDataSettings, DataRootSet)));
						DataSettings->PostEditChangeProperty(PropChangeEvent);
						DataSettings->TryUpdateDefaultConfigFile();

						PlaySettings->NewWindowWidth  = ModuleSettings->PIE_Mobile.NewWindowWidth;
						PlaySettings->NewWindowHeight = ModuleSettings->PIE_Mobile.NewWindowHeight;

						PlayMode = ECsPlayMode::InMobilePreviewEditorFloating;
					}
					else
					{
						PlaySettings->NewWindowWidth  = ModuleSettings->PIE.NewWindowWidth;
						PlaySettings->NewWindowHeight = ModuleSettings->PIE.NewWindowHeight;
					}
				}
				// Standalone Mobile
				else
				if (PlayMode == ECsPlayMode::InMobilePreview)
				{
					PlaySettings->NewWindowWidth  = ModuleSettings->Standalone_Mobile.NewWindowWidth;
					PlaySettings->NewWindowHeight = ModuleSettings->Standalone_Mobile.NewWindowHeight;
				}
				// Standalone
				else
				if (PlayMode == ECsPlayMode::InNewProcess)
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

void UCsEdEngine::OnObjectPreSave(UObject* Object, FObjectPreSaveContext SaveContext)
{
	SET_CONTEXT(OnObjectPreSave);

	if (!Object)
		return;

	UCsUserSettings* UserSettings = GetMutableDefault<UCsUserSettings>();

	// DataTable
	if (UDataTable* DataTable = Cast<UDataTable>(Object))
	{
		DataTableTool.ProcessChange(DataTable);

		// Settings
		if (UCsDataSettings* DataSettings = GetMutableDefault<UCsDataSettings>())
		{
			// TODO: Save out to .json
			
			// DataRootSet
			{
				TSet<TSoftClassPtr<UObject>> DataRootSets;

				const int32 Count = (int32)ECsPlatform::ECsPlatform_MAX;

				for (int32 I = 0; I < Count; ++I)
				{
					DataRootSets.Add(DataSettings->DataRootSets[I].DataRootSet);
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

						// Check if DataTable is in the list of DataTables
						if (UserSettings->bOnSave_DataTable_PopulatePaths)
						{
							TSoftObjectPtr<UDataTable> DataTableSoftObject(DataTable);

							UDataTable* DataTables = DataRootSet.DataTables;

							const TMap<FName, uint8*>& RowMap = DataTables->GetRowMap();

							bool Found = false;

							TArray<UObject*> ObjectsToSave;

							for (const TPair<FName, uint8*>& Pair : RowMap)
							{
								const FName& RowName		   = Pair.Key;
								FCsDataEntry_DataTable* RowPtr = reinterpret_cast<FCsDataEntry_DataTable*>(Pair.Value);

								if (DataTableSoftObject == RowPtr->DataTable)
								{
									DataEntryTool.DataTable_PopulateImpl(DataTables, RowName, RowPtr, false);
									DataTables->MarkPackageDirty();
									ObjectsToSave.Add(DataTables);

									Found = true;
									break;
								}
							}

							if (Found)
								UPackageTools::SavePackagesForObjects(ObjectsToSave);
						}

						// Datas
						if (DataTable == DataRootSet.Datas)
						{
							if (FCsDataEntry_Data::StaticStruct() == DataTable->GetRowStruct())
							{
								OnObjectPreSave_Update_DataRootSet_Datas(DataTable);
							}
							else
							{
								UE_LOG(LogCsEditor, Warning, TEXT("UCsEdEngine::OnObjectPreSave: DataRootSet: %s DataTables: %s RowStruct: %s != FCsDataEntry_Data."), *(O->GetName()), *(DataTable->GetName()), *(DataTable->GetRowStruct()->GetName()));
							}
						}
						// ScriptDatas
						if (DataTable == DataRootSet.ScriptDatas)
						{
							if (FCsDataEntry_ScriptData::StaticStruct() == DataTable->GetRowStruct())
							{
								OnObjectPreSave_Update_DataRootSet_ScriptDatas(DataTable);
							}
							else
							{
								UE_LOG(LogCsEditor, Warning, TEXT("UCsEdEngine::OnObjectPreSave: DataRootSet: %s DataTables: %s RowStruct: %s != FCsDataEntry_ScriptData."), *(O->GetName()), *(DataTable->GetName()), *(DataTable->GetRowStruct()->GetName()));
							}
						}
						// DataTables
						if (DataTable == DataRootSet.DataTables)
						{
							if (FCsDataEntry_DataTable::StaticStruct() == DataTable->GetRowStruct())
							{
								OnObjectPreSave_Update_DataRootSet_DataTables(DataTable);
							}
							else
							{
								UE_LOG(LogCsEditor, Warning, TEXT("UCsEdEngine::OnObjectPreSave: DataRootSet: %s DataTables: %s RowStruct: %s != FCsDataEntry_DataTable."), *(O->GetName()), *(DataTable->GetName()), *(DataTable->GetRowStruct()->GetName()));
							}
						}
						// Payloads
						if (DataTable == DataRootSet.Payloads)
						{
							if (FCsPayload::StaticStruct() == DataTable->GetRowStruct())
							{
								OnObjectPreSave_Update_DataRootSet_Payloads(DataTable);
							}
							else
							{
								UE_LOG(LogCsEditor, Warning, TEXT("UCsEdEngine::OnObjectPreSave: DataRootSet: %s Payloads: %s RowStruct: %s != FCsPayload."), *(O->GetName()), *(DataTable->GetName()), *(DataTable->GetRowStruct()->GetName()));
							}
						}
					}
				}
			}
			// Enum Struct
			if (UserSettings->bOnSave_DataTable_EnumStructLayoutResolveChanges)
			{			
				UCsDeveloperSettings* ModuleSettings = GetMutableDefault<UCsDeveloperSettings>();

				TSoftObjectPtr<UDataTable> DataTableSoftObject(DataTable);

				TMap<FName, FCsEnumStructLayoutHistory>& EnumStructlayoutHistoryMap = ModuleSettings->EnumStructlayoutHistoryMap;

				bool bResolveLayoutChanges = false;

				for (TPair<FName, FCsEnumStructLayoutHistory>& Pair : EnumStructlayoutHistoryMap)
				{
					FCsEnumStructLayoutHistory& History = Pair.Value;

					if (History.DataTable == DataTableSoftObject)
					{
						bResolveLayoutChanges = true;
						break;
					}
				}

				if (bResolveLayoutChanges)
					EnumStructTool.ResolveLayoutChangesImpl(false);
			}
		}
	}
	// LevelScriptActor
	if (ACsLevelScriptActor* LevelScriptActor = Cast<ACsLevelScriptActor>(Object))
	{
		OnObjectPreSave_Update_DataRootSet_Payload(LevelScriptActor->Payload);
	}

	// Data
	if (UserSettings->bOnSave_Data_PopulatePaths)
	{
		typedef NCsBlueprint::FLibrary BlueprintLibrary;
		typedef NCsData::FLibrary DataLibrary;

		if (BlueprintLibrary::Is(Object))
		{
			UObject* DefaultObject = nullptr;
			UObject* BpC		   = BlueprintLibrary::GetSafeClass(Object);

			if (UObject* DOb = BlueprintLibrary::GetSafeDefaultObject(Object))
			{
				DefaultObject = DOb;
			}
			else
			if (UObject* CDOb = BlueprintLibrary::GetSafeClassDefaultObject(Object))
			{
				DefaultObject = CDOb;
			}
		
			if (DataLibrary::SafeImplements(DefaultObject))
			{
				TSoftClassPtr<UObject> ObjectSoftClass(BpC);

				TArray<UObject*> ObjectsToSave;

				UCsDataSettings* DataSettings = GetMutableDefault<UCsDataSettings>();

				// DataRootSet
				TSet<TSoftClassPtr<UObject>> DataRootSets;

				const int32 Count = (int32)ECsPlatform::ECsPlatform_MAX;

				for (int32 I = 0; I < Count; ++I)
				{
					DataRootSets.Add(DataSettings->DataRootSets[I].DataRootSet);
				}

				for (TSoftClassPtr<UObject> SoftClass : DataRootSets)
				{
					UClass* Class					  = SoftClass.LoadSynchronous();
					UObject* O						  = Class ? Class->GetDefaultObject<UObject>() : nullptr;
					ICsGetDataRootSet* GetDataRootSet = O ? Cast<ICsGetDataRootSet>(O) : nullptr;

					bool Found = false;

					// DataRootSet
					if (GetDataRootSet)
					{
						const FCsDataRootSet& DataRootSet = GetDataRootSet->GetCsDataRootSet();

						// Datas
						{
							UDataTable* Datas = DataRootSet.Datas;

							const TMap<FName, uint8*>& RowMap = Datas->GetRowMap();

							for (const TPair<FName, uint8*>& Pair : RowMap)
							{
								const FName& RowName	  = Pair.Key;
								FCsDataEntry_Data* RowPtr = reinterpret_cast<FCsDataEntry_Data*>(Pair.Value);

								if (ObjectSoftClass == RowPtr->Data)
								{
									DataEntryTool.Data_PopulateImpl(RowPtr);
									Datas->MarkPackageDirty();
									ObjectsToSave.Add(Datas);

									Found = true;
									break;
								}
							}

							if (Found)
								continue;
						}
						// ScriptDatas
						{
							UDataTable* ScriptDatas = DataRootSet.ScriptDatas;

							const TMap<FName, uint8*>& RowMap = ScriptDatas->GetRowMap();

							for (const TPair<FName, uint8*>& Pair : RowMap)
							{
								const FName& RowName			= Pair.Key;
								FCsDataEntry_ScriptData* RowPtr = reinterpret_cast<FCsDataEntry_ScriptData*>(Pair.Value);

								if (ObjectSoftClass == RowPtr->Data)
								{
									DataEntryTool.ScriptData_PopulateImpl(RowPtr);
									ScriptDatas->MarkPackageDirty();
									ObjectsToSave.Add(ScriptDatas);

									Found = true;
									break;
								}
							}

							if (Found)
								continue;
						}
						// DataTables
						{
							UDataTable* DataTables = DataRootSet.DataTables;

							const TMap<FName, uint8*>& RowMap = DataTables->GetRowMap();

							for (const TPair<FName, uint8*>& Pair : RowMap)
							{
								const FName& RowName		   = Pair.Key;
								FCsDataEntry_DataTable* RowPtr = reinterpret_cast<FCsDataEntry_DataTable*>(Pair.Value);

								// Search each row for each DataTable if it contains a reference to Data (Object)
								if (UDataTable* DT = RowPtr->DataTable.LoadSynchronous())
								{
									typedef NCsProperty::FLibrary PropertyLibrary;

									const UScriptStruct* RowStruct	   = DT->GetRowStruct();
									const TMap<FName, uint8*>& _RowMap = DT->GetRowMap();

									for (const TPair<FName, uint8*>& _Pair : _RowMap)
									{
										uint8* _RowPtr = _Pair.Value;

										// Look for a Struct with Property Name: Data
										UStruct* Struct = nullptr;
										uint8* StructValue = nullptr;;

										if (PropertyLibrary::GetStructPropertyValuePtr(Context, _RowPtr, RowStruct, Name::Data, Struct, StructValue, nullptr))
										{
											// Look for a SoftClassPtr with Property Name: Data
											if (FSoftObjectPtr* SoftObjectPtr = PropertyLibrary::GetSoftClassPropertyValuePtr(Context, StructValue, Struct, Name::Data, nullptr))
											{
												if (ObjectSoftClass.ToSoftObjectPath() == SoftObjectPtr->ToSoftObjectPath())
												{
													DataEntryTool.DataTable_PopulateImpl(DataTables, RowName, RowPtr, false);
													DataTables->MarkPackageDirty();
													ObjectsToSave.Add(DataTables);

													Found = true;
													break;
												}
											}
										}
										// Look for a SoftClassPtr with Property Name: Data
										if (FSoftObjectPtr* SoftObjectPtr = PropertyLibrary::GetSoftClassPropertyValuePtr(Context, StructValue, Struct, Name::Data, nullptr))
										{
											if (ObjectSoftClass.ToSoftObjectPath() == SoftObjectPtr->ToSoftObjectPath())
											{
												DataEntryTool.DataTable_PopulateImpl(DataTables, RowName, RowPtr, false);
												DataTables->MarkPackageDirty();
												ObjectsToSave.Add(DataTables);

												Found = true;
												break;
											}
										}
									}
								}

								if (Found)
									break;
							}
						}
					}
				}
				UPackageTools::SavePackagesForObjects(ObjectsToSave);
			}
		}
	}
}

#pragma endregion Save

// Stream
#pragma region

bool UCsEdEngine::Stream_GetString(const TCHAR*& Str, const FString& StringType, FString& OutString, const FString& Check, const FString& Format)
{
	typedef NCsString::FLibrary StringLibrary;

	const bool Success = StringLibrary::Stream_GetValue(Str, OutString, false);

	if (Success)
	{
		UE_LOG(LogCsEditor, Warning, TEXT("Check_%s: No %s set."), *Check, *StringType);
		UE_LOG(LogCsEditor, Warning, TEXT("Check_%s: The correct format is %s"), *Check, *Format);
		return false;
	}
	return true;
}

#pragma endregion

// DataRootSet
#pragma region

void UCsEdEngine::OnObjectPreSave_Update_DataRootSet_Datas(UDataTable* DataTable)
{
	using namespace NCsEdEngine::NCached;

	const FString& Context = Str::OnObjectPreSave_Update_DataRootSet_Datas;

	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& RowName	  = Pair.Key;
		FCsDataEntry_Data* RowPtr = reinterpret_cast<FCsDataEntry_Data*>(Pair.Value);

		RowPtr->Name = RowName;

		if (RowPtr->bPopulateOnSave)
		{
			if (CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate))
			{
				UE_LOG(LogCsEditor, Warning, TEXT("%s: Populating Paths for %s.%s."), *Context, *(DataTable->GetName()), *(RowName.ToString()));
			}

			DataEntryTool.Data_PopulateImpl(RowPtr);

			RowPtr->bPopulateOnSave = false;
		}
	}
}

void UCsEdEngine::OnObjectPreSave_Update_DataRootSet_ScriptDatas(UDataTable* DataTable)
{
	using namespace NCsEdEngine::NCached;

	const FString& Context = Str::OnObjectPreSave_Update_DataRootSet_ScriptDatas;

	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& RowName			= Pair.Key;
		FCsDataEntry_ScriptData* RowPtr = reinterpret_cast<FCsDataEntry_ScriptData*>(Pair.Value);

		RowPtr->Name = RowName;

		if (RowPtr->bPopulateOnSave)
		{
			if (CS_CVAR_LOG_IS_SHOWING(LogDataEntryPopulate))
			{
				UE_LOG(LogCsEditor, Warning, TEXT("%s: Populating Paths for %s.%s."), *Context, *(DataTable->GetName()), *(RowName.ToString()));
			}

			DataEntryTool.ScriptData_PopulateImpl(RowPtr);

			RowPtr->bPopulateOnSave = false;
		}
	}
}

void UCsEdEngine::OnObjectPreSave_Update_DataRootSet_DataTables(UDataTable* DataTable)
{
	using namespace NCsEdEngine::NCached;

	const FString& Context = Str::OnObjectPreSave_Update_DataRootSet_DataTables;

	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();
	
	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& RowName		   = Pair.Key;
		FCsDataEntry_DataTable* RowPtr = reinterpret_cast<FCsDataEntry_DataTable*>(Pair.Value);

		RowPtr->Name = RowName;

		if (RowPtr->bPopulateOnSave)
		{
			DataEntryTool.DataTable_PopulateImpl(DataTable, RowName, RowPtr, false);

			RowPtr->bPopulateOnSave = false;
		}
	}
}

void UCsEdEngine::OnObjectPreSave_Update_DataRootSet_Payloads(UDataTable* DataTable)
{
	// Get Settings
	UCsDataSettings* DataSettings = GetMutableDefault<UCsDataSettings>();

	// TODO: FIX
	return;

	if (!DataSettings)
		return;

	// Get DataRootSet
	TSoftClassPtr<UObject> SoftObject	= DataSettings->DataRootSet;
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

		OnObjectPreSave_Update_DataRootSet_Payload(*RowPtr);
	}
}

void UCsEdEngine::OnObjectPreSave_Update_DataRootSet_Payload(FCsPayload& Payload)
{
	//using namespace NCsEdEngine::NCached;

	//const FString& Context = Str::OnObjectPreSave_Update_DataRootSet_Payload;

	//// Get Settings
	//UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	//// TODO: FIX
	//return;

	//if (!Settings)
	//	return;

	//// Get DataRootSet
	//TSoftClassPtr<UObject> SoftObject	= Settings->DataRootSet;
	//UClass* Class						= SoftObject.LoadSynchronous();
	//UObject* Object						= Class ? Class->GetDefaultObject<UObject>() : nullptr;
	//ICsGetDataRootSet* GetDataRootSet	= Object ? Cast<ICsGetDataRootSet>(Object) : nullptr;

	//if (!GetDataRootSet)
	//	return;

	//// Add / Update the Payload to the Datas | DataTables
	//if (Payload.bUpdateDataRootSetOnSave)
	//{
	//	FCsDataRootSet& DataRootSet = const_cast<FCsDataRootSet&>(GetDataRootSet->GetCsDataRootSet());

	//	// Datas

	//	// DataTables
	//	if (UDataTable* DataTables = DataRootSet.DataTables)
	//	{
	//		for (FCsPayload_DataTable& Payload_DataTable : Payload.DataTables)
	//		{
	//			// Check Name is Valid
	//			const FName& Name = Payload_DataTable.Name;

	//			if (Name == NAME_None)
	//			{
	//				UE_LOG(LogCsEditor, Warning, TEXT("%s: Name is NOT Valid."), *Context);
	//				continue;
	//			}

	//			// Check for Valid Path
	//			TSoftObjectPtr<UDataTable>& DT = Payload_DataTable.DataTable;
	//			const FSoftObjectPath& Path	   = DT.ToSoftObjectPath();

	//			if (!Path.IsValid())
	//			{
	//				UE_LOG(LogCsEditor, Warning, TEXT("%s: Path is NOT Valid for Name: %s."), *Context, *(Name.ToString()));
	//				continue;
	//			}

	//			// Add to Map of DataTables to Add to DataRootSet->DataTables
	//			if (Payload_DataTable.bAllRows)
	//				DataRootSet.AddDataTable(Name, DT);
	//			else
	//				DataRootSet.AddDataTable(Name, DT, Payload_DataTable.Rows);
	//		}
	//	}
	//}
	//Payload.bUpdateDataRootSetOnSave = false;
}

#pragma endregion DataRootSet

// Asset
#pragma region

bool UCsEdEngine::Check_LoadObject(const TCHAR* Stream)
{
	const FString Command	 = TEXT("LoadObject");
	const FString Parameters = TEXT("[path]");
	const FString Format	 = Command + TEXT(" ") + Parameters;

	if (FParse::Command(&Stream, *Command))
	{
		typedef NCsString::FLibrary StringLibrary;

		FString AssetPath;
		
		const bool Success = StringLibrary::Stream_GetValue(Stream, AssetPath, false);

		if (Success)
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
		UCsDataSettings* DataSettings = GetMutableDefault<UCsDataSettings>();
		DataSettings->DataRootSet	  = DataSettings->GetDataRootSet(ECsPlatform::Windows);

		FPropertyChangedEvent PropChangeEvent(UCsDataSettings::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(UCsDataSettings, DataRootSet)));
		DataSettings->PostEditChangeProperty(PropChangeEvent);
		DataSettings->TryUpdateDefaultConfigFile();

		UProjectPackagingSettings* PackageSettings		   = GetMutableDefault< UProjectPackagingSettings>();
		PackageSettings->DirectoriesToAlwaysCook[CS_FIRST] = DataSettings->GetDirectoryToAlwaysCook(ECsPlatform::Windows);
		PackageSettings->TryUpdateDefaultConfigFile();
	}

	Outer->SetPlayMode(ECsPlayMode::ECsPlayMode_MAX);
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

#undef USING_NS_CACHED
#undef SET_CONTEXT