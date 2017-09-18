// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "CsCommon.h"
#include "CsTypes.h"
#include "CsCoroutineScheduler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsCoroutineScheduler_OnTick, const float&, DeltaSeconds);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsCoroutineScheduler_OnTick, const float&);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsCoroutineScheduler_OnTickUpdate, float, DeltaSeconds);

UCLASS(transient)
class CSCORE_API UCsCoroutineScheduler : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:	

	static UCsCoroutineScheduler* Get();

	static void Init();
	static void Shutdown();

protected:

	void Initialize();
	void CleanUp();

public:

	/** Delegate for callbacks to Tick */
	FTickerDelegate	TickDelegate;

	/** Handle to various registered delegates */
	FDelegateHandle	TickDelegateHandle;

	virtual bool Tick(float DeltaSeconds);

	FBindableEvent_CsCoroutineScheduler_OnTick OnTick_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsCoroutineScheduler_OnTick OnTick_ScriptEvent;

	TWeakObjectPtr<UObject> MyOwner;

	UObject* GetMyOwner();

// Run on Tick
#pragma region 
public:

	struct FCsRoutine RoutinePool[CS_ROUTINE_POOL_SIZE];
	int32 RoutinePoolIndex;
	TArray<struct FCsRoutine*> RoutinesToInit;
	TArray<struct FCsRoutine*> RoutinesToRun;

	struct FCsRoutine* Allocate(CsCoroutine InCoroutine, AActor* InActor, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine = nullptr, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(CsCoroutine InCoroutine, UObject* InObject, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(CsCoroutine InCoroutine, AActor* InActor, UObject* InObject, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE, const bool &DoInit = true, const bool &PerformFirstRun = false);

	struct FCsRoutine* Start(CsCoroutine InCoroutine, AActor* InActor);
	struct FCsRoutine* Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor);
	struct FCsRoutine* Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* Start(CsCoroutine InCoroutine, UObject* InObject);
	struct FCsRoutine* Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject);
	struct FCsRoutine* Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* Start(CsCoroutine InCoroutine, AActor* InActor, UObject* InObject);
	struct FCsRoutine* Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject);
	struct FCsRoutine* Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);

	struct FCsRoutine* StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor);
	struct FCsRoutine* StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor);
	struct FCsRoutine* StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, UObject* InObject);
	struct FCsRoutine* StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject);
	struct FCsRoutine* StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject);
	struct FCsRoutine* StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject);
	struct FCsRoutine* StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);

	struct FCsRoutine* StartRoutine(struct FCsRoutine* R);
	
	UPROPERTY(BlueprintAssignable, Category = "0 CoroutineScheduler")
	FBindableEvent_CsCoroutineScheduler_OnTickUpdate OnTickUpdate_Event;

	void OnTick_Update(const float &DeltaSeconds);
	void EndAll();

	void BroadcastMessage(const TCsCoroutineMessage &MessageType, const FName &Message, UObject* InOwner);
	void BroadcastMessage(const TCsCoroutineMessage &MessageType, const FName &Message);

#pragma endregion Run on Tick

// Run on CalcCamera
#pragma region
public:

	struct FCsRoutine CalcCamera_RoutinePool[CS_ROUTINE_POOL_SIZE];
	int32 CalcCamera_RoutinePoolIndex;
	TArray<struct FCsRoutine*> CalcCamera_RoutinesToInit;
	TArray<struct FCsRoutine*> CalcCamera_RoutinesToRun;

	struct FCsRoutine* CalcCamera_Allocate(CsCoroutine InCoroutine, AActor* InActor, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine = nullptr, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* CalcCamera_Allocate(CsCoroutine InCoroutine, UObject* InObject, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* CalcCamera_Allocate(CsCoroutine InCoroutine, AActor* InActor, UObject* InObject, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStioCondition, AActor* InActor, UObject* InObject, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStioCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStioCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE, const bool &DoInit = true, const bool &PerformFirstRun = false);

	struct FCsRoutine* CalcCamera_Start(CsCoroutine InCoroutine, AActor* InActor);
	struct FCsRoutine* CalcCamera_Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor);
	struct FCsRoutine* CalcCamera_Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* CalcCamera_Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* CalcCamera_Start(CsCoroutine InCoroutine, AActor* InActor, UObject* InObject);
	struct FCsRoutine* CalcCamera_Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject);
	struct FCsRoutine* CalcCamera_Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* CalcCamera_Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);

	struct FCsRoutine* CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor);
	struct FCsRoutine* CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor);
	struct FCsRoutine* CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject);
	struct FCsRoutine* CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject);
	struct FCsRoutine* CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);
	
	struct FCsRoutine* CalcCamera_StartRoutine(struct FCsRoutine* R);
	
	void OnCalcCamera_Update(float DeltaSeconds);
	void CalcCamera_EndAll();

#pragma endregion Run on CalcCamera

private:
	// Singleton data
	static UCsCoroutineScheduler* s_coroutineSchedulerSingleton;
	static bool s_bCoroutineSchedulerHasShutdown;
};
