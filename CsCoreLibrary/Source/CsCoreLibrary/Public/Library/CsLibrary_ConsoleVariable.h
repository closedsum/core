// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Containers/UnrealString.h"

class IConsoleVariable;

namespace NCsConsole
{
	namespace NVariable
	{
		/**
		* Library of functions related to Console Variables
		*/
		struct CSCORELIBRARY_API FLibrary final
		{
		public:

			static IConsoleVariable* FindChecked(const FString& Context, const FString& Command);

			static void EnableChecked(const FString& Context, const FString& Command);

			static void DisableChecked(const FString& Context, const FString& Command);
		};
	}
}