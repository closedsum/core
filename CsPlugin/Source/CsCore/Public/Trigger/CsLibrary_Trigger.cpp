// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Trigger/CsLibrary_Trigger.h"

// Types
#include "Types/CsTypes_Macro.h"
#include "Types/CsCached.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Name.h"
#include "Library/CsLibrary_Valid.h"
// Trigger
#include "Engine/TriggerBase.h"
// Utility
#include "EngineUtils.h"
// World
#include "Engine/World.h"

namespace NCsTrigger
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTrigger::FLibrary, GetSafeByTag);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTrigger::FLibrary, GetSafeByName);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTrigger::FLibrary, GetSafeByLabel);
			}
		}
	}

	FString FLibrary::PrintTriggerAndClass(const ATriggerBase* Actor)
	{
		if (!Actor)
			return FString::Printf(TEXT("INVALID"));
		return FString::Printf(TEXT("Trigger: %s with Class: %s"), *(Actor->GetName()), *(Actor->GetClass()->GetName()));
	}

	#define WorldLibrary NCsWorld::FLibrary

	// Get
	#pragma region

	void FLibrary::GetChecked(const FString& Context, const UObject* WorldContext, TArray<ATriggerBase*>& OutTriggers)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		for (TActorIterator<ATriggerBase> It(World); It; ++It)
		{
			ATriggerBase* A = *It;

			if (!IsValid(A))
				continue;

			OutTriggers.Add(A);
		}
		checkf(OutTriggers.Num() > CS_EMPTY, TEXT("%s: Failed to find any Triggers of type: ATriggerBase."), *Context);
	}

	bool FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, TArray<ATriggerBase*>& OutTriggers, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

		if (!World)
			return false;

		for (TActorIterator<ATriggerBase> It(World); It; ++It)
		{
			ATriggerBase* A = *It;

			if (!IsValid(A))
				continue;

			OutTriggers.Add(A);
		}

		if (OutTriggers.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find any Triggers of type: ATriggerBase."), *Context));
			return false;
		}
		return true;
	}

	ATriggerBase* FLibrary::GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_NAME_NONE_CHECKED(Tag)

	#if UE_BUILD_SHIPPING
		for (TActorIterator<ATriggerBase> Itr(World); Itr; ++Itr)
		{
			ATriggerBase* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->Tags.Contains(Tag))
			{
				return A;
			}
		}
	#else
		ATriggerBase* Actor = nullptr;
		
		for (TActorIterator<ATriggerBase> Itr(World); Itr; ++Itr)
		{
			ATriggerBase* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->Tags.Contains(Tag))
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					checkf(0, TEXT("%s: There are more than one Triggers with the Tag: %s."), *Context, *(Tag.ToString()));
				}
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		checkf(0, TEXT("%s: Failed to find Trigger with Tag: %s."), *Context, *(Tag.ToString()));
		return nullptr;
	}

	ATriggerBase* FLibrary::GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		CS_IS_NAME_NONE_RET_NULL(Tag)

	#if UE_BUILD_SHIPPING
		for (TActorIterator<ATriggerBase> Itr(World); Itr; ++Itr)
		{
			ATriggerBase* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->Tags.Contains(Tag))
			{
				return A;
			}
		}
	#else
		ATriggerBase* Actor = nullptr;

		for (TActorIterator<ATriggerBase> Itr(World); Itr; ++Itr)
		{
			ATriggerBase* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->Tags.Contains(Tag))
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: There are more than one Triggers with the Tag: %s."), *Context, *(Tag.ToString())));
				}
			}
		}

		if (Actor)
			return Actor;
#endif // UE_BUILD_SHIPPING

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Trigger with Tag: %s."), *Context, *(Tag.ToString())));
		return nullptr;
	}

	void FLibrary::GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ATriggerBase*>& OutTriggers)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_TARRAY_EMPTY_CHECKED(Tags, FName)
		CS_IS_TARRAY_ANY_NONE_CHECKED(Tags)

		for (TActorIterator<ATriggerBase> Itr(World); Itr; ++Itr)
		{
			ATriggerBase* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;

			if (A->Tags.Num() < Tags.Num())
				continue;

			bool HasAllTags = true;

			for (const FName& Tag : Tags)
			{
				if (!A->Tags.Contains(Tag))
				{
					HasAllTags = false;
					break;
				}
			}

			if (HasAllTags)
				OutTriggers.Add(A);
		}

		typedef NCsName::FLibrary NameLibrary;

		checkf(OutTriggers.Num() > CS_EMPTY, TEXT("%s: Failed to find Triggers with Tags: %s."), *Context, *(NameLibrary::ToString(Tags)));
	}

	bool FLibrary::GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ATriggerBase*>& OutTriggers, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_TARRAY_EMPTY(Tags, FName)
		CS_IS_TARRAY_ANY_NONE(Tags)

		for (TActorIterator<ATriggerBase> Itr(World); Itr; ++Itr)
		{
			ATriggerBase* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;

			if (A->Tags.Num() < Tags.Num())
				continue;

			bool HasAllTags = true;

			for (const FName& Tag : Tags)
			{
				if (!A->Tags.Contains(Tag))
				{
					HasAllTags = false;
					break;
				}
			}

			if (HasAllTags)
				OutTriggers.Add(A);
		}

		typedef NCsName::FLibrary NameLibrary;

		if (OutTriggers.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Triggers with Tags: %s."), *Context, *(NameLibrary::ToString(Tags))));
		}
		return OutTriggers.Num() > CS_EMPTY;
	}

	ATriggerBase* FLibrary::GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_TARRAY_EMPTY_CHECKED(Tags, FName)
		CS_IS_TARRAY_ANY_NONE_CHECKED(Tags)

		typedef NCsName::FLibrary NameLibrary;

	#if UE_BUILD_SHIPPING
		for (TActorIterator<ATriggerBase> Itr(World); Itr; ++Itr)
		{
			ATriggerBase* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			bool HasAllTags = true;

			for (const FName& Tag : Tags)
			{
				if (!A->Tags.Contains(Tag))
				{
					HasAllTags = false;
					break;
				}
			}

			if (HasAllTags)
				return A;
		}
	#else
		ATriggerBase* Actor = nullptr;
		
		for (TActorIterator<ATriggerBase> Itr(World); Itr; ++Itr)
		{
			ATriggerBase* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;

			bool HasAllTags = true;

			for (const FName& Tag : Tags)
			{
				if (!A->Tags.Contains(Tag))
				{
					HasAllTags = false;
					break;
				}
			}

			if (HasAllTags)
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					checkf(0, TEXT("%s: There are more than one Triggers with the Tags: %s."), *Context, *(NameLibrary::ToString(Tags)));
				}
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		checkf(0, TEXT("%s: Failed to find Trigger with Tags: %s."), *Context, *(NameLibrary::ToString(Tags)));
		return nullptr;
	}

	ATriggerBase* FLibrary::GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_TARRAY_EMPTY_RET_NULL(Tags, FName)
		CS_IS_TARRAY_ANY_NONE_RET_NULL(Tags)

		typedef NCsName::FLibrary NameLibrary;

	#if UE_BUILD_SHIPPING
		for (TActorIterator<ATriggerBase> Itr(World); Itr; ++Itr)
		{
			ATriggerBase* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			bool HasAllTags = true;

			for (const FName& Tag : Tags)
			{
				if (!A->Tags.Contains(Tag))
				{
					HasAllTags = false;
					break;
				}
			}

			if (HasAllTags)
				return A;
		}
	#else
		ATriggerBase* Actor = nullptr;
		
		for (TActorIterator<ATriggerBase> Itr(World); Itr; ++Itr)
		{
			ATriggerBase* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;

			bool HasAllTags = true;

			for (const FName& Tag : Tags)
			{
				if (!A->Tags.Contains(Tag))
				{
					HasAllTags = false;
					break;
				}
			}

			if (HasAllTags)
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: There are more than one Triggers with the Tags: %s."), *Context, *(NameLibrary::ToString(Tags))));
				}
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Trigger with Tags: %s."), *Context, *(NameLibrary::ToString(Tags))));
		return nullptr;
	}

	ATriggerBase* FLibrary::GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
	{
		CS_IS_PTR_NULL_CHECKED(WorldContext)
		CS_IS_NAME_NONE_CHECKED(Name)

		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		for (TActorIterator<ATriggerBase> Itr(World); Itr; ++Itr)
		{
			ATriggerBase* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetFName() == Name)
			{
				return A;
			}
		}
		checkf(0, TEXT("%s: Failed to find Trigger with Name: %s."), *Context, *(Name.ToString()));
		return nullptr;
	}

	ATriggerBase* FLibrary::GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		if (Name == NAME_None)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
			return nullptr;
		}

		for (TActorIterator<ATriggerBase> Itr(World); Itr; ++Itr)
		{
			ATriggerBase* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetFName() == Name)
			{
				return A;
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Trigger with Name: %s."), *Context, *(Name.ToString())));
		return nullptr;
	}

	ATriggerBase* FLibrary::GetSafeByName(const UObject* WorldContext, const FName& Name)
	{
		using namespace NCsTrigger::NLibrary::NCached;

		const FString& Context = Str::GetSafeByName;

		return GetSafeByName(Context, WorldContext, Name, nullptr);
	}

	ATriggerBase* FLibrary::GetByLabelChecked(const FString& Context, const UObject* WorldContext, const FString& Label)
	{
	#if WITH_EDITOR
		UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_STRING_EMPTY_CHECKED(Label)

		for (TActorIterator<ATriggerBase> Itr(World); Itr; ++Itr)
		{
			ATriggerBase* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetActorLabel() == Label)
			{
				return A;
			}
		}
		checkf(0, TEXT("%s: Failed to find Trigger with Label: %s."), *Context, *Label);
		return nullptr;
	#else
		checkf(0, TEXT("%s: GetByLabelChecked is NOT Valid outside of Editor."), *Context);
		return nullptr;
	#endif // #if WITH_EDITOR
	}

	ATriggerBase* FLibrary::GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
	#if WITH_EDITOR
		UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

		if (!World)
			return nullptr;

		CS_IS_STRING_EMPTY_RET_NULL(Label)

		for (TActorIterator<ATriggerBase> Itr(World); Itr; ++Itr)
		{
			ATriggerBase* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->GetActorLabel() == Label)
			{
				return A;
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Trigger with Label: %s."), *Context, *Label));
		return nullptr;
	#else
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetSafeActorByLabel is NOT Valid outside of Editor."), *Context));
		return nullptr;
	#endif // #if !WITH_EDITOR
	}

	ATriggerBase* FLibrary::GetSafeByLabel(const UObject* WorldContext, const FString& Label)
	{
		using namespace NCsTrigger::NLibrary::NCached;

		const FString& Context = Str::GetSafeByLabel;

		return GetSafeByLabel(Context, WorldContext, Label, nullptr);
	}

	#pragma endregion Get

	#undef WorldLibrary
}