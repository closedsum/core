// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Level/CsTypes_Manager_Level.h"

#include "CsManager_Level.generated.h"

class ICsGetManagerLevel;
struct FCsRoutine;
class ULevel;
class ALevelScriptActor;

UCLASS(transient)
class CSCORE_API UCsManager_Level : public UObject
{
	GENERATED_UCLASS_BODY()
public:

// Singleton
#pragma region
public:

	static UCsManager_Level* Get(UObject* InRoot = nullptr);

	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Level> ManagerMenuClass, UObject* InOuter = nullptr);
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerLevel* Get_GetManagerLevel(UObject* InRoot);
	static ICsGetManagerLevel* GetSafe_GetManagerLevel(UObject* Object);

	static UCsManager_Level* GetSafe(UObject* Object);

public:

	static UCsManager_Level* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

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

public:

	ULevel* GetPersistentLevel();

	FString GetPersistentLevelName();
	FName GetPersistentLevelFName();

	bool IsPersistentLevelName(const FString& MapPackageName);

	ALevelScriptActor* GetPersistentLevelScriptActor();

#pragma endregion Persistent Level

// Change Map
#pragma region
protected:

	FString CurrentMap;

	bool bChangeMapCompleted;

public:

	FORCEINLINE bool HasChangeMapCompleted() const
	{
		return bChangeMapCompleted;
	}

	void ChangeMap(const FCsManagerLevelChangeMap& Params);

protected:

public:

	char ChangeMap_Internal(FCsRoutine* R);

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChangeMapComplete, const FString& /*PreviousMap*/, const FString& /*NewMap*/);

	FOnChangeMapComplete OnChangeMapComplete_Event;

#pragma endregion Change Map
};