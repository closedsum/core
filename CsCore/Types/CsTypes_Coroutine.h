// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Coroutine.generated.h"
#pragma once

// Coroutine
#pragma region

UENUM(BlueprintType)
namespace ECsCoroutineSchedule
{
	enum Type
	{
		Tick						UMETA(DisplayName = "Tick"),
		CalcCamera					UMETA(DisplayName = "CalcCamera"),
		LastTick					UMETA(DisplayName = "LastTick"),
		ECsCoroutineSchedule_MAX	UMETA(Hidden),
	};
}

namespace ECsCoroutineSchedule
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Tick = TCsString(TEXT("Tick"), TEXT("tick"));
		const TCsString CalcCamera = TCsString(TEXT("CalcCamera"), TEXT("calccamera"));
		const TCsString LastTick = TCsString(TEXT("LastTick"), TEXT("lasttick"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Tick) { return Str::Tick.Value; }
		if (EType == Type::CalcCamera) { return Str::CalcCamera.Value; }
		if (EType == Type::LastTick) { return Str::LastTick.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Tick) { return Type::Tick; }
		if (String == Str::CalcCamera) { return Type::CalcCamera; }
		if (String == Str::LastTick) { return Type::LastTick; }
		return Type::ECsCoroutineSchedule_MAX;
	}
}

#define ECS_COROUTINE_SCHEDULE_MAX (uint8)ECsCoroutineSchedule::ECsCoroutineSchedule_MAX
typedef TEnumAsByte<ECsCoroutineSchedule::Type> TCsCoroutineSchedule;

UENUM(BlueprintType)
namespace ECsCoroutineMessage
{
	enum Type
	{
		Notify					UMETA(DisplayName = "Notify"),
		Listen					UMETA(DisplayName = "Listen"),
		Stop					UMETA(DisplayName = "Stop"),
		ECsCoroutineMessage_MAX	UMETA(Hidden),
	};
}

namespace ECsCoroutineMessage
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Notify = TCsString(TEXT("Notify"), TEXT("notify"));
		const TCsString Listen = TCsString(TEXT("Listen"), TEXT("listen"));
		const TCsString Stop = TCsString(TEXT("Stop"), TEXT("stop"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Notify) { return Str::Notify.Value; }
		if (EType == Type::Listen) { return Str::Listen.Value; }
		if (EType == Type::Stop) { return Str::Stop.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Notify) { return Type::Notify; }
		if (String == Str::Listen) { return Type::Listen; }
		if (String == Str::Stop) { return Type::Stop; }
		return Type::ECsCoroutineMessage_MAX;
	}
}

#define ECS_COROUTINE_MESSAGE_MAX (uint8)ECsCoroutineMessage::ECsCoroutineMessage_MAX
typedef TEnumAsByte<ECsCoroutineMessage::Type> TCsCoroutineMessage;

UENUM(BlueprintType)
namespace ECsCoroutineEndReason
{
	enum Type
	{
		EndOfExecution				UMETA(DisplayName = "End of Execution"),
		StopMessage					UMETA(DisplayName = "Stop Message"),
		StopCondition				UMETA(DisplayName = "Stop Condition"),
		Parent						UMETA(DisplayName = "Parent"),
		UniqueInstance				UMETA(DisplayName = "Unique Instance"),
		Shutdown					UMETA(DisplayName = "Shutdown"),
		Manual						UMETA(DisplayName = "Manual"),
		ECsCoroutineEndReason_MAX	UMETA(Hidden),
	};
}

namespace ECsCoroutineEndReason
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString EndOfExecution = TCsString(TEXT("EndOfExecution"), TEXT("endofexecution"), TEXT("end of execution"));
		const TCsString StopMessage = TCsString(TEXT("StopMessage"), TEXT("stopmessage"), TEXT("stop message"));
		const TCsString StopCondition = TCsString(TEXT("StopCondition"), TEXT("stopcondition"), TEXT("stop condition"));
		const TCsString Parent = TCsString(TEXT("Parent"), TEXT("parent"), TEXT("parent"));
		const TCsString UniqueInstance = TCsString(TEXT("UniqueInstance"), TEXT("uniqueinstance"), TEXT("unique instance"));
		const TCsString Shutdown = TCsString(TEXT("Shutdown"), TEXT("shutdown"), TEXT("shutdown"));
		const TCsString Manual = TCsString(TEXT("Manual"), TEXT("manual"), TEXT("manual"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::EndOfExecution) { return Str::EndOfExecution.Value; }
		if (EType == Type::StopMessage) { return Str::StopMessage.Value; }
		if (EType == Type::StopCondition) { return Str::StopCondition.Value; }
		if (EType == Type::Parent) { return Str::Parent.Value; }
		if (EType == Type::UniqueInstance) { return Str::UniqueInstance.Value; }
		if (EType == Type::Shutdown) { return Str::Shutdown.Value; }
		if (EType == Type::Manual) { return Str::Manual.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::EndOfExecution) { return Type::EndOfExecution; }
		if (String == Str::StopMessage) { return Type::StopMessage; }
		if (String == Str::StopCondition) { return Type::StopCondition; }
		if (String == Str::Parent) { return Type::Parent; }
		if (String == Str::UniqueInstance) { return Type::UniqueInstance; }
		if (String == Str::Shutdown) { return Type::Shutdown; }
		if (String == Str::Manual) { return Type::Manual; }
		return Type::ECsCoroutineEndReason_MAX;
	}
}

#define ECS_COROUTINE_END_REASON_MAX (uint8)ECsCoroutineEndReason::ECsCoroutineEndReason_MAX
typedef TEnumAsByte<ECsCoroutineEndReason::Type> TCsCoroutineEndReason;

#define CS_ROUTINE_POOL_SIZE 256
#define CS_ROUTINE_INDEXER_SIZE 4
#define CS_ROUTINE_COUNTER_SIZE 4
#define CS_ROUTINE_FLAG_SIZE 16
#define CS_ROUTINE_TIMER_SIZE 4
#define CS_ROUTINE_INT_SIZE 4
#define CS_ROUTINE_FLOAT_SIZE 4
#define CS_ROUTINE_VECTOR_SIZE 4
#define CS_ROUTINE_COLOR_SIZE 4
#define CS_ROUTINE_STRING_SIZE 4
#define CS_ROUTINE_OBJECT_SIZE 4
#define CS_ROUTINE_VOID_POINTER_SIZE 4
#define CS_ROUTINE_VOID_DOUBLE_POINTER_SIZE 4
#define CS_ROUTINE_MAX_TYPE 255
#define CS_ROUTINE_END -1
#define CS_ROUTINE_FREE -2

typedef char(*CsCoroutine)(struct FCsRoutine*);
typedef void(*CsCoroutineStopCondition)(struct FCsRoutine*);
typedef void(*CsAddRoutine)(class UObject*, struct FCsRoutine*, const uint8&);
typedef void(*CsRemoveRoutine)(class UObject*, struct FCsRoutine*, const uint8&);

struct FCsRoutine
{
	struct FCsRoutine* self;
	struct pt pt;
	struct FCsRoutine* parent;
	TArray<struct FCsRoutine*> children;
	class UCsCoroutineScheduler* scheduler;
	TCsCoroutineSchedule scheduleType;
	CsCoroutine coroutine;
	CsCoroutineStopCondition stopCondition;
	int32 poolIndex;
	int32 index;
	FName name;
	FString nameAsString;
	uint8 type;
	TWeakObjectPtr<AActor> a;
	TWeakObjectPtr<UObject> o;
	TWeakObjectPtr<UObject> owner;
	struct FCsRoutine** ownerMemberRoutine;
	CsAddRoutine addRoutine;
	CsRemoveRoutine removeRoutine;
	float startTime;
	float deltaSeconds;
	int32 tickCount;
	float delay;

	TArray<FName> stopMessages;
	TArray<FName> stopMessages_recieved;

	TCsCoroutineEndReason endReason;

	int32 indexers[CS_ROUTINE_INDEXER_SIZE];
	int32 counters[CS_ROUTINE_COUNTER_SIZE];
	bool flags[CS_ROUTINE_FLAG_SIZE];
	float timers[CS_ROUTINE_TIMER_SIZE];
	int32 ints[CS_ROUTINE_INT_SIZE];
	float floats[CS_ROUTINE_FLOAT_SIZE];
	FVector vectors[CS_ROUTINE_VECTOR_SIZE];
	FLinearColor colors[CS_ROUTINE_COLOR_SIZE];
	FString strings[CS_ROUTINE_STRING_SIZE];
	TWeakObjectPtr<UObject> objects[CS_ROUTINE_OBJECT_SIZE];
	void* voidPointers[CS_ROUTINE_VOID_POINTER_SIZE];
	void** voidDoublePointers[CS_ROUTINE_VOID_DOUBLE_POINTER_SIZE];

	FCsRoutine()
	{
		self = nullptr;
		parent = nullptr;

		children.Reset();

		scheduler = nullptr;

		Reset();
	}

	void Init(UCsCoroutineScheduler* inScheduler, const TCsCoroutineSchedule &inScheduleType, const int32 &inPoolIndex)
	{
		self = this;
		scheduler = inScheduler;
		scheduleType = inScheduleType;
		poolIndex = inPoolIndex;

		Reset();
	}

	bool IsValid()
	{
		if (!self)
			return false;
		if (this != self)
			return false;
		return true;
	}

	void Start(CsCoroutine inCoroutine, const float &inStartTime)
	{
		Start(inCoroutine, nullptr, nullptr, nullptr, inStartTime);
	}

	void Start(CsCoroutine inCoroutine, AActor* inActor, const float &inStartTime)
	{
		Start(inCoroutine, nullptr, inActor, nullptr, inStartTime);
	}

	void Start(CsCoroutine inCoroutine, UObject* inObject, const float &inStartTime)
	{
		Start(inCoroutine, nullptr, nullptr, inObject, inStartTime);
	}

	void Start(CsCoroutine inCoroutine, AActor* inActor, UObject* inObject, const float &inStartTime)
	{
		Start(inCoroutine, nullptr, inActor, inObject, inStartTime);
	}

	void Start(CsCoroutine inCoroutine, CsCoroutineStopCondition inStopCondition, AActor* inActor, UObject* inObject, const float &inStartTime)
	{
		Start(inCoroutine, inStopCondition, inActor, inObject, inStartTime, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
	}

	void Start(CsCoroutine inCoroutine, CsCoroutineStopCondition inStopCondition, AActor* inActor, UObject* inObject, const float &inStartTime, FCsRoutine** inOwnerMemberRoutine)
	{
		Start(inCoroutine, inStopCondition, inActor, inObject, inStartTime, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);

		ownerMemberRoutine = inOwnerMemberRoutine;
		*ownerMemberRoutine = self;
	}

	void Start(CsCoroutine inCoroutine, CsCoroutineStopCondition inStopCondition, AActor* inActor, UObject* inObject, const float &inStartTime, CsAddRoutine inAddRoutine, CsRemoveRoutine inRemoveRoutine, const uint8 &inType)
	{
		coroutine = inCoroutine;
		stopCondition = inStopCondition;
		a = inActor;
		o = inObject;
		startTime = inStartTime;
		addRoutine = inAddRoutine;
		removeRoutine = inRemoveRoutine;
		type = inType;

		if (GetActor())
		{
			owner = a;
		}
		else
			if (GetRObject())
			{
				owner = o;
			}

		if (GetOwner() && addRoutine)
			(*addRoutine)(GetOwner(), self, type);
	}

	void End(const TCsCoroutineEndReason &inEndReason)
	{
		if (ownerMemberRoutine)
			*ownerMemberRoutine = nullptr;
		else
			if (GetOwner() && removeRoutine)
				(*removeRoutine)(GetOwner(), self, type);
		EndChildren();
		index = CS_ROUTINE_END;
		endReason = inEndReason;
	}

	bool HasEnded()
	{
		return index == CS_ROUTINE_END || index == CS_ROUTINE_FREE;
	}

	void Reset()
	{
		if (parent)
		{
			parent->children.Remove(self);
		}

		parent = nullptr;

		EndChildren();

		coroutine = nullptr;
		stopCondition = nullptr;
		index = CS_ROUTINE_FREE;
		name = NAME_None;
		nameAsString = ECsCachedString::Str::Empty;
		type = CS_ROUTINE_MAX_TYPE;
		a.Reset();
		a = nullptr;
		o.Reset();
		o = nullptr;
		owner.Reset();
		owner = nullptr;
		addRoutine = nullptr;
		removeRoutine = nullptr;
		ownerMemberRoutine = nullptr;
		startTime = 0.0f;
		tickCount = 0;
		delay = 0.0f;
		endReason = ECsCoroutineEndReason::ECsCoroutineEndReason_MAX;

		for (int32 i = 0; i < CS_ROUTINE_INDEXER_SIZE; i++)
		{
			indexers[i] = 0;
		}

		for (int32 i = 0; i < CS_ROUTINE_COUNTER_SIZE; i++)
		{
			counters[i] = 0;
		}

		for (int32 i = 0; i < CS_ROUTINE_FLAG_SIZE; i++)
		{
			flags[i] = false;
		}

		for (int32 i = 0; i < CS_ROUTINE_TIMER_SIZE; i++)
		{
			timers[i] = 0.0f;
		}

		for (int32 i = 0; i < CS_ROUTINE_INT_SIZE; i++)
		{
			ints[i] = 0;
		}

		for (int32 i = 0; i < CS_ROUTINE_FLOAT_SIZE; i++)
		{
			floats[i] = 0.0f;
		}

		for (int32 i = 0; i < CS_ROUTINE_VECTOR_SIZE; i++)
		{
			vectors[i] = FVector::ZeroVector;
		}

		for (int32 i = 0; i < CS_ROUTINE_COLOR_SIZE; i++)
		{
			colors[i] = FLinearColor::White;
		}

		for (int32 i = 0; i < CS_ROUTINE_STRING_SIZE; i++)
		{
			strings[i] = TEXT("");
		}

		for (int32 i = 0; i < CS_ROUTINE_OBJECT_SIZE; i++)
		{
			objects[i].Reset();
			objects[i] = nullptr;
		}

		for (int32 i = 0; i < CS_ROUTINE_VOID_POINTER_SIZE; i++)
		{
			voidPointers[i] = nullptr;
		}

		for (int32 i = 0; i < CS_ROUTINE_VOID_DOUBLE_POINTER_SIZE; i++)
		{
			voidDoublePointers[i] = nullptr;
		}

		stopMessages.Reset();
		stopMessages_recieved.Reset();
	}

	void Run(const float &inDeltaSeconds)
	{
		const int32 count = stopMessages_recieved.Num();

		for (int32 i = 0; i < count; i++)
		{
			if (stopMessages.Find(stopMessages_recieved[i]) != INDEX_NONE)
			{
				stopMessages.Reset();
				End(ECsCoroutineEndReason::StopMessage);
				break;
			}
		}
		stopMessages_recieved.Reset();

		if (stopCondition)
			(*stopCondition)(self);

		if (index == CS_ROUTINE_END)
		{
			if (endReason == ECsCoroutineEndReason::ECsCoroutineEndReason_MAX)
				End(ECsCoroutineEndReason::EndOfExecution);
			return;
		}
		deltaSeconds = inDeltaSeconds;
		tickCount++;
		(*coroutine)(self);

		if (index == CS_ROUTINE_END)
			End(ECsCoroutineEndReason::EndOfExecution);
	}

	AActor* GetActor()
	{
		return a.IsValid() ? a.Get() : nullptr;
	}

	UObject* GetRObject()
	{
		return o.IsValid() ? o.Get() : nullptr;
	}

	UObject* GetOwner()
	{
		return owner.IsValid() ? owner.Get() : nullptr;
	}

	void AddChild(struct FCsRoutine* child)
	{
		child->parent = self;
		children.Add(child);
	}

	void EndChildren()
	{
		const int32 count = children.Num();

		for (int32 i = 0; i < count; i++)
		{
			children[i]->End(ECsCoroutineEndReason::Parent);
		}
		children.Reset();
	}

	void EndChild(struct FCsRoutine* child)
	{
		const int32 count = children.Num();

		for (int32 i = count - 1; i >= 0; i--)
		{
			if (child == children[i])
			{
				child->End(ECsCoroutineEndReason::Parent);
				children.RemoveAt(i);
				break;
			}
		}
	}

	void AddMessage(const TCsCoroutineMessage &MessageType, const FName &Message)
	{
		if (MessageType == ECsCoroutineMessage::Stop)
		{
			if (stopMessages.Find(Message) == INDEX_NONE)
				stopMessages.Add(Message);
		}
	}

	void ReceiveMessage(const TCsCoroutineMessage &MessageType, const FName &Message)
	{
		if (MessageType == ECsCoroutineMessage::Stop)
		{
			if (stopMessages_recieved.Find(Message) == INDEX_NONE)
				stopMessages_recieved.Add(Message);
		}
	}
};

#define CS_COROUTINE_DECLARE(Func)	virtual void Func(); \
									static char Func##_Internal(struct FCsRoutine* r); \
									struct FCsRoutine* Func##_Internal_Routine;
#define CS_COROUTINE(Class, Func) char Class::Func(FCsRoutine* r)

#define CS_COROUTINE_INIT(r)  PT_INIT(&((r)->pt))
#define CS_COROUTINE_BEGIN(r)   { char PT_YIELD_FLAG = 1; LC_RESUME((&((r)->pt))->lc)
#define CS_COROUTINE_END(r)	(r)->index = CS_ROUTINE_END; LC_END((&((r)->pt))->lc); PT_YIELD_FLAG = 0; \
							PT_INIT(&((r)->pt)); return PT_ENDED; }			
#define CS_COROUTINE_EXIT(r)	PT_EXIT(&((r)->pt))
#define CS_COROUTINE_YIELD(r)	PT_YIELD(&((r)->pt));
#define CS_COROUTINE_WAIT_UNTIL(r, condition) PT_WAIT_UNTIL(&((r)->pt), condition);

#pragma endregion Coroutine