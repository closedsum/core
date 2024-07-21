// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsEnhancedInputLibraryLog.h"

class UObject;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;

namespace NCsInput
{
	namespace NEnhanced
	{
		struct CSENHANCEDINPUTLIBRARY_API FLibrary final
		{
		public:

			static bool IsValidMappingChecked(const FString& Context, const UInputMappingContext* MappingContext);
		};

		namespace NFirst
		{
			struct CSENHANCEDINPUTLIBRARY_API FLibrary final
			{
			public:

				/**
				* Get the EnhancedInputLocalPlayerSubsytem associated with the FIRST Local Player.
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				*/
				static UEnhancedInputLocalPlayerSubsystem* GetSubsystemChecked(const FString& Context, const UObject* WorldContext);
			};
		}
	}
}