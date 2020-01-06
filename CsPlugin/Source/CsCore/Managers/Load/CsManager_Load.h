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

// FinishLoadObjectPath
DECLARE_DELEGATE_TwoParams(FCsManagerLoad_OnFinishLoadObjectPath, const FCsObjectPathLoadedInfo& /*LoadedInfo*/, UObject* /*LoadedObject*/);
// FinishLoadObjects
DECLARE_DELEGATE_TwoParams(FCsManagerLoad_OnFinishLoadObjects, const TArray<UObject*>& /*LoadedObjects*/, const float& /*LoadTime*/);

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

	/** Async order for loading assets (i.e. FirstToLast, Bulk, ... etc). */
	ECsLoadAsyncOrder Order;

	/** The Object Paths to load. */
	TArray<FSoftObjectPath> Paths;

	/** Event to broadcast when starting to load an Object's Path. */
	FCsManagerLoad_OnStartLoadObjectPath OnStartLoadObjectPath_Event;

	/** Event to broadcast when finished loading all Paths. */
	FCsManagerLoad_OnFinishLoadObjects OnFinishLoadObjects_Event;

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

protected:

	/** */
	FStreamableManager StreamableManager;

	/** */
	FStreamableDelegate OnFinishLoadObjectPathDelegate;

	/** */
	FStreamableDelegate	OnFinishLoadObjectPathsDelegate;

	/** */
	TSharedPtr<FStreamableHandle> LoadHandle;

public:

	UCsManager_Load* Manager_Load;

public:

	FCsManagerLoad_Task_LoadObjects() :
		Index(INDEX_NONE),
		Order(ECsLoadAsyncOrder::Bulk),
		Paths(),
		OnStartLoadObjectPath_Event(),
		OnFinishLoadObjects_Event(),
		World(nullptr),
		Count(0),
		SizeLoaded(),
		Info(),
		StartTime(0.0f),
		Manager_Load(nullptr)
	{
	}

	void Init();

	void Reset()
	{
		Order = ECsLoadAsyncOrder::Bulk;
		Paths.Reset(Paths.Max());
		OnStartLoadObjectPath_Event.Unbind();
		OnFinishLoadObjects_Event.Unbind();
		World = nullptr;
		Count = 0;
		SizeLoaded.Reset();
		Info.Reset();
		StartTime = 0.0f;
	}

	void OnUpdate(const FCsDeltaTime& DeltaTime);

	void LoadObjectPaths(UWorld* InWorld, const TArray<FSoftObjectPath>& ObjectPaths, const ECsLoadAsyncOrder& AsyncOrder, FCsManagerLoad_OnFinishLoadObjects Delegate);

	void OnFinishLoadObjectPath();
	void OnFinishLoadObjectPaths();
};

#pragma endregion FCsManagerLoad_Task_LoadObjects

	// Memory Resource
#pragma region

struct CSCORE_API FCsMemoryResource_ManagerLoad_Task_LoadObjects : public TCsMemoryResource<FCsManagerLoad_Task_LoadObjects>
{
};

struct CSCORE_API FCsManager_MemoryResource_ManagerLoad_Task_LoadObjects : public TCsManager_MemoryResource_Fixed<FCsManagerLoad_Task_LoadObjects, FCsMemoryResource_ManagerLoad_Task_LoadObjects, 64>
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

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnStartLoadingAssetReferences, const int32&);

	FOnStartLoadingAssetReferences OnStartLoadingAssetReferences_Event;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnStartLoadingAssetReference, const FStringAssetReference&);

	FOnStartLoadingAssetReference OnStartLoadingAssetReference_Event;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnFinishedLoadingAssetReference, const FCsObjectPathLoadedInfo&);

	FOnFinishedLoadingAssetReference OnFinishedLoadingAssetReference_Event;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFinishedLoadingAssetReferences, const TArray<UObject*>&, const float&);

	FOnFinishedLoadingAssetReferences OnFinishedLoadingAssetReferences_Event;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnStartLoadProgress, const int32&);

	FOnStartLoadProgress OnStartLoadProgress_Event;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoadProgressUpdated, const float&);

	FOnLoadProgressUpdated OnLoadProgressUpdated_Event;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFinishedLoadingAssetReferences, const TArray<UObject*>&, const float&);

	FOnFinishedLoadingAssetReferences Bulk_OnFinishedLoadingAssetReferences_Event;

	TArray<ECsLoadAsyncOrder> AsyncOrders;
	TArray<TArray<FStringAssetReference>> AssetReferencesQueue;
	TArray<FOnFinishedLoadingAssetReferences> OnFinishedLoadingAssetReferences_Events;
	TArray<UWorld*> CurrentWorlds;

protected:

	FStreamableManager		StreamableManager;
	FStreamableDelegate		AssetReferenceLoadedDelegate;
	FStreamableDelegate		AssetReferencesLoadedDelegate;

	TSharedPtr<FStreamableHandle> LoadHandle;

// Tasks
#pragma region
protected:

	FCsManager_MemoryResource_ManagerLoad_Task_LoadObjects Manager_Tasks;

public:

#pragma endregion Tasks

protected:

	int32 AssetReferencesLoadedCount;

	FCsResourceSize ResourceSizeLoaded;

	FCsObjectPathLoadedInfo ObjectPathLoadedCache;

	void OnFinishedLoadingAssetReference();
	void OnFinishedLoadingAssetReferences();

	float LoadingStartTime;
	float LoadingTotalStartTime;

	UPROPERTY()
	TArray<TArray<UObject*>> LoadedObjects;

public:

	TArray<UObject*>& GetLoadedObjects(const int32& Index);

	FCsManagerLoad_Task_LoadObjects& LoadObjectPaths(UWorld* CurrentWorld, TArray<FSoftObjectPath>& ObjectPaths, const ECsLoadAsyncOrder& AsyncOrder, FCsManagerLoad_OnFinishLoadObjects Delegate);
	void LoadObjectPaths_Internal(TArray<FSoftObjectPath>& ObjectPaths, const ECsLoadAsyncOrder& AsyncOrder);
};