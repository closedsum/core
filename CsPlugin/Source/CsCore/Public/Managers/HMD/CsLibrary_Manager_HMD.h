// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "../CoreUObject/Public/UObject/Object.h"
#include "HeadMountedDisplay/Public/HeadMountedDisplayTypes.h"
#include "CsLibrary_Manager_HMD.generated.h"

/** Sent when the platform needs the user to fix headset tracking on startup (PS4 Morpheus only) */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_HMDTrackingInitializingAndNeedsHMDToBeTracked);
/** Sent when the platform finds that needed headset tracking on startup has completed (PS4 Morpheus only) */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_HMDTrackingInitialized);
/** Sent when the platform requests a low-level VR recentering */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_HMDRecenter);
/** Sent when connection to VR HMD is lost */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_HMDLost);
/** Sent when connection to VR HMD is restored */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_HMDReconnected);
/** Sent when connection to VR HMD connection is refused by the player */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_HMDConnectCanceled);
/** Sent when the VR HMD detects that it has been put on by the player. */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_HMDPutOnHead);
/** Sent when the VR HMD detects that it has been taken off by the player. */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_HMDRemovedFromHead);
/** Sent when a 3DOF VR controller is recentered */
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_VRControllerRecentered);

UCLASS()
class CSCORE_API UCsLibrary_Manager_HMD : public UObject
{
	GENERATED_UCLASS_BODY()

	/**
	 * Bind to Event: HMDTrackingInitializingAndNeedsHMDToBeTracked.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: HMDTrackingInitializingAndNeedsHMDToBeTracked"))
	static void BindToEvent_HMDTrackingInitializingAndNeedsHMDToBeTracked(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDTrackingInitializingAndNeedsHMDToBeTracked Delegate);

	/**
	 * Unbind from Event: HMDTrackingInitializingAndNeedsHMDToBeTracked.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: HMDTrackingInitializingAndNeedsHMDToBeTracked"))
	static void UnbindFromEvent_HMDTrackingInitializingAndNeedsHMDToBeTracked(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDTrackingInitializingAndNeedsHMDToBeTracked Delegate);

	/**
	 * Bind to Event: HMDTrackingInitialized.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: HMDTrackingInitialized"))
	static void BindToEvent_HMDTrackingInitialized(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDTrackingInitialized Delegate);

	/**
	 * Unbind from Event: HMDTrackingInitialized.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: HMDTrackingInitialized"))
	static void UnbindFromEvent_HMDTrackingInitialized(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDTrackingInitialized Delegate);

	/**
	 * Bind to Event: HMDRecenter.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: HMDRecenter"))
	static void BindToEvent_HMDRecenter(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDRecenter Delegate);

	/**
	 * Unbind from Event: HMDRecenter.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: HMDRecenter"))
	static void UnbindFromEvent_HMDRecenter(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDRecenter Delegate);

	/**
	 * Bind to Event: HMDLost.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: HMDLost"))
	static void BindToEvent_HMDLost(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDLost Delegate);

	/**
	 * Unbind from Event: HMDLost.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: HMDLost"))
	static void UnbindFromEvent_HMDLost(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDLost Delegate);

	/**
	 * Bind to Event: HMDReconnected.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: HMDReconnected"))
	static void BindToEvent_HMDReconnected(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDReconnected Delegate);

	/**
	 * Unbind from Event: HMDReconnected.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: HMDReconnected"))
	static void UnbindFromEvent_HMDReconnected(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDReconnected Delegate);

	/**
	 * Bind to Event: HMDConnectCanceled.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: HMDConnectCanceled"))
	static void BindToEvent_HMDConnectCanceled(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDConnectCanceled Delegate);

	/**
	 * Unbind from Event: HMDConnectCanceled.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: HMDConnectCanceled"))
	static void UnbindFromEvent_HMDConnectCanceled(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDConnectCanceled Delegate);

	/**
	 * Bind to Event: HMDPutOnHead.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: HMDPutOnHead"))
	static void BindToEvent_HMDPutOnHead(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDPutOnHead Delegate);

	/**
	 * Unbind from Event: HMDPutOnHead.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: HMDPutOnHead"))
	static void UnbindFromEvent_HMDPutOnHead(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDPutOnHead Delegate);

	/**
	 * Bind to Event: HMDRemovedFromHead.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: HMDRemovedFromHead"))
	static void BindToEvent_HMDRemovedFromHead(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDRemovedFromHead Delegate);

	/**
	 * Unbind from Event: HMDRemovedFromHead.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: HMDRemovedFromHead"))
	static void UnbindFromEvent_HMDRemovedFromHead(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_HMDRemovedFromHead Delegate);

	/**
	 * Bind to Event: VRControllerRecentered.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: VRControllerRecentered"))
	static void BindToEvent_VRControllerRecentered(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_VRControllerRecentered Delegate);

	/**
	 * Unbind from Event: VRControllerRecentered.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: VRControllerRecentered"))
	static void UnbindFromEvent_VRControllerRecentered(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_VRControllerRecentered Delegate);
};