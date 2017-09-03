// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/GameState.h"
#include "CsTypes.h"
#include "CsGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsGameState_OnTick, const float&, DeltaSeconds);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsGameState_OnTick, const float&);

UCLASS()
class CSCORE_API ACsGameState : public AGameState
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;

	FBindableEvent_CsGameState_OnTick OnTick_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsGameState_OnTick OnTick_ScriptEvent;

	virtual void PostActorCreated() override;

	/** Called during seamless travel transition twice (once when the transition map is loaded, once when destination map is loaded) */
	virtual void SeamlessTravelTransitionCheckpoint(bool bToTransitionMap) override;

#if WITH_EDITOR
	//virtual void OnLevelTravelTransition();
#endif // #if WITH_EDITOR

	// Javascript
#pragma region
public:

	TSubclassOf<class ACsJavascriptEntryPoint> JavascriptEntryPointClass;

	UPROPERTY(Transient)
	class ACsJavascriptEntryPoint* JavascriptEntryPoint;

#if WITH_EDITOR

	void SetupJavascriptEntryPoint();

	static char SetupJavascriptEntryPoint_Internal(FCsRoutine* r);

#endif // #if WITH_EDITOR

#pragma endregion Javascript

	// Routines
#pragma region
public:

	CsAddRoutine MyAddRoutine;
	CsRemoveRoutine MyRemoveRoutine;

#pragma endregion Routines

	// LastTickActor
#pragma region
public:

	UPROPERTY()
	class ACsLastTickActor* LastTickActor;

	void SetupLastTickActor();

	CsCoroutine CsSetupLastTickActor_Internal;

	uint8 SetupLastTickActor_Internal_RoutineType;

	struct FCsRoutine* SetupLastTickActor_Internal_Routine;

#pragma endregion LastTickActor

	// Managers
#pragma region
public:

	UPROPERTY()
	class ACsManager_WidgetActor* Manager_WidgetActor;

	UPROPERTY()
	class ACsManager_FX* Manager_FX;

	UPROPERTY()
	class ACsManager_Sound* Manager_Sound;

	UPROPERTY()
	class ACsManager_Projectile* Manager_Projectile;

	UPROPERTY()
	class ACsManager_InteractiveActor* Manager_InteractiveActor;

	UPROPERTY()
	class ACsManager_AI* Manager_AI;

	UPROPERTY()
	class ACsManager_Decal* Manager_Decal;

#pragma endregion Managers
};