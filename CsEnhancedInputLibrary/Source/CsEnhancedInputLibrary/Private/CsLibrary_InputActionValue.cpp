// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsLibrary_InputActionValue.h"

// Types
#include "CsMacro_Misc.h"

namespace NCsInput
{
	namespace NEnhanced
	{
		namespace NInputActionValue
		{
			using LogClassType = NCsInput::NEnhanced::NLibrary::FLog;

			CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

			bool FLibrary::GetBoolChecked(const FString& Context, const FInputActionValue& Value)
			{
				checkf(Value.GetValueType() == EInputActionValueType::Boolean, TEXT("%s: Value is NOT Boolean Type."), *Context);
				return Value.Get<bool>();
			}

			bool FLibrary::GetSafeBool(const FString& Context, const FInputActionValue& Value, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				OutSuccess = false;

				if (Value.GetValueType() != EInputActionValueType::Boolean)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Value is NOT Boolean Type."), *Context))
					return false;
				}

				OutSuccess = true;
				return Value.Get<bool>();
			}

			float FLibrary::GetFloatChecked(const FString& Context, const FInputActionValue& Value)
			{
				checkf(Value.GetValueType() == EInputActionValueType::Axis1D, TEXT("%s: Value is NOT Float Type."), *Context);
				return Value.Get<float>();
			}

			float FLibrary::GetSafeFloat(const FString& Context, const FInputActionValue& Value, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				OutSuccess = false;

				if (Value.GetValueType() != EInputActionValueType::Axis1D)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Value is NOT Float Type."), *Context))
					return 0.0f;
				}

				OutSuccess = true;
				return Value.Get<float>();
			}

			FVector2D FLibrary::GetVector2DChecked(const FString& Context, const FInputActionValue& Value)
			{
				checkf(Value.GetValueType() == EInputActionValueType::Axis2D, TEXT("%s: Value is NOT Vector2D Type."), *Context);
				return Value.Get<FVector2D>();
			}

			FVector2D FLibrary::GetSafeVector2D(const FString& Context, const FInputActionValue& Value, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				OutSuccess = false;

				if (Value.GetValueType() != EInputActionValueType::Axis2D)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Value is NOT Vector2D Type."), *Context))
					return FVector2D::ZeroVector;
				}

				OutSuccess = true;
				return Value.Get<FVector2D>();
			}

			FVector FLibrary::GetVectorChecked(const FString& Context, const FInputActionValue& Value)
			{
				checkf(Value.GetValueType() == EInputActionValueType::Axis3D, TEXT("%s: Value is NOT Vector Type."), *Context);
				return Value.Get<FVector>();
			}

			FVector FLibrary::GetSafeVector(const FString& Context, const FInputActionValue& Value, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				OutSuccess = false;

				if (Value.GetValueType() != EInputActionValueType::Axis3D)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Value is NOT Vector Type."), *Context))
					return FVector::ZeroVector;
				}

				OutSuccess = true;
				return Value.Get<FVector>();
			}
		}
	}
}