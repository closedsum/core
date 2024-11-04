// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
// Input
#include "InputActionValue.h"
// Log
#include "Utility/CsEnhancedInputLibraryLog.h"

class UInputAction;

namespace NCsInput
{
	namespace NEnhanced
	{
		namespace NInputActionValue
		{
			struct CSENHANCEDINPUTLIBRARY_API FLibrary final
			{
			private:

				CS_DECLARE_STATIC_LOG_LEVEL

			public:

				static bool GetBoolChecked(const FString& Context, const FInputActionValue& Value);
				static bool GetSafeBool(const FString& Context, const FInputActionValue& Value, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
				FORCEINLINE static bool GetSafeBool(const FString& Context, const FInputActionValue& Value, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					bool OutSuccess = false;
					return GetSafeBool(Context, Value, OutSuccess, Log);
				}

				static float GetFloatChecked(const FString& Context, const FInputActionValue& Value);
				static float GetSafeFloat(const FString& Context, const FInputActionValue& Value, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
				FORCEINLINE static float GetSafeFloat(const FString& Context, const FInputActionValue& Value, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					bool OutSuccess = false;
					return GetSafeFloat(Context, Value, OutSuccess, Log);
				}

				static FVector2D GetVector2DChecked(const FString& Context, const FInputActionValue& Value);
				static FVector2D GetSafeVector2D(const FString& Context, const FInputActionValue& Value, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
				FORCEINLINE static FVector2D GetSafeVector2D(const FString& Context, const FInputActionValue& Value, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					bool OutSuccess = false;
					return GetSafeVector2D(Context, Value, OutSuccess, Log);
				}

				static FVector GetVectorChecked(const FString& Context, const FInputActionValue& Value);
				static FVector GetSafeVector(const FString& Context, const FInputActionValue& Value, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
				FORCEINLINE static FVector GetSafeVector(const FString& Context, const FInputActionValue& Value, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					bool OutSuccess = false;
					return GetSafeVector(Context, Value, OutSuccess, Log);
				}
			};
		}
	}
}

using CsInputActionValueLibrary = NCsInput::NEnhanced::NInputActionValue::FLibrary;