// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Coroutine.h"

// CoroutineSchedule
EMCsCoroutineSchedule* EMCsCoroutineSchedule::Instance;

EMCsCoroutineSchedule& EMCsCoroutineSchedule::Get()
{
	if (!Instance)
		Instance = new EMCsCoroutineSchedule();
	return *Instance;
}

namespace NCsCoroutineSchedule
{
	namespace Ref
	{
		CSCORE_API const Type Tick = EMCsCoroutineSchedule::Get().Add(Type::Tick, TEXT("Tick"));
		CSCORE_API const Type CalcCamera = EMCsCoroutineSchedule::Get().Add(Type::CalcCamera, TEXT("CalcCamera"));
		CSCORE_API const Type LastTick = EMCsCoroutineSchedule::Get().Add(Type::LastTick, TEXT("LastTick"));
		CSCORE_API const Type ECsCoroutineSchedule_MAX = EMCsCoroutineSchedule::Get().Add(Type::ECsCoroutineSchedule_MAX, TEXT("ECsCoroutineSchedule_MAX"), TEXT("MAX"));
	}
}

// CoroutineMessage
EMCsCoroutineMessage* EMCsCoroutineMessage::Instance;

EMCsCoroutineMessage& EMCsCoroutineMessage::Get()
{
	if (!Instance)
		Instance = new EMCsCoroutineMessage();
	return *Instance;
}

namespace ECsCoroutineMessage
{
	namespace Ref
	{
		CSCORE_API const Type Notify = EMCsCoroutineMessage::Get().Add(Type::Notify, TEXT("Notify"));
		CSCORE_API const Type Listen = EMCsCoroutineMessage::Get().Add(Type::Listen, TEXT("Listen"));
		CSCORE_API const Type Stop = EMCsCoroutineMessage::Get().Add(Type::Stop, TEXT("Stop"));
		CSCORE_API const Type ECsCoroutineMessage_MAX = EMCsCoroutineMessage::Get().Add(Type::ECsCoroutineMessage_MAX, TEXT("ECsCoroutineMessage_MAX"), TEXT("MAX"));
	}
}

// CoroutineEndReason
EMCsCoroutineEndReason* EMCsCoroutineEndReason::Instance;

EMCsCoroutineEndReason& EMCsCoroutineEndReason::Get()
{
	if (!Instance)
		Instance = new EMCsCoroutineEndReason();
	return *Instance;
}

namespace ECsCoroutineEndReason
{
	namespace Ref
	{
		CSCORE_API const Type EndOfExecution = EMCsCoroutineEndReason::Get().Add(Type::EndOfExecution, TEXT("EndOfExecution"), TEXT("End of Execution"));
		CSCORE_API const Type StopMessage = EMCsCoroutineEndReason::Get().Add(Type::StopMessage, TEXT("StopMessage"), TEXT("Stop Message"));
		CSCORE_API const Type StopCondition = EMCsCoroutineEndReason::Get().Add(Type::StopCondition, TEXT("StopCondition"), TEXT("Stop Condition"));
		CSCORE_API const Type Parent = EMCsCoroutineEndReason::Get().Add(Type::Parent, TEXT("Parent"));
		CSCORE_API const Type UniqueInstance = EMCsCoroutineEndReason::Get().Add(Type::UniqueInstance, TEXT("UniqueInstance"), TEXT("Unique Instance"));
		CSCORE_API const Type Shutdown = EMCsCoroutineEndReason::Get().Add(Type::Shutdown, TEXT("Shutdown"));
		CSCORE_API const Type Manual = EMCsCoroutineEndReason::Get().Add(Type::Manual, TEXT("Manual"));
		CSCORE_API const Type ECsCoroutineEndReason_MAX = EMCsCoroutineEndReason::Get().Add(Type::ECsCoroutineEndReason_MAX, TEXT("ECsCoroutineEndReason_MAX"), TEXT("MAX"));
	}
}