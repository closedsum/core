// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Property.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Property.h"

// Cached
#pragma region

namespace NCsScriptLibraryProperty
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, GetBoolByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, GetInt);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, GetIntByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, GetSoftObjectPtrAsStringByPath);
			// Set
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, SetBool);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, SetInt);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, SetFloat);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Property::UCsScriptLibrary_Property(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define PropertyLibrary NCsProperty::FLibrary

// Get
#pragma region

bool UCsScriptLibrary_Property::GetBoolByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	using namespace NCsScriptLibraryProperty::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetBoolByPath : Context;

	return PropertyLibrary::GetBoolPropertyValueByPath(Ctxt, Object, Object->GetClass(), Path, OutSuccess);
}

int32 UCsScriptLibrary_Property::GetIntByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	using namespace NCsScriptLibraryProperty::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetIntByPath : Context;

	return PropertyLibrary::GetIntPropertyValueByPath(Ctxt, Object, Object->GetClass(), Path, OutSuccess);
}

int32 UCsScriptLibrary_Property::GetInt(const FString& Context, UObject* Object, const FName& PropertyName, bool& OutSuccess)
{
	using namespace NCsScriptLibraryProperty::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetInt : Context;

	return PropertyLibrary::GetIntPropertyValue(Ctxt, Object, Object->GetClass(), PropertyName, OutSuccess);
}

FString UCsScriptLibrary_Property::GetSoftObjectPtrAsStringByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	using namespace NCsScriptLibraryProperty::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetSoftObjectPtrAsStringByPath : Context;

	FSoftObjectPtr SoftObject = PropertyLibrary::GetSoftObjectPropertyValueByPath(Ctxt, Object, Object->GetClass(), Path, OutSuccess);

	if (OutSuccess)
		return SoftObject.ToSoftObjectPath().ToString();
	return FString();
}

#pragma endregion Get

// Set
#pragma region

bool UCsScriptLibrary_Property::SetBool(const FString& Context, UObject* Object, const FName& PropertyName, bool Value)
{
	using namespace NCsScriptLibraryProperty::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetBool : Context;

	return PropertyLibrary::SetBoolPropertyByName(Ctxt, Object, Object->GetClass(), PropertyName, Value);
}

bool UCsScriptLibrary_Property::SetInt(const FString& Context, UObject* Object, const FName& PropertyName, int32 Value)
{
	using namespace NCsScriptLibraryProperty::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetInt : Context;

	return PropertyLibrary::SetIntPropertyByName(Ctxt, Object, Object->GetClass(), PropertyName, Value);
}

bool UCsScriptLibrary_Property::SetFloat(const FString& Context, UObject* Object, const FName& PropertyName, float Value)
{
	using namespace NCsScriptLibraryProperty::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFloat : Context;

	return PropertyLibrary::SetFloatPropertyByName(Ctxt, Object, Object->GetClass(), PropertyName, Value);
}

#pragma endregion Set

#undef PropertyLibrary