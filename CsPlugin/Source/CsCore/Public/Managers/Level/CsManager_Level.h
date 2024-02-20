// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
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

UCLASS(transient, BlueprintType, Blueprintable, Meta = (ShowWorldContextPin))
class CSCORE_API UCsManager_Level : public UObject
{
	GENERATED_UCLASS_BODY()
public:

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

	UFUNCTION(BlueprintImplementableEvent, Category = "Singleton", meta = (DisplayName = "Clean Up"))
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

	UFUNCTION(BlueprintPure)
	UObject* GetWorldContext() const;

// Persistent Level
#pragma region
protected:

	bool bFinishedLoadingPersistentlLevel;

public:
	
	FORCEINLINE bool HasFinishedLoadingPersistentLevel() const
	{
		return bFinishedLoadingPersistentlLevel;
	}

	void Check_FinishedLoadingPersistentLevel();
	void Check_FinishedLoadingPersistentLevel(const FString& MapPackageName);

protected:

	char Check_FinishedLoadingPersistentLevel_Internal(FCsRoutine* R);

#pragma endregion Persistent Level

// Change Map
#pragma region
protected:

	FString CurrentMap;

	bool bChangeMapCompleted;

public:

	FORCEINLINE bool HasChangeMapCompleted() const { return bChangeMapCompleted; }

#define ChangeMapParamsType NCsLevel::NManager::NChangeMap::FParams

	void ChangeMap(const ChangeMapParamsType& Params);
private:
	char ChangeMap_Internal(FCsRoutine* R);

	void ChangeMap_TransitionAsDestination(const ChangeMapParamsType& Params);
	char ChangeMap_TransitionAsDestination_Internal(FCsRoutine* R);

#undef ChangeMapParamsType

#define OnChangeMapStartEventType NCsLevel::NManager::FChangeMap_OnStart
#define OnChangeMapCompleteEventType NCsLevel::NManager::FChangeMap_OnComplete

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

#undef OnChangeMapStartEventType
#undef OnChangeMapCompleteEventType

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

#define OnLevelLoadedEventType NCsLevel::NManager::NLevel::NStreaming::FOnLoaded
#define OnLevelUnloadedEventType NCsLevel::NManager::NLevel::NStreaming::FOnUnloaded
#define OnLevelShownEventType NCsLevel::NManager::NLevel::NStreaming::FOnShown
#define OnLevelHiddenEventType NCsLevel::NManager::NLevel::NStreaming::FOnHidden

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

#undef OnLevelLoadedEventType
#undef OnLevelUnloadedEventType
#undef OnLevelShownEventType
#undef OnLevelHiddenEventType

#pragma endregion Streaming

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