// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Ability/CsTypes_GameplayAbility.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Ability
#include "Abilities/GameplayAbility.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_GameplayAbility)

// GameplayAbilityInstance
#pragma region

namespace NCsGameplayAbilityInstance
{
	typedef EMCsGameplayAbilityInstance EnumMapType;

	namespace Ref
	{
		CSGAMEPLAYABILITIES_API CS_ADD_TO_ENUM_MAP(DefaultObject);
		CSGAMEPLAYABILITIES_API CS_ADD_TO_ENUM_MAP(Instance);
		CSGAMEPLAYABILITIES_API CS_ADD_TO_ENUM_MAP(Replicated);
		CSGAMEPLAYABILITIES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsGameplayAbilityInstance_MAX, "MAX");
	}
}

namespace NCsGameplayAbility
{
	namespace NInstance
	{
		namespace Ref
		{
			typedef EMInstance EnumMapType;

			CSGAMEPLAYABILITIES_API CS_ADD_TO_ENUM_MAP(DefaultObject);
			CSGAMEPLAYABILITIES_API CS_ADD_TO_ENUM_MAP(Instance);
			CSGAMEPLAYABILITIES_API CS_ADD_TO_ENUM_MAP(Replicated);
			CSGAMEPLAYABILITIES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EInstance_MAX, "MAX");
		}
	}
}

#pragma endregion GameplayAbilityInstance

// FCsGameplayAbility
#pragma region

namespace NCsGameplayAbility
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsGameplayAbility, SafeLoad);
		}
	}
}

#define USING_NS_CACHED using namespace NCsGameplayAbility::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsGameplayAbility::NCached; \
	const FString& Context = Str::__FunctionName

UGameplayAbility* FCsGameplayAbility::SafeLoad(const FString& Context, void(*Log)(const FString&) /*=&NCsGameplayAbilities::FLog::Warning*/)
{
	CS_IS_SOFT_CLASS_PTR_VALID_RET_NULL(Ability, UGameplayAbility)

	const FSoftObjectPath& Path = Ability.ToSoftObjectPath();

	if (!CsObjectLibrary::IsValidObject(Ability_Internal))
	{
		Ability_Class = Ability.LoadSynchronous();

		if (Ability_Class)
		{
			UObject* DOb = Ability_Class->GetDefaultObject();	

			if (!DOb)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get DefaultObject for Ability @ Path: %s with Class: %s."), *Context, *(Path.ToString()), *(Ability_Class->GetName())))
				return nullptr;
			}

			Ability_Internal = CS_CAST(DOb, UObject, UGameplayAbility);

			if (!Ability_Internal)
				return nullptr;
			return Ability_Internal;
		}
		else
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load Data @ Path: %s."), *Context, *(Path.ToString())))
			return nullptr;
		}
	}
	return Ability_Internal;
}

UGameplayAbility* FCsGameplayAbility::SafeLoad()
{
	SET_CONTEXT(SafeLoad);

	return SafeLoad(Context, nullptr);
}

UObject* FCsGameplayAbility::SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) /*=&NCsGameplayAbilities::FLog::Warning*/)
{
	CS_IS_SOFT_CLASS_PTR_VALID_RET_NULL(Ability, UGameplayAbility)

	const FSoftObjectPath& Path = Ability.ToSoftObjectPath();
	UObject* O					= Ability.LoadSynchronous();

	if (!O)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load Ability at Path: %s."), *Context, *(Path.ToString())))
		return nullptr;
	}
	return O;
}

#undef USING_NS_CACHED
#undef SET_CONTEXT

#pragma endregion FCsGameplayAbility

// FCsGameplayAbilityInfo
#pragma region

bool FCsGameplayAbilityInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Ability);
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Level, 0)
	return true;
}

bool FCsGameplayAbilityInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsGameplayAbilities::FLog::Warning*/) const
{
	CS_IS_VALID(Ability)
	CS_IS_INT_GREATER_THAN_OR_EQUAL(Level, 0)
	return true;
}

bool FCsGameplayAbilityInfo::IsTopValidChecked(const FString& Context) const
{
	CS_IS_TOP_VALID_CHECKED(Ability);
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Level, 0)
	return true;
}

bool FCsGameplayAbilityInfo::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&NCsGameplayAbilities::FLog::Warning*/) const
{
	CS_IS_TOP_VALID(Ability)
	CS_IS_INT_GREATER_THAN_OR_EQUAL(Level, 0)
	return true;
}

#pragma endregion FCsGameplayAbilityInfo