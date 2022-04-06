// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "Components/SlateWrapperTypes.h"
#pragma once

namespace NCsUserWidget
{
	namespace NPayload
	{
		/**
		*/
		struct CSUI_API IPayload : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IPayload(){}

			virtual const ESlateVisibility& GetVisibility() const = 0;

			virtual const bool& ShouldAddToViewport() const = 0;

			/**
			* Get the scale to apply to Render Transform (set via SetRenderScale(GetScale() * FVector2D::UnitVector)).
			*
			* return Scale
			*/
			virtual const float& GetRenderScale() const = 0;

			/**
			* Get the amount of the time to display the widget.
			*
			* return Time
			*/
			virtual const float& GetLifeTime() const = 0;
		};
	}
}