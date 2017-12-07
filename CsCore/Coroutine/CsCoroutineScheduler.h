// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Common/CsCommon.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsCoroutineScheduler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsCoroutineScheduler_OnTick, const float&, DeltaSeconds);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsCoroutineScheduler_OnTick, const float&);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsCoroutineScheduler_OnTickUpdate, float, DeltaSeconds);

// Enums
#pragma region

UENUM(BlueprintType)
namespace ECsCoroutineTransaction
{
	enum Type
	{
		Allocate					UMETA(DisplayName = "Allocate"),
		Start						UMETA(DisplayName = "Start"),
		End							UMETA(DisplayName = "End"),
		ECsCoroutineTransaction_MAX	UMETA(Hidden),
	};
}

namespace ECsCoroutineTransaction
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Allocate = TCsString(TEXT("Allocate"), TEXT("allocate"), TEXT("Allocating"));
		const TCsString Start = TCsString(TEXT("Start"), TEXT("start"), TEXT("Starting"));
		const TCsString End = TCsString(TEXT("End"), TEXT("end"), TEXT("Ending"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Allocate) { return Str::Allocate.Value; }
		if (EType == Type::Start) { return Str::Start.Value; }
		if (EType == Type::End) { return Str::End.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToActionString(const Type &EType)
	{
		if (EType == Type::Allocate) { return Str::Allocate.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Start) { return Str::Start.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::End) { return Str::End.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Allocate) { return Type::Allocate; }
		if (String == Str::Start) { return Type::Start; }
		if (String == Str::End) { return Type::End; }
		return Type::ECsCoroutineTransaction_MAX;
	}
}

#define ECS_COROUTINE_TRANSACTION_MAX (uint8)ECsCoroutineTransaction::ECsCoroutineTransaction_MAX
typedef TEnumAsByte<ECsCoroutineTransaction::Type> TCsCoroutineTransaction;

#pragma endregion Enums

namespace ECsCoroutineCachedString
{
	namespace Str
	{
		const FString Allocate = TEXT("UCsCoroutineScheduler::Allocate");
		const FString Start = TEXT("UCsCoroutineScheduler::Start");
		const FString Update = TEXT("UCsCoroutineScheduler::Update");
		const FString OnTick_Update = TEXT("UCsCoroutineScheduler::OnTick_Update");
		const FString OnCacCamera_Update = TEXT("UCsCoroutineScheduler::OnCacCamera_Update");
		const FString OnLastTick_Update = TEXT("UCsCoroutineScheduler::OnLastTick_Update");
	}

	FORCEINLINE FString ToUpdate(const TCsCoroutineSchedule &ScheduleType)
	{
		if (ScheduleType == ECsCoroutineSchedule::Tick) { return Str::OnTick_Update; }
		if (ScheduleType == ECsCoroutineSchedule::CalcCamera) { return Str::OnCacCamera_Update; }
		if (ScheduleType == ECsCoroutineSchedule::LastTick) { return Str::OnLastTick_Update; }
		return Str::Update;
	}
}

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

	struct FCsRoutine RoutinePools[ECS_COROUTINE_SCHEDULE_MAX][CS_ROUTINE_POOL_SIZE];
	TArray<int32> RoutinePoolIndices;
	TArray<TArray<struct FCsRoutine*>> RoutinesToInit;
	TArray<TArray<struct FCsRoutine*>> RoutinesToRun;

	struct FCsRoutine* Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, AActor* InActor, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine = nullptr, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, UObject* InObject, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE, const bool &DoInit = true, const bool &PerformFirstRun = false);

	struct FCsRoutine* Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, AActor* InActor);
	struct FCsRoutine* Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor);
	struct FCsRoutine* Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, UObject* InObject);
	struct FCsRoutine* Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject);
	struct FCsRoutine* Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject);
	struct FCsRoutine* Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject);
	struct FCsRoutine* Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);

	struct FCsRoutine* StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor);
	struct FCsRoutine* StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor);
	struct FCsRoutine* StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, UObject* InObject);
	struct FCsRoutine* StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject);
	struct FCsRoutine* StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject);
	struct FCsRoutine* StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject);
	struct FCsRoutine* StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8 &RoutineType = CS_ROUTINE_MAX_TYPE);

	struct FCsRoutine* StartRoutine(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* R);

	void EndAll(const TCsCoroutineSchedule &ScheduleType = ECsCoroutineSchedule::ECsCoroutineSchedule_MAX);

	void BroadcastMessage(const TCsCoroutineSchedule &ScheduleType, const TCsCoroutineMessage &MessageType, const FName &Message, UObject* InOwner);
	void BroadcastMessage(const TCsCoroutineSchedule &ScheduleType, const TCsCoroutineMessage &MessageType, const FName &Message);

	void Update(const TCsCoroutineSchedule &ScheduleType, const float &DeltaSeconds);

// Run on Tick
#pragma region 
public:

	void OnTick_Update(const float &DeltaSeconds);

	UPROPERTY(BlueprintAssignable, Category = "0 CoroutineScheduler")
	FBindableEvent_CsCoroutineScheduler_OnTickUpdate OnTickUpdate_Event;

#pragma endregion Run on Tick

// Run on CalcCamera
#pragma region

	void OnCalcCamera_Update(const float &DeltaSeconds);

#pragma endregion Run on CalcCamera

// Run on LastTick
#pragma region

	void OnLastTick_Update(const float &DeltaSeconds);

#pragma endregion Run on LastTick

	void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsCoroutineTransaction::Type> &Transaction, struct FCsRoutine* R);
	void LogRunning(const TCsCoroutineSchedule &ScheduleType);

private:
	// Singleton data
	static UCsCoroutineScheduler* s_coroutineSchedulerSingleton;
	static bool s_bCoroutineSchedulerHasShutdown;
};
