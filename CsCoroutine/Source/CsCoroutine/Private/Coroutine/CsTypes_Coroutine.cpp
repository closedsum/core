// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coroutine/CsTypes_Coroutine.h"

// Library
#include "Managers/Time/CsLibrary_Manager_Time.h"
	// Common
#include "Library/CsLibrary_Valid.h"
// Actor
#include "GameFramework/Actor.h"

namespace NCsCoroutine
{
	// State
	#pragma region

	namespace NState
	{
		namespace Ref
		{
			typedef EMState EnumMapType;

			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Free);
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Init);
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Update);
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(End);
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EState_MAX, "MAX");
		}

		CSCOROUTINE_API const uint8 MAX = (uint8)Type::EState_MAX;
	}

	#pragma endregion State

	// Message
	#pragma region

	namespace NMessage
	{
		namespace Ref
		{
			typedef EMMessage EnumMapType;

			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Notify);
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Listen);
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Abort);
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMessage_MAX, "MAX");
		}

		CSCOROUTINE_API const uint8 MAX = (uint8)Type::EMessage_MAX;
	}

	#pragma endregion Message

	// EndReason
	#pragma region

	namespace NEndReason
	{
		namespace Ref
		{
			typedef EMEndReason EnumMapType;

			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EndOfExecution, "End of Execution");
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP_CUSTOM(AbortMessage, "Abort Message");
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP_CUSTOM(AbortCondition, "Abort Condition");
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP_CUSTOM(OwnerIsInvalid, "Owner is Invalid");
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Parent);
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP_CUSTOM(UniqueInstance, "Unique Instance");
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Shutdown);
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Manual);
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EEndReason_MAX, "MAX");
		}

		CSCOROUTINE_API const uint8 MAX = (uint8)Type::EEndReason_MAX;
	}

	#pragma endregion EndReason

	// Transaction
	#pragma region

	namespace NTransaction
	{
		namespace Ref
		{
			typedef EMTransaction EnumMapType;

			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Allocate);
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Start);
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(End);
			CSCOROUTINE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ETransaction_MAX, "MAX");
		}

		CSCOROUTINE_API const uint8 MAX = (uint8)Type::ETransaction_MAX;

		namespace Str
		{
			CSCOROUTINE_API const TCsString Allocate = TCsString(TEXT("Allocate"), TEXT("allocate"), TEXT("Allocating"));
			CSCOROUTINE_API const TCsString Start = TCsString(TEXT("Start"), TEXT("start"), TEXT("Starting"));
			CSCOROUTINE_API const TCsString End = TCsString(TEXT("End"), TEXT("end"), TEXT("Ending"));
		}
	}

	#pragma endregion Transaction

	// FOwner
	#pragma region

	void FOwner::SetObject(UObject* InObject)
	{
		Owner = InObject;
		Object = InObject;
		WeakObject = Object;
		bObject = true;
		Actor = Cast<AActor>(Object);
	}

	bool FOwner::IsValidChecked(const FString& Context) const
	{
		// Check Owner is Valid
		CS_IS_PTR_NULL_CHECKED(Owner)
		// If UObject, Check Object is Valid
		if (bObject)
		{
			CS_IS_PTR_NULL_CHECKED(Object)
		}
		return true;
	}

	#pragma endregion FOwner

	namespace NRegister
	{
		// ValueType
		#pragma region

		namespace NValueType
		{
			namespace Ref
			{
				typedef EMValueType EnumMapType;

				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Flag);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Timer);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(DeltaTime);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Int);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(UnsignedInt);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Float);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Double);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Vector);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Rotator);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Color);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Name);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(String);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(StringPtr);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Object);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP(Void);
				extern CSCOROUTINE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EValueType_MAX, "MAX");
			}

			CSCOROUTINE_API const uint8 MAX = (uint8)Type::EValueType_MAX;

			void SetDefaultValue(const Type& ValueType, void* Ptr)
			{
				// Flag
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
					*V		 = 0;
				}
				// UnsignedInt
				else
				if (ValueType == Type::UnsignedInt)
				{
					uint32* V = (uint32*)Ptr;
					*V		  = 0;
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
					FVector3f* V = (FVector3f*)Ptr;
					*V		   = FVector3f::ZeroVector;
				}
				// Rotator
				else
				if (ValueType == Type::Rotator)
				{
					FRotator3f* V = (FRotator3f*)Ptr;
					*V		    = FRotator3f::ZeroRotator;
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
				// StringPtr
				else
				if (ValueType == Type::String)
				{
					FString** V = (FString**)Ptr;
					*V = nullptr;
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
				// Flag
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
				// UnsignedInt
				else
				if (ValueType == Type::UnsignedInt)
				{
					SetValue_Internal<uint32>(From, To);
				}
				// Float
				else
				if (ValueType == Type::Float)
				{
					SetValue_Internal<float>(From, To);
				}
				// Double
				else
				if (ValueType == Type::Double)
				{
					SetValue_Internal<double>(From, To);
				}
				// Vector
				else
				if (ValueType == Type::Vector)
				{
					SetValue_Internal<FVector3f>(From, To);
				}
				// Rotator
				else
				if (ValueType == Type::Rotator)
				{
					SetValue_Internal<FRotator3f>(From, To);
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
				// String
				else
				if (ValueType == Type::StringPtr)
				{
					SetValue_Internal<FString*>(From, To);
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

		#pragma endregion ValueType

		// FMap
		#pragma region

		FMap::FMap()
		{
			Values.Reset((uint8)EValueType::EValueType_MAX);
			UsedValues.Reset((uint8)EValueType::EValueType_MAX);

				// Flags
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			Flags.AddDefaulted(CS_ROUTINE_FLAG_SIZE);
			UsedValues[(uint8)EValueType::Flag].AddDefaulted(Flags.Max());

			for (bool& Flag : Flags)
			{
				Flag = false;
				Values[(uint8)EValueType::Flag].Add(&Flag);
			}

				// Timer
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			Timers.AddDefaulted(CS_ROUTINE_TIMER_SIZE);
			UsedValues[(uint8)EValueType::Timer].AddDefaulted(Timers.Max());

			for (FCsTime& Timer : Timers)
			{
				Timer.Reset();
				Values[(uint8)EValueType::Timer].Add(&Timer);
			}

				// DeltaTime
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			DeltaTimes.AddDefaulted(CS_ROUTINE_DELTA_TIME_SIZE);
			UsedValues[(uint8)EValueType::DeltaTime].AddDefaulted(DeltaTimes.Max());

			for (FCsDeltaTime& DT : DeltaTimes)
			{
				DT.Reset();
				Values[(uint8)EValueType::DeltaTime].Add(&DT);
			}

				// Ints
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			Ints.AddDefaulted(CS_ROUTINE_INT_SIZE);
			UsedValues[(uint8)EValueType::Int].AddDefaulted(Ints.Max());

			for (int32& I : Ints)
			{
				I = 0;
				Values[(uint8)EValueType::Int].Add(&I);
			}

				// UnsignedInts
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			UnsignedInts.AddDefaulted(CS_ROUTINE_INT_SIZE);
			UsedValues[(uint8)EValueType::UnsignedInt].AddDefaulted(Ints.Max());

			for (uint32& I : UnsignedInts)
			{
				I = 0;
				Values[(uint8)EValueType::UnsignedInt].Add(&I);
			}

				// Float
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			Floats.AddDefaulted(CS_ROUTINE_FLOAT_SIZE);
			UsedValues[(uint8)EValueType::Float].AddDefaulted(Floats.Max());

			for (float& Float : Floats)
			{
				Float = 0.0f;
				Values[(uint8)EValueType::Float].Add(&Float);
			}

				// Double
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			Doubles.AddDefaulted(CS_ROUTINE_DOUBLE_SIZE);
			UsedValues[(uint8)EValueType::Double].AddDefaulted(Doubles.Max());

			for (double& Double : Doubles)
			{
				Double = 0.0;
				Values[(uint8)EValueType::Double].Add(&Double);
			}

				// Vector
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			Vectors.AddDefaulted(CS_ROUTINE_VECTOR_SIZE);
			UsedValues[(uint8)EValueType::Vector].AddDefaulted(Vectors.Max());

			for (FVector3f& V : Vectors)
			{
				V = FVector3f::ZeroVector;
				Values[(uint8)EValueType::Vector].Add(&V);
			}

				// Rotator
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			Rotators.AddDefaulted(CS_ROUTINE_ROTATOR_SIZE);
			UsedValues[(uint8)EValueType::Rotator].AddDefaulted(Rotators.Max());

			for (FRotator3f& R : Rotators)
			{
				R = FRotator3f::ZeroRotator;
				Values[(uint8)EValueType::Rotator].Add(&R);
			}

				// Color
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			Colors.AddDefaulted(CS_ROUTINE_COLOR_SIZE);
			UsedValues[(uint8)EValueType::Color].AddDefaulted(Colors.Max());

			for (FLinearColor& C : Colors)
			{
				C = FLinearColor::White;
				Values[(uint8)EValueType::Color].Add(&C);
			}

				// Name
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			Names.AddDefaulted(CS_ROUTINE_NAME_SIZE);
			UsedValues[(uint8)EValueType::Name].AddDefaulted(Names.Max());

			for (FName& N : Names)
			{
				N = NAME_None;
				Values[(uint8)EValueType::Name].Add(&N);
			}

				// String
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			Strings.AddDefaulted(CS_ROUTINE_STRING_SIZE);
			UsedValues[(uint8)EValueType::String].AddDefaulted(Strings.Max());

			for (FString& S : Strings)
			{
				S.Empty();
				Values[(uint8)EValueType::String].Add(&S);
			}

				// String
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			StringPointers.AddDefaulted(CS_ROUTINE_STRING_SIZE);
			UsedValues[(uint8)EValueType::StringPtr].AddDefaulted(StringPointers.Max());

			for (FString*& S : StringPointers)
			{
				S = nullptr;
				Values[(uint8)EValueType::StringPtr].Add(&S);
			}

				// Object
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			Objects.AddDefaulted(CS_ROUTINE_OBJECT_SIZE);
			UsedValues[(uint8)EValueType::Object].AddDefaulted(Objects.Max());

			for (TCsWeakObjectPtr<UObject>& Object : Objects)
			{
				Object.Reset();
				Values[(uint8)EValueType::Object].Add(&Object);
			}

				// VoidPointers
			Values.AddDefaulted();
			UsedValues.AddDefaulted();
			VoidPointers.AddDefaulted(CS_ROUTINE_VOID_POINTER_SIZE);
			UsedValues[(uint8)EValueType::Void].AddDefaulted(VoidPointers.Max());

			for (void*& V : VoidPointers)
			{
				V = nullptr;
				Values[(uint8)EValueType::Void].Add(&V);
			}
		}

		void FMap::Reset()
		{
			// Reset to default value
			for (const FInfo& Info : Infos)
			{
				const EValueType& Type = Info.Type;
				const int32& I		   = Info.Index;

				void* Ptr = Values[(uint8)Type][I];

				NValueType::SetDefaultValue(Type, Ptr);

				UsedValues[(uint8)Type][I] = false;
			}
			Infos.Reset(Infos.Max());
		}

		#pragma endregion FMap
	}

	namespace NPayload
	{
		// FImpl
		#pragma region

		FImpl::FImpl() :
			Index(INDEX_NONE),
			Group(),
			CoroutineImpl(),
			StartTime(),
			Owner(),
			AbortImpls(),
			OnAborts(),
			OnEnds(),
			ParentHandle(),
			bDoInit(true),
			bPerformFirstUpdate(true),
			AbortMessages(),
			RegisterMap(),
			bDeltaTimeScalar(false),
			DeltaTimeScalar(nullptr),
			Name(nullptr),
			Name_Internal(NAME_None)
		{
			Group = EMCsUpdateGroup::Get().GetMAX();

			Reset();
		}

		void FImpl::SetIndex(const int32& InIndex)
		{
			Index = InIndex;
		}

		void FImpl::Init(const FString& Context, UObject* InOwner, const UObject* ContextObject, const FECsUpdateGroup& UpdateGroup, const FString& InName, const FName& InNameInternal)
		{
			CS_IS_PENDING_KILL_CHECKED(InOwner)
			CS_IS_PENDING_KILL_CHECKED(ContextObject)
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, UpdateGroup)
			CS_IS_STRING_EMPTY_CHECKED(InName)
			CS_IS_NAME_NONE_CHECKED(InNameInternal)

			typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

			StartTime = TimeManagerLibrary::GetTimeChecked(Context, ContextObject, UpdateGroup);
			Owner.SetObject(InOwner);
			SetName(InName);
			SetFName(InNameInternal);
		}

		void FImpl::Reset()
		{
			CoroutineImpl.Unbind();
			StartTime.Reset();
			Owner.Reset();
			AbortImpls.Reset(AbortImpls.Max());
			OnAborts.Reset(OnAborts.Max());
			OnEnds.Reset(OnEnds.Max());
			ParentHandle.Reset();
			bDoInit = true;
			bPerformFirstUpdate = true;
			Name = nullptr;
			Name_Internal = NAME_None;

			AbortMessages.Reset(AbortMessages.Max());

			RegisterMap.Reset();
		}

		bool FImpl::IsValidChecked(const FString& Context) const
		{
			// Check CoroutineImpl is Bound
			checkf(CoroutineImpl.IsBound(), TEXT("%s: CoroutineImpl is NOT Bound to any method."), *Context);
			// Check Group is Valid
			check(EMCsUpdateGroup::Get().IsValidEnumChecked(Context, Group));
			// Check Owner is Valid
			check(Owner.IsValidChecked(Context));
			// Check AbortMessages is Valid
			{
				const int32 Count = AbortMessages.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					checkf(AbortMessages[I] != NAME_None, TEXT("%s: AbortMessages[%d]: None is NOT Valid."), *Context, I);
				}
			}
			return true;
		}

		#pragma endregion FImpl
	}
}