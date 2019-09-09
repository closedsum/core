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
};