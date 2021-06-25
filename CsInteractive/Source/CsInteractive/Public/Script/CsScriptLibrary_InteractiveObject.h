// Copyright 2019, RCT Studios and The Rogue Initiative. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Params
#include "Select/CsInteractiveObject_Select_Params.h"
#include "Hover/CsInteractiveObject_Hover_Params.h"

#include "CsScriptLibrary_InteractiveObject.generated.h"

class ICsInteractiveObject;

UCLASS()
class CSINTERACTIVE_API UCsScriptLibrary_InteractiveObject : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Library|Interactive|Object", meta = (AutoCreateRefTerm = "Context,Params"))
	static bool Select(const FString& Context, UObject* Target, const FCsInteractiveObject_Select_Params& Params);

	UFUNCTION(BlueprintCallable, Category = "Library|Interactive|Object", meta = (AutoCreateRefTerm = "Context,Params"))
	static bool Deselect(const FString& Context, UObject* Target, const FCsInteractiveObject_Deselect_Params& Params);

	UFUNCTION(BlueprintCallable, Category = "Library|Interactive|Object", meta = (AutoCreateRefTerm = "Context,Params"))
	static bool Hover(const FString& Context, UObject* Target, const FCsInteractiveObject_Hover_Params& Params);

	UFUNCTION(BlueprintCallable, Category = "Library|Interactive|Object", meta = (AutoCreateRefTerm = "Context,Params"))
	static bool UnHover(const FString& Context, UObject* Target, const FCsInteractiveObject_UnHover_Params& Params);
};