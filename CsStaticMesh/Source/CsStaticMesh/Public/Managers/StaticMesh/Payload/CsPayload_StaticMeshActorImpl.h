// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActor.h"

class UObject;
struct FCsInterfaceMap;
class UStaticMesh;
class UMaterialInterface;

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
		namespace NImpl
		{
			using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
			using PayloadType = NCsStaticMeshActor::NPayload::IPayload;

			struct CSSTATICMESH_API FImpl final : public PooledPayloadType,
												  public PayloadType
			{
			public:

				static const FName Name;

			private:

				using DeallocateMethodType = NCsStaticMeshActor::EDeallocateMethod;

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

				// PayloadType (NCsStaticMeshActor::NPayload::IPayload)

				UStaticMesh* Mesh;

				TArray<UMaterialInterface*> Materials;

				bool bGenerateMIDs;

				DeallocateMethodType DeallocateMethod;

				float LifeTime;
	
				FAttachmentTransformRules AttachmentTransformRules;

				FName Bone;

				int32 TransformRules;

				FTransform Transform;

				bool bCastShadow;

				bool bReceivesDecals;

				bool bUseAsOccluder;

				bool bRenderCustomDepth;

				int32 CustomDepthStencilValue;

				TArray<FName> Tags;

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

			// PayloadType (NCsStaticMeshActor::NPayload::IPayload)
			#pragma region
			public:

				FORCEINLINE UStaticMesh* GetStaticMesh() const { return Mesh; }
				FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return Materials; }
				FORCEINLINE const bool& ShouldGenerateMIDs() const { return bGenerateMIDs; }
				FORCEINLINE const DeallocateMethodType& GetDeallocateMethod() const { return DeallocateMethod; }
				FORCEINLINE const float& GetLifeTime() const { return LifeTime; }
				FORCEINLINE const FAttachmentTransformRules& GetAttachmentTransformRule() const { return AttachmentTransformRules; }
				FORCEINLINE const FName& GetBone() const { return Bone; }
				FORCEINLINE const int32& GetTransformRules() const { return TransformRules; }
				FORCEINLINE const FTransform& GetTransform() const { return Transform; }
				FORCEINLINE const bool& CastShadow() const { return bCastShadow; }
				FORCEINLINE const bool& ReceivesDecals() const { return bReceivesDecals; }
				FORCEINLINE const bool& UseAsOccluder() const { return bUseAsOccluder; }
				FORCEINLINE const bool& UseRenderCustomDepth() const { return bRenderCustomDepth; }
				FORCEINLINE const int32& GetCustomDepthStencilValue() const { return CustomDepthStencilValue; }
				FORCEINLINE const TArray<FName>& GetTags() const { return Tags; }

			#pragma endregion PayloadType (NCsStaticMeshActor::NPayload::IPayload)
			};
		}
	}
}