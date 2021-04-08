// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsLog.h"
#pragma once

// NCsFX::NParameter::IParameter
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NParameter, IParameter)

namespace NCsFX
{
	namespace NParameter
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORE_API const FString GetIntChecked;
				extern CSCORE_API const FString GetSafeInt;
				extern CSCORE_API const FString GetFloatChecked;
				extern CSCORE_API const FString GetSafeFloat;
				extern CSCORE_API const FString GetVectorChecked;
				extern CSCORE_API const FString GetSafeVector;
			}
		}

		/**
		*/
		struct CSCORE_API FLibrary
		{
		#define ParameterType NCsFX::NParameter::IParameter

		public:

			/**
			* 
			* 
			* @param Context	The calling context.
			* @param Parameter
			*/
			static bool IsValidChecked(const FString& Context, const ParameterType* Parameter);

		// Int
		#pragma region
		public:

			/**
			* Get a value of type: Int from Parameter implementing the interface: 
			* ParameterType (NCsFX::NParameter::IParameter).
			* 
			* @param Context	The calling context.
			* @param Parameter  Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* return			Int value.
			*/
			static const int32& GetIntChecked(const FString& Context, const ParameterType* Parameter);

			/**
			* Get a value of type: Int from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Parameter	Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* return			Int value.
			*/
			FORCEINLINE static const int32& GetIntChecked(const ParameterType* Parameter)
			{
				return GetIntChecked(NCached::Str::GetIntChecked, Parameter);
			}

			/**
			* Safely get a value of type: Int from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Context	The calling context.
			* @param Parameter	Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* @param Log
			* return			Int value.
			*/
			static bool GetSafeInt(const FString& Context, const ParameterType* Parameter, int32& OutValue, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get a value of type: Int from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Parameter	Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* return			Int value.
			*/
			FORCEINLINE static bool GetSafeInt(const ParameterType* Parameter, int32& OutValue)
			{
				return GetSafeInt(NCached::Str::GetSafeFloat, Parameter, OutValue, nullptr);
			}

		#pragma endregion Int

		// Float
		#pragma region
		public:

			/**
			* Get a value of type: Float from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Context	The calling context.
			* @param Parameter  Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* return			Float value.
			*/
			static const float& GetFloatChecked(const FString& Context, const ParameterType* Parameter);

			/**
			* Get a value of type: Float from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Parameter  Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* return			Float value.
			*/
			FORCEINLINE static const float& GetFloatChecked(const ParameterType* Parameter)
			{
				return GetFloatChecked(NCached::Str::GetFloatChecked, Parameter);
			}

			/**
			* Safely get a value of type: Float from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Context	The calling context.
			* @param Parameter	Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* @param Log
			* return			Float value.
			*/
			static bool GetSafeFloat(const FString& Context, const ParameterType* Parameter, float& OutValue);

			/**
			* Safely get a value of type: Float from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Parameter	Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* return			Float value.
			*/
			FORCEINLINE static bool GetSafeFloat(const ParameterType* Parameter, float& OutValue)
			{
				return GetSafeFloat(NCached::Str::GetSafeFloat, Parameter, OutValue);
			}

		#pragma endregion Float

		// Vector
		#pragma region Vector
		public:

			/**
			* Get a value of type: FVector from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Context	The calling context.
			* @param Parameter  Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* return			FVector value.
			*/
			static const FVector& GetVectorChecked(const FString& Context, const ParameterType* Parameter);

			/**
			* Get a value of type: FVector from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Parameter  Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* return			FVector value.
			*/
			FORCEINLINE static const FVector& GetVectorChecked(const ParameterType* Parameter)
			{
				return GetVectorChecked(NCached::Str::GetVectorChecked, Parameter);
			}

			/**
			* Safely get a value of type: FVector from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Context	The calling context.
			* @param Parameter	Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* @param Log
			* return			FVector value.
			*/
			static bool GetSafeVector(const FString& Context, const ParameterType* Parameter, FVector& OutValue);

			/**
			* Safely get a value of type: FVector from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Parameter	Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* return			FVector value.
			*/
			FORCEINLINE static bool GetSafeVector(const ParameterType* Parameter, FVector& OutValue)
			{
				return GetSafeVector(NCached::Str::GetSafeVector, Parameter, OutValue);
			}

		#pragma endregion Vector

		#undef ParameterType
		};
	}
}