// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Character/CsLibrary_ScriptableCharacter.h"

// Types
#include "Types/CsTypes_Macro.h"
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

		// Interface
		#pragma region
		
		bool FLibrary::Implements(const ACharacter* A) 
		{
			if (!A)
				return false;
			if (!Cast<ICsScriptableActor>(A) &&
				!A->GetClass()->ImplementsInterface(UCsScriptableActor::StaticClass()))
				return false;
			return true;
		}

		#pragma endregion Interface

		// Get
		#pragma region

		#define WorldLibrary NCsWorld::FLibrary

		void FLibrary::GetChecked(const FString& Context, const UObject* WorldContext, TArray<ACharacter*>& OutCharacters)
		{
			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

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

			typedef NCsName::FLibrary NameLibrary;

			checkf(OutCharacters.Num() > CS_EMPTY, TEXT("%s: Failed to find any Scriptable Actors (implements the interface: ICsScriptableActor)."), *Context);
		}

		bool FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, TArray<ACharacter*>& OutCharacters, void(*Log)(const FString&) /*=&NCsJs::FLog::Warning*/)
		{
			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

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

			typedef NCsName::FLibrary NameLibrary;

			if (OutCharacters.Num() == CS_EMPTY)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find any Scriptable Actors (implements the interface: ICsScriptableActor)."), *Context));
				return false;
			}
			return true;
		}

		ACharacter* FLibrary::GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
		{
			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

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

		ACharacter* FLibrary::GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

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
			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

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

			typedef NCsName::FLibrary NameLibrary;

			checkf(OutCharacters.Num() > CS_EMPTY, TEXT("%s: Failed to find Scriptable Actors (implements the interface: ICsScriptableActor) with Tags: %s."), *Context, *(NameLibrary::ToString(Tags)));
		}

		bool FLibrary::GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

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

			typedef NCsName::FLibrary NameLibrary;

			if (OutCharacters.Num() == CS_EMPTY)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Scriptable Actors (implements the interface: ICsScriptableActor) with Tags: %s."), *Context, *(NameLibrary::ToString(Tags))));
			}
			return OutCharacters.Num() > CS_EMPTY;
		}

		ACharacter* FLibrary::GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
		{
			CS_IS_PTR_NULL_CHECKED(WorldContext)
			CS_IS_NAME_NONE_CHECKED(Name)

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

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

		ACharacter* FLibrary::GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

			if (!World)
				return nullptr;

			if (Name == NAME_None)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
				return nullptr;
			}

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
			using namespace NCsCharacter::NScriptable::NLibrary::NCached;

			const FString& Context = Str::GetSafeByName;

			return GetSafeByName(Context, WorldContext, Name, nullptr);
		}

		ACharacter* FLibrary::GetByLabelChecked(const FString& Context, const UObject* WorldContext, const FString& Label)
		{
		#if WITH_EDITOR
			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

			checkf(!Label.IsEmpty(), TEXT("%s: Label is EMPTY."), *Context);

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

		ACharacter* FLibrary::GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
		#if WITH_EDITOR
			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

			if (!World)
				return nullptr;

			if (Label.IsEmpty())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Label is EMPTY."), *Context));
				return nullptr;
			}

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
			using namespace NCsCharacter::NScriptable::NLibrary::NCached;

			const FString& Context = Str::GetSafeByLabel;

			return GetSafeByLabel(Context, WorldContext, Label, nullptr);
		}

		#undef WorldLibrary

		#pragma endregion Get
	}
}