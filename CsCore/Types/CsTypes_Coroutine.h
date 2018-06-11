// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"
#include "Coroutine/pt.h"

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

typedef ECsCoroutineSchedule::Type TCsCoroutineSchedule;

struct CSCORE_API EMCsCoroutineSchedule : public TCsEnumMap<ECsCoroutineSchedule::Type>
{
protected:
	EMCsCoroutineSchedule() {}
	EMCsCoroutineSchedule(const EMCsCoroutineSchedule &) = delete;
	EMCsCoroutineSchedule(EMCsCoroutineSchedule &&) = delete;
public:
	~EMCsCoroutineSchedule() {}
private:
	static EMCsCoroutineSchedule* Instance;

public:
	static EMCsCoroutineSchedule& Get();
};

namespace ECsCoroutineSchedule
{
	namespace Ref
	{
		extern CSCORE_API const Type Tick;
		extern CSCORE_API const Type CalcCamera;
		extern CSCORE_API const Type LastTick;
		extern CSCORE_API const Type ECsCoroutineSchedule_MAX;
	}
}

#define ECS_COROUTINE_SCHEDULE_MAX (uint8)ECsCoroutineSchedule::ECsCoroutineSchedule_MAX

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
typedef ECsCoroutineMessage::Type TCsCoroutineMessage;

struct CSCORE_API EMCsCoroutineMessage : public TCsEnumMap<ECsCoroutineMessage::Type>
{
protected:
	EMCsCoroutineMessage() {}
	EMCsCoroutineMessage(const EMCsCoroutineMessage &) = delete;
	EMCsCoroutineMessage(EMCsCoroutineMessage &&) = delete;
public:
	~EMCsCoroutineMessage() {}
private:
	static EMCsCoroutineMessage* Instance;

public:
	static EMCsCoroutineMessage& Get();
};

namespace ECsCoroutineMessage
{
	namespace Ref
	{
		extern CSCORE_API const Type Notify;
		extern CSCORE_API const Type Listen;
		extern CSCORE_API const Type Stop;
		extern CSCORE_API const Type ECsCoroutineMessage_MAX;
	}
}

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

typedef ECsCoroutineEndReason::Type TCsCoroutineEndReason;

struct CSCORE_API EMCsCoroutineEndReason : public TCsEnumMap<ECsCoroutineEndReason::Type>
{
protected:
	EMCsCoroutineEndReason() {}
	EMCsCoroutineEndReason(const EMCsCoroutineEndReason &) = delete;
	EMCsCoroutineEndReason(EMCsCoroutineEndReason &&) = delete;
public:
	~EMCsCoroutineEndReason() {}
private:
	static EMCsCoroutineEndReason* Instance;

public:
	static EMCsCoroutineEndReason& Get();
};

namespace ECsCoroutineEndReason
{
	namespace Ref
	{
		extern CSCORE_API const Type EndOfExecution;
		extern CSCORE_API const Type StopMessage;
		extern CSCORE_API const Type StopCondition;
		extern CSCORE_API const Type Parent;
		extern CSCORE_API const Type UniqueInstance;
		extern CSCORE_API const Type Shutdown;
		extern CSCORE_API const Type Manual;
		extern CSCORE_API const Type ECsCoroutineEndReason_MAX;
	}
}

#define CS_ROUTINE_POOL_SIZE 2048
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
public:

	struct FCsRoutine* self;
	struct pt pt;
	struct FCsRoutine* parent;
	TArray<struct FCsRoutine*> children;
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
	float elapsedTime;
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

		Reset();
	}

	void Init(const TCsCoroutineSchedule &inScheduleType, const int32 &inPoolIndex)
	{
		self = this;
		scheduleType = inScheduleType;
		poolIndex = inPoolIndex;

		Reset();
	}

	void SetIndex(const int32 &inIndex)
	{
		index = inIndex;
	}

	int32 GetIndex()
	{
		return index;
	}

	void IncrementIndex()
	{
		index++;
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
		nameAsString = ECsCached::Str::Empty;
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
		elapsedTime = 0.0f;
		tickCount = 0;
		delay = 0.0f;
		endReason = ECsCoroutineEndReason::ECsCoroutineEndReason_MAX;

		for (int32 i = 0; i < CS_ROUTINE_INDEXER_SIZE; ++i)
		{
			indexers[i] = 0;
		}

		for (int32 i = 0; i < CS_ROUTINE_COUNTER_SIZE; ++i)
		{
			counters[i] = 0;
		}

		for (int32 i = 0; i < CS_ROUTINE_FLAG_SIZE; ++i)
		{
			flags[i] = false;
		}

		for (int32 i = 0; i < CS_ROUTINE_TIMER_SIZE; ++i)
		{
			timers[i] = 0.0f;
		}

		for (int32 i = 0; i < CS_ROUTINE_INT_SIZE; ++i)
		{
			ints[i] = 0;
		}

		for (int32 i = 0; i < CS_ROUTINE_FLOAT_SIZE; ++i)
		{
			floats[i] = 0.0f;
		}

		for (int32 i = 0; i < CS_ROUTINE_VECTOR_SIZE; ++i)
		{
			vectors[i] = FVector::ZeroVector;
		}

		for (int32 i = 0; i < CS_ROUTINE_COLOR_SIZE; ++i)
		{
			colors[i] = FLinearColor::White;
		}

		for (int32 i = 0; i < CS_ROUTINE_STRING_SIZE; ++i)
		{
			strings[i] = TEXT("");
		}

		for (int32 i = 0; i < CS_ROUTINE_OBJECT_SIZE; ++i)
		{
			objects[i].Reset();
			objects[i] = nullptr;
		}

		for (int32 i = 0; i < CS_ROUTINE_VOID_POINTER_SIZE; ++i)
		{
			voidPointers[i] = nullptr;
		}

		for (int32 i = 0; i < CS_ROUTINE_VOID_DOUBLE_POINTER_SIZE; ++i)
		{
			voidDoublePointers[i] = nullptr;
		}

		stopMessages.Reset();
		stopMessages_recieved.Reset();
	}

	void Run(const float &inDeltaSeconds)
	{
		const int32 count = stopMessages_recieved.Num();

		for (int32 i = 0; i < count; ++i)
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
		elapsedTime += deltaSeconds;
		++tickCount;
		(*coroutine)(self);

		if (index == CS_ROUTINE_END)
			End(ECsCoroutineEndReason::EndOfExecution);
	}

	AActor* GetActor()
	{
		return a.IsValid() ? a.Get() : nullptr;
	}

	template<typename T>
	T* GetActor()
	{
		return Cast<T>(GetActor());
	}

	UObject* GetRObject()
	{
		return o.IsValid() ? o.Get() : nullptr;
	}

	template<typename T>
	T* GetRObject()
	{
		return Cast<T>(GetRObject());
	}

	UObject* GetOwner()
	{
		return owner.IsValid() ? owner.Get() : nullptr;
	}

	template<typename T>
	T* GetOwner()
	{
		Cast<T>(GetOwner());
	}

	UObject* GetObjectAt(const uint8 &inIndex)
	{
		return objects[inIndex].IsValid() ? objects[inIndex].Get() : nullptr;
	}

	template<typename T>
	T* GetObjectAt(const uint8 &inIndex)
	{
		return Cast<T>(GetObjectAt(inIndex));
	}

	void AddChild(struct FCsRoutine* child)
	{
		child->parent = self;
		children.Add(child);
	}

	void EndChildren()
	{
		const int32 count = children.Num();

		for (int32 i = 0; i < count; ++i)
		{
			children[i]->End(ECsCoroutineEndReason::Parent);
		}
		children.Reset();
	}

	void EndChild(struct FCsRoutine* child)
	{
		const int32 count = children.Num();

		for (int32 i = count - 1; i >= 0; --i)
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