// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Params/CsLibrary_Params_FX.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// FX
#include "Managers/FX/Params/CsParams_FX.h"

namespace NCsFX
{
	namespace NParameter
	{
		namespace NCached
		{
			namespace Str
			{
				CSFX_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetIntChecked);
				CSFX_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetSafeInt);
				CSFX_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetFloatChecked);
				CSFX_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetSafeFloat);
				CSFX_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetVectorChecked);
				CSFX_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NParameter::FLibrary, GetSafeVector);
			}
		}

		#define LogLevel void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/
		
		using ParameterType = NCsFX::NParameter::IParameter;

		bool FLibrary::IsValidChecked(const FString& Context, const ParameterType* Parameter)
		{
			CS_IS_PTR_NULL_CHECKED(Parameter)
			CS_IS_NAME_NONE_CHECKED(Parameter->GetName())
			CS_IS_ENUM_VALID_CHECKED(EMValue, Parameter->GetValueType())
			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const ParameterType* Parameter, LogLevel)
		{
			CS_IS_PTR_NULL(Parameter)
			CS_IS_NAME_NONE(Parameter->GetName())
			CS_IS_ENUM_VALID(EMValue, EValue, Parameter->GetValueType())
			return true;
		}

		// Int
		#pragma region

		const int32& FLibrary::GetIntChecked(const FString& Context, const ParameterType* Parameter)
		{
			CS_IS_PTR_NULL_CHECKED(Parameter)

			checkf(Parameter->GetValueType() == EValue::Int, TEXT("%s: Parameter->GetValueType(): %s != Int."), *Context, EMValue::Get().ToChar(Parameter->GetValueType()));
			return *(int32*)(Parameter->GetValuePtr());
		}

		bool FLibrary::GetSafeInt(const FString& Context, const ParameterType* Parameter, int32& OutValue, LogLevel)
		{
			CS_IS_PTR_NULL(Parameter)

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
			CS_IS_PTR_NULL_CHECKED(Parameter)

			checkf(Parameter->GetValueType() == EValue::Float, TEXT("%s: Parameter->GetValueType(): %s != Float."), *Context, EMValue::Get().ToChar(Parameter->GetValueType()));
			return *(float*)(Parameter->GetValuePtr());
		}

		bool FLibrary::GetSafeFloat(const FString& Context, const ParameterType* Parameter, float& OutValue)
		{
			CS_IS_PTR_NULL_CHECKED(Parameter)

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

		const FVector3f& FLibrary::GetVectorChecked(const FString& Context, const ParameterType* Parameter)
		{
			CS_IS_PTR_NULL_CHECKED(Parameter)

			checkf(Parameter->GetValueType() == EValue::Vector, TEXT("%s: Parameter->GetValueType(): %s != Vector."), *Context, EMValue::Get().ToChar(Parameter->GetValueType()));
			return *(FVector3f*)(Parameter->GetValuePtr());
		}

		bool FLibrary::GetSafeVector(const FString& Context, const ParameterType* Parameter, FVector3f& OutValue)
		{
			CS_IS_PTR_NULL_CHECKED(Parameter)

			if (Parameter->GetValueType() == EValue::Vector)
			{
				OutValue = *(FVector3f*)(Parameter->GetValuePtr());
				return true;
			}
			return false;
		}

		#pragma endregion Vector

		#undef LogLevel
	}
}