// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/UserWidget/Text/CsTypes_UserWidget_Text.h"

#include "CsData_UserWidget_Text.generated.h"

namespace NCsUserWidget
{
	namespace NData
	{
		namespace NText
		{
			/**
			*
			*/
			struct CSUI_API IText : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			private:

				// Allow clearer names without name collisions
				struct _
				{
					using OutlineSettingsType = NCsUserWidget::NText::FOutline;
					using ShadowSettingsType = NCsUserWidget::NText::FShadow;
				};

			public:

				virtual ~IText() {}

				/**
				* Get the color of the text.
				* 
				* return Color
				*/
				virtual const FLinearColor& GetColor() const = 0;

				/**
				* Get the scale to apply to Render Transform (set via SetRenderScale(GetScale() * FVector2D::UnitVector)).
				* 
				* return Scale
				*/
				virtual const float& GetScale() const = 0;

				/**
				* Get the amount of the time to display the text.
				* 
				* return Time
				*/
				virtual const float& GetDisplayTime() const = 0;

				/**
				* Get any information describing the Outline Settings for the text.
				* 
				* return Settings
				*/
				virtual const _::OutlineSettingsType& GetOutlineSettings() const = 0;
					
				/**
				* Get any information describing the Shadow Settings for the text.
				*
				* return Settings
				*/
				virtual const _::ShadowSettingsType& GetShadowSettings() const = 0;
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSUI_API UCsData_UserWidget_Text : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSUI_API ICsData_UserWidget_Text : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

private:

	// Allow clearer names without name collisions
	struct _
	{
		using OutlineSettingsType = NCsUserWidget::NText::FOutline;
		using ShadowSettingsType = NCsUserWidget::NText::FShadow;
	};

	/**
	* Get the color of the text.
	* 
	* return Color
	*/
	virtual const FLinearColor& GetColor() const = 0;

	/**
	* Get the scale to apply to Render Transform (set via SetRenderScale(GetScale() * FVector2D::UnitVector)).
	*
	* return Scale
	*/
	virtual const float& GetScale() const = 0;

	/**
	* Get the amount of the time to display the text.
	*
	* return Time
	*/
	virtual const float& GetDisplayTime() const = 0;

	/**
	* Get any information describing the Outline Settings for the text.
	* 
	* return Settings
	*/
	virtual const _::OutlineSettingsType& GetOutlineSettings() const = 0;

	/**
	* Get any information describing the Shadow Settings for the text.
	*
	* return Settings
	*/
	virtual const _::ShadowSettingsType& GetShadowSettings() const = 0;
};