// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"

#pragma once

namespace NCsFX
{
	namespace NParameter
	{
		/**
		*/
		enum class EValue : uint8 
		{
			Int,
			Float,
			Vector,
			EValue_MAX
		};

		struct CSCORE_API EMValue final : public TCsEnumMap<EValue>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMValue, EValue)
		};

		namespace NValue
		{
			typedef EValue Type;

			namespace Ref
			{
				extern CSCORE_API const Type Int;
				extern CSCORE_API const Type Float;
				extern CSCORE_API const Type Vector;
				extern CSCORE_API const Type EValue_MAX;
			}

			extern CSCORE_API const uint8 MAX;

			FORCEINLINE uint32 GetSizeInBytes(const Type& InType)
			{
				if (InType == Type::Int)
					return sizeof(int32);
				if (InType == Type::Float)
					return sizeof(float);
				if (InType == Type::Vector)
					return sizeof(FVector);
				checkf(0, TEXT("NCsFX::NParameter::NValue::GetSizeInBytes: InType is NOT Valid."));
				return 0;
			}
		}

		/**
		*/
		struct CSCORE_API IParameter
		{
		public:

			virtual ~IParameter() {}

			virtual const int32& GetIndex() const = 0;

			virtual const FName& GetName() const = 0;

			virtual const EValue& GetValueType() const = 0;

			virtual void* GetValuePtr() const = 0;

			virtual uint32 GetSizeInBytes() const = 0;
		};

		namespace NInt
		{
			/**
			* Container holding information for Niagara Int Parameter
			*/
			struct CSCORE_API FIntType : IParameter
			{
			private:

				int32 Index;

				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)

			public:

				EValue ValueType;

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Value, int32)

			public:

				FIntType() :
					Index(INDEX_NONE),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					ValueType(EValue::Float),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0)
				{
					CS_CTOR_SET_MEMBER_PROXY(Name);
					CS_CTOR_SET_MEMBER_PROXY(Value);
				}

				FORCEINLINE void SetIndex(const int32& InIndex) { Index = InIndex; }

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Name, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, int32)

			// IParameter
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const EValue& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<int32*>(Value_Proxy); }
				FORCEINLINE uint32 GetSizeInBytes() const { return sizeof(int32); }

			#pragma endregion IParameter

				FORCEINLINE bool IsValidChecked(const FString& Context) const
				{
					// Check Name is Valid
					checkf(GetName() != NAME_None, TEXT("%s: GetName(): None is NOT Valid."), *Context);
					// Check ValueType is Valid
					checkf(ValueType == EValue::Int, TEXT("%s: ValueType: %s is NOT Int."), *Context, EMValue::Get().ToChar(ValueType));
					return true;
				}
			};
		}

		namespace NFloat
		{
			/**
			* Container holding information for Niagara Float Parameter
			*/
			struct CSCORE_API FFloatType : IParameter
			{
			private:

				int32 Index;

				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)

			public:

				EValue ValueType;

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Value, float)

			public:

				FFloatType() :
					Index(INDEX_NONE),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					ValueType(EValue::Float),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(Name);
					CS_CTOR_SET_MEMBER_PROXY(Value);
				}

				FORCEINLINE void SetIndex(const int32& InIndex) { Index = InIndex; }

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Name, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, float)

			// IParameter
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const EValue& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<float*>(Value_Proxy); }
				FORCEINLINE uint32 GetSizeInBytes() const { return sizeof(float); }

			#pragma endregion IParameter

				FORCEINLINE bool IsValidChecked(const FString& Context) const
				{
					// Check Name is Valid
					checkf(GetName() != NAME_None, TEXT("%s: GetName(): None is NOT Valid."), *Context);
					// Check ValueType is Valid
					checkf(ValueType == EValue::Float, TEXT("%s: ValueType: %s is NOT Float."), *Context, EMValue::Get().ToChar(ValueType));
					return true;
				}
			};
		}

		namespace NVector
		{
			/**
			* Container holding information for Niagara Vector Parameter
			*/
			struct CSCORE_API FVectorType : IParameter
			{
			private:

				int32 Index;

				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)

			public:

				EValue ValueType;

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Value, FVector)

			public:

				FVectorType() :
					Index(INDEX_NONE),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					ValueType(EValue::Vector),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(Name);
					CS_CTOR_SET_MEMBER_PROXY(Value);
				}

				FORCEINLINE void SetIndex(const int32& InIndex) { Index = InIndex; }

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Name, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, FVector)

			// IParameter
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const EValue& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<FVector*>(Value_Proxy); }
				FORCEINLINE uint32 GetSizeInBytes() const { return sizeof(FVector); }

			#pragma endregion IParameter

				FORCEINLINE bool IsValidChecked(const FString& Context) const
				{
					// Check Name is Valid
					checkf(GetName() != NAME_None, TEXT("%s: GetName(): None is NOT Valid."), *Context);
					// Check ValueType is Valid
					checkf(ValueType == EValue::Vector, TEXT("%s: ValueType: %s is NOT Vector."), *Context, EMValue::Get().ToChar(ValueType));
					return true;
				}
			};
		}
	}
}