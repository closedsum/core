// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "Types/CsTypes_UserWidget_Anim.h"
#include "Components/SlateWrapperTypes.h"

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

		#define PositionType NCsUserWidget::EPosition
		#define AnimParamsType NCsUserWidget::NAnim::NPlay::FParams

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
			* Get the way to interpret Position information for being converted to screen space.
			* 
			* return Position Type
			*/
			virtual const PositionType& GetPositionType() const = 0;

			/**
			* Get the position for the widget (set via SetPositionInViewport(GetPosition()).
			* If the UserWidget is being "attached" (following) to a Parent object, the Position is applied 
			* as an additive offset to the Location of the Parent object.
			* 
			* return Position
			*/
			virtual const FVector3f& GetPosition() const = 0;

			/**
			* Get the way to interpret Offset information for being converted to screen space.
			*
			* return Position Type
			*/
			virtual const PositionType& GetOffsetType() const = 0;

			virtual const FVector3f& GetOffset() const = 0;

			/** 
			* Get the order priority this widget is rendered in.  Higher values are rendered last (and so they will appear to be on top).
			* 
			* return Order
			*/
			virtual const int32& GetZOrder() const = 0;

			virtual const bool& HasAnimParams() const = 0;

			virtual const AnimParamsType& GetAnimParams() const = 0;

		#undef PositionType
		#undef AnimParamsType
		};
	}
}