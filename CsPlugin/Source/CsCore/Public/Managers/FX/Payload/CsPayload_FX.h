// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/FX/CsTypes_FX.h"
#include "Types/CsTypes_AttachDetach.h"
#pragma once

class UNiagaraSystem;

// NCsFX::NParameter::IParameter
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NParameter, IParameter)

namespace NCsFX
{
	namespace NPayload
	{
		/**
		*/
		struct CSCORE_API IPayload : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		#define DeallocateMethodType NCsFX::EDeallocateMethod
		#define ParameterType NCsFX::NParameter::IParameter

		public:

			virtual ~IPayload(){}

			/**
			* Get the FX System to pass to the pooled FX object
			*
			* return FX System
			*/
			virtual UNiagaraSystem* GetFXSystem() const = 0;

			/**
			* Get the Deallocate Method. Used to determine the conditions
			* to deallocate an FX Object (Lifetime, Complete, ... etc).
			* 
			* return Deallocate Method
			*/
			virtual const DeallocateMethodType& GetDeallocateMethod() const = 0;

			/**
			* Relevant if the DeallocateMethod == DeallocateMethodType::LifeTime.
			* - If an FX IS attached to a Parent object, 
			*	 LifeTime == 0.0f means the FX object will be deallocated immediately
			*     when the Parent object has been destroyed / deallocated.
			*	 LifeTime > 0.0f will be the time after the Parent object has been 
			*	  destroyed / deallocated to deallocate the FX object.
			* - If an FX is NOT attached to a Parent object,
			*	 LifeTime == 0.0f means the FX object will stay active forever.
			*	 LifeTime > 0.0f means the FX will be deallocated after LifeTime amount of time after
			*     the FX object has been allocated.
			* 
			* return Life Time
			*/
			virtual const float& GetLifeTime() const = 0;

			/**
			* Whether to Hide the FX when FX->GetCache()->QueueDeallocate() is called.
			* The main purpose of this is for FX that should be deallocated "immediately" after
			* QueueDeallocate() is called. Normally, the FX is allowed to "complete" / deactivate
			* gracefully.
			* 
			* return Whether to Hide the FX on QueueDeallocate() or not
			*/
			virtual const bool& ShouldHideOnQueueDeallocate() const = 0;

			/**
			* Relevant if the FX is attached to a Parent object or when an FX object is
			* allocated, the Parent field of the payload is set. If the Parent object is NULL, 
			* the FX will NOT be attached.
			*
			* return Attachment Rule
			*/
			virtual const ECsAttachmentTransformRules& GetAttachmentTransformRule() const = 0;

			/** 
			* Relevant if the FX is attached to a Parent object.
			* Bone or Socket to attach to.
			*
			* return Bone
			*/
			virtual const FName& GetBone() const = 0;

			/** 
			* Which of the components of Transform to apply to the FX.
			*
			* return Transform Rules (as a Bit Mask)
			*/
			virtual const int32& GetTransformRules() const = 0;

			/**
			* Get the Transform to apply to the FX. 
			* If the FX is being attached to a Parent object, the Transform is applied as a Relative Transform
			* after the attachment.
			* Else, the Transform is applied as a World Transform.
			*
			* return Transform
			*/
			virtual const FTransform& GetTransform() const = 0;

			/**
			*/
			virtual const TArray<ParameterType*>& GetParameters() const = 0;

		#undef DeallocateMethodType
		#undef ParameterType
		};
	}
}