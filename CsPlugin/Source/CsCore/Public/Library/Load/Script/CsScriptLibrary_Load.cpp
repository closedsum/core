// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Load/Script/CsScriptLibrary_Load.h"
#include "CsCore.h"

// Library
#include "Library/Load/CsLibrary_Load.h"
// Log
#include "Utility/CsLog.h"

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

UCsScriptLibrary_Load::UCsScriptLibrary_Load(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
	
#define LoadLibrary UCsLibrary_Load

void UCsScriptLibrary_Load::LoadObject(const FString& Context, UObject* Object, const int32& LoadFlags, const int32& LoadCodes)
{
	using namespace NCsScriptLibraryLoad::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadObject : Context;

	if (!Object)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Object is NULL."), *Ctxt);
		return;
	}

	LoadLibrary::LoadStruct(Object, Object->GetClass(), LoadFlags, LoadCodes);
}

UObject* UCsScriptLibrary_Load::LoadSoftClassPtr(const FString& Context, const TSoftClassPtr<UObject>& SoftClass, const int32& LoadFlags, const int32& LoadCodes)
{
	using namespace NCsScriptLibraryLoad::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadSoftClassPtr : Context;

	if (!SoftClass.ToSoftObjectPath().IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("%s: SoftClass is NOT NULL."), *Ctxt);
		return nullptr;
	}

	return LoadLibrary::LoadSoftClassPtrChecked(Context, SoftClass, LoadFlags, LoadCodes);
}

#undef LoadLibrary