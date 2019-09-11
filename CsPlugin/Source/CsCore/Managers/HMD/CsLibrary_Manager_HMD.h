// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "../CoreUObject/Public/UObject/Object.h"
#include "HeadMountedDisplay/Public/HeadMountedDisplayTypes.h"
#include "CsLibrary_Manager_HMD.generated.h"

/** Sent when the platform needs the user to fix headset tracking on startup (PS4 Morpheus only) */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked);
/** Sent when the platform finds that needed headset tracking on startup has completed (PS4 Morpheus only) */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_VRHeadsetTrackingInitialized);
/** Sent when the platform requests a low-level VR recentering */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_VRHeadsetRecenter);
/** Sent when connection to VR HMD is lost */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_VRHeadsetLost);
/** Sent when connection to VR HMD is restored */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_VRHeadsetReconnected);
/** Sent when connection to VR HMD connection is refused by the player */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_VRHeadsetConnectCanceled);
/** Sent when the VR HMD detects that it has been put on by the player. */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_VRHeadsetPutOnHead);
/** Sent when the VR HMD detects that it has been taken off by the player. */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_VRHeadsetRemovedFromHead);
/** Sent when a 3DOF VR controller is recentered */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_VRControllerRecentered);

UCLASS()
class CSCORE_API UCsLibrary_Manager_HMD : public UObject
{
	GENERATED_UCLASS_BODY()

	/**
	 * Bind to Event: VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked"))
	static void BindToEvent_VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked Delegate);

	/**
	 * Unbind from Event: VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked"))
	static void UnbindFromEvent_VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_VRHeadsetTrackingInitializingAndNeedsHMDToBeTracked Delegate);

	/**
	 * Bind to Event: VRHeadsetTrackingInitialized.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: VRHeadsetTrackingInitialized"))
	static void BindToEvent_VRHeadsetTrackingInitialized(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_VRHeadsetTrackingInitialized Delegate);

	/**
	 * Unbind from Event: VRHeadsetTrackingInitialized.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: VRHeadsetTrackingInitialized"))
	static void UnbindFromEvent_VRHeadsetTrackingInitialized(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_VRHeadsetTrackingInitialized Delegate);

	/**
	 * Bind to Event: VRHeadsetRecenter.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: VRHeadsetRecenter"))
	static void BindToEvent_VRHeadsetRecenter(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_VRHeadsetRecenter Delegate);

	/**
	 * Unbind from Event: VRHeadsetRecenter.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: VRHeadsetRecenter"))
	static void UnbindFromEvent_VRHeadsetRecenter(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_VRHeadsetRecenter Delegate);

	/**
	 * Bind to Event: VRHeadsetLost.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: VRHeadsetLost"))
	static void BindToEvent_VRHeadsetLost(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_VRHeadsetLost Delegate);

	/**
	 * Unbind from Event: VRHeadsetLost.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: VRHeadsetLost"))
	static void UnbindFromEvent_VRHeadsetLost(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_VRHeadsetLost Delegate);
};