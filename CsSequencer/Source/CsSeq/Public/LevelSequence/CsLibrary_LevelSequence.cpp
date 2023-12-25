// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "LevelSequence/CsLibrary_LevelSequence.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Settings/CsLibrary_LevelSequenceProjectSettings.h"
	// Common
#include "MovieScene/CsLibrary_MovieScene.h"
#include "Library/CsLibrary_World.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Name.h"
#include "Library/CsLibrary_Valid.h"
// Sequence
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
// MovieScene
#include "Compilation/MovieSceneCompiledDataManager.h"
// Utility
#include "EngineUtils.h"
// World
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

		ULevelSequencePlayer* FLibrary::GetPlayerChecked(const FString& Context, ALevelSequenceActor* Sequence)
		{
			CS_IS_PENDING_KILL_CHECKED(Sequence)

			ULevelSequencePlayer* Player = Sequence->GetSequencePlayer();

			CS_IS_PENDING_KILL_CHECKED(Player)
			return Player;
		}

		ULevelSequencePlayer* FLibrary::GetSafePlayer(const FString& Context, ALevelSequenceActor* Sequence, bool& OutSuccess, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
		{
			CS_IS_PENDING_KILL_RET_NULL(Sequence)

			ULevelSequencePlayer* Player = Sequence->GetSequencePlayer();

			CS_IS_PENDING_KILL_RET_NULL(Player)
			return Player;
		}

		#define SequencePlayerLibrary NCsLevelSequence::NPlayer::FLibrary

		void FLibrary::PlayFromStartChecked(const FString& Context, ALevelSequenceActor* Sequence)
		{
			SequencePlayerLibrary::PlayFromStartChecked(Context, GetPlayerChecked(Context, Sequence));
		}

		bool FLibrary::SafePlayFromStart(const FString& Context, ALevelSequenceActor* Sequence, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
		{
			return SequencePlayerLibrary::SafePlayFromStart(Context, GetSafePlayer(Context, Sequence, Log), Log);
		}

		#undef SequencePlayerLibrary

		FFrameRate FLibrary::GetFrameRateChecked(const FString& Context, ALevelSequenceActor* Sequence)
		{
			return GetPlayerChecked(Context, Sequence)->GetFrameRate();
		}

		bool FLibrary::GetSafeFrameRate(const FString& Context, ALevelSequenceActor* Sequence, FFrameRate& OutFrameRate, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
		{
			OutFrameRate = FFrameRate();

			if (ULevelSequencePlayer* Player = GetSafePlayer(Context, Sequence, Log))
			{
				OutFrameRate = Player->GetFrameRate();
				return true;
			}
			return false;
		}

		void FLibrary::SetPlaybackPositionFrameZeroChecked(const FString& Context, ALevelSequenceActor* Sequence)
		{
			FMovieSceneSequencePlaybackParams Params;
			Params.Frame = FFrameTime();
			Params.PositionType = EMovieScenePositionType::Frame;
			Params.UpdateMethod = EUpdatePositionMethod::Jump;

			GetPlayerChecked(Context, Sequence)->SetPlaybackPosition(Params);
		}

		bool FLibrary::SetSafePlaybackPositionFrameZero(const FString& Context, ALevelSequenceActor* Sequence, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
		{
			if (ULevelSequencePlayer* Player = GetSafePlayer(Context, Sequence, Log))
			{
				FMovieSceneSequencePlaybackParams Params;
				Params.Frame = FFrameTime();
				Params.PositionType = EMovieScenePositionType::Frame;
				Params.UpdateMethod = EUpdatePositionMethod::Jump;

				Player->SetPlaybackPosition(Params);
				return true;
			}
			return false;
		}

		#pragma endregion Player
	}

	namespace NPlayer
	{
		// Get
		#pragma region

		#define LevelSequenceLibrary NCsLevelSequence::NActor::FLibrary

		ULevelSequencePlayer* FLibrary::GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
		{
			ULevelSequencePlayer* Player = LevelSequenceLibrary::GetByTagChecked(Context, WorldContext, Tag)->GetSequencePlayer();

			CS_IS_PENDING_KILL_CHECKED(Player)
			return Player;
		}

		ULevelSequencePlayer* FLibrary::GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
		{
			if (ALevelSequenceActor* LSA = LevelSequenceLibrary::GetSafeByTag(Context, WorldContext, Tag, Log))
			{
				ULevelSequencePlayer* Player = LSA->GetSequencePlayer();

				CS_IS_PENDING_KILL_RET_NULL(Player)
				return Player;
			}
			return nullptr;
		}

		ULevelSequencePlayer* FLibrary::GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags)
		{
			ULevelSequencePlayer* Player = LevelSequenceLibrary::GetByTagsChecked(Context, WorldContext, Tags)->GetSequencePlayer();

			CS_IS_PENDING_KILL_CHECKED(Player)
			return Player;
		}

		ULevelSequencePlayer* FLibrary::GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
		{
			if (ALevelSequenceActor* LSA = LevelSequenceLibrary::GetSafeByTags(Context, WorldContext, Tags, Log))
			{
				ULevelSequencePlayer* Player = LSA->GetSequencePlayer();

				CS_IS_PENDING_KILL_RET_NULL(Player)
				return Player;
			}
			return nullptr;
		}

		ULevelSequencePlayer* FLibrary::GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
		{
			ULevelSequencePlayer* Player = LevelSequenceLibrary::GetByNameChecked(Context, WorldContext, Name)->GetSequencePlayer();

			CS_IS_PENDING_KILL_CHECKED(Player)
			return Player;
		}

		ULevelSequencePlayer* FLibrary::GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
		{
			if (ALevelSequenceActor* LSA = LevelSequenceLibrary::GetSafeByName(Context, WorldContext, Name, Log))
			{
				ULevelSequencePlayer* Player = LSA->GetSequencePlayer();

				CS_IS_PENDING_KILL_RET_NULL(Player)
				return Player;
			}
			return nullptr;
		}

		ULevelSequencePlayer* FLibrary::GetSafeByName(const UObject* WorldContext, const FName& Name)
		{
			using namespace NCsLevelSequence::NActor::NLibrary::NCached;

			const FString& Context = Str::GetSafeByName;

			return GetSafeByName(Context, WorldContext, Name, nullptr);
		}

		ULevelSequencePlayer* FLibrary::GetByLabelChecked(const FString& Context, const UObject* WorldContext, const FString& Label)
		{
		#if WITH_EDITOR
			ULevelSequencePlayer* Player = LevelSequenceLibrary::GetByLabelChecked(Context, WorldContext, Label)->GetSequencePlayer();

			CS_IS_PENDING_KILL_CHECKED(Player)
			return Player;
		#else
			checkf(0, TEXT("%s: GetByLabelChecked is NOT Valid outside of Editor."), *Context);
			return nullptr;
		#endif // #if WITH_EDITOR
		}

		ULevelSequencePlayer* FLibrary::GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
		{
		#if WITH_EDITOR
			if (ALevelSequenceActor* LSA = LevelSequenceLibrary::GetSafeByLabel(Context, WorldContext, Label, Log))
			{
				ULevelSequencePlayer* Player = LSA->GetSequencePlayer();

				CS_IS_PENDING_KILL_RET_NULL(Player)
				return Player;
			}
			return nullptr;
	#else
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetSafeActorByLabel is NOT Valid outside of Editor."), *Context));
			return nullptr;
	#endif // #if !WITH_EDITOR
		}

		ULevelSequencePlayer* FLibrary::GetSafeByLabel(const UObject* WorldContext, const FString& Label)
		{
			using namespace NCsLevelSequence::NActor::NLibrary::NCached;

			const FString& Context = Str::GetSafeByLabel;

			return GetSafeByLabel(Context, WorldContext, Label, nullptr);
		}

		#undef LevelSequenceLibrary

		#pragma endregion Get

		// Play
		#pragma region

		void FLibrary::PlayFromStartChecked(const FString& Context, ULevelSequencePlayer* Player)
		{
			CS_IS_PENDING_KILL_CHECKED(Player)

			FMovieSceneSequencePlaybackParams Params;
			Params.Frame = FFrameTime();
			Params.PositionType = EMovieScenePositionType::Frame;
			Params.UpdateMethod = EUpdatePositionMethod::Jump;

			Player->SetPlaybackPosition(Params);
			Player->Play();
		}

		bool FLibrary::SafePlayFromStart(const FString& Context, ULevelSequencePlayer* Player, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
		{
			CS_IS_PENDING_KILL(Player)

			FMovieSceneSequencePlaybackParams Params;
			Params.Frame = FFrameTime();
			Params.PositionType = EMovieScenePositionType::Frame;
			Params.UpdateMethod = EUpdatePositionMethod::Jump;

			Player->SetPlaybackPosition(Params);
			Player->Play();
			return true;
		}

		#pragma endregion Play
	}

	namespace NTrack
	{
		namespace NCameraCut
		{
			#define TrackLibrary NCsMovieScene::NTrack::NCameraCut::FLibrary

			UMovieSceneCameraCutTrack* FLibrary::GetChecked(const FString& Context, ULevelSequence* Sequence)
			{
				CS_IS_PENDING_KILL_CHECKED(Sequence)

				return TrackLibrary::GetChecked(Context, Sequence->GetMovieScene());
			}

			UMovieSceneCameraCutTrack* FLibrary::GetSafe(const FString& Context, ULevelSequence* Sequence, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
			{
				CS_IS_PENDING_KILL_RET_NULL(Sequence)

				return TrackLibrary::GetSafe(Context, Sequence->GetMovieScene(), Log);
			}

			void FLibrary::EnableChecked(const FString& Context, ULevelSequence* Sequence)
			{
				CS_IS_PENDING_KILL_CHECKED(Sequence)

				TrackLibrary::EnableChecked(Context, Sequence->GetMovieScene());

				UMovieSceneCompiledDataManager::GetPrecompiledData()->Compile(Sequence);
			}

			bool FLibrary::EnableSafe(const FString& Context, ULevelSequence* Sequence, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
			{
				CS_IS_PENDING_KILL(Sequence)

				if (!TrackLibrary::EnableSafe(Context, Sequence->GetMovieScene(), Log))
					return false;

				UMovieSceneCompiledDataManager::GetPrecompiledData()->Compile(Sequence);
				return true;
			}

			void FLibrary::MuteChecked(const FString& Context, ULevelSequence* Sequence)
			{
				CS_IS_PENDING_KILL_CHECKED(Sequence)

				TrackLibrary::MuteChecked(Context, Sequence->GetMovieScene());

				UMovieSceneCompiledDataManager::GetPrecompiledData()->Compile(Sequence);
			}

			bool FLibrary::MuteSafe(const FString& Context, ULevelSequence* Sequence, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
			{
				CS_IS_PENDING_KILL(Sequence)

				if (!TrackLibrary::MuteSafe(Context, Sequence->GetMovieScene(), Log))
					return false;

				UMovieSceneCompiledDataManager::GetPrecompiledData()->Compile(Sequence);
				return true;
			}

			bool FLibrary::SetSafeEaseInDuration(const FString& Context, ULevelSequence* Sequence, const int32& Frames, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
			{
				CS_IS_PENDING_KILL(Sequence)

				return TrackLibrary::SetSafeEaseInDuration(Context, Sequence->GetMovieScene(), Frames, Log);
			}

			bool FLibrary::SetSafeEaseInFramesByCurrentFps(const FString& Context, ALevelSequenceActor* Sequence, const int32& Frames, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
			{
				typedef NCsLevelSequence::NActor::FLibrary LevelSequenceActorLibrary;

				FFrameRate FrameRate;

				if (!LevelSequenceActorLibrary::GetSafeFrameRate(Context, Sequence, FrameRate, Log))
					return false;

				CS_IS_INT_GREATER_THAN(Frames, 1)

				typedef NCsLevelSequence::NProject::NSettings::FLibrary SettingsLibrary;

				const float Time = (float)Frames * FrameRate.AsInterval();

				const int32 Duration = FMath::CeilToInt32(Time * SettingsLibrary::GetDefaultTickResolution());

				return SetSafeEaseInDuration(Context, Sequence->GetSequence(), Duration, Log);
			}

			bool FLibrary::SetSafeEaseInSeconds(const FString& Context, ALevelSequenceActor* Sequence, const float& Seconds, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
			{
				CS_IS_FLOAT_GREATER_THAN(Seconds, 0.0f)

				typedef NCsLevelSequence::NProject::NSettings::FLibrary SettingsLibrary;

				const int32 Duration = FMath::CeilToInt32(Seconds * SettingsLibrary::GetDefaultTickResolution());

				return SetSafeEaseInDuration(Context, Sequence->GetSequence(), Duration, Log);
			}

			#undef TrackLibrary
		}
	}
}