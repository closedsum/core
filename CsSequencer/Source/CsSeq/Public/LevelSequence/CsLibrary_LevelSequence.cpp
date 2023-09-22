// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "LevelSequence/CsLibrary_LevelSequence.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Name.h"
#include "Library/CsLibrary_Valid.h"
// Sequence
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
// Utility
#include "EngineUtils.h"
// World
#include "Engine/World.h"
#include "Engine/World.h"

namespace NCsLevelSequence
{
	namespace NActor
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CSSEQ_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevelSequence::NActor::FLibrary, GetSafeByTag);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevelSequence::NActor::FLibrary, GetSafeByName);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevelSequence::NActor::FLibrary, GetSafeByLabel);
				}

				namespace Name
				{
				}
			}
		}

		// Get
		#pragma region

		#define WorldLibrary NCsWorld::FLibrary

		ALevelSequenceActor* FLibrary::GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
		{
			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

			CS_IS_NAME_NONE_CHECKED(Tag)

		#if UE_BUILD_SHIPPING
			for (TActorIterator<ALevelSequenceActor> Itr(World); Itr; ++Itr)
			{
				ALevelSequenceActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (A->Tags.Contains(Tag))
				{
					return A;
				}
			}
		#else
				ALevelSequenceActor* Actor = nullptr;
		
			for (TActorIterator<ALevelSequenceActor> Itr(World); Itr; ++Itr)
			{
				ALevelSequenceActor* A = *Itr;

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
						checkf(0, TEXT("%s: There are more than one LevelSequenceActors with the Tag: %s."), *Context, *(Tag.ToString()));
					}
				}
			}

			if (Actor)
				return Actor;
		#endif // UE_BUILD_SHIPPING

			checkf(0, TEXT("%s: Failed to find LevelSequenceActor with Tag: %s."), *Context, *(Tag.ToString()));
			return nullptr;
		}

		ALevelSequenceActor* FLibrary::GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
		{
			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

			if (!World)
				return nullptr;

			CS_IS_NAME_NONE_RET_NULL(Tag)

		#if UE_BUILD_SHIPPING
			for (TActorIterator<ALevelSequenceActor> Itr(World); Itr; ++Itr)
			{
				ALevelSequenceActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (A->Tags.Contains(Tag))
				{
					return A;
				}
			}
	#	else
				ALevelSequenceActor* Actor = nullptr;

			for (TActorIterator<ALevelSequenceActor> Itr(World); Itr; ++Itr)
			{
				ALevelSequenceActor* A = *Itr;

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
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: There are more than one LevelSequenceActors with the Tag: %s."), *Context, *(Tag.ToString())));
					}
				}
			}

			if (Actor)
				return Actor;
		#endif // UE_BUILD_SHIPPING

			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find LevelSequenceActor with Tag: %s."), *Context, *(Tag.ToString())));
			return nullptr;
		}

		ALevelSequenceActor* FLibrary::GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags)
		{
			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

			CS_IS_TARRAY_EMPTY_CHECKED(Tags, FName)
			CS_IS_TARRAY_ANY_NONE_CHECKED(Tags)

			typedef NCsName::FLibrary NameLibrary;

		#if UE_BUILD_SHIPPING
			for (TActorIterator<ALevelSequenceActor> Itr(World); Itr; ++Itr)
			{
				ALevelSequenceActor* A = *Itr;

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
			ALevelSequenceActor* Actor = nullptr;
		
			for (TActorIterator<ALevelSequenceActor> Itr(World); Itr; ++Itr)
			{
				ALevelSequenceActor* A = *Itr;

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
						checkf(0, TEXT("%s: There are more than one LevelSequenceActors with the Tags: %s."), *Context, *(NameLibrary::ToString(Tags)));
					}
				}
			}

			if (Actor)
				return Actor;
		#endif // UE_BUILD_SHIPPING

			checkf(0, TEXT("%s: Failed to find LevelSequenceActor with Tags: %s."), *Context, *(NameLibrary::ToString(Tags)));
			return nullptr;
		}

		ALevelSequenceActor* FLibrary::GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
		{
			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

			CS_IS_TARRAY_EMPTY_RET_NULL(Tags, FName)
			CS_IS_TARRAY_ANY_NONE_RET_NULL(Tags)

			typedef NCsName::FLibrary NameLibrary;

		#if UE_BUILD_SHIPPING
			for (TActorIterator<ALevelSequenceActor> Itr(World); Itr; ++Itr)
			{
				ALevelSequenceActor* A = *Itr;

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
			ALevelSequenceActor* Actor = nullptr;
		
			for (TActorIterator<ALevelSequenceActor> Itr(World); Itr; ++Itr)
			{
				ALevelSequenceActor* A = *Itr;

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
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: There are more than one LevelSequenceActors with the Tags: %s."), *Context, *(NameLibrary::ToString(Tags))));
					}
				}
			}

			if (Actor)
				return Actor;
		#endif // UE_BUILD_SHIPPING

			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find LevelSequenceActor with Tags: %s."), *Context, *(NameLibrary::ToString(Tags))));
			return nullptr;
		}

		ALevelSequenceActor* FLibrary::GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
		{
			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

			if (!World)
				return nullptr;

			CS_IS_NAME_NONE_CHECKED(Name)

			for (TActorIterator<ALevelSequenceActor> Itr(World); Itr; ++Itr)
			{
				ALevelSequenceActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (A->GetFName() == Name)
				{
					return A;
				}
			}
			checkf(0, TEXT("%s: Failed to find LevelSequenceActor with Name: %s."), *Context, *(Name.ToString()));
			return nullptr;
		}

		ALevelSequenceActor* FLibrary::GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
		{
			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext);

			if (!World)
				return nullptr;

			if (Name == NAME_None)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
				return nullptr;
			}

			for (TActorIterator<ALevelSequenceActor> Itr(World); Itr; ++Itr)
			{
				ALevelSequenceActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (A->GetFName() == Name)
				{
					return A;
				}
			}
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find LevelSequenceActor with Name: %s."), *Context, *(Name.ToString())));
			return nullptr;
		}

		ALevelSequenceActor* FLibrary::GetSafeByName(const UObject* WorldContext, const FName& Name)
		{
			using namespace NCsLevelSequence::NActor::NLibrary::NCached;

			const FString& Context = Str::GetSafeByName;

			return GetSafeByName(Context, WorldContext, Name, nullptr);
		}

		ALevelSequenceActor* FLibrary::GetByLabelChecked(const FString& Context, const UObject* WorldContext, const FString& Label)
		{
		#if WITH_EDITOR

			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

			checkf(!Label.IsEmpty(), TEXT("%s: Label is EMPTY."), *Context);

			for (TActorIterator<ALevelSequenceActor> Itr(World); Itr; ++Itr)
			{
				ALevelSequenceActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (A->GetActorLabel() == Label)
				{
					return A;
				}
			}
			checkf(0, TEXT("%s: Failed to find LevelSequenceActor with Label: %s."), *Context, *Label);
			return nullptr;
		#else
			checkf(0, TEXT("%s: GetByLabelChecked is NOT Valid outside of Editor."), *Context);
			return nullptr;
		#endif // #if WITH_EDITOR
		}

		ALevelSequenceActor* FLibrary::GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
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

			for (TActorIterator<ALevelSequenceActor> Itr(World); Itr; ++Itr)
			{
				ALevelSequenceActor* A = *Itr;

				// Check is Valid and NOT getting destroyed
				if (!IsValid(A))
					continue;
				if (A->GetActorLabel() == Label)
				{
					return A;
				}
			}
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find LevelSequenceActor with Label: %s."), *Context, *Label));
			return nullptr;
	#else
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetSafeActorByLabel is NOT Valid outside of Editor."), *Context));
			return nullptr;
	#endif // #if !WITH_EDITOR
		}

		ALevelSequenceActor* FLibrary::GetSafeByLabel(const UObject* WorldContext, const FString& Label)
		{
			using namespace NCsLevelSequence::NActor::NLibrary::NCached;

			const FString& Context = Str::GetSafeByLabel;

			return GetSafeByLabel(Context, WorldContext, Label, nullptr);
		}

		#undef WorldLibrary

		#pragma endregion Get

		// Player
		#pragma region

		void FLibrary::SetPlaybackPositionFrameZeroChecked(const FString& Context, ALevelSequenceActor* Sequence)
		{
			CS_IS_PENDING_KILL_CHECKED(Sequence)

			ULevelSequencePlayer* Player = Sequence->GetSequencePlayer();

			CS_IS_PENDING_KILL_CHECKED(Player)

			FMovieSceneSequencePlaybackParams Params;
			Params.Frame = FFrameTime();
			Params.PositionType = EMovieScenePositionType::Frame;
			Params.UpdateMethod = EUpdatePositionMethod::Jump;

			Player->SetPlaybackPosition(Params);
		}

		bool FLibrary::SetSafePlaybackPositionFrameZero(const FString& Context, ALevelSequenceActor* Sequence, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
		{
			CS_IS_PENDING_KILL(Sequence)

			ULevelSequencePlayer* Player = Sequence->GetSequencePlayer();

			CS_IS_PENDING_KILL(Player)

			FMovieSceneSequencePlaybackParams Params;
			Params.Frame = FFrameTime();
			Params.PositionType = EMovieScenePositionType::Frame;
			Params.UpdateMethod = EUpdatePositionMethod::Jump;

			Player->SetPlaybackPosition(Params);
			return true;
		}

		#pragma endregion Player
	}
}