// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_LevelSequence.generated.h"

class ALevelSequenceActor;
class UMovieSceneCameraCutTrack;

UCLASS()
class CSSEQ_API UCsScriptLibrary_LevelSequence : public UObject
{
	GENERATED_UCLASS_BODY()

public:

// Get
#pragma region
public:

	/**
	* Get an LevelSequenceActor with the given Tag (checks ALevelSequenceActor->Tags)
	* NOTE: Find the FIRST LevelSequenceActor the given Tag.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tag
	* return				LevelSequenceActor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequenceActor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Tag"))
	static ALevelSequenceActor* GetByTag(const FString& Context, UObject* WorldContextObject, const FName& Tag);

	/**
	* Get an LevelSequenceActor with the given Tags (checks ALevelSequenceActor->Tags)
	* NOTE: Find the FIRST LevelSequenceActor the given Tags.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tags
	* return				LevelSequenceActor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequenceActor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Tags"))
	static ALevelSequenceActor* GetByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags);

	/**
	* Get an LevelSequenceActor with the given Name.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				LevelSequenceActor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequenceActor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static ALevelSequenceActor* GetByName(const FString& Context, UObject* WorldContextObject, const FName& Name);

	/**
	* Get an LevelSequenceActor with the given Label.
	* NOTE: - More than 1 LevelSequenceActor can have the SAME Label in Editor. In this case, the FIRST
	*		  LevelSequenceActor found in the search will be returned.
	*		- Only valid in Editor.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				LevelSequenceActor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequenceActor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Label"))
	static ALevelSequenceActor* GetByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label);

#pragma endregion Get

// Player
#pragma region
public:

	/**
	* Set the current time of the player by evaluating from the current time to frame 0, as if the sequence is playing.
	* Triggers events that lie within the evaluated range. Does not alter the persistent playback status of the player (IsPlaying).
	*
	* @param Context		The calling context.
	* @param Sequence
	*/
	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequenceActor", meta = (AutoCreateRefTerm = "Context"))
	static bool SetPlaybackPositionFrameZero(const FString& Context, ALevelSequenceActor* Sequence);

#pragma endregion Player

// Tracks
#pragma region
public:

	// Camera
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequence|Track|Camera Cut", meta = (AutoCreateRefTerm = "Context"))
	static UMovieSceneCameraCutTrack* Track_GetCameraCut(const FString& Context, ULevelSequence* Sequence);

	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequence|Track|Camera Cut", meta = (AutoCreateRefTerm = "Context"))
	static bool Track_CameraCut_Enable(const FString& Context, ULevelSequence* Sequence);

	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequence|Track|Camera Cut", meta = (AutoCreateRefTerm = "Context"))
	static bool Track_CameraCut_Mute(const FString& Context, ULevelSequence* Sequence);

	/**
	* Set Camera Track's Section's Ease In Duration in Seconds
	* 
	* @parma Context	The calling context.
	* @param Sequence
	* @param Seconds
	* return
	*/
	//UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequence|Track", meta = (AutoCreateRefTerm = "Context,Seconds"))
	//static bool Track_CameraCut_SetEaseIn(const FString& Context, ULevelSequence* Sequence, const float& Seconds);

	/**
	* Set Camera Track's Section's Ease In Duration in Frames
	*  Frames represents a value the same as the Tick Resolution (i.e. the Default Tick Resolution is 24000 fps).
	* 
	* @parma Context	The calling context.
	* @param Sequence
	* @param Frames
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequence|Track|Camera Cut", meta = (AutoCreateRefTerm = "Context,Frames"))
	static bool Track_CameraCut_SetEaseInDuration(const FString& Context, ULevelSequence* Sequence, const int32& Frames);

	/**
	* Set Camera Track's Section's Ease In Frames by the current Fps of the Sequence.
	*  Frames represents a value with respect to the current Fps (i.e. 30 fps -> 15 Frames = 0.5 sec, etc).
	* 
	* @parma Context	The calling context.
	* @param Sequence
	* @param Frames
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequence|Track|Camera Cut", meta = (AutoCreateRefTerm = "Context,Frames"))
	static bool Track_CameraCut_SetEaseInFramesByCurrentFps(const FString& Context, ALevelSequenceActor* Sequence, const int32& Frames);

	/**
	* Set Camera Track's Section's Ease In Seconds.
	* 
	* @parma Context	The calling context.
	* @param Sequence
	* @param Seconds
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequence|Track|Camera Cut", meta = (AutoCreateRefTerm = "Context,Seconds"))
	static bool Track_CameraCut_SetEaseSeconds(const FString& Context, ALevelSequenceActor* Sequence, const float& Seconds);

#pragma endregion Camera

#pragma endregion Tracks
};