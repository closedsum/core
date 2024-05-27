// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "GameplayTagContainer.h"

namespace NCsGameplayTags
{
	namespace NValid
	{
		namespace NGameplayTag
		{
			struct CSGAMEPLAYTAGS_API FLibrary final
			{
			public:

				FORCEINLINE static bool IsValid(const FString& Context, const FGameplayTag& Tag, const FString& TagName, void(*Log)(const FString&))
				{
					if (!Tag.IsValid())
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s is NOT Valid."), *Context, *TagName));
						return false;
					}
					return true;
				}

				FORCEINLINE static bool IsValidChecked(const FString& Context, const FGameplayTag& Tag, const FString& TagName)
				{
					checkf(Tag.IsValid(), TEXT("%s: %s is NOT Valid."), *Context, *TagName);
					return true;
				}

				FORCEINLINE static bool IsValid(const FString& Context, const TArray<FGameplayTag>& Tags, const FString& TagsName, void(*Log)(const FString&))
				{
					const int32 Count = Tags.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						const FGameplayTag& Tag = Tags[I];

						if (!Tag.IsValid())
						{
							if (Log)
								Log(FString::Printf(TEXT("%s: %s[%d] is NOT Valid."), *Context, *TagsName, I));
							return false;
						}
					}
					return true;
				}

				FORCEINLINE static bool IsValidChecked(const FString& Context, const TArray<FGameplayTag>& Tags, const FString& TagsName)
				{
					const int32 Count = Tags.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						checkf(Tags[I].IsValid(), TEXT("%s: %s is NOT Valid."), *Context, *TagsName, I);
					}
					return true;
				}

				FORCEINLINE static bool IsValid(const FString& Context, const TSet<FGameplayTag>& Tags, const FString& TagsName, void(*Log)(const FString&))
				{
					for (const FGameplayTag& Tag : Tags)
					{
						if (!Tag.IsValid())
						{
							if (Log)
								Log(FString::Printf(TEXT("%s: %s is NOT Valid."), *Context, *TagsName));
							return false;
						}
					}
					return true;
				}

				FORCEINLINE static bool IsValidChecked(const FString& Context, const TSet<FGameplayTag>& Tags, const FString& TagsName)
				{
					for (const FGameplayTag& Tag : Tags)
					{
						checkf(Tag.IsValid(), TEXT("%s: %s is NOT Valid."), *Context, *TagsName);
					}
					return true;
				}
			};
		}

		namespace NGameplayTagContainer
		{
			struct CSGAMEPLAYTAGS_API FLibrary final
			{
			public:

				FORCEINLINE static bool IsValid(const FString& Context, const FGameplayTagContainer& Tags, const FString& TagsName, void(*Log)(const FString&))
				{
					if (!Tags.IsValid())
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s is NOT Valid."), *Context, *TagsName));
						return false;
					}
					return true;
				}

				FORCEINLINE static bool IsValidChecked(const FString& Context, const FGameplayTagContainer& Tags, const FString& TagsName)
				{
					checkf(Tags.IsValid(), TEXT("%s: %s is NOT Valid."), *Context, *TagsName);
					return true;
				}
			};
		}
	}
}

// CHECKED

#if !UE_BUILD_SHIPPING

// FGameplayTag
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_GAMEPLAY_TAG_VALID_CHECKED(__Tag) \
	{ \
		static const FString __temp__str__ = #__Tag; \
		check(NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValidChecked(Context, __Tag, __temp__str__)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_GAMEPLAY_TAGS_VALID_CHECKED(__Tags) \
	{ \
		static const FString __temp__str__ = #__Tags; \
		check(NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValidChecked(Context, __Tags, __temp__str__)); \
	}

#pragma endregion FGameplayTag

// FGameplayTagContainer
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_GAMEPLAY_TAG_CONTAINER_VALID_CHECKED(__Tags) \
	{ \
		static const FString __temp__str__ = #__Tags; \
		check(NCsGameplayTags::NValid::NGameplayTagContainer::FLibrary::IsValidChecked(Context, __Tags, __temp__str__)); \
	}

#pragma endregion FGameplayTagContainer

#else

// FGameplayTag
#define CS_IS_GAMEPLAY_TAG_VALID_CHECKED(__Tag)
// FGameplayTagContainer
#define CS_IS_GAMEPLAY_TAG_CONTAINER_VALID_CHECKED(__Tags)

#endif // #if !UE_BUILD_SHIPPING

// SAFE

// FGameplayTag
#pragma region

#if !UE_BUILD_SHIPPING

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_VALID(__Tag) \
	{ \
		static const FString __temp__str__ = #__Tag; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tag, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_VALID_EXIT(__Tag) \
	{ \
		static const FString __temp__str__ = #__Tag; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tag, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_VALID_RET_NULL(__Tag) \
	{ \
		static const FString __temp__str__ = #__Tag; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tag, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_VALID_RET_VALUE(__Tag, __Value) \
	{ \
		static const FString __temp__str__ = #__Tag; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tag, __temp__str__, Log)) { return __Value; } \
	}

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAGS_VALID(__Tags) \
	{ \
		static const FString __temp__str__ = #__Tags; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAGS_VALID_EXIT(__Tags) \
	{ \
		static const FString __temp__str__ = #__Tags; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tag, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAGS_VALID_RET_NULL(__Tags) \
	{ \
		static const FString __temp__str__ = #__Tags; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAGS_VALID_RET_VALUE(__Tags, __Value) \
	{ \
		static const FString __temp__str__ = #__Tags; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return __Value; } \
	}

#else

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_VALID(__Tag) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tag, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_VALID_EXIT(__Tag) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tag, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_VALID_RET_NULL(__Tag) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tag, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_VALID_RET_VALUE(__Tag, __Value) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tag, __temp__str__, Log)) { return __Value; } \
	}

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAGS_VALID(__Tags) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAGS_VALID_EXIT(__Tags) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAGS_VALID_RET_NULL(__Tags) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAGS_VALID_RET_VALUE(__Tags, __Value) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayTags::NValid::NGameplayTag::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return __Value; } \
	}

#endif // #if !UE_BUILD_SHIPPING

#pragma endregion FGameplayTag

// FGameplayTagContainer
#pragma region

#if !UE_BUILD_SHIPPING

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_CONTAINER_VALID(__Tags) \
	{ \
		static const FString __temp__str__ = #__Tags; \
		if (!NCsGameplayTags::NValid::NGameplayTagContainer::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_CONTAINER_VALID_EXIT(__Tags) \
	{ \
		static const FString __temp__str__ = #__Tags; \
		if (!NCsGameplayTags::NValid::NGameplayTagContainer::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_CONTAINER_VALID_RET_NULL(__Tags) \
	{ \
		static const FString __temp__str__ = #__Tags; \
		if (!NCsGameplayTags::NValid::NGameplayTagContainer::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_CONTAINER_VALID_RET_VALUE(__Tags, __Value) \
	{ \
		static const FString __temp__str__ = #__Tags; \
		if (!NCsGameplayTags::NValid::NGameplayTagContainer::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return __Value; } \
	}

#else

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_CONTAINER_VALID(__Tags) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayTags::NValid::NGameplayTagContainer::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_CONTAINER_VALID_EXIT(__Tags) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayTags::NValid::NGameplayTagContainer::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_CONTAINER_VALID_RET_NULL(__Tags) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayTags::NValid::NGameplayTagContainer::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_GAMEPLAY_TAG_CONTAINER_VALID_RET_VALUE(__Tags, __Value) \
	{ \
		static const FString __temp__str__; \
		if (!NCsGameplayTags::NValid::NGameplayTagContainer::FLibrary::IsValid(Context, __Tags, __temp__str__, Log)) { return __Value; } \
	}

#endif // #if !UE_BUILD_SHIPPING

#pragma endregion FGameplayTagContainer