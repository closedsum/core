// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "InputCoreTypes.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class UObject;

namespace NCsInput
{
	namespace NTouch
	{
		struct CSCORELIBRARY_API FLibrary final
		{
		public:

			/**
			*
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param FingerIndex
			* @param OutPosition	(out)
			*/
			static bool GetPositionChecked(const FString& Context, const UObject* WorldContext, const ETouchIndex::Type& FingerIndex, FIntPoint& OutPosition);
		};
	}
}