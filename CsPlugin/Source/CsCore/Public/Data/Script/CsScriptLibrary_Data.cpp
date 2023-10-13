// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Script/CsScriptLibrary_Data.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Data/CsLibrary_Data.h"

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

#define DataLibrary NCsData::FLibrary

// ICsScriptData
#pragma region

bool UCsScriptLibrary_Data::Script_Load(const FString& Context, UObject* Object, const int32& LoadFlags)
{
	using namespace NCsScriptLibraryData::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Script_Load : Context;

	return DataLibrary::SafeScript_Load(Ctxt, Object, LoadFlags);
}

#pragma endregion ICsScriptData

#undef DataLibrary