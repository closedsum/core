// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

	// CoroutineTransaction
#pragma region

UENUM(BlueprintType)
enum class ECsCoroutineTransaction : uint8
{
	Allocate					UMETA(DisplayName = "Allocate"),
	Start						UMETA(DisplayName = "Start"),
	End							UMETA(DisplayName = "End"),
	ECsCoroutineTransaction_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsCoroutineTransaction : public TCsEnumMap<ECsCoroutineTransaction>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsCoroutineTransaction)
};

namespace NCsCoroutineTransaction
{
	typedef ECsCoroutineTransaction Type;

	namespace Ref
	{
		extern CSCORE_API const Type Allocate;
		extern CSCORE_API const Type Start;
		extern CSCORE_API const Type End;
		extern CSCORE_API const Type ECsCoroutineTransaction_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	namespace Str
	{
		typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

		extern CSCORE_API const TCsString Allocate;
		extern CSCORE_API const TCsString Start;
		extern CSCORE_API const TCsString End;
	}

	FORCEINLINE const FString& ToString(const Type& EType)
	{
		if (EType == Type::Allocate) { return Str::Allocate.Value; }
		if (EType == Type::Start) { return Str::Start.Value; }
		if (EType == Type::End) { return Str::End.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const FString& ToActionString(const Type& EType)
	{
		if (EType == Type::Allocate) { return Str::Allocate.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Start) { return Str::Start.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::End) { return Str::End.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString& String)
	{
		if (String == Str::Allocate) { return Ref::Allocate; }
		if (String == Str::Start) { return Ref::Start; }
		if (String == Str::End) { return Ref::End; }
		return Ref::ECsCoroutineTransaction_MAX;
	}
}

#define ECS_COROUTINE_TRANSACTION_MAX (uint8)NCsCoroutineTransaction::MAX

#pragma endregion CoroutineTransaction

#pragma endregion Enums

namespace NCsCoroutineCached
{
	namespace Str
	{
		extern const FString Allocate;// = TEXT("UCsCoroutineScheduler::Allocate");
		extern const FString Start;// = TEXT("UCsCoroutineScheduler::Start");
		extern const FString Update;// = TEXT("UCsCoroutineScheduler::Update");
		extern const FString OnTick_Update;// = TEXT("UCsCoroutineScheduler::OnTick_Update");
		extern const FString OnCacCamera_Update;//= TEXT("UCsCoroutineScheduler::OnCacCamera_Update");
		extern const FString OnLastTick_Update;// = TEXT("UCsCoroutineScheduler::OnLastTick_Update");
	}

	FORCEINLINE FString ToUpdate(const ECsCoroutineSchedule &ScheduleType)
	{
		if (ScheduleType == ECsCoroutineSchedule::Tick) { return Str::OnTick_Update; }
		if (ScheduleType == ECsCoroutineSchedule::CalcCamera) { return Str::OnCacCamera_Update; }
		if (ScheduleType == ECsCoroutineSchedule::LastTick) { return Str::OnLastTick_Update; }
		return Str::Update;
	}
}

// Structs
#pragma region

struct FCsCoroutinePayload
{
	bool IsAllocated;

	ECsCoroutineSchedule Schedule;

	FCsRoutine* Parent;
	CsCoroutine Function;
	AActor* Actor;
	UObject* Object;
	FCsRoutine** Routine;
	FCsRoutine::FCoroutineStopCondition Stop;
	CsAddRoutine Add;
	CsRemoveRoutine Remove;
	uint8 Type;
	bool DoInit;
	bool PerformFirstRun;

	FName Name;
	FString NameAsString;

	FCsCoroutinePayload()
	{
		Reset();
	}
	~FCsCoroutinePayload(){}

	void Reset()
	{
		IsAllocated = false;

		Schedule = ECsCoroutineSchedule::ECsCoroutineSchedule_MAX;
		Function = nullptr;
		Actor = nullptr;
		Object = nullptr;
		Routine = nullptr;
		Stop.Clear();
		Add = nullptr;
		Remove = nullptr;
		Type = CS_ROUTINE_MAX_TYPE;
		DoInit = true;
		PerformFirstRun = false;
		Name = NAME_None;
		NameAsString = NCsCached::Str::Empty;
	}
};

#pragma endregion Structs

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

	struct FCsRoutine* Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, AActor* InActor, const bool& DoInit = true, const bool& PerformFirstRun = false);
	struct FCsRoutine* Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, const bool& DoInit = true, const bool& PerformFirstRun = false);
	struct FCsRoutine* Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine = nullptr, const bool& DoInit = true, const bool& PerformFirstRun = false);
	struct FCsRoutine* Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8& RoutineType = CS_ROUTINE_MAX_TYPE, const bool& DoInit = true, const bool& PerformFirstRun = false);
	struct FCsRoutine* Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, UObject* InObject, const bool &DoInit = true, const bool &PerformFirstRun = false);
	struct FCsRoutine* Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, const bool& DoInit = true, const bool& PerformFirstRun = false);
	struct FCsRoutine* Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr, const bool& DoInit = true, const bool& PerformFirstRun = false);
	struct FCsRoutine* Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8& RoutineType = CS_ROUTINE_MAX_TYPE, const bool& DoInit = true, const bool& PerformFirstRun = false);
	struct FCsRoutine* Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject, const bool& DoInit = true, const bool& PerformFirstRun = false);
	struct FCsRoutine* Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, const bool& DoInit = true, const bool& PerformFirstRun = false);
	struct FCsRoutine* Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr, const bool& DoInit = true, const bool& PerformFirstRun = false);
	struct FCsRoutine* Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8& RoutineType = CS_ROUTINE_MAX_TYPE, const bool& DoInit = true, const bool& PerformFirstRun = false);
	struct FCsRoutine* Allocate(FCsCoroutinePayload* Payload);

	struct FCsRoutine* Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, AActor* InActor);
	struct FCsRoutine* Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor);
	struct FCsRoutine* Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8& RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, UObject* InObject);
	struct FCsRoutine* Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject);
	struct FCsRoutine* Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8& RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject);
	struct FCsRoutine* Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject);
	struct FCsRoutine* Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8& RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* Start(FCsCoroutinePayload* Payload);

	struct FCsRoutine* StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor);
	struct FCsRoutine* StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor);
	struct FCsRoutine* StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8& RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, UObject* InObject);
	struct FCsRoutine* StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject);
	struct FCsRoutine* StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8& RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject);
	struct FCsRoutine* StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject);
	struct FCsRoutine* StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine = nullptr);
	struct FCsRoutine* StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine = nullptr, CsRemoveRoutine InRemoveRoutine = nullptr, const uint8& RoutineType = CS_ROUTINE_MAX_TYPE);
	struct FCsRoutine* StartChild(FCsCoroutinePayload* Payload);

	struct FCsRoutine* StartRoutine(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* R);

	void EndAll(const ECsCoroutineSchedule& ScheduleType = ECsCoroutineSchedule::ECsCoroutineSchedule_MAX);

	void BroadcastMessage(const ECsCoroutineSchedule& ScheduleType, const TCsCoroutineMessage& MessageType, const FName& Message, UObject* InOwner);
	void BroadcastMessage(const ECsCoroutineSchedule& ScheduleType, const TCsCoroutineMessage& MessageType, const FName& Message);

	void Update(const ECsCoroutineSchedule& ScheduleType, const float& DeltaSeconds);

// Run on Tick
#pragma region 
public:

	void OnTick_Update(const float& DeltaSeconds);

	UPROPERTY(BlueprintAssignable, Category = "CoroutineScheduler")
	FBindableEvent_CsCoroutineScheduler_OnTickUpdate OnTickUpdate_Event;

#pragma endregion Run on Tick

// Run on CalcCamera
#pragma region

	void OnCalcCamera_Update(const float& DeltaSeconds);

#pragma endregion Run on CalcCamera

// Run on LastTick
#pragma region

	void OnLastTick_Update(const float& DeltaSeconds);

#pragma endregion Run on LastTick

	void LogTransaction(const FString& FunctionName, const ECsCoroutineTransaction& Transaction, struct FCsRoutine* R);
	void LogRunning(const ECsCoroutineSchedule& ScheduleType);

// Payload
#pragma region

	FCsCoroutinePayload Payloads[CS_ROUTINE_POOL_SIZE];

	uint16 PayloadIndex;

	FCsCoroutinePayload* AllocatePayload();

#pragma endregion Payload

private:
	// Singleton data
	static UCsCoroutineScheduler* s_coroutineSchedulerSingleton;
	static bool s_bCoroutineSchedulerHasShutdown;
};
