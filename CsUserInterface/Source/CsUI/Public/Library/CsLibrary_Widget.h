// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_UserWidget_Anim.h"

class UUserWidget;
class UWidgetAnimation;

namespace NCsWidget
{
	namespace NPosition
	{
		struct CSUI_API FLibrary final
		{
		public:

			/**
			* Get the position of the Widget by Cast<UCanvasPanelSlot>(Widget->Slot)->GetAbsolutePosition().
			*
			* @param Context	The calling context.
			* @param Widget
			* return			Position of the Widget.
			*/
			static FVector2D GetBySlotChecked(const FString& Context, UUserWidget* Widget);

			/**
			* Safely get the position of the Widget by Cast<UCanvasPanelSlot>(Widget->Slot)->GetAbsolutePosition().
			*
			* @param Context	The calling context.
			* @param Widget
			* @param Log
			* return			Position of the Widget.
			*/
			static FVector2D GetSafeBySlot(const FString& Context, UUserWidget* Widget, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely get the position of the Widget by Cast<UCanvasPanelSlot>(Widget->Slot)->GetAbsolutePosition().
			*
			* @param Widget
			* return			Position of the Widget.
			*/
			static FVector2D GetSafeBySlot(UUserWidget* Widget);

			/**
			* Get the absolute position of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
			*
			* @param Context	The calling context.
			* @param Widget
			* return			Absolute position of the Widget.
			*/
			static FVector2D GetAbsoluteByCachedGeometryChecked(const FString& Context, UUserWidget* Widget);

			/**
			* Safely get the absolute position of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
			*
			* @param Context	The calling context.
			* @param Widget
			* @param Log
			* return			Absolute position of the Widget.
			*/
			static FVector2D GetSafeAbsoluteByCachedGeometry(const FString& Context, UUserWidget* Widget, void(*Log)(const FString&) = &NCsUI::FLog::Warning);

			/**
			* Safely get the absolute position of the Widget by Widget->GetCachedGeometry()->GetAbsolutionPosition().
			*
			* @param Widget
			* return			Absolute position of the Widget.
			*/
			static FVector2D GetSafeAbsoluteByCachedGeometry(UUserWidget* Widget);
		};
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
}