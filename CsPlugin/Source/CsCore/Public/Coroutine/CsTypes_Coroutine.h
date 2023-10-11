// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnumMap.h"
#include "Types/Property/Multi/CsProperty_Multi_FString_Enum_ThreeParams.h"
#include "Coroutine/pt.h"
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/Time/CsTypes_Update.h"
#include "Containers/CsWeakObjectPtr.h"
#include "Coroutine/CsRoutineHandle.h"

class UObject;
class AActor;
struct FCsRoutine;

namespace NCsCoroutine
{
	// State
	#pragma region

	enum class EState : uint8
	{
		Free,
		Init,
		Update,
		End,
		EState_MAX
	};

	struct CSCORE_API EMState : public TCsEnumMap<EState>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMState, EState)
	};

	namespace NState
	{
		typedef EState Type;

		namespace Ref
		{
			extern CSCORE_API const Type Free;
			extern CSCORE_API const Type Init;
			extern CSCORE_API const Type Update;
			extern CSCORE_API const Type End;
			extern CSCORE_API const Type EState_MAX;
		}

		extern CSCORE_API const uint8 MAX;
	}

	#pragma endregion State

	// Message
	#pragma region

	enum class EMessage : uint8
	{
		Notify,
		Listen,
		Abort,
		EMessage_MAX
	};

	struct CSCORE_API EMMessage : public TCsEnumMap<EMessage>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMMessage, EMessage)
	};

	namespace NMessage
	{
		typedef EMessage Type;

		namespace Ref
		{
			extern CSCORE_API const Type Notify;
			extern CSCORE_API const Type Listen;
			extern CSCORE_API const Type Abort;
			extern CSCORE_API const Type EMessage_MAX;
		}

		extern CSCORE_API const uint8 MAX;
	}

	#pragma endregion Message

	// EndReason
	#pragma region

	enum class EEndReason : uint8
	{
		EndOfExecution,
		AbortMessage,
		AbortCondition,
		OwnerIsInvalid,
		Parent,
		UniqueInstance,
		Shutdown,
		Manual,
		EEndReason_MAX
	};

	struct CSCORE_API EMEndReason : public TCsEnumMap<EEndReason>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMEndReason, EEndReason)
	};

	namespace NEndReason
	{
		typedef EEndReason Type;

		namespace Ref
		{
			extern CSCORE_API const Type EndOfExecution;
			extern CSCORE_API const Type AbortMessage;
			extern CSCORE_API const Type AbortCondition;
			extern CSCORE_API const Type OwnerIsInvalid;
			extern CSCORE_API const Type Parent;
			extern CSCORE_API const Type UniqueInstance;
			extern CSCORE_API const Type Shutdown;
			extern CSCORE_API const Type Manual;
			extern CSCORE_API const Type EEndReason_MAX;
		}

		extern CSCORE_API const uint8 MAX;
	}

	#pragma endregion EndReason

	// Transaction
	#pragma region

	enum class ETransaction : uint8
	{
		Allocate,
		Start,
		End,
		ETransaction_MAX
	};

	struct CSCORE_API EMTransaction : public TCsEnumMap<ETransaction>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMTransaction, ETransaction)
	};

	namespace NTransaction
	{
		typedef ETransaction Type;

		namespace Ref
		{
			extern CSCORE_API const Type Allocate;
			extern CSCORE_API const Type Start;
			extern CSCORE_API const Type End;
			extern CSCORE_API const Type ETransaction_MAX;
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
			return Ref::ETransaction_MAX;
		}
	}

#define ECS_COROUTINE_TRANSACTION_MAX (uint8)ETransaction::ETransaction_MAX

	#pragma endregion Transaction

	// FOwner
	#pragma region

	struct CSCORE_API FOwner
	{
	private:

		void* Owner;

		UObject* Object;
		TWeakObjectPtr<UObject> WeakObject;
		bool bObject;

		AActor* Actor;

	public:

		FOwner() :
			Owner(nullptr),
			Object(nullptr),
			WeakObject(nullptr),
			bObject(false),
			Actor(nullptr)
		{
		}

		~FOwner()
		{
		}

		FORCEINLINE void SetOwner(void* InOwner) { Owner = InOwner; }

		FORCEINLINE void* GetOwner() { return Owner; }

		void SetObject(UObject* InObject)
		{
			Owner = InObject;
			Object = InObject;
			WeakObject = Object;
			bObject = true;
			Actor = Cast<AActor>(Object);
		}

		FORCEINLINE UObject* GetObject() { return Object; }

		template<typename T>
		FORCEINLINE T* GetObject() { return Cast<T>(GetObject()); }

		FORCEINLINE UObject* GetSafeObject()
		{
			return WeakObject.IsValid() ? WeakObject.Get() : nullptr;
		}

		template<typename T>
		FORCEINLINE T* GetSafeObject() { return Cast<T>(GetSafeObject()); }

		FORCEINLINE bool IsObject() const { return bObject; }

		FORCEINLINE AActor* GetActor() { return Actor; }

		void Reset()
		{
			Owner = nullptr;
			Object = nullptr;
			WeakObject = nullptr;
			bObject = false;
			Actor = nullptr;
		}

		bool IsValidChecked(const FString& Context) const;
	};

	#pragma endregion FOwner

	namespace NRegister
	{

		// ValueType
		#pragma region

		/**
		*/
		enum class EValueType : uint8
		{
			Flag,
			Timer,
			DeltaTime,
			Int,
			UnsignedInt,
			Float,
			Double,
			Vector,
			Rotator,
			Color,
			Name,
			String,
			StringPtr,
			Object,
			Void,
			EValueType_MAX
		};

		struct CSCORE_API EMValueType : public TCsEnumMap<EValueType>
		{
			CS_ENUM_MAP_BODY(EMValueType, EValueType)
		};

		namespace NValueType
		{
			typedef EValueType Type;

			namespace Ref
			{
				extern CSCORE_API const Type Flag;
				extern CSCORE_API const Type Timer;
				extern CSCORE_API const Type DeltaTime;
				extern CSCORE_API const Type Int;
				extern CSCORE_API const Type UnsignedInt;
				extern CSCORE_API const Type Float;
				extern CSCORE_API const Type Double;
				extern CSCORE_API const Type Vector;
				extern CSCORE_API const Type Rotator;
				extern CSCORE_API const Type Color;
				extern CSCORE_API const Type Name;
				extern CSCORE_API const Type String;
				extern CSCORE_API const Type StringPtr;
				extern CSCORE_API const Type Object;
				extern CSCORE_API const Type Void;
				extern CSCORE_API const Type EValueType_MAX;
			}

			extern CSCORE_API const uint8 MAX;

			void SetDefaultValue(const Type& ValueType, void* Ptr);
			void SetValue(const Type& ValueType, void* From, void* To);

			template<typename ValueType>
			void SetValue_Internal(void* From, void* To)
			{
				ValueType* F = (ValueType*)From;
				ValueType* T = (ValueType*)To;
				*F = *T;
			}
		}
		#pragma endregion ValueType

		// FInfo
		#pragma region

		struct CSCORE_API FInfo
		{
		public:

			EValueType Type;

			int32 Index;

			FInfo() :
				Type(EValueType::EValueType_MAX),
				Index(INDEX_NONE)
			{
			}

			~FInfo()
			{
			}
		};

		#pragma endregion FInfo

#define CS_ROUTINE_FLAG_SIZE 8
#define CS_ROUTINE_TIMER_SIZE 4
#define CS_ROUTINE_DELTA_TIME_SIZE 4
#define CS_ROUTINE_INT_SIZE 16
#define CS_ROUTINE_FLOAT_SIZE 8
#define CS_ROUTINE_DOUBLE_SIZE 4
#define CS_ROUTINE_VECTOR_SIZE 4
#define CS_ROUTINE_ROTATOR_SIZE 4
#define CS_ROUTINE_COLOR_SIZE 4
#define CS_ROUTINE_NAME_SIZE 4
#define CS_ROUTINE_STRING_SIZE 4
#define CS_ROUTINE_STRING_POINTER_SIZE 4
#define CS_ROUTINE_OBJECT_SIZE 4
#define CS_ROUTINE_VOID_POINTER_SIZE 4

		// FMap
		#pragma region

		struct CSCORE_API FMap
		{
		public:

			TArray<FInfo> Infos;
			TArray<TArray<void*>> Values;

		protected:

			TArray<TArray<bool>> UsedValues;

			TArray<bool, TFixedAllocator<CS_ROUTINE_FLAG_SIZE>> Flags;
			TArray<FCsTime, TFixedAllocator<CS_ROUTINE_TIMER_SIZE>> Timers;
			TArray<FCsDeltaTime, TFixedAllocator<CS_ROUTINE_DELTA_TIME_SIZE>> DeltaTimes;
			TArray<int32, TFixedAllocator<CS_ROUTINE_INT_SIZE>> Ints;
			TArray<uint32, TFixedAllocator<CS_ROUTINE_INT_SIZE>> UnsignedInts;
			TArray<float, TFixedAllocator<CS_ROUTINE_FLOAT_SIZE>> Floats;
			TArray<double, TFixedAllocator<CS_ROUTINE_DOUBLE_SIZE>> Doubles;
			TArray<FVector3f, TFixedAllocator<CS_ROUTINE_VECTOR_SIZE>> Vectors;
			TArray<FRotator3f, TFixedAllocator<CS_ROUTINE_ROTATOR_SIZE>> Rotators;
			TArray<FLinearColor, TFixedAllocator<CS_ROUTINE_COLOR_SIZE>> Colors;
			TArray<FName, TFixedAllocator<CS_ROUTINE_NAME_SIZE>> Names;
			TArray<FString, TFixedAllocator<CS_ROUTINE_STRING_SIZE>> Strings;
			TArray<FString*, TFixedAllocator<CS_ROUTINE_STRING_POINTER_SIZE>> StringPointers;
			TArray<TCsWeakObjectPtr<UObject>, TFixedAllocator<CS_ROUTINE_OBJECT_SIZE>> Objects;
			TArray<void*, TFixedAllocator<CS_ROUTINE_VOID_POINTER_SIZE>> VoidPointers;

		public:

			FMap();

			// Set
			#pragma region

		public:

			FORCEINLINE void SetUsedValue(const EValueType& Type, const int32& InIndex)
			{
				if (!UsedValues[(uint8)Type][InIndex])
				{
					FInfo& Info = Infos.AddDefaulted_GetRef();
					Info.Type	= Type;
					Info.Index	= InIndex;

					UsedValues[(uint8)Type][InIndex] = true;
				}
			}

			FORCEINLINE void SetValue_Flag(const int32& InIndex, const bool& Value)
			{
				SetUsedValue(EValueType::Flag, InIndex);
				Flags[InIndex] = Value;
			}

			FORCEINLINE void SetValue_Timer(const int32& InIndex, const FCsTime& Value)
			{
				SetUsedValue(EValueType::Timer, InIndex);
				Timers[InIndex] = Value;
			}

			FORCEINLINE void SetValue_DeltaTime(const int32& InIndex, const FCsDeltaTime& Value)
			{
				SetUsedValue(EValueType::DeltaTime, InIndex);
				DeltaTimes[InIndex] = Value;
			}

			FORCEINLINE void SetValue_Int(const int32& InIndex, const int32& Value)
			{
				SetUsedValue(EValueType::Int, InIndex);
				Ints[InIndex] = Value;
			}

			FORCEINLINE void SetValue_UnsignedInt(const int32& InIndex, const uint32& Value)
			{
				SetUsedValue(EValueType::UnsignedInt, InIndex);
				UnsignedInts[InIndex] = Value;
			}

			FORCEINLINE void SetValue_Float(const int32& InIndex, const float& Value)
			{
				SetUsedValue(EValueType::Float, InIndex);
				Floats[InIndex] = Value;
			}

			FORCEINLINE void SetValue_Double(const int32& InIndex, const float& Value)
			{
				SetUsedValue(EValueType::Double, InIndex);
				Doubles[InIndex] = Value;
			}

			FORCEINLINE void SetValue_Vector(const int32& InIndex, const FVector3f& Value)
			{
				SetUsedValue(EValueType::Vector, InIndex);
				Vectors[InIndex] = Value;
			}

			FORCEINLINE void SetValue_Rotator(const int32& InIndex, const FRotator3f& Value)
			{
				SetUsedValue(EValueType::Rotator, InIndex);
				Rotators[InIndex] = Value;
			}

			FORCEINLINE void SetValue_Color(const int32& InIndex, const FLinearColor& Value)
			{
				SetUsedValue(EValueType::Color, InIndex);
				Colors[InIndex] = Value;
			}

			FORCEINLINE void SetValue_Name(const int32& InIndex, const FName& Value)
			{
				SetUsedValue(EValueType::Name, InIndex);
				Names[InIndex] = Value;
			}

			FORCEINLINE void SetValue_String(const int32& InIndex, const FString& Value)
			{
				SetUsedValue(EValueType::String, InIndex);
				Strings[InIndex] = Value;
			}

			FORCEINLINE void SetValue_StringPtr(const int32& InIndex, FString* Value)
			{
				SetUsedValue(EValueType::StringPtr, InIndex);
				StringPointers[InIndex] = Value;
			}

			FORCEINLINE void SetValue_Object(const int32& InIndex, UObject* Value)
			{
				SetUsedValue(EValueType::Object, InIndex);
				Objects[InIndex].Set(Value);
			}

			FORCEINLINE void SetValue_Void(const int32& InIndex, void* Value)
			{
				SetUsedValue(EValueType::Void, InIndex);
				VoidPointers[InIndex] = Value;
			}
			#pragma endregion Set

			// Get
			#pragma region
			public:
	
				FORCEINLINE bool& GetValue_Flag(const int32& InIndex)
				{
					SetUsedValue(EValueType::Flag, InIndex);
					return Flags[InIndex];
				}

				FORCEINLINE FCsTime& GetValue_Timer(const int32& InIndex)
				{
					SetUsedValue(EValueType::Timer, InIndex);
					return Timers[InIndex];
				}

				FORCEINLINE FCsDeltaTime& GetValue_DeltaTime(const int32& InIndex)
				{
					SetUsedValue(EValueType::DeltaTime, InIndex);
					return DeltaTimes[InIndex];
				}

				FORCEINLINE int32& GetValue_Int(const int32& InIndex)
				{
					SetUsedValue(EValueType::Int, InIndex);
					return Ints[InIndex];
				}

				FORCEINLINE uint32& GetValue_UnsignedInt(const int32& InIndex)
				{
					SetUsedValue(EValueType::UnsignedInt, InIndex);
					return UnsignedInts[InIndex];
				}

				FORCEINLINE float& GetValue_Float(const int32& InIndex)
				{
					SetUsedValue(EValueType::Float, InIndex);
					return Floats[InIndex];
				}

				FORCEINLINE double& GetValue_Double(const int32& InIndex)
				{
					SetUsedValue(EValueType::Double, InIndex);
					return Doubles[InIndex];
				}

				FORCEINLINE FVector3f& GetValue_Vector(const int32& InIndex)
				{
					SetUsedValue(EValueType::Vector, InIndex);
					return Vectors[InIndex];
				}

				FORCEINLINE FRotator3f& GetValue_Rotator(const int32& InIndex)
				{
					SetUsedValue(EValueType::Rotator, InIndex);
					return Rotators[InIndex];
				}

				FORCEINLINE FLinearColor& GetValue_Color(const int32& InIndex)
				{
					SetUsedValue(EValueType::Color, InIndex);
					return Colors[InIndex];
				}

				FORCEINLINE FName& GetValue_Name(const int32& InIndex)
				{
					SetUsedValue(EValueType::Name, InIndex);
					return Names[InIndex];
				}

				FORCEINLINE FString& GetValue_String(const int32& InIndex)
				{
					SetUsedValue(EValueType::String, InIndex);
					return Strings[InIndex];
				}

				FORCEINLINE FString* GetValue_StringPtr(const int32& InIndex)
				{
					SetUsedValue(EValueType::StringPtr, InIndex);
					return StringPointers[InIndex];
				}

				FORCEINLINE UObject* GetValue_Object(const int32& InIndex)
				{
					SetUsedValue(EValueType::Object, InIndex);
					return Objects[InIndex].GetSafe();
				}

				template<typename T>
				FORCEINLINE T* GetValue_Object(const int32& InIndex)
				{
					SetUsedValue(EValueType::Object, InIndex);
					return Objects[InIndex].GetSafe<T>();
				}

				FORCEINLINE void* GetValue_Void(const int32& InIndex)
				{
					SetUsedValue(EValueType::Void, InIndex);
					return VoidPointers[InIndex];
				}

				template<typename T>
				FORCEINLINE T* GetValue_Void(const int32& InIndex)
				{
					SetUsedValue(EValueType::Void, InIndex);
					return (T*)VoidPointers[InIndex];
				}

			#pragma endregion Get
		public:

			void Reset();
		};

		#pragma endregion FMap
	}

	// Run
	DECLARE_DELEGATE_RetVal_OneParam(char, FImpl, FCsRoutine*);
	// Abort Condition
	DECLARE_DELEGATE_RetVal_OneParam(bool, FAbortConditionImpl, FCsRoutine*);
	DECLARE_DELEGATE_OneParam(FOnAbort, FCsRoutine*);
	// End
	DECLARE_DELEGATE_OneParam(FOnEnd, FCsRoutine*);

	namespace NPayload
	{
		// FPayload
		#pragma region

		struct CSCORE_API FImpl
		{
		private:

			typedef NCsCoroutine::NRegister::EValueType ValueType;
			typedef NCsCoroutine::NRegister::FMap RegisterMapType;

			int32 Index;

		public:

			FECsUpdateGroup Group;

			NCsCoroutine::FImpl CoroutineImpl;

			FCsTime StartTime;

			NCsCoroutine::FOwner Owner;

			TArray<FAbortConditionImpl> AbortImpls;

			TArray<FOnAbort> OnAborts;

			TArray<FOnEnd> OnEnds;

			FCsRoutineHandle ParentHandle;

			bool bDoInit;

			bool bPerformFirstUpdate;

			TArray<FName> AbortMessages;

			RegisterMapType RegisterMap;

		public:

			FImpl();

			~FImpl() {}

			void SetIndex(const int32& InIndex);

			FORCEINLINE const int32& GetIndex() const
			{
				return Index;
			}

			template<typename T>
			FORCEINLINE void Init(const FString& Context, T* Object, char(T::*Delegate)(FCsRoutine*), const UObject* ContextObject, const FECsUpdateGroup& UpdateGroup, const FString& InName, const FName& InNameInternal)
			{
				static_assert(std::is_base_of<UObject, T>(), "T is NOT of type: UObject.");

				CoroutineImpl.BindUObject(Object, Delegate);
				Init(Context, Object, ContextObject, UpdateGroup, InName, InNameInternal);
			}

			template<typename T>
			FORCEINLINE void Init(const FString& Context, T* Object, char(T::* Delegate)(FCsRoutine*), UObject* InOwner, const UObject* ContextObject, const FECsUpdateGroup& UpdateGroup, const FString& InName, const FName& InNameInternal)
			{
				static_assert(!std::is_base_of<UObject, T>(), "T IS of type: UObject.");

				CoroutineImpl.BindRaw(Object, Delegate);
				Init(Context, InOwner, ContextObject, UpdateGroup, InName, InNameInternal);
			}

			FORCEINLINE void Init(const FString& Context, char(* Delegate)(FCsRoutine*), UObject* InOwner, const UObject* ContextObject, const FECsUpdateGroup& UpdateGroup, const FString& InName, const FName& InNameInternal)
			{
				CoroutineImpl.BindStatic(Delegate);
				Init(Context, InOwner, ContextObject, UpdateGroup, InName, InNameInternal);
			}

			void Init(const FString& Context, UObject* InOwner, const UObject* ContextObject, const FECsUpdateGroup& UpdateGroup, const FString& InName, const FName& InNameInternal);

			void Reset();

			bool IsValidChecked(const FString& Context) const;

		// Registers
		#pragma region

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

		#pragma endregion Registers

		// Name
		#pragma region
		protected:

			FString* Name;

			FName Name_Internal;

		public:

			FORCEINLINE void SetName(const FString& InName)
			{
				Name = const_cast<FString*>(&InName);
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
		};

		#pragma endregion FPayload
	}
}

// Payload
#pragma region

// Flag (bool)
#define CS_COROUTINE_PAYLOAD_PASS_FLAG_START int32 __Coroutine__Payload__Flag__Counter__ = 0;
#define CS_COROUTINE_PAYLOAD_PASS_FLAG(__Payload, __Value) __Payload->SetValue_Flag(__Coroutine__Payload__Flag__Counter__, __Value); \
	++__Coroutine__Payload__Flag__Counter__
// Int (int32)
#define CS_COROUTINE_PAYLOAD_PASS_INT_START int32 __Coroutine__Payload__Int__Counter__ = 0;
#define CS_COROUTINE_PAYLOAD_PASS_INT(__Payload, __Value) __Payload->SetValue_Int(__Coroutine__Payload__Int__Counter__, __Value); \
	++__Coroutine__Payload__Int__Counter__
// Unsigned Int (uint32)
#define CS_COROUTINE_PAYLOAD_PASS_UNSIGNED_INT_START int32 __Coroutine__Payload__UnsignedInt__Counter__ = 0;
#define CS_COROUTINE_PAYLOAD_PASS_UNSIGNED_INT(__Payload, __Value) __Payload->SetValue_UnsignedInt(__Coroutine__Payload__UnsignedInt__Counter__, __Value); \
	++__Coroutine__Payload__UnsignedInt__Counter__
// Float
#define CS_COROUTINE_PAYLOAD_PASS_FLOAT_START int32 __Coroutine__Payload__Float__Counter__ = 0;
#define CS_COROUTINE_PAYLOAD_PASS_FLOAT(__Payload, __Value) __Payload->SetValue_Float(__Coroutine__Payload__Float__Counter__, __Value); \
	++__Coroutine__Payload__Float__Counter__
// Vector (FVector3f)
#define CS_COROUTINE_PAYLOAD_PASS_VECTOR_START int32 __Coroutine__Payload__Vector__Counter__ = 0;
#define CS_COROUTINE_PAYLOAD_PASS_VECTOR(__Payload, __Value) __Payload->SetValue_Vector(__Coroutine__Payload__Vector__Counter__, __Value); \
	++__Coroutine__Payload__Vector__Counter__
// Color (FLinearColor)
#define CS_COROUTINE_PAYLOAD_PASS_COLOR_START int32 __Coroutine__Payload__Color__Counter__ = 0;
#define CS_COROUTINE_PAYLOAD_PASS_COLOR(__Payload, __Value) __Payload->SetValue_Color(__Coroutine__Payload__Color__Counter__, __Value); \
	++__Coroutine__Payload__Color__Counter__
// Name
#define CS_COROUTINE_PAYLOAD_PASS_NAME_START int32 __Coroutine__Payload__Name__Counter__ = 0;
#define CS_COROUTINE_PAYLOAD_PASS_NAME(__Payload, __Value) __Payload->SetValue_Name(__Coroutine__Payload__Name__Counter__, __Value); \
	++__Coroutine__Payload__Name__Counter__
// String
#define CS_COROUTINE_PAYLOAD_PASS_STRING_START int32 __Coroutine__Payload__String__Counter__ = 0;
#define CS_COROUTINE_PAYLOAD_PASS_STRING(__Payload, __Value) __Payload->SetValue_String(__Coroutine__Payload__String__Counter__, __Value); \
	++__Coroutine__Payload__String__Counter__
// Void
#define CS_COROUTINE_PAYLOAD_PASS_OBJECT_START int32 __Coroutine__Payload__Object__Counter__ = 0;
#define CS_COROUTINE_PAYLOAD_PASS_OBJECT(__Payload, __Value) __Payload->SetValue_Object(__Coroutine__Payload__Object__Counter__, __Value); \
	++__Coroutine__Payload__Object__Counter__
// Void
#define CS_COROUTINE_PAYLOAD_PASS_VOID_START int32 __Coroutine__Payload__Void__Counter__ = 0;
#define CS_COROUTINE_PAYLOAD_PASS_VOID(__Payload, __Value) __Payload->SetValue_Void(__Coroutine__Payload__Void__Counter__, __Value); \
	++__Coroutine__Payload__Void__Counter__

#pragma endregion Payload

// Routine
#pragma region

// Flag (bool)
#define CS_COROUTINE_READ_FLAG_START int32 __Coroutine__Read__Flag__Counter__ = 0;
#define CS_COROUTINE_READ_FLAG(__R, __VariableName) bool __VariableName = __R->GetValue_Flag(__Coroutine__Read__Flag__Counter__); \
	++__Coroutine__Read__Flag__Counter__
#define CS_COROUTINE_READ_FLAG_REF(__R, __VariableName) bool& __VariableName = __R->GetValue_Flag(__Coroutine__Read__Flag__Counter__); \
	++__Coroutine__Read__Flag__Counter__
#define CS_COROUTINE_READ_FLAG_CONST(__R, __VariableName) const bool __VariableName = __R->GetValue_Flag(__Coroutine__Read__Flag__Counter__); \
	++__Coroutine__Read__Flag__Counter__
#define CS_COROUTINE_READ_FLAG_CONST_REF(__R, __VariableName) const bool& __VariableName = __R->GetValue_Flag(__Coroutine__Read__Flag__Counter__); \
	++__Coroutine__Read__Flag__Counter__
// DeltaTime
#define CS_COROUTINE_READ_DELTA_TIME_START int32 __Coroutine__Read__DeltaTime__Counter__ = 0;
#define CS_COROUTINE_READ_DELTA_TIME(__R, __VariableName) FCsDeltaTime __VariableName = __R->GetValue_DeltaTime(__Coroutine__Read__DeltaTime__Counter__); \
	++__Coroutine__Read__DeltaTime__Counter__
#define CS_COROUTINE_READ_DELTA_TIME_REF(__R, __VariableName) FCsDeltaTime& __VariableName = __R->GetValue_DeltaTime(__Coroutine__Read__DeltaTime__Counter__); \
	++__Coroutine__Read__DeltaTime__Counter__
#define CS_COROUTINE_READ_DELTA_TIME_CONST(__R, __VariableName) const FCsDeltaTime __VariableName = __R->GetValue_DeltaTime(__Coroutine__Read__DeltaTime__Counter__); \
	++__Coroutine__Read__DeltaTime__Counter__
#define CS_COROUTINE_READ_DELTA_TIME_CONST_REF(__R, __VariableName) const FCsDeltaTime& __VariableName = __R->GetValue_DeltaTime(__Coroutine__Read__DeltaTime__Counter__); \
	++__Coroutine__Read__DeltaTime__Counter__
// Int (int32)
#define CS_COROUTINE_READ_INT_START int32 __Coroutine__Read__Int__Counter__ = 0;
#define CS_COROUTINE_READ_INT(__R, __VariableName) int32 __VariableName = __R->GetValue_Int(__Coroutine__Read__Int__Counter__); \
	++__Coroutine__Read__Int__Counter__
#define CS_COROUTINE_READ_INT_REF(__R, __VariableName) int32& __VariableName = __R->GetValue_Int(__Coroutine__Read__Int__Counter__); \
	++__Coroutine__Read__Int__Counter__
#define CS_COROUTINE_READ_INT_CONST(__R, __VariableName) const int32 __VariableName = __R->GetValue_Int(__Coroutine__Read__Int__Counter__); \
	++__Coroutine__Read__Int__Counter__
#define CS_COROUTINE_READ_INT_CONST_REF(__R, __VariableName) const int32& __VariableName = __R->GetValue_Int(__Coroutine__Read__Int__Counter__); \
	++__Coroutine__Read__Int__Counter__
#define CS_COROUTINE_READ_INT_AS_ENUM(__R, __VariableName, __EnumType) __EnumType __VariableName = (__EnumType)(__R->GetValue_Int(__Coroutine__Read__Int__Counter__)); \
	++__Coroutine__Read__Int__Counter__
#define CS_COROUTINE_READ_INT_AS_ENUM_CONST(__R, __VariableName, __EnumType) const __EnumType __VariableName = (__EnumType)(__R->GetValue_Int(__Coroutine__Read__Int__Counter__)); \
	++__Coroutine__Read__Int__Counter__
// Unsigned Int (uint32)
#define CS_COROUTINE_READ_UNSIGNED_INT_START int32 __Coroutine__Read__UnsignedInt__Counter__ = 0;
#define CS_COROUTINE_READ_UNSIGNED_INT(__R, __VariableName) uint32 __VariableName = __R->GetValue_UnsignedInt(__Coroutine__Read__UnsignedInt__Counter__); \
	++__Coroutine__Read__UnsignedInt__Counter__
#define CS_COROUTINE_READ_UNSIGNED_INT_REF(__R, __VariableName) uint32& __VariableName = __R->GetValue_UnsignedInt(__Coroutine__Read__UnsignedInt__Counter__); \
	++__Coroutine__Read__UnsignedInt__Counter__
#define CS_COROUTINE_READ_UNSIGNED_INT_CONST(__R, __VariableName) const uint32 __VariableName = __R->GetValue_UnsignedInt(__Coroutine__Read__UnsignedInt__Counter__); \
	++__Coroutine__Read__UnsignedInt__Counter__
#define CS_COROUTINE_READ_UNSIGNED_INT_CONST_REF(__R, __VariableName) const uint32& __VariableName = __R->GetValue_UnsignedInt(__Coroutine__Read__UnsignedInt__Counter__); \
	++__Coroutine__Read__UnsignedInt__Counter__
#define CS_COROUTINE_READ_UNSIGNED_INT_AS_ENUM(__R, __VariableName, __EnumType) __EnumType __VariableName = (__EnumType)(__R->GetValue_UnsignedInt(__Coroutine__Read__UnsignedInt__Counter__)); \
	++__Coroutine__Read__UnsignedInt__Counter__
#define CS_COROUTINE_READ_UNSIGNED_INT_AS_ENUM_CONST(__R, __VariableName, __EnumType) const __EnumType __VariableName = (__EnumType)(__R->GetValue_UnsignedInt(__Coroutine__Read__UnsignedInt__Counter__)); \
	++__Coroutine__Read__UnsignedInt__Counter__
// Float
#define CS_COROUTINE_READ_FLOAT_START int32 __Coroutine__Read__Float__Counter__ = 0;
#define CS_COROUTINE_READ_FLOAT(__R, __VariableName) float __VariableName = __R->GetValue_Float(__Coroutine__Read__Float__Counter__); \
	++__Coroutine__Read__Float__Counter__
#define CS_COROUTINE_READ_FLOAT_REF(__R, __VariableName) float& __VariableName = __R->GetValue_Float(__Coroutine__Read__Float__Counter__); \
	++__Coroutine__Read__Float__Counter__
#define CS_COROUTINE_READ_FLOAT_CONST(__R, __VariableName) const float __VariableName = __R->GetValue_Float(__Coroutine__Read__Float__Counter__); \
	++__Coroutine__Read__Float__Counter__
#define CS_COROUTINE_READ_FLOAT_CONST_REF(__R, __VariableName) const float& __VariableName = __R->GetValue_Float(__Coroutine__Read__Float__Counter__); \
	++__Coroutine__Read__Float__Counter__
// Vector (FVector3f)
#define CS_COROUTINE_READ_VECTOR_START int32 __Coroutine__Read__Vector__Counter__ = 0;
#define CS_COROUTINE_READ_VECTOR(__R, __VariableName) FVector3f __VariableName = __R->GetValue_Vector(__Coroutine__Read__Vector__Counter__); \
	++__Coroutine__Read__Vector__Counter__
#define CS_COROUTINE_READ_VECTOR_REF(__R, __VariableName) FVector3f& __VariableName = __R->GetValue_Vector(__Coroutine__Read__Vector__Counter__); \
	++__Coroutine__Read__Vector__Counter__
#define CS_COROUTINE_READ_VECTOR_CONST(__R, __VariableName) const FVector3f __VariableName = __R->GetValue_Vector(__Coroutine__Read__Vector__Counter__); \
	++__Coroutine__Read__Vector__Counter__
#define CS_COROUTINE_READ_VECTOR_CONST_REF(__R, __VariableName) const FVector3f& __VariableName = __R->GetValue_Vector(__Coroutine__Read__Vector__Counter__); \
	++__Coroutine__Read__Vector__Counter__
// Color (FLinearColor)
#define CS_COROUTINE_READ_COLOR_START int32 __Coroutine__Read__Color__Counter__ = 0;
#define CS_COROUTINE_READ_COLOR(__R, __VariableName) FLinearColor __VariableName = __R->GetValue_Color(__Coroutine__Read__Color__Counter__); \
	++__Coroutine__Read__Color__Counter__
#define CS_COROUTINE_READ_COLOR_REF(__R, __VariableName) FLinearColor& __VariableName = __R->GetValue_Color(__Coroutine__Read__Color__Counter__); \
	++__Coroutine__Read__Color__Counter__
#define CS_COROUTINE_READ_COLOR_CONST(__R, __VariableName) const FLinearColor __VariableName = __R->GetValue_Color(__Coroutine__Read__Color__Counter__); \
	++__Coroutine__Read__Color__Counter__
#define CS_COROUTINE_READ_COLOR_CONST_REF(__R, __VariableName) const FLinearColor& __VariableName = __R->GetValue_Color(__Coroutine__Read__Color__Counter__); \
	++__Coroutine__Read__Color__Counter__
// Name
#define CS_COROUTINE_READ_NAME_START int32 __Coroutine__Read__Name__Counter__ = 0;
#define CS_COROUTINE_READ_NAME(__R, __VariableName) FName __VariableName = __R->GetValue_Name(__Coroutine__Read__Name__Counter__); \
	++__Coroutine__Read__Name__Counter__
#define CS_COROUTINE_READ_NAME_REF(__R, __VariableName) FName& __VariableName = __R->GetValue_Name(__Coroutine__Read__Name__Counter__); \
	++__Coroutine__Read__Name__Counter__
#define CS_COROUTINE_READ_NAME_CONST(__R, __VariableName) const FName __VariableName = __R->GetValue_Name(__Coroutine__Read__Name__Counter__); \
	++__Coroutine__Read__Name__Counter__
#define CS_COROUTINE_READ_NAME_CONST_REF(__R, __VariableName) const FName& __VariableName = __R->GetValue_Name(__Coroutine__Read__Name__Counter__); \
	++__Coroutine__Read__Name__Counter__
// String
#define CS_COROUTINE_READ_STRING_START int32 __Coroutine__Read__String__Counter__ = 0;
#define CS_COROUTINE_READ_STRING(__R, __VariableName) FString __VariableName = __R->GetValue_String(__Coroutine__Read__String__Counter__); \
	++__Coroutine__Read__String__Counter__
#define CS_COROUTINE_READ_STRING_REF(__R, __VariableName) FString& __VariableName = __R->GetValue_String(__Coroutine__Read__String__Counter__); \
	++__Coroutine__Read__String__Counter__
#define CS_COROUTINE_READ_STRING_CONST(__R, __VariableName) const FString __VariableName = __R->GetValue_String(__Coroutine__Read__String__Counter__); \
	++__Coroutine__Read__String__Counter__
#define CS_COROUTINE_READ_STRING_CONST_REF(__R, __VariableName) const FString& __VariableName = __R->GetValue_String(__Coroutine__Read__String__Counter__); \
	++__Coroutine__Read__String__Counter__
// Object
#define CS_COROUTINE_READ_OBJECT_START int32 __Coroutine__Read__Object__Counter__ = 0;
#define CS_COROUTINE_READ_OBJECT(__R, __VariableName) UObject* __VariableName = __R->GetValue_Object(__Coroutine__Read__Object__Counter__); \
	++__Coroutine__Read__Object__Counter__
#define CS_COROUTINE_READ_OBJECT_AS(__R, __VariableName, __ObjectType) __ObjectType* __VariableName = __R->GetValue_Object<__ObjectType>(__Coroutine__Read__Object__Counter__); \
	++__Coroutine__Read__Object__Counter__
// Void
#define CS_COROUTINE_READ_VOID_START int32 __Coroutine__Read__Void__Counter__ = 0;
#define CS_COROUTINE_READ_VOID(__R, __VariableName, __ObjectType) __ObjectType* __VariableName = __R->GetValue_Void<__ObjectType>(__Coroutine__Read__Void__Counter__); \
	++__Coroutine__Read__Void__Counter__

#pragma endregion Routine

#define CS_ROUTINE_END -1
#define CS_ROUTINE_FREE -2

#define CS_COROUTINE_DECLARE(Func)	virtual void Func(); \
									static char Func##_Internal(struct FCsRoutine* r); \
									struct FCsRoutine* Func##_Internal_Routine;
#define CS_COROUTINE(Class, Func) char Class::Func(FCsRoutine* r)

#define CS_COROUTINE_INIT(r)  PT_INIT(&((r)->pt))
#define CS_COROUTINE_BEGIN(r)   { char PT_YIELD_FLAG = 1; LC_RESUME((&((r)->pt))->lc)
#define CS_COROUTINE_END(r)	(r)->State = NCsCoroutine::EState::End; LC_END((&((r)->pt))->lc); PT_YIELD_FLAG = 0; \
							PT_INIT(&((r)->pt)); return PT_ENDED; }			
#define CS_COROUTINE_EXIT(r)	(r)->State = NCsCoroutine::EState::End; PT_EXIT(&((r)->pt))
#define CS_COROUTINE_YIELD(r)	PT_YIELD(&((r)->pt));
#define CS_COROUTINE_WAIT_UNTIL(r, condition) PT_WAIT_UNTIL(&((r)->pt), condition);