// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_ConsoleVariable.h"

// Library
#include "Library/CsLibrary_Valid.h"
// CVar
#include "HAL/IConsoleManager.h"

namespace NCsConsole
{
	namespace NVariable
	{
		IConsoleVariable* FLibrary::FindChecked(const FString& Context, const FString& Command)
		{
			CS_IS_STRING_EMPTY_CHECKED(Command)

			IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(*Command);

			CS_IS_PTR_NULL_CHECKED(CVar)
			return CVar;
		}

		void FLibrary::EnableChecked(const FString& Context, const FString& Command)
		{
			FindChecked(Context, Command)->Set(true);
		}

		void FLibrary::DisableChecked(const FString& Context, const FString& Command)
		{
			FindChecked(Context, Command)->Set(false);
		}
	}
}