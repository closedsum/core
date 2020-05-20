// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsTypes_Coroutine.h"
#include "Coroutine/pt.h"
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

#pragma once

// Delegates
#pragma region

#pragma endregion Delegates

class UObject;
class AActor;

struct CSCORE_API FCsRoutine
{
public:

	FCsRoutine();
	
	~FCsRoutine();

public:

	struct pt pt;

	FECsUpdateGroup Group;

	FCsCoroutine Coroutine;

	// Time
#pragma region
public:

	FCsTime StartTime;
	FCsDeltaTime ElapsedTime;
	FCsDeltaTime DeltaTime;

	int32 TickCount;

	float Delay;

	FCsScopedTimerHandle RoutineScopedTimerHandle;
	FCsScopedTimerHandle CoroutineScopedTimerHandle;

#pragma endregion Time

public:

	FCsRoutineHandle Handle;

	TArray<FCsCoroutineAbortCondition> Aborts;

	TArray<FCsOnCoroutineAbort> OnAborts;

	ECsCoroutineState State;

// Index
#pragma region
private:

	int32 Index;

public:

	void SetIndex(const int32& InIndex);

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
	}

#pragma endregion Index

// Name
#pragma region
private:

	FString* Name;

	FName Name_Internal;

public:

	FORCEINLINE void SetName(const FString* InName)
	{
		Name = const_cast<FString*>(InName);
	}

	FORCEINLINE void SetFName(const FName& InName)
	{
		Name_Internal = InName;
	}

	FORCEINLINE const FString* GetName()
	{
		return Name;
	}

	FORCEINLINE const FName& GetFName()
	{
		return Name_Internal;
	}

#pragma endregion Name

public:

	void Init(FCsCoroutinePayload* Payload);

// Run
#pragma region
public:

	FORCEINLINE void StartUpdate()
	{
		State = ECsCoroutineState::Update;
	}

	void Update(const FCsDeltaTime& InDeltaTime);

#pragma endregion Run

// End
#pragma region
public:

	ECsCoroutineEndReason EndReason;

	void End(const ECsCoroutineEndReason& InEndReason);

	FORCEINLINE bool HasEnded() const
	{
		return State == ECsCoroutineState::End || State == ECsCoroutineState::Free;
	}

#pragma endregion End

public:

	void Reset();

// Owner
#pragma region
public:

	FCsRoutineOwner Owner;

	FORCEINLINE void* GetOwner()
	{
		return Owner.GetOwner();
	}

	template<typename T>
	FORCEINLINE T* GetOwner()
	{
		return (T*)GetOwner();
	}

	FORCEINLINE UObject* GetOwnerAsObject()
	{
		return Owner.GetObject();
	}

	template<typename T>
	FORCEINLINE T* GetOwnerAsObject()
	{
		return Cast<T>(GetOwnerAsObject());
	}

	FORCEINLINE AActor* GetOwnerAsActor()
	{
		return Owner.GetActor();
	}

#pragma endregion Owner

// Children
#pragma region
public:

	FCsRoutine* Parent;

	TArray<FCsRoutine*> Children;

	void AddChild(FCsRoutine* Child);

	FORCEINLINE FCsRoutine* GetLastChild()
	{
		return Parent->Children.Num() > CS_EMPTY ? Parent->Children.Last() : nullptr;
	}

	void EndChildren();

	void EndChild(FCsRoutine* Child);

#pragma endregion Children

// Registers
#pragma region
protected:

	TArray<FCsRoutineRegisterInfo> RegisterInfos;
	TArray<TArray<bool>> RegisterFlags;

	TArray<TArray<void*>> Registers;

	TArray<int32, TFixedAllocator<CS_ROUTINE_INDEXER_SIZE>> Indexers;
	TArray<int32, TFixedAllocator<CS_ROUTINE_COUNTER_SIZE>> Counters;
	TArray<bool, TFixedAllocator<CS_ROUTINE_FLAG_SIZE>> Flags;
	TArray<FCsTime, TFixedAllocator<CS_ROUTINE_TIMER_SIZE>> Timers;
	TArray<FCsDeltaTime, TFixedAllocator<CS_ROUTINE_DELTA_TIME_SIZE>> DeltaTimes;
	TArray<int32, TFixedAllocator<CS_ROUTINE_INT_SIZE>> Ints;
	TArray<float, TFixedAllocator<CS_ROUTINE_FLOAT_SIZE>> Floats;
	TArray<double, TFixedAllocator<CS_ROUTINE_FLOAT_SIZE>> Doubles;
	TArray<FVector, TFixedAllocator<CS_ROUTINE_VECTOR_SIZE>> Vectors;
	TArray<FRotator, TFixedAllocator<CS_ROUTINE_ROTATOR_SIZE>> Rotators;
	TArray<FLinearColor, TFixedAllocator<CS_ROUTINE_COLOR_SIZE>> Colors;
	TArray<FName, TFixedAllocator<CS_ROUTINE_NAME_SIZE>> Names;
	TArray<FString, TFixedAllocator<CS_ROUTINE_STRING_SIZE>> Strings;
	TArray<FString*, TFixedAllocator<CS_ROUTINE_STRING_SIZE>> StringPointers;
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
		SetRegisterFlag(ECsRoutineRegisterValueType::Timer, InIndex);
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

	FORCEINLINE void SetValue_Double(const int32& InIndex, const double& Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::Double, InIndex);
		Doubles[InIndex] = Value;
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
		SetRegisterFlag(ECsRoutineRegisterValueType::Name, InIndex);
		Names[InIndex] = Value;
	}

	FORCEINLINE void SetValue_String(const int32& InIndex, const FString& Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::String, InIndex);
		Strings[InIndex] = Value;
	}

	FORCEINLINE void SetValue_StringPtr(const int32& InIndex, FString* Value)
	{
		SetRegisterFlag(ECsRoutineRegisterValueType::StringPtr, InIndex);
		StringPointers[InIndex] = Value;
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

	// Get
#pragma region
public:

	FORCEINLINE int32& GetValue_Indexer(const int32& InIndex)
	{
		return Indexers[InIndex];
	}
	
	FORCEINLINE int32& GetValue_Counter(const int32& InIndex)
	{
		return Counters[InIndex];
	}
	
	FORCEINLINE bool& GetValue_Flag(const int32& InIndex)
	{
		return Flags[InIndex];
	}

	FORCEINLINE FCsTime& GetValue_Timer(const int32& InIndex)
	{
		return Timers[InIndex];
	}

	FORCEINLINE FCsDeltaTime& GetValue_DeltaTime(const int32& InIndex)
	{
		return DeltaTimes[InIndex];
	}

	FORCEINLINE int32& GetValue_Int(const int32& InIndex)
	{
		return Ints[InIndex];
	}

	FORCEINLINE float& GetValue_Float(const int32& InIndex)
	{
		return Floats[InIndex];
	}

	FORCEINLINE double& GetValue_Double(const int32& InIndex)
	{
		return Doubles[InIndex];
	}

	FORCEINLINE FVector& GetValue_Vector(const int32& InIndex)
	{
		return Vectors[InIndex];
	}

	FORCEINLINE FRotator& GetValue_Rotator(const int32& InIndex)
	{
		return Rotators[InIndex];
	}

	FORCEINLINE FLinearColor& GetValue_Color(const int32& InIndex)
	{
		return Colors[InIndex];
	}

	FORCEINLINE FName& GetValue_Name(const int32& InIndex)
	{
		return Names[InIndex];
	}

	FORCEINLINE FString& GetValue_String(const int32& InIndex)
	{
		return Strings[InIndex];
	}

	FORCEINLINE FString* GetValue_StringPtr(const int32& InIndex)
	{
		return StringPointers[InIndex];
	}

	FORCEINLINE TCsWeakObjectPtr<UObject>& GetValue_Object(const int32& InIndex)
	{
		return Objects[InIndex];
	}

	FORCEINLINE void* GetValue_Void(const int32& InIndex)
	{
		return VoidPointers[InIndex];
	}

	template<typename T>
	FORCEINLINE T* GetValue_Void(const int32& InIndex)
	{
		return (T*)VoidPointers[InIndex];
	}

#pragma endregion Get

#pragma endregion Registers

// Message
#pragma region
public:

	TArray<TSet<FName>> Messages;
	TArray<TSet<FName>> Messages_Recieved;

	FORCEINLINE void AddMessage(const ECsCoroutineMessage& MessageType, const FName& Message)
	{
		Messages[(uint8)MessageType].Add(Message);
	}

	FORCEINLINE void ReceiveMessage(const ECsCoroutineMessage& MessageType, const FName& Message)
	{
		Messages_Recieved[(uint8)MessageType].Add(Message);
	}

#pragma endregion Message
};