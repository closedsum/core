// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Runnable/CsRunnable.h"

#include "HAL/RunnableThread.h"
// Runnable
#include "Managers/Runnable/Cache/CsCache_Runnable.h"
#include "Managers/Runnable/Payload/CsPayload_Runnable.h"
// Task
#include "Managers/Runnable/Task/CsRunnableTask.h"
#include "Managers/Runnable/Task/CsPayload_RunnableTask.h"

// Cache
#pragma region

namespace NCsRunnableDelegate
{
	namespace NCached
	{
		namespace Str
		{
			const FString CsRunnable = TEXT("FCsRunnable");
		}
	}
}

#pragma endregion Cache

FCsRunnable::FCsRunnable() :
	// Thread
	Thread(nullptr),
	StopTaskCounter(),
	ThreadName(),
	Cache(nullptr),
	// State
	State(EState::_None),
	// Task
	Task(nullptr),
	TaskState(ETaskState::None)

{
	Cache = new CacheType();
}

FCsRunnable::~FCsRunnable()
{
	if (Thread)
		delete Thread;
	Thread = nullptr;

	// Currently assume any owner will be a UObject and that UObject "controls" the
	// lifecycle of the Task. If the UObject is destroyed for some reason before the Runnable
	// is deconstructed, delete the Task.
	if (!Cache->GetOwner() &&
		Task)
	{
		delete Task;
	}
	delete Cache;
}

using PayloadType = NCsRunnable::NPayload::FImpl;
using TaskPayloadType = NCsRunnable::NTask::NPayload::FImpl;

// FRunnable interface
#pragma region

bool FCsRunnable::Init()
{
	return true;
}

uint32 FCsRunnable::Run()
{
	while(1)
	{
		// Idle
		if (State == EState::_Idle)
		{
			continue;
		}
		// Running
		else
		if (State == EState::_Running)
		{
			checkf(Task, TEXT("FCsRunnable::Run: Task is NULL."));

			TaskState = ETaskState::Running;

			Task->Execute();

			typedef NCsRunnable::NTask::FOnComplete OnCompleteType;

			for (OnCompleteType& OnComplete : Task->GetOnComplete_AsyncEvents())
			{
				OnComplete.Execute();
			}

			TaskState = ETaskState::Complete;

			State = EState::_Idle;
		}
		// Stop
		else
		if (State == EState::_Stop)
		{
			break;
		}
		// Exit
		else
		if (State == EState::_Exit)
		{
			break;
		}
	}
	return 0;
}

void FCsRunnable::Stop()
{
	StopTaskCounter.Increment();

	State = EState::_Stop;
}

void FCsRunnable::Exit()
{
	State = EState::_Exit;
}

#pragma endregion FRunnable interface

// Pool
#pragma region

void FCsRunnable::Allocate(PayloadType* Payload)
{
	Cache->Allocate(Payload);

	Task = Payload->Task;

	Start();
}

void FCsRunnable::Deallocate()
{
	if (Thread)
		delete Thread;
	Thread = nullptr;

	Cache->Reset();

	Task = nullptr;
}

#pragma endregion Pool

// Thread
#pragma region

void FCsRunnable::StartThread()
{
	using namespace NCsRunnableDelegate::NCached;

	// TODO: BUG: Issue with STAT groups being created and needing a unique name. This is a problem on NON-SHIPPING Builds
#if UE_BUILD_SHIPPING
	ThreadName = Str::CsRunnable + TEXT("_") + FString::Printf(TEXT("%d"), Cache->GetIndex());
#else
	const uint64 UniqueId = (uint64)FMath::RandRange(0, INT32_MAX - 1) + (uint64)FMath::RandRange(0, INT32_MAX - 1);
	ThreadName			  = Str::CsRunnable + TEXT("_") + FString::Printf(TEXT("%llu"), UniqueId);
#endif // #if UE_BUILD_SHIPPING

	// Windows default = 8mb for thread, could specify more
	Thread = FRunnableThread::Create(this, *ThreadName, 0, TPri_Normal);

	Handle.New();

	State = EState::_Idle;
}

void FCsRunnable::EnsureCompletion()
{
	Stop();

	if (Thread)
		Thread->WaitForCompletion();
}

#pragma endregion Thread

void FCsRunnable::SetIndex(const int32& InIndex)
{
	Cache->SetIndex(InIndex);

	Handle.Index = InIndex;
}

// State
#pragma region

#pragma endregion State

// Task
#pragma region

FCsRunnableHandle FCsRunnable::StartTask(TaskPayloadType* Payload)
{
	checkf(Payload, TEXT("FCsRunnable::StartTask: Payload is NULL."));

	Cache->Owner = Payload->Owner;

	checkf(Payload->Task, TEXT("FCsRunnable::StartTask: Payload->Task is NULL."));

	Task = Payload->Task;

	Start();

	if (Payload->Handle != FCsRunnableHandle::Invalid  &&
		Payload->Handle.GetIndex() == Handle.GetIndex())
	{
		Handle = Payload->Handle;
	}
	else
	{
		Handle.New();
	}
	return Handle;
}

void FCsRunnable::ReadyForTask()
{
	TaskState = ETaskState::Ready;

	Task = nullptr;

	Handle.Reset();
}

#pragma endregion Task