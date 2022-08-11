// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Material/CsTypes_Material.h"

#include "CsScriptLibrary_Material.generated.h"

class UMaterialInterface;

UCLASS()
class CSCORE_API UCsScriptLibrary_Material : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Load
#pragma region
public:

	/**
	* Load a Material Interface at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		SoftObjectPath to the Material Interface to load.
	* return			Material Interface
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,Path"))
	static UMaterialInterface* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a Material Interface at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the Material Interface to load.
	* return			Material Interface
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,Path"))
	static UMaterialInterface* LoadByStringPath(const FString& Context, const FString& Path);

	/**
	* Load Material Interfaces for the given Paths.
	*
	* @param Context		The calling context.
	* @param Paths			FString paths to the Material Interfaces to load.
	* @param OutMaterials	(out)
	* return				Whether the Material Interfaces were successfully loaded for the given Paths.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context"))
	static bool LoadByStringPaths(const FString& Context, const TArray<FString>& Paths, TArray<UMaterialInterface*>& OutMaterials);

#pragma endregion Load

// Set
#pragma region
public:

	/**
	* Set the Material at ALL Indices on Component
	*
	* @param Context	The calling context
	* @param Component
	* @param Material
	* return			Whether the Material was successful set at given Index or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,Index"))
	static bool SetAll(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material);

	/**
	* Set the Material at the given Index on Component
	*
	* @param Context	The calling context
	* @param Component
	* @param Material
	* @param Index
	* return			Whether the Material was successful set at given Index or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,Index"))
	static bool SetAt(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index);

	/**
	* Set the Materials on Component
	*
	* @param Context	The calling context
	* @param Component
	* @param Materials
	* return			Whether the Material was successful set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context"))
	static bool Set(const FString& Context, UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials);

	/**
	* Set the Materials on Component
	*
	* @param Context	The calling context
	* @param Materials
	* @param Component
	* return			Whether the Material was successful set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,Materials"))
	static bool SetFromStruct(const FString& Context, const FCsTArrayMaterialInterface& Materials, UPrimitiveComponent* Component);

	/**
	* Set the materials on Component from PropertyName on Object.
	*
	* @param Context		The calling context
	* @param Object
	* @param PropertyName
	* @param Component
	* return				Whether the Material was successful set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,PropertyName"))
	static bool SetFromObject(const FString& Context, UObject* Object, const FName& PropertyName, UPrimitiveComponent* Component);

#pragma endregion Set
};