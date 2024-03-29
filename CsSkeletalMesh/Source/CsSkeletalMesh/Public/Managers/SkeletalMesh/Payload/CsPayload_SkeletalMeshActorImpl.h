// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActor.h"

class UObject;
struct FCsInterfaceMap;
class USkeletalMesh;
class UMaterialInterface;

// NCsSkeletalMeshActor::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSkeletalMeshActor, NParams, IParams)

namespace NCsSkeletalMeshActor
{
	namespace NPayload
	{
	#define PooledPayloadType NCsPooledObject::NPayload::IPayload
	#define SkeletalMeshPayloadType NCsSkeletalMeshActor::NPayload::IPayload

		struct CSSKELETALMESH_API FImpl final : public PooledPayloadType,
										public SkeletalMeshPayloadType
		{
		public:

			static const FName Name;

		#define DeallocateMethodType NCsSkeletalMeshActor::EDeallocateMethod
		#define ParamsType NCsSkeletalMeshActor::NParams::IParams

		private:

			FCsInterfaceMap* InterfaceMap;

			bool bAllocated;

		public:

			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

			NCsPooledObject::EUpdate UpdateType;

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;
	
			FCsTime Time;

			uint32 PreserveChangesFromDefaultMask;

			// SkeletalMeshPayloadType (NCsSkeletalMeshActor::NPayload::IPayload)

			USkeletalMesh* Mesh;

			TArray<UMaterialInterface*> Materials;

			bool bGenerateMIDs;

			DeallocateMethodType DeallocateMethod;

			float LifeTime;
	
			FAttachmentTransformRules AttachmentTransformRules;

			FName Bone;

			int32 TransformRules;

			FTransform3f Transform;

			bool bCastShadow;

			bool bReceivesDecals;

			bool bUseAsOccluder;

			bool bRenderCustomDepth;

			int32 CustomDepthStencilValue;

			bool bSlavePoseComponent;

			TArray<FName> Tags;

			ParamsType* Params;

		public:

			FImpl();
			~FImpl();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		#pragma region
		public:

			FORCEINLINE const bool& IsAllocated() const { return bAllocated; }
			FORCEINLINE const NCsPooledObject::EUpdate& GetUpdateType() const { return UpdateType; }
			FORCEINLINE UObject* GetInstigator() const { return Instigator; }
			FORCEINLINE UObject* GetOwner() const { return Owner; }
			FORCEINLINE UObject* GetParent() const { return Parent; }
			FORCEINLINE const FCsTime& GetTime() const { return Time; }
			FORCEINLINE void Allocate() { bAllocated = true; }

			void Reset();

			FORCEINLINE const uint32& GetPreserveChangesFromDefaultMask() const { return PreserveChangesFromDefaultMask; }

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)

		public:

			template<typename T>
			FORCEINLINE T* GetInstigator() const { return Cast<T>(GetInstigator()); }

			template<typename T>
			FORCEINLINE T* GetOwner() const { return Cast<T>(GetOwner()); }

			template<typename T>
			FORCEINLINE T* GetParent() const { return Cast<T>(GetParent()); }

			FORCEINLINE void SetMaterials(const TArray<UMaterialInterface*>& InMaterials)
			{
				const int32 Count = InMaterials.Num();

				Materials.Reset(FMath::Max(Materials.Max(), Count));

				for (UMaterialInterface* Material : InMaterials)
				{
					Materials.Add(Material);
				}
			}

		// SkeletalMeshPayloadType (NCsSkeletalMeshActor::NPayload::IPayload)
		#pragma region
		public:

			FORCEINLINE USkeletalMesh* GetSkeletalMesh() const { return Mesh; }
			FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return Materials; }
			FORCEINLINE const bool& ShouldGenerateMIDs() const { return bGenerateMIDs; }
			FORCEINLINE const DeallocateMethodType& GetDeallocateMethod() const { return DeallocateMethod; }
			FORCEINLINE const float& GetLifeTime() const { return LifeTime; }
			FORCEINLINE const FAttachmentTransformRules& GetAttachmentTransformRule() const { return AttachmentTransformRules; }
			FORCEINLINE const FName& GetBone() const { return Bone; }
			FORCEINLINE const int32& GetTransformRules() const { return TransformRules; }
			FORCEINLINE const FTransform3f& GetTransform() const { return Transform; }
			FORCEINLINE const bool& CastShadow() const { return bCastShadow; }
			FORCEINLINE const bool& ReceivesDecals() const { return bReceivesDecals; }
			FORCEINLINE const bool& UseAsOccluder() const { return bUseAsOccluder; }
			FORCEINLINE const bool& UseRenderCustomDepth() const { return bRenderCustomDepth; }
			FORCEINLINE const int32& GetCustomDepthStencilValue() const { return CustomDepthStencilValue; }
			FORCEINLINE const bool& IsSlavePoseComponent() const { return bSlavePoseComponent; }
			FORCEINLINE const TArray<FName>& GetTags() const { return Tags; }
			FORCEINLINE ParamsType* GetParams() const { return Params; }

		#pragma endregion SkeletalMeshPayloadType (NCsSkeletalMeshActor::NPayload::IPayload)

		#undef DeallocateMethodType
		#undef ParamsType
		};

	#undef PooledPayloadType
	#undef SkeletalMeshPayloadType
	}
}