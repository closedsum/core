// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsCoroutineScheduler.h"
#include "CsCore.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Coroutine/CsGetCoroutineScheduler.h"
#endif // #if WITH_EDITOR

// static initializations
UCsCoroutineScheduler* UCsCoroutineScheduler::s_Instance;
bool UCsCoroutineScheduler::s_bShutdown = false;

// Cache
#pragma region

namespace NCsCoroutineCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoroutineScheduler, Allocate);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoroutineScheduler, Start);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoroutineScheduler, Update);
	}
}

#pragma endregion Cache

UCsCoroutineScheduler::UCsCoroutineScheduler(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsCoroutineScheduler* UCsCoroutineScheduler::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetCoroutineScheduler(InRoot)->GetCoroutineScheduler();
#else
	if (s_bShutdown)
		return nullptr;

	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsCoroutineScheduler::Init(UObject* InRoot)
{
#if WITH_EDITOR
	ICsGetCoroutineScheduler* GetCoroutineScheduler = Get_GetCoroutineScheduler(InRoot);

	UCsCoroutineScheduler* Scheduler = NewObject<UCsCoroutineScheduler>(InRoot, UCsCoroutineScheduler::StaticClass(), TEXT("Coroutine_Scheduler_Singleton"), RF_Transient | RF_Public);

	GetCoroutineScheduler->SetCoroutineScheduler(Scheduler);

	Scheduler->SetMyRoot(InRoot);
	Scheduler->Initialize();
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsCoroutineScheduler>(GetTransientPackage(), UCsCoroutineScheduler::StaticClass(), TEXT("Coroutine_Scheduler_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsCoroutineScheduler::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetCoroutineScheduler* GetCoroutineScheduler = Get_GetCoroutineScheduler(InRoot);
	UCsCoroutineScheduler* Scheduler				= GetCoroutineScheduler->GetCoroutineScheduler();
	Scheduler->CleanUp();

	GetCoroutineScheduler->SetCoroutineScheduler(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetCoroutineScheduler* UCsCoroutineScheduler::Get_GetCoroutineScheduler(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsCoroutineScheduler::Get: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsCoroutineScheduler::Get: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsCoroutineScheduler::Get: Manager_Singleton is NULL."));

	ICsGetCoroutineScheduler* GetCoroutineScheduler = Cast<ICsGetCoroutineScheduler>(Manager_Singleton);

	checkf(GetCoroutineScheduler, TEXT("UCsCoroutineScheduler::Get: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetCoroutineScheduler."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetCoroutineScheduler;
}

/*static*/ ICsGetCoroutineScheduler* UCsCoroutineScheduler::GetSafe_GetCoroutineScheduler(UObject* Object)
{
	if (!Object)
		return nullptr;

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
		return nullptr;

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
		return nullptr;

	return Cast<ICsGetCoroutineScheduler>(Manager_Singleton);
}

/*static*/ UCsCoroutineScheduler* UCsCoroutineScheduler::GetSafe(UObject* Object)
{
	if (ICsGetCoroutineScheduler* GetCoroutineScheduler = GetSafe_GetCoroutineScheduler(Object))
		return GetCoroutineScheduler->GetCoroutineScheduler();
	return nullptr;
}

/*static*/ UCsCoroutineScheduler* UCsCoroutineScheduler::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsCoroutineScheduler* Scheduler = GetSafe(World->GetGameInstance()))
			return Scheduler;

		UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::GetFromWorldContextObject: Failed to Manager Save of type UCsCoroutineScheduler from GameInstance."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsCoroutineScheduler::Initialize()
{
	// Schedules
	{
		const int32& Count = EMCsUpdateGroup::Get().Num();

		Schedules.Reset(Count);

		for (const FECsUpdateGroup& Group : EMCsUpdateGroup::Get())
		{
			Schedules.AddDefaulted();
			FCsCoroutineSchedule& Schedule = Schedules.Last();
			Schedule.SetGroup(Group);
		}
	}
}

void UCsCoroutineScheduler::CleanUp()
{
	for (FCsCoroutineSchedule& Schedule : Schedules)
	{
		Schedule.End();
	}
	Schedules.Reset();
}

#pragma endregion Singleton

// Start
#pragma region

const FCsRoutineHandle& UCsCoroutineScheduler::Start(FCsResource_CoroutinePayload* PayloadContainer)
{
	FCsCoroutinePayload* Payload = PayloadContainer->Get();

	return Schedules[Payload->Group.GetValue()].Start(PayloadContainer);
}

const FCsRoutineHandle& UCsCoroutineScheduler::Start(FCsCoroutinePayload* Payload)
{
	return Schedules[Payload->Group.GetValue()].Start(Payload);
}

const FCsRoutineHandle& UCsCoroutineScheduler::StartChild(FCsResource_CoroutinePayload* PayloadContainer)
{
	FCsCoroutinePayload* Payload = PayloadContainer->Get();

	return Schedules[Payload->Group.GetValue()].StartChild(PayloadContainer);
}

const FCsRoutineHandle& UCsCoroutineScheduler::StartChild(FCsCoroutinePayload* Payload)
{
	return Schedules[Payload->Group.GetValue()].StartChild(Payload);
}

#pragma endregion Start

// Update
#pragma region

void UCsCoroutineScheduler::Update(const FECsUpdateGroup& Group, const FCsDeltaTime& DeltaTime)
{
	Schedules[Group.GetValue()].Update(DeltaTime);
}

#pragma endregion Update

// End
#pragma region

void UCsCoroutineScheduler::End(const FECsUpdateGroup& Group)
{
	Schedules[Group.GetValue()].End();
}

void UCsCoroutineScheduler::End(const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
{
	Schedules[Group.GetValue()].End(Handle);
}

void UCsCoroutineScheduler::UCsCoroutineScheduler::EndAll()
{
	for (FCsCoroutineSchedule& Schedule : Schedules)
	{
		Schedule.End();
	}
}

#pragma endregion End

// Payload
#pragma region

FCsResource_CoroutinePayload* UCsCoroutineScheduler::AllocatePayloadContainer(const FECsUpdateGroup& Group)
{
	return Schedules[Group.GetValue()].AllocatePayloadContainer();
}

FCsCoroutinePayload* UCsCoroutineScheduler::AllocatePayload(const FECsUpdateGroup& Group)
{
	return Schedules[Group.GetValue()].AllocatePayload();
}

#pragma endregion Payload

// Message
#pragma region

void UCsCoroutineScheduler::BroadcastMessage(const FECsUpdateGroup& Group, const ECsCoroutineMessage& MessageType, const FName& Message, void* InOwner /*=nullptr*/)
{
	Schedules[Group.Value].BroadcastMessage(MessageType, Message, nullptr);
}

#pragma endregion Message