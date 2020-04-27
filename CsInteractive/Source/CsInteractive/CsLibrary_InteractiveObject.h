// Copyright 2019, RCT Studios and The Rogue Initiative. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
#include "CsLibrary_InteractiveObject.generated.h"

class ICsInteractiveObject;

UCLASS()
class CSINTERACTIVE_API UCsLibrary_InteractiveObject : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Library|ICsInteractiveObject")
	static void Freeze(UPARAM(ref) TScriptInterface<ICsInteractiveObject>& Target);

	UFUNCTION(BlueprintCallable, Category = "Library|ICsInteractiveObject")
	static void UnFreeze(UPARAM(ref) TScriptInterface<ICsInteractiveObject>& Target);

	UFUNCTION(BlueprintCallable, Category = "Library|ICsInteractiveObject")
	static void Hold(UPARAM(ref) TScriptInterface<ICsInteractiveObject>& Target);

	UFUNCTION(BlueprintCallable, Category = "Library|ICsInteractiveObject")
	static void Release(UPARAM(ref) TScriptInterface<ICsInteractiveObject>& Target);

	UFUNCTION(BlueprintCallable, Category = "Library|ICsInteractiveObject")
	static void Touch(UPARAM(ref) TScriptInterface<ICsInteractiveObject>& Target);

	UFUNCTION(BlueprintCallable, Category = "Library|ICsInteractiveObject")
	static void Hover(UPARAM(ref) TScriptInterface<ICsInteractiveObject>& Target);

	UFUNCTION(BlueprintCallable, Category = "Library|ICsInteractiveObject")
	static void UnHover(UPARAM(ref) TScriptInterface<ICsInteractiveObject>& Target);

	UFUNCTION(BlueprintCallable, Category = "Library|ICsInteractiveObject")
	static void Collide(UPARAM(ref) TScriptInterface<ICsInteractiveObject>& Target);

	UFUNCTION(BlueprintCallable, Category = "Library|ICsInteractiveObject")
	static void UnCollide(UPARAM(ref) TScriptInterface<ICsInteractiveObject>& Target);

	UFUNCTION(BlueprintCallable, Category = "Library|ICsInteractiveObject")
	static void Remove(UPARAM(ref) TScriptInterface<ICsInteractiveObject>& Target);
};