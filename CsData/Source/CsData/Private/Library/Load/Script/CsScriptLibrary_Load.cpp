// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Load/Script/CsScriptLibrary_Load.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/Load/CsLibrary_Load.h"
#include "Library/CsLibrary_Valid.h"
// Log
#include "Utility/CsDataLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Load)

namespace NCsScriptLibraryLoad
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Load, LoadObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Load, LoadSoftClassPtr);
		}
	}
}

void(*UCsScriptLibrary_Load::Log)(const FString&) = &NCsData::FLog::Warning;

UCsScriptLibrary_Load::UCsScriptLibrary_Load(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryLoad::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryLoad::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

bool UCsScriptLibrary_Load::LoadObject(const FString& Context, UObject* Object, const int32& LoadFlags, const int32& LoadCodes)
{
	CONDITIONAL_SET_CTXT(LoadObject);

	CS_IS_PTR_NULL2(Object)

	CsLoadLibrary::LoadStruct(Object, Object->GetClass(), LoadFlags, LoadCodes);
	return true;
}

UObject* UCsScriptLibrary_Load::LoadSoftClassPtr(const FString& Context, const TSoftClassPtr<UObject>& SoftClass, const int32& LoadFlags, const int32& LoadCodes)
{
	CONDITIONAL_SET_CTXT(LoadSoftClassPtr);

	// TODO: Add CS_IS_SOFT_CLASS_PTR_VALID_RET_NULL2
	CS_IS_SOFT_CLASS_PTR_VALID_RET_NULL(SoftClass, UObject)

	return CsLoadLibrary::LoadSoftClassPtrChecked(Context, SoftClass, LoadFlags, LoadCodes);
}

bool UCsScriptLibrary_Load::UnloadObject(const FString& Context, UObject* Object)
{
	CONDITIONAL_SET_CTXT(LoadObject);

	CsLoadLibrary::UnloadStruct(Object, Object->GetClass());
	return true;
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT