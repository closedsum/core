// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsManager_Time.h"
#include "CsCore.h"

// static initializations
UCsManager_Time* UCsManager_Time::s_Instance;
bool UCsManager_Time::s_bShutdown = false;

UCsManager_Time::UCsManager_Time(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_Time* UCsManager_Time::Get()
{
	if (s_bShutdown)
		return nullptr;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Time>(GetTransientPackage(), UCsManager_Time::StaticClass(), TEXT("Manager_Time_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->Initialize();
	}

	return s_Instance;
}

/*static*/ void UCsManager_Time::Init(UCsManager_Time* Manager)
{
	s_bShutdown = false;
	UCsManager_Time::Get();
}

/*static*/ void UCsManager_Time::Shutdown()
{
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
}

void UCsManager_Time::Initialize()
{
	// Time Groups
	{
		const int32& Count = EMCsTimeGroup::Get().Num();

		TimeGroups.Reserve(Count);

		for (const FECsTimeGroup& Group : EMCsTimeGroup::Get())
		{
			TimeGroups.AddDefaulted();
		}
	}
}

void UCsManager_Time::CleanUp()
{
}

#pragma endregion Singleton

void UCsManager_Time::Start(const FECsTimeGroup& Group)
{
	TimeGroups[Group.Value].Start();
}

// Pause
#pragma region

void UCsManager_Time::Pause(const FECsTimeGroup& Group)
{
	TimeGroups[Group.Value].Pause();
}

void UCsManager_Time::Unpause(const FECsTimeGroup& Group)
{
	TimeGroups[Group.Value].Unpause();
}

#pragma endregion Pause

// Update
#pragma region

void UCsManager_Time::Update(const FECsTimeGroup& Group, const float& DeltaTime)
{
	TimeGroups[Group.Value].Update(DeltaTime);
}

void UCsManager_Time::Update(const FECsTimeGroup& Group, const float& DeltaTime, const float& Time, const float& RealTime)
{
	TimeGroups[Group.Value].Update(DeltaTime, Time, RealTime);
}

#pragma endregion Update