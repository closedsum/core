// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "LevelSequence/Script/CsScriptLibrary_LevelSequence.h"

// CVars
#include "Script/CsCVars_Script.h"
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "LevelSequence/CsLibrary_LevelSequence.h"

// Cached
#pragma region

namespace NCsScriptLibraryLevelSequence
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequence, GetByTag);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequence, GetByTags);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequence, GetByName);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequence, GetByLabel);
			// Player
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequence, PlayFromStart);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequence, PlayFromStartChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequence, SetPlaybackPositionFrameZero);
			// Tracks
				// Camera
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequence, Track_GetCameraCut);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequence, Track_CameraCut_Enable);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequence, Track_CameraCut_Mute);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequence, Track_CameraCut_SetEaseInDuration);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequence, Track_CameraCut_SetEaseInFramesByCurrentFps);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_LevelSequence, Track_CameraCut_SetEaseSeconds);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_LevelSequence::UCsScriptLibrary_LevelSequence(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryLevelSequence::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryLevelSequence::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::##__FunctionName : Context
#define LogError &NCsSequencer::FLog::Error
#define LevelSequenceActorLibrary NCsLevelSequence::NActor::FLibrary

// Get
#pragma region

ALevelSequenceActor* UCsScriptLibrary_LevelSequence::GetByTag(const FString& Context, UObject* WorldContextObject, const FName& Tag)
{
	CONDITIONAL_SET_CTXT(GetByTag);

	return LevelSequenceActorLibrary::GetSafeByTag(Ctxt, WorldContextObject, Tag);
}

ALevelSequenceActor* UCsScriptLibrary_LevelSequence::GetByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags)
{
	CONDITIONAL_SET_CTXT(GetByTags);

	return LevelSequenceActorLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags);
}

ALevelSequenceActor* UCsScriptLibrary_LevelSequence::GetByName(const FString& Context, UObject* WorldContextObject, const FName& Name)
{
	CONDITIONAL_SET_CTXT(GetByName);

	return LevelSequenceActorLibrary::GetSafeByName(Ctxt, WorldContextObject, Name);
}

ALevelSequenceActor* UCsScriptLibrary_LevelSequence::GetByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label)
{
	CONDITIONAL_SET_CTXT(GetByLabel);

	return LevelSequenceActorLibrary::GetSafeByLabel(Ctxt, WorldContextObject, Label);
}

#pragma endregion Get

// Player
#pragma region

bool UCsScriptLibrary_LevelSequence::PlayFromStart(const FString& Context, ALevelSequenceActor* Sequence)
{
	CONDITIONAL_SET_CTXT(PlayFromStart);

	return LevelSequenceActorLibrary::SafePlayFromStart(Ctxt, Sequence);
}

void UCsScriptLibrary_LevelSequence::PlayFromStartChecked(const FString& Context, ALevelSequenceActor* Sequence, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(PlayFromStartChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(LevelSequenceActorLibrary::PlayFromStartChecked(Ctxt, Sequence), LevelSequenceActorLibrary::SafePlayFromStart(Ctxt, Sequence, OutSuccess, LogError));
}

bool UCsScriptLibrary_LevelSequence::SetPlaybackPositionFrameZero(const FString& Context, ALevelSequenceActor* Sequence)
{
	CONDITIONAL_SET_CTXT(SetPlaybackPositionFrameZero);

	return LevelSequenceActorLibrary::SetSafePlaybackPositionFrameZero(Ctxt, Sequence);
}

#pragma endregion Player

// Tracks
#pragma region

#define TrackLibrary NCsLevelSequence::NTrack::NCameraCut::FLibrary

	// Camera
#pragma region

UMovieSceneCameraCutTrack* UCsScriptLibrary_LevelSequence::Track_GetCameraCut(const FString& Context, ULevelSequence* Sequence)
{
	CONDITIONAL_SET_CTXT(Track_GetCameraCut);

	return TrackLibrary::GetSafe(Ctxt, Sequence);
}

bool UCsScriptLibrary_LevelSequence::Track_CameraCut_Enable(const FString& Context, ULevelSequence* Sequence)
{
	CONDITIONAL_SET_CTXT(Track_CameraCut_Enable);

	return TrackLibrary::EnableSafe(Ctxt, Sequence);
}

bool UCsScriptLibrary_LevelSequence::Track_CameraCut_Mute(const FString& Context, ULevelSequence* Sequence)
{
	CONDITIONAL_SET_CTXT(Track_CameraCut_Mute);

	return TrackLibrary::MuteSafe(Ctxt, Sequence);
}

bool UCsScriptLibrary_LevelSequence::Track_CameraCut_SetEaseInDuration(const FString& Context, ULevelSequence* Sequence, const int32& Frames)
{
	CONDITIONAL_SET_CTXT(Track_CameraCut_SetEaseInDuration);

	return TrackLibrary::SetSafeEaseInDuration(Ctxt, Sequence, Frames);
}

bool UCsScriptLibrary_LevelSequence::Track_CameraCut_SetEaseInFramesByCurrentFps(const FString& Context, ALevelSequenceActor* Sequence, const int32& Frames)
{
	CONDITIONAL_SET_CTXT(Track_CameraCut_SetEaseInFramesByCurrentFps);

	return TrackLibrary::SetSafeEaseInFramesByCurrentFps(Ctxt, Sequence, Frames);
}

bool UCsScriptLibrary_LevelSequence::Track_CameraCut_SetEaseSeconds(const FString& Context, ALevelSequenceActor* Sequence, const float& Seconds)
{
	CONDITIONAL_SET_CTXT(Track_CameraCut_SetEaseSeconds);

	return TrackLibrary::SetSafeEaseInSeconds(Ctxt, Sequence, Seconds);
}

#pragma endregion Camera

#undef TrackLibrary

#pragma endregion Tracks

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
#undef LevelSequenceActorLibrary