// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Level/CsTypes_Manager_Level.h"

#include "CsManager_Level.generated.h"

class ICsGetManagerLevel;
struct FCsRoutine;
class ULevel;
class ALevelScriptActor;
class UObject;

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

	struct FChangeMapParams
	{
	public:

		FString Map;

		FString TransitionMap;

		FChangeMapParams() :
			Map(),
			TransitionMap()
		{
		}
	};

	void ChangeMap(const FChangeMapParams& Params);

protected:

public:

	char ChangeMap_Internal(FCsRoutine* R);

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChangeMapComplete, const FString& /*PreviousMap*/, const FString& /*NewMap*/);

	FOnChangeMapComplete OnChangeMapComplete_Event;

#pragma endregion Change Map
};