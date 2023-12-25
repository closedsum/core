// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsSeqLog.h"

class UObject;
class ALevelSequenceActor;
class ULevelSequence;
class ULevelSequencePlayer;
class UMovieSceneCameraCutTrack;

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
					extern CSSEQ_API const FString GetSafeByTag;
				}
			}
		}

		/**
		* Library of functions related to a LevelSequenceActor
		*/
		struct CSSEQ_API FLibrary final
		{
		// Get
		#pragma region
		public:

			/**
			* Get an LevelSequenceActor with the given Tag (checks ALevelSequenceActor->Tags)
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* return
			*/
			static ALevelSequenceActor* GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag);

			/**
			* Safely get an LevelSequenceActor with the given Tag (checks ALevelSequenceActor->Tags)
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* @param Log
			* return				LevelSequenceActor
			*/
			static ALevelSequenceActor* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

			/**
			* Safely get an LevelSequenceActor with the given Tag (checks ALevelSequenceActor->Tags)
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* return				LevelSequenceActor
			*/
			FORCEINLINE static ALevelSequenceActor* GetSafeByTag(const UObject* WorldContext, const FName& Tag)
			{
				using namespace NCsLevelSequence::NActor::NLibrary::NCached;

				const FString& Context = Str::GetSafeByTag;

				return GetSafeByTag(Context, WorldContext, Tag, nullptr);
			}

			/**
			* Get an LevelSequenceActor with the given Tags (checks ALevelSequenceActor->Tags).
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tags
			* returns				LevelSequenceActor
			*/
			static ALevelSequenceActor* GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags);

			/**
			* Safely get an LevelSequenceActor with the given Tags (checks ALevelSequenceActor->Tags).
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tags
			* @param Log			(optional)
			* return				LevelSequenceActor
			*/
			static ALevelSequenceActor* GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

			/**
			* Get an LevelSequenceActor with the given Name.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* return
			*/
			static ALevelSequenceActor* GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name);

			/**
			* Get an LevelSequenceActor with the given Name.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* @param Log
			* return
			*/
			static ALevelSequenceActor* GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

			/**
			* Get an LevelSequenceActor with the given Name.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* return
			*/
			static ALevelSequenceActor* GetSafeByName(const UObject* WorldContext, const FName& Name);

			/**
			* Get an LevelSequenceActor with the given Label.
			* NOTE: - More than 1 Actor can have the SAME Label in Editor. In this case, the FIRST
			*		  LevelSequenceActor found in the search will be returned.
			*		- Only valid in Editor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Level
			* return
			*/
			static ALevelSequenceActor* GetByLabelChecked(const FString& Context, const UObject* WorldContext, const FString& Label);

			/**
			* Get an LevelSequenceActor with the given Label.
			* NOTE: - More than 1 LevelSequenceActor can have the SAME Label in Editor. In this case, the FIRST
			*		  Actor found in the search will be returned.
			*		- Only valid in Editor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* @param Log
			* return
			*/
			static ALevelSequenceActor* GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

			/**
			* Get an LevelSequenceActor with the given Label.
			* NOTE: - More than 1 LevelSequenceActor can have the SAME Label in Editor. In this case, the FIRST
			*		  Actor found in the search will be returned.
			*		- Only valid in Editor.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* return
			*/
			static ALevelSequenceActor* GetSafeByLabel(const UObject* WorldContext, const FString& Label);

		#pragma endregion Get

		// Player
		#pragma region
		public:

			static ULevelSequencePlayer* GetPlayerChecked(const FString& Context, ALevelSequenceActor* Sequence);

			static ULevelSequencePlayer* GetSafePlayer(const FString& Context, ALevelSequenceActor* Sequence, bool& OutSuccess, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);
			FORCEINLINE static ULevelSequencePlayer* GetSafePlayer(const FString& Context, ALevelSequenceActor* Sequence, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning)
			{
				bool OutSuccess = false;
				return GetSafePlayer(Context, Sequence, OutSuccess, Log);
			}

			static void PlayFromStartChecked(const FString& Context, ALevelSequenceActor* Sequence);

			static bool SafePlayFromStart(const FString& Context, ALevelSequenceActor* Sequence, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);
			FORCEINLINE static bool SafePlayFromStart(const FString& Context, ALevelSequenceActor* Sequence, bool& OutSuccess, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning)
			{
				OutSuccess = SafePlayFromStart(Context, Sequence, Log);
				return OutSuccess;
			}

			/**
			* Get the Frame Rate for the Player associated with Sequence
			*  Sequence->GetSequencePlayer()->GetFrameRate().
			* 
			* @param Context	The calling context.
			* @param Sequence
			* return			Frame Rate.
			*/
			static FFrameRate GetFrameRateChecked(const FString& Context, ALevelSequenceActor* Sequence);

			/**
			* Safely get the Frame Rate for the Player associated with Sequence
			*  Sequence->GetSequencePlayer()->GetFrameRate().
			*
			* @param Context		The calling context.
			* @param Sequence
			* @param OutFrameRate
			* @param Log			(optional)
			* return				Frame Rate.
			*/
			static bool GetSafeFrameRate(const FString& Context, ALevelSequenceActor* Sequence, FFrameRate& OutFrameRate, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

			/**
			* Set the current time of the player by evaluating from the current time to frame 0, as if the sequence is playing.
			* Triggers events that lie within the evaluated range. Does not alter the persistent playback status of the player (IsPlaying).
			*
			* @param Context		The calling context.
			* @param Sequence
			*/
			static void SetPlaybackPositionFrameZeroChecked(const FString& Context, ALevelSequenceActor* Sequence);

			/**
			* Set the current time of the player by evaluating from the current time to frame 0, as if the sequence is playing.
			* Triggers events that lie within the evaluated range. Does not alter the persistent playback status of the player (IsPlaying).
			*
			* @param Context		The calling context.
			* @param Sequence
			* @param Log			(optional)
			* return
			*/
			static bool SetSafePlaybackPositionFrameZero(const FString& Context, ALevelSequenceActor* Sequence, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

		#pragma endregion Player
		};
	}

	namespace NPlayer
	{
		struct CSSEQ_API FLibrary final
		{
		// Get
		#pragma region
		public:

			/**
			* Get an LevelSequencePlayer with the given Tag (checks ALevelSequenceActor->Tags)
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* return				LevelSequencePlayer
			*/
			static ULevelSequencePlayer* GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag);

			/**
			* Safely get an LevelSequencePlayer with the given Tag (checks ALevelSequenceActor->Tags)
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* @param Log			(optional)
			* return				LevelSequencePlayer
			*/
			static ULevelSequencePlayer* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

			/**
			* Safely get an LevelSequencePlayer with the given Tag (checks ALevelSequenceActor->Tags)
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* return				LevelSequencePlayer
			*/
			FORCEINLINE static ULevelSequencePlayer* GetSafeByTag(const UObject* WorldContext, const FName& Tag)
			{
				using namespace NCsLevelSequence::NActor::NLibrary::NCached;

				const FString& Context = Str::GetSafeByTag;

				return GetSafeByTag(Context, WorldContext, Tag, nullptr);
			}

			/**
			* Get an LevelSequencePlayer with the given Tags (checks ALevelSequenceActor->Tags).
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tags
			* returns				LevelSequencePlayer
			*/
			static ULevelSequencePlayer* GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags);

			/**
			* Safely get an LevelSequencePlayer with the given Tags (checks ALevelSequenceActor->Tags).
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tags
			* @param Log			(optional)
			* return				LevelSequencePlayer
			*/
			static ULevelSequencePlayer* GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

			/**
			* Get an LevelSequencePlayer with the given Name.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* return				LevelSequencePlayer
			*/
			static ULevelSequencePlayer* GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name);

			/**
			* Get an LevelSequencePlayer with the given Name.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* @param Log			(optional)
			* return				LevelSequencePlayer
			*/
			static ULevelSequencePlayer* GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

			/**
			* Get an LevelSequencePlayer with the given Name.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* return				LevelSequencePlayer
			*/
			static ULevelSequencePlayer* GetSafeByName(const UObject* WorldContext, const FName& Name);

			/**
			* Get an LevelSequencePlayer with the given Label.
			* NOTE: - More than 1 Actor can have the SAME Label in Editor. In this case, the FIRST
			*		  LevelSequencePlayer found in the search will be returned.
			*		- Only valid in Editor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Level
			* return				LevelSequencePlayer
			*/
			static ULevelSequencePlayer* GetByLabelChecked(const FString& Context, const UObject* WorldContext, const FString& Label);

			/**
			* Get an LevelSequencePlayer with the given Label.
			* NOTE: - More than 1 LevelSequencePlayer can have the SAME Label in Editor. In this case, the FIRST
			*		  Actor found in the search will be returned.
			*		- Only valid in Editor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* @param Log			(optional)
			* return				LevelSequencePlayer
			*/
			static ULevelSequencePlayer* GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

			/**
			* Get an LevelSequencePlayer with the given Label.
			* NOTE: - More than 1 LevelSequencePlayer can have the SAME Label in Editor. In this case, the FIRST
			*		  Actor found in the search will be returned.
			*		- Only valid in Editor.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* return				LevelSequencePlayer
			*/
			static ULevelSequencePlayer* GetSafeByLabel(const UObject* WorldContext, const FString& Label);

		#pragma endregion Get

		// Play
		#pragma region
		public:

			static void PlayFromStartChecked(const FString& Context, ULevelSequencePlayer* Player);

			static bool SafePlayFromStart(const FString& Context, ULevelSequencePlayer* Player, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);
			FORCEINLINE static bool SafePlayFromStart(const FString& Context, ULevelSequencePlayer* Player, bool& OutSuccess, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning)
			{
				OutSuccess = SafePlayFromStart(Context, Player, Log);
				return OutSuccess;
			}

		#pragma endregion Play
		};
	}

	namespace NTrack
	{
		namespace NCameraCut
		{
			struct CSSEQ_API FLibrary final
			{
			public:

				static UMovieSceneCameraCutTrack* GetChecked(const FString& Context, ULevelSequence* Sequence);

				static UMovieSceneCameraCutTrack* GetSafe(const FString& Context, ULevelSequence* Sequence, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

				static void EnableChecked(const FString& Context, ULevelSequence* Sequence);

				static bool EnableSafe(const FString& Context, ULevelSequence* Sequence, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

				static void MuteChecked(const FString& Context, ULevelSequence* Sequence);

				static bool MuteSafe(const FString& Context, ULevelSequence* Sequence, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

				static bool SetSafeEaseInDuration(const FString& Context, ULevelSequence* Sequence, const int32& Frames, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

				static bool SetSafeEaseInFramesByCurrentFps(const FString& Context, ALevelSequenceActor* Sequence, const int32& Frames, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

				static bool SetSafeEaseInSeconds(const FString& Context, ALevelSequenceActor* Sequence, const float& Seconds, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);
			};
		}
	}
}                                                                                                                                                                                                                                                                                                                                            