// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UUserWidget;
class UClass;
class UObject;
class UWidgetAnimation;
class UTextBlock;
class UButton;
class UImage;

#include "CsScriptLibrary_Widget.generated.h"

UCLASS()
class CSUI_API UCsScriptLibrary_Widget : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* 
	* 
	* @param Context			The calling context.
	* @param Owner
	* @param UserWidgetClass
	* @param WidgetName			(optional)
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsUI|Library|Widget", meta = (AutoCreateRefTerm = "Context,WidgetName"))
	static UUserWidget* Create(const FString& Context, UObject* Owner, TSubclassOf<UUserWidget> UserWidgetClass, const FName& WidgetName);

	// Load
#pragma region
public:

	/**
	* Load a UserWidget at the given Path.
	*
	* @param Context	The calling context.
	* @param Path		SoftObjectPath to the UserWidget to load.
	* return			Class associated with UserWidget.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Widget", meta = (AutoCreateRefTerm = "Context,Path"))
	static UClass* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a UserWidget at the given Path.
	*
	* @param Context	The calling context.
	* @param Path		FString path to the UserWidget to load.
	* return			Class associated with UserWidget.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Widget", meta = (AutoCreateRefTerm = "Context,Path"))
	static UClass* LoadByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load

// Position
#pragma region
public:

	// Screen
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Widget|Position", meta = (AutoCreateRefTerm = "Context"))
	static FVector2D GetScreenPositionBySlot(const FString& Context, UWidget* Widget);

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Widget|Position", meta = (AutoCreateRefTerm = "Context"))
	static FVector2D GetAbsoluteScreenPositionByCachedGeometry(const FString& Context, UWidget* Widget);

#pragma endregion Screen

	// Viewport
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Widget|Position", meta = (AutoCreateRefTerm = "Context,OutPixelPosition,OutViewportPosition"))
	static void GetPixelAndViewportPositionByCachedGeometry(const FString& Context, UWidget* Widget, FVector2D& OutPixelPosition, FVector2D& OutViewportPosition);

#pragma endregion Viewport

	// World
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Widget|Position", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,OutPosition,OutDirection"))
	static bool GetWorldPositionBySlot(const FString& Context, UObject* WorldContextObject, const int32& ControllerId, UWidget* Widget, FVector& OutPosition, FVector& OutDirection);

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Widget|Position", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,OutPosition,OutDirection"))
	static bool GetWorldPositionByCachedGeometry(const FString& Context, UObject* WorldContextObject, const int32& ControllerId, UWidget* Widget, FVector& OutPosition, FVector& OutDirection);

#pragma endregion World

#pragma endregion Position

// Animation
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Widget|Animation", meta = (AutoCreateRefTerm = "Context,AnimName"))
	static UWidgetAnimation* GetAnimation(const FString& Context, UUserWidget* Widget, const FName& AnimName);

#pragma endregion Animation

// TextBlock
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Widget|TextBlock", meta = (AutoCreateRefTerm = "Context,PropertyName"))
	static UTextBlock* GetTextBlock(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

#pragma endregion TextBlock

// Button
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Widget|Button", meta = (AutoCreateRefTerm = "Context,PropertyName"))
	static UButton* GetButton(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

#pragma endregion Button

// Image
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUI|Library|Widget|Image", meta = (AutoCreateRefTerm = "Context,PropertyName"))
	static UImage* GetImage(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

#pragma endregion Image
};