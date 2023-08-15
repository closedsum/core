// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Object/Script/CsScriptLibrary_Object.h"
#include "CsCore.h"

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Object, Object_MarkPendingKill);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Object::UCsScriptLibrary_Object(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Load
#pragma region

UObject* UCsScriptLibrary_Object::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	typedef NCsObject::FLibrary ObjectLibrary;

	return ObjectLibrary::SafeLoad(Ctxt, Path);
}

UObject* UCsScriptLibrary_Object::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	typedef NCsObject::FLibrary ObjectLibrary;

	return ObjectLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

UObject* UCsScriptLibrary_Object::ConstructObject(const FString& Context, UObject* Outer, UClass* Class)
{
	using namespace NCsScriptLibraryObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ConstructObject : Context;

	void(*Log)(const FString&) = &FCsLog::Warning;

	if (!Outer)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Outer is NULL."), *Ctxt));
		return nullptr;
	}

	if (!Class)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Class is NULL."), *Ctxt));
		return nullptr;
	}
	return NewObject<UObject>(Outer, Class);
}

bool UCsScriptLibrary_Object::Object_MarkPendingKill(const FString& Context, UObject* Object)
{
	using namespace NCsScriptLibraryObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Object_MarkPendingKill : Context;

	void(*Log)(const FString&) = &FCsLog::Warning;

	if (!Object)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object is NULL."), *Ctxt));
		return false;
	}

	if (!IsValid(Object))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object: %s with Class: %s has ALREADY been marked pending kill."), *Ctxt, *(Object->GetName()), *(Object->GetClass()->GetName())));
		return false;
	}

	Object->MarkAsGarbage();
	return true;
}