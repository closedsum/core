// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Character.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Animation/CsLibrary_AnimMontage.h"
#include "Library/CsLibrary_World.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Name.h"
#include "Library/CsLibrary_Valid.h"
// Character
#include "GameFramework/Character.h"
// Component
#include "Components/SkeletalMeshComponent.h"
// Utility
#include "EngineUtils.h"
// World
#include "Engine/World.h"

namespace NCsCharacter
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCharacter::FLibrary, GetSafeByTag);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeByName);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsActor::FLibrary, GetSafeByLabel);
			}

			namespace Name
			{
			}
		}
	}

	#define USING_NS_CACHED using namespace NCsCharacter::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsCharacter::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
	#define LogWarning void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/
	#define AnimMontageLibrary NCsAnimMontage::FLibrary

	// Get
	#pragma region

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
			if (A->Tags.Contains(Tag))
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					checkf(0, TEXT("%s: There are more than one Characters with the Tag: %s."), *Context, *(Tag.ToString()));
				}
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		checkf(0, TEXT("%s: Failed to find Character with Tag: %s."), *Context, *(Tag.ToString()));
		return nullptr;
	}

	ACharacter* FLibrary::GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, LogWarning)
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
			if (A->Tags.Contains(Tag))
			{
				return A;
			}
		}
#	else
			ACharacter* Actor = nullptr;

		for (TActorIterator<ACharacter> Itr(World); Itr; ++Itr)
		{
			ACharacter* A = *Itr;

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
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: There are more than one Characters with the Tag: %s."), *Context, *(Tag.ToString())));
				}
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Character with Tag: %s."), *Context, *(Tag.ToString())));
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

		checkf(OutCharacters.Num() > CS_EMPTY, TEXT("%s: Failed to find Characters with Tags: %s."), *Context, *(CsNameLibrary::ToString(Tags)));
	}
	
	ACharacter* FLibrary::GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags)
	{
		UWorld* World = CsWorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_TARRAY_EMPTY_CHECKED(Tags, FName)
		CS_IS_TARRAY_ANY_NONE_CHECKED(Tags)

		ACharacter* C = nullptr;

		int32 Count = 0;

		for (TActorIterator<ACharacter> Itr(World); Itr; ++Itr)
		{
			ACharacter* A = *Itr;

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
			{
				if (!C)
					C = A;
				++Count;
			}
		}

		checkf(Count == 1, TEXT("%s: Found %d Character. Failed to find Only ONE Character with Tags: %s."), *Context, Count, *(CsNameLibrary::ToString(Tags)));
		return C;
	}

	bool FLibrary::GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters, LogWarning)
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
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Characters with Tags: %s."), *Context, *(CsNameLibrary::ToString(Tags))));
		}
		return OutCharacters.Num() > CS_EMPTY;
	}

	ACharacter* FLibrary::GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, LogWarning)
	{
		TArray<ACharacter*> Characters;
		if (GetSafeByTags(Context, WorldContext, Tags, Characters, Log))
		{
			if (Characters.Num() > 1)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: More than 1 Character founds with Tags."), *Context));
			}
			return Characters[CS_FIRST];
		}
		return nullptr;
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
			if (A->GetFName() == Name)
			{
				return A;
			}
		}
		checkf(0, TEXT("%s: Failed to find Character with Name: %s."), *Context, *(Name.ToString()));
		return nullptr;
	}

	ACharacter* FLibrary::GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, LogWarning)
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
			if (A->GetFName() == Name)
			{
				return A;
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Character with Name: %s."), *Context, *(Name.ToString())));
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
			if (A->GetActorLabel() == Label)
			{
				return A;
			}
		}
		checkf(0, TEXT("%s: Failed to find Character with Label: %s."), *Context, *Label);
		return nullptr;
	#else
		checkf(0, TEXT("%s: GetByLabelChecked is NOT Valid outside of Editor."), *Context);
		return nullptr;
	#endif // #if WITH_EDITOR
	}

	ACharacter* FLibrary::GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, LogWarning)
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
			if (A->GetActorLabel() == Label)
			{
				return A;
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Character with Label: %s."), *Context, *Label));
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

	// Anim
	#pragma region

	#define ParamsType NCsAnimMontage::NPlay::FParams

	float FLibrary::PlayChecked(const FString& Context, const ACharacter* Character, const ParamsType& Params)
	{
		CS_IS_PENDING_KILL_CHECKED(Character)

		USkeletalMeshComponent* Mesh = Character->GetMesh();

		CS_IS_PENDING_KILL_CHECKED(Mesh)

		return AnimMontageLibrary::PlayChecked(Context, Mesh, Params);
	}

	float FLibrary::SafePlay(const FString& Context, const ACharacter* Character, const ParamsType& Params, bool& OutSuccess, LogWarning)
	{
		OutSuccess = false;

		CS_IS_PENDING_KILL_RET_VALUE(Character, -1.0f)

		USkeletalMeshComponent* Mesh = Character->GetMesh();

		CS_IS_PENDING_KILL_RET_VALUE(Mesh, -1.0f)

		return AnimMontageLibrary::SafePlay(Context, Mesh, Params, OutSuccess, Log);
	}

	float FLibrary::SafePlay(const FString& Context, const ACharacter* Character, const FCsAnimMontage_PlayByPathParams& Params, bool& OutSuccess, LogWarning)
	{
		OutSuccess = false;

		CS_IS_PENDING_KILL_RET_VALUE(Character, -1.0f)

		USkeletalMeshComponent* Mesh = Character->GetMesh();

		CS_IS_PENDING_KILL_RET_VALUE(Mesh, -1.0f)

		return AnimMontageLibrary::SafePlay(Context, Mesh, Params, OutSuccess, Log);
	}

	#undef ParamsType

	#pragma endregion Anim

	#undef USING_NS_CACHED
	#undef SET_CONTEXT
	#undef LogWarning
	#undef AnimMontageLibrary
}