// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_MPC.generated.h"

class UMaterialParameterCollection;

UCLASS()
class CSCORE_API UCsScriptLibrary_MPC : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Scalar
#pragma region
public:

	/**
	* Set the Scalar Parameter Value with name: ParamName with value Value on the Collection (Material Parameter Collection).
	*  NOTE: Editor ONLY
	* 
	* @param Collection		Material Parameter Collection.
	* @param ParamName		Name of the Scalar Parameter Value to set.
	* @param Value			The value to set.
	* return				Whether the parameter was successful set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,ParamName,Value"))
	static bool SetScalarParameterValue(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const float& Value);

	/**
	* Set the Scalar Parameter Value with name: ParamName with value Value on the Collection (Material Parameter Collection).
	*  NOTE: Editor ONLY
	* 
	* @param Collection		Material Parameter Collection.
	* @param ParamName		Name of the Scalar Parameter Value to set.
	* @param Value			The value to set.
	* return				Whether the parameter was successful set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,ParamName,Value"))
	static bool SetScalarParameterValue_UpdateMaterials(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const float& Value);

#pragma endregion Scalar

// Vector
#pragma region
public:

	/**
	* Set the Vector Parameter Value with name: ParamName with value Value on the Collection (Material Parameter Collection).
	*  NOTE: Editor ONLY
	* 
	* @param Collection		Material Parameter Collection.
	* @param ParamName		Name of the Scalar Parameter Value to set.
	* @param Value			The value to set.
	* return				Whether the parameter was successful set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,ParamName,Value"))
	static bool SetVectorParameterValue(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const FLinearColor& Value);

	/**
	* Set the Vector Parameter Value with name: ParamName with value Value on the Collection (Material Parameter Collection).
	*  NOTE: Editor ONLY
	* 
	* @param Collection		Material Parameter Collection.
	* @param ParamName		Name of the Scalar Parameter Value to set.
	* @param Value			The value to set.
	* return				Whether the parameter was successful set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,ParamName,Value"))
	static bool SetVectorParameterValue_UpdateMaterials(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const FLinearColor& Value);

#pragma endregion Vector

public:

	/**
	* NOTE: Editor ONLY
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context"))
	static bool UpdateMaterial(const FString& Context, UMaterialParameterCollection* Collection, UMaterial* Material);

	/**
	* NOTE: Editor ONLY
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context"))
	static bool UpdateMaterials(const FString& Context, UMaterialParameterCollection* Collection, TArray<UMaterial*>& Materials);
};