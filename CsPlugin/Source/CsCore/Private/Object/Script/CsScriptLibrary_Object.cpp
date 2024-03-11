// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Object/Script/CsScriptLibrary_Object.h"
#include "CsCore.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Object/CsLibrary_Object.h"
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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Object, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Object, LoadByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Object, ConstructObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Object, GetDefaultObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Object, Object_GetUniqueID);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Object, IsValidChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Object, Object_MarkPendingKill);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Object::UCsScriptLibrary_Object(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define ObjectLibrary NCsObject::FLibrary

// Load
#pragma region

UObject* UCsScriptLibrary_Object::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	return ObjectLibrary::SafeLoad(Ctxt, Path);
}

UObject* UCsScriptLibrary_Object::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	return ObjectLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

UObject* UCsScriptLibrary_Object::ConstructObject(const FString& Context, UObject* Outer, UClass* Class)
{
	using namespace NCsScriptLibraryObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ConstructObject : Context;

	return ObjectLibrary::SafeConstruct(Ctxt, Outer, Class);
}

UObject* UCsScriptLibrary_Object::GetDefaultObject(const FString& Context, UObject* Object)
{
	using namespace NCsScriptLibraryObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDefaultObject : Context;

	return ObjectLibrary::GetSafeDefaultObject(Ctxt, Object);
}

int32 UCsScriptLibrary_Object::Object_GetUniqueID(const FString& Context, const UObject* Object)
{
	using namespace NCsScriptLibraryObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Object_GetUniqueID : Context;

	return ObjectLibrary::GetSafeUniqueID(Ctxt, Object);
}

int32 UCsScriptLibrary_Object::DOb_GetUniqueID(const FString& Context, const UObject* Object)
{
	if (UObject* DOb = ObjectLibrary::GetSafeDefaultObject(Context, Object))
		return DOb->GetUniqueID();
	return INDEX_NONE;
}

bool UCsScriptLibrary_Object::IsValidChecked(const FString& Context, UObject* Object)
{
	using namespace NCsScriptLibraryObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsValidChecked : Context;

	return CS_SCRIPT_GET_CHECKED(ObjectLibrary::IsValidChecked(Ctxt, Object), ObjectLibrary::SafeIsValid(Ctxt, Object));
}

bool UCsScriptLibrary_Object::Object_MarkPendingKill(const FString& Context, UObject* Object)
{
	using namespace NCsScriptLibraryObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Object_MarkPendingKill : Context;

	return ObjectLibrary::SafeMarkAsGarbage(Ctxt, Object);
}

#undef ObjectLibrary