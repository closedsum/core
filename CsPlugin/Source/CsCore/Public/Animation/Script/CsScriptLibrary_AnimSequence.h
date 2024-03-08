// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Animation/CsTypes_Anim.h"

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

// Unload
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimSequence", meta = (DisplayName = "Unload (FCsAnimSequence)", CompactNodeTitle = "Unload"))
	static void FCsAnimSequence_Unload(UPARAM(ref) FCsAnimSequence& Anim)
	{
		Anim.Unload();
	}

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimSequence", meta = (DisplayName = "Unload (FCsAnimSequenceInfo)", CompactNodeTitle = "Unload"))
	static void FCsAnimSequenceInfo_Unload(UPARAM(ref) FCsAnimSequenceInfo& Anim)
	{
		Anim.Unload();
	}

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimSequence", meta = (DisplayName = "Unload (TArray<FCsAnimSequence>)", CompactNodeTitle = "Unload"))
	static void TArray_FCsAnimSequence_Unload(UPARAM(ref) TArray<FCsAnimSequence>& Anims)
	{
		for (FCsAnimSequence& Anim : Anims)
		{
			Anim.Unload();
		}
	}

#pragma endregion Unload

// Get
#pragma region
public:

	/**
	* Get the AnimSequence value at the give Path for Object.
	* 
	* @param Context	The calling context.
	* @param Object
	* @param Path		Full variable path to the AnimSequence value on Object.
	* @param OutSuccess	(out)
	* return			AnimSequence
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|AnimSequence", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimSequence* GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess);

#pragma endregion Get

// Property
#pragma region
public:

	/**
	* Set the UAnimSequence value for the Property with name: PropertyName from Object.
	*
	* @param Context		The calling context.
	* @param Object
	* @param PropertyName
	* @param Anim
	* return				Whether Value was successfully set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimSequence", meta = (AutoCreateRefTerm = "Context,PropertyName"))
	static bool SetProperty(const FString& Context, UObject* Object, const FName& PropertyName, UAnimSequence* Anim);

#pragma endregion Property
};