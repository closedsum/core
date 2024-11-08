// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"

#include "HAL/Runnable.h"
#include "HAL/ThreadSafeCounter.h"
#include "Delegates/DelegateCombinations.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "Containers/UnrealString.h"

#include "Managers/Runnable/CsTypes_Runnable.h"

class FRunnableThread;

// NCsRunnable::FCache
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsRunnable, FCache)
// NCsRunnable::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsRunnable, NPayload, FImpl)
// NCsRunnable::NTask::ITask
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsRunnable, NTask, ITask)
// NCsRunnable::NTask::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsRunnable, NTask, NPayload, FImpl)

/**
*/
class CSTHREAD_API FCsRunnable : public FRunnable
{

public:

	FCsRunnable();
	virtual ~FCsRunnable();
	
// FRunnable interface
#pragma region
public:

	bool Init();
	uint32 Run();
	void Stop();
	void Exit();

#pragma endregion FRunnable interface

// Pool
#pragma region
public:

#define PayloadType NCsRunnable::NPayload::FImpl
	void Allocate(PayloadType* Payload);
#undef PayloadType

	void Deallocate();

#pragma endregion Pool

// Thread
#pragma region
private:

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	FString ThreadName;

public:

	void StartThread();

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

#pragma endregion Thread

#define CsRunnableCacheType NCsRunnable::FCache

private:

	CsRunnableCacheType* Cache;
public:
	FORCEINLINE CsRunnableCacheType* GetCache() const { return Cache; }

#undef CsRunnableCacheType

private:

	FCsRunnableHandle Handle;

public:

	FORCEINLINE const FCsRunnableHandle& GetHandle() const { return Handle; }

	void SetIndex(const int32& InIndex);

// State
#pragma region
private:

	/**
	*/
	enum class EState : uint8
	{
		_None,
		_Idle,
		_Running,
		_Stop,
		_Exit
	};

	EState State;

public:

	FORCEINLINE bool IsIdle() const
	{
		return State == EState::_Idle;
	}

	FORCEINLINE void Start()
	{
		State = EState::_Running;
	}

#pragma endregion State

// Task
#pragma region

#define CsRunnableTaskType NCsRunnable::NTask::ITask

private:

	/** */
	CsRunnableTaskType* Task;

public:

	FORCEINLINE CsRunnableTaskType* GetTask() const { return Task; }

#undef CsRunnableTaskType

private:

	/**
	*/
	enum class ETaskState : uint8
	{
		None,
		Ready,
		Running,
		Complete
	};

	ETaskState TaskState;

public:

	FORCEINLINE bool IsTaskComplete() const
	{
		return TaskState == ETaskState::Complete;
	}

#define TaskPayloadType NCsRunnable::NTask::NPayload::FImpl
	FCsRunnableHandle StartTask(TaskPayloadType* Payload);
#undef TaskPayloadType

	void StopTask();

	void ReadyForTask();

	FORCEINLINE bool IsReadyForTask() const
	{
		return TaskState == ETaskState::Ready;
	}

#pragma endregion Task
};