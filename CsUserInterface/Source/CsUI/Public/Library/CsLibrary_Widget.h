// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_UserWidget_Anim.h"
// Log
#include "Utility/CsUILog.h"

class UUserWidget;
class UWidgetAnimation;

namespace NCsWidget
{
	struct CSUI_API FLibrary final
	{
	// Animation
	#pragma region
	public:

		/**
		* Get a Widget Animation with name AnimName from Widget.
		* 
		* @parma Context	The calling context.
		* @param Widget
		* @param AnimName
		* return			Widget Animation.
		*/
		static UWidgetAnimation* GetAnimationChecked(const FString& Context, UUserWidget* Widget, const FName& AnimName);

		#define ParamsType NCsUserWidget::NAnim::NPlay::FParams

		/**
		* 
		* 
		* @param Context
		* @param Widget
		* @param Params
		*/
		static void PlayAnimationChecked(const FString& Context, UUserWidget* Widget, const ParamsType& Params);

		#undef ParamsType

		/**
		*
		*
		* @param Context
		* @param Widget
		* @param Params
		*/
		static void PlayAnimationChecked(const FString& Context, UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params);

	#pragma endregion Animation
	};
}