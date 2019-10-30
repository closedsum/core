// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/MemoryResource/CsManager_MemoryResource.h"
#include "Types/CsTypes_Coroutine.h"

#include "Coroutine/CsCoroutineScheduler.h"

// Structs
#pragma region

	// Routine

struct FCsMemoryResource_Routine : public TCsMemoryResource<FCsRoutine>
{
};

struct FCsManager_Routine : public TCsManager_MemoryResource<FCsRoutine, FCsMemoryResource_Routine, CS_ROUTINE_POOL_SIZE>
{
};

	// Payload

struct FCsMemoryResource_CoroutinePayload : public TCsMemoryResource<FCsCoroutinePayload>
{
};

struct FCsManager_CoroutinePayload : public TCsManager_MemoryResource<FCsCoroutinePayload, FCsMemoryResource_CoroutinePayload, CS_ROUTINE_POOL_SIZE>
{
};

#pragma endregion Structs

class FCsCoroutineSchedule
{
public:

	FCsCoroutineSchedule()
	{

	}

	virtual ~FCsCoroutineSchedule()
	{

	}

public:

	FCsManager_Routine Manager_Routine;

	TLinkedList<FCsMemoryResource_Routine*> RoutinesToInitHead;
	TLinkedList<FCsMemoryResource_Routine*> RoutinesToRunHead;

// Payload
#pragma region
protected:

	FCsManager_CoroutinePayload Manager_CoroutinePayload;

public:

	FCsMemoryResource_CoroutinePayload* AllocatePayload()
	{
		return Manager_CoroutinePayload.Allocate();
	}

#pragma endregion Payload
};