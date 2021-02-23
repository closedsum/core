// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_UserWidget_Anim.h"

class UUserWidget;

namespace NCsWidget
{
	struct CSUI_API FLibrary
	{
	public:

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
	};
}