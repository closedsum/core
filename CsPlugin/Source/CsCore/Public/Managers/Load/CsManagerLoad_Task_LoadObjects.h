// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/StreamableManager.h"
// Types
#include "Types/CsTypes_Load.h"
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/Time/CsTypes_Time.h"
// Load
#include "Load/CsResourceSize.h"
#include "Load/CsLoadHandle.h"

#include "CsManagerLoad_Task_LoadObjects.generated.h"

// NCsLoad::NObjectPath::FInfo
#pragma region

namespace NCsLoad
{
	namespace NObjectPath
	{
		struct CSCORE_API FInfo
		{
		public:

			FSoftObjectPath Path;

			int32 Count;

			FCsResourceSize Size;

			float Time;

			FInfo() :
				Path(),
				Count(0),
				Size(),
				Time(0.0f)
			{
			}

			void Reset()
			{
				Path.Reset();
				Count = 0;
				Size.Reset();
				Time = 0.0f;
			}
		};
	}
}

#pragma endregion NCsLoad::NObjectPath::FInfo

// Delegates
#pragma region

/**
* OnFinishLoadObjectPaths 
*  Delegate type for when loading has finished for any paths provided when executing 
*  LoadObjectPaths.
*  This is a synchronous event (fired on the Game Thread).
*
* @param Handle			Handle to Task from Manager_Load. This is only valid in the executing scope.
* @param Handles		Streamable Handles that hold onto the reference of a loaded asset.
* @param LoadedPaths	The paths that were loaded.
* @param LoadedObjects	The objects that were loaded.
* @param LoadTime		How long it took to load LoadedPaths.
*/
DECLARE_DELEGATE_FiveParams(FCsManagerLoad_OnFinishLoadObjectPaths, const FCsLoadHandle& /*Handle*/, const TArray<TSharedPtr<FStreamableHandle>>& /*Handles*/, const TArray<FSoftObjectPath>& /*LoadedPaths*/, const TArray<UObject*>& /*LoadedObjects*/, const float& /*LoadTime*/);

#pragma endregion Delegates

// Structs
#pragma region

namespace NCsLoad
{
	namespace NManager
	{
		namespace NLoadObjectPaths
		{
			struct CSCORE_API FPayload
			{
			public:

				TArray<FSoftObjectPath> ObjectPaths;

				ECsLoadAsyncOrder AsyncOrder;
	
				FCsManagerLoad_OnFinishLoadObjectPaths OnFinishLoadObjectPaths;

				FPayload() :
					ObjectPaths(),
					AsyncOrder(ECsLoadAsyncOrder::Bulk),
					OnFinishLoadObjectPaths()
				{
				}
			};
		}
	}
}

#pragma endregion Structs

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

private:
	
	bool bComplete;

public:

	FORCEINLINE bool IsComplete() const { return bComplete; }

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
	TArray<TSharedPtr<FStreamableHandle>> StreamableHandles;

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

#define LoadInfoType NCsLoad::NObjectPath::FInfo

	/**
	*  Delegate type
	*
	* @param LoadedInfo
	* @param LoadedObject
	*/
	DECLARE_DELEGATE_TwoParams(FOnFinishLoadObjectPath, const LoadInfoType& /*LoadedInfo*/, UObject* /*LoadedObject*/);

	/** Event to broadcast when finish loading an Object's Path. */
	FOnFinishLoadObjectPath OnFinishLoadObjectPath_Event;

#undef LoadInfoType

	/**
	*  Delegate type
	*
	* @param LoadSize
	*/
	DECLARE_DELEGATE_OneParam(FOnStartLoadObjectPaths, const int32& /*LoadSize*/);

	/** Event to broadcast when starting to load all Object Paths. */
	FOnStartLoadObjectPaths OnStartLoadObjectPaths_Event;

	/** Event to broadcast when finished loading all Object Paths. */
	FCsManagerLoad_OnFinishLoadObjectPaths OnFinishLoadObjectPaths_Event;

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

#define LoadInfoType NCsLoad::NObjectPath::FInfo
	/** */
	LoadInfoType Info;
#undef LoadInfoType

	/** */
	float StartTime;

	/** */
	float SingleStartTime;

	UPROPERTY()
	TArray<UObject*> LoadedObjects;

public:

#define PayloadType NCsLoad::NManager::NLoadObjectPaths::FPayload
	FCsLoadHandle LoadObjectPaths(const PayloadType& Payload);
#undef PayloadType

#pragma endregion Load
};