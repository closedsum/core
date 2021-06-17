// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_AnimSequence.generated.h"

class UAnimSequence;

UCLASS()
class CSCORE_API UCsScriptLibrary_AnimSequence : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Load
#pragma region
public:

	/**
	* Load a AnimSequence at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		SoftObjectPath to the AnimSequence to load.
	* return			AnimSequence
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimSequence", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimSequence* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a AnimSequence at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the AnimSequence to load.
	* return			AnimSequence
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimSequence", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimSequence* LoadByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load
};