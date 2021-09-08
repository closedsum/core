// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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

bool UCsScriptLibrary_Property::SetBool(const FString& Context, UObject* Object, const FName& PropertyName, bool Value)
{
	using namespace NCsScriptLibraryProperty::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetBool : Context;

	typedef NCsProperty::FLibrary PropertyLibrary;

	return PropertyLibrary::SetBoolPropertyByName(Ctxt, Object, Object->GetClass(), PropertyName, Value);
}

bool UCsScriptLibrary_Property::SetInt(const FString& Context, UObject* Object, const FName& PropertyName, int32 Value)
{
	using namespace NCsScriptLibraryProperty::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetInt : Context;

	typedef NCsProperty::FLibrary PropertyLibrary;

	return PropertyLibrary::SetIntPropertyByName(Ctxt, Object, Object->GetClass(), PropertyName, Value);
}

bool UCsScriptLibrary_Property::SetFloat(const FString& Context, UObject* Object, const FName& PropertyName, float Value)
{
	using namespace NCsScriptLibraryProperty::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFloat : Context;

	typedef NCsProperty::FLibrary PropertyLibrary;

	return PropertyLibrary::SetFloatPropertyByName(Ctxt, Object, Object->GetClass(), PropertyName, Value);
}