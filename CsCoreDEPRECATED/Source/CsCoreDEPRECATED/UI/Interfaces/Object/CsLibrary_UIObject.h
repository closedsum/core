// Copyright 2019, RCT Studios and The Rogue Initiative. All Rights Reserved.
#pragma once

#include "Runtime/CoreUObject/Public/UObject/Object.h"
#include "CsLibrary_UIObject.generated.h"

class ICsUIObject;

UCLASS()
class CSCOREDEPRECATED_API UCsLibrary_UIObject : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Library|ICsUIObject")
	static void Show(UPARAM(ref) TScriptInterface<ICsUIObject>& Target);

	UFUNCTION(BlueprintCallable, Category = "Library|ICsUIObject")
	static void Hide(UPARAM(ref) TScriptInterface<ICsUIObject>& Target);

	UFUNCTION(BlueprintCallable, Category = "Library|ICsUIObject")
	static void Enable(UPARAM(ref) TScriptInterface<ICsUIObject>& Target);

	UFUNCTION(BlueprintCallable, Category = "Library|ICsUIObject")
	static void Disable(UPARAM(ref) TScriptInterface<ICsUIObject>& Target);
};