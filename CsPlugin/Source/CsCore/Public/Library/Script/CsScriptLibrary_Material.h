// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Coroutine/CsRoutineHandle.h"
#include "Material/CsTypes_Material_Anim.h"
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
	* @parma Path		FString path to the Material Interface to load.
	* return			Material Interface
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,Path"))
	static UMaterialInterface* LoadByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load

// Set
#pragma region
public:

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

// Anim
#pragma region
public:

	/**
	* Animate any number of parameters on a MaterialInstanceDynamic with the given Params.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Params				Information describing how to animate any number of parameters on a MaterialInstanceDynamic.
	* return					Handle to the movement coroutine.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Params"))
	static FCsRoutineHandle PlayAnim(const FString& Context, const UObject* WorldContextObject, const FCsMaterialAnim_Params& Params);

#pragma endregion Anim
};