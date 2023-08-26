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
	static void DataEntry_DataTable_PopulateImpl(UObject* DataTable, const FName& RowName, FCsDataEntry_DataTable* Entry, const bool& AllRows);

#pragma endregion GetDataEntryTool

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

	void OnObjectPreSave(UObject* Object, FObjectPreSaveContext Context);

#pragma endregion Save

// PIE
#pragma region
protected:

	virtual void OnBeginPIE(bool IsSimulating);
	virtual void OnEndPIE(bool IsSimulating);

public:

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Editor|Engine|PIE")
	FCsEdEngine_OnEndPIE OnEndPIE_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Editor|Engine|PIE")
	FCsEdEngine_OnEndPIE OnEndPIE_Last_ScriptEvent;

protected:

	void OnEndPIE_NextFrame(bool IsSimulating);
	char OnEndPIE_NextFrame_Internal(FCsRoutine* R);

	virtual void OnEndPlayMapPIE(bool IsSimulating);

#pragma endregion PIE

// Stream
#pragma region
public:

	bool Stream_GetString(const TCHAR*& Str, const FString& StringType, FString& OutString, const FString& Check, const FString& Format);

#pragma endregion Stream

// DataRootSet
#pragma region
public:

	void OnObjectPreSave_Update_DataRootSet_Datas(UDataTable* DataTable);

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
