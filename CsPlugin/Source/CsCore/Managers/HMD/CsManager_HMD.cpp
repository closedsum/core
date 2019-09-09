// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/HMD/CsManager_HMD.h"
#include "CsCore.h"

#include "HeadMountedDisplay/Public/HeadMountedDisplayFunctionLibrary.h"

// static initializations
UCsManager_HMD* UCsManager_HMD::s_Instance;
bool UCsManager_HMD::s_bShutdown = false;

UCsManager_HMD::UCsManager_HMD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_HMD* UCsManager_HMD::Get()
{
	if (s_bShutdown)
		return nullptr;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_HMD>(GetTransientPackage(), UCsManager_HMD::StaticClass(), TEXT("Manager_HMD_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->Initialize();
	}

	return s_Instance;
}

/*static*/ void UCsManager_HMD::Init()
{
	s_bShutdown = false;
	UCsManager_HMD::Get();
}

/*static*/ void UCsManager_HMD::Shutdown()
{
	if (!s_Instance)
		return;

	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(s_Instance->TickDelegateHandle);

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
}

void UCsManager_HMD::Initialize()
{
	// Register delegate for ticker callback
	TickDelegate	   = FTickerDelegate::CreateUObject(this, &UCsManager_HMD::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);

	WornState.Set(EHMDWornState::Unknown);
	WornState.Resolve();
	WornState.OnChange_Event.AddUObject(this, &UCsManager_HMD::OnChange_WornState);
}

void UCsManager_HMD::CleanUp()
{
	
}

#pragma endregion Singleton

// Tick
#pragma region

bool UCsManager_HMD::Tick(float DeltaSeconds)
{
	WornState = UHeadMountedDisplayFunctionLibrary::GetHMDWornState();
	return true;
}

#pragma endregion Tick

// Worn State
#pragma region

void UCsManager_HMD::OnChange_WornState(const EHMDWornState::Type& NewState)
{
	OnChange_WornState_Event.Broadcast(NewState);
	OnChange_WornState_ScriptEvent.Broadcast(NewState);
	// FirstWorn
	if (NewState == EHMDWornState::Worn)
	{
		OnWornState_FirstWorn_Event.Broadcast();
		OnWornState_FirstWorn_ScriptEvent.Broadcast();
	}
	// NotWorn
	else
	if (NewState == EHMDWornState::NotWorn)
	{
		OnWornState_FirstNotWorn_Event.Broadcast();
		OnWornState_FirstNotWorn_ScriptEvent.Broadcast();
	}
}

#pragma endregion Worn State