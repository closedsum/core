// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_Property.generated.h"

class UObject;

UCLASS()
class CSCORE_API UCsScriptLibrary_Property : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get the bool value by Path from Object.
	*
	* @param Context		The calling context.
	* @param Object
	* @param Path
	* @param OutSuccess		(out)
	* return				bool value by Path.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Property", meta = (AutoCreateRefTerm = "Context,Path"))
	static bool GetBoolByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess);

	/**
	* Get the int32 value for the Property with name: PropertyName from Object.
	*
	* @param Context		The calling context.
	* @param Object
	* @param PropertyName
	* @param OutSuccess		(out)
	* return				int32 value Property with name: PropertyName.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Property", meta = (AutoCreateRefTerm = "Context,PropertyName"))
	static int32 GetInt(const FString& Context, UObject* Object, const FName& PropertyName, bool& OutSuccess);

	/**
	* Get the int32 value by Path from Object.
	*
	* @param Context		The calling context.
	* @param Object
	* @param Path
	* @param OutSuccess		(out)
	* return				int32 value by Path.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Property", meta = (AutoCreateRefTerm = "Context,Path"))
	static int32 GetIntByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess);

	/**
	* Get the SoftObjectPtr as a String value by Path from Object.
	*
	* @param Context		The calling context.
	* @param Object
	* @param Path
	* @param OutSuccess		(out)
	* return				SoftObjectPtr as a String value by Path.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Property", meta = (AutoCreateRefTerm = "Context,Path"))
	static FString GetSoftObjectPtrAsStringByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess);

#pragma endregion Get

// Set
#pragma region
public:

	/**
	* Set the bool value for the Property with name: PropertyName from Object.
	*
	* @param Context		The calling context.
	* @param Object
	* @param PropertyName
	* @param Value
	* return				Whether Value was successfully set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Property", meta = (AutoCreateRefTerm = "Context,PropertyName"))
	static bool SetBool(const FString& Context, UObject* Object, const FName& PropertyName, bool Value);

	/**
	* Set the int32 value for the Property with name: PropertyName from Object.
	*
	* @param Context		The calling context.
	* @param Object
	* @param PropertyName
	* @param Value
	* return				Whether Value was successfully set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Property", meta = (AutoCreateRefTerm = "Context,PropertyName"))
	static bool SetInt(const FString& Context, UObject* Object, const FName& PropertyName, int32 Value);

	/**
	* Set the float value for the Property with name: PropertyName from Object.
	*
	* @param Context		The calling context.
	* @param Object
	* @param PropertyName
	* @param Value
	* return				Whether Value was successfully set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Property", meta = (AutoCreateRefTerm = "Context,PropertyName"))
	static bool SetFloat(const FString& Context, UObject* Object, const FName& PropertyName, float Value);

#pragma endregion Set
};