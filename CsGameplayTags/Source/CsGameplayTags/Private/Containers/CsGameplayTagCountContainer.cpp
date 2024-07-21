// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Containers/CsGameplayTagCountContainer.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "CsLibrary_GameplayTags.h"

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
					CSGAMEPLAYTAGS_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameplayTag::NCount::FContainer, HasMatchingTag);
					CSGAMEPLAYTAGS_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameplayTag::NCount::FContainer, HasAllMatchingTags);
					CSGAMEPLAYTAGS_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameplayTag::NCount::FContainer, HasAnyMatchingTags);
					CSGAMEPLAYTAGS_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameplayTag::NCount::FContainer, UpdateTagCount);
					CSGAMEPLAYTAGS_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameplayTag::NCount::FContainer, UpdateTagCount_DeferredParentRemoval);
					CSGAMEPLAYTAGS_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameplayTag::NCount::FContainer, SetTagCount);
					CSGAMEPLAYTAGS_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameplayTag::NCount::FContainer, GetTagCount);
					CSGAMEPLAYTAGS_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameplayTag::NCount::FContainer, GetExplicitTagCount);
				}
			}
		}

		#define GameplayTagsLibrary NCsGameplayTags::FLibrary
		#define OnDeferredChangeEventType NCsGameplayTag::NCount::FOnDeferredChange
		#define OnCountChangedEventType NCsGameplayTag::NCount::FOnCountChanged
		#define EventType NCsGameplayTag::NCount::EEvent

		void FContainer::Notify_StackCountChange(const FGameplayTag& Tag)
		{	
			// The purpose of this function is to let anyone listening on the EGameplayTagEventType::AnyCountChange event know that the 
			// stack count of a GE that was backing this GE has changed. We do not update our internal map/count with this info, since that
			// map only counts the number of GE/sources that are giving that tag.
			static FGameplayTagContainer TagAndParentsContainer;
			
			GameplayTagsLibrary::Copy(Tag.GetGameplayTagParents(), TagAndParentsContainer);

			for (auto CompleteTagIt = TagAndParentsContainer.CreateConstIterator(); CompleteTagIt; ++CompleteTagIt)
			{
				const FGameplayTag& CurTag = *CompleteTagIt;
				FDelegateInfo* DelegateInfo = GameplayTagEventMap.Find(CurTag);

				if (DelegateInfo)
				{
					const int32& TagCount = GameplayTagCountMap.FindOrAdd(CurTag);

					DelegateInfo->OnAnyChange.Broadcast(CurTag, TagCount);
				}
			}
		}

		OnCountChangedEventType& FContainer::RegisterEvent(const FGameplayTag& Tag, const EventType& Type)
		{
			FDelegateInfo& Info = GameplayTagEventMap.FindOrAdd(Tag);

			if (Type == EventType::NewOrRemoved)
				return Info.OnNewOrRemove;
			return Info.OnAnyChange;
		}

		void FContainer::Reset(bool bResetCallbacks /*=true*/)
		{
			GameplayTagCountMap.Reset();
			ExplicitTagCountMap.Reset();
			ExplicitTags.Reset();

			if (bResetCallbacks)
			{
				GameplayTagEventMap.Reset();
				OnAnyTagChangeDelegate.Clear();
			}
		}

		bool FContainer::UpdateExplicitTags(const FGameplayTag& Tag, const int32& CountDelta, const bool& bDeferParentTagsOnRemove)
		{
			const bool bTagAlreadyExplicitlyExists = ExplicitTags.HasTagExact(Tag);

			// Need special case handling to maintain the explicit tag list correctly, adding the tag to the list if it didn't previously exist and a
			// positive delta comes in, and removing it from the list if it did exist and a negative delta comes in.
			if (!bTagAlreadyExplicitlyExists)
			{
				// Brand new tag with a positive delta needs to be explicitly added
				if (CountDelta > 0)
				{
					ExplicitTags.AddTag(Tag);
				}
				// Block attempted reduction of non-explicit tags, as they were never truly added to the container directly
				else
				{
					// only warn about tags that are in the container but will not be removed because they aren't explicitly in the container
					checkf(!ExplicitTags.HasTag(Tag), TEXT("Attempted to remove tag: %s from tag count container, but it is not explicitly in the container!"), *Tag.ToString());
					return false;
				}
			}

			// Update the explicit tag count map. This has to be separate than the map below because otherwise the count of nested tags ends up wrong
			int32& ExistingCount = ExplicitTagCountMap.FindOrAdd(Tag);
			ExistingCount		 = FMath::Max(ExistingCount + CountDelta, 0);

			// If our new count is 0, remove us from the explicit tag list
			if (ExistingCount <= 0)
			{
				// Remove from the explicit list
				ExplicitTags.RemoveTag(Tag, bDeferParentTagsOnRemove);
			}
			return true;
		}

		bool FContainer::GatherTagChangeDelegates(const FGameplayTag& Tag, const int32& CountDelta, TArray<OnDeferredChangeEventType>& TagChangeDelegates)
		{
			// Check if change delegates are required to fire for the tag or any of its parents based on the count change
			static FGameplayTagContainer TagAndParentsContainer;
			
			GameplayTagsLibrary::Copy(Tag.GetGameplayTagParents(), TagAndParentsContainer);

			bool CreatedSignificantChange				 = false;

			for (auto CompleteTagIt = TagAndParentsContainer.CreateConstIterator(); CompleteTagIt; ++CompleteTagIt)
			{
				const FGameplayTag& CurTag = *CompleteTagIt;

				// Get the current count of the specified tag. NOTE: Stored as a reference, so subsequent changes propagate to the map.
				int32& TagCountRef   = GameplayTagCountMap.FindOrAdd(CurTag);
				const int32 OldCount = TagCountRef;

				// Apply the delta to the count in the map
				int32 NewTagCount = FMath::Max(OldCount + CountDelta, 0);
				TagCountRef		  = NewTagCount;

				// If a significant change (new addition or total removal) occurred, trigger related delegates
				const bool SignificantChange = (OldCount == 0 || NewTagCount == 0);
				CreatedSignificantChange	|= SignificantChange;

				if (SignificantChange)
				{
					TagChangeDelegates.AddDefaulted();
					TagChangeDelegates.Last().BindLambda([Delegate = OnAnyTagChangeDelegate, CurTag, NewTagCount]()
					{
						Delegate.Broadcast(CurTag, NewTagCount);
					});
				}

				FDelegateInfo* DelegateInfo = GameplayTagEventMap.Find(CurTag);
				if (DelegateInfo)
				{
					TagChangeDelegates.AddDefaulted();
					TagChangeDelegates.Last().BindLambda([Delegate = DelegateInfo->OnAnyChange, CurTag, NewTagCount]()
					{
						Delegate.Broadcast(CurTag, NewTagCount);
					});

					if (SignificantChange)
					{
						TagChangeDelegates.AddDefaulted();
						TagChangeDelegates.Last().BindLambda([Delegate = DelegateInfo->OnNewOrRemove, CurTag, NewTagCount]()
						{
							Delegate.Broadcast(CurTag, NewTagCount);
						});
					}
				}
			}
			return CreatedSignificantChange;
		}

		bool FContainer::UpdateTagMap_Internal(const FGameplayTag& Tag, const int32& CountDelta)
		{
			if (!UpdateExplicitTags(Tag, CountDelta, false))
				return false;

			static TArray<OnDeferredChangeEventType> DeferredTagChangeDelegates;
			DeferredTagChangeDelegates.Reset(DeferredTagChangeDelegates.Max());

			bool bSignificantChange = GatherTagChangeDelegates(Tag, CountDelta, DeferredTagChangeDelegates);

			for (OnDeferredChangeEventType& Delegate : DeferredTagChangeDelegates)
			{
				Delegate.Execute();
			}
			return bSignificantChange;
		}

		bool FContainer::UpdateTagMapDeferredParentRemoval_Internal(const FGameplayTag& Tag, const int32& CountDelta, TArray<OnDeferredChangeEventType>& DeferredTagChangeDelegates)
		{
			if (!UpdateExplicitTags(Tag, CountDelta, true))
				return false;
			return GatherTagChangeDelegates(Tag, CountDelta, DeferredTagChangeDelegates);
		}

		#undef GameplayTagsLibrary
		#undef OnDeferredChangeEventType
		#undef OnCountChangedEventType
		#undef EventType
	}
}