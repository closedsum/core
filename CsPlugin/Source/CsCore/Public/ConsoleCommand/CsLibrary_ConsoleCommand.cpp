// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#include "ConsoleCommand/CsLibrary_ConsoleCommand.h"
#include "CsCore.h"

namespace NCsConsoleCommand
{
	namespace NLibrary
	{
		bool FLibrary::ConsumeNextCharAndCheckNotEmpty(const FString& Context, FString& Str, const FString& Definition)
		{
			// Remove next char (usually a blank space ' ')
			Str.RemoveAt(0);

			if (Str.IsEmpty())
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Command:"), *Context);
				UE_LOG(LogCs, Warning, TEXT("%s:"), *Definition);
				return false;
			}
			return true;
		}
	}
}