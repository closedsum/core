// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsManager_Time.h"
#include "CsCore.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Time/CsGetManagerTime.h"
#endif // #if WITH_EDITOR

// static initializations
UCsManager_Time* UCsManager_Time::s_Instance;
bool UCsManager_Time::s_bShutdown = false;

UCsManager_Time::UCsManager_Time(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_Time* UCsManager_Time::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerTime(InRoot)->GetManager_Time();
#else
	if (s_bShutdown)
		return nullptr;

	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Time::Init(UObject* InRoot)
{
#if WITH_EDITOR
	ICsGetManagerTime* GetManagerTime = Get_GetManagerTime(InRoot);

	UCsManager_Time* Manager_Time = NewObject<UCsManager_Time>(InRoot, UCsManager_Time::StaticClass(), TEXT("Manager_Time_Singleton"), RF_Transient | RF_Public);

	GetManagerTime->SetManager_Time(Manager_Time);

	Manager_Time->SetMyRoot(InRoot);
	Manager_Time->Initialize();
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Time>(GetTransientPackage(), UCsManager_Time::StaticClass(), TEXT("Manager_Time_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Time::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerTime* GetManagerTime = Get_GetManagerTime(InRoot);
	UCsManager_Time* Manager_Time	  = GetManagerTime->GetManager_Time();
	Manager_Time->CleanUp();

	GetManagerTime->SetManager_Time(nullptr);
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

/*static*/ ICsGetManagerTime* UCsManager_Time::Get_GetManagerTime(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Time::Get: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Time::Get: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Time::Get: Manager_Singleton is NULL."));

	ICsGetManagerTime* GetManagerTime = Cast<ICsGetManagerTime>(Manager_Singleton);

	checkf(GetManagerTime, TEXT("UCsManager_Time::Get: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerTime."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerTime;
}

#endif // #if WITH_EDITOR

void UCsManager_Time::Initialize()
{
	// Time Groups
	{
		const int32& Count = EMCsUpdateGroup::Get().Num();

		UpdateGroups.Reset(Count);

		for (const FECsUpdateGroup& Group : EMCsUpdateGroup::Get())
		{
			UpdateGroups.AddDefaulted();
		}
	}
}

void UCsManager_Time::CleanUp()
{
}

#pragma endregion Singleton

void UCsManager_Time::Start(const FECsUpdateGroup& Group)
{
	UpdateGroups[Group.Value].Start();
}

// Pause
#pragma region

void UCsManager_Time::Pause(const FECsUpdateGroup& Group)
{
	UpdateGroups[Group.Value].Pause();
}

void UCsManager_Time::Unpause(const FECsUpdateGroup& Group)
{
	UpdateGroups[Group.Value].Unpause();
}

#pragma endregion Pause

// Update
#pragma region

void UCsManager_Time::Update(const FECsUpdateGroup& Group, const float& DeltaTime)
{
	UpdateGroups[Group.GetValue()].Update(DeltaTime);
}

void UCsManager_Time::Update(const FECsUpdateGroup& Group, const float& DeltaTime, const float& Time, const float& RealTime)
{
	UpdateGroups[Group.GetValue()].Update(DeltaTime, Time, RealTime);
}

#pragma endregion Update

FCsTime UCsManager_Time::GetTimeNow(const FECsUpdateGroup& Group)
{
	FCsTime Time = GetTime(Group);

	Time.DateTime = FDateTime::Now();

	return Time;
}