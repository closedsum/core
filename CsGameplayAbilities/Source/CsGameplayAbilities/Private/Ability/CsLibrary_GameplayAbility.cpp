// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Ability/CsLibrary_GameplayAbility.h"

// Library
	// Common
#include "Object/CsLibrary_Object.h"
#include "CsLibrary_Valid_GameplayTags.h"
#include "CsLibrary_Valid_GameplayAbilities.h"
#include "Library/CsLibrary_Valid.h"
// Ability
#include "Abilities/GameplayAbility.h"

namespace NCsGameplayAbility
{
	#define LogLevel void(*Log)(const FString&) /*=&NCsGameplayAbilities::FLog::Warning*/

	// Spec
	#pragma region
	
	bool FLibrary::IsValidSpecChecked(const FString& Context, const FGameplayAbilitySpec& Spec)
	{
		CS_IS_GA_SPEC_HANDLE_VALID_CHECKED(Spec.Handle)
		CS_IS_OBJECT_PTR_NULL_CHECKED(Spec.Ability, UGameplayAbility)
		return true;
	}

	bool FLibrary::IsValidSpec(const FString& Context, const FGameplayAbilitySpec& Spec, LogLevel)
	{
		CS_IS_GA_SPEC_HANDLE_VALID(Spec.Handle)
		CS_IS_OBJECT_PTR_NULL(Spec.Ability, UGameplayAbility)
		return true;
	}

	bool FLibrary::IsValidSpecChecked(const FString& Context, const FGameplayAbilitySpec* Spec)
	{
		CS_IS_PTR_NULL_CHECKED(Spec)
		return IsValidSpecChecked(Context, *Spec);
	}

	bool FLibrary::IsValidSpec(const FString& Context, const FGameplayAbilitySpec* Spec, LogLevel)
	{
		CS_IS_PTR_NULL(Spec)
		return IsValidSpec(Context, *Spec, Log);
	}

	void FLibrary::BuildChecked(const FString& Context, UGameplayAbility* AbilityClass, const int32& Level, const int32& InputID, FGameplayAbilitySpec& OutSpec)
	{
		check(CsObjectLibrary::IsDefaultObjectChecked(Context, AbilityClass));
		CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Level, 0)
		
		OutSpec = FGameplayAbilitySpec(AbilityClass, Level, InputID);
		/*Reset(OutSpec);

		OutSpec.Ability = AbilityClass;
		OutSpec.Level	= Level;
		OutSpec.InputID = InputID;
		OutSpec.Handle.GenerateNewHandle();*/
	}

	void FLibrary::BuildChecked(const FString& Context, const FCsGameplayAbilityInfo& Info, FGameplayAbilitySpec& OutSpec)
	{
		CS_IS_VALID_CHECKED(Info);

		BuildChecked(Context, Info.Ability.GetChecked(Context), Info.Level, -1, OutSpec);
	}

	bool FLibrary::HasAll(const FString& Context, const FGameplayAbilitySpec& Spec, const FGameplayTagContainer& Tags)
	{
		CS_IS_OBJECT_PTR_NULL_CHECKED(Spec.Ability, UGameplayAbility)
		CS_IS_GAMEPLAY_TAG_CONTAINER_VALID_CHECKED(Tags)

		return Spec.Ability->AbilityTags.HasAll(Tags);
	}

	#pragma endregion Spec

	#undef LogLevel
}