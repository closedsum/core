// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Attribute/CsAttributeSet.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Ability
#include "AttributeSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsAttributeSet)

// FCsAttributeSet
#pragma region

namespace NCsAttributeSet
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsAttributeSet, SafeLoad);
		}
	}
}

#define USING_NS_CACHED using namespace NCsAttributeSet::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsAttributeSet::NCached; \
	const FString& Context = Str::__FunctionName

UAttributeSet* FCsAttributeSet::SafeLoad(const FString& Context, void(*Log)(const FString&) /*=&NCsGameplayAbilities::FLog::Warning*/)
{
	CS_IS_SOFT_CLASS_PTR_VALID_RET_NULL(Set, UAttributeSet)

	const FSoftObjectPath& Path = Set.ToSoftObjectPath();

	if (!CsObjectLibrary::IsValidObject(Set_Internal))
	{
		Set_Class = Set.LoadSynchronous();

		if (Set_Class)
		{
			UObject* DOb = Set_Class->GetDefaultObject();
			
			if (!DOb)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get DefaultObject for Set @ Path: %s with Class: %s."), *Context, *(Path.ToString()), *(Set_Class->GetName())))
				return nullptr;
			}

			Set_Internal = CS_CAST(DOb, UObject, UAttributeSet);

			if (!Set_Internal)
				return nullptr;
			return Set_Internal;
		}
		else
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load Data @ Path: %s."), *Context, *(Path.ToString())))
			return nullptr;
		}
	}
	return Set_Internal;
}

UAttributeSet* FCsAttributeSet::SafeLoad()
{
	SET_CONTEXT(SafeLoad);

	return SafeLoad(Context, nullptr);
}

UObject* FCsAttributeSet::SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) /*=&NCsGameplayAbilities::FLog::Warning*/)
{
	CS_IS_SOFT_CLASS_PTR_VALID_RET_NULL(Set, UAttributeSet)

	const FSoftObjectPath& Path = Set.ToSoftObjectPath();
	UObject* O					= Set.LoadSynchronous();

	if (!O)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load Set at Path: %s."), *Context, *(Path.ToString())))
		return nullptr;
	}
	return O;
}

#undef USING_NS_CACHED
#undef SET_CONTEXT

#pragma endregion FCsGameplayAbility