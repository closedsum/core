// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "String/CsLibrary_StringTable.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// String
#include "Internationalization/StringTable.h"
#include "Internationalization/StringTableCore.h"

namespace NCsString
{
	namespace NTable
	{
	#define LogWarning void(*Log)(const FString&) /*=FCsLog::Warning*/

		bool FLibrary::SetSafeSourceString(const FString& Context, UStringTable* StringTable, const FTextKey& InKey, const FString& InSourceString, LogWarning)
		{
			CS_IS_PENDING_KILL(StringTable)

			if (InKey.IsEmpty())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InKey is EMPTY."), *Context));
				return false;
			}

			FStringTableRef Ref = StringTable->GetMutableStringTable();
			Ref->SetSourceString(InKey, InSourceString);
			return true;
		}

	#undef LogWarning
	}
}