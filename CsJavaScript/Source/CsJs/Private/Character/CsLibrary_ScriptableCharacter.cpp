// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Character/CsLibrary_ScriptableCharacter.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Name.h"
#include "Library/CsLibrary_Valid.h"
// Script
#include "Actor/CsScriptableActor.h"
// Character
#include "GameFramework/Character.h"
// Utility
#include "EngineUtils.h"
// World
#include "Engine/World.h"

namespace NCsCharacter
{
	namespace NScriptable
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CSJS_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCharacter::FLibrary, GetSafeByTag);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCharacter::FLibrary, GetSafeByName);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCharacter::FLibrary, GetSafeByLabel);
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsCharacter::NScriptable::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsCharacter::NScriptable::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define LogLevel void(*Log)(const FString&) /*=&NCsJs::FLog::Warning*/

		// Interface
		#pragma region
		
		bool FLibrary::Implements(const ACharacter* A) 
		{
			if (!IsValid(A))
				return false;
			if (!Cast<ICsScriptableActor>(A) &&
				!A->GetClass()->ImplementsInterface(UCsScriptableActor::StaticClass()))
				return false;
			return true;
		}

		#pragma endregion Interface

		// Get
		#pragma region

		void FLibrary::GetChecked(const FString& Context, const UObject* WorldContext, TArray<ACharacter*>& OutCharacters)
		{
			UWorld* World = CsWorldLibrary::GetChecked(Context, WorldContext);

			for (TActorIterator<ACharacter> Itr(World); Itr; ++Itr)
			{
				ACharacter* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (!Implements(A))
					continue;

				OutCharacters.Add(A);
			}
			checkf(OutCharacters.Num() > CS_EMPTY, TEXT("%s: Failed to find any Scriptable Actors (implements the interface: ICsScriptableActor)."), *Context);
		}

		bool FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, TArray<ACharacter*>& OutCharacters, LogLevel)
		{
			UWorld* World = CsWorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return false;

			for (TActorIterator<ACharacter> Itr(World); Itr; ++Itr)
			{
				ACharacter* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (!Implements(A))
					continue;

				OutCharacters.Add(A);
			}

			if (OutCharacters.Num() == CS_EMPTY)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find any Scriptable Actors (implements the interface: ICsScriptableActor)."), *Context));
				return false;
			}
			return true;
		}

		ACharacter* FLibrary::GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
		{
			UWorld* World = CsWorldLibrary::GetChecked(Context, WorldContext);

			CS_IS_NAME_NONE_CHECKED(Tag)

		#if UE_BUILD_SHIPPING
			for (TActorIterator<ACharacter> Itr(World); Itr; ++Itr)
			{
				ACharacter* A = *Itr;

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
			ACharacter* Actor = nullptr;
		
			for (TActorIterator<ACharacter> Itr(World); Itr; ++Itr)
			{
				ACharacter* A = *Itr;

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

		ACharacter* FLibrary::GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, LogLevel)
		{
			UWorld* World = CsWorldLibrary::GetSafe(Context, WorldContext);

			if (!World)
				return nullptr;

			CS_IS_NAME_NONE_RET_NULL(Tag)

	#if UE_BUILD_SHIPPING
			for (TActorIterator<ACharacter> Itr(World); Itr; ++Itr)
			{
				ACharacter* A = *Itr;

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
				ACharacter* Actor = nullptr;

			for (TActorIterator<ACharacter> Itr(World); Itr; ++Itr)
			{
				ACharacter* A = *Itr;

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

		void FLibrary::GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters)
		{
			UWorld* World = CsWorldLibrary::GetChecked(Context, WorldContext);

			CS_IS_TARRAY_EMPTY_CHECKED(Tags, FName)
			CS_IS_TARRAY_ANY_NONE_CHECKED(Tags)

			for (TActorIterator<ACharacter> Itr(World); Itr; ++Itr)
			{
				ACharacter* A = *Itr;

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
					OutCharacters.Add(A);
			}
			checkf(OutCharacters.Num() > CS_EMPTY, TEXT("%s: Failed to find Scriptable Actors (implements the interface: ICsScriptableActor) with Tags: %s."), *Context, *(CsNameLibrary::ToString(Tags)));
		}

		bool FLibrary::GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters, LogLevel)
		{
			UWorld* World = CsWorldLibrary::GetChecked(Context, WorldContext);

			CS_IS_TARRAY_EMPTY(Tags, FName)
			CS_IS_TARRAY_ANY_NONE(Tags)

			for (TActorIterator<ACharacter> Itr(World); Itr; ++Itr)
			{
				ACharacter* A = *Itr;

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
					OutCharacters.Add(A);
			}

			if (OutCharacters.Num() == CS_EMPTY)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Scriptable Actors (implements the interface: ICsScriptableActor) with Tags: %s."), *Context, *(CsNameLibrary::ToString(Tags))));
			}
			return OutCharacters.Num() > CS_EMPTY;
		}

		ACharacter* FLibrary::GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
		{
			CS_IS_PTR_NULL_CHECKED(WorldContext)
			CS_IS_NAME_NONE_CHECKED(Name)

			UWorld* World = CsWorldLibrary::GetChecked(Context, WorldContext);

			for (TActorIterator<ACharacter> Itr(World); Itr; ++Itr)
			{
				ACharacter* A = *Itr;

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

		ACharacter* FLibrary::GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, LogLevel)
		{
			UWorld* World = CsWorldLibrary::GetSafe(Context, WorldContext);

			if (!World)
				return nullptr;

			CS_IS_NAME_NONE_RET_NULL(Name)

			for (TActorIterator<ACharacter> Itr(World); Itr; ++Itr)
			{
				ACharacter* A = *Itr;

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

		ACharacter* FLibrary::GetSafeByName(const UObject* WorldContext, const FName& Name)
		{
			SET_CONTEXT(GetSafeByName);

			return GetSafeByName(Context, WorldContext, Name, nullptr);
		}

		ACharacter* FLibrary::GetByLabelChecked(const FString& Context, const UObject* WorldContext, const FString& Label)
		{
		#if WITH_EDITOR
			UWorld* World = CsWorldLibrary::GetChecked(Context, WorldContext);

			CS_IS_STRING_EMPTY_CHECKED(Label)

			for (TActorIterator<ACharacter> Itr(World); Itr; ++Itr)
			{
				ACharacter* A = *Itr;

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

		ACharacter* FLibrary::GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, LogLevel)
		{
		#if WITH_EDITOR
			UWorld* World = CsWorldLibrary::GetSafe(Context, WorldContext);

			if (!World)
				return nullptr;

			CS_IS_STRING_EMPTY_RET_NULL(Label)

			for (TActorIterator<ACharacter> Itr(World); Itr; ++Itr)
			{
				ACharacter* A = *Itr;

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

		ACharacter* FLibrary::GetSafeByLabel(const UObject* WorldContext, const FString& Label)
		{
			SET_CONTEXT(GetSafeByLabel);

			return GetSafeByLabel(Context, WorldContext, Label, nullptr);
		}

		#pragma endregion Get

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef LogLevel
	}
}