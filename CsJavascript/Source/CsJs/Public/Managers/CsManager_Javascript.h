// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "CsTypes_Javascript.h"
#include "EntryPoint/CsTypes_ScriptEntryPointInfo.h"
#include "Script/CsTypes_ScriptInfo.h"
// Log
#include "Utility/CsLog.h"

#include "CsManager_Javascript.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerJavascript_OnShutdown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerJavascript_OnShutdownScripts);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerJavascript_OnPreReloadScript, const int32&, Index);

#pragma endregion Delegates

class ICsGetManagerJavascript;
struct FCsRoutine;
class UGameInstance;

UCLASS()
class CSJS_API UCsManager_Javascript : public UObject
{
	GENERATED_UCLASS_BODY()

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

	static ICsGetManagerJavascript* GetSafe_GetManagerJavascript(const FString& Context, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);
	static ICsGetManagerJavascript* GetSafe_GetManagerJavascript(UObject* Object);

public:

	static UCsManager_Javascript* GetSafe(const FString& Context, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);
	static UCsManager_Javascript* GetSafe(UObject* Object);

	static UCsManager_Javascript* GetFromWorldContextObject(const FString& Context, const UObject* WorldContextObject, void(*Log)(const FString&) = &FCsLog::Warning);
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
	void ConditionalCreateScriptObject();
	void SetupScriptObjects(UGameInstance* GameInstance = nullptr);

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

	void RunScripts();

	void ReloadScript(const int32& Index);

	UPROPERTY(BlueprintAssignable)
	FCsManagerJavascript_OnPreReloadScript OnPreReloadScript_ScriptEvent;

	void ShutdownScripts();

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

		UCsManager_Javascript* Outer;

	public:

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
			OwnerByOwnerIdMap(),
			IndexByOwnerIdMap(),
			IdByOwnerIdMap(),
			OwnerIdByIdMap()
		{
		}

		FORCEINLINE TArray<FCsJavascriptFileObjects>& GetObjects() { return Outer->GetEditorScriptObjects(); }

		void Validate();

		FGuid CreateAndRun(UObject* Owner, const FString& Path);

		void Shutdown(UObject* Owner);
	};

	FEditorScriptImpl EditorScriptImpl;

#pragma endregion Editor Scripts

// Events
#pragma region
public:

	void SetupCallbacks();

private:

	void OnAnyKey_Pressed(const FKey& Key);

#pragma endregion Events
};