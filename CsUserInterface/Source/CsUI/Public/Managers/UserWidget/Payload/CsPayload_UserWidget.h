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

			/**
			* Get the viewport position for the widget (set via SetPositionInViewport(GetPosition()).
			* If the UserWidget is being "attached" (following) to a Parent object, the Position is applied 
			* as an additive offset to the Location of the Parent object.
			* 
			* return Position
			*/
			virtual const FVector2D& GetPosition() const = 0;

			/** 
			* Get the order priority this widget is rendered in.  Higher values are rendered last (and so they will appear to be on top).
			* 
			* return Order
			*/
			virtual const int32& GetZOrder() const = 0;
		};
	}
}