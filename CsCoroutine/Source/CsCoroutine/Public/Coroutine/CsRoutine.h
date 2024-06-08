// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsMacro_Misc.h"
#include "Coroutine/CsTypes_Coroutine.h"
#include "Coroutine/pt.h"
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

// Delegates
#pragma region

#pragma endregion Delegates

class UObject;
class AActor;

struct CSCOROUTINE_API FCsRoutine
{
public:

	FCsRoutine();
	
	~FCsRoutine();

private:

	typedef NCsCoroutine::FImpl CoroutineImplType;
	typedef NCsCoroutine::FAbortConditionImpl AbortConditionImplType;
	typedef NCsCoroutine::FOnAbort OnAbortType;
	typedef NCsCoroutine::FOnEnd OnEndType;

	typedef NCsCoroutine::EState StateType;
	typedef NCsCoroutine::EMessage MessageType;
	typedef NCsCoroutine::EEndReason EndReasonType;
	typedef NCsCoroutine::EMEndReason EndReasonMapType;
	typedef NCsCoroutine::NRegister::EValueType ValueType;
	typedef NCsCoroutine::NRegister::FMap RegisterMapType;

	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	typedef NCsCoroutine::FOwner OwnerType;

public:

	struct pt pt;

	CoroutineImplType CoroutineImpl;

	// Time
#pragma region
private:

	FECsUpdateGroup Group;

public:

	void SetGroup(const FECsUpdateGroup& InGroup);

	FORCEINLINE const FECsUpdateGroup& GetGroup() const { return Group; }

private:

	FString ScopeName;

public:

	FORCEINLINE const FString& GetScopeName() const { return ScopeName; }

private:

	FCsTime StartTime;
	FCsDeltaTime ElapsedTime;
	FCsDeltaTime DeltaTime;

	int32 TickCount;

	float Delay;

	bool bDeltaTimeScalar;

	float* DeltaTimeScalar;

public:

	FORCEINLINE const FCsTime& GetStartTime() const { return StartTime; }
	FORCEINLINE const FCsDeltaTime& GetElapsedTime() const { return ElapsedTime; }
	FORCEINLINE const FCsDeltaTime& GetDeltaTime() const { return DeltaTime; }
	FORCEINLINE const int32& GetTickCount() const { return TickCount; }
	FORCEINLINE const float& GetDelay() const { return Delay; }

	FORCEINLINE void SetDeltaTimeScalar(float* Scalar)
	{
		checkf(Scalar, TEXT("FCsRoutine::SetDeltaTimeScalar: Scalar is NULL."));

		DeltaTimeScalar  = Scalar;
		bDeltaTimeScalar = true;
	}
	FORCEINLINE float GetDeltaTimeScalar() const { return bDeltaTimeScalar ? *DeltaTimeScalar : 1.0f; }

private:

	FCsScopedTimerHandle RoutineScopedTimerHandle;
	FCsScopedTimerHandle CoroutineScopedTimerHandle;

#pragma endregion Time

protected:

	FCsRoutineHandle Handle;

public:

	FORCEINLINE const FCsRoutineHandle& GetHandle() const { return Handle; }

	TArray<AbortConditionImplType> AbortImpls;

	TArray<OnAbortType> OnAborts;

public:

	StateType State;

// Index
#pragma region
private:

	int32 Index;

public:

	void SetIndex(const int32& InIndex);

	FORCEINLINE const int32& GetIndex() const { return Index; }

#pragma endregion Index

// Name
#pragma region
private:

	FString* Name;

	FName Name_Internal;

public:

	FORCEINLINE void SetName(const FString* InName) { Name = const_cast<FString*>(InName); }

	FORCEINLINE void SetFName(const FName& InName) { Name_Internal = InName; }

	FORCEINLINE const FString* GetName() { return Name; }

	FORCEINLINE const FName& GetFName() { return Name_Internal; }

	FORCEINLINE const TCHAR* ToChar() { return *(*GetName()); }

#pragma endregion Name

public:

	void Init(PayloadType* Payload);

// Run
#pragma region
public:

	FORCEINLINE void StartUpdate() { State = StateType::Update; }

	void Update(const FCsDeltaTime& InDeltaTime);

private:

	bool bUpdateComplete;

public:

	FORCEINLINE bool IsUpdateComplete() const { return bUpdateComplete; }
	
private:

	bool bExecuteComplete;

public:

	FORCEINLINE bool IsExecuteComplete() const { return bExecuteComplete; }

	FORCEINLINE bool IsRunning() const { return State == StateType::Update; }

#pragma endregion Run

// End
#pragma region
public:

	EndReasonType EndReason;

	FORCEINLINE const EndReasonType& GetEndReason() const { return EndReason; }
	FORCEINLINE bool IsEndOfExeuction() const { return EndReason == EndReasonType::EndOfExecution; }

	TArray<OnEndType> OnEnds;

	void End(const EndReasonType& InEndReason);

	FORCEINLINE bool HasJustEnded() const { return State == StateType::End; }
	FORCEINLINE bool HasEnded() const
	{
		return State == StateType::End || State == StateType::Free;
	}

#pragma endregion End

public:

	void Reset();

// Owner
#pragma region
public:

	OwnerType Owner;

	FORCEINLINE void* GetOwner() { return Owner.GetOwner(); }

	template<typename T>
	FORCEINLINE T* GetOwner() { return (T*)GetOwner(); }

	FORCEINLINE UObject* GetOwnerAsObject() { return Owner.GetObject(); }

	template<typename T>
	FORCEINLINE T* GetOwnerAsObject() { return Cast<T>(GetOwnerAsObject()); }

	FORCEINLINE UObject* GetSafeOwnerAsObject() { return Owner.GetSafeObject(); }

	FORCEINLINE AActor* GetOwnerAsActor() { return Owner.GetActor(); }

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

	RegisterMapType RegisterMap;

	// Set
#pragma region
public:

	FORCEINLINE void SetValue_Flag(const int32& InIndex, const bool& Value){				RegisterMap.SetValue_Flag(InIndex, Value); }
	FORCEINLINE void SetValue_Timer(const int32& InIndex, const FCsTime& Value){			RegisterMap.SetValue_Timer(InIndex, Value); }
	FORCEINLINE void SetValue_DeltaTime(const int32& InIndex, const FCsDeltaTime& Value){	RegisterMap.SetValue_DeltaTime(InIndex, Value); }
	FORCEINLINE void SetValue_Int(const int32& InIndex, const int32& Value){				RegisterMap.SetValue_Int(InIndex, Value); }
	FORCEINLINE void SetValue_UnsignedInt(const int32& InIndex, const uint32& Value){		RegisterMap.SetValue_UnsignedInt(InIndex, Value); }
	FORCEINLINE void SetValue_Float(const int32& InIndex, const float& Value){				RegisterMap.SetValue_Float(InIndex, Value); }
	FORCEINLINE void SetValue_Double(const int32& InIndex, const double& Value){			RegisterMap.SetValue_Double(InIndex, Value); }
	FORCEINLINE void SetValue_Vector(const int32& InIndex, const FVector3f& Value){			RegisterMap.SetValue_Vector(InIndex, Value); }
	FORCEINLINE void SetValue_Rotator(const int32& InIndex, const FRotator3f& Value){			RegisterMap.SetValue_Rotator(InIndex, Value); }
	FORCEINLINE void SetValue_Color(const int32& InIndex, const FLinearColor& Value){		RegisterMap.SetValue_Color(InIndex, Value); }
	FORCEINLINE void SetValue_Name(const int32& InIndex, const FName& Value){				RegisterMap.SetValue_Name(InIndex, Value); }
	FORCEINLINE void SetValue_String(const int32& InIndex, const FString& Value){			RegisterMap.SetValue_String(InIndex, Value); }
	FORCEINLINE void SetValue_StringPtr(const int32& InIndex, FString* Value){				RegisterMap.SetValue_StringPtr(InIndex, Value); }
	FORCEINLINE void SetValue_Object(const int32& InIndex, UObject* Value){					RegisterMap.SetValue_Object(InIndex, Value); }
	FORCEINLINE void SetValue_Void(const int32& InIndex, void* Value){						RegisterMap.SetValue_Void(InIndex, Value); }

#pragma endregion Set

	// Get
#pragma region
public:

	FORCEINLINE bool& GetValue_Flag(const int32& InIndex){							return RegisterMap.GetValue_Flag(InIndex); }
	FORCEINLINE FCsTime& GetValue_Timer(const int32& InIndex){						return RegisterMap.GetValue_Timer(InIndex); }
	FORCEINLINE FCsDeltaTime& GetValue_DeltaTime(const int32& InIndex){				return RegisterMap.GetValue_DeltaTime(InIndex); }
	FORCEINLINE int32& GetValue_Int(const int32& InIndex){							return RegisterMap.GetValue_Int(InIndex); }
	FORCEINLINE uint32& GetValue_UnsignedInt(const int32& InIndex){					return RegisterMap.GetValue_UnsignedInt(InIndex); }
	FORCEINLINE float& GetValue_Float(const int32& InIndex){						return RegisterMap.GetValue_Float(InIndex); }
	FORCEINLINE double& GetValue_Double(const int32& InIndex){						return RegisterMap.GetValue_Double(InIndex); }
	FORCEINLINE FVector3f& GetValue_Vector(const int32& InIndex){						return RegisterMap.GetValue_Vector(InIndex); }
	FORCEINLINE FRotator3f& GetValue_Rotator(const int32& InIndex){					return RegisterMap.GetValue_Rotator(InIndex); }
	FORCEINLINE FLinearColor& GetValue_Color(const int32& InIndex){					return RegisterMap.GetValue_Color(InIndex); }
	FORCEINLINE FName& GetValue_Name(const int32& InIndex){							return RegisterMap.GetValue_Name(InIndex); }
	FORCEINLINE FString& GetValue_String(const int32& InIndex){						return RegisterMap.GetValue_String(InIndex); }
	FORCEINLINE FString* GetValue_StringPtr(const int32& InIndex){					return RegisterMap.GetValue_StringPtr(InIndex); }
	FORCEINLINE UObject* GetValue_Object(const int32& InIndex){						return RegisterMap.GetValue_Object(InIndex); }
	template<typename T>
	FORCEINLINE T* GetValue_Object(const int32& InIndex) {							return RegisterMap.GetValue_Object<T>(InIndex); }
	FORCEINLINE void* GetValue_Void(const int32& InIndex){							return RegisterMap.GetValue_Void(InIndex); }
	template<typename T>
	FORCEINLINE T* GetValue_Void(const int32& InIndex){								return RegisterMap.GetValue_Void<T>(InIndex); }

#pragma endregion Get

#pragma endregion Registers

// Message
#pragma region
public:

	TArray<TSet<FName>> Messages;
	TArray<TSet<FName>> Messages_Recieved;

	FORCEINLINE void AddMessage(const MessageType& Type, const FName& Message)
	{
		Messages[(uint8)Type].Add(Message);
	}

	FORCEINLINE void ReceiveMessage(const MessageType& Type, const FName& Message)
	{
		Messages_Recieved[(uint8)Type].Add(Message);
	}

#pragma endregion Message
};