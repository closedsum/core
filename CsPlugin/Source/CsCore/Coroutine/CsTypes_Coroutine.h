// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"
#include "Coroutine/pt.h"
#include "Managers/Time/CsTypes_Time.h"
#include "Utility/CsWeakObjectPtr.h"

#include "CsTypes_Coroutine.generated.h"
#pragma once

// CoroutineState
#pragma region

UENUM(BlueprintType)
enum class ECsCoroutineState : uint8
{
	Free					UMETA(DisplayName = "Free"),
	Init					UMETA(DisplayName = "Init"),
	Run						UMETA(DisplayName = "Run"),
	End						UMETA(DisplayName = "End"),
	ECsCoroutineState_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsCoroutineState : public TCsEnumMap<ECsCoroutineState>
{
	CS_ENUM_MAP_BODY(EMCsCoroutineState, ECsCoroutineState)
};

namespace NCsCoroutineState
{
	typedef ECsCoroutineState Type;

	namespace Ref
	{
		extern CSCORE_API const Type Free;
		extern CSCORE_API const Type Init;
		extern CSCORE_API const Type Run;
		extern CSCORE_API const Type End;
		extern CSCORE_API const Type ECsCoroutineState_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion CoroutineState

// CoroutineMessage
#pragma region

UENUM(BlueprintType)
enum class ECsCoroutineMessage : uint8
{
	Notify					UMETA(DisplayName = "Notify"),
	Listen					UMETA(DisplayName = "Listen"),
	Stop					UMETA(DisplayName = "Stop"),
	ECsCoroutineMessage_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsCoroutineMessage : public TCsEnumMap<ECsCoroutineMessage>
{
	CS_ENUM_MAP_BODY(EMCsCoroutineMessage, ECsCoroutineMessage)
};

namespace NCsCoroutineMessage
{
	typedef ECsCoroutineMessage Type;

	namespace Ref
	{
		extern CSCORE_API const Type Notify;
		extern CSCORE_API const Type Listen;
		extern CSCORE_API const Type Stop;
		extern CSCORE_API const Type ECsCoroutineMessage_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion CoroutineMessage

// CoroutineEndReason
#pragma region

UENUM(BlueprintType)
enum class ECsCoroutineEndReason : uint8
{
	EndOfExecution				UMETA(DisplayName = "End of Execution"),
	StopMessage					UMETA(DisplayName = "Stop Message"),
	StopCondition				UMETA(DisplayName = "Stop Condition"),
	OwnerIsInvalid				UMETA(DisplayName = "Owner is Invalid"),
	Parent						UMETA(DisplayName = "Parent"),
	UniqueInstance				UMETA(DisplayName = "Unique Instance"),
	Shutdown					UMETA(DisplayName = "Shutdown"),
	Manual						UMETA(DisplayName = "Manual"),
	ECsCoroutineEndReason_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsCoroutineEndReason : public TCsEnumMap<ECsCoroutineEndReason>
{
	CS_ENUM_MAP_BODY(EMCsCoroutineEndReason, ECsCoroutineEndReason)
};

namespace NCsCoroutineEndReason
{
	typedef ECsCoroutineEndReason Type;

	namespace Ref
	{
		extern CSCORE_API const Type EndOfExecution;
		extern CSCORE_API const Type StopMessage;
		extern CSCORE_API const Type StopCondition;
		extern CSCORE_API const Type OwnerIsInvalid;
		extern CSCORE_API const Type Parent;
		extern CSCORE_API const Type UniqueInstance;
		extern CSCORE_API const Type Shutdown;
		extern CSCORE_API const Type Manual;
		extern CSCORE_API const Type ECsCoroutineEndReason_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion CoroutineEndReason

// CoroutineTransaction
#pragma region

UENUM(BlueprintType)
enum class ECsCoroutineTransaction : uint8
{
	Allocate					UMETA(DisplayName = "Allocate"),
	Start						UMETA(DisplayName = "Start"),
	End							UMETA(DisplayName = "End"),
	ECsCoroutineTransaction_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsCoroutineTransaction : public TCsEnumMap<ECsCoroutineTransaction>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsCoroutineTransaction, ECsCoroutineTransaction)
};

namespace NCsCoroutineTransaction
{
	typedef ECsCoroutineTransaction Type;

	namespace Ref
	{
		extern CSCORE_API const Type Allocate;
		extern CSCORE_API const Type Start;
		extern CSCORE_API const Type End;
		extern CSCORE_API const Type ECsCoroutineTransaction_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	namespace Str
	{
		typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

		extern CSCORE_API const TCsString Allocate;
		extern CSCORE_API const TCsString Start;
		extern CSCORE_API const TCsString End;
	}

	FORCEINLINE const FString& ToString(const Type& EType)
	{
		if (EType == Type::Allocate) { return Str::Allocate.Value; }
		if (EType == Type::Start) { return Str::Start.Value; }
		if (EType == Type::End) { return Str::End.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const FString& ToActionString(const Type& EType)
	{
		if (EType == Type::Allocate) { return Str::Allocate.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::Start) { return Str::Start.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		if (EType == Type::End) { return Str::End.Values[CS_FSTRING_ENUM_ALT_1_VALUE]; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString& String)
	{
		if (String == Str::Allocate) { return Ref::Allocate; }
		if (String == Str::Start) { return Ref::Start; }
		if (String == Str::End) { return Ref::End; }
		return Ref::ECsCoroutineTransaction_MAX;
	}
}

#define ECS_COROUTINE_TRANSACTION_MAX (uint8)NCsCoroutineTransaction::MAX

#pragma endregion CoroutineTransaction

USTRUCT(BlueprintType)
struct CSCORE_API FCsRoutineHandle
{
	GENERATED_USTRUCT_BODY()

public:

	static const FCsRoutineHandle Invalid;

public:

	UPROPERTY()
	int32 Index;

	UPROPERTY()
	FGuid Handle;

	FCsRoutineHandle() :
		Index(INDEX_NONE),
		Handle()
	{
	}

	friend uint32 GetTypeHash(const FCsRoutineHandle& InHandle)
	{
		return GetTypeHash(InHandle.Handle);
	}

	bool IsValid() const
	{
		return Index > INDEX_NONE && Handle.IsValid();
	}

	void New()
	{
		Handle.NewGuid();
	}

	void Reset()
	{
		Handle.Invalidate();
	}
};

class UObject;
class AActor;

struct CSCORE_API FCsRoutineOwner
{
private:

	void* Owner;

	UObject* Object;
	TWeakObjectPtr<UObject> WeakObject;
	bool bObject;

	AActor* Actor;

public:

	FCsRoutineOwner() :
		Owner(nullptr),
		Object(nullptr),
		WeakObject(nullptr),
		bObject(false),
		Actor(nullptr)
	{
	}

	~FCsRoutineOwner()
	{
	}

	void SetOwner(void* InOwner)
	{
		Owner = InOwner;
	}

	FORCEINLINE void* GetOwner()
	{
		return Owner;
	}

	void SetObject(UObject* InObject)
	{
		Object		= InObject;
		WeakObject  = Object;
		bObject		= true;
		Actor		= Cast<AActor>(Object);
	}

	FORCEINLINE UObject* GetObject()
	{
		return Object;
	}

	template<typename T>
	FORCEINLINE T* GetObject()
	{
		return Cast<T>(GetObject());
	}

	FORCEINLINE UObject* GetSafeObject()
	{
		return WeakObject.IsValid() ? WeakObject.Get() : nullptr;
	}

	template<typename T>
	FORCEINLINE T* GetSafeObject()
	{
		return Cast<T>(GetSafeObject());
	}

	FORCEINLINE bool IsObject() const
	{
		return bObject;
	}

	FORCEINLINE AActor* GetActor()
	{
		return Actor;
	}

	void Reset()
	{
		Owner = nullptr;
		Object = nullptr;
		WeakObject = nullptr;
		bObject = false;
		Actor = nullptr;
	}
};

// RoutineRegisterValue
#pragma region

UENUM(BlueprintType)
enum class ECsRoutineRegisterValueType : uint8
{
	Indexer							UMETA(DisplayName = "Indexer"),
	Counter							UMETA(DisplayName = "Counter"),
	Flag							UMETA(DisplayName = "Flag"),
	Timer							UMETA(DisplayName = "Timer"),
	DeltaTime						UMETA(DisplayName = "Delta Time"),
	Int								UMETA(DisplayName = "Int"),
	Float							UMETA(DisplayName = "Float"),
	Vector							UMETA(DisplayName = "Vector"),
	Rotator							UMETA(DisplayName = "Rotator"),
	Color							UMETA(DisplayName = "Color"),
	Name							UMETA(DisplayName = "Name"),
	String							UMETA(DisplayName = "String"),
	Object							UMETA(DisplayName = "Object"),
	Void							UMETA(DisplayName = "Void"),
	ECsRoutineRegisterValueType_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsRoutineRegisterValueType : public TCsEnumMap<ECsRoutineRegisterValueType>
{
	CS_ENUM_MAP_BODY(EMCsRoutineRegisterValueType, ECsRoutineRegisterValueType)
};

namespace NCsRoutineRegisterValueType
{
	typedef ECsRoutineRegisterValueType Type;

	namespace Ref
	{
		extern CSCORE_API const Type Indexer;
		extern CSCORE_API const Type Counter;
		extern CSCORE_API const Type Flag;
		extern CSCORE_API const Type Timer;
		extern CSCORE_API const Type DeltaTime;
		extern CSCORE_API const Type Int;
		extern CSCORE_API const Type Float;
		extern CSCORE_API const Type Vector;
		extern CSCORE_API const Type Rotator;
		extern CSCORE_API const Type Color;
		extern CSCORE_API const Type Name;
		extern CSCORE_API const Type String;
		extern CSCORE_API const Type Object;
		extern CSCORE_API const Type Void;
		extern CSCORE_API const Type ECsRoutineRegisterValueType_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	void SetDefaultValue(const Type& ValueType, void* Ptr);
	void SetValue(const Type& ValueType, void* From, void* To);

	template<typename ValueType>
	void SetValue_Internal(void* From, void* To)
	{
		ValueType* F = (ValueType*)From;
		ValueType* T = (ValueType*)To;
		*F			 = *T;
	}
}

#pragma endregion RoutineRegisterValue

struct CSCORE_API FCsRoutineRegisterInfo
{
public:

	ECsRoutineRegisterValueType ValueType;

	int32 Index;

	FCsRoutineRegisterInfo() :
		ValueType(ECsRoutineRegisterValueType::ECsRoutineRegisterValueType_MAX),
		Index(INDEX_NONE)
	{
	}

	~FCsRoutineRegisterInfo()
	{
	}
};

struct FCsRoutine;

// Run
DECLARE_DELEGATE_RetVal_OneParam(char, FCsCoroutine, FCsRoutine*);
// Stop Condition
DECLARE_DELEGATE_RetVal_OneParam(bool, FCsCoroutineStopCondition, FCsRoutine*);

#define CS_ROUTINE_MAX_TYPE 255
#define CS_ROUTINE_INDEXER_SIZE 4
#define CS_ROUTINE_COUNTER_SIZE 4
#define CS_ROUTINE_FLAG_SIZE 4
#define CS_ROUTINE_TIMER_SIZE 4
#define CS_ROUTINE_DELTA_TIME_SIZE 4
#define CS_ROUTINE_INT_SIZE 4
#define CS_ROUTINE_FLOAT_SIZE 4
#define CS_ROUTINE_VECTOR_SIZE 4
#define CS_ROUTINE_ROTATOR_SIZE 4
#define CS_ROUTINE_COLOR_SIZE 4
#define CS_ROUTINE_NAME_SIZE 4
#define CS_ROUTINE_STRING_SIZE 4
#define CS_ROUTINE_OBJECT_SIZE 4
#define CS_ROUTINE_VOID_POINTER_SIZE 4
#define CS_ROUTINE_END -1
#define CS_ROUTINE_FREE -2

struct CSCORE_API FCsCoroutinePayload
{
private:

	int32 Index;

public:

	FECsTimeGroup Group;

	FCsCoroutine Coroutine;

	FCsTime StartTime;

	FCsRoutineOwner Owner;

	TArray<FCsCoroutineStopCondition> Stops;

	FCsRoutineHandle ParentHandle;

	bool bDoInit;

	bool bPerformFirstRun;

	FName Name;

	FString NameAsString;

	TArray<FName> StopMessages;

public:

	FRsCoroutinePayload();

	~FRsCoroutinePayload() {}

	void SetIndex(const int32& InIndex);

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
	}

	void Reset();

// Registers
#pragma region
public:

	TArray<FCsRoutineRegisterInfo> RegisterInfos;
	TArray<TArray<void*>> Registers;

protected:

	TArray<TArray<bool>> RegisterFlags;

	TArray<int32, TFixedAllocator<CS_ROUTINE_INDEXER_SIZE>> Indexers;
	TArray<int32, TFixedAllocator<CS_ROUTINE_COUNTER_SIZE>> Counters;
	TArray<bool, TFixedAllocator<CS_ROUTINE_FLAG_SIZE>> Flags;
	TArray<FCsTime, TFixedAllocator<CS_ROUTINE_TIMER_SIZE>> Timers;
	TArray<FCsDeltaTime, TFixedAllocator<CS_ROUTINE_DELTA_TIME_SIZE>> DeltaTimes;
	TArray<int32, TFixedAllocator<CS_ROUTINE_INT_SIZE>> Ints;
	TArray<float, TFixedAllocator<CS_ROUTINE_FLOAT_SIZE>> Floats;
	TArray<FVector, TFixedAllocator<CS_ROUTINE_VECTOR_SIZE>> Vectors;
	TArray<FRotator, TFixedAllocator<CS_ROUTINE_ROTATOR_SIZE>> Rotators;
	TArray<FLinearColor, TFixedAllocator<CS_ROUTINE_COLOR_SIZE>> Colors;
	TArray<FName, TFixedAllocator<CS_ROUTINE_NAME_SIZE>> Names;
	TArray<FString, TFixedAllocator<CS_ROUTINE_STRING_SIZE>> Strings;
	TArray<TCsWeakObjectPtr<UObject>, TFixedAllocator<CS_ROUTINE_OBJECT_SIZE>> Objects;
	TArray<void*, TFixedAllocator<CS_ROUTINE_VOID_POINTER_SIZE>> VoidPointers;

	// Set
#pragma region
protected:

	FORCEINLINE void SetRegisterFlag(const ECsRoutineRegisterValueType& ValueType, const int32& InIndex)
	{
		if (!RegisterFlags[(uint8)ValueType][InIndex])
		{
			RegisterInfos.AddDefaulted();
			FCsRoutineRegisterInfo& Info = RegisterInfos.Last();
			Info.ValueType				 = ValueType;
			Info.Index					 = InIndex;
		}
	}

public:

	FORCEINLINE void SetValue_Indexer(const int32& InIndex, const int32& Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::Indexer, InIndex);
		Indexers[InIndex] = Value;
	}

	FORCEINLINE void SetValue_Counter(const int32& InIndex, const int32& Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::Counter, InIndex);
		Counters[InIndex] = Value;
	}

	FORCEINLINE void SetValue_Flag(const int32& InIndex, const bool& Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::Flag, InIndex);
		Flags[InIndex] = Value;
	}

	FORCEINLINE void SetValue_Timer(const int32& InIndex, const FCsTime& Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::Timer, InIndex);
		Timers[InIndex] = Value;
	}

	FORCEINLINE void SetValue_DeltaTime(const int32& InIndex, const FCsDeltaTime& Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::DeltaTime, InIndex);
		DeltaTimes[InIndex] = Value;
	}

	FORCEINLINE void SetValue_Int(const int32& InIndex, const int32& Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::Int, InIndex);
		Ints[InIndex] = Value;
	}

	FORCEINLINE void SetValue_Float(const int32& InIndex, const float& Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::Float, InIndex);
		Floats[InIndex] = Value;
	}

	FORCEINLINE void SetValue_Vector(const int32& InIndex, const FVector& Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::Vector, InIndex);
		Vectors[InIndex] = Value;
	}

	FORCEINLINE void SetValue_Rotator(const int32& InIndex, const FRotator& Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::Rotator, InIndex);
		Rotators[InIndex] = Value;
	}

	FORCEINLINE void SetValue_Color(const int32& InIndex, const FLinearColor& Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::Color, InIndex);
		Colors[InIndex] = Value;
	}

	FORCEINLINE void SetValue_Name(const int32& InIndex, const FName& Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::Indexer, InIndex);
		Names[InIndex] = Value;
	}

	FORCEINLINE void SetValue_String(const int32& InIndex, const FString& Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::Name, InIndex);
		Strings[InIndex] = Value;
	}

	FORCEINLINE void SetValue_Object(const int32& InIndex, UObject* Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::Object, InIndex);
		Objects[InIndex].Set(Value);
	}

	FORCEINLINE void SetValue_Void(const int32& InIndex, void* Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::Void, InIndex);
		VoidPointers[InIndex] = Value;
	}

#pragma endregion Set

#pragma endregion Registers
};

#define CS_COROUTINE_DECLARE(Func)	virtual void Func(); \
									static char Func##_Internal(struct FCsRoutine* r); \
									struct FCsRoutine* Func##_Internal_Routine;
#define CS_COROUTINE(Class, Func) char Class::Func(FCsRoutine* r)

#define CS_COROUTINE_INIT(r)  PT_INIT(&((r)->pt))
#define CS_COROUTINE_BEGIN(r)   { char PT_YIELD_FLAG = 1; LC_RESUME((&((r)->pt))->lc)
#define CS_COROUTINE_END(r)	(r)->State = ECsCoroutineState::End; LC_END((&((r)->pt))->lc); PT_YIELD_FLAG = 0; \
							PT_INIT(&((r)->pt)); return PT_ENDED; }			
#define CS_COROUTINE_EXIT(r)	PT_EXIT(&((r)->pt))
#define CS_COROUTINE_YIELD(r)	PT_YIELD(&((r)->pt));
#define CS_COROUTINE_WAIT_UNTIL(r, condition) PT_WAIT_UNTIL(&((r)->pt), condition);