// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Coroutine/CsRoutineHandle.h"
#include "Material/CsTypes_Material_Anim.h"

#include "CsScriptLibrary_MID.generated.h"

class UMaterialInstanceDynamic;

UCLASS()
class CSCORE_API UCsScriptLibrary_MID : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Scalar
#pragma region
public:

	/**
	* Set the Scalar Parameter Value with name: ParamName with value Value on MID.
	*
	* @param MID		Material Instance Dynamic.
	* @param ParamName	Name of the Scalar Parameter Value to set.
	* @param Value		The value to set.
	* return			Whether the parameter was successful set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,ParamName,Value"))
	static bool SetScalarParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value);

	/**
	* Set the Scalar Parameter Value with name: ParamName with value: Value on all MIDs.
	*
	* @param MIDs		Array of Material Instance Dynamic.
	* @param ParamName	Name of the Scalar Parameter Value to set.
	* @param Value		The value to set.
	* return			Whether the parameter was successful set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,ParamName,Value"))
	static bool SetArrayScalarParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value);

#pragma endregion Scalar

// Vector
#pragma region
public:

	/**
	* Set the Vector Parameter Value with name: ParamName with value Value on MID.
	*
	* @param MID		Material Instance Dynamic.
	* @param ParamName	Name of the Scalar Parameter Value to set.
	* @param Value		The value to set.
	* return			Whether the parameter was successful set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Material", meta = (AutoCreateRefTerm = "Context,ParamName,Value"))
	static bool SetVectorParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value);

#pragma endregion Vector

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