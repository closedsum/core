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

		namespace NFloat
		{
			/**
			* Container holding information for Niagara Float Parameter
			*/
			struct CSCORE_API FFloatType : IParameter
			{
			private:

				int32 Index;

			public:

				FName Name;

			private:

				EValue ValueType;

			public:

				float Value;

				FFloatType() :
					Index(INDEX_NONE),
					Name(NAME_None),
					ValueType(EValue::Float),
					Value(0.0f)
				{
				}

				FORCEINLINE void SetIndex(const int32& InIndex) { Index = InIndex; }

			// IParameter
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const FName& GetName() const { return Name; }
				FORCEINLINE const EValue& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<float*>(&Value); }

			#pragma endregion IParameter

				FORCEINLINE const float& GetValue() const { return Value; }
			};

			/**
			* Container "emulating" a container holding information for Niagara Float Parameter
			* and has pointers to the appropriate members of the emulated container.
			*/
			struct CSCORE_API FFloatTypeEmu : IParameter
			{
			private:

				int32 Index;

				FName* Name;

				EValue ValueType;

				float* Value;

			public:

				FFloatTypeEmu() :
					Index(INDEX_NONE),
					Name(nullptr),
					ValueType(EValue::Float),
					Value(nullptr)
				{
				}

			
				FORCEINLINE void SetName(FName* InValue) { Name = InValue; }
				FORCEINLINE void SetValue(float* InValue) { Value = InValue; }

			// IParameter
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const FName& GetName() const { return *Name; }
				FORCEINLINE const EValue& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<float*>(Value); }

			#pragma endregion IParameter

				FORCEINLINE const float& GetValue() const { return *Value; }
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

			public:

				FName Name;

			private:

				EValue ValueType;

			public:

				FVector Value;

				FVectorType() :
					Index(INDEX_NONE),
					Name(NAME_None),
					ValueType(EValue::Vector),
					Value(0.0f)
				{
				}

				FORCEINLINE void SetIndex(const int32& InIndex) { Index = InIndex; }

			// IParameter
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const FName& GetName() const { return Name; }
				FORCEINLINE const EValue& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<FVector*>(&Value); }

			#pragma endregion IParameter

				FORCEINLINE const FVector& GetValue() const { return Value; }
			};

			/**
			* Container "emulating" a container holding information for Niagara Vector Parameter
			* and has pointers to the appropriate members of the emulated container.
			*/
			struct CSCORE_API FVectorTypeEmu : IParameter
			{
			private:

				int32 Index;

				FName* Name;

				EValue ValueType;

				FVector* Value;

			public:

				FVectorTypeEmu() :
					Index(INDEX_NONE),
					Name(nullptr),
					ValueType(EValue::Vector),
					Value(nullptr)
				{
				}

			
				FORCEINLINE void SetName(FName* InValue) { Name = InValue; }
				FORCEINLINE void SetValue(FVector* InValue) { Value = InValue; }

			// IParameter
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const FName& GetName() const { return *Name; }
				FORCEINLINE const EValue& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<FVector*>(Value); }

			#pragma endregion IParameter

				FORCEINLINE const FVector& GetValue() const { return *Value; }
			};
		}
	}
}