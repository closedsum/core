// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsCoroutineScheduler.h"
#include "CsCore.h"
#include "CsCVars.h"

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
		const FString Allocate = TEXT("UCsCoroutineScheduler::Allocate");
		const FString Start = TEXT("UCsCoroutineScheduler::Start");
		const FString Update = TEXT("UCsCoroutineScheduler::Update");
	}
}

#pragma endregion Cache

UCsCoroutineScheduler::UCsCoroutineScheduler(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsCoroutineScheduler* UCsCoroutineScheduler::Get()
{
	if (s_bShutdown)
		return nullptr;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsCoroutineScheduler>(GetTransientPackage(), UCsCoroutineScheduler::StaticClass(), TEXT("Coroutine_Scheduler_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->Initialize();
	}

	return s_Instance;
}

/*static*/ void UCsCoroutineScheduler::Init()
{
	s_bShutdown = false;
	UCsCoroutineScheduler::Get();
}

/*static*/ void UCsCoroutineScheduler::Shutdown()
{
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
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

/*static*/ UCsCoroutineScheduler* UCsCoroutineScheduler::Get(UObject* InRoot)
{
	ICsGetCoroutineScheduler* GetCoroutineScheduler = Get_GetCoroutineScheduler(InRoot);

	return GetCoroutineScheduler->GetCoroutineScheduler();
}

/*static*/ void UCsCoroutineScheduler::Init(UObject* InRoot)
{
	ICsGetCoroutineScheduler* GetCoroutineScheduler = Get_GetCoroutineScheduler(InRoot);

	UCsCoroutineScheduler* Scheduler = NewObject<UCsCoroutineScheduler>(InRoot, UCsCoroutineScheduler::StaticClass(), TEXT("Coroutine_Scheduler_Singleton"), RF_Transient | RF_Public);

	GetCoroutineScheduler->SetCoroutineScheduler(Scheduler);

	Scheduler->SetMyRoot(InRoot);
	Scheduler->Initialize();
}

/*static*/ void UCsCoroutineScheduler::Shutdown(UObject* InRoot)
{
	ICsGetCoroutineScheduler* GetCoroutineScheduler = Get_GetCoroutineScheduler(InRoot);
	UCsCoroutineScheduler* Scheduler				= GetCoroutineScheduler->GetCoroutineScheduler();
	Scheduler->CleanUp();

	GetCoroutineScheduler->SetCoroutineScheduler(nullptr);
}

#endif // #if WITH_EDITOR

void UCsCoroutineScheduler::Initialize()
{
	// Schedules
	{
		const int32& Count = EMCsUpdateGroup::Get().Num();

		Schedules.Reserve(Count);

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

const FCsRoutineHandle& UCsCoroutineScheduler::Start(FCsMemoryResource_CoroutinePayload* PayloadContainer)
{
	FCsCoroutinePayload* Payload = PayloadContainer->Get();

	return Schedules[Payload->Group.Value].Start(PayloadContainer);
}

const FCsRoutineHandle& UCsCoroutineScheduler::Start(FCsCoroutinePayload* Payload)
{
	return Schedules[Payload->Group.Value].Start(Payload);
}

const FCsRoutineHandle& UCsCoroutineScheduler::StartChild(FCsMemoryResource_CoroutinePayload* PayloadContainer)
{
	FCsCoroutinePayload* Payload = PayloadContainer->Get();

	return Schedules[Payload->Group.Value].StartChild(PayloadContainer);
}

const FCsRoutineHandle& UCsCoroutineScheduler::StartChild(FCsCoroutinePayload* Payload)
{
	return Schedules[Payload->Group.Value].StartChild(Payload);
}

#pragma endregion Start

// Update
#pragma region

void UCsCoroutineScheduler::Update(const FECsUpdateGroup& Group, const FCsDeltaTime& DeltaTime)
{
	Schedules[Group.Value].Update(DeltaTime);
}

#pragma endregion Update

// End
#pragma region

void UCsCoroutineScheduler::End(const FECsUpdateGroup& Group)
{
	Schedules[Group.Value].End();
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

FCsMemoryResource_CoroutinePayload* UCsCoroutineScheduler::AllocatePayload(const FECsUpdateGroup& Group)
{
	return Schedules[Group.Value].AllocatePayload();
}

#pragma endregion Payload

// Message
#pragma region

void UCsCoroutineScheduler::BroadcastMessage(const FECsUpdateGroup& Group, const ECsCoroutineMessage& MessageType, const FName& Message, void* InOwner /*=nullptr*/)
{
	Schedules[Group.Value].BroadcastMessage(MessageType, Message, nullptr);
}

#pragma endregion Message