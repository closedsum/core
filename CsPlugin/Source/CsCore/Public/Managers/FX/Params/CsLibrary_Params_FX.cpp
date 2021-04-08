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
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetIntChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetSafeInt);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetFloatChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetSafeFloat);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetVectorChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetSafeVector);
			}
		}

		#define ParameterType NCsFX::NParameter::IParameter

		bool FLibrary::IsValidChecked(const FString& Context, const ParameterType* Parameter)
		{
			checkf(Parameter, TEXT("%s: Parameter is NULL."), *Context);

			checkf(Parameter->GetName() != NAME_None, TEXT("%s: Parameter->GetName(): None is NOT Valid."), *Context);

			check(EMValue::Get().IsValidEnumChecked(Context, Parameter->GetValueType()));

			return true;
		}

		// Int
		#pragma region

		const int32& FLibrary::GetIntChecked(const FString& Context, const ParameterType* Parameter)
		{
			checkf(Parameter, TEXT("%s: Parameter is NULL."), *Context);

			checkf(Parameter->GetValueType() == EValue::Float, TEXT("%s: Parameter->GetValueType(): %s != Float."), *Context, EMValue::Get().ToChar(Parameter->GetValueType()));

			return *(int32*)(Parameter->GetValuePtr());
		}

		bool FLibrary::GetSafeInt(const FString& Context, const ParameterType* Parameter, int32& OutValue, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
		{
			if (!Parameter)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Parameter is NULL."), *Context));
				return false;
			}

			if (Parameter->GetValueType() == EValue::Int)
			{
				OutValue = *(int32*)(Parameter->GetValuePtr());
				return true;
			}
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Parameter's ValueType: %s is NOT Int."), *Context, EMValue::Get().ToChar(Parameter->GetValueType())));
			return false;
		}

		#pragma endregion Int

		// Float
		#pragma region 

		const float& FLibrary::GetFloatChecked(const FString& Context, const ParameterType* Parameter)
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

		#pragma endregion Float

		// Vector
		#pragma region

		const FVector& FLibrary::GetVectorChecked(const FString& Context, const ParameterType* Parameter)
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

		#pragma endregion Vector

		#undef ParameterType
	}
}