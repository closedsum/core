// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_UserWidget_Anim.h"


#include "CsScriptLibrary_Widget.generated.h"

class UUserWidget;
class UClass;
class UObject;
class UWidgetAnimation;
class UTextBlock;
class UButton;
class UImage;
class UProgressBar;

UCLASS()
class CSUICORE_API UCsScriptLibrary_Widget : public UObject
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
	UFUNCTION(BlueprintCallable, Category = "CsUICore|Library|Widget", meta = (AutoCreateRefTerm = "Context,WidgetName"))
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
	UFUNCTION(BlueprintCallable, Category = "CsUICore|Library|Widget", meta = (AutoCreateRefTerm = "Context,Path"))
	static UClass* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a UserWidget at the given Path.
	*
	* @param Context	The calling context.
	* @param Path		FString path to the UserWidget to load.
	* return			Class associated with UserWidget.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsUICore|Library|Widget", meta = (AutoCreateRefTerm = "Context,Path"))
	static UClass* LoadByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load

// Get
#pragma region
public:

	/**
	* Get the UserWidget value at the give Path for Object.
	* 
	* @param Context	The calling context.
	* @param Object
	* @param Path		Full variable path to the UserWidget value on Object.
	* @param OutSuccess	(out)
	* return			UserWidget
	*/
	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget", meta = (AutoCreateRefTerm = "Context,Path"))
	static UUserWidget* GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess);

	/**
	* Get a SoftClassPtr of type: UserWidget value at the give Path for Object as a String.
	* 
	* @param Context			The calling context.
	* @param Object
	* @param Path				Full variable path to the UserWidget value on Object.
	* @param OutPathAsString	(out)
	* @param OutSuccess			(out)
	* return					String
	*/
	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget", meta = (AutoCreateRefTerm = "Context,Path"))
	static bool GetSoftClassAsStringByPath(const FString& Context, UObject* Object, const FString& Path, FString& OutPathAsString, bool& OutSuccess);

#pragma endregion Get

// Render
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsUICore|Library|Widget", meta = (AutoCreateRefTerm = "Context,Easing,Start,End,Alpha"))
	static bool Render_Opacity_Ease(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha);

	UFUNCTION(BlueprintCallable, Category = "CsUICore|Library|Widget", meta = (AutoCreateRefTerm = "Context,Easing,Start,End,Alpha"))
	static bool Render_Scale_Ease(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha);

#pragma endregion Render

// Position
#pragma region
public:

	// Screen
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget|Position", meta = (AutoCreateRefTerm = "Context"))
	static FVector2f GetScreenPositionBySlot(const FString& Context, UWidget* Widget);

	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget|Position", meta = (AutoCreateRefTerm = "Context"))
	static FVector2f GetAbsoluteScreenPositionByCachedGeometry(const FString& Context, UWidget* Widget);

#pragma endregion Screen

	// Viewport
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget|Position", meta = (AutoCreateRefTerm = "Context,OutPixelPosition,OutViewportPosition"))
	static void GetPixelAndViewportPositionByCachedGeometry(const FString& Context, UWidget* Widget, FVector2f& OutPixelPosition, FVector2f& OutViewportPosition);

#pragma endregion Viewport

	// World
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget|Position", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,OutPosition,OutDirection"))
	static bool GetWorldPositionBySlot(const FString& Context, UObject* WorldContextObject, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection);

	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget|Position", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,OutPosition,OutDirection"))
	static bool GetWorldPositionByCachedGeometry(const FString& Context, UObject* WorldContextObject, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection);

#pragma endregion World

#pragma endregion Position

// Animation
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget|Animation", meta = (AutoCreateRefTerm = "Context,AnimName"))
	static UWidgetAnimation* GetAnimation(const FString& Context, UUserWidget* Widget, const FName& AnimName);

	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget|Animation", meta = (DisplayName = "Get Animation (Checked)", AutoCreateRefTerm = "Context,AnimName"))
	static UWidgetAnimation* GetAnimationChecked(const FString& Context, UUserWidget* Widget, const FName& AnimName, bool& OutSuccess);

	UFUNCTION(BlueprintCallable, Category = "CsUICore|Library|Widget|Animation", meta = (AutoCreateRefTerm = "Context,Params"))
	static bool PlayAnimation(const FString& Context, UUserWidget* Widget, const FCsUserWidget_Anim_PlayParams& Params);

#pragma endregion Animation

// TextBlock
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget|TextBlock", meta = (AutoCreateRefTerm = "Context,PropertyName"))
	static UTextBlock* GetTextBlock(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

#pragma endregion TextBlock

// Button
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget|Button", meta = (AutoCreateRefTerm = "Context,PropertyName"))
	static UButton* GetButton(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

#pragma endregion Button

// Image
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget|Image", meta = (AutoCreateRefTerm = "Context,PropertyName"))
	static UImage* GetImage(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

#pragma endregion Image

// ProgressBar
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget|ProgressBar", meta = (AutoCreateRefTerm = "Context,PropertyName"))
	static UProgressBar* GetProgressBar(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

#pragma endregion ProgressBar

// Border
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget|Border", meta = (AutoCreateRefTerm = "Context,PropertyName"))
	static UBorder* GetBorder(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

#pragma endregion ProgressBar
};

UCLASS()
class CSUICORE_API UCsScriptLibrary_Widget_Animation : public UObject
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintPure, Category = "CsUICore|Library|Widget|Animation", meta = (AutoCreateRefTerm = "Context"))
	static bool HasFinished(const FString& Context, const UUserWidget* Widget, const UWidgetAnimation* Animation);
};