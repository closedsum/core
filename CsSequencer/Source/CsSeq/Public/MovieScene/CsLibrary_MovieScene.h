// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsSeqLog.h"

class UMovieScene;

class UMovieSceneCameraCutTrack;

namespace NCsMovieScene
{
	namespace NTrack
	{
		namespace NCameraCut
		{
			struct CSSEQ_API FLibrary final
			{
			public:

				static UMovieSceneCameraCutTrack* GetChecked(const FString& Context, UMovieScene* Scene);

				static UMovieSceneCameraCutTrack* GetSafe(const FString& Context, UMovieScene* Scene, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

				static void EnableChecked(const FString& Context, UMovieScene* Scene);

				static bool EnableSafe(const FString& Context, UMovieScene* Scene, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

				static void MuteChecked(const FString& Context, UMovieScene* Scene);

				static bool MuteSafe(const FString& Context, UMovieScene* Scene, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);

				static void SetEaseInDurationChecked(const FString& Context, UMovieScene* Scene, const int32& Frames);

				static bool SetSafeEaseInDuration(const FString& Context, UMovieScene* Scene, const int32& Frames, void(*Log)(const FString&) = &NCsSequencer::FLog::Warning);
			};
		}
	}
}