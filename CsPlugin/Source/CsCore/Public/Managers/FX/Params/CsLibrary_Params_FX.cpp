// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Params/CsLibrary_Params_FX.h"

#include "Managers/FX/Params/CsParams_FX.h"

namespace NCsFX
{
	namespace NParameter
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetFloat);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetSafeFloat);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetVector);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetSafeVector);
			}
		}

		#define ParameterType NCsFX::NParameter::IParameter

		// Float

		const float& FLibrary::GetFloat(const FString& Context, const ParameterType* Parameter)
		{
			checkf(Parameter, TEXT("%s: Parameter is NULL."), *Context);

			checkf(Parameter->GetValueType() == EValue::Float, TEXT("%s: Parameter->GetValueType(): %s != Float."), *Context, EMValue::Get().ToChar(Parameter->GetValueType()));

			return *(float*)(Parameter->GetValuePtr());
		}

		bool FLibrary::GetSafeFloat(const FString& Context, const ParameterType* Parameter, float& OutValue)
		{
			checkf(Parameter, TEXT("%s: Parameter is NULL."), *Context);

			if (Parameter->GetValueType() == EValue::Float)
			{
				OutValue = *(float*)(Parameter->GetValuePtr());
				return true;
			}
			return false;
		}

		// Vector

		const FVector& FLibrary::GetVector(const FString& Context, const ParameterType* Parameter)
		{
			checkf(Parameter, TEXT("%s: Parameter is NULL."), *Context);

			checkf(Parameter->GetValueType() == EValue::Vector, TEXT("%s: Parameter->GetValueType(): %s != Vector."), *Context, EMValue::Get().ToChar(Parameter->GetValueType()));

			return *(FVector*)(Parameter->GetValuePtr());
		}

		bool FLibrary::GetSafeVector(const FString& Context, const ParameterType* Parameter, FVector& OutValue)
		{
			checkf(Parameter, TEXT("%s: Parameter is NULL."), *Context);

			if (Parameter->GetValueType() == EValue::Vector)
			{
				OutValue = *(FVector*)(Parameter->GetValuePtr());
				return true;
			}
			return false;
		}

		#undef ParameterType
	}
}