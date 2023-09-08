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
};