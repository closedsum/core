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

	bExit = false;
}

void FCsRunnable_Delegate::Start()
{
	// TODO: BUG: Issue with STAT groups being created and needing a unique name. This is a problem on NON-SHIPPING Builds
#if UE_BUILD_SHIPPING
	const FString& ThreadName = Cache.Name;
#else
	const uint64 UniqueId    = (uint64)FMath::RandRange(0, INT32_MAX - 1) + (uint64)FMath::RandRange(0, INT32_MAX - 1);
	const FString ThreadName = Cache.Name + TEXT("_") + FString::Printf(TEXT("%llu"), UniqueId);
#endif // #if UE_BUILD_SHIPPING

	// Windows default = 8mb for thread, could specify more
	Thread = FRunnableThread::Create(this, *ThreadName, 0, TPri_Normal);
}

void FCsRunnable_Delegate::EnsureCompletion()
{
	Stop();

	if (Thread)
		Thread->WaitForCompletion();
}

void FCsRunnable_Delegate::DeAllocate()
{
	if (Thread)
		delete Thread;
	Thread = nullptr;

	Delegate.Clear();
	Delegate_OnExit.Clear();
	Cache.Reset();
}