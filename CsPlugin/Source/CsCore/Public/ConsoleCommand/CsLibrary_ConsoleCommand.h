// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#pragma once

namespace NCsConsoleCommand
{
	namespace NLibrary
	{
		template<typename ValueType>
		struct TParams_GetValue
		{
			ValueType* OutValue;

			enum class ECheck : uint8 
			{
				None,
				Exact,
				GreaterThan,
				GreaterThanOrEqual,
				LessThan,
				LessThanOrEqual,
				RangeInclusive,
				RangeExclusive
			};

			ECheck CheckType;

			ValueType Value;
			ValueType MinValue;
			ValueType MaxValue;

			FString* ValueName;

			FString* Definition;

			TParams_GetValue() :
				OutValue(nullptr),
				CheckType(ECheck::None),
				ValueName(nullptr),
				Definition(nullptr)
			{
			}

			bool IsOutValueValid() const
			{
				// None
				if (CheckType == ECheck::None)
					return true;
				// Exact
				if (CheckType == ECheck::Exact)
					return *OutValue == Value;
				// GreaterThan
				if (CheckType == ECheck::GreaterThan)
					return *OutValue > Value;
				// GreaterThanOrEqual
				if (CheckType == ECheck::GreaterThanOrEqual)
					return *OutValue >= Value;
				// LessThan
				if (CheckType == ECheck::LessThan)
					return *OutValue < Value;
				// LessThanOrEqual
				if (CheckType == ECheck::LessThanOrEqual)
					return *OutValue <= Value;
				// RangeInclusive
				if (CheckType == ECheck::RangeInclusive)
					return *OutValue >= MinValue && *OutValue <= MaxValue;
				// RangeExclusive
				if (CheckType == ECheck::RangeExclusive)
					return *OutValue > MinValue && *OutValue < MaxValue;
				return true;
			}

			FORCEINLINE const TCHAR* ValueNameToChar() const { return **ValueName; }
			FORCEINLINE const TCHAR* DefinitionToChar() const { return **Definition; }
		};

		struct FParams_GetValue_int32 : public TParams_GetValue<int32>
		{
		private:

			typedef TParams_GetValue<int32> Super;

		public:
			
			FParams_GetValue_int32() : Super()
			{
				Value = 0;
				MinValue = 0;
				MaxValue = 0;
			}
		};

		/**
		*/
		struct CSCORE_API FLibrary
		{
			/**
			* 
			* 
			* @param Context
			* @param Str
			* @param Definition
			*/
			static bool ConsumeNextCharAndCheckNotEmpty(const FString& Context, FString& Str, const FString& Definition);



			static bool Stream_GetValue(const FString& Context, const TCHAR*& Str, FParams_GetValue_int32& Params);
		};
	}
}