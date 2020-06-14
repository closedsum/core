// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsRoutine.h"

// CVar
#include "Coroutine/CsCVars_Coroutine.h"
// Managers
#include "Managers/ScopedTimer/CsManager_ScopedTimer.h"

FCsRoutine::FCsRoutine()
{
	Parent = nullptr;

	Children.Reset(Children.Max());

	for (const ECsCoroutineMessage& MessageType : EMCsCoroutineMessage::Get())
	{
		Messages.AddDefaulted();
		Messages_Recieved.AddDefaulted();
	}

	// Registers
	Registers.Reserve(NCsRoutineRegisterValueType::MAX);
	RegisterFlags.Reserve(NCsRoutineRegisterValueType::MAX);

		// Indexers
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Indexers.AddDefaulted(CS_ROUTINE_INDEXER_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::Indexer].AddDefaulted(Indexers.Max());

	for (int32& I : Indexers)
	{
		I = 0;
		Registers[(uint8)ECsRoutineRegisterValueType::Indexer].Add(&I);
	}

		// Counter
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Counters.AddDefaulted(CS_ROUTINE_COUNTER_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::Counter].AddDefaulted(Counters.Max());

	for (int32& I : Counters)
	{
		I = 0;
		Registers[(uint8)ECsRoutineRegisterValueType::Counter].Add(&I);
	}

		// Flags
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Flags.AddDefaulted(CS_ROUTINE_FLAG_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::Flag].AddDefaulted(Flags.Max());

	for (bool& Flag : Flags)
	{
		Flag = false;
		Registers[(uint8)ECsRoutineRegisterValueType::Flag].Add(&Flag);
	}

		// Timer
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Timers.AddDefaulted(CS_ROUTINE_TIMER_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::Timer].AddDefaulted(Timers.Max());

	for (FCsTime& Timer : Timers)
	{
		Timer.Reset();
		Registers[(uint8)ECsRoutineRegisterValueType::Timer].Add(&Timer);
	}

		// DeltaTime
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	DeltaTimes.AddDefaulted(CS_ROUTINE_TIMER_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::DeltaTime].AddDefaulted(DeltaTimes.Max());

	for (FCsDeltaTime& DT : DeltaTimes)
	{
		DT.Reset();
		Registers[(uint8)ECsRoutineRegisterValueType::DeltaTime].Add(&DT);
	}

		// Ints
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Ints.AddDefaulted(CS_ROUTINE_INT_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::Int].AddDefaulted(Ints.Max());

	for (int32& I : Ints)
	{
		I = 0;
		Registers[(uint8)ECsRoutineRegisterValueType::Int].Add(&I);
	}

		// Float
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Floats.AddDefaulted(CS_ROUTINE_FLOAT_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::Int].AddDefaulted(Floats.Max());
	
	for (float& Float : Floats)
	{
		Float = 0.0f;
		Registers[(uint8)ECsRoutineRegisterValueType::Float].Add(&Float);
	}

		// Double
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Doubles.AddDefaulted(CS_ROUTINE_DOUBLE_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::Double].AddDefaulted(Doubles.Max());
	
	for (double& Double : Doubles)
	{
		Double = 0.0;
		Registers[(uint8)ECsRoutineRegisterValueType::Double].Add(&Double);
	}

		// Vector
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Vectors.AddDefaulted(CS_ROUTINE_VECTOR_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::Vector].AddDefaulted(Vectors.Max());

	for (FVector& V : Vectors)
	{
		V = FVector::ZeroVector;
		Registers[(uint8)ECsRoutineRegisterValueType::Vector].Add(&V);
	}

		// Rotator
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Registers[(uint8)ECsRoutineRegisterValueType::Rotator].AddDefaulted(Rotators.Max());
	Rotators.AddDefaulted(CS_ROUTINE_ROTATOR_SIZE);

	for (FRotator& R : Rotators)
	{
		R = FRotator::ZeroRotator;
		Registers[(uint8)ECsRoutineRegisterValueType::Rotator].Add(&R);
	}

		// Color
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Colors.AddDefaulted(CS_ROUTINE_COLOR_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::Color].AddDefaulted(Colors.Max());

	for (FLinearColor& C : Colors)
	{
		C = FLinearColor::White;
		Registers[(uint8)ECsRoutineRegisterValueType::Color].Add(&C);
	}

		// Name
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Names.AddDefaulted(CS_ROUTINE_NAME_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::Name].AddDefaulted(Names.Max());

	for (FName& N : Names)
	{
		N = NAME_None;
		Registers[(uint8)ECsRoutineRegisterValueType::Name].Add(&N);
	}

		// String
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Strings.AddDefaulted(CS_ROUTINE_STRING_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::String].AddDefaulted(Strings.Max());
	
	for (FString& S : Strings)
	{
		S.Empty();
		Registers[(uint8)ECsRoutineRegisterValueType::String].Add(&S);
	}

		// StringPtr
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	StringPointers.AddDefaulted(CS_ROUTINE_STRING_POINTER_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::StringPtr].AddDefaulted(StringPointers.Max());
	
	for (FString*& S : StringPointers)
	{
		S = nullptr;
		Registers[(uint8)ECsRoutineRegisterValueType::StringPtr].Add(&S);
	}

		// Object
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Objects.AddDefaulted(CS_ROUTINE_OBJECT_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::Object].AddDefaulted(Objects.Max());

	for (TCsWeakObjectPtr<UObject>& Object : Objects)
	{
		Object.Reset();
		Registers[(uint8)ECsRoutineRegisterValueType::Object].Add(&Object);
	}

		// VoidPointers
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	VoidPointers.AddDefaulted(CS_ROUTINE_VOID_POINTER_SIZE);
	RegisterFlags[(uint8)ECsRoutineRegisterValueType::Void].AddDefaulted(VoidPointers.Max());
	
	for (void*& V : VoidPointers)
	{
		V = nullptr;
		Registers[(uint8)ECsRoutineRegisterValueType::Void].Add(&V);
	}
	Reset();
}

FCsRoutine::~FCsRoutine()
{
}

// Time
#pragma region

void FCsRoutine::SetGroup(const FECsUpdateGroup& InGroup)
{
	Group	  = InGroup;
	ScopeName = FString::Printf(TEXT("Routine_%d_%s"), Index, *(Group.GetName()));
}

#pragma endregion Time

// Index
#pragma region

void FCsRoutine::SetIndex(const int32& InIndex)
{
	Index		 = InIndex;
	Handle.Index = InIndex;
}

#pragma endregion Index

void FCsRoutine::Init(FCsCoroutinePayload* Payload)
{
	State = ECsCoroutineState::Init;

	CoroutineImpl = Payload->CoroutineImpl;
	StartTime = Payload->StartTime;
	Owner	  = Payload->Owner;
	
	for (const FName& Message : Payload->AbortMessages)
	{
		Messages[(uint8)ECsCoroutineMessage::Abort].Add(Message);
	}

	for (const FCsCoroutineAbortConditionImpl& AbortImpl : Payload->AbortImpls)
	{
		AbortImpls.AddDefaulted();
		FCsCoroutineAbortConditionImpl& Last = AbortImpls.Last();
		Last = AbortImpl;
	}

	Name_Internal	= Payload->GetFName();
	Name			= const_cast<FString*>(Payload->GetName());

	// Copy Register values over
	for (const FCsRoutineRegisterInfo& Info : Payload->RegisterInfos)
	{
		const ECsRoutineRegisterValueType& ValueType = Info.ValueType;
		const int32&							   I = Info.Index;

		void* From = Registers[(uint8)ValueType][I];
		void* To   = Payload->Registers[(uint8)ValueType][I];

		NCsRoutineRegisterValueType::SetValue(ValueType, From, To);
	}
	Handle.New();

	CS_GET_SCOPED_TIMER_HANDLE(RoutineScopedTimerHandle, &ScopeName, NCsCVarLog::LogRoutineScopedTimer);
	CS_GET_SCOPED_TIMER_HANDLE(CoroutineScopedTimerHandle, Name, NCsCVarLog::LogCoroutineScopedTimer);
}

// Update
#pragma region

void FCsRoutine::Update(const FCsDeltaTime& InDeltaTime)
{
	CS_SCOPED_TIMER(RoutineScopedTimerHandle);

	const int32 AbortIndex = (int32)ECsCoroutineMessage::Abort;

	TSet<FName>& AbortMessages		    = Messages[AbortIndex];
	TSet<FName>& AbortMessages_Recieved = Messages_Recieved[AbortIndex];

	if (AbortMessages.Num() > CS_EMPTY)
	{
		bool MatchFound = false;

		for (const FName& Recieved : AbortMessages_Recieved)
		{
			if (AbortMessages.Find(Recieved))
			{
				AbortMessages.Reset();
				End(ECsCoroutineEndReason::AbortMessage);

				MatchFound = true;
			}

			if (MatchFound)
				break;
		}
	}
	AbortMessages_Recieved.Reset();

	if (State == ECsCoroutineState::End &&
		EndReason == ECsCoroutineEndReason::AbortMessage)
	{
		return;
	}

	if (Owner.IsObject())
	{
		UObject* O = Owner.GetSafeObject();

		if (!O ||
			O->IsPendingKill())
		{
			End(ECsCoroutineEndReason::OwnerIsInvalid);
			return;
		}
	}

	for (FCsCoroutineAbortConditionImpl& AbortImpl : AbortImpls)
	{
		if (AbortImpl.Execute(this))
		{
			for (FCsOnCoroutineAbort& OnAbort : OnAborts)
			{
				OnAbort.Execute(this);
			}
			End(ECsCoroutineEndReason::AbortCondition);
			return;
		}
	}

	if (State == ECsCoroutineState::End)
	{
		if (EndReason == ECsCoroutineEndReason::ECsCoroutineEndReason_MAX)
			End(ECsCoroutineEndReason::EndOfExecution);
		return;
	}

	DeltaTime = InDeltaTime;

	ElapsedTime += DeltaTime;

	++TickCount;

	{
		CS_SCOPED_TIMER(CoroutineScopedTimerHandle);

		CoroutineImpl.Execute(this);
	}

	if (State == ECsCoroutineState::End)
		End(ECsCoroutineEndReason::EndOfExecution);
}

#pragma endregion Update

// End
#pragma region

void FCsRoutine::End(const ECsCoroutineEndReason& InEndReason)
{
	EndChildren();
	State = ECsCoroutineState::End;
	EndReason = InEndReason;

	FCsManager_ScopedTimer::Get().ClearHandle(CoroutineScopedTimerHandle);
}

#pragma endregion End

void FCsRoutine::Reset()
{
	if (Parent)
	{
		Parent->Children.Remove(this);
	}

	Parent = nullptr;

	EndChildren();

	CoroutineImpl.Unbind();

	// Time
	StartTime.Reset();
	ElapsedTime.Reset();
	DeltaTime.Reset();
	TickCount = 0;
	Delay = 0.0f;

	RoutineScopedTimerHandle.Reset();
	CoroutineScopedTimerHandle.Reset();

	Handle.Reset();
	AbortImpls.Reset(AbortImpls.Max());
	OnAborts.Reset(OnAborts.Max());
	State = ECsCoroutineState::Free;
	Name = nullptr;
	Name_Internal = NAME_None;

	EndReason = ECsCoroutineEndReason::ECsCoroutineEndReason_MAX;

	Owner.Reset();
	
	// Registers

		// Reset to default value
	for (const FCsRoutineRegisterInfo& Info : RegisterInfos)
	{
		const ECsRoutineRegisterValueType& ValueType = Info.ValueType;
		const int32& I								 = Info.Index;

		void* Ptr = Registers[(uint8)ValueType][I];

		NCsRoutineRegisterValueType::SetDefaultValue(ValueType, Ptr);

		RegisterFlags[(uint8)ValueType][I] = false;
	}

	RegisterInfos.Reset(RegisterInfos.Max());

	// Messages

	for (const ECsCoroutineMessage& MessageType : EMCsCoroutineMessage::Get())
	{
		const int32 I = (int32)MessageType;

		Messages[I].Reset();
		Messages_Recieved[I].Reset();
	}
}

// Children
#pragma region

void FCsRoutine::AddChild(FCsRoutine* Child)
{
	Child->Parent = this;
	Children.Add(Child);
}

void FCsRoutine::EndChildren()
{
	for (FCsRoutine* Child : Children)
	{
		Child->End(ECsCoroutineEndReason::Parent);
	}
	Children.Reset(Children.Max());
}

void FCsRoutine::EndChild(FCsRoutine* Child)
{
	const int32 Count = Children.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		if (Child == Children[I])
		{
			Child->End(ECsCoroutineEndReason::Parent);
			Children.RemoveAt(I, 1, false);
			break;
		}
	}
}

#pragma endregion Children