// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_UserWidget_Anim.h"

class UObject;
class UUserWidget;
class UWidgetAnimation;
class UTextBlock;
class UButton;

namespace NCsWidget
{
	struct CSUI_API FLibrary final
	{
	public:

		/**
		*
		*
		* @param Context			The calling context.
		* @param Owner
		* @param UserWidgetClass
		* @param WidgetName			(optional)
		* @param Log				(optional)
		*/
		static UUserWidget* CreateSafe(const FString& Context, UObject* Owner, TSubclassOf<UUserWidget> UserWidgetClass, const FName& WidgetName = NAME_None, void(*Log)(const FString&) = &NCsUI::FLog::Warning);
	};

	namespace NPosition
	{
		namespace NScreen
		{
			struct CSUI_API FLibrary final
			{
				/**
				* Get the screen position of the Widget by Cast<UCanvasPanelSlot>(Widget->Slot)->GetAbsolutePosition().
				*
				* @param Context	The calling context.
				* @param Widget
				* return			Position of the Widget.
				*/
				static FVector2D GetBySlotChecked(const FString& Context, UUserWidget* Widget);

				/**
				* Safely get the screen position of the Widget by Cast<UCanvasPanelSlot>(Widget->Slot)->GetAbsolutePosition().
				*
				* @param Context	The calling context.
				* @param Widget
				* @param Log
				* return			Position of the Widget.
				*/
				static FVector2D GetSafeBySlot(const FString& Context, UUserWidget* Widget, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

				/**
				* Safely get the screen position of the Widget by Cast<UCanvasPanelSlot>(Widget->Slot)->GetAbsolutePosition().
				*
				* @param Widget
				* return			Position of the Widget.
				*/
				static FVector2D GetSafeBySlot(UUserWidget* Widget);

				/**
				* Get the absolute screen position of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
				*
				* @param Context	The calling context.
				* @param Widget
				* return			Absolute position of the Widget.
				*/
				static FVector2D GetAbsoluteByCachedGeometryChecked(const FString& Context, UUserWidget* Widget);

				/**
				* Safely get the absolute screen position of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
				*
				* @param Context	The calling context.
				* @param Widget
				* @param Log
				* return			Absolute position of the Widget.
				*/
				static FVector2D GetSafeAbsoluteByCachedGeometry(const FString& Context, UUserWidget* Widget, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

				/**
				* Safely get the absolute screen position of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
				*
				* @param Widget
				* return			Absolute position of the Widget.
				*/
				static FVector2D GetSafeAbsoluteByCachedGeometry(UUserWidget* Widget);
			};
		}

		namespace NViewport
		{
			struct CSUI_API FLibrary final
			{
				/**
				* Get the pixel and viewport position of the Widget by transform the absolute position:
				* NCsWidget::NScreen::GetAbsoluteByCachedGeometryChecked to viewport space.
				*
				* @param Context				The calling context.
				* @param Widget
				* @param OutPixelPosition		(out) The position in the game's viewport, usable for line traces and
				*									  other uses where you need a coordinate in the space of viewport resolution units.
				* @param OutViewportPosition	(out) The position in the space of other widgets in the viewport.  Like if you wanted
				*									  to add another widget to the viewport at the same position in viewport space as this location, 
				*									  this is what you would use.
				*/
				static void GetByCachedGeometryChecked(const FString& Context, UUserWidget* Widget, FVector2D& OutPixelPosition, FVector2D& OutViewportPosition);

				/**
				* Safely get the pixel and viewport position of the Widget by transform the absolute position:
				* NCsWidget::NScreen::GetAbsoluteByCachedGeometryChecked to viewport space.
				*
				* @param Context	The calling context.
				* @param Widget
				* @param OutPixelPosition		(out) The position in the game's viewport, usable for line traces and
				*									  other uses where you need a coordinate in the space of viewport resolution units.
				* @param OutViewportPosition	(out) The position in the space of other widgets in the viewport.  Like if you wanted
				*									  to add another widget to the viewport at the same position in viewport space as this location,
				*									  this is what you would use.
				* @param Log
				*/
				static void GetSafeByCachedGeometry(const FString& Context, UUserWidget* Widget, FVector2D& OutPixelPosition, FVector2D& OutViewportPosition, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

				/**
				* Safely get the viewport position of the Widget by transform the absolute position:
				* NCsWidget::NScreen::GetAbsoluteByCachedGeometryChecked to viewport space.
				*
				* @param Widget
				* @param OutPixelPosition		(out) The position in the game's viewport, usable for line traces and
				*									  other uses where you need a coordinate in the space of viewport resolution units.
				* @param OutViewportPosition	(out) The position in the space of other widgets in the viewport.  Like if you wanted
				*									  to add another widget to the viewport at the same position in viewport space as this location,
				*									  this is what you would use.
				*/
				static void GetSafeByCachedGeometry(UUserWidget* Widget, FVector2D& OutPixelPosition, FVector2D& OutViewportPosition);
			};
		}

		namespace NWorld
		{
			struct CSUI_API FLibrary final
			{
			public:

				/**
				* Get the world position and direction of the Widget by Cast<UCanvasPanelSlot>(Widget->Slot)->GetAbsolutePosition().
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllderId	The Id of the player's view to use to deproject the Widget's screen position to a world position.
				* @param Widget
				* @param OutPosition	(out) Location of the Widget in World Space (convert the Screen Position to World Space).
				* @param OutDirection	(out) World space direction vector away from the camera at the Widget's Screen's position.
				* return				Whether a valid world position and direction was found.
				*/
				static bool GetBySlotChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection);

				/**
				* Safely get the world position and direction of the Widget by Cast<UCanvasPanelSlot>(Widget->Slot)->GetAbsolutePosition().
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllderId	The Id of the player's view to use to deproject the Widget's screen position to a world position.
				* @param Widget
				* @param OutPosition	(out) Location of the Widget in World Space (convert the Screen Position to World Space).
				* @param OutDirection	(out) World space direction vector away from the camera at the Widget's Screen's position.
				* @param Log
				* return				Whether a valid world position and direction was found.
				*/
				static bool GetSafeBySlot(const FString& Context, UObject* WorldContext, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

				/**
				* Safely get the world position and direction of the Widget by Cast<UCanvasPanelSlot>(Widget->Slot)->GetAbsolutePosition().
				*
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllderId	The Id of the player's view to use to deproject the Widget's screen position to a world position.
				* @param Widget
				* @param OutPosition	(out) Location of the Widget in World Space (convert the Screen Position to World Space).
				* @param OutDirection	(out) World space direction vector away from the camera at the Widget's Screen's position.
				* @param Log
				* return				Whether a valid world position and direction was found.
				*/
				static bool GetSafeBySlot(UObject* WorldContext, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection);

				/**
				* Get the world position and direction of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllderId	The Id of the player's view to use to deproject the Widget's screen position to a world position.
				* @param Widget
				* @param OutPosition	(out) Location of the Widget in World Space (convert the Screen Position to World Space).
				* @param OutDirection	(out) World space direction vector away from the camera at the Widget's Screen's position.
				* return				Whether a valid world position and direction was found.
				*/
				static bool GetByCachedGeometryChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection);

				/**
				* Safely get the absolute screen position of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllderId	The Id of the player's view to use to deproject the Widget's screen position to a world position.
				* @param Widget
				* @param OutPosition	(out) Location of the Widget in World Space (convert the Screen Position to World Space).
				* @param OutDirection	(out) World space direction vector away from the camera at the Widget's Screen's position.
				* return				Whether a valid world position and direction was found.
				*/
				static bool GetSafeByCachedGeometry(const FString& Context, UObject* WorldContext, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

				/**
				* Safely get the absolute screen position of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
				*
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ControllderId	The Id of the player's view to use to deproject the Widget's screen position to a world position.
				* @param Widget
				* @param OutPosition	(out) Location of the Widget in World Space (convert the Screen Position to World Space).
				* @param OutDirection	(out) World space direction vector away from the camera at the Widget's Screen's position.
				* return				Whether a valid world position and direction was found.
				*/
				static bool GetSafeByCachedGeometry(UObject* WorldContext, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection);
			};
		}
	}

	namespace NAnimation
	{
		struct CSUI_API FLibrary final
		{
		public:

			/**
			* Get a Widget Animation with AnimName from Widget.
			* 
			* @parma Context	The calling context.
			* @param Widget
			* @param AnimName	Name of the animation.
			* return			Widget Animation.
			*/
			static UWidgetAnimation* GetChecked(const FString& Context, UUserWidget* Widget, const FName& AnimName);

			/**
			* Safely get a Widget Animation with AnimName from Widget.
			*
			* @parma Context	The calling context.
			* @param Widget
			* @param AnimName	Name of the animation.
			* @param Log
			* return			Widget Animation.
			*/
			static UWidgetAnimation* GetSafe(const FString& Context, UUserWidget* Widget, const FName& AnimName, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely get a Widget Animation with AnimName from Widget.
			*
			* @param Widget
			* @param AnimName	Name of the animation.
			* return			Widget Animation.
			*/
			static UWidgetAnimation* GetSafe(UUserWidget* Widget, const FName& AnimName);

			#define ParamsType NCsUserWidget::NAnim::NPlay::FParams

			/**
			* Play the Widget Animation with the given Params.
			* 
			* @param Context
			* @param Widget
			* @param Params
			*/
			static void PlayChecked(const FString& Context, UUserWidget* Widget, const ParamsType& Params);

			/**
			* Safely play the Widget Animation with the given Params.
			*
			* @param Context
			* @param Widget
			* @param Params
			* @param Log
			*/
			static void SafePlay(const FString& Context, UUserWidget* Widget, const ParamsType& Params, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely play the Widget Animation with the given Params.
			*
			* @param Widget
			* @param Params
			*/
			static void SafePlay(UUserWidget* Widget, const ParamsType& Params);

			#undef ParamsType

			/**
			*
			*
			* @param Context
			* @param Widget
			* @param Params
			*/
			static void PlayChecked(const FString& Context, UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params);

			/**
			* Safely play the Widget Animation with the given Params.
			*
			* @param Context
			* @param Widget
			* @param Params
			* @param Log
			*/
			static void SafePlay(const FString& Context, UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely play the Widget Animation with the given Params.
			*
			* @param Widget
			* @param Params
			*/
			static void SafePlay(UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params);
		};
	}

	namespace NTextBlock
	{
		struct CSUI_API FLibrary final
		{
		public:

			/**
			* Get a TextBlock with PropertyName from Widget.
			*
			* @parma Context		The calling context.
			* @param Widget
			* @param PropertyName	Name of the property.
			* return				TextBlock.
			*/
			static UTextBlock* GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

			/**
			* Safely get a TextBlock with PropertyName from Widget.
			*
			* @parma Context		The calling context.
			* @param Widget
			* @param PropertyName	Name of the property.
			* @param Log
			* return				TextBlock.
			*/
			static UTextBlock* GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely get a TextBlock with PropertyName from Widget.
			*
			* @param Widget
			* @param PropertyName	Name of the property.
			* return				TextBlock.
			*/
			static UTextBlock* GetSafe(UUserWidget* Widget, const FName& PropertyName);
		};
	}

	namespace NButton
	{
		struct CSUI_API FLibrary final
		{
		public:

			/**
			* Get a Button with PropertyName from Widget.
			*
			* @parma Context		The calling context.
			* @param Widget
			* @param PropertyName	Name of the property.
			* return				Button.
			*/
			static UButton* GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

			/**
			* Safely get a Button with PropertyName from Widget.
			*
			* @parma Context		The calling context.
			* @param Widget
			* @param PropertyName	Name of the property.
			* @param Log
			* return				Button.
			*/
			static UButton* GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely get a Button with PropertyName from Widget.
			*
			* @param Widget
			* @param PropertyName	Name of the property.
			* return				Button.
			*/
			static UButton* GetSafe(UUserWidget* Widget, const FName& PropertyName);
		};
	}
}