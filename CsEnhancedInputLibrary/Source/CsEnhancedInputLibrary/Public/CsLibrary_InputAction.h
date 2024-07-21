// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsEnhancedInputLibraryLog.h"

class UInputAction;

namespace NCsInput
{
	namespace NEnhanced
	{
		namespace NInputAction
		{
			struct CSENHANCEDINPUTLIBRARY_API FLibrary final
			{
			public:

				static bool IsBool(const FString& Context, const UInputAction* InputAction);

				static bool HasPressedOrReleasedChecked(const FString& Context, const UInputAction* InputAction);

				//static bool HasPressed(const FString& Context, const UInputAction* InputAction);

				//static bool HasReleased(const FString& Context, const UInputAction* InputAction);

				//static bool HasPressedOrReleasedOrDownChecked(const FString& Context, const UInputAction* InputAction);
			};
		}
	}
}