// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
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
				extern CSCORE_API const FString GetFloat;
				extern CSCORE_API const FString GetSafeFloat;
				extern CSCORE_API const FString GetVector;
				extern CSCORE_API const FString GetSafeVector;
			}
		}

		/**
		*/
		struct CSCORE_API FLibrary
		{
		#define ParameterType NCsFX::NParameter::IParameter

		public:

			// Float

			static const float& GetFloat(const FString& Context, const ParameterType* Parameter);

			FORCEINLINE static const float& GetFloat(const ParameterType* Parameter)
			{
				return GetFloat(NCached::Str::GetFloat, Parameter);
			}

			static bool GetSafeFloat(const FString& Context, const ParameterType* Parameter, float& OutValue);

			FORCEINLINE static bool GetSafeFloat(const ParameterType* Parameter, float& OutValue)
			{
				return GetSafeFloat(NCached::Str::GetSafeFloat, Parameter, OutValue);
			}

			// Vector

			static const FVector& GetVector(const FString& Context, const ParameterType* Parameter);

			FORCEINLINE static const FVector& GetVector(const ParameterType* Parameter)
			{
				return GetVector(NCached::Str::GetVector, Parameter);
			}

			static bool GetSafeVector(const FString& Context, const ParameterType* Parameter, FVector& OutValue);

			FORCEINLINE static bool GetSafeVector(const ParameterType* Parameter, FVector& OutValue)
			{
				return GetSafeVector(NCached::Str::GetSafeVector, Parameter, OutValue);
			}

		#undef ParameterType
		};
	}
}