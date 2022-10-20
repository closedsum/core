// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Object.generated.h"


UCLASS()
class CSCORE_API UCsScriptLibrary_Object : public UObject
{
	GENERATED_UCLASS_BODY()

// Load
#pragma region
public:

	/**
	* Load a Object at the given Path.
	*
	* @param Context	The calling context.
	* @param Path		SoftObjectPath to the Object to load.
	* return			Object
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Object", meta = (AutoCreateRefTerm = "Context,Path"))
	static UObject* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a Object at the given Path.
	*
	* @param Context	The calling context.
	* @param Path		FString path to the Object to load.
	* return			Object
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimInstance", meta = (AutoCreateRefTerm = "Context,Path"))
	static UObject* LoadByStringPath(const FString& Object, const FString& Path);

#pragma endregion Load

public:

	/**
	*
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Object", meta = (AutoCreateRefTerm = "Context"))
	static UObject* ConstructObject(const FString& Context, UObject* Outer, UClass* Class);

	/**
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Object", meta = (AutoCreateRefTerm = "Context"))
	static bool Object_MarkPendingKill(const FString& Context, UObject* Object);
};