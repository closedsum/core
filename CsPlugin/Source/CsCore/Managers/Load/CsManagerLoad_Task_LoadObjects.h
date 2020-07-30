// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Engine/StreamableManager.h"
// Types
#include "Types/CsTypes_Load.h"
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/Time/CsTypes_Time.h"

#include "CsManagerLoad_Task_LoadObjects.generated.h"

class UWorld;
class UCsManager_Load;

UCLASS(Transient)
class CSCORE_API UCsManagerLoad_Task_LoadObjects : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/** Internal Index of the struct in the Manager_Resource. */
	int32 Index;

	/** */
	FCsLoadHandle Handle;

	void Init();
	void Reset();

// Update
#pragma region
public:

	FECsUpdateGroup UpdateGroup;

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion Update

// StreamableManager
#pragma region
private:

	/** */
	FStreamableManager* StreamableManager;

public:

	FORCEINLINE void SetStreamableManager(FStreamableManager* InManager)
	{
		StreamableManager = InManager;
	}

private:

	/** */
	TSharedPtr<FStreamableHandle> StreamableHandle;

	/** */
	FStreamableDelegate OnFinishLoadObjectPathDelegate;

public:

	void OnFinishLoadObjectPath();

private:

	/** */
	FStreamableDelegate	OnFinishLoadObjectPathsDelegate;

public:

	void OnFinishLoadObjectPaths();

#pragma endregion StreamableManager

// Events
#pragma region
public:

	/**
	*  Delegate type
	*
	* @param ObjectPath
	*/
	DECLARE_DELEGATE_OneParam(FOnStartLoadObjectPath, const FSoftObjectPath& /*ObjectPath*/);

	/** Event to broadcast when starting to load an Object's Path. */
	FOnStartLoadObjectPath OnStartLoadObjectPath_Event;

	/**
	*  Delegate type
	*
	* @param LoadedInfo
	* @param LoadedObject
	*/
	DECLARE_DELEGATE_TwoParams(FOnFinishLoadObjectPath, const FCsObjectPathLoadedInfo& /*LoadedInfo*/, UObject* /*LoadedObject*/);

	/** Event to broadcast when finish loading an Object's Path. */
	FOnFinishLoadObjectPath OnFinishLoadObjectPath_Event;

	/**
	*  Delegate type
	*
	* @param LoadSize
	*/
	DECLARE_DELEGATE_OneParam(FOnStartLoadObjectPaths, const int32& /*LoadSize*/);

	/** Event to broadcast when starting to load all Object Paths. */
	FOnStartLoadObjectPaths OnStartLoadObjectPaths_Event;

	/**
	*  Delegate type
	*
	* @param Handle
	* @param LoadedPaths
	* @param LoadedObjects
	* @param LoadTime
	*/
	DECLARE_DELEGATE_FourParams(FOnFinishLoadObjectPaths, const FCsLoadHandle& /*Handle*/, const TArray<FSoftObjectPath>& /*LoadedPaths*/, const TArray<UObject*>& /*LoadedObjects*/, const float& /*LoadTime*/);

	/** Event to broadcast when finished loading all Object Paths. */
	FOnFinishLoadObjectPaths OnFinishLoadObjectPaths_Event;

	/**
	*  Delegate type
	*
	* @param LoadSize
	*/
	DECLARE_DELEGATE_OneParam(FOnStartLoadProgress, const int32& /*LoadSize*/);

	/** */
	FOnStartLoadProgress OnStartLoadProgress_Event;

	/**
	*  Delegate type
	*
	* @param Progress
	*/
	DECLARE_DELEGATE_OneParam(FOnLoadProgressUpdated, const float& /*Progress*/);

	/** */
	FOnLoadProgressUpdated OnLoadProgressUpdated_Event;

#pragma endregion Events

// Load
#pragma region
private:

	/** Async order for loading assets (i.e. FirstToLast, Bulk, ... etc). */
	ECsLoadAsyncOrder Order;

	/** The Object Paths to load. */
	TArray<FSoftObjectPath> Paths;

	/** World Context associated with the load. */
	UWorld * World;

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

	UPROPERTY()
	TArray<UObject*> LoadedObjects;

public:

	FCsLoadHandle LoadObjectPaths(const TArray<FSoftObjectPath>& ObjectPaths, const ECsLoadAsyncOrder& AsyncOrder, FOnFinishLoadObjectPaths Delegate);

#pragma endregion Load
};