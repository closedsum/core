// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Start/CsStartPlay.h"
#include "ICsSpawner.h"
// Types
#include "Coroutine/CsTypes_Coroutine.h"
#include "CsTypes_Spawner.h"
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"

#include "CsSpawnerImpl.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsSpawnerImpl_OnSpawnObject, ACsSpawnerImpl*, Spawner, UObject*, SpawnedObject);

#pragma endregion Delegates

// Structs
#pragma region

	// SpawnedObjects
#pragma region

namespace NCsSpawner
{
	namespace NSpawnedObjects
	{
	#define ResourceType NCsSpawner::FSpawnedObjects

		struct CSSPAWNER_API FResource : public TCsResourceContainer<ResourceType>
		{
		};

		struct CSSPAWNER_API FManager : public NCsResource::NManager::NValue::TFixed<ResourceType, FResource, 0>
		{
		};

	#undef ResourceType
	}
}

#pragma endregion Memory Resource

#pragma endregion Structs

struct FCsRoutine;

// NCsSpawner::NPoint::IImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NPoint, IImpl)

// NCsSpawner::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NParams, IParams)
// NCsSpawner::NParams::FCount
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NParams, FCount)
// NCsSpawner::NParams::FFrequency
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NParams, FFrequency)

struct FCsDebugDrawCircle;
struct FCsDebugDrawSphere;

UCLASS()
class CSSPAWNER_API ACsSpawnerImpl : public AActor,
									 public ICsStartPlay,
									 public ICsSpawner
{
	GENERATED_UCLASS_BODY()

#define ParamsType NCsSpawner::NParams::IParams

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

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

// StartPlay
#pragma region
protected:

	UPROPERTY(BlueprintReadWrite, Category = "Spawner|StartPlay", meta = (AllowPrivateAccess = "true"))
	bool bOverride_StartPlay;

public:

	UFUNCTION(BlueprintImplementableEvent)
	void Override_StartPlay();

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Spawner|StartPlay", meta = (AllowPrivateAccess = "true"))
	bool bReceiveStartPlay;

public:

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveStartPlay();

#pragma endregion StartPlay

// Point
#pragma region
protected:

#define PointImplType NCsSpawner::NPoint::IImpl

	PointImplType* PointImpl;

public:

	FORCEINLINE const PointImplType* GetPointImpl() const { return PointImpl; }

protected:

	virtual void ConstructPointImpl();

	UPROPERTY(BlueprintReadWrite, Category = "Spawner|Point")
	bool bConstructDefaultPointImpl;

	void(*DeconstructPointImplImpl)(void* Ptr);

public:

	void SetPointImpl(const FString& Context, PointImplType* InPointImpl, void(*InDeconstructPointImplImpl)(void*));

#undef PointImplType

	void SetPointCenter(AActor* Center);
	void SetPointCenter(const FTransform3f& Center);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Spawner|Point")
	FTransform3f PointImpl_GetCurrentTransform();

#pragma endregion Point

// Params
#pragma region
protected:

	ParamsType* Params;

protected:

#define CountParamsType NCsSpawner::NParams::FCount
	/** Reference to Params->GetCountParams() for easy / quick access. */
	CountParamsType* CountParams;
#undef CountParamsType

#define FrequencyParamsType NCsSpawner::NParams::FFrequency
	/** Reference to Params->GetFrequencyParams() for easy / quick access. */
	FrequencyParamsType* FrequencyParams;
#undef FrequencyParamsType

	/** Reference to Params->GetTotalTime() for easy / quick access. */
	float* TotalTime;

	virtual void ConstructParams();

	UPROPERTY(BlueprintReadWrite, Category = "Spawner|Params")
	bool bConstructDefaultParams;

	void(*DeconstructParamsImpl)(void* Ptr);

	bool(*IsParamsValidImpl)(const FString&, ParamsType*);

public:

	virtual void SetParams(const FString& Context, ParamsType* InParams, void(*InDeconstructParamsImpl)(void*), bool(*InIsParamsValidImpl)(const FString&, ParamsType*));

	UFUNCTION(BlueprintCallable, Category = "CsCore|Spawner|Params")
	void SetupFromParams();

#pragma endregion Params

// Events
#pragma region
protected:

	NCsSpawner::FOnStart OnStart_Event;

	NCsSpawner::FOnStop OnStop_Event;

	NCsSpawner::FOnSpawn OnSpawn_Event;

	NCsSpawner::FOnSpawnObject OnSpawnObject_Event;

	NCsSpawner::FOnSpawnObjects OnSpawnObjects_Event;

	NCsSpawner::FOnFinish OnFinish_Event;

#pragma endregion Events

// ICsSpawner
#pragma region
public:

	FORCEINLINE ParamsType* GetParams() const { return Params; }

	UFUNCTION(BlueprintCallable, Category = "CsCore|ICsSpawner")
	virtual void Start();

	FORCEINLINE NCsSpawner::FOnStart& GetOnStart_Event() { return OnStart_Event; }

	UFUNCTION(BlueprintCallable, Category = "CsCore|ICsSpawner")
	void Stop();

	FORCEINLINE NCsSpawner::FOnStop& GetOnStop_Event() { return OnStop_Event; }

	UFUNCTION(BlueprintCallable, Category = "CsCore|ICsSpawner")
	void Spawn();
	
	FORCEINLINE NCsSpawner::FOnSpawn& GetOnSpawn_Event() { return OnSpawn_Event; }
	FORCEINLINE NCsSpawner::FOnSpawnObject& GetOnSpawnObject_Event() { return OnSpawnObject_Event; }
	FORCEINLINE NCsSpawner::FOnSpawnObjects& GetOnSpawnObjects_Event() { return OnSpawnObjects_Event; }
	FORCEINLINE NCsSpawner::FOnFinish& GetOnFinish_Event() { return OnFinish_Event; }

#pragma endregion ICsSpawner

// Spawn
#pragma region
protected:

	/** */
	int32 CurrentSpawnCount;

	/** */
	int32 MaxConcurrentSpawnObjects;

#define SpawnedObjectsManagerType NCsSpawner::NSpawnedObjects::FManager
	/** Manager for objects of type: SpawnedObjectsType (NCsSpawner::FSpawnedObjects). */
	SpawnedObjectsManagerType Manager_SpawnedObjects;
#undef SpawnedObjectsManagerType

	/** */
#define SpawnedObjectsType NCsSpawner::FSpawnedObjects
	SpawnedObjectsType SpawnedObjects;
#undef SpawnedObjectsType

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreStart, ICsSpawner* /*Spawner*/);

	FOnPreStart OnPreStart_Event;

protected:

	//virtual void OnPreStart(ICsSpawner* Spawner);

	char Start_Internal(FCsRoutine* R);

	FCsRoutineHandle Start_Internal_Handle;

public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreSpawnObjects, ICsSpawner* /*Spawner*/, const int32& /*Index*/);

	FOnPreSpawnObjects OnPreSpawnObjects_Event;

protected:
	
	//virtual void OnPreSpawnObjects(ICsSpawner* Spawner, const int32& Index);

	void SpawnObjects(const int32& Index);
	char SpawnObjects_Internal(FCsRoutine* R);
	void SpawnObjects_Internal_OnEnd(FCsRoutine* R);
	TArray<FCsRoutineHandle> SpawnObjects_Internal_Handles;

	void SpawnObjects_InfiniteFillToCount();
	char SpawnObjects_InfiniteFillToCount_Internal(FCsRoutine* R);
	void SpawnObjects_InfiniteFillToCount_Internal_OnEnd(FCsRoutine* R);
	FCsRoutineHandle SpawnObjects_InfiniteFillToCount_Handle;

public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreSpawnObject, ICsSpawner* /*Spawner*/, const int32& /*Index*/);

	FOnPreSpawnObject OnPreSpawnObject_Event;

protected:

	//virtual void OnPreSpawnObject(ICsSpawner* Spawner, const int32& Index);

	virtual UObject* SpawnObject(const int32& Count, const int32& Group, const int32& CountPerGroup);

	UPROPERTY(BlueprintAssignable, Category = "Spawner|Spawn")
	FCsSpawnerImpl_OnSpawnObject OnSpawnObject_ScriptEvent;


	UPROPERTY(BlueprintReadWrite, Category = "Spawner|Spawn", meta = (AllowPrivateAccess = "true"))
	bool bOverride_SpawnObject;

public:

	UFUNCTION(BlueprintImplementableEvent)
	UObject* Override_SpawnObject(const int32& Count, const int32& Group, const int32& CountPerGroup);

protected:

	// <Index indentifing Object, Object>
	TMap<int32, UObject*> SpawnedObjectByIndexMap;

public:

	FORCEINLINE const TMap<int32, UObject*>& GetSpawnedObjectByIndexMap() const { return SpawnedObjectByIndexMap; };

	UFUNCTION(BlueprintPure, Category = "CsCore|ICsSpawner")
	void GetSpawnedObjects(TArray<UObject*>& OutObjects) const
	{
		OutObjects.Reset(FMath::Max(OutObjects.Max(), SpawnedObjectByIndexMap.Num()));

		for (const TPair<int32, UObject*>& Pair : SpawnedObjectByIndexMap)
		{
			OutObjects.Add(Pair.Value);
		}
	}

protected:

	// <Index indentifing Object, Object>
	TMap<int32, UObject*> InfiniteFillToCount_SpawnedObjectByIndexMap;

	void OnObjectDestroyed(const int32& Index, const UObject* Object);

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

#undef ParamsType
};