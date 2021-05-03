// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UWorld;
class UObject;

#include "CsScriptLibrary_Widget.generated.h"

UCLASS()
class CSUI_API UCsScriptLibrary_Widget : public UObject
{
	GENERATED_UCLASS_BODY()

// Position
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Widget|Position", meta = (AutoCreateRefTerm = "Context"))
	static FVector2D GetPositionBySlot(const FString& Context, UUserWidget* Widget);

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Widget|Position", meta = (AutoCreateRefTerm = "Context"))
	static FVector2D GetAbsolutePositionByCachedGeometry(const FString& Context, UUserWidget* Widget);

#pragma endregion Position

// Animation
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Widget|Animation", meta = (AutoCreateRefTerm = "Context,AnimName"))
	static UWidgetAnimation* GetAnimation(const FString& Context, UUserWidget* Widget, const FName& AnimName);

#pragma endregion Animation
};