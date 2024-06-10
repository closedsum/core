// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coroutine/CsCoroutineScheduler.h"

// Settings
#include "Coroutine/CsSettings_CoroutineScheduler.h"
// Package
#include "UObject/Package.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_Valid.h"
// Singleton
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Coroutine/CsGetCoroutineScheduler.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsCoroutineScheduler)

// static initializations
UCsCoroutineScheduler* UCsCoroutineScheduler::s_Instance;
bool UCsCoroutineScheduler::s_bShutdown = false;

namespace NCsCoroutineScheduler
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoroutineScheduler, AllocageCustomGroupIndexAndOwnerID);
		}
	}
}

UCsCoroutineScheduler::UCsCoroutineScheduler(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// Default
	DefaultSchedules_Internal(),
	DefaultSchedules(),
	// Custom
	CustomSchedules()
{
}

#define USING_NS_CACHED using namespace NCsCoroutineScheduler::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsCoroutineScheduler::NCached; \
	const FString& Context = Str::__FunctionName
#define DefaultScheduleType NCsCoroutine::NSchedule::FDefault
#define CustomScheduleType NCsCoroutine::NSchedule::FCustom

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
	// Default
	{
		const int32& Count = EMCsUpdateGroup::Get().Num();

		DefaultSchedules_Internal.Reset(Count - 1);
		DefaultSchedules.Reset(Count);

		for (const FECsUpdateGroup& Group : EMCsUpdateGroup::Get())
		{
			DefaultScheduleType& Schedule = DefaultSchedules_Internal.AddDefaulted_GetRef();
			Schedule.SetGroup(Group);
		}

		DefaultSchedules.AddDefaulted();
		DefaultSchedules[NCsUpdateGroup::Custom.GetValue()] = nullptr;

		for (int32 I = 0; I < Count - 1; ++I)
		{
			DefaultSchedules.AddDefaulted();
			DefaultSchedules[I + 1] = &(DefaultSchedules_Internal[I]);
		}
	}
	// Custom
	{
		const FCsSettings_CoroutineScheduler_Custom& Settings = FCsSettings_CoroutineScheduler_Custom::Get();

		const int32& MaxGroups = Settings.MaxGroups;

		CustomSchedules.Reset(MaxGroups);

		for (int32 I = 0; I < MaxGroups; ++I)
		{
			CustomScheduleType& Schedule = CustomSchedules.AddDefaulted_GetRef();
			Schedule.SetGroup(NCsUpdateGroup::Custom);
		}
	}
}

void UCsCoroutineScheduler::CleanUp()
{
	for (DefaultScheduleType& Schedule : DefaultSchedules_Internal)
	{
		Schedule.End();
	}
	DefaultSchedules_Internal.Reset();
	DefaultSchedules.Reset();
}

#pragma endregion Singleton

// End
#pragma region

void UCsCoroutineScheduler::UCsCoroutineScheduler::EndAll()
{
	for (DefaultScheduleType& Schedule : DefaultSchedules_Internal)
	{
		Schedule.End();
	}

	for (CustomScheduleType& Schedule : CustomSchedules)
	{
		Schedule.End();
	}
}

#pragma endregion End

// Custom
#pragma region

	// Owner
#pragma region

void UCsCoroutineScheduler::AllocageCustomGroupIndexAndOwnerID(int32& OutGroupIndex, int32& OutOwnerID)
{
	SET_CONTEXT(AllocageCustomGroupIndexAndOwnerID);

	const int32 Count = CustomSchedules.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		CustomScheduleType& Schedule = CustomSchedules[I];

		if (Schedule.HasFreeOwnerID())
		{
			OutOwnerID	  = Schedule.AllocateOwnerID();
			OutGroupIndex = I;
			return;
		}
	}
	checkf(0, TEXT("%s: All Custom Schedules are Exhausted."), *Context);
}

#pragma endregion Owner

#pragma endregion Custom

#undef USING_NS_CACHED
#undef SET_CONTEXT
#undef DefaultScheduleType
#undef CustomScheduleType