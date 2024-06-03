// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Script/CsScriptLibrary_Data.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Data/CsLibrary_Data.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Data)

// Cached
#pragma region

namespace NCsScriptLibraryData
{
	namespace NCached
	{
		namespace Str
		{
			// ICsScriptData
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Data, Script_Load);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Data::UCsScriptLibrary_Data(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryData::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryData::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define DataLibrary NCsData::FLibrary

// ICsScriptData
#pragma region

bool UCsScriptLibrary_Data::Script_Load(const FString& Context, UObject* Object, const int32& LoadFlags, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(Script_Load);

	return DataLibrary::SafeScript_Load(Ctxt, Object, LoadFlags, OutSuccess);
}

#pragma endregion ICsScriptData

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef DataLibrary