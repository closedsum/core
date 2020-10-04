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

private:

	typedef NCsCoroutine::EMessage MessageType;
	typedef NCsCoroutine::NPayload::FImpl PayloadType;
	typedef NCsCoroutine::NPayload::FResource PayloadResourceType;

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

	/** */
	TArray<FCsCoroutineSchedule> Schedules;

// Start
#pragma region
public:

	/**
	*
	*
	* @param PayloadContainer
	* return
	*/
	FORCEINLINE const FCsRoutineHandle& Start(PayloadResourceType* PayloadContainer)
	{
		PayloadType* Payload = PayloadContainer->Get();

		return Schedules[Payload->Group.GetValue()].Start(PayloadContainer);
	}

	/**
	*
	*
	* @param Payload
	* return
	*/
	FORCEINLINE const FCsRoutineHandle& Start(PayloadType* Payload)
	{
		return Schedules[Payload->Group.GetValue()].Start(Payload);
	}

	/**
	*
	*
	* @param PayloadContainer
	* return
	*/
	FORCEINLINE const FCsRoutineHandle& StartChild(PayloadResourceType* PayloadContainer)
	{
		PayloadType* Payload = PayloadContainer->Get();

		return Schedules[Payload->Group.GetValue()].StartChild(PayloadContainer);
	}

	/**
	*
	*
	* @param Payload
	* return
	*/
	FORCEINLINE const FCsRoutineHandle& StartChild(PayloadType* Payload)
	{
		return Schedules[Payload->Group.GetValue()].StartChild(Payload);
	}

#pragma endregion Start

// Update
#pragma region
public:

	/**
	*
	*
	* @param Group
	* @param DeltaTime
	*/
	FORCEINLINE void Update(const FECsUpdateGroup& Group, const FCsDeltaTime& DeltaTime)
	{
		Schedules[Group.GetValue()].Update(DeltaTime);
	}

#pragma endregion Update
	
// End
#pragma region
public:

	/**
	*
	*
	* @param Group
	*/
	FORCEINLINE void End(const FECsUpdateGroup& Group)
	{
		Schedules[Group.GetValue()].End();
	}

	/**
	*
	*
	* @param Group
	* @param Handle
	*/
	FORCEINLINE void End(const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle)
	{
		Schedules[Group.GetValue()].End(Handle);
	}


	/**
	*
	*/
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
	FORCEINLINE PayloadResourceType* AllocatePayloadContainer(const FECsUpdateGroup& Group)
	{
		return Schedules[Group.GetValue()].AllocatePayloadContainer();
	}

	/**
	*
	*
	* @param Group
	* return
	*/
	FORCEINLINE PayloadType* AllocatePayload(const FECsUpdateGroup& Group)
	{
		return Schedules[Group.GetValue()].AllocatePayload();
	}

#pragma endregion Payload

// Handle
#pragma region
public:

	FORCEINLINE bool IsHandleValid(const FECsUpdateGroup& Group, const FCsRoutineHandle& Handle) const
	{
		return Schedules[Group.GetValue()].GetRoutineContainer(Handle) != nullptr;
	}

#pragma endregion Handle

// Message
#pragma region
public:

	FORCEINLINE void BroadcastMessage(const FECsUpdateGroup& Group, const MessageType& Type, const FName& Message, void* InOwner = nullptr)
	{
		Schedules[Group.Value].BroadcastMessage(Type, Message, InOwner);
	}

#pragma endregion Message
};