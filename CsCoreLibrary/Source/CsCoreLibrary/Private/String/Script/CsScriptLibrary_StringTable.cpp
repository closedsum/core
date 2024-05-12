// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "String/Script/CsScriptLibrary_StringTable.h"

// CVars
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "String/CsLibrary_StringTable.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_StringTable)

// Cached
#pragma region

namespace NCsScriptLibraryStringTable
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_StringTable, SetSourceString);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_StringTable::UCsScriptLibrary_StringTable(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryStringTable::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryStringTable::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &NCsCore::NLibrary::FLog::Error
#define StringTableLibrary NCsString::NTable::FLibrary

bool UCsScriptLibrary_StringTable::SetSourceString(const FString& Context, UStringTable* StringTable, const FString& Key, const FString& SourceString)
{
	CONDITIONAL_SET_CTXT(SetSourceString);

	return StringTableLibrary::SetSafeSourceString(Ctxt, StringTable, Key, SourceString);
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
#undef StringTableLibrary