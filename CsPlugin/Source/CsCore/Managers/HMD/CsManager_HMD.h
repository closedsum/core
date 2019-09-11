// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "../CoreUObject/Public/UObject/Object.h"
#include "Types/CsTypes_Primitive.h"
#include "HeadMountedDisplay/Public/HeadMountedDisplayTypes.h"
#include "CsManager_HMD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerHMD_OnChange_WornState, const EHMDWornState::Type&, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerHMD_OnWornState_FirstWorn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerHMD_OnWornState_FirstNotWorn);

UCLASS(transient)
class CSCORE_API UCsManager_HMD : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsManager_HMD* Get();
	static void Init();
	static void Shutdown();

protected:

	void Initialize();
	void CleanUp();

private:
	// Singleton data
	static UCsManager_HMD* s_Instance;
	static bool s_bShutdown;

#pragma endregion Singleton

// Tick
#pragma region
public:

	/** Delegate for callbacks to Tick */
	FTickerDelegate	TickDelegate;

	/** Handle to various registered delegates */
	FDelegateHandle	TickDelegateHandle;

	bool Tick(float DeltaSeconds);

#pragma endregion Tick

// Worn State
#pragma region
protected:

	TCsProperty<EHMDWornState::Type> WornState;

	void OnChange_WornState(const EHMDWornState::Type& NewState);

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnChange_WornState, const EHMDWornState::Type&);

	FOnChange_WornState OnChange_WornState_Event;

	FCsManagerHMD_OnChange_WornState OnChange_WornState_ScriptEvent;
	
	DECLARE_MULTICAST_DELEGATE(FOnWornState_FirstWorn);

	FOnWornState_FirstWorn OnWornState_FirstWorn_Event;

	FCsManagerHMD_OnWornState_FirstWorn OnWornState_FirstWorn_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE(FOnWornState_FirstNotWorn);

	FOnWornState_FirstNotWorn OnWornState_FirstNotWorn_Event;

	FCsManagerHMD_OnWornState_FirstNotWorn OnWornState_FirstNotWorn_ScriptEvent;

#pragma endregion Worn State

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHMDDelegate);

	// This will be called on Morpheus if the HMD starts up and is not fully initialized (in NOT_STARTED or CALIBRATING states).  
	// The HMD will stay in NOT_STARTED until it is successfully position tracked.  Until it exits NOT_STARTED orientation
	// based reprojection does not happen.  Therefore we do not update rotation at all to avoid user discomfort.
	// Instructions to get the hmd tracked should be shown to the user.
	// Sony may fix this eventually. (PS4 Only) 
	FHMDDelegate HMDTrackingInitializingAndNeedsHMDToBeTrackedDelegate;

	// This will be called on Morpheus when the HMD is done initializing and therefore
	// reprojection will start functioning.
	// The app can continue now. (PS4 Only) 
	FHMDDelegate HMDTrackingInitializedDelegate;

	// This will be called when the application is asked for VR headset recenter.  
	FHMDDelegate HMDRecenteredDelegate;

	// This will be called when connection to HMD is lost.  
	FHMDDelegate HMDLostDelegate;

	// This will be called when connection to HMD is restored.  
	FHMDDelegate HMDReconnectedDelegate;

	// This will be called when the user declines to connect the HMD when prompted to do so by a system dialog. (PS4 Only)  
	FHMDDelegate HMDConnectCanceledDelegate;

	// This will be called when the HMD detects that it has been put on by a player.  
	FHMDDelegate HMDPutOnHeadDelegate;

	// This will be called when the HMD detects that it has been taken off by a player (disconnecting the hmd also causes it to register as taken off).  
	FHMDDelegate HMDRemovedFromHeadDelegate;

	// This will be called when the VR system recenters a controller.  
	FHMDDelegate VRControllerRecenteredDelegate;

private:
	/** Native handlers that get registered with the actual FCoreDelegates, and then proceed to broadcast to the delegates above */
	void HMDTrackingInitializingAndNeedsHMDToBeTrackedDelegate_Handler()	{ HMDTrackingInitializingAndNeedsHMDToBeTrackedDelegate.Broadcast(); }
	void HMDTrackingInitializedDelegate_Handler()	{ HMDTrackingInitializedDelegate.Broadcast(); }
	void HMDRecenteredDelegate_Handler()	{ HMDRecenteredDelegate.Broadcast(); }
	void HMDLostDelegate_Handler()			{ HMDLostDelegate.Broadcast(); }
	void HMDReconnectedDelegate_Handler()	{ HMDReconnectedDelegate.Broadcast(); }
	void HMDConnectCanceledDelegate_Handler() { HMDConnectCanceledDelegate.Broadcast(); }
	void HMDPutOnHeadDelegate_Handler() { HMDPutOnHeadDelegate.Broadcast(); }
	void HMDRemovedFromHeadDelegate_Handler() { HMDRemovedFromHeadDelegate.Broadcast(); }
	void VRControllerRecentered_Handler() { VRControllerRecenteredDelegate.Broadcast(); }
};