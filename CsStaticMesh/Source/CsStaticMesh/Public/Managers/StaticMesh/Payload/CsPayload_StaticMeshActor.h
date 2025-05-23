// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"

class UStaticMesh;

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
		/**
		*/
		struct CSSTATICMESH_API IPayload : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		private:

			// Allow clearer names without name collisions
			struct _
			{
				using DeallocateMethodType = NCsStaticMeshActor::EDeallocateMethod;
			};

		public:

			virtual ~IPayload(){}

			/**
			* Get the StaticMesh Asset to pass to the pooled StaticMeshActor
			*
			* return StaticMesh Asset
			*/
			virtual UStaticMesh* GetStaticMesh() const = 0;

			/**
			* Get the Materials to apply to the StaticMesh asset.
			*
			* return Materials
			*/
			virtual const TArray<UMaterialInterface*>& GetMaterials() const = 0;

			/**
			* Whether to generate Material Instance Dynamic(s) or MIDs for 
			* the materials on the StaticMesh.
			* 
			* return Whether MIDs should be generated or not.
			*/
			virtual const bool& ShouldGenerateMIDs() const = 0;

			/**
			* Get the Deallocate Method. Used to determine the conditions
			* to deallocate a StaticMeshActor (Lifetime, Complete, ... etc).
			* 
			* return Deallocate Method
			*/
			virtual const _::DeallocateMethodType& GetDeallocateMethod() const = 0;

			/**
			* Relevant if the DeallocateMethod == DeallocateMethodType::LifeTime.
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
			virtual const FAttachmentTransformRules& GetAttachmentTransformRule() const = 0;

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

			/**
			* Controls whether the StaticMeshActor should cast an shadow or not.
			*
			* return
			*/
			virtual const bool& CastShadow() const = 0;

			/**
			* Whether the StaticMeshActor receives decals.
			*
			* return
			*/
			virtual const bool& ReceivesDecals() const = 0;

			/**
			* Whether to render the StaticMeshActor in the depth only pass.
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
			* Get the Tags to append to the StaticMeshActor's Tags list.
			* If the StaticMeshActor is being attached to a Parent object, instead
			* append to the StaticMeshActor's RootComponent (StaticMeshComponent's ComponentTags list).
			* 
			* return
			*/
			virtual const TArray<FName>& GetTags() const = 0;
		};
	}
}