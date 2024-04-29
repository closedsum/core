// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Coroutine/CsRoutineHandle.h"
#include "Material/CsTypes_Material_Anim.h"

#include "CsScriptLibrary_MID_Anim.generated.h"

class UMaterialInstanceDynamic;

UCLASS()
class CSCORE_API UCsScriptLibrary_MID_Anim : public UObject
{ 
	GENERATED_UCLASS_BODY() 

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