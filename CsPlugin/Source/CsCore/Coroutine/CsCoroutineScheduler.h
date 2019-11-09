// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Coroutine/CsCoroutineSchedule.h"
#include "CsCoroutineScheduler.generated.h"

namespace NCsCoroutineCached
{
	namespace Str
	{
		extern const FString Allocate;// = TEXT("UCsCoroutineScheduler::Allocate");
		extern const FString Start;// = TEXT("UCsCoroutineScheduler::Start");
		extern const FString Update;// = TEXT("UCsCoroutineScheduler::Update");
	}
}

UCLASS(transient)
class CSCORE_API UCsCoroutineScheduler : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsCoroutineScheduler* Get();

	static void Init();
	static void Shutdown();

protected:

	void Initialize();
	void CleanUp();

private:
	// Singleton data
	static UCsCoroutineScheduler* s_Instance;
	static bool s_bShutdown;

#pragma endregion Singleton

// Owner
#pragma region
public:

	TWeakObjectPtr<UObject> MyOwner;

	FORCEINLINE UObject* GetMyOwner()
	{
		return MyOwner.IsValid() ? MyOwner.Get() : nullptr;
	}


#pragma endregion Owner

protected:

	TArray<FCsCoroutineSchedule> Schedules;

// Start
#pragma region
public:

	const FCsRoutineHandle& Start(FCsMemoryResource_CoroutinePayload* PayloadContainer);
	const FCsRoutineHandle& Start(FCsCoroutinePayload* Payload);

	const FCsRoutineHandle& StartChild(FCsMemoryResource_CoroutinePayload* PayloadContainer);
	const FCsRoutineHandle& StartChild(FCsCoroutinePayload* Payload);

#pragma endregion Start

// Update
#pragma region
public:

	void Update(const FECsUpdateGroup& Group, const FCsDeltaTime& DeltaTime);

#pragma endregion Update
	
// End
#pragma region
public:

	void End(const FECsUpdateGroup& Group);
	void EndAll();

#pragma endregion End

// Payload
#pragma region
public:

	FCsMemoryResource_CoroutinePayload* AllocatePayload(const FECsUpdateGroup& Group);

#pragma endregion Payload

// Message
public:

	void BroadcastMessage(const FECsUpdateGroup& Group, const ECsCoroutineMessage& MessageType, const FName& Message, void* InOwner = nullptr);

#pragma endregion Message
};