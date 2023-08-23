// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Object", meta = (AutoCreateRefTerm = "Context,Path"))
	static UObject* LoadByStringPath(const FString& Object, const FString& Path);

#pragma endregion Load

public:

	/**
	*
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Object", meta = (AutoCreateRefTerm = "Context"))
	static UObject* ConstructObject(const FString& Context, UObject* Outer, UClass* Class);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Object", meta = (AutoCreateRefTerm = "Context"))
	static UObject* GetDefaultObject(const FString& Context, UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Object", meta = (AutoCreateRefTerm = "Context"))
	static int32 Object_GetUniqueID(const FString& Context, UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Object", meta = (AutoCreateRefTerm = "Context"))
	static int32 DOb_GetUniqueID(const FString& Context, UObject* Object);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Object")
	static bool IsNull(UObject* Object)
	{
		return Object == nullptr;
	}

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Object")
	static bool IsNullOrPendingKill(UObject* Object)
	{
		return !IsValid(Object);
	}

	/**
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Object", meta = (AutoCreateRefTerm = "Context"))
	static bool Object_MarkPendingKill(const FString& Context, UObject* Object);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Object")
	static bool EqualEqual(UObject* A, UObject* B)
	{
		return A == B;
	}
};