// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "GameplayAbilitySpec.h"

namespace NCsGameplayAbilities
{
	namespace NValid
	{
		namespace NGameplayAbilitySpecHandle
		{
			struct CSGAMEPLAYABILITIES_API FLibrary final
			{
			public:

				FORCEINLINE static bool IsValid(const FString& Context, const FGameplayAbilitySpecHandle& Handle, const FString& HandleName, void(*Log)(const FString&))
				{
					if (!Handle.IsValid())
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s is NOT Valid."), *Context, *HandleName));
						return false;
					}
					return true;
				}

				FORCEINLINE static bool IsValidChecked(const FString& Context, const FGameplayAbilitySpecHandle& Handle, const FString& HandleName)
				{
					checkf(Handle.IsValid(), TEXT("%s: %s is NOT Valid."), *Context, *HandleName);
					return true;
				}
			};
		}
	}
}

// CHECKED

#if !UE_BUILD_SHIPPING

// FGameplayAbilitySpecHandle
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_GA_SPEC_HANDLE_VALID_CHECKED(__Handle) \
	{ \
		static const FString __temp__str__ = #__Handle; \
		check(NCsGameplayAbilities::NValid::NGameplayAbilitySpecHandle::FLibrary::IsValidChecked(Context, __Handle, __temp__str__)); \
	}

#pragma endregion FGameplayAbilitySpecHandle

#else

// FGameplayAbilitySpecHandle
#define CS_IS_GA_SPEC_HANDLE_VALID_CHECKED(__Handle)

#endif // #if !UE_BUILD_SHIPPING

// SAFE

// FGameplayAbilitySpecHandle
#pragma region

#if !UE_BUILD_SHIPPING

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GA_SPEC_HANDLE_VALID(__Handle) \
	{ \
		static const FString __temp__str__ = #__Handle; \
		if (!NCsGameplayAbilities::NValid::NGameplayAbilitySpecHandle::FLibrary::IsValid(Context, __Handle, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GA_SPEC_HANDLE_VALID_EXIT(__Handle) \
	{ \
		static const FString __temp__str__ = #__Handle; \
		if (!NCsGameplayAbilities::NValid::NGameplayAbilitySpecHandle::FLibrary::IsValid(Context, __Handle, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GA_SPEC_HANDLE_VALID_RET_NULL(__Handle) \
	{ \
		static const FString __temp__str__ = #__Handle; \
		if (!NCsGameplayAbilities::NValid::NGameplayAbilitySpecHandle::FLibrary::IsValid(Context, __Handle, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GA_SPEC_HANDLE_VALID_RET_VALUE(__Handle, __Value) \
	{ \
		static const FString __temp__str__ = #__Handle; \
		if (!NCsGameplayAbilities::NValid::NGameplayAbilitySpecHandle::FLibrary::IsValid(Context, __Handle, __temp__str__, Log)) { return __Value; } \
	}

#else

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GA_SPEC_HANDLE_VALID(__Handle) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayAbilities::NValid::NGameplayAbilitySpecHandle::FLibrary::IsValid(Context, __Handle, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GA_SPEC_HANDLE_VALID_EXIT(__Handle) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayAbilities::NValid::NGameplayAbilitySpecHandle::FLibrary::IsValid(Context, __Handle, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GA_SPEC_HANDLE_VALID_RET_NULL(__Handle) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayAbilities::NValid::NGameplayAbilitySpecHandle::FLibrary::IsValid(Context, __Handle, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GA_SPEC_HANDLE_VALID_RET_VALUE(__Handle, __Value) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayAbilities::NValid::NGameplayAbilitySpecHandle::FLibrary::IsValid(Context, __Handle, __temp__str__, Log)) { return __Value; } \
	}

#endif // #if !UE_BUILD_SHIPPING

#pragma endregion FGameplayAbilitySpecHandle