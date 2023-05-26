// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/Sound/CsTypes_Sound.h"

class USoundBase;
class USoundAttenuation;

namespace NCsSound
{
	namespace NPayload
	{
		/**
		*/
		struct CSCORE_API IPayload : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IPayload(){}

			/**
			* Get the Sound Asset to pass to the pooled Sound Asset
			*
			* return Sound Asset
			*/
			virtual USoundBase* GetSound() const = 0;

			/**
			* Get the Sound Attenuation
			*
			* return Sound Attenuation
			*/
			virtual USoundAttenuation* GetSoundAttenuation() const = 0;

			/**
			* Get the Deallocate Method. Used to determine the conditions
			* to deallocate a Sound Object (Lifetime, Complete, ... etc).
			* 
			* return Deallocate Method
			*/
			virtual const EDeallocateMethod& GetDeallocateMethod() const = 0;

			/**
			* Relevant if the DeallocateMethod == EDeallocateMethod::LifeTime.
			* - If a Sound IS attached to a Parent object, 
			*	 LifeTime == 0.of means the Sound object will be deallocated immediately
			*     when the Parent object has been destroyed / deallocated.
			*	 LifeTime > 0.0f will be the time after the Parent object has been 
			*	  destroyed / deallocated to deallocate the Sound object.
			* - If a Sound is NOT attached to a Parent object,
			*	 LifeTime == 0.0f means the Sound object will stay active forever.
			*	 LifeTime > 0.0f means the Sound will be deallocated after LifeTime amount of time after
			*     the Sound object has been allocated.
			* 
			* return Life Time
			*/
			virtual const float& GetLifeTime() const = 0;

			/**
			* The amount to scale the Sound's duration. 
			* Only Valid if DeallocateMethod == EDeallocateMethod::Complete.
			* 
			* return Multiplier
			*/
			virtual const float& GetDurationMultiplier() const = 0;

			/**
			* Get the amount of time it takes to Fade In the Sound to the default Volume Multiplier.
			*
			* return Fade In Time
			*/
			virtual const float& GetFadeInTime() const = 0;

			/**
			* Relevant if the Sound is attached to a Parent object or when a Sound object is
			* allocated, the Parent field of the payload is set. If the Parent object is NULL, 
			* the Sound will NOT be attached.
			*
			* return Attachment Rule
			*/
			virtual const FAttachmentTransformRules& GetAttachmentTransformRule() const = 0;

			/** 
			* Relevant if the Sound is attached to a Parent object. 
			* Bone or Socket to attach to.
			*
			* return Bone
			*/
			virtual const FName& GetBone() const = 0;

			/** 
			* Which of the components of Transform to apply to the Sound.
			*
			* return Transform Rules (as a Bit Mask)
			*/
			virtual const int32& GetTransformRules() const = 0;

			/**
			* Get the Transform to apply to the Sound. 
			* If the Sound is being attached to a Parent object, the Transform is applied as a Relative Transform
			* after the attachment.
			* Else, the Transform is applied as a World Transform.
			*
			* return Transform
			*/
			virtual const FTransform& GetTransform() const = 0;

			/**
			* Get the amount to multiply / scale the volume of the Sound.
			*
			* return Multiplier
			*/
			virtual const float& GetVolumeMultiplier() const = 0;

			/**
			* Get the amount to multiply / scale the pitch of the Sound.
			* 
			* return Multiplier
			*/
			virtual const float& GetPitchMultiplier() const = 0;
		};
	}
}