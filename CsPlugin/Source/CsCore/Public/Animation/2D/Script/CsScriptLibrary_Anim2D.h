// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Animation/2D/CsTypes_Library_Anim2D.h"

#include "CsScriptLibrary_Anim2D.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Anim2D : public UObject
{
	GENERATED_UCLASS_BODY()

public:

// Texture
#pragma region
public:

	/**
	* Play a Texture 2D animation with the given Params.
	*
	* @param Context	The calling context.
	* @param Params		Information describing how to animate the material flipbook.
	* return			Handle to the anim coroutine.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Params"))
	static FCsRoutineHandle PlayTextureFlipbook(const FString& Context, const FCsAnim2DTextureFlipbook_Params& Params);

#pragma endregion Texture

// Material
#pragma region
public:

	/**
	* Play a Material 2D animation with the given Params.
	*
	* @param Context	The calling context.
	* @param Params		Information describing how to animate the material flipbook.
	* return			Handle to the anim coroutine.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Params"))
	static FCsRoutineHandle PlayMaterialFlipbook(const FString& Context, const FCsAnim2DMaterialFlipbook_Params& Params);

#pragma endregion Material
};