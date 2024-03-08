// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_LevelSequencePlayer.generated.h"

class ULevelSequencePlayer;

UCLASS()
class CSSEQ_API UCsScriptLibrary_LevelSequencePlayer : public UObject
{
	GENERATED_UCLASS_BODY()

public:

// Get
#pragma region
public:

	/**
	* Get an LevelSequencePlayer with the given Tag (checks ALevelSequenceActor->Tags)
	* NOTE: Find the FIRST LevelSequencePlayer the given Tag.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tag
	* return				LevelSequencePlayer
	*/
	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequencePlayer", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Tag"))
	static ULevelSequencePlayer* GetByTag(const FString& Context, UObject* WorldContextObject, const FName& Tag);

	/**
	* Get an LevelSequencePlayer with the given Tags (checks ALevelSequenceActor->Tags)
	* NOTE: Find the FIRST LevelSequencePlayer the given Tags.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tags
	* return				LevelSequencePlayer
	*/
	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequencePlayer", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Tags"))
	static ULevelSequencePlayer* GetByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags);

	/**
	* Get an LevelSequencePlayer with the given Name.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				LevelSequencePlayer
	*/
	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequencePlayer", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static ULevelSequencePlayer* GetByName(const FString& Context, UObject* WorldContextObject, const FName& Name);

	/**
	* Get an LevelSequencePlayer with the given Label.
	* NOTE: - More than 1 LevelSequencePlayer can have the SAME Label in Editor. In this case, the FIRST
	*		  LevelSequencePlayer found in the search will be returned.
	*		- Only valid in Editor.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				LevelSequencePlayer
	*/
	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequencePlayer", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Label"))
	static ULevelSequencePlayer* GetByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label);

#pragma endregion Get

// Play
#pragma region
public:

	/**
	* Set the current time of the player by evaluating from the current time to frame 0, as if the sequence is playing and then Play.
	* 
	* @param Context		The calling context.
	* @param Player
	*/
	UFUNCTION(BlueprintCallable, Category = "CsSeq|Library|LevelSequencePlayer", meta = (AutoCreateRefTerm = "Context"))
	static bool PlayFromStart(const FString& Context, ULevelSequencePlayer* Player);

#pragma endregion Player
};