// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/Core/Public/HAL/Runnable.h"
#include "Runtime/Core/Public/HAL/ThreadSafeCounter.h"
#include "Runtime/Core/Public/Delegates/DelegateCombinations.h"
#include "Runtime/Core/Public/UObject/WeakObjectPtrTemplates.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

#include "Managers/Runnable/CsTypes_Runnable.h"

class FRunnableThread;
struct FCsRunnableCache;
struct FCsRunnablePayload;
struct ICsRunnableTask;
struct FCsRunnableTaskPayload;

/**
*/
class CSCORE_API FCsRunnable : public FRunnable
{

public:

	FCsRunnable();
	virtual ~FCsRunnable();
	
// FRunnable interface
#pragma region
public:

	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	virtual void Exit();

#pragma endregion FRunnable interface

// Pool
#pragma region
public:

	void Allocate(FCsRunnablePayload* Payload);

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

private:

	FCsRunnableCache* Cache;

public:

	FORCEINLINE FCsRunnableCache* GetCache() const
	{
		return Cache;
	}

private:

	FCsRunnableHandle Handle;

public:

	FORCEINLINE const FCsRunnableHandle& GetHandle() const
	{
		return Handle;
	}

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
private:

	/** */
	ICsRunnableTask* Task;

public:

	FORCEINLINE ICsRunnableTask* GetTask() const
	{
		return Task;
	}

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

	FCsRunnableHandle StartTask(FCsRunnableTaskPayload* Payload);

	void StopTask();

	void ReadyForTask();

	FORCEINLINE bool IsReadyForTask() const
	{
		return TaskState == ETaskState::Ready;
	}

#pragma endregion Task
};