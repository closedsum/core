// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Actor/CsLibrary_ScriptableActor.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Actor/CsLibrary_Actor.h"
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Name.h"
#include "Library/CsLibrary_Valid.h"
// Script
#include "Actor/CsScriptableActor.h"
// Utility
#include "EngineUtils.h"
// World
#include "Engine/World.h"

namespace NCsActor
{
	namespace NScriptable
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CSJS_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeByTag);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeByName);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeByLabel);
				}
			}
		}

		using LogClassType = NCsJs::FLog;

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		#define USING_NS_CACHED using namespace NCsActor::NScriptable::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsActor::NScriptable::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		// Interface
		#pragma region
		
		bool FLibrary::Implements(const AActor* A) 
		{
			if (!IsValid(A))
				return false;
			if (!Cast<ICsScriptableActor>(A) &&
				!A->GetClass()->ImplementsInterface(UCsScriptableActor::StaticClass()))
				return false;
			return true;
		}

		bool FLibrary::Implements(const AActor* A, bool& OutIsScript)
		{
			if (!IsValid(A))
				return false;

			if (Cast<ICsScriptableActor>(A))
			{
				OutIsScript = false;
				return true;
			}

			if (A->GetClass()->ImplementsInterface(UCsScriptableActor::StaticClass()))
			{
				OutIsScript = true;
				return true;
			}
			return false;
		}

		bool FLibrary::SafeImplements(const FString& Context, const AActor* A, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			CS_IS_PENDING_KILL(A)

			if (!Cast<ICsScriptableActor>(A) &&
				!A->GetClass()->ImplementsInterface(UCsScriptableActor::StaticClass()))
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s %s does NOT implement the interface: ICsScriptableActor."), *Context, *CsActorLibrary::PrintActorAndClass(A)));
				return false;
			}
			return true;
		}

		bool FLibrary::SafeImplements(const FString& Context, const AActor* A, bool& OutIsScript, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			CS_IS_PENDING_KILL(A)

			if (Cast<ICsScriptableActor>(A))
			{
				OutIsScript = false;
				return true;
			}

			if (A->GetClass()->ImplementsInterface(UCsScriptableActor::StaticClass()))
			{
				OutIsScript = true;
				return true;
			}

			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s %s does NOT implement the interface: ICsScriptableActor."), *Context, *CsActorLibrary::PrintActorAndClass(A)));
			return false;
		}

		#pragma endregion Interface

		// Get
		#pragma region

		void FLibrary::GetChecked(const FString& Context, const UObject* WorldContext, TArray<AActor*>& OutActors)
		{
			UWorld* World = CsWorldLibrary::GetChecked(Context, WorldContext);

			for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
			{
				AActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (!Implements(A))
					continue;

				OutActors.Add(A);
			}
			checkf(OutActors.Num() > CS_EMPTY, TEXT("%s: Failed to find any Scriptable Actors (implements the interface: ICsScriptableActor)."), *Context);
		}

		bool FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, TArray<AActor*>& OutActors, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			UWorld* World = CsWorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return false;

			for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
			{
				AActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (!Implements(A))
					continue;

				OutActors.Add(A);
			}

			if (OutActors.Num() == CS_EMPTY)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find any Scriptable Actors (implements the interface: ICsScriptableActor)."), *Context));
				return false;
			}
			return true;
		}

		AActor* FLibrary::GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
		{
			UWorld* World = CsWorldLibrary::GetChecked(Context, WorldContext);

			CS_IS_NAME_NONE_CHECKED(Tag)

		#if UE_BUILD_SHIPPING
			for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
			{
				AActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (!Implements(A))
					continue;
				if (A->Tags.Contains(Tag))
				{
					return A;
				}
			}
		#else
			AActor* Actor = nullptr;
		
			for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
			{
				AActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (!Implements(A))
					continue;
				if (A->Tags.Contains(Tag))
				{
					if (!Actor)
					{
						Actor = A;
					}
					else
					{
						checkf(0, TEXT("%s: There are more than one Scriptable Actors (implements the interface: ICsScriptableActor) with the Tag: %s."), *Context, *(Tag.ToString()));
					}
				}
			}

			if (Actor)
				return Actor;
	#endif // UE_BUILD_SHIPPING

			checkf(0, TEXT("%s: Failed to find Scriptable Actor (implements the interface: ICsScriptableActor) with Tag: %s."), *Context, *(Tag.ToString()));
			return nullptr;
		}

		AActor* FLibrary::GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			UWorld* World = CsWorldLibrary::GetSafe(Context, WorldContext);

			if (!World)
				return nullptr;

			CS_IS_NAME_NONE_RET_NULL(Tag)

	#if UE_BUILD_SHIPPING
			for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
			{
				AActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (!Implements(A))
					continue;
				if (A->Tags.Contains(Tag))
				{
					return A;
				}
			}
	#else
			AActor* Actor = nullptr;

			for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
			{
				AActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (!Implements(A))
					continue;
				if (A->Tags.Contains(Tag))
				{
					if (!Actor)
					{
						Actor = A;
					}
					else
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: There are more than one Scriptable Actors (implements the interface: ICsScriptableActor) with the Tag: %s."), *Context, *(Tag.ToString())));
					}
				}
			}

			if (Actor)
				return Actor;
	#endif // UE_BUILD_SHIPPING

			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Scriptable Actor (implements the interface: ICsScriptableActor) with Tag: %s."), *Context, *(Tag.ToString())));
			return nullptr;
		}

		void FLibrary::GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<AActor*>& OutActors)
		{
			UWorld* World = CsWorldLibrary::GetChecked(Context, WorldContext);

			CS_IS_TARRAY_EMPTY_CHECKED(Tags, FName)
			CS_IS_TARRAY_ANY_NONE_CHECKED(Tags)

			for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
			{
				AActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (!Implements(A))
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
					OutActors.Add(A);
			}
			checkf(OutActors.Num() > CS_EMPTY, TEXT("%s: Failed to find Scriptable Actors (implements the interface: ICsScriptableActor) with Tags: %s."), *Context, *(CsNameLibrary::ToString(Tags)));
		}

		bool FLibrary::GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<AActor*>& OutActors, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			UWorld* World = CsWorldLibrary::GetChecked(Context, WorldContext);

			CS_IS_TARRAY_EMPTY(Tags, FName)
			CS_IS_TARRAY_ANY_NONE(Tags)

			for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
			{
				AActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (!Implements(A))
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
					OutActors.Add(A);
			}

			if (OutActors.Num() == CS_EMPTY)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Scriptable Actors (implements the interface: ICsScriptableActor) with Tags: %s."), *Context, *(CsNameLibrary::ToString(Tags))));
			}
			return OutActors.Num() > CS_EMPTY;
		}

		AActor* FLibrary::GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
		{
			CS_IS_PTR_NULL_CHECKED(WorldContext)
			CS_IS_NAME_NONE_CHECKED(Name)

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

			for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
			{
				AActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (!Implements(A))
					continue;
				if (A->GetFName() == Name)
				{
					return A;
				}
			}
			checkf(0, TEXT("%s: Failed to find Scriptable Actor (implements the interface: ICsScriptableActor) with Name: %s."), *Context, *(Name.ToString()));
			return nullptr;
		}

		AActor* FLibrary::GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			UWorld* World = CsWorldLibrary::GetSafe(Context, WorldContext);

			if (!World)
				return nullptr;

			CS_IS_NAME_NONE_RET_NULL(Name)

			for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
			{
				AActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (!Implements(A))
					continue;
				if (A->GetFName() == Name)
				{
					return A;
				}
			}
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Scriptable Actor (implements the interface: ICsScriptableActor) with Name: %s."), *Context, *(Name.ToString())));
			return nullptr;
		}

		AActor* FLibrary::GetSafeByName(const UObject* WorldContext, const FName& Name)
		{
			SET_CONTEXT(GetSafeByName);

			return GetSafeByName(Context, WorldContext, Name, nullptr);
		}

		AActor* FLibrary::GetByLabelChecked(const FString& Context, const UObject* WorldContext, const FString& Label)
		{
		#if WITH_EDITOR
			UWorld* World = CsWorldLibrary::GetChecked(Context, WorldContext);

			CS_IS_STRING_EMPTY_CHECKED(Label)

			for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
			{
				AActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (!Implements(A))
					continue;
				if (A->GetActorLabel() == Label)
				{
					return A;
				}
			}
			checkf(0, TEXT("%s: Failed to find Scriptable Actor (implements the interface: ICsScriptableActor) with Label: %s."), *Context, *Label);
			return nullptr;
		#else
			checkf(0, TEXT("%s: GetByLabelChecked is NOT Valid outside of Editor."), *Context);
			return nullptr;
		#endif // #if WITH_EDITOR
		}

		AActor* FLibrary::GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
		#if WITH_EDITOR
			UWorld* World = CsWorldLibrary::GetSafe(Context, WorldContext);

			if (!World)
				return nullptr;

			CS_IS_STRING_EMPTY_RET_NULL(Label)

			for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
			{
				AActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (!Implements(A))
					continue;
				if (A->GetActorLabel() == Label)
				{
					return A;
				}
			}
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Scriptable Actor (implements the interface: ICsScriptableActor) with Label: %s."), *Context, *Label));
			return nullptr;
	#else
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetSafeActorByLabel is NOT Valid outside of Editor."), *Context));
			return nullptr;
	#endif // #if !WITH_EDITOR
		}

		AActor* FLibrary::GetSafeByLabel(const UObject* WorldContext, const FString& Label)
		{
			SET_CONTEXT(GetSafeByLabel);

			return GetSafeByLabel(Context, WorldContext, Label, nullptr);
		}

		#pragma endregion Get

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}