// Copyright 2019, RCT Studios and The Rogue Initiative. All Rights Reserved.
#pragma once

#include "Runtime/CoreUObject/Public/UObject/Object.h"
#include "CsLibrary_Menu.generated.h"

class ICsMenu;

UCLASS()
class CSCORE_API UCsLibrary_Menu : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Library|Menu")
	static void Open(UPARAM(ref) TScriptInterface<ICsMenu>& Target);

	UFUNCTION(BlueprintPure, Category = "Library|Menu")
	static bool IsOpened(UPARAM(ref) TScriptInterface<ICsMenu>& Target);

	UFUNCTION(BlueprintCallable, Category = "Library|Menu")
	static void Close(UPARAM(ref) TScriptInterface<ICsMenu>& Target);

	UFUNCTION(BlueprintPure, Category = "Library|Menu")
	static bool IsClosed(UPARAM(ref) TScriptInterface<ICsMenu>& Target);
};