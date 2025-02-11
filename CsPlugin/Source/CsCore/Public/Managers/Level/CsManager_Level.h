// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "CsMacro_Cached.h"
#include "Managers/Level/CsTypes_Manager_Level.h"
#include "Managers/Level/CsManager_Level_Delegates.h"
#include "Level/CsLevel_Delegates.h"

#include "CsManager_Level.generated.h"

class ICsGetManagerLevel;
struct FCsRoutine;
class ULevel;
class ALevelScriptActor;
class UObject;
class UWorld;
class ULevelStreaming;
class ACsLevel_Streaming_EventHandler;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME(CsManager_Level)

UCLASS(transient, BlueprintType, Blueprintable, Meta = (ShowWorldContextPin))
class CSCORE_API UCsManager_Level : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	CS_USING_CACHED_FUNCTION_NAME(CsManager_Level);

	using ChangeMapParamsType = NCsLevel::NManager::NChangeMap::FParams;
	using OnChangeMapStartEventType = NCsLevel::NManager::FChangeMap_OnStart;
	using OnChangeMapCompleteEventType = NCsLevel::NManager::FChangeMap_OnComplete;
	using OnLevelLoadedEventType = NCsLevel::NManager::NLevel::NStreaming::FOnLoaded;
	using OnLevelUnloadedEventType = NCsLevel::NManager::NLevel::NStreaming::FOnUnloaded;
	using OnLevelShownEventType = NCsLevel::NManager::NLevel::NStreaming::FOnShown;
	using OnLevelHiddenEventType = NCsLevel::NManager::NLevel::NStreaming::FOnHidden;


// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Level* Get(const UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_Level* Get(const UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	template<typename T>
	FORCEINLINE static T* Get(const UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static UCsManager_Level* GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsManager_Level* GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Level> ManagerLevelClass, UObject* InOuter = nullptr);
	static void Init(UObject* InRoot, UObject* InOuter = nullptr);
	static void Shutdown(const UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerLevel* Get_GetManagerLevel(const UObject* InRoot);
	static ICsGetManagerLevel* GetSafe_GetManagerLevel(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

	UFUNCTION(BlueprintImplementableEvent, Category = "CsCore|Managers|Level", meta = (DisplayName = "Clean Up"))
	void ReceiveCleanUp();

private:
	// Singleton data
	static UCsManager_Level* s_Instance;
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

public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Managers|Level")
	UObject* GetWorldContext() const;

// Persistent Level
#pragma region
public:
	
	struct FFinishedLoadingPersistentLevelInfo
	{
		bool bActive;
		bool bCompleted;

		FString MapPackageName;

		FFinishedLoadingPersistentLevelInfo() :
			bActive(false),
			bCompleted(false),
			MapPackageName()
		{
		}

		FORCEINLINE bool IsActive() const { return bActive; }
		FORCEINLINE bool IsCompleted() const { return bCompleted; }
		FORCEINLINE void MarkCompleted() { bCompleted = true; }

		FORCEINLINE void Reset()
		{
			bActive = false;
			bCompleted = false;
			MapPackageName.Empty();
		}
	};

private:

	FFinishedLoadingPersistentLevelInfo FinishedLoadingPersistentLevelInfo;

public:

	FORCEINLINE bool HasFinishedLoadingPersistentLevel() const
	{
		return FinishedLoadingPersistentLevelInfo.IsCompleted();
	}

	void Check_FinishedLoadingPersistentLevel();
	void Check_FinishedLoadingPersistentLevel(const FString& MapPackageName);

	FORCEINLINE void ClearCheck_Check_FinishedLoadingPersistentLevel()
	{
		FinishedLoadingPersistentLevelInfo.Reset();
	}

protected:

	char Check_FinishedLoadingPersistentLevel_Internal(FCsRoutine* R);

#pragma endregion Persistent Level

// Change Map
#pragma region
protected:

	FString CurrentMap;

public:

	struct FChangeMapInfo
	{
		bool bActive;
		bool bCompleted;

		FString DestinationMap;

		FChangeMapInfo() :
			bActive(false),
			bCompleted(false),
			DestinationMap()
		{
		}

		FORCEINLINE bool IsActive() const { return bActive; }
		FORCEINLINE bool IsCompleted() const { return bCompleted; }
		FORCEINLINE void MarkCompleted() { bCompleted = true; }
	};

private:

	FChangeMapInfo ChangeMapInfo;

public:

	FORCEINLINE bool HasChangeMapCompleted() const { return ChangeMapInfo.IsCompleted(); }



	void ChangeMap(const ChangeMapParamsType& Params);
private:
	char ChangeMap_Internal(FCsRoutine* R);

	void ChangeMap_TransitionAsDestination(const ChangeMapParamsType& Params);
	char ChangeMap_TransitionAsDestination_Internal(FCsRoutine* R);

private:

	OnChangeMapStartEventType ChangeMap_OnStart_Event;

public:

	FORCEINLINE OnChangeMapStartEventType& GetChangeMap_OnStart_Event() { return ChangeMap_OnStart_Event; }

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Managers|Level")
	FCsManagerLevel_ChangeMap_OnStart ChangeMap_OnStart_ScriptEvent;

private:

	OnChangeMapCompleteEventType ChangeMap_OnComplete_Event;

public:

	FORCEINLINE OnChangeMapCompleteEventType& GetChangeMap_OnComplete_Event() { return ChangeMap_OnComplete_Event; }

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Managers|Level")
	FCsManagerLevel_ChangeMap_OnComplete ChangeMap_OnComplete_ScriptEvent;

#pragma endregion Change Map

// Transition
#pragma region
private:

	void GameInstance_Transition_OnFinish();

#pragma endregion Transition

// Streaming
#pragma region
private:

	TMap<uint32, ACsLevel_Streaming_EventHandler*> StreamingEventsByIdMap;

public:

	// OnAdded
	
private:

	void Level_Streaming_OnAdded(UWorld* World, ULevelStreaming* LevelStreaming);

public:

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Managers|Level|Streaming")
	FCsLevel_Streaming_OnAdded Level_Streaming_OnAdded_ScriptEvent;

	// OnLoaded

	OnLevelLoadedEventType Level_Streaming_OnLoaded_Event;

	FORCEINLINE OnLevelLoadedEventType& GetLevel_Streaming_OnLoaded_Event() { return Level_Streaming_OnLoaded_Event; }

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Managers|Level|Streaming")
	FCsManagerLevel_LevelStreaming_OnLoaded Level_Streaming_OnLoaded_ScriptEvent;

	void Broadcast_Level_Streaming_OnLoaded(ULevelStreaming* Level);

	// OnUnloaded

	OnLevelUnloadedEventType Level_Streaming_OnUnloaded_Event;

	FORCEINLINE OnLevelUnloadedEventType& GetLevel_Streaming_OnUnloaded_Event() { return Level_Streaming_OnUnloaded_Event; }

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Managers|Level|Streaming")
	FCsManagerLevel_LevelStreaming_OnUnloaded Level_Streaming_OnUnloaded_ScriptEvent;

	void Broadcast_Level_Streaming_OnUnloaded(ULevelStreaming* Level);

	// OnShown

	OnLevelShownEventType Level_Streaming_OnShown_Event;

	FORCEINLINE OnLevelShownEventType& GetLevel_Streaming_OnShown_Event() { return Level_Streaming_OnShown_Event; }

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Managers|Level|Streaming")
	FCsManagerLevel_LevelStreaming_OnShown Level_Streaming_OnShown_ScriptEvent;

	void Broadcast_Level_Streaming_OnShown(ULevelStreaming* Level);

	// OnHidden

	OnLevelHiddenEventType Level_Streaming_OnHidden_Event;

	FORCEINLINE OnLevelHiddenEventType& GetLevel_Streaming_OnHidden_Event() { return Level_Streaming_OnHidden_Event; }

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Managers|Level|Streaming")
	FCsManagerLevel_LevelStreaming_OnHidden Level_Streaming_OnHidden_ScriptEvent;

	void Broadcast_Level_Streaming_OnHidden(ULevelStreaming* Level);

#pragma endregion Streaming

// Events
#pragma region
protected:

	void OnPostWorldInitialization(UWorld* World);
	
#pragma endregion Events

#if WITH_EDITOR

protected:

	bool bFinishedDestroyingOtherPIEWorld;

public:

	FORCEINLINE bool HasFinishedDestroyingOtherPIEWorld() const { return bFinishedDestroyingOtherPIEWorld; }

	void DestroyOtherPIEWorld(const FString& URL);
private:
	char DestroyOtherPIEWorld_Internal(FCsRoutine* R);

#endif // #if WITH_EDITOR
};