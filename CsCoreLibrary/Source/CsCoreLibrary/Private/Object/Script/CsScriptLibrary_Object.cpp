// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Object/Script/CsScriptLibrary_Object.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Object)

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Object, SafeIsValid);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Object, Object_MarkPendingKill);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Object::UCsScriptLibrary_Object(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryObject::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryObject::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// Load
#pragma region

UObject* UCsScriptLibrary_Object::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(LoadBySoftObjectPath);

	return CsObjectLibrary::SafeLoad(Ctxt, Path);
}

UObject* UCsScriptLibrary_Object::LoadByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadByStringPath);

	return CsObjectLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

UObject* UCsScriptLibrary_Object::ConstructObject(const FString& Context, UObject* Outer, UClass* Class)
{
	CONDITIONAL_SET_CTXT(ConstructObject);

	return CsObjectLibrary::SafeConstruct(Ctxt, Outer, Class);
}

UObject* UCsScriptLibrary_Object::GetDefaultObject(const FString& Context, UObject* Object)
{
	CONDITIONAL_SET_CTXT(GetDefaultObject);

	return CsObjectLibrary::GetSafeDefaultObject(Ctxt, Object);
}

int32 UCsScriptLibrary_Object::Object_GetUniqueID(const FString& Context, const UObject* Object)
{
	CONDITIONAL_SET_CTXT(Object_GetUniqueID);

	return CsObjectLibrary::GetSafeUniqueID(Ctxt, Object);
}

int32 UCsScriptLibrary_Object::DOb_GetUniqueID(const FString& Context, const UObject* Object)
{
	if (UObject* DOb = CsObjectLibrary::GetSafeDefaultObject(Context, Object))
		return DOb->GetUniqueID();
	return INDEX_NONE;
}

bool UCsScriptLibrary_Object::IsValidChecked(const FString& Context, UObject* Object)
{
	CONDITIONAL_SET_CTXT(IsValidChecked);

	return CS_SCRIPT_GET_CHECKED(CsObjectLibrary::IsValidChecked(Ctxt, Object), CsObjectLibrary::SafeIsValid(Ctxt, Object));
}

bool UCsScriptLibrary_Object::SafeIsValid(const FString& Context, UObject* Object)
{
	CONDITIONAL_SET_CTXT(SafeIsValid);

	return CsObjectLibrary::SafeIsValid(Ctxt, Object);
}

bool UCsScriptLibrary_Object::Object_MarkPendingKill(const FString& Context, UObject* Object)
{
	CONDITIONAL_SET_CTXT(Object_MarkPendingKill);

	return CsObjectLibrary::SafeMarkAsGarbage(Ctxt, Object);
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT