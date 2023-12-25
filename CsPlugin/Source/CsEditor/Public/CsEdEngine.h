// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Editor/UnrealEdEngine.h"
// Interfaces
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Object/CsGetCreatedObjects.h"
#include "Play/Mode/CsGetPlayMode.h"
#include "Data/Tool/CsGetDataEntryTool.h"
#include "UI/Tool/CsGetSlateApplicationTool.h"
#include "Asset/Tool/CsGetAssetTool.h"
#include "Types/Enum/Tool/CsGetEnumStructTool.h"
#include "Data/Tool/CsGetDataTableTool.h"
#include "SourceControl/Tool/CsGetSourceControlTool.h"
#include "Asset/Event/CsAsset_Event.h"
#include "Level/Editor/Event/CsLevelEditor_Event.h"
#include "PIE/Event/CsPIE_Event.h"
#include "Animation/Event/CsAnimation_Event.h"
// Types
#include "Object/CsTypes_Object.h"
#include "Data/CsTypes_Payload.h"
// Object
#include "UObject/ObjectSaveContext.h"

#include "CsEdEngine.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsEdEngine_OnEndPIE, bool, IsSimulating);

#pragma endregion Delegates

struct FCsRoutine;

struct FCsDataEntry_Data;
struct FCsDataEntry_DataTable;

UCLASS()
class CSEDITOR_API UCsEdEngine : public UUnrealEdEngine,
								 public ICsGetManagerSingleton,
								 public ICsGetCreatedObjects,
								 public ICsGetPlayMode,
								 public ICsGetDataEntryTool,
								 public ICsGetSlateApplicationTool,
								 public ICsGetAssetTool,
								 public ICsGetEnumStructTool,
								 public ICsGetDataTableTool,
								 public ICsGetSourceControlTool,
								 public ICsAsset_Event,
								 public ICsLevelEditor_Event,
								 public ICsPIE_Event,
								 public ICsAnimation_Event // TODO: Move
{
public:

	GENERATED_BODY()

// UEngine Interface
#pragma region
public:

	virtual void Init(IEngineLoop* InEngineLoop) override;
	virtual void PreExit() override;
	virtual void Tick(float DeltaSeconds, bool bIdleMode) override;

#pragma endregion UEngine Interface

// UEditorEngine Interface
#pragma region
public:

	virtual void LaunchNewProcess(const FRequestPlaySessionParams& InParams, const int32 InInstanceNum, EPlayNetMode NetMode, bool bIsDedicatedServer) override;

#pragma endregion UUEditorEngine Interface

// FExec Interface
#pragma region
public:

	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar = *GLog) override;

#pragma endregion FExec Interface

// ICsGetManagerSingleton
#pragma region
public:

	FORCEINLINE UCsManager_Singleton* GetManager_Singleton() const { return Manager_Singleton; }

#pragma endregion ICsGetManagerSingleton

// Managers
#pragma region
protected:

	UPROPERTY()
	UCsManager_Singleton* Manager_Singleton;

	virtual void ConstructManagerSingleton() {}

#pragma endregion Managers

// Init
#pragma region
private:

	void PostInit();
	char PostInit_Internal(FCsRoutine* R);

protected:

	bool bPostInit;

	void SetPostInit() { bPostInit = true; }

	virtual void OnPostInit();

#pragma endregion Init

// World
#pragma region
protected:

	void OnWorldContextDestroyed_Internal(FWorldContext& WorldContext);

#pragma endregion World

// ICsGetCreatedObjects
#pragma region
public:

#define CreatedObjectsType NCsObject::NCreate::FCreated

	FORCEINLINE CreatedObjectsType* GetCreatedObjects() { return &CreatedObjects; }

#undef CreatedObjectsType

#pragma endregion ICsGetCreatedObjects

// Object
#pragma region
public:

#define CreatedObjectsType NCsObject::NCreate::FCreated

	CreatedObjectsType CreatedObjects;

#undef CreatedObjectsType

#pragma endregion Object

// ICsGetPlayMode
#pragma region
public:

	FORCEINLINE const ECsPlayMode& GetPlayMode() const { return PlayMode; }

#pragma endregion ICsGetPlayMode

// PlayMode
#pragma region
protected:

	ECsPlayMode PlayMode;

public:

	void SetPlayMode(const ECsPlayMode& Value) { PlayMode = Value; }

#pragma endregion PlayMode

// ICsGetDataEntryTool
#pragma region
public:

#define DataEntryToolType NCsData::NEntry::NTool::FImpl
	FORCEINLINE DataEntryToolType* GetDataEntryTool() { return &DataEntryTool; }
#undef DataEntryToolType

#pragma endregion ICsGetDataEntryTool

// GetDataEntryTool
#pragma region
private:

#define DataEntryToolType NCsData::NEntry::NTool::FImpl
	DataEntryToolType DataEntryTool;
#undef DataEntryToolType

	static void DataEntry_Data_PopulateImpl(FCsDataEntry_Data* Entry);
	static void DataEntry_ScriptData_PopulateImpl(FCsDataEntry_ScriptData* Entry);
	static void DataEntry_DataTable_PopulateImpl(UObject* DataTable, const FName& RowName, FCsDataEntry_DataTable* Entry, const bool& AllRows);

#pragma endregion GetDataEntryTool

// ICsGetSlateApplicationTool
#pragma region
public:

#define SlateApplicationToolType NCsSlate::NApplication::NTool::FImpl
	FORCEINLINE SlateApplicationToolType* GetSlateApplicationTool() { return &SlateApplicationTool; }
#undef SlateApplicationToolType

#pragma endregion ICsGetSlateApplicationTool

// GetSlateApplicationTool
#pragma region
private:

#define SlateApplicationToolType NCsSlate::NApplication::NTool::FImpl
	SlateApplicationToolType SlateApplicationTool;
#undef SlateApplicationToolType

	static void ApplyApplicationScaleImpl(const float& ApplicationScale); 

#pragma endregion GetSlateApplicationTool

// ICsGetAssetTool
#pragma region
public:

#define AssetToolType NCsAsset::NTool::FImpl
	FORCEINLINE AssetToolType* GetAssetTool() { return &AssetTool; }
#undef AssetToolType

#pragma endregion ICsGetAssetTool

// GetAssetTool
#pragma region
private:

#define AssetToolType NCsAsset::NTool::FImpl
	AssetToolType AssetTool;
#undef AssetToolType

	TArray<UObject*> OpenedAssets;

public:

	const TArray<UObject*>& GetOpenedAssets() const { return OpenedAssets; }

private:

	static const TArray<UObject*>& GetOpenedAssets_Internal();

#pragma endregion GetAssetTool

// ICsGetEnumStructTool
#pragma region
public:

#define EnumStructToolType NCsEnum::NStruct::NTool::FImpl
	FORCEINLINE EnumStructToolType& GetEnumStructTool() { return EnumStructTool; }
#undef EnumStructToolType

#pragma endregion ICsGetEnumStructTool

// GetEnumStructTool
#pragma region
private:

#define EnumStructToolType NCsEnum::NStruct::NTool::FImpl
	EnumStructToolType EnumStructTool;
#undef EnumStructToolType

public:

	virtual void EnumStruct_ResolveLayoutChanges(bool bForce);

private:

	static void EnumStruct_ResolveLayoutChanges_Internal(bool bForce);

#pragma endregion GetEnumStructTool

// ICsGetDataTableTool
#pragma region
public:

#define DataTableToolType NCsDataTable::NTool::FImpl
	FORCEINLINE DataTableToolType* GetDataTableTool() { return &DataTableTool; }
#undef DataTableToolType

#pragma endregion ICsGetDataTableTool

// GetDataTableTool
#pragma region
private:

#define DataTableToolType NCsDataTable::NTool::FImpl
	DataTableToolType DataTableTool;
#undef DataTableToolType

#pragma endregion GetDataTableTool

// ICsGetSourceControlTool
#pragma region
public:

#define SourceControlToolType NCsSourceControl::NTool::FImpl
	FORCEINLINE SourceControlToolType* GetSourceControlTool() { return &SourceControlTool; }
#undef SourceControlToolType

#pragma endregion ICsGetSourceControlTool

// GetSourceControlTool
#pragma region
private:

#define SourceControlToolType NCsSourceControl::NTool::FImpl
	SourceControlToolType SourceControlTool;
#undef SourceControlToolType

#pragma endregion GetSourceControlTool

// ICsAsset_Event
#pragma region
public:

	FORCEINLINE ICsAsset_Event::FOnOpenedInEditor& GetAsset_OpenedInEditor_Event() { return Asset_OnOpenedInEditor_Event; }
	FORCEINLINE ICsAsset_Event::FOnUniqueOpenedInEditor& GetAsset_UniqueOpenedInEditor_Event() { return Asset_OnUniqueOpenedInEditor_Event; }
	FORCEINLINE ICsAsset_Event::FOnRequest_Close& GetAssetEditor_OnRequest_Close_Event() { return AssetEditor_OnRequest_Close_Event; }
	FORCEINLINE FCsAssetEditor_OnRequest_Close& GetAssetEditor_OnRequest_Close_ScriptEvent() { return AssetEditor_OnRequest_Close_ScriptEvent; }

#pragma endregion ICsAsset_Event

// Asset_Event
#pragma region
public:

	ICsAsset_Event::FOnOpenedInEditor Asset_OnOpenedInEditor_Event;
	ICsAsset_Event::FOnUniqueOpenedInEditor Asset_OnUniqueOpenedInEditor_Event;
	ICsAsset_Event::FOnRequest_Close AssetEditor_OnRequest_Close_Event;

	UPROPERTY(BlueprintAssignable)
	FCsAssetEditor_OnRequest_Close AssetEditor_OnRequest_Close_ScriptEvent;	

private:

	void OnAssetOpenedInEditor(UObject* Asset, IAssetEditorInstance* EditorInstance);
	void OnAssetEditorRequestClose(UObject* Asset, EAssetEditorCloseReason Reason);

#pragma endregion Asset_Event

// ICsLevelEditor_Event
#pragma region
public:

	FORCEINLINE ICsLevelEditor_Event::FOnActorSelectionChanged& GetOnActorSelectionChanged_Event() { return OnActorSelectionChanged_Event; }
	FORCEINLINE FCsLevelEditor_OnActorSelectionChanged& GetOnActorSelectionChanged_ScriptEvent() { return OnActorSelectionChanged_ScriptEvent; }

#pragma endregion ICsLevelEditor_Event

// LevelEditor_Event
#pragma region
public:

	ICsLevelEditor_Event::FOnActorSelectionChanged OnActorSelectionChanged_Event;

	UPROPERTY(BlueprintAssignable)
	FCsLevelEditor_OnActorSelectionChanged OnActorSelectionChanged_ScriptEvent;	

private:

	void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);

#pragma endregion LevelEditor_Event

// ICsPIE_Event
#pragma region
public:

	FORCEINLINE FCsPIE_OnBegin& GetPIE_OnBegin_ScriptEvent() { return PIE_OnBegin_ScriptEvent; }
	FORCEINLINE FCsPIE_OnEnd& GetPIE_OnEnd_ScriptEvent() { return PIE_OnEnd_ScriptEvent; }
	FORCEINLINE FCsPIE_OnEnd_Last& GetPIE_OnEnd_Last_ScriptEvent() { return PIE_OnEnd_Last_ScriptEvent; }
	FORCEINLINE FCsPIE_OnEnd_NextFrame& GetPIE_OnEnd_NextFrame_ScriptEvent() { return PIE_OnEnd_NextFrame_ScriptEvent; }
	FORCEINLINE FCsPIE_OnEndPlayMap& GetPIE_OnEndPlayMap_ScriptEvent() { return PIE_OnEndPlayMap_ScriptEvent; }

#pragma endregion ICsPIE_Event

// PIE_Event
#pragma region
protected:

	virtual void OnBeginPIE(bool IsSimulating);

public:

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Editor|Engine|PIE")
	FCsPIE_OnBegin PIE_OnBegin_ScriptEvent;

protected:

	virtual void OnEndPIE(bool IsSimulating);

public:

	/** DEPRECATED */
	UPROPERTY(BlueprintAssignable, Category = "CsCore|Editor|Engine|PIE")
	FCsPIE_OnEnd OnEndPIE_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Editor|Engine|PIE")
	FCsPIE_OnEnd PIE_OnEnd_ScriptEvent;

	/** DEPRECATED */
	UPROPERTY(BlueprintAssignable, Category = "CsCore|Editor|Engine|PIE")
	FCsPIE_OnEnd_Last OnEndPIE_Last_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Editor|Engine|PIE")
	FCsPIE_OnEnd_Last PIE_OnEnd_Last_ScriptEvent;

protected:

	void OnEndPIE_NextFrame(bool IsSimulating);
	char OnEndPIE_NextFrame_Internal(FCsRoutine* R);

	virtual void OnEndPlayMapPIE(bool IsSimulating);

public:

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Editor|Engine|PIE")
	FCsPIE_OnEnd_NextFrame PIE_OnEnd_NextFrame_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Editor|Engine|PIE")
	FCsPIE_OnEndPlayMap PIE_OnEndPlayMap_ScriptEvent;

#pragma endregion PIE_Event

// ICsAnimation_Event
#pragma region
public:

	FORCEINLINE ICsAnimation_Event::FOnInit& GetOnInit_Event() { return AnimationEvent_OnInit_Event; }
	FORCEINLINE FCsAnimationEvent_OnInit& GetOnInit_ScriptEvent() { return AnimationEvent_OnInit_ScriptEvent; }

#pragma endregion ICsAnimation_Event

// Animation_Event
#pragma region
public:

	ICsAnimation_Event::FOnInit AnimationEvent_OnInit_Event;

	UPROPERTY(BlueprintAssignable)
	FCsAnimationEvent_OnInit AnimationEvent_OnInit_ScriptEvent;

#pragma endregion Animation_Event

// PropertyChange
#pragma region
public:

void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& e);

#pragma endregion PropertyChange

// Save
#pragma region
public:

	void OnObjectPreSave(UObject* Object, FObjectPreSaveContext SaveContext);

#pragma endregion Save

// Stream
#pragma region
public:

	bool Stream_GetString(const TCHAR*& Str, const FString& StringType, FString& OutString, const FString& Check, const FString& Format);

#pragma endregion Stream

// DataRootSet
#pragma region
public:

	void OnObjectPreSave_Update_DataRootSet_Datas(UDataTable* DataTable);

	void OnObjectPreSave_Update_DataRootSet_ScriptDatas(UDataTable* DataTable);

	void OnObjectPreSave_Update_DataRootSet_DataTables(UDataTable* DataTable);

	void OnObjectPreSave_Update_DataRootSet_Payloads(UDataTable* DataTable);

	void OnObjectPreSave_Update_DataRootSet_Payload(FCsPayload& Payload);

#pragma endregion DataRootSet

// References
#pragma region
public:

	bool Check_PrintBlueprintReferencesReport(const TCHAR* Stream);

	void PrintBlueprintReferencesReport(const FName& AssetName);

#pragma endregion References

// Asset
#pragma region
public:

	bool Check_GetObjectPaths(const TCHAR* Stream);
	void GetObjectPaths(const FString& AssetPath);

	bool Check_LoadObject(const TCHAR* Stream);
	void LoadObject(const FString& AssetPath);

#pragma endregion Asset

// Standalone
#pragma region
protected:

	struct FStandalone
	{
		friend class UCsEdEngine;

	public:

		UCsEdEngine* Outer;

		bool bActive;

		uint32 ProcessID;

		FStandalone() :
			Outer(nullptr),
			bActive(false),
			ProcessID(0)
		{
		}

		void Reset()
		{
			bActive   = false;
			ProcessID = 0;
		}

		void Monitor();
		char Monitor_Internal(FCsRoutine* R);
	};

	FStandalone Standalone;

	void OnStandaloneLocalPlayEvent(uint32 ProcessID);
	
#pragma endregion Standalone
};
