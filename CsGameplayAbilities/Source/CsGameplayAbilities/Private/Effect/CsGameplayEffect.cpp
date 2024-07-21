// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Effect/CsGameplayEffect.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Ability
#include "GameplayEffect.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsGameplayEffect)

// FCsGameplayEffect
#pragma region

namespace NCsGameplayEffect
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsGameplayEffect, SafeLoad);
		}
	}
}

#define USING_NS_CACHED using namespace NCsGameplayEffect::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsGameplayEffect::NCached; \
	const FString& Context = Str::__FunctionName

UGameplayEffect* FCsGameplayEffect::SafeLoad(const FString& Context, void(*Log)(const FString&) /*=&NCsGameplayAbilities::FLog::Warning*/)
{
	CS_IS_SOFT_CLASS_PTR_VALID_RET_NULL(Effect, UGameplayEffect)

	const FSoftObjectPath& Path = Effect.ToSoftObjectPath();

	if (!CsObjectLibrary::IsValidObject(Effect_Internal))
	{
		Effect_Class = Effect.LoadSynchronous();

		if (Effect_Class)
		{
			UObject* DOb = Effect_Class->GetDefaultObject();	

			if (!DOb)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get DefaultObject for Effect @ Path: %s with Class: %s."), *Context, *(Path.ToString()), *(Effect_Class->GetName())))
				return nullptr;
			}

			Effect_Internal = CS_CAST(DOb, UObject, UGameplayEffect);

			if (!Effect_Internal)
				return nullptr;
			return Effect_Internal;
		}
		else
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load Effect @ Path: %s."), *Context, *(Path.ToString())))
			return nullptr;
		}
	}
	return Effect_Internal;
}

UGameplayEffect* FCsGameplayEffect::SafeLoad()
{
	SET_CONTEXT(SafeLoad);

	return SafeLoad(Context, nullptr);
}

UObject* FCsGameplayEffect::SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) /*=&NCsGameplayAbilities::FLog::Warning*/)
{
	CS_IS_SOFT_CLASS_PTR_VALID_RET_NULL(Effect, UGameplayEffect)

	const FSoftObjectPath& Path = Effect.ToSoftObjectPath();
	UObject* O					= Effect.LoadSynchronous();

	if (!O)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load Effect at Path: %s."), *Context, *(Path.ToString())))
		return nullptr;
	}
	return O;
}

#undef USING_NS_CACHED
#undef SET_CONTEXT

#pragma endregion FCsGameplayEffect

// FCsGameplayEffectInfo
#pragma region

bool FCsGameplayEffectInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Effect);
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Level, 0)
	return true;
}

bool FCsGameplayEffectInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsGameplayAbilities::FLog::Warning*/) const
{
	CS_IS_VALID(Effect)
	CS_IS_INT_GREATER_THAN_OR_EQUAL(Level, 0)
	return true;
}

bool FCsGameplayEffectInfo::IsTopValidChecked(const FString& Context) const
{
	CS_IS_TOP_VALID_CHECKED(Effect);
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Level, 0)
	return true;
}

bool FCsGameplayEffectInfo::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&NCsGameplayAbilities::FLog::Warning*/) const
{
	CS_IS_TOP_VALID(Effect)
	CS_IS_INT_GREATER_THAN_OR_EQUAL(Level, 0)
	return true;
}

#pragma endregion FCsGameplayEffectInfo