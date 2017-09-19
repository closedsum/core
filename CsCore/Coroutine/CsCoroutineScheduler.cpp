// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsCoroutineScheduler.h"
#include "CsCore.h"
#include "Game/CsGameState.h"

// static initializations
UCsCoroutineScheduler* UCsCoroutineScheduler::s_coroutineSchedulerSingleton;
bool UCsCoroutineScheduler::s_bCoroutineSchedulerHasShutdown = false;

UCsCoroutineScheduler::UCsCoroutineScheduler(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	for (int32 I = 0; I < ECS_COROUTINE_SCHEDULE_MAX; I++)
	{
		RoutinePoolIndices.Add(0);
		RoutinesToInit.AddDefaulted();
		RoutinesToRun.AddDefaulted();

		for (int32 J = 0; J < CS_ROUTINE_POOL_SIZE; J++)
		{
			RoutinePools[I][J].Init(this, J);
		}
	}
}

/*static*/ UCsCoroutineScheduler* UCsCoroutineScheduler::Get()
{
	if (s_bCoroutineSchedulerHasShutdown)
		return nullptr;

	if (!s_coroutineSchedulerSingleton)
	{
		s_coroutineSchedulerSingleton = NewObject<UCsCoroutineScheduler>(GetTransientPackage(), UCsCoroutineScheduler::StaticClass(), TEXT("Coroutine_Scheduler_Singleton"), RF_Transient | RF_Public);
		s_coroutineSchedulerSingleton->AddToRoot();
		s_coroutineSchedulerSingleton->Initialize();
	}

	return s_coroutineSchedulerSingleton;
}

/*static*/ void UCsCoroutineScheduler::Init()
{
	s_bCoroutineSchedulerHasShutdown = false;
	UCsCoroutineScheduler::Get();
}

/*static*/ void UCsCoroutineScheduler::Shutdown()
{
	if (!s_coroutineSchedulerSingleton)
		return;

	s_coroutineSchedulerSingleton->CleanUp();
	s_coroutineSchedulerSingleton->RemoveFromRoot();
	s_coroutineSchedulerSingleton = nullptr;
	s_bCoroutineSchedulerHasShutdown = true;
}

void UCsCoroutineScheduler::Initialize()
{
	// Register delegate for ticker callback
	TickDelegate	   = FTickerDelegate::CreateUObject(this, &UCsCoroutineScheduler::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);
}

void UCsCoroutineScheduler::CleanUp()
{
	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
}

bool UCsCoroutineScheduler::Tick(float DeltaSeconds)
{
	return true;
}

UObject* UCsCoroutineScheduler::GetMyOwner()
{
	return MyOwner.IsValid() ? MyOwner.Get() : nullptr;
}

// Allocate
#pragma region

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, AActor* InActor, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, nullptr, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, InActor, nullptr, InOwnerMemberRoutine, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, InActor, nullptr, InAddRoutine, InRemoveRoutine, RoutineType, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, UObject* InObject, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, nullptr, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, nullptr, InObject, InOwnerMemberRoutine, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, nullptr, InObject, InAddRoutine, InRemoveRoutine, RoutineType, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine, const bool &DoInit, const bool &PerformFirstRun)
{
	const uint8 Schedule = (uint8)ScheduleType;

	for (int32 Index = 0; Index < CS_ROUTINE_POOL_SIZE; Index++)
	{
		RoutinePoolIndices[Schedule] = (RoutinePoolIndices[Schedule] + 1) % CS_ROUTINE_POOL_SIZE;

		FCsRoutine* R = &(RoutinePools[Schedule][Index]);

		if (R->index == CS_ROUTINE_FREE)
		{
			UWorld* World = nullptr;

			if (InActor)
				World = InActor->GetWorld();
			if (InObject)
				World = InObject->GetWorld();

			const float CurrentTime = World ? World->GetTimeSeconds() : UCsCommon::GetCurrentDateTimeSeconds();

			R->Start(InCoroutine, InStopCondition, InActor, InObject, CurrentTime, InOwnerMemberRoutine);

			if (DoInit)
			{
				CS_COROUTINE_INIT(R);
				R->index = RoutinesToRun[Schedule].Num();
				RoutinesToRun[Schedule].Add(R);

				if (PerformFirstRun)
				{
					R->Run(0.0f);
				}
			}
			else
			{
				RoutinesToInit[Schedule].Add(R);
			}
			return R;
		}
	}
	UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::Allocate: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
	return nullptr;
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType, const bool &DoInit, const bool &PerformFirstRun)
{
	const uint8 Schedule = (uint8)ScheduleType;

	for (int32 Index = 0; Index < CS_ROUTINE_POOL_SIZE; Index++)
	{
		RoutinePoolIndices[Schedule] = (RoutinePoolIndices[Schedule] + 1) % CS_ROUTINE_POOL_SIZE;

		FCsRoutine* R = &(RoutinePools[Schedule][Index]);

		if (R->index == CS_ROUTINE_FREE)
		{
			UWorld* World = nullptr;

			if (InActor)
				World = InActor->GetWorld();
			if (InObject)
				World = InObject->GetWorld();

			const float CurrentTime = World ? World->GetTimeSeconds() : UCsCommon::GetCurrentDateTimeSeconds();

			R->Start(InCoroutine, InStopCondition, InActor, InObject, CurrentTime, InAddRoutine, InRemoveRoutine, RoutineType);

			if (DoInit)
			{
				CS_COROUTINE_INIT(R);
				R->index = RoutinesToRun[Schedule].Num();
				RoutinesToRun[Schedule].Add(R);

				if (PerformFirstRun)
				{
					R->Run(0.0f);
				}
			}
			else
			{
				RoutinesToInit[Schedule].Add(R);
			}
			return R;
		}
	}
	UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::Allocate: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
	return nullptr;
}

#pragma endregion Allocate

// Start
#pragma region

struct FCsRoutine* UCsCoroutineScheduler::Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, AActor* InActor)
{
	return Allocate(ScheduleType, InCoroutine, nullptr, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, InActor, nullptr, InOwnerMemberRoutine, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, InActor, nullptr, InAddRoutine, InRemoveRoutine, RoutineType, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, UObject* InObject)
{
	return Allocate(ScheduleType, InCoroutine, nullptr, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, nullptr, InObject, InOwnerMemberRoutine, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, nullptr, InObject, InAddRoutine, InRemoveRoutine, RoutineType, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject)
{
	return Allocate(ScheduleType, InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const TCsCoroutineSchedule &ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

#pragma endregion // Start

// StartChild
#pragma region

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor)
{
	return StartChild(ScheduleType, Parent, InCoroutine, nullptr, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor)
{
	return StartChild(ScheduleType, Parent, InCoroutine, InStopCondition, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine)
{
	return StartChild(ScheduleType, Parent, InCoroutine, InStopCondition, InActor, nullptr, InOwnerMemberRoutine);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType)
{
	return StartChild(ScheduleType, Parent, InCoroutine, InStopCondition, InActor, nullptr, InAddRoutine, InRemoveRoutine, RoutineType);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, UObject* InObject)
{
	return StartChild(ScheduleType, Parent, InCoroutine, nullptr, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject)
{
	return StartChild(ScheduleType, Parent, InCoroutine, InStopCondition, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine)
{
	return StartChild(ScheduleType, Parent, InCoroutine, InStopCondition, nullptr, InObject, InOwnerMemberRoutine);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType)
{
	return StartChild(ScheduleType, Parent, InCoroutine, InStopCondition, nullptr, InObject, InAddRoutine, InRemoveRoutine, RoutineType);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject)
{
	return StartChild(ScheduleType, Parent, InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject)
{
	return StartChild(ScheduleType, Parent, InCoroutine, InStopCondition, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine)
{
	const uint8 Schedule = (uint8)ScheduleType;

	for (int32 Index = 0; Index < CS_ROUTINE_POOL_SIZE; Index++)
	{
		RoutinePoolIndices[Schedule] = (RoutinePoolIndices[Schedule] + 1) % CS_ROUTINE_POOL_SIZE;

		FCsRoutine* R = &(RoutinePools[Schedule][Index]);

		if (R->index == CS_ROUTINE_FREE)
		{
			UWorld* World = nullptr;

			if (InActor)
				World = InActor->GetWorld();
			if (InObject)
				World = InObject->GetWorld();

			const float CurrentTime = World ? World->GetTimeSeconds() : UCsCommon::GetCurrentDateTimeSeconds();

			Parent->AddChild(R);
			R->Start(InCoroutine, InStopCondition, InActor, InObject, CurrentTime, InOwnerMemberRoutine);

			CS_COROUTINE_INIT(R);

			bool InsertedAtLastChild = Parent->children.Num() > 0 && Parent->children.Last() && Parent->children.Last() != R;
			FCsRoutine* Element		 = InsertedAtLastChild ? Parent->children.Last() : Parent;
			R->index				 = RoutinesToRun[Schedule].Find(Element);
			RoutinesToRun[Schedule].Insert(R, R->index);

			const int32 ParentIndex = Parent->index;

			for (int32 J = R->index + 1; J <= ParentIndex; J++)
			{
				R->index++;
			}

			R->Run(0.0f);
			return R;
		}
	}
	UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::StartChild: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
	return nullptr;
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType)
{
	const uint8 Schedule = (uint8)ScheduleType;

	for (int32 Index = 0; Index < CS_ROUTINE_POOL_SIZE; Index++)
	{
		RoutinePoolIndices[Schedule] = (RoutinePoolIndices[Schedule] + 1) % CS_ROUTINE_POOL_SIZE;

		FCsRoutine* R = &(RoutinePools[Schedule][Index]);

		if (R->index == CS_ROUTINE_FREE)
		{
			UWorld* World = nullptr;

			if (InActor)
				World = InActor->GetWorld();
			if (InObject)
				World = InObject->GetWorld();

			const float CurrentTime = World ? World->GetTimeSeconds() : UCsCommon::GetCurrentDateTimeSeconds();

			Parent->AddChild(R);
			R->Start(InCoroutine, InStopCondition, InActor, InObject, CurrentTime, InAddRoutine, InRemoveRoutine, RoutineType);

			CS_COROUTINE_INIT(R);

			bool InsertedAtLastChild = Parent->children.Num() > 0 && Parent->children.Last() && Parent->children.Last() != R;
			FCsRoutine* Element		 = InsertedAtLastChild ? Parent->children.Last() : Parent;
			R->index				 = RoutinesToRun[Schedule].Find(Element);
			RoutinesToRun[Schedule].Insert(R, R->index);

			const int32 ParentIndex = Parent->index;

			for (int32 J = R->index + 1; J <= ParentIndex; J++)
			{
				R->index++;
			}
			
			R->Run(0.0f);
			return R;
		}
	}
	UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::StartChild: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
	return nullptr;
}

#pragma endregion // StartChild

struct FCsRoutine* UCsCoroutineScheduler::StartRoutine(const TCsCoroutineSchedule &ScheduleType, struct FCsRoutine* R)
{
	const uint8 Schedule = (uint8)ScheduleType;

	// TODO: This should never happen. If it does, need to trace how and fix it.
	// HACK: Index should never be greater than the RoutinesToRun Count.
	if (R->index < 0 ||
		R->index >= RoutinesToRun[Schedule].Num())
	{
		FString State = R->index == CS_ROUTINE_END ? TEXT("END") : TEXT("FREE");

		UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::StartRoutine: Attempting to start a Routine marked %s"), *State);

		// Check if the Routine is in the list of RoutinesToExecute
		const int32 Count = RoutinesToRun[Schedule].Num();

		for (int32 Index = Count - 1; Index >= 0; Index--)
		{
			if (R == RoutinesToRun[Schedule][Index])
			{
				RoutinesToRun[Schedule].RemoveAt(Index);

				UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::StartRoutine: Removing Routine marked %s at index %d in RoutinesToExecute"), *State, Index);
				break;
			}
		}
		check(0);
		R->Reset();
		return R;
	}
	RoutinesToRun[Schedule][R->index]->Run(0.0f);
	return R;
}

void UCsCoroutineScheduler::EndAll(const TCsCoroutineSchedule &ScheduleType /*= ECsCoroutineSchedule::ECsCoroutineSchedule_MAX*/)
{
	const uint8 Start = ScheduleType == ECsCoroutineSchedule::ECsCoroutineSchedule_MAX ? 0 : (uint8)ScheduleType;
	const uint8 End   = ScheduleType == ECsCoroutineSchedule::ECsCoroutineSchedule_MAX ? ECS_COROUTINE_SCHEDULE_MAX : Start + 1;

	for (int32 I = Start; I < End; I++)
	{
		int32 Count = RoutinesToInit[I].Num();

		for (int32 Index = 0; Index < Count; Index++)
		{
			FCsRoutine* R = RoutinesToInit[I][Index];

			R->End();
			R->Reset();
		}

		RoutinesToInit[I].Reset();

		Count = RoutinesToRun[I].Num();

		for (int32 Index = 0; Index < Count; Index++)
		{
			FCsRoutine* R = RoutinesToRun[I][Index];

			R->End();
			R->Reset();
		}
		RoutinesToRun[I].Reset();
	}
}

void UCsCoroutineScheduler::BroadcastMessage(const TCsCoroutineSchedule &ScheduleType, const TCsCoroutineMessage &MessageType, const FName &Message, UObject* InOwner)
{
	const uint8 Schedule = (uint8)ScheduleType;

	int32 Count = RoutinesToInit[Schedule].Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (InOwner && InOwner != RoutinesToInit[Schedule][I]->GetOwner())
			continue;

		if (MessageType == ECsCoroutineMessage::Stop)
			RoutinesToInit[Schedule][I]->ReceiveMessage(MessageType, Message);
	}

	Count = RoutinesToRun[Schedule].Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (InOwner && InOwner != RoutinesToRun[Schedule][I]->GetOwner())
			continue;

		if (MessageType == ECsCoroutineMessage::Stop)
			RoutinesToRun[Schedule][I]->ReceiveMessage(MessageType, Message);
	}
}

void UCsCoroutineScheduler::BroadcastMessage(const TCsCoroutineSchedule &ScheduleType, const TCsCoroutineMessage &MessageType, const FName &Message)
{
	BroadcastMessage(ScheduleType, MessageType, Message, nullptr);
}

void UCsCoroutineScheduler::Update(const TCsCoroutineSchedule &ScheduleType, const float &DeltaSeconds)
{
	const uint8 Schedule = (uint8)ScheduleType;

	// Init
	int32 Count = RoutinesToInit[Schedule].Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		FCsRoutine* R = RoutinesToInit[Schedule][Index];

		CS_COROUTINE_INIT(R);
		R->index = RoutinesToRun[Schedule].Num();
		RoutinesToRun[Schedule].Add(R);
	}

	RoutinesToInit[Schedule].Reset();

	// Remove any Routines executed previous to tick
	Count = RoutinesToRun[Schedule].Num();

	for (int32 Index = Count - 1; Index >= 0; Index--)
	{
		FCsRoutine* R = RoutinesToRun[Schedule][Index];

		if (R->index == CS_ROUTINE_END)
		{
			R->Reset();
			RoutinesToRun[Schedule].RemoveAt(Index);
		}
	}
	// Execute
	Count = RoutinesToRun[Schedule].Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		RoutinesToRun[Schedule][Index]->Run(DeltaSeconds);
	}
	// Remove any Routines executed end of tick
	for (int32 Index = Count - 1; Index >= 0; Index--)
	{
		FCsRoutine* R = RoutinesToRun[Schedule][Index];

		if (R->index == CS_ROUTINE_END)
		{
			R->Reset();
			RoutinesToRun[Schedule].RemoveAt(Index);
		}
	}
}

// Run on Tick
#pragma region 

void UCsCoroutineScheduler::OnTick_Update(const float &DeltaSeconds)
{
	Update(ECsCoroutineSchedule::Tick, DeltaSeconds);
	OnTickUpdate_Event.Broadcast(DeltaSeconds);
}

#pragma endregion Run on Tick

// Run on CalcCamera
#pragma region

void UCsCoroutineScheduler::OnCalcCamera_Update(const float &DeltaSeconds)
{
	Update(ECsCoroutineSchedule::CalcCamera, DeltaSeconds);
}

#pragma endregion Run on CalcCamera

// Run on LastTick
#pragma region

void UCsCoroutineScheduler::OnLastTick_Update(const float &DeltaSeconds)
{
	Update(ECsCoroutineSchedule::LastTick, DeltaSeconds);
}

#pragma endregion Run on LastTick