// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/HMD/CsManager_HMD.h"
#include "CsHMD.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Misc/CoreDelegates.h"

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
	FTSTicker::GetCoreTicker().RemoveTicker(s_Instance->TickDelegateHandle);

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
}

void UCsManager_HMD::Initialize()
{
	// Register delegate for ticker callback
	TickDelegate	   = FTickerDelegate::CreateUObject(this, &UCsManager_HMD::Tick);
	TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(TickDelegate);

	FCoreDelegates::VRHeadsetTrackingInitializingAndNeedsHMDToBeTrackedDelegate.AddUObject(this, &UCsManager_HMD::OnHMDTrackingInitializingAndNeedsHMDToBeTracked);
	FCoreDelegates::VRHeadsetTrackingInitializedDelegate.AddUObject(this, &UCsManager_HMD::OnHMDTrackingInitialized);
	FCoreDelegates::VRHeadsetRecenter.AddUObject(this, &UCsManager_HMD::OnHMDRecenter);
	FCoreDelegates::VRHeadsetLost.AddUObject(this, &UCsManager_HMD::OnHMDLost);
	FCoreDelegates::VRHeadsetReconnected.AddUObject(this, &UCsManager_HMD::OnHMDReconnected);
	FCoreDelegates::VRHeadsetConnectCanceled.AddUObject(this, &UCsManager_HMD::OnHMDConnectCanceled);
	FCoreDelegates::VRHeadsetPutOnHead.AddUObject(this, &UCsManager_HMD::OnHMDPutOnHead);
	FCoreDelegates::VRHeadsetRemovedFromHead.AddUObject(this, &UCsManager_HMD::OnHMDRemovedFromHead);
	FCoreDelegates::VRControllerRecentered.AddUObject(this, &UCsManager_HMD::OnVRControllerRecentered);
}

void UCsManager_HMD::CleanUp()
{
	FCoreDelegates::VRHeadsetTrackingInitializingAndNeedsHMDToBeTrackedDelegate.RemoveAll(this);
	FCoreDelegates::VRHeadsetTrackingInitializedDelegate.RemoveAll(this);
	FCoreDelegates::VRHeadsetRecenter.RemoveAll(this);
	FCoreDelegates::VRHeadsetLost.RemoveAll(this);
	FCoreDelegates::VRHeadsetReconnected.RemoveAll(this);
	FCoreDelegates::VRHeadsetConnectCanceled.RemoveAll(this);
	FCoreDelegates::VRHeadsetPutOnHead.RemoveAll(this);
	FCoreDelegates::VRHeadsetRemovedFromHead.RemoveAll(this);
	FCoreDelegates::VRControllerRecentered.RemoveAll(this);

	OnHMDTrackingInitializingAndNeedsHMDToBeTracked_Event.Clear();
	OnHMDTrackingInitialized_Event.Clear();
	OnHMDRecenter_Event.Clear();
	OnHMDLost_Event.Clear();
	OnHMDReconnected_Event.Clear();
	OnHMDConnectCanceled_Event.Clear();
	OnHMDPutOnHead_Event.Clear();
	OnHMDRemovedFromHead_Event.Clear();
	OnVRControllerRecentered_Event.Clear();
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

UWorld* UCsManager_HMD::GetCurrentWorld()
{
	return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr;
}

void UCsManager_HMD::OnHMDTrackingInitializingAndNeedsHMDToBeTracked()
{
	OnHMDTrackingInitializingAndNeedsHMDToBeTracked_Event.Broadcast();
}

void UCsManager_HMD::OnHMDTrackingInitialized()
{
	OnHMDTrackingInitialized_Event.Broadcast();
}

void UCsManager_HMD::OnHMDRecenter()
{
	OnHMDRecenter_Event.Broadcast();
}

void UCsManager_HMD::OnHMDLost()
{
	OnHMDLost_Event.Broadcast();
}

void UCsManager_HMD::OnHMDReconnected()
{
	OnHMDReconnected_Event.Broadcast();
}

void UCsManager_HMD::OnHMDConnectCanceled()
{
	OnHMDConnectCanceled_Event.Broadcast();
}

void UCsManager_HMD::OnHMDPutOnHead()
{
	OnHMDPutOnHead_Event.Broadcast();
}

void UCsManager_HMD::OnHMDRemovedFromHead()
{
	OnHMDRemovedFromHead_Event.Broadcast();
}

void UCsManager_HMD::OnVRControllerRecentered()
{
	OnVRControllerRecentered_Event.Broadcast();
}