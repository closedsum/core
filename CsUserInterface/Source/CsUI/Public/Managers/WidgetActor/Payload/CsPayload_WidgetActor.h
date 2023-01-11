// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/WidgetActor/Types/CsTypes_WidgetActor.h"
#include "Managers/UserWidget/CsTypes_UserWidget.h"

class UUserWidget;

namespace NCsWidgetActor
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

			/**
			* Get the UserWidget
			*
			* return UserWidget
			*/
			virtual UUserWidget* GetUserWidget() const = 0;

			/**
			* Get the Deallocate Method. Used to determine the conditions
			* to deallocate a Widget Actor, object that implements the 
			* interface: ICsWidgetActor, (Lifetime, ... etc).
			* 
			* return Deallocate Method
			*/
			virtual const ECsWidgetActorDeallocateMethod& GetDeallocateMethod() const = 0;

			/**
			* Relevant if the DeallocateMethod == ECsWidgetActorDeallocateMethod::LifeTime.
			* - If an Widget Actor IS attached to a Parent object, 
			*	 LifeTime == 0.0f means the Widget Actor will be deallocated immediately
			*     when the Parent object has been destroyed / deallocated.
			*	 LifeTime > 0.0f will be the time after the Parent object has been 
			*	  destroyed / deallocated to deallocate the Widget Actor.
			* - If a Widget Actor is NOT attached to a Parent object,
			*	 LifeTime == 0.0f means the Widget Actor will stay active forever.
			*	 LifeTime > 0.0f means the Widget Actor will be deallocated after LifeTime amount of time after
			*     the Widget Actor has been allocated.
			* 
			* return Life Time
			*/
			virtual const float& GetLifeTime() const = 0;

			/**
			* Relevant if the WidgetActor is attached to a Parent object or when an WidgetActor is
			* allocated, the Parent field of the payload is set. If the Parent object is NULL, 
			* the WidgetActor will NOT be attached.
			*
			* return Attachment Rule
			*/
			virtual const ECsAttachmentTransformRules& GetAttachmentTransformRule() const = 0;

			/** 
			* Relevant if the WidgetActor is attached to a Parent object.
			* Bone or Socket to attach to.
			*
			* return Bone
			*/
			virtual const FName& GetBone() const = 0;

			/** 
			* Which of the components of Transform to apply to the WidgetActor.
			*
			* return Transform Rules (as a Bit Mask)
			*/
			virtual const int32& GetTransformRules() const = 0;

			/**
			* Get the Transform to apply to the FX. 
			* If the WidgetActor is being attached to a Parent object, the Transform is applied as a Relative Transform
			* after the attachment.
			* Else, the Transform is applied as a World Transform.
			*
			* return Transform
			*/
			virtual const FTransform& GetTransform() const = 0;
		};
	}
}