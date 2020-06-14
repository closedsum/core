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

class ICsGetCoroutineScheduler;

UCLASS(transient)
class CSCORE_API UCsCoroutineScheduler : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsCoroutineScheduler* Get(UObject* InRoot = nullptr);
	static void Init(UObject* InRoot);
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetCoroutineScheduler* Get_GetCoroutineScheduler(UObject* InRoot);
	static ICsGetCoroutineScheduler* GetSafe_GetCoroutineScheduler(UObject* Object);

	static UCsCoroutineScheduler* GetSafe(UObject* Object);

public:

	static UCsCoroutineScheduler* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	void Initialize();
	void CleanUp();

private:
	// Singleton data
	static UCsCoroutineScheduler* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
private:

	UObject* MyRoot;

public:

	FORCEINLINE void SetMyRoot(UObject* InRoot)
	{
		MyRoot = InRoot;
	}

	FORCEINLINE const UObject* GetMyRoot() const
	{
		return MyRoot;
	}

#pragma endregion Root

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

	const FCsRoutineHandle& Start(FCsResource_CoroutinePayload* PayloadContainer);
	const FCsRoutineHandle& Start(FCsCoroutinePayload* Payload);

	const FCsRoutineHandle& StartChild(FCsResource_CoroutinePayload* PayloadContainer);
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

	/**
	*
	*
	* @param Group
	* return
	*/
	FCsResource_CoroutinePayload* AllocatePayloadContainer(const FECsUpdateGroup& Group);

	/**
	*
	*
	* @param Group
	* return
	*/
	FCsCoroutinePayload* AllocatePayload(const FECsUpdateGroup& Group);

#pragma endregion Payload

// Message
public:

	void BroadcastMessage(const FECsUpdateGroup& Group, const ECsCoroutineMessage& MessageType, const FName& Message, void* InOwner = nullptr);

#pragma endregion Message
};