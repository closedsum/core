// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "../CoreUObject/Public/UObject/Object.h"
#include "Types/CsTypes_Primitive.h"
#include "HeadMountedDisplay/Public/HeadMountedDisplayTypes.h"
#include "CsManager_HMD.generated.h"

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


	TWeakObjectPtr<UWorld> CurrentWorld;

	UWorld* GetCurrentWorld();

	// This will be called on Morpheus if the HMD starts up and is not fully initialized (in NOT_STARTED or CALIBRATING states).  
	// The HMD will stay in NOT_STARTED until it is successfully position tracked.  Until it exits NOT_STARTED orientation
	// based reprojection does not happen.  Therefore we do not update rotation at all to avoid user discomfort.
	// Instructions to get the hmd tracked should be shown to the user.
	// Sony may fix this eventually. (PS4 Only) 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHMDTrackingInitializingAndNeedsHMDToBeTracked);
	FOnHMDTrackingInitializingAndNeedsHMDToBeTracked OnHMDTrackingInitializingAndNeedsHMDToBeTracked_Event;

	// This will be called on Morpheus when the HMD is done initializing and therefore
	// reprojection will start functioning.
	// The app can continue now. (PS4 Only) 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHMDTrackingInitialized);
	FOnHMDTrackingInitialized OnHMDTrackingInitialized_Event;

	// This will be called when the application is asked for VR headset recenter.
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHMDRecentered);
	FOnHMDRecentered OnHMDRecenter_Event;

	// This will be called when connection to HMD is lost.
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHMDLost);
	FOnHMDLost OnHMDLost_Event;

	// This will be called when connection to HMD is restored.
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHMDReconnected);
	FOnHMDReconnected OnHMDReconnected_Event;

	// This will be called when the user declines to connect the HMD when prompted to do so by a system dialog. (PS4 Only)
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHMDConnectCanceled);
	FOnHMDConnectCanceled OnHMDConnectCanceled_Event;

	// This will be called when the HMD detects that it has been put on by a player.
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHMDPutOnHead);
	FOnHMDPutOnHead OnHMDPutOnHead_Event;

	// This will be called when the HMD detects that it has been taken off by a player (disconnecting the hmd also causes it to register as taken off).  
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHMDRemovedFromHead);
	FOnHMDRemovedFromHead OnHMDRemovedFromHead_Event;

	// This will be called when the VR system recenters a controller.
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVRControllerRecentered);
	FOnVRControllerRecentered OnVRControllerRecentered_Event;

private:

	/** Native handlers that get registered with the actual FCoreDelegates, and then proceed to broadcast to the delegates above */
	void OnHMDTrackingInitializingAndNeedsHMDToBeTracked();
	void OnHMDTrackingInitialized();
	void OnHMDRecenter();
	void OnHMDLost();
	void OnHMDReconnected();
	void OnHMDConnectCanceled();
	void OnHMDPutOnHead();
	void OnHMDRemovedFromHead();
	void OnVRControllerRecentered();
};