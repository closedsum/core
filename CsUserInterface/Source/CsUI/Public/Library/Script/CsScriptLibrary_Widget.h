// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UWorld;
class UObject;

#include "CsScriptLibrary_Widget.generated.h"

UCLASS()
class CSUI_API UCsScriptLibrary_Widget : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Widget", meta = (AutoCreateRefTerm = "AnimName"))
	static UWidgetAnimation* GetSafeAnimation(UUserWidget* Widget, const FName& AnimName);
};