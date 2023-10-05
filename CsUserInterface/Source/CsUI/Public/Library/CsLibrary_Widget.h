// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_UserWidget_Anim.h"
#include "Types/CsTypes_Interpolation.h"
// Coroutine
#include "Coroutine/CsRoutineHandle.h"
// Log
#include "Utility/CsUILog.h"

class UObject;
class UWidget;
class UUserWidget;
class UClass;
class UCanvasPanelSlot;
class UWidgetAnimation;
class UTextBlock;
class UButton;
class UImage;
class UProgressBar;
class UBorder;

struct FCsRoutine;

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

		/**
		* Get the order priority this widget is rendered in. Higher values are rendered last (and so they will appear to be on top).
		* 
		* @param Context	The calling context
		* @param Widget
		* return			ZOrder
		*/
		static int32 GetZOrderChecked(const FString& Context, const UUserWidget* Widget);

		/**
		* Set the order this widget is rendered in. Higher values are rendered last (and so they will appear to be on top).
		* 
		* @param Context	The calling context.
		* @param Widget
		* @param ZOrder
		*/
		static void SetZOrderChecked(const FString& Context, UUserWidget* Widget, const int32& ZOrder);

	// Load
	#pragma region
	public:

		/**
		* Load the UserWidget at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the UserWidget to load.
		* return			Class associated with the UserWidget.
		*/
		static UClass* LoadChecked(const FString& Context, const FSoftObjectPath& Path);

		/**
		* Safely load the UserWidget at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the UserWidget to load.
		* @param Log		(optional)
		* return			Class associated with the UserWidget.
		*/
		static UClass* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

		/**
		* Load a UserWidget at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the UserWidget to load.
		* @param Log		(optional)
		* return			Class associated with the UserWidget.
		*/
		static UClass* LoadChecked(const FString& Context, const FString& Path);

		/**
		* Safely load a UserWidget at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the UserWidget to load.
		* @param Log		(optional)
		* return			Class associated with the UserWidget.
		*/
		static UClass* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

	#pragma endregion Load

	public:

		static void AddToScreenChecked(const FString& Context, const UObject* WorldContext, UWidget* Widget, ULocalPlayer* Player, const int32& ZOrder);
	};

	namespace NRender
	{
		struct CSUI_API FLibrary final
		{
		public:

			static bool CanEaseChecked(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha);

			static bool CanEase(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			static float GetPercentChecked(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha);

			static void Opacity_EaseChecked(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha);

			static bool Opacity_SafeEase(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			static void Scale_EaseChecked(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha);

			static bool Scale_SafeEase(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

		// Anim
		#pragma region
		public:

		/*
			static FCsRoutineHandle Scale_AnimChecked(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Duration);
		private:
			static char Scale_AnimByScalar_Internal(FCsRoutine* R);
		*/

		#pragma endregion Anim
		};
	}

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
				static FVector2d GetBySlot2dChecked(const FString& Context, UWidget* Widget);

				/**
				* Get the screen position of the Widget by Cast<UCanvasPanelSlot>(Widget->Slot)->GetAbsolutePosition().
				*
				* @param Context	The calling context.
				* @param Widget
				* return			Position of the Widget.
				*/
				static FVector2f GetBySlot2fChecked(const FString& Context, UWidget* Widget);

				/**
				* Safely get the screen position of the Widget by Cast<UCanvasPanelSlot>(Widget->Slot)->GetAbsolutePosition().
				*
				* @param Context	The calling context.
				* @param Widget
				* @param Log
				* return			Position of the Widget.
				*/
				static FVector2d GetSafeBySlot2d(const FString& Context, UWidget* Widget, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

				/**
				* Safely get the screen position of the Widget by Cast<UCanvasPanelSlot>(Widget->Slot)->GetAbsolutePosition().
				*
				* @param Context	The calling context.
				* @param Widget
				* @param Log
				* return			Position of the Widget.
				*/
				static FVector2f GetSafeBySlot2f(const FString& Context, UWidget* Widget, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

				/**
				* Safely get the screen position of the Widget by Cast<UCanvasPanelSlot>(Widget->Slot)->GetAbsolutePosition().
				*
				* @param Widget
				* return			Position of the Widget.
				*/
				static FVector2d GetSafeBySlot2d(UWidget* Widget);

				/**
				* Safely get the screen position of the Widget by Cast<UCanvasPanelSlot>(Widget->Slot)->GetAbsolutePosition().
				*
				* @param Widget
				* return			Position of the Widget.
				*/
				static FVector2f GetSafeBySlot2f(UWidget* Widget);

				/**
				* Get the absolute screen position of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
				*
				* @param Context	The calling context.
				* @param Widget
				* return			Absolute position of the Widget.
				*/
				static FVector2d GetAbsoluteByCachedGeometry2dChecked(const FString& Context, UWidget* Widget);

				/**
				* Get the absolute screen position of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
				*
				* @param Context	The calling context.
				* @param Widget
				* return			Absolute position of the Widget.
				*/
				static FVector2f GetAbsoluteByCachedGeometry2fChecked(const FString& Context, UWidget* Widget);

				/**
				* Safely get the absolute screen position of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
				*
				* @param Context	The calling context.
				* @param Widget
				* @param Log
				* return			Absolute position of the Widget.
				*/
				static FVector2d GetSafeAbsoluteByCachedGeometry2d(const FString& Context, UWidget* Widget, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

				/**
				* Safely get the absolute screen position of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
				*
				* @param Context	The calling context.
				* @param Widget
				* @param Log
				* return			Absolute position of the Widget.
				*/
				static FVector2f GetSafeAbsoluteByCachedGeometry2f(const FString& Context, UWidget* Widget, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

				/**
				* Safely get the absolute screen position of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
				*
				* @param Widget
				* return			Absolute position of the Widget.
				*/
				static FVector2d GetSafeAbsoluteByCachedGeometry2d(UWidget* Widget);

				/**
				* Safely get the absolute screen position of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
				*
				* @param Widget
				* return			Absolute position of the Widget.
				*/
				static FVector2f GetSafeAbsoluteByCachedGeometry2f(UWidget* Widget);
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
				static void GetByCachedGeometryChecked(const FString& Context, UWidget* Widget, FVector2d& OutPixelPosition, FVector2d& OutViewportPosition);

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
				static void GetByCachedGeometryChecked(const FString& Context, UWidget* Widget, FVector2f& OutPixelPosition, FVector2f& OutViewportPosition);

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
				static void GetSafeByCachedGeometry(const FString& Context, UWidget* Widget, FVector2d& OutPixelPosition, FVector2d& OutViewportPosition, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

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
				static void GetSafeByCachedGeometry(const FString& Context, UWidget* Widget, FVector2f& OutPixelPosition, FVector2f& OutViewportPosition, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

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
				static void GetSafeByCachedGeometry(UWidget* Widget, FVector2d& OutPixelPosition, FVector2d& OutViewportPosition);

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
				static void GetSafeByCachedGeometry(UWidget* Widget, FVector2f& OutPixelPosition, FVector2f& OutViewportPosition);
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
				static bool GetBySlotChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3d& OutPosition, FVector3d& OutDirection);

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
				static bool GetBySlotChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection);

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
				static bool GetSafeBySlot(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3d& OutPosition, FVector3d& OutDirection, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

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
				static bool GetSafeBySlot(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

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
				static bool GetSafeBySlot(UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3d& OutPosition, FVector3d& OutDirection);

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
				static bool GetSafeBySlot(UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection);

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
				static bool GetByCachedGeometryChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3d& OutPosition, FVector3d& OutDirection);

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
				static bool GetByCachedGeometryChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection);

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
				static bool GetSafeByCachedGeometry(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3d& OutPosition, FVector3d& OutDirection, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

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
				static bool GetSafeByCachedGeometry(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

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
				static bool GetSafeByCachedGeometry(UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3d& OutPosition, FVector3d& OutDirection);

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
				static bool GetSafeByCachedGeometry(UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection);
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
			* @param Context	The calling context.
			* @param Widget
			* @param AnimName	Name of the animation.
			* return			Widget Animation.
			*/
			static UWidgetAnimation* GetChecked(const FString& Context, UUserWidget* Widget, const FName& AnimName);

			/**
			* Safely get a Widget Animation with AnimName from Widget.
			*
			* @param Context	The calling context.
			* @param Widget
			* @param AnimName	Name of the animation.
			* @param Log		(optional)
			* return			Widget Animation.
			*/
			static UWidgetAnimation* GetSafe(const FString& Context, UUserWidget* Widget, const FName& AnimName, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely get a Widget Animation with AnimName from Widget.
			*
			* @param Context	The calling context.
			* @param Widget
			* @param AnimName	Name of the animation.
			* @param OutSuccess (out)
			* @param Log		(optional)
			* return			Widget Animation.
			*/
			static UWidgetAnimation* GetSafe(const FString& Context, UUserWidget* Widget, const FName& AnimName, bool& OutSuccess, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely get a Widget Animation with AnimName from Widget.
			*
			* @param Widget
			* @param AnimName	Name of the animation.
			* return			Widget Animation.
			*/
			static UWidgetAnimation* GetSafe(UUserWidget* Widget, const FName& AnimName);

			/**
			* Get the "length" of Animation (GetEndTime() - GetStartTime()).
			* 
			* @param Context	The calling context.
			* @param Animation
			* return			Animation length.
			*/
			static float GetLengthChecked(const FString& Context, const UWidgetAnimation* Animation);

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
			static bool SafePlay(const FString& Context, UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely play the Widget Animation with the given Params.
			*
			* @param Widget
			* @param Params
			*/
			static bool SafePlay(UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params);

			/**
			*
			*
			* @param Context
			* @param Widget
			* @param Params
			*/
			static void PlayChecked(const FString& Context, UUserWidget* Widget, const FCsUserWidget_Anim_PlayParams& Params);

			/**
			* Safely play the Widget Animation with the given Params.
			*
			* @param Context
			* @param Widget
			* @param Params
			* @param Log
			*/
			static bool SafePlay(const FString& Context, UUserWidget* Widget, const FCsUserWidget_Anim_PlayParams& Params, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely play the Widget Animation with the given Params.
			*
			* @param Widget
			* @param Params
			*/
			static bool SafePlay(UUserWidget* Widget, const FCsUserWidget_Anim_PlayParams& Params);
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
			* @param Context		The calling context.
			* @param Widget
			* @param PropertyName	Name of the property.
			* return				TextBlock.
			*/
			static UTextBlock* GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

			/**
			* Safely get a TextBlock with PropertyName from Widget.
			*
			* @param Context		The calling context.
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
			* @param Context		The calling context.
			* @param Widget
			* @param PropertyName	Name of the property.
			* return				Button.
			*/
			static UButton* GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

			/**
			* Safely get a Button with PropertyName from Widget.
			*
			* @param Context		The calling context.
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

	namespace NImage
	{
		struct CSUI_API FLibrary final
		{
		public:

			/**
			* Get a Image with PropertyName from Widget.
			*
			* @param Context		The calling context.
			* @param Widget
			* @param PropertyName	Name of the property.
			* return				Image.
			*/
			static UImage* GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

			/**
			* Safely get a Image with PropertyName from Widget.
			*
			* @param Context		The calling context.
			* @param Widget
			* @param PropertyName	Name of the property.
			* @param Log
			* return				Image.
			*/
			static UImage* GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely get a Image with PropertyName from Widget.
			*
			* @param Widget
			* @param PropertyName	Name of the property.
			* return				Image.
			*/
			static UImage* GetSafe(UUserWidget* Widget, const FName& PropertyName);
		};
	}

	namespace NProgressBar
	{
		struct CSUI_API FLibrary final
		{
		public:

			/**
			* Get a ProgressBar with PropertyName from Widget.
			*
			* @param Context		The calling context.
			* @param Widget
			* @param PropertyName	Name of the property.
			* return				ProgressBar.
			*/
			static UProgressBar* GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

			/**
			* Safely get a ProgressBar with PropertyName from Widget.
			*
			* @param Context		The calling context.
			* @param Widget
			* @param PropertyName	Name of the property.
			* @param Log
			* return				ProgressBar.
			*/
			static UProgressBar* GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely get a ProgressBar with PropertyName from Widget.
			*
			* @param Widget
			* @param PropertyName	Name of the property.
			* return				ProgressBar.
			*/
			static UProgressBar* GetSafe(UUserWidget* Widget, const FName& PropertyName);
		};
	}

	namespace NBorder
	{
		struct CSUI_API FLibrary final
		{
		public:

			/**
			* Get a Border with PropertyName from Widget.
			*
			* @param Context		The calling context.
			* @param Widget
			* @param PropertyName	Name of the property.
			* return				Border.
			*/
			static UBorder* GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName);

			/**
			* Safely get a Border with PropertyName from Widget.
			*
			* @param Context		The calling context.
			* @param Widget
			* @param PropertyName	Name of the property.
			* @param Log
			* return				Border.
			*/
			static UBorder* GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely get a Border with PropertyName from Widget.
			*
			* @param Widget
			* @param PropertyName	Name of the property.
			* return				Border.
			*/
			static UBorder* GetSafe(UUserWidget* Widget, const FName& PropertyName);
		};
	}
}