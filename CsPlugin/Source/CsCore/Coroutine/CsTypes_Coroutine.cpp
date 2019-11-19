// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsTypes_Coroutine.h"

// CoroutineState
#pragma region

namespace NCsCoroutineState
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsCoroutineState, Free);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsCoroutineState, Init);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsCoroutineState, Update);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsCoroutineState, End);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCoroutineState, ECsCoroutineState_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsCoroutineState_MAX;
}

#pragma endregion CoroutineState

// CoroutineMessage
#pragma region

namespace NCsCoroutineMessage
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsCoroutineMessage, Notify);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsCoroutineMessage, Listen);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsCoroutineMessage, Abort);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCoroutineMessage, ECsCoroutineMessage_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsCoroutineMessage_MAX;
}

#pragma endregion CoroutineMessage

// CoroutineEndReason
#pragma region

namespace NCsCoroutineEndReason
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCoroutineEndReason, EndOfExecution, "End of Execution");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCoroutineEndReason, AbortMessage, "Abort Message");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCoroutineEndReason, AbortCondition, "Abort Condition");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCoroutineEndReason, OwnerIsInvalid, "Owner is Invalid");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsCoroutineEndReason, Parent);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCoroutineEndReason, UniqueInstance, "Unique Instance");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsCoroutineEndReason, Shutdown);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsCoroutineEndReason, Manual);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsCoroutineEndReason, ECsCoroutineEndReason_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsCoroutineEndReason_MAX;
}

#pragma endregion CoroutineEndReason

// CoroutineTransaction
#pragma region

namespace NCsCoroutineTransaction
{
	namespace Ref
	{
		CSCORE_API const Type Allocate = EMCsCoroutineTransaction::Get().Add(Type::Allocate, TEXT("Allocate"));
		CSCORE_API const Type Start = EMCsCoroutineTransaction::Get().Add(Type::Start, TEXT("Start"));
		CSCORE_API const Type End = EMCsCoroutineTransaction::Get().Add(Type::End, TEXT("End"));
		CSCORE_API const Type ECsCoroutineTransaction_MAX = EMCsCoroutineTransaction::Get().Add(Type::ECsCoroutineTransaction_MAX, TEXT("ECsCoroutineTransaction_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsCoroutineTransaction_MAX;

	namespace Str
	{
		CSCORE_API const TCsString Allocate = TCsString(TEXT("Allocate"), TEXT("allocate"), TEXT("Allocating"));
		CSCORE_API const TCsString Start = TCsString(TEXT("Start"), TEXT("start"), TEXT("Starting"));
		CSCORE_API const TCsString End = TCsString(TEXT("End"), TEXT("end"), TEXT("Ending"));
	}
}

#pragma endregion CoroutineTransaction

// RoutineRegisterValue
#pragma region

namespace NCsRoutineRegisterValueType
{
	namespace Ref
	{
		extern CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsRoutineRegisterValueType, Indexer);
		extern CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsRoutineRegisterValueType, Counter);
		extern CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsRoutineRegisterValueType, Flag);
		extern CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsRoutineRegisterValueType, Timer);
		extern CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsRoutineRegisterValueType, DeltaTime);
		extern CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsRoutineRegisterValueType, Int);
		extern CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsRoutineRegisterValueType, Float);
		extern CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsRoutineRegisterValueType, Vector);
		extern CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsRoutineRegisterValueType, Rotator);
		extern CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsRoutineRegisterValueType, Color);
		extern CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsRoutineRegisterValueType, Name);
		extern CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsRoutineRegisterValueType, String);
		extern CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsRoutineRegisterValueType, Object);
		extern CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsRoutineRegisterValueType, Void);
		extern CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsRoutineRegisterValueType, ECsRoutineRegisterValueType_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsRoutineRegisterValueType_MAX;

	void SetDefaultValue(const Type& ValueType, void* Ptr)
	{
		// Indexer
		if (ValueType == Type::Indexer)
		{
			int32* V = (int32*)Ptr;
			*V		 = 0;
		}
		// Counter
		else
		if (ValueType == Type::Counter)
		{
			int32* V = (int32*)Ptr;
			*V		 = 0;
		}
		// Flag
		else
		if (ValueType == Type::Flag)
		{
			bool* V = (bool*)Ptr;
			*V		 = false;
		}
		// Timer
		else
		if (ValueType == Type::Timer)
		{
			FCsTime* V = (FCsTime*)Ptr;
			V->Reset();
		}
		// DeltaTime
		else
		if (ValueType == Type::DeltaTime)
		{
			FCsDeltaTime* V = (FCsDeltaTime*)Ptr;
			V->Reset();
		}
		// Int
		else
		if (ValueType == Type::Int)
		{
			int32* V = (int32*)Ptr;
			*V		 = 0.0f;
		}
		// Float
		else
		if (ValueType == Type::Float)
		{
			float* V = (float*)Ptr;
			*V		 = 0.0f;
		}
		// Vector
		else
		if (ValueType == Type::Vector)
		{
			FVector* V = (FVector*)Ptr;
			*V		   = FVector::ZeroVector;
		}
		// Rotator
		else
		if (ValueType == Type::Rotator)
		{
			FRotator* V = (FRotator*)Ptr;
			*V		    = FRotator::ZeroRotator;
		}
		// Color
		else
		if (ValueType == Type::Color)
		{
			FLinearColor* V = (FLinearColor*)Ptr;
			*V				= FLinearColor::White;
		}
		// Name
		else
		if (ValueType == Type::Name)
		{
			FName* V = (FName*)Ptr;
			*V		 = NAME_None;
		}
		// String
		else
		if (ValueType == Type::String)
		{
			FString* V = (FString*)Ptr;
			V->Empty();
		}
		// Object
		else
		if (ValueType == Type::Object)
		{
			TCsWeakObjectPtr<UObject>* V = (TCsWeakObjectPtr<UObject>*)Ptr;
			V->Reset();
		}
		// Void
		else
		if (ValueType == Type::Void)
		{
			void** V = (void**)Ptr;
			*V		 = nullptr;
		}
	}

	void SetValue(const Type& ValueType, void* From, void* To)
	{
		// Indexer
		if (ValueType == Type::Indexer)
		{
			SetValue_Internal<int32>(From, To);
		}
		// Counter
		else
		if (ValueType == Type::Counter)
		{
			SetValue_Internal<int32>(From, To);
		}
		// Flag
		else
		if (ValueType == Type::Flag)
		{
			SetValue_Internal<bool>(From, To);
		}
		// Timer
		else
		if (ValueType == Type::Timer)
		{
			SetValue_Internal<FCsTime>(From, To);
		}
		// DeltaTime
		else
		if (ValueType == Type::DeltaTime)
		{
			SetValue_Internal<FCsDeltaTime>(From, To);
		}
		// Int
		else
		if (ValueType == Type::Int)
		{
			SetValue_Internal<int32>(From, To);
		}
		// Float
		else
		if (ValueType == Type::Float)
		{
			SetValue_Internal<float>(From, To);
		}
		// Vector
		else
		if (ValueType == Type::Vector)
		{
			SetValue_Internal<FVector>(From, To);
		}
		// Rotator
		else
		if (ValueType == Type::Rotator)
		{
			SetValue_Internal<FRotator>(From, To);
		}
		// Color
		else
		if (ValueType == Type::Color)
		{
			SetValue_Internal<FLinearColor>(From, To);
		}
		// Name
		else
		if (ValueType == Type::Name)
		{
			SetValue_Internal<FName>(From, To);
		}
		// String
		else
		if (ValueType == Type::String)
		{
			SetValue_Internal<FString>(From, To);
		}
		// Object
		else
		if (ValueType == Type::Object)
		{
			SetValue_Internal<TCsWeakObjectPtr<UObject>>(From, To);
		}
		// Void
		else
		if (ValueType == Type::Void)
		{
			void** F = (void**)From;
			void** T = (void**)To;
			*F		 = *T;
		}
	}
}

#pragma endregion RoutineRegisterValue

const FCsRoutineHandle FCsRoutineHandle::Invalid;

// FCsCoroutinePayload
#pragma region

FCsCoroutinePayload::FCsCoroutinePayload()
{
	Index = INDEX_NONE;

	// Registers
	Registers.Reserve(NCsRoutineRegisterValueType::MAX);
	RegisterFlags.Reserve(NCsRoutineRegisterValueType::MAX);

		// Indexers
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Registers[(uint8)ECsRoutineRegisterValueType::Indexer].AddDefaulted(Indexers.Max());
	Indexers.AddDefaulted(CS_ROUTINE_INDEXER_SIZE);

	for (int32& I : Indexers)
	{
		I = 0;
		Registers[(uint8)ECsRoutineRegisterValueType::Indexer].Add(&I);
	}

		// Counter
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Registers[(uint8)ECsRoutineRegisterValueType::Counter].AddDefaulted(Counters.Max());
	Counters.AddDefaulted(CS_ROUTINE_COUNTER_SIZE);

	for (int32& I : Counters)
	{
		I = 0;
		Registers[(uint8)ECsRoutineRegisterValueType::Counter].Add(&I);
	}

		// Flags
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Registers[(uint8)ECsRoutineRegisterValueType::Flag].AddDefaulted(Flags.Max());
	Flags.AddDefaulted(CS_ROUTINE_FLAG_SIZE);

	for (bool& Flag : Flags)
	{
		Flag = false;
		Registers[(uint8)ECsRoutineRegisterValueType::Flag].Add(&Flag);
	}

		// Timer
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Registers[(uint8)ECsRoutineRegisterValueType::Timer].AddDefaulted(Timers.Max());
	Timers.AddDefaulted(CS_ROUTINE_TIMER_SIZE);

	for (FCsTime& Timer : Timers)
	{
		Timer.Reset();
		Registers[(uint8)ECsRoutineRegisterValueType::Timer].Add(&Timer);
	}

		// DeltaTime
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Registers[(uint8)ECsRoutineRegisterValueType::DeltaTime].AddDefaulted(DeltaTimes.Max());
	DeltaTimes.AddDefaulted(CS_ROUTINE_DELTA_TIME_SIZE);

	for (FCsDeltaTime& DT : DeltaTimes)
	{
		DT.Reset();
		Registers[(uint8)ECsRoutineRegisterValueType::DeltaTime].Add(&DT);
	}

		// Ints
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Registers[(uint8)ECsRoutineRegisterValueType::Int].AddDefaulted(Ints.Max());
	Ints.AddDefaulted(CS_ROUTINE_INT_SIZE);

	for (int32& I : Ints)
	{
		I = 0;
		Registers[(uint8)ECsRoutineRegisterValueType::Int].Add(&I);
	}

		// Float
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Registers[(uint8)ECsRoutineRegisterValueType::Int].AddDefaulted(Ints.Max());
	Floats.AddDefaulted(CS_ROUTINE_FLOAT_SIZE);

	for (float& Float : Floats)
	{
		Float = 0.0f;
		Registers[(uint8)ECsRoutineRegisterValueType::Float].Add(&Float);
	}

		// Vector
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Registers[(uint8)ECsRoutineRegisterValueType::Vector].AddDefaulted(Vectors.Max());
	Vectors.AddDefaulted(CS_ROUTINE_VECTOR_SIZE);

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
	Registers[(uint8)ECsRoutineRegisterValueType::Color].AddDefaulted(Colors.Max());
	Colors.AddDefaulted(CS_ROUTINE_COLOR_SIZE);

	for (FLinearColor& C : Colors)
	{
		C = FLinearColor::White;
		Registers[(uint8)ECsRoutineRegisterValueType::Color].Add(&C);
	}

		// Name
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Registers[(uint8)ECsRoutineRegisterValueType::Name].AddDefaulted(Names.Max());
	Names.AddDefaulted(CS_ROUTINE_NAME_SIZE);

	for (FName& N : Names)
	{
		N = NAME_None;
		Registers[(uint8)ECsRoutineRegisterValueType::Name].Add(&N);
	}

		// String
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Registers[(uint8)ECsRoutineRegisterValueType::String].AddDefaulted(Strings.Max());
	Strings.AddDefaulted(CS_ROUTINE_STRING_SIZE);

	for (FString& S : Strings)
	{
		S.Empty();
		Registers[(uint8)ECsRoutineRegisterValueType::String].Add(&S);
	}

		// Object
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Registers[(uint8)ECsRoutineRegisterValueType::Object].AddDefaulted(Objects.Max());
	Objects.AddDefaulted(CS_ROUTINE_OBJECT_SIZE);

	for (TCsWeakObjectPtr<UObject>& Object : Objects)
	{
		Object.Reset();
		Registers[(uint8)ECsRoutineRegisterValueType::Object].Add(&Object);
	}

		// VoidPointers
	Registers.AddDefaulted();
	RegisterFlags.AddDefaulted();
	Registers[(uint8)ECsRoutineRegisterValueType::Void].AddDefaulted(VoidPointers.Max());
	VoidPointers.AddDefaulted(CS_ROUTINE_VOID_POINTER_SIZE);

	for (void*& V : VoidPointers)
	{
		V = nullptr;
		Registers[(uint8)ECsRoutineRegisterValueType::Void].Add(&V);
	}
	Reset();
}

void FCsCoroutinePayload::SetIndex(const int32& InIndex)
{
	Index = InIndex;
}


void FCsCoroutinePayload::Reset()
{
	Group = EMCsUpdateGroup::Get().GetMAX();
	Coroutine.Unbind();
	StartTime.Reset();
	Owner.Reset();
	Aborts.Reset(Aborts.Max());
	OnAborts.Reset(OnAborts.Max());
	ParentHandle.Reset();
	bDoInit = true;
	bPerformFirstUpdate = false;
	Name = NAME_None;
	NameAsString.Empty();
	AbortMessages.Reset(AbortMessages.Max());

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
}

#pragma endregion FCsCoroutinePayload