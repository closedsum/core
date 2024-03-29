// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
#include "Coroutine/CsRoutine.h"

#define CS_ROUTINE_POOL_SIZE 2048
#define CS_COROUTINE_PAYLOAD_SIZE 64

// Structs
#pragma region

	// Routine
	
namespace NCsRoutine
{
	struct CSCORE_API FResource : public TCsResourceContainer<FCsRoutine>
	{
	};

	struct CSCORE_API FManager : public NCsResource::NManager::NValue::TFixed<FCsRoutine, FResource, CS_ROUTINE_POOL_SIZE>
	{
	};
}

	// Payload

namespace NCsCoroutine
{
	namespace NPayload
	{
		struct CSCORE_API FResource : public TCsResourceContainer<FImpl>
		{
		};

		struct CSCORE_API FManager : public NCsResource::NManager::NValue::TFixed<FImpl, FResource, CS_COROUTINE_PAYLOAD_SIZE>
		{
		};
	}
}

#pragma endregion Structs

class CSCORE_API FCsCoroutineSchedule
{
public:

	FCsCoroutineSchedule();

	virtual ~FCsCoroutineSchedule();

private:

	typedef NCsRoutine::FResource RoutineResourceType;
	typedef NCsRoutine::FManager RoutineManagerType;

	typedef NCsCoroutine::EMessage MessageType;
	typedef NCsCoroutine::ETransaction TransactionType;
	typedef NCsCoroutine::NPayload::FImpl PayloadType;
	typedef NCsCoroutine::NPayload::FResource PayloadResourceType;
	typedef NCsCoroutine::NPayload::FManager PayloadManagerType;

// Schedule
#pragma region
protected:

	/** */
	FECsUpdateGroup Group;

public:

	/**
	*
	*
	* @param InGroup
	*/
	void SetGroup(const FECsUpdateGroup& InGroup);

#pragma endregion Schedule

// Routine
#pragma region
protected:

	/** */
	RoutineManagerType Manager_Routine;

public:

	/**
	*
	*
	* @param Handle
	* return
	*/
	RoutineResourceType* GetRoutineContainer(const FCsRoutineHandle& Handle) const;

	/**
	*
	*
	* @param Handle
	* return
	*/
	FCsRoutine* GetRoutine(const FCsRoutineHandle& Handle) const;

#pragma endregion Routine

// Handle
#pragma region
public:

	FORCEINLINE bool IsHandleValid(const FCsRoutineHandle& Handle) const
	{
		return GetRoutineContainer(Handle) != nullptr;
	}

	bool IsRunning(const FCsRoutineHandle& Handle) const;

#pragma endregion Handle

// Start
#pragma region
public:

	/**
	*
	*
	* @param PayloadContainer
	* return
	*/
	const FCsRoutineHandle& Start(PayloadResourceType* PayloadContainer);

	/**
	*
	*
	* @param Payload
	* return
	*/
	const FCsRoutineHandle& Start(PayloadType* Payload);

	/**
	*
	*
	* @param PayloadContainer
	* return
	*/
	const FCsRoutineHandle& StartChild(PayloadResourceType* PayloadContainer);

	/**
	*
	*
	* @param Payload
	* return
	*/
	const FCsRoutineHandle& StartChild(PayloadType* Payload);

#pragma endregion Start

// End
#pragma region
public:

	/**
	* End all routines.
	*/
	bool End();

	/**
	* End the routine associated with the Handle.
	*
	* @param Handle		Handle to a routine.
	* return			Whether the routine has successful ended.
	*					NOTE: If the routine has already ended or send to queued to end, 
	*						  this will return false.
	*/
	bool End(const FCsRoutineHandle& Handle);

	/**
	* Check if a routine associated with the Handle has already ended.
	* NOTE: This returns True if Handle is NOT Valid.
	* 
	* @param Handle		Handle to a routine.
	* return			Whether the routine has already ended.
	*/
	bool HasEnded(const FCsRoutineHandle& Handle) const;

	/**
	* Check if a routine associated with the Handle has just ended.
	*
	* @param Handle		Handle to a routine.
	* return			Whether the routine has just ended.
	*/
	bool HasJustEnded(const FCsRoutineHandle& Handle) const;

private:

	/** Handles to End either beginning of the next Update or the end of the
		current Update.
		NOTE: This list is populated when a Routine is currently being Executed and
			  requested to End. */
	TArray<FCsRoutineHandle> QueueEndHandles;

#pragma endregion End

// Update
#pragma region
public:

	/**
	*
	*
	* @param DeltaTime
	*/
	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion Update

// Payload
#pragma region
protected:

	/** */
	PayloadManagerType Manager_Payload;

public:

	/**
	*
	*
	* return
	*/
	FORCEINLINE PayloadResourceType* AllocatePayloadContainer()
	{
		return Manager_Payload.Allocate();
	}

	/**
	*
	*
	* return
	*/
	FORCEINLINE PayloadType* AllocatePayload()
	{
		return Manager_Payload.AllocateResource();
	}

protected:

	/**
	*
	*
	* @param Payload
	* return
	*/
	PayloadResourceType* GetPayloadContainer(PayloadType* Payload);

#pragma endregion Payload

// Message
#pragma region
public:

	/**
	*
	*
	* @param Type
	* @param Message
	* @param Owner
	*/
	void BroadcastMessage(const MessageType& Type, const FName& Message, void* Owner = nullptr);

#pragma endregion Message

// Log
#pragma region
public:

	/**
	*
	*
	* @param FunctionName
	* @param Transaction
	* @param R
	*/
	void LogTransaction(const FString& FunctionName, const TransactionType& Transaction, FCsRoutine* R);

	/**
	*
	*/
	void LogRunning();

#pragma endregion Log
};