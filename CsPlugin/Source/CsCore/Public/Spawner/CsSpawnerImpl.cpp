// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/CsSpawnerImpl.h"
#include "CsCore.h"

// CVar
#include "Spawner/CsCVars_Spawner.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Debug/CsTypes_Debug.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Spawner/Params/CsLibrary_SpawnerParams.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Spawner
#include "Spawner/Params/CsSpawnerParams.h"

// Cached
#pragma region

namespace NCsSpawnerImplCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSpawnerImpl, StartPlay);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSpawnerImpl, Start);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSpawnerImpl, Start_Internal);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSpawnerImpl, Spawn);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSpawnerImpl, SpawnObjects);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSpawnerImpl, SpawnObjects_Internal);
	}

	namespace Name
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ACsSpawnerImpl, Start_Internal);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ACsSpawnerImpl, SpawnObjects_Internal);
	}
}

#pragma endregion Cached

ACsSpawnerImpl::ACsSpawnerImpl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// ICsStartPlay
	bHasStartedPlay(false),
	// ICsSpawner
		// Params
	CountParams(nullptr),
	FrequencyParams(nullptr),
	TotalTime(nullptr),
		// Events
	OnStart_Event(),
	OnStop_Event(),
	OnSpawn_Event(),
	OnSpawnObject_Event(),
	OnSpawnObjects_Event(),
	OnFinish_Event(),
	// Spawn
	CurrentSpawnCount(0),
	MaxConcurrentSpawnObjects(4),
	Manager_SpawnedObjects(),
	SpawnedObjects(),
	Start_Internal_Handle(),
	SpawnObjects_Internal_Handles()
{
	PrimaryActorTick.bCanEverTick = true;
#if WITH_EDITOR
	PrimaryActorTick.bStartWithTickEnabled = true;
#else
	PrimaryActorTick.bStartWithTickEnabled = false;
#endif // #if WITH_EDITOR
}

// AActor Interface
#pragma region

void ACsSpawnerImpl::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITOR
	SetActorTickEnabled(false);
#endif // #if WITH_EDITOR

#if !UE_BUILD_SHIPPING
	if (FCsDebugDrawSphere* Sphere = GetDebugDrawSphere())
	{
		if (Sphere->bEnableInPlay)
		{
			SetActorTickEnabled(true);
		}
	}
#endif // #if !UE_BUILD_SHIPPING
}

void ACsSpawnerImpl::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

#if !UE_BUILD_SHIPPING
	DebugDraw();
#endif // #if !UE_BUILD_SHIPPING
}

bool ACsSpawnerImpl::ShouldTickIfViewportsOnly() const
{
#if WITH_EDITOR
	if (FCsLibrary_World::IsPlayInEditor(GetWorld()) ||
		FCsLibrary_World::IsPlayInEditorPreview(GetWorld()))
	{
		return true;
	}
#endif // #if WITH_EDITOR
	return Super::ShouldTickIfViewportsOnly();
}

#pragma endregion AActor Interface

// ICsStartPlay
#pragma region

void ACsSpawnerImpl::StartPlay()
{
	using namespace NCsSpawnerImplCached;

	const FString& Context = Str::StartPlay;

	// ICsSpawner

		// Params

	ConstructParams();

	checkf(Params, TEXT("%s: Params is NULL. Failed to ConstructParams."), *Context);

	CountParams = const_cast<FCsSpawnerCountParams*>(&(Params->GetCountParams()));

	checkf(CountParams, TEXT("%s: CountParams is NULL. Failed to get the reference for CountParams."), *Context);

	FrequencyParams = const_cast<FCsSpawnerFrequencyParams*>(&(Params->GetFrequencyParams()));

	checkf(FrequencyParams, TEXT("%s: FrequencyParams is NULL. Failed to get the reference for FrequencyParams."), *Context);

	TotalTime = const_cast<float*>(&(Params->GetTotalTime()));

	checkf(TotalTime, TEXT("%s: TotalTime is NULL. Failed to get the reference for TotalTime."), *Context);

	checkf(IsParamsValid(Context), TEXT("%s: Parms is NOT Valid."), *Context);

	*TotalTime = FCsLibrary_SpawnerParams::CalculateTotalTime(Params);

	// Spawn

	if (MaxConcurrentSpawnObjects > 0)
		Manager_SpawnedObjects.CreatePool(MaxConcurrentSpawnObjects);
}

#pragma endregion ICsStartPlay

void ACsSpawnerImpl::ConstructParams(){}

bool ACsSpawnerImpl::IsParamsValid(const FString& Context) const
{
	checkf(0, TEXT("ACsSpawnerImpl::IsParamsValid: This MUST be implemented."));
	return true;
}

// ICsSpawner
#pragma region

void ACsSpawnerImpl::Start()
{
	using namespace NCsSpawnerImplCached;

	const FString& Context = Str::Start;

	const FECsUpdateGroup UpdateGroup = NCsUpdateGroup::GameState;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetGameInstance());

	if (Scheduler->IsHandleValid(UpdateGroup, Start_Internal_Handle))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Spawner has already started. Call Stop first."), *Context);
		return;
	}

	checkf(IsParamsValid(Context), TEXT("%s: Params is NOT Valid."), *Context);

#if !UE_BUILD_SHIPPING
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogSpawnerTransactions))
	{
		UE_LOG(LogCs, Warning, TEXT("%s (%s): Starting"), *Context, *(GetName()));
		LogParams();
	}
#endif // #if !UE_BUILD_SHIPPING

	CurrentSpawnCount = 0;

	FCsCoroutinePayload* Payload = Scheduler->AllocatePayload(UpdateGroup);

	Payload->CoroutineImpl.BindUObject(this, &ACsSpawnerImpl::Start_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetGameInstance())->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::Start_Internal);
	Payload->SetFName(Name::Start_Internal);

	Start_Internal_Handle = Scheduler->Start(Payload);
}

void ACsSpawnerImpl::ACsSpawnerImpl::Stop()
{
	const FECsUpdateGroup UpdateGroup = NCsUpdateGroup::GameState;

#if !UE_BUILD_SHIPPING
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogSpawnerTransactions))
	{
		UE_LOG(LogCs, Warning, TEXT("ACsSpawnerImpl::Stop (%s): Stopping"), *(GetName()));
	}
#endif // #if !UE_BUILD_SHIPPING

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetGameInstance());

	Scheduler->End(UpdateGroup, Start_Internal_Handle);

	Start_Internal_Handle.Reset();

	for (FCsRoutineHandle& Handle : SpawnObjects_Internal_Handles)
	{
		Scheduler->End(UpdateGroup, Handle);

		Handle.Reset();
	}
	SpawnObjects_Internal_Handles.Reset(SpawnObjects_Internal_Handles.Max());
}

void ACsSpawnerImpl::Spawn()
{
	using namespace NCsSpawnerImplCached;

	const FString& Context = Str::Spawn;

	const FECsUpdateGroup UpdateGroup = NCsUpdateGroup::GameState;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetGameInstance());

	if (Scheduler->IsHandleValid(UpdateGroup, Start_Internal_Handle))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Spawner has already started. Call Stop first."), *Context);
		return;
	}

#if !UE_BUILD_SHIPPING
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogSpawnerTransactions))
	{
		UE_LOG(LogCs, Warning, TEXT("%s (%s): Spawning"), *(GetName()), *Context);
	}
#endif // #if !UE_BUILD_SHIPPING

	static const int32 FROM_SPAWN = -1;
	SpawnObjects(FROM_SPAWN);
}

#pragma endregion ICsSpawner

// Spawn
#pragma region

//void ACsSpawnerImpl::OnPreStart(ICsSpawner* Spawner){}

char ACsSpawnerImpl::Start_Internal(FCsRoutine* R)
{
	FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);

	ElapsedTime += R->DeltaTime;

	static const int32 CAN_SPAWN = 0;
	bool& CanSpawn = R->GetValue_Flag(CAN_SPAWN);

	static const int32 HAS_SPAWN_INTERVAL = 1;
	bool& HasSpawnInterval = R->GetValue_Flag(HAS_SPAWN_INTERVAL);

	const ECsSpawnerFrequency& FrequencyType = FrequencyParams->Type;

	CS_COROUTINE_BEGIN(R);

	OnPreStart_Event.Broadcast(this);
	OnPreSpawnObjects_Event.Broadcast(this, CurrentSpawnCount);
	OnPreSpawnObject_Event.Broadcast(this, CurrentSpawnCount);

	// If there is a Delay, Wait
	CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= FrequencyParams->Delay);

	OnStart_Event.Broadcast(this);

	CanSpawn = true;

	do
	{
		{
			ElapsedTime.Reset();

			SpawnObjects(CurrentSpawnCount);

			// Once
			if (FrequencyType == ECsSpawnerFrequency::Once)
			{
				 // Do Nothing 
			}
			// Count | TimeCount | TimeInterval
			else
			if (FrequencyType == ECsSpawnerFrequency::Count ||
				FrequencyType == ECsSpawnerFrequency::TimeCount ||
				FrequencyType == ECsSpawnerFrequency::TimeInterval)
			{
				CanSpawn		 = CurrentSpawnCount < FrequencyParams->Count;
				HasSpawnInterval = CanSpawn && FrequencyParams->Interval > 0.0f;
			}
			// Infinite
			else
			if (FrequencyType == ECsSpawnerFrequency::Infinite)
			{
				CanSpawn		 = true;
				HasSpawnInterval = true;
			}

			if (HasSpawnInterval)
			{
				OnPreSpawnObjects_Event.Broadcast(this, CurrentSpawnCount);
				OnPreSpawnObject_Event.Broadcast(this, CurrentSpawnCount);

				CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= FrequencyParams->Interval);
			}
		}
	} while (CanSpawn);

	CS_COROUTINE_WAIT_UNTIL(R, R->ElapsedTime.Time >= *TotalTime);

#if !UE_BUILD_SHIPPING
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogSpawnerTransactions))
	{
		UE_LOG(LogCs, Warning, TEXT("ACsSpawnerImpl::Start_Internal (%s): Finished Spawning %d Objects."), *(GetName()), CurrentSpawnCount);
	}
#endif // #if !UE_BUILD_SHIPPING

	OnFinish_Event.Broadcast(this);

	CS_COROUTINE_END(R);
}

//void ACsSpawnerImpl::OnPreSpawnObjects(ICsSpawner* Spawner, const int32& Index){}

void ACsSpawnerImpl::SpawnObjects(const int32& Index)
{
	using namespace NCsSpawnerImplCached;
	
	const FString& Context = Str::SpawnObjects;

	const FECsUpdateGroup UpdateGroup = NCsUpdateGroup::GameState;

#if !UE_BUILD_SHIPPING
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogSpawnerTransactions))
	{
		static const int32 FROM_SPAWN = -1;
		
		if (Index == FROM_SPAWN)
		{
			UE_LOG(LogCs, Warning, TEXT("%s (%s): Spawning Objects"));
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s (%s): Spawning Objects. Group: %d"), *Context, *(GetName()), Index);
		}
		LogCountParams();
	}
#endif // #if !UE_BUILD_SHIPPING

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetGameInstance());

	checkf(IsParamsValid(Context), TEXT("%s: Params is NOT Valid."), *Context);

	FCsCoroutinePayload* Payload = Scheduler->AllocatePayload(UpdateGroup);

	Payload->CoroutineImpl.BindUObject(this, &ACsSpawnerImpl::SpawnObjects_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetGameInstance())->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::SpawnObjects_Internal);
	Payload->SetFName(Name::SpawnObjects_Internal);
	Payload->OnEnds.AddDefaulted();
	Payload->OnEnds.Last().BindUObject(this, &ACsSpawnerImpl::SpawnObjects_Internal_OnEnd);

	SpawnObjects_Internal_Handles.AddDefaulted();
	FCsRoutineHandle& Handle = SpawnObjects_Internal_Handles.Last();

	// Allocate a Spawned Objects container
	FCsResource_SpawnerSpawnedObjects* Container = Manager_SpawnedObjects.Allocate();
	FCsSpawnerSpawnedObjects* Resource = Container->Get();

	Resource->Group = Index;

	static const int32 RESOURCE_SPAWNED_OBJECTS = 0;
	Payload->SetValue_Int(RESOURCE_SPAWNED_OBJECTS, Container->GetIndex());

	static const int32 CURRENT_GROUP = 1;
	Payload->SetValue_Int(CURRENT_GROUP, Index);

	Handle = Scheduler->Start(Payload);
}

char ACsSpawnerImpl::SpawnObjects_Internal(FCsRoutine* R)
{
	FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);

	ElapsedTime += R->DeltaTime;

	static const int32 RESOURCE_SPAWNED_OBJECTS = 0;
	const int32& ResourceIndex = R->GetValue_Int(RESOURCE_SPAWNED_OBJECTS);

	FCsSpawnerSpawnedObjects* Resource = Manager_SpawnedObjects.GetResourceAt(ResourceIndex);

	static const int32 CURRENT_GROUP = 1;
	const int32& CurrentGroup = R->GetValue_Int(CURRENT_GROUP);

	static const int32 CURRENT_COUNT_PER_SPAWN = 2;
	int32& CurrentCountPerSpawn = R->GetValue_Int(CURRENT_COUNT_PER_SPAWN);

	CS_COROUTINE_BEGIN(R);

	do
	{
		{
			ElapsedTime.Reset();
			
#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogSpawnerTransactions))
			{
				static const int32 FROM_SPAWN = -1;

				if (CurrentGroup == FROM_SPAWN)
				{
					UE_LOG(LogCs, Warning, TEXT("ACsSpawnerImpl::SpawnObjects_Internal (%s): Group: %d. Spawning Object: %d / %d"), *(GetName()), CurrentGroup, CurrentCountPerSpawn, CountParams->CountPerSpawn);
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("ACsSpawnerImpl::SpawnObjects_Internal (%s): Spawning Object: %d / %d"), *(GetName()), CurrentCountPerSpawn, CountParams->CountPerSpawn);
				}
			}
#endif // #if !UE_BUILD_SHIPPING

			// Spawn Object
			{
				UObject* SpawnedObject = SpawnObject(CurrentCountPerSpawn);

				Resource->Add(SpawnedObject);
				SpawnedObjects.Add(SpawnedObject);

				OnSpawnObject_Event.Broadcast(this, SpawnedObject);
				OnSpawnObject_ScriptEvent.Broadcast(this, SpawnedObject);
			}

			++CurrentSpawnCount;
			++CurrentCountPerSpawn;

			if (CurrentCountPerSpawn < CountParams->CountPerSpawn)
			{
				OnPreSpawnObject_Event.Broadcast(this, CurrentSpawnCount);

				CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= CountParams->TimeBetweenCountPerSpawn);
			}
		}
	} while (CurrentCountPerSpawn < CountParams->CountPerSpawn);

	OnSpawnObjects_Event.Broadcast(this, Resource->Objects);

#if !UE_BUILD_SHIPPING
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogSpawnerTransactions))
	{
		static const int32 FROM_SPAWN = -1;

		if (CurrentGroup == FROM_SPAWN)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsSpawnerImpl::SpawnObjects_Internal (%s): Finished Spawning %d Objects."), *(GetName()), CountParams->CountPerSpawn);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("ACsSpawnerImpl::SpawnObjects_Internal (%s): Group: %d. Finished Spawning %d Objects."), *(GetName()), CurrentGroup, CountParams->CountPerSpawn);
		}
	}
#endif // #if !UE_BUILD_SHIPPING

	CS_COROUTINE_END(R);
}

void ACsSpawnerImpl::SpawnObjects_Internal_OnEnd(FCsRoutine* R)
{
	// "Free" the Spawned Objects resource
	static const int32 RESOURCE_SPAWNED_OBJECTS = 0;
	const int32& ResourceIndex = R->GetValue_Int(RESOURCE_SPAWNED_OBJECTS);

	FCsSpawnerSpawnedObjects* Resource = Manager_SpawnedObjects.GetResourceAt(ResourceIndex);

	Resource->Reset();

	Manager_SpawnedObjects.DeallocateAt(ResourceIndex);
}

//void ACsSpawnerImpl::OnPreSpawnObject(ICsSpawner* Spawner, const int32& Index){}

UObject* ACsSpawnerImpl::SpawnObject(const int32& Index)
{
	checkf(0, TEXT("ACsSpawnerImpl::SpawnObject: This MUST be implemented."));
	return nullptr;
}

#pragma endregion Spawn

// Log
#pragma region

void ACsSpawnerImpl::LogParams() const
{
	// CountParams
	LogCountParams();

	// FrequencyParams
	UE_LOG(LogCs, Warning, TEXT("- FrequencyParams"));
	UE_LOG(LogCs, Warning, TEXT("-- Type: %s"), EMCsSpawnerFrequency::Get().ToChar(FrequencyParams->Type));
	UE_LOG(LogCs, Warning, TEXT("-- Delay: %f"), FrequencyParams->Delay);
	UE_LOG(LogCs, Warning, TEXT("-- Count: %d"), FrequencyParams->Count);
	UE_LOG(LogCs, Warning, TEXT("-- Interval: %f"), FrequencyParams->Interval);
	UE_LOG(LogCs, Warning, TEXT("-- Time: %f"), FrequencyParams->Time);

	// TotalTime
	UE_LOG(LogCs, Warning, TEXT("- TotalTime: %f"), *TotalTime);
}

void ACsSpawnerImpl::LogCountParams() const
{
	UE_LOG(LogCs, Warning, TEXT("- CountParams"));
	UE_LOG(LogCs, Warning, TEXT("-- CountPerSpawn: %d"), CountParams->CountPerSpawn);
	UE_LOG(LogCs, Warning, TEXT("-- TimeBetweenCountPerSpawn: %f"), CountParams->TimeBetweenCountPerSpawn);
}

#pragma endregion Log

// Debug
#pragma region

void ACsSpawnerImpl::DebugDraw()
{
	// Circle
	if (FCsDebugDrawCircle* Circle = GetDebugDrawCircle())
	{
		Circle->Draw(GetWorld(), GetActorTransform());
	}
	// Sphere
	if (FCsDebugDrawSphere* Sphere = GetDebugDrawSphere())
	{
		Sphere->Draw(GetWorld(), GetActorTransform());
	}
}

FCsDebugDrawCircle* ACsSpawnerImpl::GetDebugDrawCircle()
{
	return nullptr;
}

FCsDebugDrawSphere* ACsSpawnerImpl::GetDebugDrawSphere()
{
	return nullptr;
}

#pragma endregion Debug