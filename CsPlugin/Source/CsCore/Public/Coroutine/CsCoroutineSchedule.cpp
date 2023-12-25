// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coroutine/CsCoroutineSchedule.h"
#include "CsCore.h"

// CVars
#include "Coroutine/CsCVars_Coroutine.h"

// Cached
#pragma region

namespace NCsCoroutine
{
	namespace NSchedule
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsCoroutineSchedule, Start);
			}
		}
	}
}

#pragma endregion Cached

FCsCoroutineSchedule::FCsCoroutineSchedule()
{
	// Set Index for fast look up

	// Routine
	{
		const TArray<RoutineResourceType*>& Pool = Manager_Routine.GetPool();

		for (RoutineResourceType* Container : Pool)
		{
			FCsRoutine* R	   = Container->Get();
			const int32& Index = Container->GetIndex();
			R->SetIndex(Index);
		}
	}
	// Payload
	{
		const TArray<PayloadResourceType*>& Pool = Manager_Payload.GetPool();

		for (PayloadResourceType* Container : Pool)
		{
			PayloadType* P		= Container->Get();
			const int32& Index	= Container->GetIndex();
			P->SetIndex(Index);
		}
	}
}

FCsCoroutineSchedule::~FCsCoroutineSchedule()
{
}

// Schedule
#pragma region

void FCsCoroutineSchedule::SetGroup(const FECsUpdateGroup& InGroup)
{
	Group = InGroup;

	// Update TimeGroup

	// Routine
	{
		const TArray<RoutineResourceType*>& Pool = Manager_Routine.GetPool();

		for (RoutineResourceType* Container : Pool)
		{
			FCsRoutine* R = Container->Get();
			R->SetGroup(Group);
		}
	}
	// Payload
	{
		const TArray<PayloadResourceType*>& Pool = Manager_Payload.GetPool();

		for (PayloadResourceType* Container : Pool)
		{
			PayloadType* P = Container->Get();
			P->Group	   = Group;
		}
	}
}

#pragma endregion Schedule

// Routine
#pragma region

NCsRoutine::FResource* FCsCoroutineSchedule::GetRoutineContainer(const FCsRoutineHandle& Handle) const
{
	if (!Handle.IsValid())
		return nullptr;

	const int32& PoolSize = Manager_Routine.GetPoolSize();

	if (Handle.GetIndex() >= PoolSize)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsCoroutineSchedule::GetRoutineContainer: Handle's Index: %d is not associated with any Routine with Group: %s."), Handle.GetIndex(), Group.ToChar())
		return nullptr;
	}

	RoutineResourceType* Container = Manager_Routine.GetAt(Handle.GetIndex());
	FCsRoutine* R				   = Container->Get();

	if (R->GetHandle() == Handle)
		return Container;
	return nullptr;
}

FCsRoutine* FCsCoroutineSchedule::GetRoutine(const FCsRoutineHandle& Handle) const
{
	RoutineResourceType* Container = GetRoutineContainer(Handle);

	return Container ? Container->Get() : nullptr;
}

#pragma endregion Routine

// Handle
#pragma region

bool FCsCoroutineSchedule::IsRunning(const FCsRoutineHandle& Handle) const
{
	if (FCsRoutine* R = GetRoutine(Handle))
		return R->IsRunning();
	return false;
}

#pragma endregion Handle

// Start
#pragma region

const FCsRoutineHandle& FCsCoroutineSchedule::Start(PayloadResourceType* PayloadContainer)
 {
	using namespace NCsCoroutine::NSchedule::NCached;

	const FString& Context = Str::Start;

	PayloadType* Payload = PayloadContainer->Get();

	checkf(Payload, TEXT("%s: PayloadContainer does NOT contain a reference to a Payload."), *Context);

	check(Payload->IsValidChecked(Context));

	checkf(Group == Payload->Group, TEXT("%s: Mismatch between Payload->Group: %s and Group: %s"), *Context, Payload->Group.ToChar(), Group.ToChar());

	FCsRoutine* R = Manager_Routine.AllocateResource();

	R->Init(Payload);

	CS_COROUTINE_INIT(R);

	if (Payload->bPerformFirstUpdate)
	{
		R->StartUpdate();
		R->Update(FCsDeltaTime::Zero);
	}

	//LogTransaction(NCsCoroutineCached::Str::Allocate, (Payload->bDoInit && Payload->bPerformFirstRun) ? TransactionType::Start : TransactionType::Allocate, R);

	Payload->Reset();
	Manager_Payload.Deallocate(PayloadContainer);
	return R->HasEnded() ? FCsRoutineHandle::Invalid : R->GetHandle();
}

const FCsRoutineHandle& FCsCoroutineSchedule::Start(PayloadType* Payload)
{
	return Start(GetPayloadContainer(Payload));
}

const FCsRoutineHandle& FCsCoroutineSchedule::StartChild(PayloadResourceType* PayloadContainer)
{
	PayloadType* Payload = PayloadContainer->Get();

	checkf(Payload, TEXT("FCsCoroutineSchedule::StartChild: PayloadContainer does NOT contain a reference to a Payload."));

	checkf(Group == Payload->Group, TEXT("FCsCoroutineSchedule::StartChild: Mismatch between Payload->Group: %s and Group: %s"), Payload->Group.ToChar(), Group.ToChar());

	RoutineResourceType* ParentContainer = GetRoutineContainer(Payload->ParentHandle);

	checkf(ParentContainer, TEXT("FCsCoroutineSchedule::StartChild: Failed to find a container for Payload."));

	FCsRoutine* Parent = ParentContainer->Get();

	FCsRoutine* LastChild = Parent->GetLastChild();

	RoutineResourceType* RoutineContainer = nullptr;

	// Add after Last Child
	if (LastChild)
	{
		RoutineResourceType* LastChildContainer = Manager_Routine.GetAt(LastChild->GetIndex());

		RoutineContainer = Manager_Routine.AllocateAfter(LastChildContainer);
	}
	// Add after Parent
	else
	{
		RoutineContainer = Manager_Routine.AllocateAfter(ParentContainer);
	}

	FCsRoutine* R = RoutineContainer->Get();

	Parent->AddChild(R);

	R->Init(Payload);

	CS_COROUTINE_INIT(R);

	R->StartUpdate();
	R->Update(FCsDeltaTime::Zero);

	Payload->Reset();
	//UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::StartChild: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
	return R->HasEnded() ? FCsRoutineHandle::Invalid : R->GetHandle();
}

const FCsRoutineHandle& FCsCoroutineSchedule::StartChild(PayloadType* Payload)
{
	return StartChild(GetPayloadContainer(Payload));
}

#pragma endregion Start

// End
#pragma region

bool FCsCoroutineSchedule::End()
{
	bool Result = false;

	TCsDoubleLinkedList<RoutineResourceType*>* Current = Manager_Routine.GetAllocatedHead();
	TCsDoubleLinkedList<RoutineResourceType*>* Next	   = Current;

	while (Next)
	{
		Current								  = Next;
		RoutineResourceType* RoutineContainer = **Current;
		Next								  = Current->GetNextLink();

		FCsRoutine* R = RoutineContainer->Get();

		if (!R->HasEnded())
		{
			typedef NCsCoroutine::EEndReason EndReasonType;

			R->End(EndReasonType::Shutdown);
		}
		//LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

		R->Reset();
		Manager_Routine.Deallocate(RoutineContainer);

		Result = true;
	}
	return Result;
}

bool FCsCoroutineSchedule::End(const FCsRoutineHandle& Handle)
{
	if (RoutineResourceType* Container = GetRoutineContainer(Handle))
	{
		FCsRoutine* R = Container->Get();

		// If the Routine has already Ended, exit
		if (R->HasEnded() ||
			R->HasJustEnded())
		{
			return false;
		}

		// If the Routine is currently being Updated, queue the End for either the
		// beginning of the next Update or the end of the current Update.
		if (!R->IsUpdateComplete())
		{
			QueueEndHandles.Add(Handle);
			return false;
		}

		typedef NCsCoroutine::EEndReason EndReasonType;

		R->End(EndReasonType::Manual);

		//LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

		R->Reset();
		Manager_Routine.Deallocate(Container);
		return true;
	}
	return false;
}

bool FCsCoroutineSchedule::HasEnded(const FCsRoutineHandle& Handle) const
{
	if (FCsRoutine* R = GetRoutine(Handle))
		return R->HasEnded();
	return true;
}

bool FCsCoroutineSchedule::HasJustEnded(const FCsRoutineHandle& Handle) const
{
	if (FCsRoutine* R = GetRoutine(Handle))
		return R->HasJustEnded();
	return true;
}

#pragma endregion End

// Update
#pragma region

void FCsCoroutineSchedule::Update(const FCsDeltaTime& DeltaTime)
{
	// End any pending Handles requested for End from the previous Update
	for (const FCsRoutineHandle& Handle : QueueEndHandles)
	{
		End(Handle);
	}

	QueueEndHandles.Reset(QueueEndHandles.Max());

	TCsDoubleLinkedList<RoutineResourceType*>* Current = Manager_Routine.GetAllocatedHead();
	TCsDoubleLinkedList<RoutineResourceType*>* Next    = Current;

	while (Next)
	{
		Current								  = Next;
		RoutineResourceType* RoutineContainer = **Current;
		Next								  = Current->GetNextLink();

		FCsRoutine* R = RoutineContainer->Get();

		typedef NCsCoroutine::EState StateType;

		const StateType& State = R->State;

		// Init -> Update
		if (State == StateType::Init)
		{
			R->StartUpdate();
			R->Update(DeltaTime);
		}
		// Update
		else
		if (State == StateType::Update)
		{
			R->Update(DeltaTime);
		}

		// End
		if (State == StateType::End)
		{
			//LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

			R->Reset();
			Manager_Routine.Deallocate(RoutineContainer);
		}
	}

	// End any Handles requested for End on the current Update
	for (const FCsRoutineHandle& Handle : QueueEndHandles)
	{
		End(Handle);
	}

	QueueEndHandles.Reset(QueueEndHandles.Max());
}

#pragma endregion Update

// Payload
#pragma region

#define _PayloadResourceType NCsCoroutine::NPayload::FResource
_PayloadResourceType* FCsCoroutineSchedule::GetPayloadContainer(PayloadType* Payload)
{
#undef _PayloadResourceType

	if (Payload->GetIndex() == INDEX_NONE)
	{
		PayloadResourceType* Container = Manager_Payload.Allocate();
		PayloadType* P				   = Container->Get();

		*P = *Payload;

		return Container;
	}
	return Manager_Payload.GetAt(Payload->GetIndex());
}

#pragma endregion Payload

// Message
#pragma region

void FCsCoroutineSchedule::BroadcastMessage(const MessageType& Type, const FName& Message, void* Owner /*=nullptr*/)
{
	TCsDoubleLinkedList<RoutineResourceType*>* Current = Manager_Routine.GetAllocatedHead();
	TCsDoubleLinkedList<RoutineResourceType*>* Next    = Current;

	while (Next)
	{
		Current								  = Next;
		RoutineResourceType* RoutineContainer = **Current;
		Next								  = Current->GetNextLink();

		FCsRoutine* R = RoutineContainer->Get();

		if (Owner)
		{
			if (R->Owner.GetOwner() == Owner)
				R->ReceiveMessage(Type, Message);
		}
		else
		{
			R->ReceiveMessage(Type, Message);
		}
	}
}

#pragma endregion Message

// Log
#pragma region

void FCsCoroutineSchedule::LogTransaction(const FString& FunctionName, const TransactionType& Transaction, FCsRoutine* R)
{
	/*
	if (CsCVarLogCoroutineTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		FString TransactionAsString = NCsCoroutine::NTransaction::ToActionString(Transaction);
			
		if (Transaction == TransactionType::End)
			TransactionAsString = NCsCoroutine::NTransaction::ToActionString(Transaction) + TEXT("(Reason=") + EMCsCoroutineEndReason::Get().ToString(R->endReason) + TEXT(")");

		const FString& ScheduleTypeAsString = EMCsCoroutineSchedule::Get().ToString(R->scheduleType);

		AActor* Actor			= R->GetActor();
		const FString ActorName = Actor ? Actor->GetName() : NCsCached::Str::Empty;
		UObject* Object			= R->GetRObject();
		const FString ObjectName = Object ? Object->GetName() : NCsCached::Str::Empty;
		UObject* Owner			= R->GetOwner();
		const FString OwnerName	= Owner ? Owner->GetName() : NCsCached::Str::Empty;

		UWorld* World = nullptr;

		if (Actor)
			World = Actor->GetWorld();
		if (Object)
			World = Object->GetWorld();

		const float CurrentTime = World ? World->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();

		const FString CoroutineName = R->name == NAME_None ? NCsCached::Str::None : R->nameAsString;

		FString Elapsed = NCsCached::Str::None;

		if (Transaction == TransactionType::End)
		{
			const float Duration = CurrentTime - R->startTime;
			Elapsed = TEXT("Ran for ") + FString::FromInt(R->tickCount) + TEXT(" Ticks and  ") + UCsLibrary_Common::GetFloatAsStringWithPrecision(Duration, 2) + TEXT(" Seconds.");
		}

		if (Actor && Object)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. Owner: %s using Actor: %s and Object: %s. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *ActorName, *ObjectName, *Elapsed);
		}
		else
		if (Actor)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. Using Owner: %s. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *ActorName, *Elapsed);
		}
		else
		if (Object)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. Using Owner: %s. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *ObjectName, *Elapsed);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *Elapsed);
		}
	}
	*/
}

void FCsCoroutineSchedule::LogRunning()
{
	/*
	if (CsCVarLogCoroutineRunning->GetInt() != CS_CVAR_SHOW_LOG)
		return;

	const uint8 Schedule = (uint8)ScheduleType;
	const int32 Count    = RoutinesToRun[Schedule].Num();

	if (Count == CS_EMPTY)
		return;

	UWorld* World = nullptr;

	if (UObject* Object = GetMyOwner())
		World = Object->GetWorld();

	float CurrentTime = World ? World->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();

	const FString& FunctionName		    = NCsCoroutineCached::Str::Update;
	const FString& ScheduleTypeAsString = EMCsCoroutineSchedule::Get().ToString(ScheduleType);

	UE_LOG(LogCs, Warning, TEXT("%s: On%s. Running %d Coroutines at %f."), *FunctionName, *ScheduleTypeAsString, Count, CurrentTime);

	for (int32 Index = 0; Index < Count; ++Index)
	{
		FCsRoutine* R = RoutinesToRun[Schedule][Index];

		AActor* Actor			= R->GetActor();
		const FString ActorName = Actor ? Actor->GetName() : NCsCached::Str::Empty;
		UObject* Object			= R->GetRObject();
		const FString ObjectName = Object ? Object->GetName() : NCsCached::Str::Empty;
		UObject* Owner			= R->GetOwner();
		const FString OwnerName = Owner ? Owner->GetName() : NCsCached::Str::Empty;

		const FString CoroutineName = R->name == NAME_None ? NCsCached::Str::None : R->name.ToString();

		const float Duration = CurrentTime - R->startTime;

		if (Actor && Object)
		{
			UE_LOG(LogCs, Warning, TEXT("-- Routine with Coroutine: %s. Owner: %s using Actor: %s and Object: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, *ActorName, *ObjectName, R->tickCount, Duration);
		}
		else
		if (Actor)
		{
			UE_LOG(LogCs, Warning, TEXT("-- Routine with Coroutine: %s. Using Owner: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, *ActorName, R->tickCount, Duration);
		}
		else
		if (Object)
		{
			UE_LOG(LogCs, Warning, TEXT("-- Routine with Coroutine: %s. Using Owner: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, *ObjectName, R->tickCount, Duration);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("-- Routine with Coroutine: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, R->tickCount, Duration);
		}
	}
	*/
}

#pragma endregion Log