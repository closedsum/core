// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Templates
#include "UObject/ObjectPtr.h"
// Log
#include "Utility/CsEnhancedInputLibraryLog.h"

class UInputTrigger;

namespace NCsInput
{
	namespace NEnhanced
	{
		namespace NInputTrigger
		{
			struct CSENHANCEDINPUTLIBRARY_API FLibrary final
			{
			public:

				static bool IsPressedOrReleasedChecked(const FString& Context, const UInputTrigger* InputTrigger);

				static bool IsPressedOrReleased(const FString& Context, const UInputTrigger* InputTrigger);

				static bool IsPressedOrReleasedOrDown(const FString& Context, const UInputTrigger* InputTrigger);

				static bool IsPressed(const FString& Context, const UInputTrigger* InputTrigger);

				static bool IsReleased(const FString& Context, const UInputTrigger* InputTrigger);

				static bool HasPressedOrReleasedChecked(const FString& Context, const TArray<TObjectPtr<UInputTrigger>>& Triggers);

				static bool HasPressedOrReleased(const FString& Context, const TArray<TObjectPtr<UInputTrigger>>& Triggers);

				static bool HasPressedOrReleasedOrDownChecked(const FString& Context, const TArray<TObjectPtr<UInputTrigger>>& Triggers);

				static bool HasPressedOrReleasedOrDown(const FString& Context, const TArray<TObjectPtr<UInputTrigger>>& Triggers);

				static bool HasPressed(const FString& Context, const TArray<TObjectPtr<UInputTrigger>>& Triggers);

				static bool HasReleased(const FString& Context, const TArray<TObjectPtr<UInputTrigger>>& Triggers);
			};
		}
	}
}