// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "GameplayTagContainer.h"

#include "CsGameplayTagCountContainer.generated.h"

USTRUCT()
struct CSGAMEPLAYTAGS_API FCsGameplayTagCountContainer_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsGameplayTagCountContainer_STUB()
	{
	}
};

// GameplayTagCountEvent
#pragma region

/**
* Rather a tag was added or removed, used in callbacks
*/
UENUM(BlueprintType)
enum class ECsGameplayTagCountEvent : uint8
{
	/** Event only happens when tag is new or completely removed */
	NewOrRemoved	UMETA(DisplayName = "New or Removed"),
	/** Event happens any time tag "count" changes */
	AnyCountChange	UMETA(DisplayName = "Any Count Changed")
};

namespace NCsGameplayTag
{
	namespace NCount
	{
		enum class EEvent : uint8
		{
			/** Event only happens when tag is new or completely removed */
			NewOrRemoved,
			/** Event happens any time tag "count" changes */
			AnyCountChange
		};
	}
}

#pragma endregion GameplayTagCountEvent

// Delegates
#pragma region

namespace NCsGameplayTag
{
	namespace NCount
	{
		DECLARE_DELEGATE(FOnDeferredChange);

		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCountChanged, const FGameplayTag& /*Tag*/, const int32& /*Count*/);
		DECLARE_DELEGATE_RetVal_OneParam(FOnCountChanged&, FRegisterOnCountChanged, const FGameplayTag& /*Tag*/);
	}
}

#pragma endregion Delegates

namespace NCsGameplayTag
{
	namespace NCount
	{
		namespace NContainer
		{
			namespace NCached
			{
				namespace Str
				{
					extern CSGAMEPLAYTAGS_API const FString HasMatchingTag;
					extern CSGAMEPLAYTAGS_API const FString HasAllMatchingTags;
					extern CSGAMEPLAYTAGS_API const FString HasAnyMatchingTags;
					extern CSGAMEPLAYTAGS_API const FString UpdateTagCount;
					extern CSGAMEPLAYTAGS_API const FString UpdateTagCount_DeferredParentRemoval;
					extern CSGAMEPLAYTAGS_API const FString SetTagCount;
					extern CSGAMEPLAYTAGS_API const FString GetTagCount;
					extern CSGAMEPLAYTAGS_API const FString GetExplicitTagCount;
				}
			}
		}

		/**
		* NOTE: Mostly mimics FGameplayTagCountContainer
		* 
		* Struct that tracks the number/count of tag applications within it. Explicitly tracks the tags added or removed,
		* while simultaneously tracking the count of parent tags as well. Events/delegates are fired whenever the tag counts
		* of any tag (explicit or parent) are modified.
		*/
		struct CSGAMEPLAYTAGS_API FContainer
		{	
		public:

		#define USING_NS_CACHED using namespace NCsGameplayTag::NCount::NContainer::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsGameplayTag::NCount::NContainer::NCached; \
				const FString& Context = Str::__FunctionName
		#define OnDeferredChangeEventType NCsGameplayTag::NCount::FOnDeferredChange
		#define OnCountChangedEventType NCsGameplayTag::NCount::FOnCountChanged

			FContainer()
			{}

			/**
			 * Check if the count container has a gameplay tag that matches against the specified tag (expands to include parents of asset tags)
			 * 
			 * @param TagToCheck	Tag to check for a match
			 * @return				True if the count container has a gameplay tag that matches, false if not
			 */
			FORCEINLINE bool HasMatchingTagChecked(const FString& Context, const FGameplayTag& TagToCheck) const
			{
				checkf(TagToCheck.IsValid(), TEXT("%s: TagToCheck is NOT Valid."), *Context);
				checkf(GameplayTagCountMap.FindRef(TagToCheck) > 0, TEXT("%s: TagToCheck: %s has NOT been added."), *Context, *(TagToCheck.ToString()));
				return true;
			}

			/**
			 * Check if the count container has a gameplay tag that matches against the specified tag (expands to include parents of asset tags)
			 * 
			 * @param TagToCheck	Tag to check for a match
			 * @return				True if the count container has a gameplay tag that matches, false if not
			 */
			FORCEINLINE bool HasMatchingTag(const FGameplayTag& TagToCheck) const
			{
				SET_CONTEXT(HasMatchingTag);

				checkf(TagToCheck.IsValid(), TEXT("%s: TagToCheck is NOT Valid."), *Context);
				return GameplayTagCountMap.FindRef(TagToCheck) > 0;
			}

			/**
			 * Check if the count container has gameplay tags that matches against all of the specified tags (expands to include parents of asset tags)
			 * 
			 * @param TagContainer	Tag container to check for a match. If empty will return true
			 * @return				True if the count container matches all of the gameplay tags
			 */
			FORCEINLINE bool HasAllMatchingTags(const FGameplayTagContainer& TagContainer) const
			{
				SET_CONTEXT(HasAllMatchingTags);

				checkf(TagContainer.IsValid(), TEXT("%s: TagContainer is NOT Valid."), *Context);

				// if the TagContainer count is 0 return bCountEmptyAsMatch;
				if (TagContainer.Num() == 0)
				{
					return true;
				}

				bool AllMatch = true;
				for (const FGameplayTag& Tag : TagContainer)
				{
					if (GameplayTagCountMap.FindRef(Tag) <= 0)
					{
						AllMatch = false;
						break;
					}
				}		
				return AllMatch;
			}
	
			/**
			 * Check if the count container has gameplay tags that matches against any of the specified tags (expands to include parents of asset tags)
			 * 
			 * @param TagContainer	Tag container to check for a match. If empty will return false
			 * @return				True if the count container matches any of the gameplay tags
			 */
			FORCEINLINE bool HasAnyMatchingTags(const FGameplayTagContainer& TagContainer) const
			{
				SET_CONTEXT(HasAnyMatchingTags);

				checkf(TagContainer.IsValid(), TEXT("%s: TagContainer is NOT Valid."), *Context);

				if (TagContainer.Num() == 0)
				{
					return false;
				}

				bool AnyMatch = false;
				for (const FGameplayTag& Tag : TagContainer)
				{
					if (GameplayTagCountMap.FindRef(Tag) > 0)
					{
						AnyMatch = true;
						break;
					}
				}
				return AnyMatch;
			}
	
			/**
			 * Update the specified container of tags by the specified delta, potentially causing an additional or removal from the explicit tag list
			 * 
			 * @param Container		Container of tags to update
			 * @param CountDelta	Delta of the tag count to apply
			 */
			FORCEINLINE void UpdateTagCount(const FGameplayTagContainer& Container, const int32& CountDelta)
			{
				SET_CONTEXT(UpdateTagCount);

				checkf(Container.IsValid(), TEXT("%s: Container is NOT Valid."), *Context);
				checkf(CountDelta != 0, TEXT("%s: CountDelta: 0 is NOT Valid."), *Context);

				bool bUpdatedAny = false;

				static TArray<OnDeferredChangeEventType> DeferredTagChangeDelegates;
				DeferredTagChangeDelegates.Reset(DeferredTagChangeDelegates.Max());

				for (auto TagIt = Container.CreateConstIterator(); TagIt; ++TagIt)
				{
					bUpdatedAny |= UpdateTagMapDeferredParentRemoval_Internal(*TagIt, CountDelta, DeferredTagChangeDelegates);
				}

				if (bUpdatedAny && CountDelta < 0)
				{
					ExplicitTags.FillParentTags();
				}

				for (OnDeferredChangeEventType& Delegate : DeferredTagChangeDelegates)
				{
					Delegate.Execute();
				}
			}
	
			/**
			 * Update the specified tag by the specified delta, potentially causing an additional or removal from the explicit tag list
			 * 
			 * @param Tag						Tag to update
			 * @param CountDelta				Delta of the tag count to apply
			 * 
			 * @return True if tag was *either* added or removed. (E.g., we had the tag and now dont. or didnt have the tag and now we do. We didn't just change the count (1 count -> 2 count would return false).
			 */
			FORCEINLINE bool UpdateTagCount(const FGameplayTag& Tag, const int32& CountDelta)
			{
				SET_CONTEXT(UpdateTagCount);

				checkf(Tag.IsValid(), TEXT("%s: Tag is NOT Valid."), *Context);
				checkf(CountDelta != 0, TEXT("%s: CountDelta: 0 is NOT Valid."), *Context);
				return UpdateTagMap_Internal(Tag, CountDelta);
			}

			/**
			 * Update the specified tag by the specified delta, potentially causing an additional or removal from the explicit tag list.
			 * Calling code MUST call FillParentTags followed by executing the returned delegates.
			 * 
			 * @param Tag							Tag to update
			 * @param CountDelta					Delta of the tag count to apply
			 * @param DeferredTagChangeDelegates	Delegates to be called after this code runs
			 * 
			 * @return True if tag was *either* added or removed. (E.g., we had the tag and now dont. or didnt have the tag and now we do. We didn't just change the count (1 count -> 2 count would return false).
			 */
			FORCEINLINE bool UpdateTagCount_DeferredParentRemoval(const FGameplayTag& Tag, const int32& CountDelta, TArray<OnDeferredChangeEventType>& DeferredTagChangeDelegates)
			{
				SET_CONTEXT(UpdateTagCount_DeferredParentRemoval);

				checkf(Tag.IsValid(), TEXT("%s: Tag is NOT Valid."), *Context);
				checkf(CountDelta != 0, TEXT("%s: CountDelta: 0 is NOT Valid."), *Context);
				return UpdateTagMapDeferredParentRemoval_Internal(Tag, CountDelta, DeferredTagChangeDelegates);
			}

			/**
			* Set the specified tag count to a specific value
			* 
			* @param Context	The calling context.
			* @param Tag		Tag to update
			* @param Count		New count of the tag
			* 
			* @return True if tag was *either* added or removed. (E.g., we had the tag and now dont. or didnt have the tag and now we do. We didn't just change the count (1 count -> 2 count would return false).
			*/
			FORCEINLINE bool SetTagCountChecked(const FString& Context, const FGameplayTag& Tag, const int32& NewCount)
			{
				checkf(Tag.IsValid(), TEXT("%s: Tag is NOT Valid."), *Context);

			#if WITH_EDITOR
				int32* Ptr  = ExplicitTagCountMap.Find(Tag);

				checkf(Ptr, TEXT("%s: Tag: %s has NOT been added."), *Context, *(Tag.ToString()));

				const int32& ExistingCount = *Ptr;
			#else
				const int32& ExistingCount = ExplicitTagCountMap[Tag];
			#endif // #if WITH_EDITOR

				const int32 CountDelta = NewCount - ExistingCount;

				return UpdateTagMap_Internal(Tag, CountDelta);
			}

			/**
			* Set the specified tag count to a specific value
			* 
			* @param Tag	Tag to update
			* @param Count	New count of the tag
			* 
			* @return True if tag was *either* added or removed. (E.g., we had the tag and now dont. or didnt have the tag and now we do. We didn't just change the count (1 count -> 2 count would return false).
			*/
			FORCEINLINE bool SetTagCount(const FGameplayTag& Tag, const int32& NewCount)
			{
				SET_CONTEXT(SetTagCount);

				checkf(Tag.IsValid(), TEXT("%s: Tag is NOT Valid."), *Context);

				int32 ExistingCount = 0;
				if (int32* Ptr  = ExplicitTagCountMap.Find(Tag))
				{
					ExistingCount = *Ptr;
				}

				const int32 CountDelta = NewCount - ExistingCount;

				return UpdateTagMap_Internal(Tag, CountDelta);
			}

			/**
			* return the hierarchical count for a specified tag
			* e.g. if A.B & A.C were added, GetTagCount("A") would return 2.
			*
			* @param Context	The calling context.
			* @param Tag		Tag to update
			* @return			The count of the passed in tag
			*/
			FORCEINLINE const int32& GetTagCountChecked(const FString& Context, const FGameplayTag& Tag) const
			{
				checkf(Tag.IsValid(), TEXT("%s: Tag is NOT Valid."), *Context);

			#if WITH_EDITOR
				const int32* Ptr = GameplayTagCountMap.Find(Tag);

				checkf(Ptr, TEXT("%s: Tag: %s has NOT been added."), *Context, *(Tag.ToString()));
				return *Ptr;
			#else
				return GameplayTagCountMap[Tag];
			#endif // #if WITH_EDITOR
			}

			/**
			* return the hierarchical count for a specified tag
			* e.g. if A.B & A.C were added, GetTagCount("A") would return 2.
			*
			* @param Tag	Tag to update
			* @return		The count of the passed in tag
			*/
			FORCEINLINE int32 GetTagCount(const FGameplayTag& Tag) const
			{
				SET_CONTEXT(GetTagCount);

				checkf(Tag.IsValid(), TEXT("%s: Tag is NOT Valid."), *Context);

				if (const int32* Ptr = GameplayTagCountMap.Find(Tag))
				{
					return *Ptr;
				}
				return 0;
			}

			/**
			* return how many times the exact specified tag has been added to the container (ignores the tag hierarchy)
			* e.g. if A.B & A.C were added, GetExplicitTagCount("A") would return 0, and GetExplicitTagCount("A.B") would return 1.
			*
			* @param Context	The calling context.
			* @param Tag		Tag to update
			* @return			The count of the passed in tag
			*/
			FORCEINLINE const int32& GetExplicitTagCountChecked(const FString& Context, const FGameplayTag& Tag) const
			{
				checkf(Tag.IsValid(), TEXT("%s: Tag is NOT Valid."), *Context);

			#if WITH_EDITOR
				const int32* Ptr = ExplicitTagCountMap.Find(Tag);

				checkf(Ptr, TEXT("%s: Tag: %s has NOT been added."), *Context, *(Tag.ToString()));
				return *Ptr;
			#else
				return ExplicitTagCountMap[Tag];
			#endif // #if WITH_EDITOR
			}

			/**
			* return how many times the exact specified tag has been added to the container (ignores the tag hierarchy)
			* e.g. if A.B & A.C were added, GetExplicitTagCount("A") would return 0, and GetExplicitTagCount("A.B") would return 1.
			*
			* @param Tag	Tag to update
			* @return		The count of the passed in tag
			*/
			FORCEINLINE int32 GetExplicitTagCount(const FGameplayTag& Tag) const
			{
				SET_CONTEXT(GetExplicitTagCount);

				checkf(Tag.IsValid(), TEXT("%s: Tag is NOT Valid."), *Context);

				if (const int32* Ptr = ExplicitTagCountMap.Find(Tag))
				{
					return *Ptr;
				}
				return 0;
			}

			/**
			 *	Broadcasts the AnyChange event for this tag. This is called when the stack count of the backing gameplay effect change.
			 *	It is up to the receiver of the broadcasted delegate to decide what to do with this.
			 */
			void Notify_StackCountChange(const FGameplayTag& Tag);

			/**
			 * Return delegate that can be bound to for when the specific tag's count changes to or off of zero
			 *
			 * @param Tag	Tag to get a delegate for
			 * @return		Delegate for when the specified tag's count changes to or off of zero
			 */
			FOnCountChanged& RegisterEvent(const FGameplayTag& Tag, const NCsGameplayTag::NCount::EEvent& Type = NCsGameplayTag::NCount::EEvent::NewOrRemoved);
	
			/**
			 * Return delegate that can be bound to for when the any tag's count changes to or off of zero
			 * 
			 * @return Delegate for when any tag's count changes to or off of zero
			 */
			OnCountChangedEventType& RegisterGenericEvent()
			{
				return OnAnyTagChangeDelegate;
			}

			/** Simple accessor to the explicit gameplay tag list */
			const FGameplayTagContainer& GetExplicitTags() const
			{
				return ExplicitTags;
			}

			/**
			 * Removes all of the tags. Does not notify any delegates.
			 * 
			 * @param bResetCallbacks	If true, also remove all of the registered tag count change delegates
			 */
			void Reset(bool bResetCallbacks = true);

			/** Fills in ParentTags from GameplayTags */
			void FillParentTags()
			{
				ExplicitTags.FillParentTags();
			}

		private:

			struct FDelegateInfo
			{
				OnCountChangedEventType	OnNewOrRemove;
				OnCountChangedEventType	OnAnyChange;
			};

			/** Map of tag to delegate that will be fired when the count for the key tag changes to or away from zero */
			TMap<FGameplayTag, FDelegateInfo> GameplayTagEventMap;

			/** Map of tag to active count of that tag */
			TMap<FGameplayTag, int32> GameplayTagCountMap;

			/** Map of tag to explicit count of that tag. Cannot share with above map because it's not safe to merge explicit and generic counts */	
			TMap<FGameplayTag, int32> ExplicitTagCountMap;

			/** Delegate fired whenever any tag's count changes to or away from zero */
			OnCountChangedEventType OnAnyTagChangeDelegate;

			/** Container of tags that were explicitly added */
			FGameplayTagContainer ExplicitTags;

			/** Internal helper function to adjust the explicit tag list & corresponding maps/delegates/etc. as necessary */
			bool UpdateTagMap_Internal(const FGameplayTag& Tag, const int32& CountDelta);

			/** Internal helper function to adjust the explicit tag list & corresponding maps/delegates/etc. as necessary. This does not call FillParentTags or any of the tag change delegates. These delegates are returned and must be executed by the caller. */
			bool UpdateTagMapDeferredParentRemoval_Internal(const FGameplayTag& Tag, const int32& CountDelta, TArray<OnDeferredChangeEventType>& DeferredTagChangeDelegates);

			/** Internal helper function to adjust the explicit tag list & corresponding map. */
			bool UpdateExplicitTags(const FGameplayTag& Tag, const int32& CountDelta, const bool& bDeferParentTagsOnRemove);

			/** Internal helper function to collect the delegates that need to be called when Tag has its count changed by CountDelta. */
			bool GatherTagChangeDelegates(const FGameplayTag& Tag, const int32& CountDelta, TArray<OnDeferredChangeEventType>& TagChangeDelegates);

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef OnDeferredChangeEventType
		#undef OnCountChangedEventType
		};
	}
}