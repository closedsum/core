// Copyright 2019, RCT Studios and The Rogue Initiative. All Rights Reserved.
#pragma once

#include "Runtime/CoreUObject/Public/UObject/Object.h"
#include "CsLibrary_Button.generated.h"

class ICsButton;

UCLASS()
class CSCORE_API UCsLibrary_Button : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Library|ICsButton")
	static void Press(UPARAM(ref) TScriptInterface<ICsButton>& Target);

	UFUNCTION(BlueprintCallable, Category = "Library|ICsButton")
	static void Release(UPARAM(ref) TScriptInterface<ICsButton>& Target);
};