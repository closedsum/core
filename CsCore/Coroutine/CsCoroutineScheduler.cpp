// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsCoroutineScheduler.h"
#include "CsCore.h"
#include "Game/CsGameState.h"

// static initializations
UCsCoroutineScheduler* UCsCoroutineScheduler::s_coroutineSchedulerSingleton;
bool UCsCoroutineScheduler::s_bCoroutineSchedulerHasShutdown = false;

UCsCoroutineScheduler::UCsCoroutineScheduler(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	for (int32 Index = 0; Index < CS_ROUTINE_POOL_SIZE; Index++)
	{
		RoutinePool[Index].Init(&RoutinePool[Index], this, Index);
	}

	for (int32 Index = 0; Index < CS_ROUTINE_POOL_SIZE; Index++)
	{
		CalcCamera_RoutinePool[Index].Init(&CalcCamera_RoutinePool[Index], this, Index);
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
}

void UCsCoroutineScheduler::CleanUp()
{
}

UObject* UCsCoroutineScheduler::GetMyOwner()
{
	return MyOwner.IsValid() ? MyOwner.Get() : nullptr;
}

// Run on Tick
#pragma region 

	// Allocate
#pragma region

struct FCsRoutine* UCsCoroutineScheduler::Allocate(CsCoroutine InCoroutine, AActor* InActor, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(InCoroutine, nullptr, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(InCoroutine, InStopCondition, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(InCoroutine, InStopCondition, InActor, nullptr, InOwnerMemberRoutine, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(InCoroutine, InStopCondition, InActor, nullptr, InAddRoutine, InRemoveRoutine, RoutineType, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(CsCoroutine InCoroutine, UObject* InObject, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(InCoroutine, nullptr, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(InCoroutine, InStopCondition, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(InCoroutine, InStopCondition, nullptr, InObject, InOwnerMemberRoutine, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(InCoroutine, InStopCondition, nullptr, InObject, InAddRoutine, InRemoveRoutine, RoutineType, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(CsCoroutine InCoroutine, AActor* InActor, UObject* InObject, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, const bool &DoInit, const bool &PerformFirstRun)
{
	return Allocate(InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine, const bool &DoInit, const bool &PerformFirstRun)
{
	for (int32 Index = 0; Index < CS_ROUTINE_POOL_SIZE; Index++)
	{
		RoutinePoolIndex = (RoutinePoolIndex + 1) % CS_ROUTINE_POOL_SIZE;

		FCsRoutine* R = &RoutinePool[Index];

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
				R->index = RoutinesToRun.Num();
				RoutinesToRun.Add(R);

				if (PerformFirstRun)
				{
					R->Run(0.0f);
				}
			}
			else
			{
				RoutinesToInit.Add(R);
			}
			return R;
		}
	}
	UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::Allocate: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
	return nullptr;
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType, const bool &DoInit, const bool &PerformFirstRun)
{
	for (int32 Index = 0; Index < CS_ROUTINE_POOL_SIZE; Index++)
	{
		RoutinePoolIndex = (RoutinePoolIndex + 1) % CS_ROUTINE_POOL_SIZE;

		FCsRoutine* R = &RoutinePool[Index];

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
				R->index = RoutinesToRun.Num();
				RoutinesToRun.Add(R);

				if (PerformFirstRun)
				{
					R->Run(0.0f);
				}
			}
			else
			{
				RoutinesToInit.Add(R);
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

struct FCsRoutine* UCsCoroutineScheduler::Start(CsCoroutine InCoroutine, AActor* InActor)
{
	return Allocate(InCoroutine, nullptr, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor)
{
	return Allocate(InCoroutine, InStopCondition, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine)
{
	return Allocate(InCoroutine, InStopCondition, InActor, nullptr, InOwnerMemberRoutine, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType)
{
	return Allocate(InCoroutine, InStopCondition, InActor, nullptr, InAddRoutine, InRemoveRoutine, RoutineType, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(CsCoroutine InCoroutine, UObject* InObject)
{
	return Allocate(InCoroutine, nullptr, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject)
{
	return Allocate(InCoroutine, InStopCondition, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine)
{
	return Allocate(InCoroutine, InStopCondition, nullptr, InObject, InOwnerMemberRoutine, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType)
{
	return Allocate(InCoroutine, InStopCondition, nullptr, InObject, InAddRoutine, InRemoveRoutine, RoutineType, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(CsCoroutine InCoroutine, AActor* InActor, UObject* InObject)
{
	return Allocate(InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject)
{
	return Allocate(InCoroutine, InStopCondition, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

#pragma endregion // Start

	// StartChild
#pragma region

struct FCsRoutine* UCsCoroutineScheduler::StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor)
{
	return StartChild(Parent, InCoroutine, nullptr, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor)
{
	return StartChild(Parent, InCoroutine, InStopCondition, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine)
{
	return StartChild(Parent, InCoroutine, InStopCondition, InActor, nullptr, InOwnerMemberRoutine);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType)
{
	return StartChild(Parent, InCoroutine, InStopCondition, InActor, nullptr, InAddRoutine, InRemoveRoutine, RoutineType);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, UObject* InObject)
{
	return StartChild(Parent, InCoroutine, nullptr, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject)
{
	return StartChild(Parent, InCoroutine, InStopCondition, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine)
{
	return StartChild(Parent, InCoroutine, InStopCondition, nullptr, InObject, InOwnerMemberRoutine);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType)
{
	return StartChild(Parent, InCoroutine, InStopCondition, nullptr, InObject, InAddRoutine, InRemoveRoutine, RoutineType);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject)
{
	return StartChild(Parent, InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject)
{
	return StartChild(Parent, InCoroutine, InStopCondition, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine)
{
	for (int32 Index = 0; Index < CS_ROUTINE_POOL_SIZE; Index++)
	{
		RoutinePoolIndex = (RoutinePoolIndex + 1) % CS_ROUTINE_POOL_SIZE;

		FCsRoutine* R = &RoutinePool[Index];

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
			R->index				 = RoutinesToRun.Find(Element);
			RoutinesToRun.Insert(R, R->index);

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

struct FCsRoutine* UCsCoroutineScheduler::StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType)
{
	for (int32 Index = 0; Index < CS_ROUTINE_POOL_SIZE; Index++)
	{
		RoutinePoolIndex = (RoutinePoolIndex + 1) % CS_ROUTINE_POOL_SIZE;

		FCsRoutine* R = &RoutinePool[Index];

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
			R->index				 = RoutinesToRun.Find(Element);
			RoutinesToRun.Insert(R, R->index);

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

struct FCsRoutine* UCsCoroutineScheduler::StartRoutine(struct FCsRoutine* R)
{
	// TODO: This should never happen. If it does, need to trace how and fix it.
	// HACK: Index should never be greater than the RoutinesToRun Count.
	if (R->index < 0 ||
		R->index >= RoutinesToRun.Num())
	{
		FString State = R->index == CS_ROUTINE_END ? TEXT("END") : TEXT("FREE");

		UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::StartRoutine: Attempting to start a Routine marked %s"), *State);

		// Check if the Routine is in the list of RoutinesToExecute
		const int32 Count = RoutinesToRun.Num();

		for (int32 Index = Count - 1; Index >= 0; Index--)
		{
			if (R == RoutinesToRun[Index])
			{
				RoutinesToRun.RemoveAt(Index);

				UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::StartRoutine: Removing Routine marked %s at index %d in RoutinesToExecute"), *State, Index);
				break;
			}
		}
		check(0);
		R->Reset();
		return R;
	}
	RoutinesToRun[R->index]->Run(0.0f);
	return R;
}

void UCsCoroutineScheduler::OnTick_Update(const float &DeltaSeconds)
{
	// Init
	int32 Count = RoutinesToInit.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		FCsRoutine* R = RoutinesToInit[Index];

		CS_COROUTINE_INIT(R);
		R->index = RoutinesToRun.Num();
		RoutinesToRun.Add(R);
	}

	RoutinesToInit.Reset();

	// Remove any Routines executed previous to tick
	Count = RoutinesToRun.Num();

	for (int32 Index = Count - 1; Index >= 0; Index--)
	{
		FCsRoutine* R = RoutinesToRun[Index];

		if (R->index == CS_ROUTINE_END)
		{
			R->Reset();
			RoutinesToRun.RemoveAt(Index);
		}
	}
	// Execute
	Count = RoutinesToRun.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		RoutinesToRun[Index]->Run(DeltaSeconds);
	}
	// Remove any Routines executed end of tick
	for (int32 Index = Count - 1; Index >= 0; Index--)
	{
		FCsRoutine* R = RoutinesToRun[Index];

		if (R->index == CS_ROUTINE_END)
		{
			R->Reset();
			RoutinesToRun.RemoveAt(Index);
		}
	}
	OnTickUpdate_Event.Broadcast(DeltaSeconds);
}

void UCsCoroutineScheduler::EndAll()
{
	int32 Count = RoutinesToInit.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		FCsRoutine* R = RoutinesToInit[Index];

		R->End();
		R->Reset();
	}

	RoutinesToInit.Reset();

	Count = RoutinesToRun.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		FCsRoutine* R = RoutinesToRun[Index];

		R->End();
		R->Reset();
	}
	RoutinesToRun.Reset();
}

void UCsCoroutineScheduler::BroadcastMessage(const TCsCoroutineMessage &MessageType, const FName &Message, UObject* InOwner)
{
	int32 Count = RoutinesToInit.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (InOwner && InOwner != RoutinesToInit[I]->GetOwner())
			continue;

		if (MessageType == ECsCoroutineMessage::Stop)
			RoutinesToInit[I]->ReceiveMessage(MessageType, Message);
	}

	Count = RoutinesToRun.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (InOwner && InOwner != RoutinesToRun[I]->GetOwner())
			continue;

		if (MessageType == ECsCoroutineMessage::Stop)
			RoutinesToRun[I]->ReceiveMessage(MessageType, Message);
	}
}

void UCsCoroutineScheduler::BroadcastMessage(const TCsCoroutineMessage &MessageType, const FName &Message)
{
	BroadcastMessage(MessageType, Message, nullptr);
}

#pragma endregion Run on Tick

// Run on CalcCamera
#pragma region

	// Allocate
#pragma region

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Allocate(CsCoroutine InCoroutine, AActor* InActor, const bool &DoInit, const bool &PerformFirstRun)
{
	return CalcCamera_Allocate(InCoroutine, nullptr, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, const bool &DoInit, const bool &PerformFirstRun)
{
	return CalcCamera_Allocate(InCoroutine, InStopCondition, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine, const bool &DoInit, const bool &PerformFirstRun)
{
	return CalcCamera_Allocate(InCoroutine, InStopCondition, InActor, nullptr, InOwnerMemberRoutine, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType, const bool &DoInit, const bool &PerformFirstRun)
{
	return CalcCamera_Allocate(InCoroutine, InStopCondition, InActor, nullptr, InAddRoutine, InRemoveRoutine, RoutineType, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Allocate(CsCoroutine InCoroutine, UObject* InObject, const bool &DoInit, const bool &PerformFirstRun)
{
	return CalcCamera_Allocate(InCoroutine, nullptr, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, const bool &DoInit, const bool &PerformFirstRun)
{
	return CalcCamera_Allocate(InCoroutine, InStopCondition, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine, const bool &DoInit, const bool &PerformFirstRun)
{
	return CalcCamera_Allocate(InCoroutine, InStopCondition, nullptr, InObject, InOwnerMemberRoutine, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType, const bool &DoInit, const bool &PerformFirstRun)
{
	return CalcCamera_Allocate(InCoroutine, InStopCondition, nullptr, InObject, InAddRoutine, InRemoveRoutine, RoutineType, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Allocate(CsCoroutine InCoroutine, AActor* InActor, UObject* InObject, const bool &DoInit, const bool &PerformFirstRun)
{
	return CalcCamera_Allocate(InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, const bool &DoInit, const bool &PerformFirstRun)
{
	return CalcCamera_Allocate(InCoroutine, InStopCondition, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine, const bool &DoInit, const bool &PerformFirstRun)
{
	for (int32 Index = 0; Index < CS_ROUTINE_POOL_SIZE; Index++)
	{
		CalcCamera_RoutinePoolIndex = (CalcCamera_RoutinePoolIndex + 1) % CS_ROUTINE_POOL_SIZE;

		FCsRoutine* R = &CalcCamera_RoutinePool[Index];

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
				R->index = CalcCamera_RoutinesToRun.Num();
				CalcCamera_RoutinesToRun.Add(R);

				if (PerformFirstRun)
				{
					R->Run(0.0f);
				}
			}
			else
			{
				CalcCamera_RoutinesToInit.Add(R);
			}
			return R;
		}
	}
	UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::CalcCamera_Allocate: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
	return nullptr;
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Allocate(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType, const bool &DoInit, const bool &PerformFirstRun)
{
	for (int32 Index = 0; Index < CS_ROUTINE_POOL_SIZE; Index++)
	{
		CalcCamera_RoutinePoolIndex = (CalcCamera_RoutinePoolIndex + 1) % CS_ROUTINE_POOL_SIZE;

		FCsRoutine* R = &CalcCamera_RoutinePool[Index];

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
				R->index = CalcCamera_RoutinesToRun.Num();
				CalcCamera_RoutinesToRun.Add(R);

				if (PerformFirstRun)
				{
					R->Run(0.0f);
				}
			}
			else
			{
				CalcCamera_RoutinesToInit.Add(R);
			}
			return R;
		}
	}
	UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::CalcCamera_Allocate: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
	return nullptr;
}

#pragma endregion Allocate

	// Start
#pragma region

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Start(CsCoroutine InCoroutine, AActor* InActor)
{
	return CalcCamera_Allocate(InCoroutine, nullptr, InActor, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor)
{
	return CalcCamera_Allocate(InCoroutine, InStopCondition, InActor, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine)
{
	return CalcCamera_Allocate(InCoroutine, InStopCondition, InActor, InOwnerMemberRoutine, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType)
{
	return CalcCamera_Allocate(InCoroutine, InStopCondition, InActor, InAddRoutine, InRemoveRoutine, RoutineType, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Start(CsCoroutine InCoroutine, AActor* InActor, UObject* InObject)
{
	return CalcCamera_Allocate(InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject)
{
	return CalcCamera_Allocate(InCoroutine, InStopCondition, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine)
{
	return CalcCamera_Allocate(InCoroutine, InStopCondition, InActor, InObject, InOwnerMemberRoutine, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_Start(CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType)
{
	return CalcCamera_Allocate(InCoroutine, InStopCondition, InActor, InObject, InAddRoutine, InRemoveRoutine, RoutineType, true, true);
}

#pragma endregion Start

	// StartChild
#pragma region

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor)
{
	return CalcCamera_StartChild(Parent, InCoroutine, nullptr, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor)
{
	return CalcCamera_StartChild(Parent, InCoroutine, InStopCondition, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine)
{
	return CalcCamera_StartChild(Parent, InCoroutine, InStopCondition, InActor, nullptr, InOwnerMemberRoutine);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType)
{
	return CalcCamera_StartChild(Parent, InCoroutine, InStopCondition, InActor, nullptr, InAddRoutine, InRemoveRoutine, RoutineType);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject)
{
	return CalcCamera_StartChild(Parent, InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject)
{
	return CalcCamera_StartChild(Parent, InCoroutine, InStopCondition, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine)
{
	for (int32 Index = 0; Index < CS_ROUTINE_POOL_SIZE; Index++)
	{
		CalcCamera_RoutinePoolIndex = (CalcCamera_RoutinePoolIndex + 1) % CS_ROUTINE_POOL_SIZE;

		FCsRoutine* R = &CalcCamera_RoutinePool[Index];

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
			R->index				 = CalcCamera_RoutinesToRun.Find(Element);
			CalcCamera_RoutinesToRun.Insert(R, R->index);

			const int32 ParentIndex = Parent->index;

			for (int32 J = R->index + 1; J <= ParentIndex; J++)
			{
				R->index++;
			}

			R->Run(0.0f);
			return R;
		}
	}
	UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::CalcCamera_StartChild: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
	return nullptr;
}

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_StartChild(struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8 &RoutineType)
{
	for (int32 Index = 0; Index < CS_ROUTINE_POOL_SIZE; Index++)
	{
		CalcCamera_RoutinePoolIndex = (CalcCamera_RoutinePoolIndex + 1) % CS_ROUTINE_POOL_SIZE;

		FCsRoutine* R = &CalcCamera_RoutinePool[Index];

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
			R->index				 = CalcCamera_RoutinesToRun.Find(Element);
			CalcCamera_RoutinesToRun.Insert(R, R->index);

			const int32 ParentIndex = Parent->index;

			for (int32 J = R->index + 1; J <= ParentIndex; J++)
			{
				R->index++;
			}

			R->Run(0.0f);
			return R;
		}
	}
	UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::CalcCamera_StartChild: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
	return nullptr;
}

#pragma endregion StartChild

struct FCsRoutine* UCsCoroutineScheduler::CalcCamera_StartRoutine(struct FCsRoutine* R)
{
	// TODO: This should never happen. If it does, need to trace how and fix it.
	// HACK: Index should never be greater than the CalcCamera_RoutinesToRun Count.
	if (R->index < 0 ||
		R->index >= CalcCamera_RoutinesToRun.Num())
	{
		FString State = R->index == CS_ROUTINE_END ? TEXT("END") : TEXT("FREE");

		UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::CalcCamera_StartRoutine: Attempting to start a Routine marked %s"), *State);

		// Check if the Routine is in the list of CalcCamera_RoutinesToExecute and remove it
		const int32 Count = CalcCamera_RoutinesToRun.Num();

		for (int32 Index = Count - 1; Index >= 0; Index--)
		{
			if (R == CalcCamera_RoutinesToRun[Index])
			{
				CalcCamera_RoutinesToRun.RemoveAt(Index);

				UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::CalcCamera_StartRoutine: Removing Routine marked %s at index %d in CalcCamera_RoutinesToRun"), *State, Index);
				break;
			}
		}
		check(0);
		R->Reset();
		return R;
	}
	CalcCamera_RoutinesToRun[R->index]->Run(0.0f);
	return R;
}

void UCsCoroutineScheduler::OnCalcCamera_Update(float DeltaSeconds)
{
	// Init
	int32 Count = CalcCamera_RoutinesToInit.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		FCsRoutine* R = CalcCamera_RoutinesToInit[Index];

		CS_COROUTINE_INIT(R);
		R->index = CalcCamera_RoutinesToRun.Num();
		CalcCamera_RoutinesToRun.Add(R);
	}

	CalcCamera_RoutinesToInit.Reset();

	// Remove any Routines executed previous to CalCamera
	Count = CalcCamera_RoutinesToRun.Num();

	for (int32 Index = Count - 1; Index >= 0; Index--)
	{
		FCsRoutine* R = CalcCamera_RoutinesToRun[Index];

		if (R->index == CS_ROUTINE_END)
		{
			R->Reset();
			CalcCamera_RoutinesToRun.RemoveAt(Index);
		}
	}
	// Execute
	Count = CalcCamera_RoutinesToRun.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		CalcCamera_RoutinesToRun[Index]->Run(DeltaSeconds);
	}
	// Remove any Routines executed end of CalCamera
	for (int32 Index = Count - 1; Index >= 0; Index--)
	{
		FCsRoutine* R = CalcCamera_RoutinesToRun[Index];

		if (R->index == CS_ROUTINE_END)
		{
			R->Reset();
			CalcCamera_RoutinesToRun.RemoveAt(Index);
		}
	}
}

void UCsCoroutineScheduler::CalcCamera_EndAll()
{
	int32 Count = CalcCamera_RoutinesToInit.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		FCsRoutine* R = CalcCamera_RoutinesToInit[Index];

		R->End();
		R->Reset();
	}

	CalcCamera_RoutinesToInit.Reset();

	Count = CalcCamera_RoutinesToRun.Num();

	for (int32 Index = 0; Index < Count; Index++)
	{
		FCsRoutine* R = CalcCamera_RoutinesToRun[Index];

		R->End();
		R->Reset();
	}
	CalcCamera_RoutinesToRun.Reset();
}

#pragma endregion CalcCamera