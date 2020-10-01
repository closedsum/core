// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"
#pragma once

class UStaticMesh;

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
		/**
		*/
		struct CSCORE_API IPayload : virtual public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IPayload(){}

			/**
			* Get the StaticMesh Asset to pass to the pooled StaticMeshActor
			*
			* return StaticMesh Asset
			*/
			virtual UStaticMesh* GetStaticMesh() const = 0;

			/**
			* Get the Deallocate Method. Used to determine the conditions
			* to deallocate a StaticMeshActor (Lifetime, Complete, ... etc).
			* 
			* return Deallocate Method
			*/
			virtual const ECsStaticMeshActorDeallocateMethod& GetDeallocateMethod() const = 0;

			/**
			* Relevant if the DeallocateMethod == ECsStaticMeshActorDeallocateMethod::LifeTime.
			* - If a StaticMeshActor IS attached to a Parent object, 
			*	 LifeTime == 0.of means the StaticMeshActor will be deallocated immediately
			*     when the Parent object has been destroyed / deallocated.
			*	 LifeTime > 0.0f will be the time after the Parent object has been 
			*	  destroyed / deallocated to deallocate the StaticMeshActor.
			* - If a StaticMeshActor is NOT attached to a Parent object,
			*	 LifeTime == 0.0f means the Sound object will stay active forever.
			*	 LifeTime > 0.0f means the Sound will be deallocated after LifeTime amount of time after
			*     the StaticMeshActor has been allocated.
			* 
			* return Life Time
			*/
			virtual const float& GetLifeTime() const = 0;

			/**
			* Relevant if the StaticMeshActor is attached to a Parent object or when a StaticMeshActor is
			* allocated, the Parent field of the payload is set. If the Parent object is NULL, 
			* the StaticMeshActor will NOT be attached.
			*
			* return Attachment Rule
			*/
			virtual const ECsAttachmentTransformRules& GetAttachmentTransformRule() const = 0;

			/** 
			* Relevant if the StaticMeshActor is attached to a Parent object.
			* Bone or Socket to attach to.
			*
			* return Bone
			*/
			virtual const FName& GetBone() const = 0;

			/** 
			* Which of the components of Transform to apply to the StaticMeshActor.
			*
			* return Transform Rules (as a Bit Mask)
			*/
			virtual const int32& GetTransformRules() const = 0;

			/**
			* Get the Transform to apply to the StaticMeshActor. 
			* If the StaticMeshActor is being attached to a Parent object, the Transform is applied as a Relative Transform
			* after the attachment.
			* Else, the Transform is applied as a World Transform.
			*
			* return Transform
			*/
			virtual const FTransform& GetTransform() const = 0;
		};
	}
}