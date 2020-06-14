// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsCoroutineSchedule.h"
#include "CsCore.h"

// CVars
#include "Coroutine/CsCVars_Coroutine.h"

FCsCoroutineSchedule::FCsCoroutineSchedule()
{
	// Set Index for fast look up

	// Routine
	{
		const TArray<FCsResource_Routine*>& Pool = Manager_Routine.GetPool();

		for (FCsResource_Routine* Container : Pool)
		{
			FCsRoutine* R	   = Container->Get();
			const int32& Index = Container->GetIndex();
			R->SetIndex(Index);
		}
	}
	// Payload
	{
		const TArray<FCsResource_CoroutinePayload*>& Pool = Manager_Payload.GetPool();

		for (FCsResource_CoroutinePayload* Container : Pool)
		{
			FCsCoroutinePayload* P = Container->Get();
			const int32& Index	   = Container->GetIndex();
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
		const TArray<FCsResource_Routine*>& Pool = Manager_Routine.GetPool();

		for (FCsResource_Routine* Container : Pool)
		{
			FCsRoutine* R = Container->Get();
			R->SetGroup(Group);
		}
	}
	// Payload
	{
		const TArray<FCsResource_CoroutinePayload*>& Pool = Manager_Payload.GetPool();

		for (FCsResource_CoroutinePayload* Container : Pool)
		{
			FCsCoroutinePayload* P = Container->Get();
			P->Group			   = Group;
		}
	}
}

#pragma endregion Schedule

// Routine
#pragma region

FCsResource_Routine* FCsCoroutineSchedule::GetRoutineContainer(const FCsRoutineHandle& Handle)
{
	if (!Handle.IsValid())
		return nullptr;

	const int32& PoolSize = Manager_Routine.GetPoolSize();

	if (Handle.GetIndex() >= PoolSize)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsCoroutineSchedule::GetRoutineContainer: Handle's Index: %d is not associated with any Routine with Group: %s."), Handle.GetIndex(), Group.ToChar())
		return nullptr;
	}

	return Manager_Routine.GetAt(Handle.GetIndex());
}

FCsRoutine* FCsCoroutineSchedule::GetRoutine(const FCsRoutineHandle& Handle)
{
	FCsResource_Routine* Container = GetRoutineContainer(Handle);

	return Container ? Container->Get() : nullptr;
}

#pragma endregion Routine

// Start
#pragma region

const FCsRoutineHandle& FCsCoroutineSchedule::Start(FCsResource_CoroutinePayload* PayloadContainer)
{
	FCsCoroutinePayload* Payload = PayloadContainer->Get();

	checkf(Payload, TEXT("FCsCoroutineSchedule::Start: PayloadContainer does NOT contain a reference to a Payload."));

	checkf(Group == Payload->Group, TEXT("FCsCoroutineSchedule::Start: Mismatch between Payload->Group: %s and Group: %s"), *(Payload->Group.Name), *(Group.Name));

	FCsResource_Routine* RoutineContainer = Manager_Routine.Allocate();
	FCsRoutine* R						  = RoutineContainer->Get();

	R->Init(Payload);

	CS_COROUTINE_INIT(R);

	if (Payload->bPerformFirstUpdate)
	{
		R->StartUpdate();
		R->Update(FCsDeltaTime::Zero);
	}

	//LogTransaction(NCsCoroutineCached::Str::Allocate, (Payload->bDoInit && Payload->bPerformFirstRun) ? ECsCoroutineTransaction::Start : ECsCoroutineTransaction::Allocate, R);

	Payload->Reset();
	Manager_Payload.Deallocate(PayloadContainer);
	return R->GetHandle();
}

const FCsRoutineHandle& FCsCoroutineSchedule::Start(FCsCoroutinePayload* Payload)
{
	return Start(GetPayloadContainer(Payload));
}

const FCsRoutineHandle& FCsCoroutineSchedule::StartChild(FCsResource_CoroutinePayload* PayloadContainer)
{
	FCsCoroutinePayload* Payload = PayloadContainer->Get();

	checkf(Payload, TEXT("FCsCoroutineSchedule::StartChild: PayloadContainer does NOT contain a reference to a Payload."));

	checkf(Group = Payload->Group, TEXT("FCsCoroutineSchedule::StartChild: Mismatch between Payload->Group: %s and Group: %s"), *(Payload->Group.Name), *(Group.Name));

	FCsResource_Routine* ParentContainer = GetRoutineContainer(Payload->ParentHandle);

	checkf(ParentContainer, TEXT("FCsCoroutineSchedule::StartChild: Failed to find a container for Payload."));

	FCsRoutine* Parent = ParentContainer->Get();

	FCsRoutine* LastChild = Parent->GetLastChild();

	FCsResource_Routine* RoutineContainer = nullptr;

	// Add after Last Child
	if (LastChild)
	{
		FCsResource_Routine* LastChildContainer = Manager_Routine.GetAt(LastChild->GetIndex());

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
	return R->GetHandle();
}

const FCsRoutineHandle& FCsCoroutineSchedule::StartChild(FCsCoroutinePayload* Payload)
{
	return StartChild(GetPayloadContainer(Payload));
}

#pragma endregion Start

// End
#pragma region

void FCsCoroutineSchedule::End()
{
	TCsDoubleLinkedList<FCsResource_Routine*>* Current = Manager_Routine.GetAllocatedHead();
	TCsDoubleLinkedList<FCsResource_Routine*>* Next	   = Current;

	while (Next)
	{
		Current								  = Next;
		FCsResource_Routine* RoutineContainer = **Current;
		Next								  = Current->GetNextLink();

		FCsRoutine* R = RoutineContainer->Get();

		R->End(ECsCoroutineEndReason::Shutdown);

		//LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), ECsCoroutineTransaction::End, R);

		R->Reset();
		Manager_Routine.Deallocate(RoutineContainer);
	}
}

void FCsCoroutineSchedule::End(const FCsRoutineHandle& Handle)
{
	if (FCsResource_Routine* Container = GetRoutineContainer(Handle))
	{
		FCsRoutine* R = Container->Get();


		R->End(ECsCoroutineEndReason::Manual);

		//LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), ECsCoroutineTransaction::End, R);

		R->Reset();
		Manager_Routine.Deallocate(Container);
	}
}

#pragma endregion End

// Update
#pragma region

void FCsCoroutineSchedule::Update(const FCsDeltaTime& DeltaTime)
{
	TCsDoubleLinkedList<FCsResource_Routine*>* Current = Manager_Routine.GetAllocatedHead();
	TCsDoubleLinkedList<FCsResource_Routine*>* Next    = Current;

	while (Next)
	{
		Current								  = Next;
		FCsResource_Routine* RoutineContainer = **Current;
		Next								  = Current->GetNextLink();

		FCsRoutine* R = RoutineContainer->Get();

		const ECsCoroutineState& State = R->State;

		// Init -> Update
		if (State == ECsCoroutineState::Init)
		{
			R->StartUpdate();
			R->Update(DeltaTime);
		}
		// Update
		else
		if (State == ECsCoroutineState::Update)
		{
			R->Update(DeltaTime);
		}

		// End
		if (State == ECsCoroutineState::End)
		{
			//LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), ECsCoroutineTransaction::End, R);

			R->Reset();
			Manager_Routine.Deallocate(RoutineContainer);
		}
	}
}

#pragma endregion Update

// Payload
#pragma region

FCsResource_CoroutinePayload* FCsCoroutineSchedule::GetPayloadContainer(FCsCoroutinePayload* Payload)
{
	if (Payload->GetIndex() == INDEX_NONE)
	{
		FCsResource_CoroutinePayload* PayloadContainer = Manager_Payload.Allocate();
		FCsCoroutinePayload* P						   = PayloadContainer->Get();

		*P = *Payload;

		return PayloadContainer;
	}
	return Manager_Payload.GetAt(Payload->GetIndex());
}

#pragma endregion Payload

// Message
#pragma region

void FCsCoroutineSchedule::BroadcastMessage(const ECsCoroutineMessage& MessageType, const FName& Message, void* Owner /*=nullptr*/)
{
	TCsDoubleLinkedList<FCsResource_Routine*>* Current = Manager_Routine.GetAllocatedHead();
	TCsDoubleLinkedList<FCsResource_Routine*>* Next    = Current;

	while (Next)
	{
		Current								  = Next;
		FCsResource_Routine* RoutineContainer = **Current;
		Next								  = Current->GetNextLink();

		FCsRoutine* R = RoutineContainer->Get();

		if (Owner)
		{
			if (R->Owner.GetOwner() == Owner)
				R->ReceiveMessage(MessageType, Message);
		}
		else
		{
			R->ReceiveMessage(MessageType, Message);
		}
	}
}

#pragma endregion Message

// Log
#pragma region

void FCsCoroutineSchedule::LogTransaction(const FString& FunctionName, const ECsCoroutineTransaction& Transaction, FCsRoutine* R)
{
	/*
	if (CsCVarLogCoroutineTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		FString TransactionAsString = NCsCoroutineTransaction::ToActionString(Transaction);
			
		if (Transaction == ECsCoroutineTransaction::End)
			TransactionAsString = NCsCoroutineTransaction::ToActionString(Transaction) + TEXT("(Reason=") + EMCsCoroutineEndReason::Get().ToString(R->endReason) + TEXT(")");

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

		if (Transaction == ECsCoroutineTransaction::End)
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