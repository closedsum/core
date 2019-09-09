// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "../CoreUObject/Public/UObject/Object.h"
#include "HeadMountedDisplay/Public/HeadMountedDisplayTypes.h"
#include "CsLibrary_Manager_HMD.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FCsLibraryManagerHMD_OnChange_WornState, const EHMDWornState::Type&, NewState);
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_OnWornState_FirstWorn);
DECLARE_DYNAMIC_DELEGATE(FCsLibraryManagerHMD_OnWornState_FirstNotWorn);

UCLASS()
class CSCORE_API UCsLibrary_Manager_HMD : public UObject
{
	GENERATED_UCLASS_BODY()

// Worn State
#pragma region
public:

	/**
	 * Bind to Event OnChange_WornState. This event is fired when HMDWornState changes.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: OnChange_WornState"))
	static void BindToEvent_OnChange_WornState(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_OnChange_WornState Delegate);

	/**
	 * Unbind from Event OnChange_WornState. This event is fired when HMDWornState changes.
	 * @param Delegate (Event)
	*/
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: OnChange_WornState"))
	static void UnbindFromEvent_OnChange_WornState(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_OnChange_WornState Delegate);

	/**
	 * Bind to Event OnWornState_FirstWorn. This event is fired when HMDWornState first changes to Worn.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: OnWornState_FirstWorn"))
	static void BindToEvent_OnWornState_FirstWorn(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_OnWornState_FirstWorn Delegate);

	/**
	 * Unbind from Event OnWornState_FirstWorn. This event is fired when HMDWornState first changes to Worn.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: OnWornState_FirstWorn"))
	static void UnbindFromEvent_OnWornState_FirstWorn(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_OnWornState_FirstWorn Delegate);

	/**
	 * Bind to Event OnWornState_FirstNotWorn. This event is fired when HMDWornState first changes to NotWorn.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Bind to Event: OnWornState_FirstWorn"))
	static void BindToEvent_OnWornState_FirstNotWorn(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_OnWornState_FirstNotWorn Delegate);

	/**
	 * Unbind from Event OnWornState_FirstNotWorn. This event is fired when HMDWornState first changes to NotWorn.
	 * @param Delegate (Event)
	 */
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|HMD", meta = (DisplayName = "Unbind from Event: OnWornState_FirstWorn"))
	static void UnbindFromEvent_OnWornState_FirstNotWorn(UPARAM(DisplayName = "Event") FCsLibraryManagerHMD_OnWornState_FirstNotWorn Delegate);

#pragma endregion Worn State
};