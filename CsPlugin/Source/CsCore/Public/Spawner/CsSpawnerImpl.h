// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Start/CsStartPlay.h"
#include "Spawner/CsSpawner.h"
// Types
#include "Coroutine/CsTypes_Coroutine.h"
#include "Spawner/CsTypes_Spawner.h"
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"

#include "CsSpawnerImpl.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsSpawnerImpl_OnSpawnObject, ACsSpawnerImpl*, Spawner, UObject*, SpawnedObject);


#pragma endregion Delegates

// Structs
#pragma region

	// Memory Resource
#pragma region

struct CSCORE_API FCsResource_SpawnerSpawnedObjects : public TCsResourceContainer<FCsSpawnerSpawnedObjects>
{
};

struct CSCORE_API FCsManager_SpawnerSpawnedObjects : public TCsManager_ResourceValueType_Fixed<FCsSpawnerSpawnedObjects, FCsResource_SpawnerSpawnedObjects, 0>
{
};

#pragma endregion Memory Resource

#pragma endregion Structs

struct FCsRoutine;
struct ICsSpawnerParams;
struct FCsSpawnerCountParams;
struct FCsSpawnerFrequencyParams;
struct FCsDebugDrawCircle;
struct FCsDebugDrawSphere;

UCLASS()
class CSCORE_API ACsSpawnerImpl : public AActor,
								  public ICsStartPlay,
								  public ICsSpawner
{
	GENERATED_UCLASS_BODY()

// AActor Interface
#pragma region
public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

#pragma endregion AActor Interface

protected:

	bool bHasStartedPlay;

// ICsStartPlay
#pragma region
public:

	virtual void StartPlay();

	FORCEINLINE bool HasStartedPlay() const
	{
		return bHasStartedPlay;
	}

#pragma endregion ICsStartPlay

// Params
#pragma region
protected:

	ICsSpawnerParams* Params;

	/** Reference to Params->GetCountParams() for easy / quick access. */
	FCsSpawnerCountParams* CountParams;

	/** Reference to Params->GetFrequencyParams() for easy / quick access. */
	FCsSpawnerFrequencyParams* FrequencyParams;

	/** Reference to Params->GetTotalTime() for easy / quick access. */
	float* TotalTime;

	virtual void ConstructParams();

	virtual bool IsParamsValid(const FString& Context) const;

#pragma endregion Params

// Events
#pragma region
protected:

	FCsSpawner_OnStart OnStart_Event;

	FCsSpawner_OnStop OnStop_Event;

	FCsSpawner_OnSpawn OnSpawn_Event;

	FCsSpawner_OnSpawnObject OnSpawnObject_Event;

	FCsSpawner_OnSpawnObjects OnSpawnObjects_Event;

	FCsSpawner_OnFinish OnFinish_Event;

#pragma endregion Events

// ICsSpawner
#pragma region
public:

	FORCEINLINE ICsSpawnerParams* GetParams() const
	{
		return Params;
	}

	UFUNCTION(BlueprintCallable, Category = "CsCore|ICsSpawner")
	virtual void Start();

	FORCEINLINE FCsSpawner_OnStart& GetOnStart_Event()
	{
		return OnStart_Event;
	}

	UFUNCTION(BlueprintCallable, Category = "CsCore|ICsSpawner")
	void Stop();

	FORCEINLINE FCsSpawner_OnStop& GetOnStop_Event()
	{
		return OnStop_Event;
	}

	UFUNCTION(BlueprintCallable, Category = "CsCore|ICsSpawner")
	void Spawn();
	
	FORCEINLINE FCsSpawner_OnSpawn& GetOnSpawn_Event()
	{
		return OnSpawn_Event;
	}

	FORCEINLINE FCsSpawner_OnSpawnObject& GetOnSpawnObject_Event()
	{
		return OnSpawnObject_Event;
	}

	FORCEINLINE FCsSpawner_OnSpawnObjects& GetOnSpawnObjects_Event()
	{
		return OnSpawnObjects_Event;
	}

	FORCEINLINE FCsSpawner_OnFinish& GetOnFinish_Event()
	{
		return OnFinish_Event;
	}

#pragma endregion ICsSpawner

// Spawn
#pragma region
protected:

	/** */
	int32 CurrentSpawnCount;

	/** */
	int32 MaxConcurrentSpawnObjects;

	/** Manager for objects of type: FCsSpawnerSpawnedObjects. */
	FCsManager_SpawnerSpawnedObjects Manager_SpawnedObjects;

	/** */
	FCsSpawnerSpawnedObjects SpawnedObjects;

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreStart, ICsSpawner* /*Spawner*/);

	FOnPreStart OnPreStart_Event;

protected:

	//virtual void OnPreStart(ICsSpawner* Spawner);

	FCsRoutineHandle Start_Internal_Handle;

	char Start_Internal(FCsRoutine* R);

public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreSpawnObjects, ICsSpawner* /*Spawner*/, const int32& /*Index*/);

	FOnPreSpawnObjects OnPreSpawnObjects_Event;

protected:
	
	//virtual void OnPreSpawnObjects(ICsSpawner* Spawner, const int32& Index);

	TArray<FCsRoutineHandle> SpawnObjects_Internal_Handles;

	void SpawnObjects(const int32& Index);

	char SpawnObjects_Internal(FCsRoutine* R);

	void SpawnObjects_Internal_OnEnd(FCsRoutine* R);

public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreSpawnObject, ICsSpawner* /*Spawner*/, const int32& /*Index*/);

	FOnPreSpawnObject OnPreSpawnObject_Event;

protected:

	//virtual void OnPreSpawnObject(ICsSpawner* Spawner, const int32& Index);

	virtual UObject* SpawnObject(const int32& Index);

	UPROPERTY(BlueprintAssignable, Category = "CsCore|Spawner")
	FCsSpawnerImpl_OnSpawnObject OnSpawnObject_ScriptEvent;

#pragma endregion Spawn

// Log
#pragma region
protected:

	virtual void LogParams() const;

	void LogCountParams() const;

#pragma endregion Log

// Debug
#pragma region
protected:

	virtual void DebugDraw();

	virtual FCsDebugDrawCircle* GetDebugDrawCircle();

	virtual FCsDebugDrawSphere* GetDebugDrawSphere();

#pragma endregion Debug
};