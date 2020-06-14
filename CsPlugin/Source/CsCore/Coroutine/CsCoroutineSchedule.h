// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
#include "Coroutine/CsRoutine.h"

#define CS_ROUTINE_POOL_SIZE 2048
#define CS_COROUTINE_PAYLOAD_SIZE 64

// Structs
#pragma region

	// Routine

struct CSCORE_API FCsResource_Routine : public TCsResourceContainer<FCsRoutine>
{
};

struct CSCORE_API FCsManager_Routine : public TCsManager_ResourceValueType_Fixed<FCsRoutine, FCsResource_Routine, CS_ROUTINE_POOL_SIZE>
{
};

	// Payload

struct CSCORE_API FCsResource_CoroutinePayload : public TCsResourceContainer<FCsCoroutinePayload>
{
};

struct CSCORE_API FCsManager_CoroutinePayload : public TCsManager_ResourceValueType_Fixed<FCsCoroutinePayload, FCsResource_CoroutinePayload, CS_COROUTINE_PAYLOAD_SIZE>
{
};

#pragma endregion Structs

class CSCORE_API FCsCoroutineSchedule
{
public:

	FCsCoroutineSchedule();

	virtual ~FCsCoroutineSchedule();

// Schedule
#pragma region
protected:

	FECsUpdateGroup Group;

public:

	void SetGroup(const FECsUpdateGroup& InGroup);

#pragma endregion Schedule

// Routine
#pragma region
protected:

	FCsManager_Routine Manager_Routine;

public:

	FCsResource_Routine* GetRoutineContainer(const FCsRoutineHandle& Handle);
	FCsRoutine* GetRoutine(const FCsRoutineHandle& Handle);

#pragma endregion Routine

// Start
#pragma region
public:

	const FCsRoutineHandle& Start(FCsResource_CoroutinePayload* PayloadContainer);
	const FCsRoutineHandle& Start(FCsCoroutinePayload* Payload);

	const FCsRoutineHandle& StartChild(FCsResource_CoroutinePayload* PayloadContainer);
	const FCsRoutineHandle& StartChild(FCsCoroutinePayload* Payload);

#pragma endregion Start

// End
#pragma region
public:

	void End();
	void End(const FCsRoutineHandle& Handle);

#pragma endregion End

// Update
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion Update

// Payload
#pragma region
protected:

	FCsManager_CoroutinePayload Manager_Payload;

public:

	FORCEINLINE FCsResource_CoroutinePayload* AllocatePayloadContainer()
	{
		return Manager_Payload.Allocate();
	}

	FORCEINLINE FCsCoroutinePayload* AllocatePayload()
	{
		return Manager_Payload.AllocateResource();
	}

protected:

	FCsResource_CoroutinePayload* GetPayloadContainer(FCsCoroutinePayload* Payload);

#pragma endregion Payload

// Message
#pragma region
public:

	void BroadcastMessage(const ECsCoroutineMessage& MessageType, const FName& Message, void* Owner = nullptr);

#pragma endregion Message

// Log
#pragma region
public:

	void LogTransaction(const FString& FunctionName, const ECsCoroutineTransaction& Transaction, FCsRoutine* R);

	void LogRunning();

#pragma endregion Log
};