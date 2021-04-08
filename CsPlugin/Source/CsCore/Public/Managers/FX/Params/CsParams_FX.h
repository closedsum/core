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

				FName Name;
				FName* Name_Emu;

			public:

				EValue ValueType;

			private:

				int32 Value;
				int32* Value_Emu;

			public:

				FIntType() :
					Index(INDEX_NONE),
					Name(NAME_None),
					Name_Emu(nullptr),
					ValueType(EValue::Float),
					Value(0),
					Value_Emu(nullptr)
				{
					Name_Emu  = &Name;
					Value_Emu = &Value;
				}

				FORCEINLINE void SetIndex(const int32& InIndex) { Index = InIndex; }

				FORCEINLINE void SetName(const FName& InName)
				{
					Name	 = InName;
					Name_Emu = &Name;
				}
				FORCEINLINE void SetName(FName* InName) { Name_Emu = InName; }

				FORCEINLINE void SetValue(const int32& InValue)
				{
					Value	  = InValue;
					Value_Emu = &Value;
				}
				FORCEINLINE void SetValue(int32* InValue) { Value_Emu = InValue; }

			// IParameter
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const FName& GetName() const { return *Name_Emu; }
				FORCEINLINE const EValue& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<int32*>(Value_Emu); }

			#pragma endregion IParameter

				FORCEINLINE const int32& GetValue() const { return *Value_Emu; }

				FORCEINLINE bool IsValidChecked(const FString& Context) const
				{
					// Check Name is Valid
					checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);
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

				FName Name;
				FName* Name_Emu;

			public:

				EValue ValueType;

			private:

				float Value;
				float* Value_Emu;

			public:

				FFloatType() :
					Index(INDEX_NONE),
					Name(NAME_None),
					Name_Emu(nullptr),
					ValueType(EValue::Float),
					Value(0.0f),
					Value_Emu(nullptr)
				{
					Name_Emu  = &Name;
					Value_Emu = &Value;
				}

				FORCEINLINE void SetIndex(const int32& InIndex) { Index = InIndex; }

				FORCEINLINE void SetName(const FName& InName)
				{
					Name	 = InName;
					Name_Emu = &Name;
				}
				FORCEINLINE void SetName(FName* InName) { Name_Emu = InName; }

				FORCEINLINE void SetValue(const float& InValue)
				{
					Value	  = InValue;
					Value_Emu = &Value;
				}
				FORCEINLINE void SetValue(float* InValue) { Value_Emu = InValue; }

			// IParameter
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const FName& GetName() const { return *Name_Emu; }
				FORCEINLINE const EValue& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<float*>(Value_Emu); }

			#pragma endregion IParameter

				FORCEINLINE const float& GetValue() const { return *Value_Emu; }

				FORCEINLINE bool IsValidChecked(const FString& Context) const
				{
					// Check Name is Valid
					checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);
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

				FName Name;
				FName* Name_Emu;

			public:

				EValue ValueType;

			private:

				FVector Value;
				FVector* Value_Emu;

			public:

				FVectorType() :
					Index(INDEX_NONE),
					Name(NAME_None),
					Name_Emu(nullptr),
					ValueType(EValue::Vector),
					Value(0.0f),
					Value_Emu(nullptr)
				{
					Name_Emu  = &Name;
					Value_Emu = &Value;
				}

				FORCEINLINE void SetIndex(const int32& InIndex) { Index = InIndex; }

				FORCEINLINE void SetName(const FName& InName)
				{
					Name	 = InName;
					Name_Emu = &Name;
				}
				FORCEINLINE void SetName(FName* InName) { Name_Emu = InName; }

				FORCEINLINE void SetValue(const FVector& InValue)
				{
					Value	  = InValue;
					Value_Emu = &Value;
				}
				FORCEINLINE void SetValue(FVector* InValue) { Value_Emu = InValue; }

			// IParameter
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const FName& GetName() const { return *Name_Emu; }
				FORCEINLINE const EValue& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<FVector*>(Value_Emu); }

			#pragma endregion IParameter

				FORCEINLINE const FVector& GetValue() const { return *Value_Emu; }

				FORCEINLINE bool IsValidChecked(const FString& Context) const
				{
					// Check Name is Valid
					checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);
					// Check ValueType is Valid
					checkf(ValueType == EValue::Vector, TEXT("%s: ValueType: %s is NOT Vector."), *Context, EMValue::Get().ToChar(ValueType));
					return true;
				}
			};
		}
	}
}