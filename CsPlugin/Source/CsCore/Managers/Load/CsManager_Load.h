// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Engine/StreamableManager.h"
// Types
#include "Types/CsTypes_Load.h"
#include "Managers/Time/CsTypes_Time.h"
// Managers
#include "Managers/MemoryResource/CsManager_MemoryResource_Fixed.h"
#include "CsManager_Load.generated.h"

/**
* StartLoadObjectPath
*  Delegate type
*
* @param ObjectPath
*/
DECLARE_DELEGATE_OneParam(FCsManagerLoad_OnStartLoadObjectPath, const FSoftObjectPath& /*ObjectPath*/);
/**
* FinishLoadObjectPath
*  Delegate type
*
* @param LoadedInfo
* @param LoadedObject
*/
DECLARE_DELEGATE_TwoParams(FCsManagerLoad_OnFinishLoadObjectPath, const FCsObjectPathLoadedInfo& /*LoadedInfo*/, UObject* /*LoadedObject*/);
/**
* OnStartLoadObjectPaths
*  Delegate type
*
* @param LoadSize
*/
DECLARE_DELEGATE_OneParam(FCsManagerLoad_OnStartLoadObjectPaths, const int32& /*LoadSize*/);
/**
* FinishLoadObjectPaths
*  Delegate type
*
* @param LoadedObjects
* @param LoadTime
*/
DECLARE_DELEGATE_TwoParams(FCsManagerLoad_OnFinishLoadObjectPaths, const TArray<UObject*>& /*LoadedObjects*/, const float& /*LoadTime*/);
/**
* OnStartLoadProgress
*  Delegate type
*
* @param LoadSize
*/
DECLARE_DELEGATE_OneParam(FCsManagerLoad_OnStartLoadProgress, const int32& /*LoadSize*/);
/**
* OnLoadProgressUpdated
*  Delegate type
*
* @param Progress
*/
DECLARE_DELEGATE_OneParam(FCsManagerLoad_OnLoadProgressUpdated, const float& /*Progress*/);

// Structs
#pragma region

	// FCsManagerLoad_Task_LoadObjects
#pragma region

class UWorld;
class UCsManager_Load;

struct CSCORE_API FCsManagerLoad_Task_LoadObjects
{
public:

	/** Internal Index of the struct in the Manager_MemoryResource. */
	int32 Index;

protected:

	/** Async order for loading assets (i.e. FirstToLast, Bulk, ... etc). */
	ECsLoadAsyncOrder Order;

	/** The Object Paths to load. */
	TArray<FSoftObjectPath> Paths;

public:

	/** Event to broadcast when starting to load an Object's Path. */
	FCsManagerLoad_OnStartLoadObjectPath OnStartLoadObjectPath_Event;

	/** Event to broadcast when finish loading an Object's Path. */
	FCsManagerLoad_OnFinishLoadObjectPath OnFinishLoadObjectPath_Event;

	/** Event to broadcast when starting to load all Object Paths. */
	FCsManagerLoad_OnStartLoadObjectPaths OnStartLoadObjectPaths_Event;

	/** Event to broadcast when finished loading all Object Paths. */
	FCsManagerLoad_OnFinishLoadObjectPaths OnFinishLoadObjectPaths_Event;

	/** */
	FCsManagerLoad_OnStartLoadProgress OnStartLoadProgress_Event;

	/** */
	FCsManagerLoad_OnLoadProgressUpdated OnLoadProgressUpdated_Event;

protected:

	/** World Context associated with the load. */
	UWorld* World;

	/** Current number of objects loaded. */
	int32 Count;

	/** Current memory size of all objects loaded. */
	FCsResourceSize SizeLoaded;

	/** */
	FCsObjectPathLoadedInfo Info;

	/** */
	float StartTime;

	/** */
	float SingleStartTime;

protected:

	/** */
	//FStreamableManager StreamableManager;

	/** */
	FStreamableDelegate OnFinishLoadObjectPathDelegate;

	/** */
	FStreamableDelegate	OnFinishLoadObjectPathsDelegate;

	/** */
	TSharedPtr<FStreamableHandle> Handle;

public:

	UCsManager_Load* Manager_Load;

public:

	FCsManagerLoad_Task_LoadObjects() :
		Index(INDEX_NONE),
		Order(ECsLoadAsyncOrder::Bulk),
		Paths(),
		OnStartLoadObjectPath_Event(),
		OnFinishLoadObjectPath_Event(),
		OnStartLoadObjectPaths_Event(),
		OnFinishLoadObjectPaths_Event(),
		OnStartLoadProgress_Event(),
		OnLoadProgressUpdated_Event(),
		World(nullptr),
		Count(0),
		SizeLoaded(),
		Info(),
		StartTime(0.0f),
		SingleStartTime(0.0f),
		Manager_Load(nullptr)
	{
	}

	void Init();

	void Reset()
	{
		Order = ECsLoadAsyncOrder::Bulk;
		Paths.Reset(Paths.Max());
		OnStartLoadObjectPath_Event.Unbind();
		OnFinishLoadObjectPath_Event.Unbind();
		OnStartLoadObjectPaths_Event.Unbind();
		OnFinishLoadObjectPaths_Event.Unbind();
		OnStartLoadProgress_Event.Unbind();
		OnLoadProgressUpdated_Event.Unbind();
		World = nullptr;
		Count = 0;
		SizeLoaded.Reset();
		Info.Reset();
		StartTime = 0.0f;
		SingleStartTime = 0.0f;
		Handle = nullptr;
	}

	void OnUpdate(const FCsDeltaTime& DeltaTime);

	void LoadObjectPaths(UWorld* InWorld, const TArray<FSoftObjectPath>& ObjectPaths, const ECsLoadAsyncOrder& AsyncOrder, FCsManagerLoad_OnFinishLoadObjectPaths Delegate);

	void OnFinishLoadObjectPath();
	void OnFinishLoadObjectPaths();
};

#pragma endregion FCsManagerLoad_Task_LoadObjects

	// Memory Resource
#pragma region

struct CSCORE_API FCsResourceContainer_ManagerLoad_Task_LoadObjects : public TCsResourceContainer<FCsManagerLoad_Task_LoadObjects>
{
};

struct CSCORE_API FCsManager_MemoryResource_ManagerLoad_Task_LoadObjects : public TCsManager_MemoryResource_Fixed<FCsManagerLoad_Task_LoadObjects, FCsResourceContainer_ManagerLoad_Task_LoadObjects, 64>
{
};

#pragma endregion Memory Resource

#pragma endregion Structs

class ICsGetManagerLoad;
class UWorld;

UCLASS(transient)
class CSCORE_API UCsManager_Load : public UObject
{
	GENERATED_UCLASS_BODY()
public:

// Singleton
#pragma region
public:

	static UCsManager_Load* Get(UObject* InRoot = nullptr);
	static void Init(UObject* InRoot);
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerLoad* Get_GetManagerLoad(UObject* InRoot);
	static ICsGetManagerLoad* GetSafe_GetManagerLoad(UObject* InRoot);

	static UCsManager_Load* GetSafe(UObject* InRoot);

public:

	static UCsManager_Load* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

	/** Delegate for callbacks to Tick */
	FTickerDelegate	TickDelegate;

	/** Handle to various registered delegates */
	FDelegateHandle	TickDelegateHandle;

	bool Tick(float DeltaSeconds);

protected:

	void Initialize();
	void CleanUp();

private:
	// Singleton data
	static UCsManager_Load* s_Instance;
	static bool s_bShutdown;                                      

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot() const
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

// Tasks
#pragma region
protected:

	FCsManager_MemoryResource_ManagerLoad_Task_LoadObjects Manager_Tasks;

#pragma endregion Tasks

public:

	FStreamableManager StreamableManager;

protected:

	//UPROPERTY()
	TArray<TArray<UObject*>> LoadedObjects;

public:

	TArray<UObject*>& GetLoadedObjects(const int32& Index);

	FCsManagerLoad_Task_LoadObjects& LoadObjectPaths(UWorld* CurrentWorld, TArray<FSoftObjectPath>& ObjectPaths, const ECsLoadAsyncOrder& AsyncOrder, FCsManagerLoad_OnFinishLoadObjectPaths Delegate);
	void LoadObjectPaths_Internal(TArray<FSoftObjectPath>& ObjectPaths, const ECsLoadAsyncOrder& AsyncOrder);
};