// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Script/CsScriptLibrary_Object.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Log
#include "Utility/CsLog.h"

// Cached
#pragma region

namespace NCsScriptLibraryObject
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Object, ConstructObject);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Object::UCsScriptLibrary_Object(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UObject* UCsScriptLibrary_Object::ConstructObject(const FString& Context, UObject* Outer, UClass* Class)
{
	using namespace NCsScriptLibraryObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ConstructObject : Context;

	void(*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_PTR_NULL_RET_NULL(Outer)

	CS_IS_PTR_NULL_RET_NULL(Class)

	return NewObject<UObject>(Outer, Class);
}