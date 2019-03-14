// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/Core/Public/HAL/Runnable.h"
#include "Runtime/Core/Public/HAL/ThreadSafeCounter.h"
#include "Runtime/Core/Public/Delegates/DelegateCombinations.h"
#include "Runtime/Core/Public/UObject/WeakObjectPtrTemplates.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"
#include "Types/CsTypes_Runnable.h"

struct FCsRunnableCache
{
public:

	bool bAllocated;

	uint8 Index;
	FString Name;

	TWeakObjectPtr<class UObject> Owner;

	uint32 StackSize;
	EThreadPriority ThreadPriority;

	float Time;
	float RealTime;
	uint64 Frame;
	float ElapsedTime;

public:

	FCsRunnableCache()
	{
		Reset();
	}

	virtual ~FCsRunnableCache() {}

	void Set(const uint8& InIndex, const FString& InName)
	{
		Index = InIndex;
		Name = InName;
	}

	void Init(FCsRunnablePayload* Payload, const float& InTime, const float& InRealTime, const uint64& InFrame)
	{
		bAllocated = true;
		Owner = Payload->GetOwner();
		StackSize = Payload->StackSize;
		ThreadPriority = Payload->ThreadPriority;
		Time = InTime;
		RealTime = InRealTime;
		Frame = InFrame;
	}

	virtual void Reset()
	{
		bAllocated = false;

		Owner.Reset();
		Owner = nullptr;
		Time = 0.0f;
		RealTime = 0.0f;
		Frame = 0;
		ElapsedTime = 0.0f;
	}

public:

	UObject * GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }
	template<typename T>
	T* GetOwner() { return Cast<T>(GetOwner()); }

	void DeAllocate()
	{
		Reset();
	}
};

class CSCORE_API FCsRunnable_Delegate : public FRunnable
{

public:

	/** Thread to run the worker FRunnable on */
	class FRunnableThread* Thread;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	FCsRunnable_Delegate();
	virtual ~FCsRunnable_Delegate();

// FRunnable interface
#pragma region
public:

	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	virtual void Exit();

#pragma endregion FRunnable interface

public:

	FCsRunnableCache Cache;

	void Setup(const uint8& InIndex);

	DECLARE_MULTICAST_DELEGATE(FDelegate);

	FDelegate Delegate;

	DECLARE_MULTICAST_DELEGATE(FOnExit);

	FOnExit Delegate_OnExit;

	void Allocate(FCsRunnablePayload* Payload, const float& Time, const float& RealTime, const uint64& Frame);
	void Start();

	bool bExit;

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();
	void DeAllocate();
};