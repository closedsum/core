// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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

// Unload
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (DisplayName = "Unload (FCsMaterialInterface)", CompactNodeTitle = "Unload"))
	static void FCsMaterialInterface_Unload(UPARAM(ref) FCsMaterialInterface& Material)
	{
		Material.Unload();
	}

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (DisplayName = "Unload (FCsMaterialInstance)", CompactNodeTitle = "Unload"))
	static void FCsMaterialInstance_Unload(UPARAM(ref) FCsMaterialInstance& Material)
	{
		Material.Unload();
	}

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (DisplayName = "Unload (FCsMaterialInstanceConstant)", CompactNodeTitle = "Unload"))
	static void FCsMaterialInstanceConstant_Unload(UPARAM(ref) FCsMaterialInstanceConstant& Material)
	{
		Material.Unload();
	}

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (DisplayName = "Unload (FCsTArrayMaterialInterface)", CompactNodeTitle = "Unload"))
	static void FCsTArrayMaterialInterface_Unload(UPARAM(ref) FCsTArrayMaterialInterface& Materials)
	{
		Materials.Unload();
	}

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (DisplayName = "Unload (FCsTArrayMaterialInstanceConstant)", CompactNodeTitle = "Unload"))
	static void FCsTArrayMaterialInstanceConstant_Unload(UPARAM(ref) FCsTArrayMaterialInstanceConstant& Materials)
	{
		Materials.Unload();
	}

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (DisplayName = "Unload (FCsFpsTArrayMaterialInstanceConstant)", CompactNodeTitle = "Unload"))
	static void FCsFpsTArrayMaterialInstanceConstant_Unload(UPARAM(ref) FCsFpsTArrayMaterialInstanceConstant& Materials)
	{
		Materials.Unload();
	}

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (DisplayName = "Unload (FCsMaterialInterface_WithParameters)", CompactNodeTitle = "Unload"))
	static void FCsMaterialInterface_WithParameters_Unload(UPARAM(ref) FCsMaterialInterface_WithParameters& Material)
	{
		Material.Unload();
	}

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (DisplayName = "Unload (FCsMaterialInterface_WithRangeParameters)", CompactNodeTitle = "Unload"))
	static void FCsMaterialInterface_WithRangeParameters_Unload(UPARAM(ref) FCsMaterialInterface_WithRangeParameters& Material)
	{
		Material.Unload();
	}

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (DisplayName = "Unload (FCsMaterialParameterCollection)", CompactNodeTitle = "Unload"))
	static void FCsMaterialParameterCollection_Unload(UPARAM(ref) FCsMaterialParameterCollection& Collection)
	{
		Collection.Unload();
	}

#pragma endregion Unload

// Get
#pragma region
public:

	/**
	* Get the Material Interface value at the give Path for Object.
	* 
	* @param Context	The calling context.
	* @param Object
	* @param Path		Full variable path to the Material Interface value on Object.
	* @param OutSuccess	(out)
	* return			Material Interface
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,Path"))
	static UMaterialInterface* GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess);

	/**
	* Get the SoftObjectPtr of type: Material Interface value at the give Path for Object.
	* 
	* @param Context	The calling context.
	* @param Object
	* @param Path		Full variable path to the Material Interface value on Object.
	* @param OutPath	
	* @param OutSuccess	(out)
	* return			
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,Path"))
	static bool GetSoftObjectAsStringByPath(const FString& Context, UObject* Object, const FString& Path, FString& OutPath, bool& OutSuccess);

	/**
	* Get an Array of Material Interface values at the give Path for Object.
	* 
	* @param Context	The calling context.
	* @param Object
	* @param Path		Full variable path to the Material Interface value on Object.
	* @param OutArray	(out)
	* @param OutSuccess	(out)
	* return			
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,Path"))
	static bool GetArrayByPath(const FString& Context, UObject* Object, const FString& Path, TArray<UMaterialInterface*>& OutArray, bool& OutSuccess);

	/**
	* Get an Array of SoftObjectPtr of type: Material Interface values at the give Path for Object as an Array of Strings.
	* 
	* @param Context	The calling context.
	* @param Object
	* @param Path		Full variable path to the Material Interface value on Object.
	* @param OutArray	(out)
	* @param OutSuccess	(out)
	* return			
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,Path"))
	static bool GetSoftObjectArrayAsStringByPath(const FString& Context, UObject* Object, const FString& Path, TArray<FString>& OutArray, bool& OutSuccess);

#pragma endregion Get

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