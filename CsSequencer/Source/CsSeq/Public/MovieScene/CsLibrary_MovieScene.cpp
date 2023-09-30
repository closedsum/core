// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "MovieScene/CsLibrary_MovieScene.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Movie Scene
#include "MovieScene.h"
// Tracks
#include "Tracks/MovieSceneCameraCutTrack.h"

namespace NCsMovieScene
{
	namespace NTrack
	{
		namespace NCameraCut
		{
			UMovieSceneCameraCutTrack* FLibrary::GetChecked(const FString& Context, UMovieScene* Scene)
			{
				CS_IS_PENDING_KILL_CHECKED(Scene)

				UMovieSceneTrack* Track = Scene->GetCameraCutTrack();

				CS_IS_PENDING_KILL_CHECKED(Track)

				return CS_CAST_CHECKED(Track, UMovieSceneTrack, UMovieSceneCameraCutTrack);
			}

			UMovieSceneCameraCutTrack* FLibrary::GetSafe(const FString& Context, UMovieScene* Scene, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
			{
				CS_IS_PENDING_KILL_RET_NULL(Scene)

				UMovieSceneTrack* Track = Scene->GetCameraCutTrack();

				CS_IS_PENDING_KILL_RET_NULL(Track)

				return CS_CAST(Track, UMovieSceneTrack, UMovieSceneCameraCutTrack);
			}

			void FLibrary::EnableChecked(const FString& Context, UMovieScene* Scene)
			{
				GetChecked(Context, Scene)->SetEvalDisabled(false);
			}

			bool FLibrary::EnableSafe(const FString& Context, UMovieScene* Scene, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
			{
				if (UMovieSceneCameraCutTrack* Track = GetSafe(Context, Scene, Log))
				{
					Track->SetEvalDisabled(false);
					return true;
				}
				return false;
			}

			void FLibrary::MuteChecked(const FString& Context, UMovieScene* Scene)
			{
				GetChecked(Context, Scene)->SetEvalDisabled(true);
			}

			bool FLibrary::MuteSafe(const FString& Context, UMovieScene* Scene, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
			{
				if (UMovieSceneCameraCutTrack* Track = GetSafe(Context, Scene, Log))
				{
					Track->SetEvalDisabled(true);
					return true;
				}
				return false;
			}

			void FLibrary::SetEaseInDurationChecked(const FString& Context, UMovieScene* Scene, const int32& Frames)
			{
				UMovieSceneCameraCutTrack* Track = GetChecked(Context, Scene);
				
				checkf(Track->bCanBlend, TEXT("%s: Camera Cut Track for Scene: %s is NOT set to Blend (Can Blend == FALSE / Not Checked)."), *Context, *(Scene->GetName()));
				checkf(Track->GetAllSections().Num()> CS_EMPTY, TEXT("%s: Camera Cut Track for Scene: %s has NO Sections."), *Context, *(Scene->GetName()));

				UMovieSceneSection* Section = Track->GetAllSections()[CS_FIRST];

				CS_IS_INT_GREATER_THAN_CHECKED(Frames, 1)
				CS_IS_INT_LESS_THAN_CHECKED(Frames, Section->GetRange().GetUpperBoundValue().Value)

				Section->Easing.bManualEaseIn = true;
				Section->Easing.ManualEaseInDuration = Frames;
			}

			bool FLibrary::SetSafeEaseInDuration(const FString& Context, UMovieScene* Scene, const int32& Frames, void(*Log)(const FString&) /*=&NCsSequencer::FLog::Warning*/)
			{
				if (UMovieSceneCameraCutTrack* Track = GetSafe(Context, Scene, Log))
				{
					if (!Track->bCanBlend)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Camera Cut Track for Scene: %s is NOT set to Blend (Can Blend == FALSE / Not Checked)."), *Context, *(Scene->GetName())));
						return false;
					}

					if (Track->GetAllSections().Num() == CS_EMPTY)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Camera Cut Track for Scene: %s has NO Sections."), *Context, *(Scene->GetName())));
						return false;
					}

					UMovieSceneSection* Section = Track->GetAllSections()[CS_FIRST];

					CS_IS_INT_GREATER_THAN(Frames, 1)
					CS_IS_INT_LESS_THAN(Frames, Section->GetRange().GetUpperBoundValue().Value)

					Section->Easing.bManualEaseIn		   = true;
					Section->Easing.ManualEaseInDuration = Frames;
					return true;
				}
				return false;
			}
		}
	}
}