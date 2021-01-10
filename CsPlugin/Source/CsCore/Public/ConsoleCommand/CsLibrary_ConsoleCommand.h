// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#pragma once
// Library
#include "Library/CsLibrary_String.h"

namespace NCsConsoleCommand
{
	namespace NLibrary
	{
		/**
		* Template for params used in Stream_GetValue or any other GetValue methods in 
		* FLibrary (NCsConsoleCommand::NLibrary::FLibrary)
		*/
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

			void(*Log)(const FString&);

			TParams_GetValue() :
				OutValue(nullptr),
				CheckType(ECheck::None),
				ValueName(nullptr),
				Definition(nullptr),
				Log(nullptr)
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

		/**
		* int32 specialization
		*/
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

			FORCEINLINE FString OutValueToString() const { return FString::Printf(TEXT("%d"), *OutValue); }
		};

		/**
		* float specialization
		*/
		struct FParams_GetValue_float : public TParams_GetValue<float>
		{
		private:

			typedef TParams_GetValue<float> Super;

		public:

			FParams_GetValue_float() : Super()
			{
				Value = 0;
				MinValue = 0;
				MaxValue = 0;
			}

			FORCEINLINE FString OutValueToString() const { return FString::Printf(TEXT("%f"), *OutValue); }
		};

		struct FParams_GetValue_Vector
		{
		public:

			FVector* OutValue;

			FString* ValueName;

			FString* Definition;

			void(*Log)(const FString&);

			FParams_GetValue_Vector() :
				OutValue(nullptr),
				ValueName(nullptr),
				Definition(nullptr),
				Log(nullptr)
			{
			}

			bool IsOutValueValid() const { return true; }

			FORCEINLINE const TCHAR* ValueNameToChar() const { return **ValueName; }
			FORCEINLINE const TCHAR* DefinitionToChar() const { return **Definition; }

			FORCEINLINE FString OutValueToString() const { return OutValue->ToString(); }
		};

		/**
		*/
		struct CSCORE_API FLibrary
		{
			/**
			* Get a value of type: EnumType from the CHAR ptr / string Str.
			* 
			* @param Context		The calling context.
			* @param Str			The string / CHAR ptr to get an EnumType from.
			* @param OutValue		The EnumStructType to get from Str.
			* @param EnumName		Name of the OutValue.
			* @param Definition		The definition of the Command.
			* @param Log			Log function for printing any warnings.
			*/
			template<typename EnumMapType, typename EnumType>
			static bool GetEnum(const FString& Context, const TCHAR*& Str, EnumType& OutValue, const FString& EnumName, const FString& Definition, void(*Log)(const FString&))
			{
				typedef NCsString::FLibrary StringLibrary;

				FString OutString;

				StringLibrary::Stream_GetValue(Str, OutString, true);

				if (OutString.IsEmpty())
				{
					Log(FString::Printf(TEXT("%s: %s: %s is NOT Valid. Command:"), *Context, *EnumName, *OutString));
					Log(FString::Printf(TEXT("%s"), *Definition));
					return false;
				}

				FName StringAsName = FName(*OutString);

				// Try a string conversion
				OutValue = EnumMapType::Get().GetSafeEnum(StringAsName);

				if (OutValue == EnumMapType::Get().GetMAX())
				{
					// Try int32
					int32 Value = FCString::Atoi(*OutString);

					if (Value >= 0 ||
						Value < EnumMapType::Get().Num())
					{
						OutValue = EnumMapType::Get().GetSafeEnumAt(Value);
					}
				}

				if (OutValue == EnumMapType::Get().GetMAX())
				{
					return false;
				}
				return true;
			}

			/**
			* Get a value of type: EnumStructType from the CHAR ptr / string Str.
			* 
			* @param Context		The calling context.
			* @param Str			The string / CHAR ptr to get an EnumStructType from.
			* @param OutValue		The EnumStructType to get from Str.
			* @param EnumName		Name of the OutValue.
			* @param Definition		The definition of the Command.
			* @param Log			Log function for printing any warnings.
			*/
			template<typename EnumMapType, typename EnumStructType>
			static bool GetEnumStruct(const FString& Context, const TCHAR*& Str, EnumStructType& OutValue, const FString& EnumName, const FString& Definition, void(*Log)(const FString&))
			{
				typedef NCsString::FLibrary StringLibrary;

				FString OutString;

				StringLibrary::Stream_GetValue(Str, OutString, true);

				if (OutString.IsEmpty())
				{
					Log(FString::Printf(TEXT("%s: %s: %s is NOT Valid. Command:"), *Context, *EnumName, *OutString));
					Log(FString::Printf(TEXT("%s"), *Definition));
					return false;
				}

				FName StringAsName = FName(*OutString);

				// Try a string conversion
				OutValue = EnumMapType::Get().GetSafeEnum(StringAsName);

				if (OutValue == EnumMapType::Get().GetMAX())
				{
					// Try int32
					int32 Value = FCString::Atoi(*OutString);

					if (Value >= 0 ||
						Value < EnumMapType::Get().Num())
					{
						OutValue = EnumMapType::Get().GetSafeEnumAt(Value);
					}
				}

				if (OutValue == EnumMapType::Get().GetMAX())
				{
					return false;
				}
				return true;
			}

			/**
			* Consume the next CHAR in the string Str and then check if Str is empty.
			* This utility function is used to "advance" pass empty / black / ' ' characters
			* to get to the next chunk of characters.
			* 
			* @param Context		The calling context.
			* @param Str			String from which to consume char.
			* @param Definition		Console command definition.
			*/
			static bool ConsumeNextCharAndCheckNotEmpty(const FString& Context, FString& Str, const FString& Definition);

			/**
			* Get a value of type: int32 from a Stream / TCHAR ptr.
			* 
			* @param Context	The calling context.
			* @param Str		String from which to get value.
			* @param Params
			*/
			template<typename ParamsType>
			static bool Stream_GetValue(const FString& Context, const TCHAR*& Str, ParamsType& Params)
			{
				typedef NCsString::FLibrary StringLibrary;

				if (StringLibrary::Stream_GetValue(Str, *(Params.OutValue)))
				{
					if (Params.IsOutValueValid())
					{
						return true;
					}
					else
					{
						if (Params.Log)
						{
							Params.Log(FString::Printf(TEXT("%s: %s: %d is NOT Valid from: %s. Command:"), *Context, Params.ValueNameToChar(), *(Params.OutValueToString()), Str));
							Params.Log(FString::Printf(TEXT("%s"), Params.DefinitionToChar()));
						}
						return false;
					}
				}
				else
				{
					if (Params.Log)
					{
						Params.Log(FString::Printf(TEXT("%s: Failed to get %s value from: %s. Command:"), *Context, Params.ValueNameToChar(), Str));
						Params.Log(FString::Printf(TEXT("%s"), Params.DefinitionToChar()));
					}
					return false;
				}
			}
		};
	}
}