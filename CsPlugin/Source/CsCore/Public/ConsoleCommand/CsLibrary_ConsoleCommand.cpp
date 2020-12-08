// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#include "ConsoleCommand/CsLibrary_ConsoleCommand.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_String.h"

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

		bool FLibrary::Stream_GetValue(const FString& Context, const TCHAR*& Str, FParams_GetValue_int32& Params)
		{
			typedef NCsString::FLibrary StringLibrary;

			if (StringLibrary::Stream_GetValue(Str, *(Params.OutValue)))
			{
				if (Params.IsOutValueValid())
				{
					return true;
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("%s: %s: %d is NOT Valid from: %s. Command:"), *Context, Params.ValueNameToChar(), *(Params.OutValue), Str);
					UE_LOG(LogCs, Warning, TEXT("%s"), Params.DefinitionToChar());
					return false;
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Failed to get %s value from: %s. Command:"), *Context, Params.ValueNameToChar(), Str);
				UE_LOG(LogCs, Warning, TEXT("%s"), Params.DefinitionToChar());
				return false;
			}
		}
	}
}