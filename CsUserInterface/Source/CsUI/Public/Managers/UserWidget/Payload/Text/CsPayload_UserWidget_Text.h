// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/UserWidget/Text/CsTypes_UserWidget_Text.h"

namespace NCsUserWidget
{
	namespace NPayload
	{
		namespace NText
		{
			/**
			*/
			struct CSUI_API IText : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IText(){}

			#define OutlineSettingsType NCsUserWidget::NText::FOutline
			#define ShadowSettingsType NCsUserWidget::NText::FShadow

				virtual const FText& GetText() const = 0;

				/**
				* Get the color of the text.
				*
				* return Color
				*/
				virtual const FLinearColor& GetColor() const = 0;

				/**
				* Get any information describing the Outline Settings for the text.
				*
				* return Settings
				*/
				virtual const OutlineSettingsType& GetOutlineSettings() const = 0;

				/**
				* Get any information describing the Shadow Settings for the text.
				*
				* return Settings
				*/
				virtual const ShadowSettingsType& GetShadowSettings() const = 0;

			#undef OutlineSettingsType
			#undef ShadowSettingsType
			};
		}
	}
}