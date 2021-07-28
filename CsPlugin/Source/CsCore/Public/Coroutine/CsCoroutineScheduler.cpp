// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsCoroutineScheduler.h"
#include "CsCore.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_Valid.h"
// Singleton
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Coroutine/CsGetCoroutineScheduler.h"
#endif // #if WITH_EDITOR

// static initializations
UCsCoroutineScheduler* UCsCoroutineScheduler::s_Instance;
bool UCsCoroutineScheduler::s_bShutdown = false;

// Cache
#pragma region

namespace NCsCoroutineScheduler
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoroutineScheduler, GetFromWorldContextObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoroutineScheduler, Allocate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoroutineScheduler, Start);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoroutineScheduler, Update);
		}
	}
}

#pragma endregion Cache

UCsCoroutineScheduler::UCsCoroutineScheduler(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsCoroutineScheduler* UCsCoroutineScheduler::Get(UObject* InRoot /*=nullptr*/)
{
	return Get_GetCoroutineScheduler(InRoot)->GetCoroutineScheduler();
}

/*static*/ UCsCoroutineScheduler* UCsCoroutineScheduler::GetSafe(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetCoroutineScheduler* GetCoroutineScheduler = GetSafe_GetCoroutineScheduler(Context, Object, Log))
		return GetCoroutineScheduler->GetCoroutineScheduler();
	return nullptr;
}

#endif // #if WITH_EDITOR

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

/*static*/ ICsGetCoroutineScheduler* UCsCoroutineScheduler::GetSafe_GetCoroutineScheduler(const FString& Context, UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	CS_IS_PTR_NULL_RET_NULL(InRoot)

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	if (!GetManagerSingleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Singleton from InRoot: %s with Class: %s."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}
	return Cast<ICsGetCoroutineScheduler>(Manager_Singleton);
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

#pragma endregion Start

// Update
#pragma region

#pragma endregion Update

// End
#pragma region


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

#pragma endregion Payload

// Message
#pragma region

#pragma endregion Message