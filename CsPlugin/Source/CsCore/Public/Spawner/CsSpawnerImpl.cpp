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
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Library/CsLibrary_World.h"
#include "Spawner/Params/CsLibrary_SpawnerParams.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Spawner
#include "Spawner/Point/CsSpawnerPointImpl.h"
#include "Spawner/Params/CsSpawnerParamsImpl.h"

// Cached
#pragma region

namespace NCsSpawnerImpl
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSpawnerImpl, StartPlay);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSpawnerImpl, SetupFromParams);
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
}

#pragma endregion Cached

ACsSpawnerImpl::ACsSpawnerImpl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// ICsStartPlay
	bHasStartedPlay(false),
	// StartPlay
	bOverride_StartPlay(false),
	bReceiveStartPlay(false),
	// Point
	PointImpl(nullptr),
	bConstructDefaultPointImpl(false),
	DeconstructPointImplImpl(nullptr),
	// Params
	Params(nullptr),
	CountParams(nullptr),
	FrequencyParams(nullptr),
	TotalTime(nullptr),
	bConstructDefaultParams(false),
	DeconstructParamsImpl(nullptr),
	IsParamsValidImpl(nullptr),
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
	SpawnObjects_Internal_Handles(),
	OnPreSpawnObject_Event(),
	OnSpawnObject_ScriptEvent(),
	bOverride_SpawnObject(false)
{
	PrimaryActorTick.bCanEverTick = true;
#if WITH_EDITOR
	PrimaryActorTick.bStartWithTickEnabled = true;
#else
	PrimaryActorTick.bStartWithTickEnabled = false;
#endif // #if WITH_EDITOR
}

// UObject Interface
#pragma region

void ACsSpawnerImpl::BeginDestroy()
{
	Super::BeginDestroy();

	if (Params)
	{
		DeconstructParamsImpl(Params);
		Params = nullptr;
	}
}

#pragma endregion UObject Interface

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
	typedef NCsWorld::FLibrary WorldLibrary;

	if (WorldLibrary::IsPlayInEditor(GetWorld()) ||
		WorldLibrary::IsPlayInEditorPreview(GetWorld()))
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
	using namespace NCsSpawnerImpl::NCached;

	const FString& Context = Str::StartPlay;

#if WITH_EDITOR
	if (bOverride_StartPlay)
	{
		if (CS_CVAR_LOG_IS_SHOWING(LogOverrideFunctions))
		{
			UE_LOG(LogCs, Warning, TEXT("%s: OVERRIDDEN for %s."), *Context, *(GetName()));
		}

		Override_StartPlay();

		bHasStartedPlay = true;
		return;
	}
#endif // #if WITH_EDITOR

	// ICsSpawner

		// PointImpl
	ConstructPointImpl();
		// Params
	ConstructParams();
	SetupFromParams();

	if (bReceiveStartPlay)
		ReceiveStartPlay();
	bHasStartedPlay = true;
}

#pragma endregion ICsStartPlay

// Point
#pragma region

void ACsSpawnerImpl::ConstructPointImpl()
{
	if (bConstructDefaultPointImpl)
	{
		typedef NCsSpawner::NPoint::FImpl PointImplType;

		PointImpl = new PointImplType();

		DeconstructPointImplImpl = &PointImplType::Deconstruct;

		PointImpl->SetSpawner(this);
	}
}

#define PointImplType NCsSpawner::NPoint::IImpl
void ACsSpawnerImpl::SetPointImpl(const FString& Context, PointImplType* InPointImpl, void(*InDeconstructPointImplImpl)(void*))
{
#undef PointImplType

	CS_IS_PTR_NULL_CHECKED(InPointImpl)

	checkf(InDeconstructPointImplImpl, TEXT("%s: InDeconstructPointImplImpl is NULL."), *Context);

	if (PointImpl)
	{
		DeconstructPointImplImpl(PointImpl);
		PointImpl = nullptr;
	}

	PointImpl = InPointImpl;
	DeconstructPointImplImpl = InDeconstructPointImplImpl;

	PointImpl->SetSpawner(this);
}

FTransform ACsSpawnerImpl::PointImpl_GetCurrentTransform()
{
	return PointImpl->GetCurrentTransform();
}

#pragma endregion Point

// Params
#pragma region

void ACsSpawnerImpl::ConstructParams()
{
	if (bConstructDefaultParams)
	{
		typedef NCsSpawner::NParams::FImpl ParamsType;

		Params = new ParamsType();

		DeconstructParamsImpl = &ParamsType::Deconstruct;
	}
}

#define ParamsType NCsSpawner::NParams::IParams
void ACsSpawnerImpl::SetParams(const FString& Context, ParamsType* InParams, void(*InDeconstructParamsImpl)(void*), bool(*InIsParamsValidImpl)(const FString&, ParamsType*))
{
#undef ParamsType

	CS_IS_PTR_NULL_CHECKED(InParams)

	checkf(InDeconstructParamsImpl, TEXT("%s: InDeconstructParamsImpl is NULL."), *Context);

	// Check PointImpl exists
	checkf(PointImpl, TEXT("%s: No PointImpl exists. This must be set before setting any params."), *Context);

	if (Params)
	{
		DeconstructParamsImpl(Params);
		Params = nullptr;
	}

	Params = InParams;
	DeconstructParamsImpl = InDeconstructParamsImpl;
	IsParamsValidImpl = InIsParamsValidImpl;

	PointImpl->SetParams(Params);

	SetupFromParams();
}

void ACsSpawnerImpl::SetupFromParams()
{
	using namespace NCsSpawnerImpl::NCached;

	const FString& Context = Str::SetupFromParams;

	checkf(Params, TEXT("%s: Params is NULL. Failed to ConstructParams."), *Context);

	typedef NCsSpawner::NParams::FCount CountParamsType;

	CountParams = const_cast<CountParamsType*>(&(Params->GetCountParams()));

	checkf(CountParams, TEXT("%s: CountParams is NULL. Failed to get the reference for CountParams."), *Context);

	typedef NCsSpawner::NParams::FFrequency FrequencyParamsType;

	FrequencyParams = const_cast<FrequencyParamsType*>(&(Params->GetFrequencyParams()));

	checkf(FrequencyParams, TEXT("%s: FrequencyParams is NULL. Failed to get the reference for FrequencyParams."), *Context);

	TotalTime = const_cast<float*>(&(Params->GetTotalTime()));

	checkf(TotalTime, TEXT("%s: TotalTime is NULL. Failed to get the reference for TotalTime."), *Context);

	check(IsParamsValidImpl(Context, Params));

	typedef NCsSpawner::NParams::FLibrary ParamsLibrary;

	*TotalTime = ParamsLibrary::CalculateTotalTime(Context, Params);

	// Spawn

	if (MaxConcurrentSpawnObjects > 0)
		Manager_SpawnedObjects.CreatePool(MaxConcurrentSpawnObjects);
}

#pragma endregion Params

// ICsSpawner
#pragma region

void ACsSpawnerImpl::Start()
{
	using namespace NCsSpawnerImpl::NCached;

	const FString& Context = Str::Start;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	UObject* ContextRoot			   = CoroutineSchedulerLibrary::GetContextRootChecked(Context, this);
	UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(ContextRoot);
	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameState;

	if (Scheduler->IsHandleValid(UpdateGroup, Start_Internal_Handle))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Spawner has already started. Call Stop first."), *Context);
		return;
	}

	check(IsParamsValidImpl(Context, Params));

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogSpawnerTransactions))
	{
		UE_LOG(LogCs, Warning, TEXT("%s (%s): Starting"), *Context, *(GetName()));
		LogParams();
	}
#endif // #if !UE_BUILD_SHIPPING

	CurrentSpawnCount = 0;

	SpawnedObjects.Reset();

	PointImpl->Prepare();

	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE Start_Internal

	Payload->CoroutineImpl.BindUObject(this, &ACsSpawnerImpl::COROUTINE);
	Payload->StartTime = UCsManager_Time::Get(ContextRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	Start_Internal_Handle = Scheduler->Start(Payload);
}

void ACsSpawnerImpl::ACsSpawnerImpl::Stop()
{
#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogSpawnerTransactions))
	{
		UE_LOG(LogCs, Warning, TEXT("ACsSpawnerImpl::Stop (%s) : Stopping"), *(GetName()));
	}
#endif // #if !UE_BUILD_SHIPPING

	UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(GetGameInstance());
	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameState;

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
	using namespace NCsSpawnerImpl::NCached;

	const FString& Context = Str::Spawn;

	UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(GetGameInstance());
	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameState;

	if (Scheduler->IsHandleValid(UpdateGroup, Start_Internal_Handle))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Spawner has already started. Call Stop first."), *Context);
		return;
	}

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogSpawnerTransactions))
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
	using namespace NCsSpawnerImpl::NCached;

	const FString& Context = Str::Start_Internal;

	FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);

	ElapsedTime += R->DeltaTime;

	static const int32 CAN_SPAWN = 0;
	bool& CanSpawn = R->GetValue_Flag(CAN_SPAWN);

	static const int32 HAS_SPAWN_INTERVAL = 1;
	bool& HasSpawnInterval = R->GetValue_Flag(HAS_SPAWN_INTERVAL);

	typedef NCsSpawner::EFrequency FrequencyType;

	const FrequencyType& Frequency = FrequencyParams->GetType();

	CS_COROUTINE_BEGIN(R);

	OnPreStart_Event.Broadcast(this);
	OnPreSpawnObjects_Event.Broadcast(this, CurrentSpawnCount);
	OnPreSpawnObject_Event.Broadcast(this, CurrentSpawnCount);

	// If there is a Delay, Wait
	CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= FrequencyParams->GetDelay());

	OnStart_Event.Broadcast(this);

	CanSpawn = true;

	do
	{
		{
			ElapsedTime.Reset();

			SpawnObjects(CurrentSpawnCount);

			// Once
			if (Frequency == FrequencyType::Once)
			{
				CanSpawn = false;
			}
			// Count | TimeCount | TimeInterval
			else
			if (Frequency == FrequencyType::Count ||
				Frequency == FrequencyType::TimeCount ||
				Frequency == FrequencyType::TimeInterval)
			{
				CanSpawn		 = CurrentSpawnCount < FrequencyParams->GetCount();
				HasSpawnInterval = CanSpawn && FrequencyParams->GetInterval() > 0.0f;
			}
			// Infinite
			else
			if (Frequency == FrequencyType::Infinite)
			{
				CanSpawn		 = true;
				HasSpawnInterval = true;
			}

			if (HasSpawnInterval)
			{
				OnPreSpawnObjects_Event.Broadcast(this, CurrentSpawnCount);
				OnPreSpawnObject_Event.Broadcast(this, CurrentSpawnCount);

				CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= FrequencyParams->GetInterval());
			}
		}
	} while (CanSpawn);

	CS_COROUTINE_WAIT_UNTIL(R, R->ElapsedTime.Time >= *TotalTime);

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogSpawnerTransactions))
	{
		UE_LOG(LogCs, Warning, TEXT("%s (%s): Finished Spawning %d Objects."), *Context, *(GetName()), CurrentSpawnCount);
	}
#endif // #if !UE_BUILD_SHIPPING

	OnFinish_Event.Broadcast(this);

	CS_COROUTINE_END(R);
}

//void ACsSpawnerImpl::OnPreSpawnObjects(ICsSpawner* Spawner, const int32& Index){}

void ACsSpawnerImpl::SpawnObjects(const int32& Index)
{
	using namespace NCsSpawnerImpl::NCached;
	
	const FString& Context = Str::SpawnObjects;

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogSpawnerTransactions))
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

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	UObject* ContextRoot			   = CoroutineSchedulerLibrary::GetContextRootChecked(Context, this);
	UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(ContextRoot);
	const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameState;

	check(IsParamsValidImpl(Context, Params));

	NCsCoroutine::NPayload::FImpl* Payload = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE SpawnObjects_Internal

	Payload->CoroutineImpl.BindUObject(this, &ACsSpawnerImpl::COROUTINE);
	Payload->StartTime = UCsManager_Time::Get(ContextRoot)->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);
	Payload->OnEnds.AddDefaulted();
	Payload->OnEnds.Last().BindUObject(this, &ACsSpawnerImpl::SpawnObjects_Internal_OnEnd);

	#undef COROUTINE

	SpawnObjects_Internal_Handles.AddDefaulted();
	FCsRoutineHandle& Handle = SpawnObjects_Internal_Handles.Last();

	// Allocate a Spawned Objects container
	typedef NCsSpawner::NSpawnedObjects::FResource ResourceContainerType;
	typedef NCsSpawner::FSpawnedObjects ResourceType;

	ResourceContainerType* Container = Manager_SpawnedObjects.Allocate();
	ResourceType* Resource			 = Container->Get();

	Resource->Group = Index;

	static const int32 RESOURCE_SPAWNED_OBJECTS = 0;
	Payload->SetValue_Int(RESOURCE_SPAWNED_OBJECTS, Container->GetIndex());

	static const int32 CURRENT_GROUP = 1;
	Payload->SetValue_Int(CURRENT_GROUP, Index);

	Handle = Scheduler->Start(Payload);
}

char ACsSpawnerImpl::SpawnObjects_Internal(FCsRoutine* R)
{
	using namespace NCsSpawnerImpl::NCached;

	const FString& Context = Str::SpawnObjects_Internal;

	FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);

	ElapsedTime += R->DeltaTime;

	static const int32 RESOURCE_SPAWNED_OBJECTS = 0;
	const int32& ResourceIndex = R->GetValue_Int(RESOURCE_SPAWNED_OBJECTS);

	typedef NCsSpawner::FSpawnedObjects ResourceType;

	ResourceType* Resource = Manager_SpawnedObjects.GetResourceAt(ResourceIndex);

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
			if (CS_CVAR_LOG_IS_SHOWING(LogSpawnerTransactions))
			{
				static const int32 FROM_SPAWN = -1;

				if (CurrentGroup == FROM_SPAWN)
				{
					UE_LOG(LogCs, Warning, TEXT("%s (%s): Group: %d. Spawning Object: %d / %d"), *Context, *(GetName()), CurrentGroup, CurrentCountPerSpawn, CountParams->GetCountPerSpawn());
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("%s (%s): Spawning Object: %d / %d"), *Context, *(GetName()), CurrentCountPerSpawn, CountParams->GetCountPerSpawn());
				}
			}
#endif // #if !UE_BUILD_SHIPPING

			// Spawn Object
			{
				UObject* SpawnedObject = SpawnObject(CurrentSpawnCount, CurrentGroup, CurrentCountPerSpawn);

				checkf(SpawnedObject, TEXT("%s: Failed to Spawn Object at %d / %d."), *Context, CurrentCountPerSpawn, CountParams->GetCountPerSpawn());

				Resource->Add(SpawnedObject);
				SpawnedObjects.Add(SpawnedObject);

				OnSpawnObject_Event.Broadcast(this, SpawnedObject);
				OnSpawnObject_ScriptEvent.Broadcast(this, SpawnedObject);
			}

			++CurrentSpawnCount;
			++CurrentCountPerSpawn;

			PointImpl->Advance(CurrentSpawnCount, CurrentGroup, CurrentCountPerSpawn);

			if (CurrentCountPerSpawn < CountParams->GetCountPerSpawn())
			{
				OnPreSpawnObject_Event.Broadcast(this, CurrentSpawnCount);

				CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= CountParams->GetTimeBetweenCountPerSpawn());
			}
		}
	} while (CurrentCountPerSpawn < CountParams->GetCountPerSpawn());

	OnSpawnObjects_Event.Broadcast(this, Resource->Objects);

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogSpawnerTransactions))
	{
		static const int32 FROM_SPAWN = -1;

		if (CurrentGroup == FROM_SPAWN)
		{
			UE_LOG(LogCs, Warning, TEXT("%s (%s): Finished Spawning %d Objects."), *Context, *(GetName()), CountParams->GetCountPerSpawn());
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s (%s): Group: %d. Finished Spawning %d Objects."), *Context, *(GetName()), CurrentGroup, CountParams->GetCountPerSpawn());
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

	typedef NCsSpawner::FSpawnedObjects ResourceType;

	ResourceType* Resource = Manager_SpawnedObjects.GetResourceAt(ResourceIndex);

	Resource->Reset();

	Manager_SpawnedObjects.DeallocateAt(ResourceIndex);
}

//void ACsSpawnerImpl::OnPreSpawnObject(ICsSpawner* Spawner, const int32& Index){}

UObject* ACsSpawnerImpl::SpawnObject(const int32& Count, const int32& Group, const int32& CountPerGroup)
{
#if WITH_EDITOR
	if (bOverride_SpawnObject)
	{
		if (CS_CVAR_LOG_IS_SHOWING(LogOverrideFunctions))
		{
			UE_LOG(LogCs, Warning, TEXT("ACsSpawnerImpl::bOverride_SpawnObject: OVERRIDDEN for %s."), *(GetName()));
		}

		return Override_SpawnObject(Count, Group, CountPerGroup);
	}
#endif // #if WITH_EDITOR
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
	typedef NCsSpawner::EMFrequency FrequencyMapType;

	UE_LOG(LogCs, Warning, TEXT("- FrequencyParams"));
	UE_LOG(LogCs, Warning, TEXT("-- Type: %s"), FrequencyMapType::Get().ToChar(FrequencyParams->GetType()));
	UE_LOG(LogCs, Warning, TEXT("-- Delay: %f"), FrequencyParams->GetDelay());
	UE_LOG(LogCs, Warning, TEXT("-- Count: %d"), FrequencyParams->GetCount());
	UE_LOG(LogCs, Warning, TEXT("-- Interval: %f"), FrequencyParams->GetInterval());
	UE_LOG(LogCs, Warning, TEXT("-- Time: %f"), FrequencyParams->GetTime());

	// TotalTime
	UE_LOG(LogCs, Warning, TEXT("- TotalTime: %f"), *TotalTime);
}

void ACsSpawnerImpl::LogCountParams() const
{
	UE_LOG(LogCs, Warning, TEXT("- CountParams"));
	UE_LOG(LogCs, Warning, TEXT("-- CountPerSpawn: %d"), CountParams->GetCountPerSpawn());
	UE_LOG(LogCs, Warning, TEXT("-- TimeBetweenCountPerSpawn: %f"), CountParams->GetTimeBetweenCountPerSpawn());
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