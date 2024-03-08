// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/FX/CsTypes_FX.h"
#include "Types/CsTypes_AttachDetach.h"

class UNiagaraSystem;

// NCsFX::NParameter::IParameter
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NParameter, IParameter)
// NCsFX::NParameter::NScaled::IScaled
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NParameter, NScaled, IScaled)
// NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsFX, NParameter, NDataInterface, NSkeletalMesh, FSkeletalMeshType)

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
		#define ScaledParameterType NCsFX::NParameter::NScaled::IScaled
		#define SkeletalMeshParameterType NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType

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
			* Get the time to wait after LifeTime or Complete (completion of the FX) before gracefully
			* deallocating the FX.
			* 
			* return Death Time
			*/
			virtual const float& GetDeathTime() const = 0;

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
			virtual const FAttachmentTransformRules& GetAttachmentTransformRule() const = 0;

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
			virtual const FTransform3f& GetTransform() const = 0;

			/** 
			* Get whether RelativeLocation should be considered relative to the world, rather than the parent.
			*  NOTE: This will only be valie if GetAttachmentTransformRule().LocationRule == EAttachmentRule::KeepWorld.
			* 
			* return Whether bAbsoluteLocation is set or not
			*/
			virtual const bool& GetbAbsoluteLocation() const = 0;

			/**
			* Get whether RelativeRotation should be considered relative to the world, rather than the parent.
			*  NOTE: This will only be valie if GetAttachmentTransformRule().RotationRule == EAttachmentRule::KeepWorld.
			*
			* return Whether bAbsoluteRotation is set or not
			*/
			virtual const bool& GetbAbsoluteRotation() const = 0;

			/**
			* Get whether RelativeScale should be considered relative to the world, rather than the parent.
			*  NOTE: This will only be valie if GetAttachmentTransformRule().ScaleRule == EAttachmentRule::KeepWorld.
			*
			* return Whether bAbsoluteScale is set or not
			*/
			virtual const bool& GetbAbsoluteScale() const = 0;

			/**
			* Get whether the Transform's Scale should be applied to the FX.
			* If NOT, the object defaults to FVector3f::OneVector or just the scale of the object the FX
			* is attached to.
			* NOTE: Usually when scaling parameters, this should be FALSE.
			* 
			* return Whether the Transform's Scale should be applied to the FX or not.
			*/
			virtual const bool& ShouldApplyTransformScale() const = 0;

			/**
			*/
			virtual const TArray<ParameterType*>& GetParameters() const = 0;

			/**
			*/
			virtual const TArray<ScaledParameterType*>& GetScaledParameters() const = 0;

			virtual const TArray<SkeletalMeshParameterType*>& GetSkeletalMeshParameters() const = 0;

		#undef DeallocateMethodType
		#undef ParameterType
		#undef ScaledParameterType
		#undef SkeletalMeshParameterType
		};
	}
}