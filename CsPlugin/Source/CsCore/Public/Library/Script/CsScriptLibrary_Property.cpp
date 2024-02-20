// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Property.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, GetFloatByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, GetFloatOrDoubleByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, GetNameByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, GetStringByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, GetVectorByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, GetRotatorByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, GetSoftObjectPtrAsStringByPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Property, GetClassByPath);
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

#define USING_NS_CACHED using namespace NCsScriptLibraryProperty::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryProperty::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::##__FunctionName : Context
#define LogWarning void(*Log)(const FString&) = &FCsLog::Warning;
#define PropertyLibrary NCsProperty::FLibrary

// Get
#pragma region

bool UCsScriptLibrary_Property::GetBoolByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetBoolByPath);

	LogWarning

	CS_IS_PENDING_KILL2(Object)
	return PropertyLibrary::GetBoolPropertyValueByPath(Ctxt, Object, Object->GetClass(), Path, OutSuccess);
}

int32 UCsScriptLibrary_Property::GetInt(const FString& Context, UObject* Object, const FName& PropertyName, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetInt);

	LogWarning

	CS_IS_PENDING_KILL_RET_VALUE2(Object, 0)
	return PropertyLibrary::GetIntPropertyValue(Ctxt, Object, Object->GetClass(), PropertyName, OutSuccess);
}

int32 UCsScriptLibrary_Property::GetIntByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetIntByPath);

	LogWarning

	CS_IS_PENDING_KILL_RET_VALUE2(Object, 0)
	return PropertyLibrary::GetIntPropertyValueByPath(Ctxt, Object, Object->GetClass(), Path, OutSuccess);
}

float UCsScriptLibrary_Property::GetFloatByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetFloatByPath);

	LogWarning

	CS_IS_PENDING_KILL_RET_VALUE2(Object, 0.0f)
	return PropertyLibrary::GetFloatPropertyValueByPath(Ctxt, Object, Object->GetClass(), Path, OutSuccess);
}

float UCsScriptLibrary_Property::GetFloatOrDoubleByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetFloatOrDoubleByPath);

	LogWarning

	CS_IS_PENDING_KILL_RET_VALUE2(Object, 0.0f)
	return PropertyLibrary::GetFloatOrDoublePropertyValueByPath(Ctxt, Object, Object->GetClass(), Path, OutSuccess);
}

FName UCsScriptLibrary_Property::GetNameByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetNameByPath);

	LogWarning

	CS_IS_PENDING_KILL_RET_VALUE2(Object, NAME_None)
	return PropertyLibrary::GetNamePropertyValueByPath(Ctxt, Object, Object->GetClass(), Path, OutSuccess);
}

FString UCsScriptLibrary_Property::GetStringByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetNameByPath);

	LogWarning

	CS_IS_PENDING_KILL_RET_VALUE2(Object, FString())
	return PropertyLibrary::GetStringPropertyValueByPath(Ctxt, Object, Object->GetClass(), Path, OutSuccess);
}

FVector UCsScriptLibrary_Property::GetVectorByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetVectorByPath);

	LogWarning

	CS_IS_PENDING_KILL_RET_VALUE2(Object, FVector::ZeroVector)
	return PropertyLibrary::GetVectorPropertyValueByPath(Ctxt, Object, Object->GetClass(), Path, OutSuccess);
}

FRotator UCsScriptLibrary_Property::GetRotatorByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetRotatorByPath);

	LogWarning

	CS_IS_PENDING_KILL_RET_VALUE2(Object, FRotator::ZeroRotator)
	return PropertyLibrary::GetRotatorPropertyValueByPath(Ctxt, Object, Object->GetClass(), Path, OutSuccess);
}

FString UCsScriptLibrary_Property::GetSoftObjectPtrAsStringByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetSoftObjectPtrAsStringByPath);

	LogWarning

	CS_IS_PENDING_KILL_RET_VALUE2(Object, FString())

	FSoftObjectPtr SoftObject = PropertyLibrary::GetSoftObjectPropertyValueByPath(Ctxt, Object, Object->GetClass(), Path, OutSuccess);

	if (OutSuccess)
		return SoftObject.ToSoftObjectPath().ToString();
	return FString();
}

UClass* UCsScriptLibrary_Property::GetClassByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetClassByPath);

	LogWarning

	CS_IS_PENDING_KILL2(Object)
	return PropertyLibrary::GetClassPropertyValueByPath(Ctxt, Object, Object->GetClass(), Path, OutSuccess);
}

#pragma endregion Get

// Set
#pragma region

bool UCsScriptLibrary_Property::SetBool(const FString& Context, UObject* Object, const FName& PropertyName, bool Value)
{
	CONDITIONAL_SET_CTXT(SetBool);

	LogWarning

	CS_IS_PENDING_KILL2(Object)
	return PropertyLibrary::SetBoolPropertyByName(Ctxt, Object, Object->GetClass(), PropertyName, Value);
}

bool UCsScriptLibrary_Property::SetInt(const FString& Context, UObject* Object, const FName& PropertyName, int32 Value)
{
	CONDITIONAL_SET_CTXT(SetInt);

	LogWarning

	CS_IS_PENDING_KILL2(Object)
	return PropertyLibrary::SetIntPropertyByName(Ctxt, Object, Object->GetClass(), PropertyName, Value);
}

bool UCsScriptLibrary_Property::SetFloat(const FString& Context, UObject* Object, const FName& PropertyName, float Value)
{
	CONDITIONAL_SET_CTXT(SetFloat);

	LogWarning

	CS_IS_PENDING_KILL2(Object)
	return PropertyLibrary::SetFloatPropertyByName(Ctxt, Object, Object->GetClass(), PropertyName, Value);
}

#pragma endregion Set

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogWarning
#undef PropertyLibrary