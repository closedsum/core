// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class ATriggerBase;

namespace NCsTrigger
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORE_API const FString GetSafeByTag;
			}
		}
	}

	/**
	* Library of functions related to TriggerBase
	*/
	struct CSCORE_API FLibrary final
	{
	public:

		static FString PrintTriggerAndClass(const ATriggerBase* Actor);

	// Get
	#pragma region
	public:

		/**
		* Get all Triggers of type: ATriggerBase.
		*  Assumes there should be at least ONE Trigger found.
		*
		* @param Context		The calling context.
		* @param WorldContxt
		* @param OutTriggers		(out)
		*/
		static void GetChecked(const FString& Context, const UObject* WorldContext, TArray<ATriggerBase*>& OutTriggers);

		/**
		* Safely get all Triggers of type: ATriggerBase.
		*  Assumes there should be at least ONE Trigger found.
		*
		* @param Context		The calling context.
		* @param WorldContxt
		* @param OutTriggers		(out)
		* @param Log			(optional)
		* return
		*/
		static bool GetSafe(const FString& Context, const UObject* WorldContext, TArray<ATriggerBase*>& OutTriggers, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get an Actor with the given Tag (checks AActor->Tags)
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return
		*/
		static ATriggerBase* GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag);

		/**
		* Get a Trigger (casted to type T) with the given Tag (checks ATriggerBase->Tags)
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return
		*/
		template<typename T>
		FORCEINLINE static T* GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
		{
			T* A = Cast<T>(GetByTagChecked(Context, WorldContext, Tag));

			checkf(A, TEXT("%s: Failed to cast Actor to type: %s."), *Context, *(T::StaticClass()->GetName()));

			return A;
		}

		/**
		* Safely get a Trigger with the given Tag (checks ATriggerBase->Tags)
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* @param Log
		* return				Trigger
		*/
		static ATriggerBase* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely get a Trigger (casted to type T) with the given Tag (checks ATriggerBase->Tags)
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* @param Log
		* return				Trigger
		*/
		template<typename T>
		FORCEINLINE static T* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			T* A = Cast<T>(GetSafeByTag(Context, WorldContext, Tag, Log));

			if (!A)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Failed to cast Actor to type: %s."), *Context, *(T::StaticClass()->GetName())));
			}
			return A;
		}

		/**
		* Safely get a Trigger with the given Tag (checks ATriggerBase->Tags)
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return				Trigger
		*/
		FORCEINLINE static ATriggerBase* GetSafeByTag(const UObject* WorldContext, const FName& Tag)
		{
			using namespace NCsTrigger::NLibrary::NCached;

			const FString& Context = Str::GetSafeByTag;

			return GetSafeByTag(Context, WorldContext, Tag, nullptr);
		}

		/**
		* Safely get a Trigger (casted to type T) with the given Tag (checks ATriggerBase->Tags)
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return				Trigger
		*/
		template<typename T>
		FORCEINLINE static T* GetSafeByTag(const UObject* WorldContext, const FName& Tag)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::GetSafeByTag;

			return GetSafeByTag<T>(Context, WorldContext, Tag, nullptr);
		}

		/**
		* Get a list of Triggers with the given Tag (checks ATriggerBase->Tags).
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tags
		* @param OutTriggers	(out)
		*/
		static void GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ATriggerBase*>& OutTriggers);

		/**
		* Safely get a list of Triggers with the given Tag (checks ATriggerBase->Tags).
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tags
		* @param OutTriggers	(out)
		* @param Log			(optional)
		* return				Whether any actors were found with Tags.
		*/
		static bool GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ATriggerBase*>& OutTriggers, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get a Trigger with the given Tags (checks ATriggerBase->Tags).
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tags
		* returns				Trigger
		*/
		static ATriggerBase* GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags);

		/**
		* Safely get a Trigger with the given Tags (checks ATriggerBase->Tags).
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tags
		* @param Log			(optional)
		* return				Trigger
		*/
		static ATriggerBase* GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get an Trigger with the given Name.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* return				Trigger
		*/
		static ATriggerBase* GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name);

		/**
		* Get an Trigger with the given Name.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* @param Log			(optional)
		* return				Trigger
		*/
		static ATriggerBase* GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get an Trigger with the given Name.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* return				Trigger
		*/
		static ATriggerBase* GetSafeByName(const UObject* WorldContext, const FName& Name);

		/**
		* Get an Trigger with the given Label.
		* NOTE: - More than 1 Trigger can have the SAME Label in Editor. In this case, the FIRST
		*		  Trigger found in the search will be returned.
		*		- Only valid in Editor.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Level
		* return				Trigger
		*/
		static ATriggerBase* GetByLabelChecked(const FString& Context, const UObject* WorldContext, const FString& Label);

		/**
		* Get an Trigger with the given Label.
		* NOTE: - More than 1 Trigger can have the SAME Label in Editor. In this case, the FIRST
		*		  Trigger found in the search will be returned.
		*		- Only valid in Editor.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* @param Log			(optional)
		* return				Trigger
		*/
		static ATriggerBase* GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get an Trigger with the given Label.
		* NOTE: - More than 1 Trigger can have the SAME Label in Editor. In this case, the FIRST
		*		  Trigger in the search will be returned.
		*		- Only valid in Editor.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* return				Trigger
		*/
		static ATriggerBase* GetSafeByLabel(const UObject* WorldContext, const FString& Label);

	#pragma endregion Get
	};
}