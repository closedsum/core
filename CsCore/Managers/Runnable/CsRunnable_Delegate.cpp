#include "Managers/Runnable/CsRunnable_Delegate.h"
#include "CsCore.h"

#include "Runtime/Core/Public/HAL/RunnableThread.h"

// Cache
#pragma region

namespace ECsRunnableDelegateCachedString
{
	namespace Str
	{
		const FString CsRunnable_Delegate = TEXT("FCsRunnable_Delegate");
	}
}

#pragma endregion Cache

FCsRunnable_Delegate::FCsRunnable_Delegate()
{
}

FCsRunnable_Delegate::~FCsRunnable_Delegate()
{
	if (Thread)
		delete Thread;
	Thread = nullptr;
}

// FRunnable interface
#pragma region

bool FCsRunnable_Delegate::Init()
{
	bExit = false;
	return true;
}

uint32 FCsRunnable_Delegate::Run()
{
	Delegate.Broadcast();
	return 0;
}

void FCsRunnable_Delegate::Stop()
{
	StopTaskCounter.Increment();
}

void FCsRunnable_Delegate::Exit()
{
	Delegate_OnExit.Broadcast();

	if (Thread)
		delete Thread;
	Thread = nullptr;
	bExit = true;
}

#pragma endregion FRunnable interface

void FCsRunnable_Delegate::Setup(const uint8& InIndex)
{
	const FString Name = ECsRunnableDelegateCachedString::Str::CsRunnable_Delegate + FString::FromInt(InIndex);
	Cache.Set(InIndex, Name);
}

void FCsRunnable_Delegate::Allocate(const uint8 &ActiveIndex, FCsRunnablePayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame)
{
	Cache.Init(ActiveIndex, Payload, Time, RealTime, Frame);
}

void FCsRunnable_Delegate::Start()
{
	// Windows default = 8mb for thread, could specify more
	Thread = FRunnableThread::Create(this, *(Cache.Name), 0, TPri_Normal);
}

void FCsRunnable_Delegate::EnsureCompletion()
{
	Stop();

	if (Thread)
		Thread->WaitForCompletion();
}

void FCsRunnable_Delegate::DeAllocate()
{
	EnsureCompletion();
	Delegate.Clear();
	Delegate_OnExit.Clear();
}