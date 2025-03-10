// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Interface
#include "Instance/CsGetJavascriptInstance.h"
#include "Isolate/CsGetJavascriptIsolate.h"
// Types
#include "CsMacro_Cached.h"
#include "CsTypes_Javascript.h"
#include "EntryPoint/CsTypes_ScriptEntryPointInfo.h"
#include "Script/CsTypes_ScriptInfo.h"
// Managers
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// Log
#include "Utility/CsJsLog.h"

#include "CsManager_Javascript.generated.h"

// Structs
#pragma region

namespace NCsJs
{
	namespace NFileObject
	{
		struct CSJS_API FResource : public TCsResourceContainer<FCsJavascriptFileObjects>
		{
			~FResource(){}
		};

		struct CSJS_API FManager : public NCsResource::NManager::NPointer::TFixed<FCsJavascriptFileObjects, FResource, 0>
		{
			~FManager(){}
		};
	}
}

#pragma endregion Structs

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerJavascript_OnShutdown);
// Scripts
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerJavascript_OnShutdownScripts_Start);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerJavascript_OnShutdownScripts);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerJavascript_OnPreReloadScript, const int32&, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerJavascript_OnRunScriptsComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerJavascript_OnSetupAndRunScriptsComplete);
// Editor Scripts
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerJavascript_EditorScript_OnShutdown, const FGuid&, Id);

#pragma endregion Delegates

class FJavascriptInstance;
class FJavascriptIsolate;

class ICsGetManagerJavascript;
struct FCsRoutine;
class UGameInstance;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME(CsManager_Javascript)
CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_1(NCsManager_Javascript, EditorScriptImpl)

UCLASS()
class CSJS_API UCsManager_Javascript : public UObject,
									   public ICsGetJavascriptInstance,
									   public ICsGetJavascriptIsolate
{
	GENERATED_UCLASS_BODY()

private:

	CS_USING_CACHED_FUNCTION_NAME(CsManager_Javascript);

// ICsGetJavascriptInstance
#pragma region
public:

	FORCEINLINE TSharedPtr<FJavascriptInstance>& GetJavascriptInstance() { return JavascriptInstance; }
	FORCEINLINE CsJavascriptInstanceInfo& GetJavascriptInstanceInfo() { return JavascriptInstanceInfo; }

#pragma endregion ICsGetJavascriptInstance

// GetJavascriptInstance
#pragma region
private:

	CsJavascriptInstanceInfo JavascriptInstanceInfo;

	TSharedPtr<FJavascriptInstance> JavascriptInstance;
	
#pragma endregion GetJavascriptInstance

// ICsGetJavascriptIsolate
#pragma region
public:

	TSharedPtr<FJavascriptIsolate> GetSharedJavascriptIsolate();

#pragma endregion ICsGetJavascriptIsolate

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Javascript* Get(UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_Javascript* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static bool IsValid(UObject* InRoot = nullptr);
#else
	FORCEINLINE static bool IsValid(UObject* InRoot = nullptr)
	{
		return s_Instance != nullptr;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot);

	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

	UPROPERTY(BlueprintAssignable)
	FCsManagerJavascript_OnShutdown OnShutdown_ScriptEvent;

#if WITH_EDITOR
protected:

	static ICsGetManagerJavascript* Get_GetManagerJavascript(UObject* InRoot);

	static ICsGetManagerJavascript* GetSafe_GetManagerJavascript(const FString& Context, UObject* Object, void(*Log)(const FString&) = &NCsJs::FLog::Warning);
	static ICsGetManagerJavascript* GetSafe_GetManagerJavascript(UObject* Object);

public:

	static UCsManager_Javascript* GetSafe(const FString& Context, UObject* Object, void(*Log)(const FString&) = &NCsJs::FLog::Warning);
	static UCsManager_Javascript* GetSafe(UObject* Object);

	static UCsManager_Javascript* GetFromWorldContextObject(const FString& Context, const UObject* WorldContextObject, void(*Log)(const FString&) = &NCsJs::FLog::Warning);
	static UCsManager_Javascript* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Javascript* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

private:

	UObject* WorldContext;

public:

	FORCEINLINE void SetWorldContext(UObject* InWorldContext) { WorldContext = InWorldContext; }

private:

	UGameInstance* GameInstance;

// Entry Point
#pragma region
private:

	UPROPERTY(Transient)
	FCsJavascriptFileObjects EntryPoint;

	FCsScriptEntryPointInfo EntryPointInfo;

public:

	FORCEINLINE void SetEntryPointInfo(const FCsScriptEntryPointInfo& Info) { EntryPointInfo = Info; }
	FORCEINLINE const FCsScriptEntryPointInfo& GetEntryPointInfo() const { return EntryPointInfo; }

	void CreateEntryPoint();
private:
	char CreateEntryPoint_Internal(FCsRoutine* R);
public:
	void SetupEntryPoint(UGameInstance* GameInstance = nullptr);

private:

	char SetupEntryPoint_Internal(FCsRoutine* R);

public:

	DECLARE_DELEGATE(FAdditionalSetupEntryPoint_Impl);

	FAdditionalSetupEntryPoint_Impl AdditionalSetupEntryPoint_Impl;

	DECLARE_DELEGATE_RetVal(bool, FIsAdditionalSetupEntryPointComplete_Impl);

	FIsAdditionalSetupEntryPointComplete_Impl IsAdditionalSetupEntryPointComplete_Impl;

private:

	bool bSetupEntryPointComplete;

public:

	FORCEINLINE bool IsSetupEntryPointComplete() const { return bSetupEntryPointComplete; }

public:

	void SetupAndRunEntryPoint(UGameInstance* GameInstance = nullptr);

private:

	char SetupAndRunEntryPoint_Internal(FCsRoutine* R);

public:

	void RunEntryPoint();
	void ShutdownEntryPoint();

#pragma endregion Entry Point

// Scripts
#pragma region
private:

	UPROPERTY(Transient)
	TArray<FCsJavascriptFileObjects> ScriptObjects;

	FCsScriptInfo ScriptInfo;

public:

	FORCEINLINE void SetScriptInfo(const FCsScriptInfo& Info) { ScriptInfo = Info; }
	FORCEINLINE const FCsScriptInfo& GetScriptInfo() const { return ScriptInfo; }

	void CreateScriptObjects();
private:
	char CreateScriptObjects_Internal(FCsRoutine* R);
public:
	void ConditionalCreateScriptObjects();
	void SetupScriptObjects(UGameInstance* InGameInstance = nullptr);

private:

	char SetupScriptObjects_Internal(FCsRoutine* R);

public:

	DECLARE_DELEGATE_OneParam(FAdditionalSetupScriptObjects_Impl, const int32& /*Index*/);

	FAdditionalSetupScriptObjects_Impl AdditionalSetupScriptObjects_Impl;

	DECLARE_DELEGATE_RetVal(bool, FIsAdditionalSetupScriptObjectsComplete_Impl);

	FIsAdditionalSetupScriptObjectsComplete_Impl IsAdditionalSetupScriptObjectsComplete_Impl;

private:

	bool bSetupScriptObjectsComplete;

public:

	FORCEINLINE bool IsSetupScriptObjectsComplete() const { return bSetupScriptObjectsComplete; }

public:

	void SetupAndRunScripts(UGameInstance* GameInstance = nullptr);

private:

	char SetupAndRunScripts_Internal(FCsRoutine* R);

public:

	UPROPERTY(BlueprintAssignable)
	FCsManagerJavascript_OnSetupAndRunScriptsComplete OnSetupAndRunScriptsComplete_ScriptEvent;

	void RunScripts();

	UPROPERTY(BlueprintAssignable)
	FCsManagerJavascript_OnRunScriptsComplete OnRunScriptsComplete_ScriptEvent;

	void ReloadScript(const int32& Index);

	UPROPERTY(BlueprintAssignable)
	FCsManagerJavascript_OnPreReloadScript OnPreReloadScript_ScriptEvent;

	void DeactivateScripts(const bool& bForce = false);
	void ShutdownScripts();

	UPROPERTY(BlueprintAssignable)
	FCsManagerJavascript_OnShutdownScripts_Start OnShutdownScripts_Start_ScriptEvent;

private:

	int32 CurrentScriptIndex;

public:

	UFUNCTION(BlueprintPure)
	const int32& GetCurrentScriptIndex() const
	{
		return CurrentScriptIndex;
	}

private:

	bool bScriptReload;

public:

	UFUNCTION(BlueprintPure)
	bool IsScriptReload() const
	{
		return bScriptReload;
	}

#pragma endregion Scripts

// Editor Scripts
#pragma region
private:

	UPROPERTY(Transient)
	TArray<FCsJavascriptFileObjects> EditorScriptObjects;

public:

	FORCEINLINE TArray<FCsJavascriptFileObjects>& GetEditorScriptObjects() { return EditorScriptObjects; }

	struct CSJS_API FEditorScriptImpl
	{
		friend class UCsManager_Javascript;

	private:

		CS_USING_CACHED_FUNCTION_NAME_NESTED_1(NCsManager_Javascript, EditorScriptImpl);

		using ObjectManagerType = NCsJs::NFileObject::FManager;

	private:

		UCsManager_Javascript* Outer;

	public:

		ObjectManagerType Manager_Objects;

		// <Owner Id, Owner>
		TMap<int32, UObject*> OwnerByOwnerIdMap;
		// <Owner Id, Script Index>
		TMap<int32, int32> IndexByOwnerIdMap;
		// <Owner Id, Script Id>
		TMap<int32, FGuid> IdByOwnerIdMap;
		// <Script Id, Owner Id>
		TMap<FGuid, int32> OwnerIdByIdMap;

		FEditorScriptImpl() :
			Outer(nullptr),
			Manager_Objects(),
			OwnerByOwnerIdMap(),
			IndexByOwnerIdMap(),
			IdByOwnerIdMap(),
			OwnerIdByIdMap()
		{
		}

		FORCEINLINE TArray<FCsJavascriptFileObjects>& GetObjects() { return Outer->GetEditorScriptObjects(); }

		void Init();
	private:
		char Init_Internal(FCsRoutine* R);

	public:

		void Validate();

		FGuid CreateAndRun(UObject* Owner, const FString& Path);

		void Reload(const FGuid& Id, const FString& Path);

		bool Shutdown(UObject* Owner);
		void Shutdown();
	};

	FEditorScriptImpl EditorScriptImpl;

	/** Index of the Editor Script in a list of Editor Scripts.
		This is first assigned with Run is called but can change over the lifetime
		of the Script if there are many Scripts running at once. 
		NOTE: FUTURE: This should be updated. */
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentEditorScriptIndex;

	/** A Unique Id assigned to the Editor Script when Run is called. 
		This will remain valid and unchanged until the Script has been Shutdown. */
	UPROPERTY(BlueprintReadWrite)
	FGuid CurrentEditorScriptId;

	/**
	* Delegate for the event when an Editor Script will be Shutdown.
	* @param Id		Unique Id associated with the Script.
	*/
	UPROPERTY(BlueprintAssignable)
	FCsManagerJavascript_EditorScript_OnShutdown EditorScript_OnShutdown_ScriptEvent;

	UFUNCTION(BlueprintCallable)
	bool EditorScript_Shutdown_ByOwner(const FString& Context, UObject* Owner);

#pragma endregion Editor Scripts

// Events
#pragma region
public:

	void SetupCallbacks();

private:

	void OnAnyKey_Pressed(const FKey& Key);

#pragma endregion Events
};