// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"
#pragma once

class USkeletalMesh;
class UMaterialInterface;

// NCsSkeletalMeshActor::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSkeletalMeshActor, NParams, IParams)

namespace NCsSkeletalMeshActor
{
	namespace NPayload
	{
		/**
		*/
		struct CSCORE_API IPayload : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		#define DeallocateMethodType NCsSkeletalMeshActor::EDeallocateMethod
		#define ParamsType NCsSkeletalMeshActor::NParams::IParams

		public:

			virtual ~IPayload(){}

			/**
			* Get the SkeletalMesh Asset to pass to the pooled SkeletalMeshActor
			*
			* return SkeletalMesh Asset
			*/
			virtual USkeletalMesh* GetSkeletalMesh() const = 0;

			/**
			* Get the Materials to apply to the SkeletalMesh asset.
			* 
			* return Materials
			*/
			virtual const TArray<UMaterialInterface*>& GetMaterials() const = 0;

			/**
			* Whether to generate Material Instance Dynamic(s) or MIDs for
			* the materials on the SkeletalMesh.
			*
			* return Whether MIDs should be generated or not.
			*/
			virtual const bool& ShouldGenerateMIDs() const = 0;

			/**
			* Get the Deallocate Method. Used to determine the conditions
			* to deallocate a SkeletalMeshActor (Lifetime, Complete, ... etc).
			* 
			* return Deallocate Method
			*/
			virtual const DeallocateMethodType& GetDeallocateMethod() const = 0;

			/**
			* Relevant if the DeallocateMethod == DeallocateMethodType::LifeTime.
			* - If a SkeletalMeshActor IS attached to a Parent object, 
			*	 LifeTime == 0.of means the SkeletalMeshActor will be deallocated immediately
			*     when the Parent object has been destroyed / deallocated.
			*	 LifeTime > 0.0f will be the time after the Parent object has been 
			*	  destroyed / deallocated to deallocate the SkeletalMeshActor.
			* - If a SkeletalMeshActor is NOT attached to a Parent object,
			*	 LifeTime == 0.0f means the Sound object will stay active forever.
			*	 LifeTime > 0.0f means the Sound will be deallocated after LifeTime amount of time after
			*     the SkeletalMeshActor has been allocated.
			* 
			* return Life Time
			*/
			virtual const float& GetLifeTime() const = 0;

			/**
			* Relevant if the SkeletalMeshActor is attached to a Parent object or when a SkeletalMeshActor is
			* allocated, the Parent field of the payload is set. If the Parent object is NULL, 
			* the SkeletalMeshActor will NOT be attached.
			*
			* return Attachment Rule
			*/
			virtual const FAttachmentTransformRules& GetAttachmentTransformRule() const = 0;

			/** 
			* Relevant if the SkeletalMeshActor is attached to a Parent object.
			* Bone or Socket to attach to.
			*
			* return Bone
			*/
			virtual const FName& GetBone() const = 0;

			/** 
			* Which of the components of Transform to apply to the SkeletalMeshActor.
			*
			* return Transform Rules (as a Bit Mask)
			*/
			virtual const int32& GetTransformRules() const = 0;

			/**
			* Get the Transform to apply to the SkeletalMeshActor. 
			* If the SkeletalMeshActor is being attached to a Parent object, the Transform is applied as a Relative Transform
			* after the attachment.
			* Else, the Transform is applied as a World Transform.
			*
			* return Transform
			*/
			virtual const FTransform3f& GetTransform() const = 0;

			/**
			* Controls whether the SkeletalMeshActor should cast an shadow or not.
			* 
			* return
			*/
			virtual const bool& CastShadow() const = 0;

			/**
			* Whether the SkeletalMeshActor receives decals.
			* 
			* return
			*/
			virtual const bool& ReceivesDecals() const = 0;

			/** 
			 * Whether to render the SkeletalMeshActor in the depth only pass.  
			 * This should generally be true for all objects, and let the renderer make decisions about whether to render objects in the depth only pass.
			 * 
			 * return
			 */
			virtual const bool& UseAsOccluder() const = 0;

			/**
			* If true, the StatisMeshComponent will be rendered in the CustomDepth pass (usually used for outlines)
			*
			* return
			*/
			virtual const bool& UseRenderCustomDepth() const = 0;

			/**
			* Optionally write this 0-255 value to the stencil buffer in CustomDepth pass (Requires project setting or r.CustomDepth == 3)
			*
			* return
			*/
			virtual const int32& GetCustomDepthStencilValue() const = 0;

			/**
			* Get whether the SkeletalMeshComponent has another component as a MasterPoseComponent.
			* 
			* return
			*/
			virtual const bool& IsSlavePoseComponent() const = 0;

			/**
			* Get the Tags to append to the SkeletalMeshActor's Tags list.
			* If the SkeletalMeshActor is being attached to a Parent object, instead
			* append to the SkeletalMeshActor's RootComponent (SkeletalMeshComponent's ComponentTags list).
			*
			* return
			*/
			virtual const TArray<FName>& GetTags() const = 0;

			/**
			*/
			virtual ParamsType* GetParams() const = 0;

		#undef DeallocateMethodType
		#undef ParamsType
		};
	}
}