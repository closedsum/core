// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
#include "CsMacro_Namespace.h"
// Log
#include "Utility/CsFXLog.h"

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
				extern CSFX_API const FString GetIntChecked;
				extern CSFX_API const FString GetSafeInt;
				extern CSFX_API const FString GetFloatChecked;
				extern CSFX_API const FString GetSafeFloat;
				extern CSFX_API const FString GetVectorChecked;
				extern CSFX_API const FString GetSafeVector;
			}
		}

		/**
		*/
		struct CSFX_API FLibrary
		{
		private:

			CS_DECLARE_STATIC_LOG_LEVEL

			using ParameterType = NCsFX::NParameter::IParameter;

		public:

			/**
			* Check if the Parameter is Valid with checks.
			* 
			* @param Context	The calling context.
			* @param Parameter
			*/
			static bool IsValidChecked(const FString& Context, const ParameterType* Parameter);

			/**
			* Check if the Parameter is Valid.
			*
			* @param Context	The calling context.
			* @param Parameter
			*/
			static bool IsValid(const FString& Context, const ParameterType* Parameter, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
			static bool GetSafeInt(const FString& Context, const ParameterType* Parameter, int32& OutValue, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
			* Get a value of type: FVector3f from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Context	The calling context.
			* @param Parameter  Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* return			FVector3f value.
			*/
			static const FVector3f& GetVectorChecked(const FString& Context, const ParameterType* Parameter);

			/**
			* Get a value of type: FVector3f from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Parameter  Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* return			FVector3f value.
			*/
			FORCEINLINE static const FVector3f& GetVectorChecked(const ParameterType* Parameter)
			{
				return GetVectorChecked(NCached::Str::GetVectorChecked, Parameter);
			}

			/**
			* Safely get a value of type: FVector3f from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Context	The calling context.
			* @param Parameter	Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* @param Log
			* return			FVector3f value.
			*/
			static bool GetSafeVector(const FString& Context, const ParameterType* Parameter, FVector3f& OutValue);

			/**
			* Safely get a value of type: FVector3f from Parameter implementing the interface:
			* ParameterType (NCsFX::NParameter::IParameter).
			*
			* @param Parameter	Object which implements the interface: ParameterType (NCsFX::NParameter::IParameter).
			* return			FVector3f value.
			*/
			FORCEINLINE static bool GetSafeVector(const ParameterType* Parameter, FVector3f& OutValue)
			{
				return GetSafeVector(NCached::Str::GetSafeVector, Parameter, OutValue);
			}

		#pragma endregion Vector
		};
	}
}

using CsFXParameterLibrary = NCsFX::NParameter::FLibrary;