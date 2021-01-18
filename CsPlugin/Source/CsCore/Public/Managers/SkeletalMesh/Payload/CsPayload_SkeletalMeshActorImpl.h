// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActor.h"

#pragma once

class UObject;
struct FCsInterfaceMap;
class USkeletalMesh;

// NCsSkeletalMeshActor::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSkeletalMeshActor, NParams, IParams)

namespace NCsSkeletalMeshActor
{
	namespace NPayload
	{
	#define PooledPayloadType NCsPooledObject::NPayload::IPayload
	#define SkeletalMeshPayloadType NCsSkeletalMeshActor::NPayload::IPayload

		struct CSCORE_API FImpl final : public PooledPayloadType,
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

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;
	
			FCsTime Time;

			// SkeletalMeshPayloadType (NCsSkeletalMeshActor::NPayload::IPayload)

			USkeletalMesh* Mesh;

			DeallocateMethodType DeallocateMethod;

			float LifeTime;
	
			ECsAttachmentTransformRules AttachmentTransformRules;

			FName Bone;

			int32 TransformRules;

			FTransform Transform;

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
			FORCEINLINE UObject* GetInstigator() const { return Instigator; }
			FORCEINLINE UObject* GetOwner() const { return Owner; }
			FORCEINLINE UObject* GetParent() const { return Parent; }
			FORCEINLINE const FCsTime& GetTime() const { return Time; }
			FORCEINLINE void Allocate() { bAllocated = true; }

			void Reset();

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)

		public:

			template<typename T>
			FORCEINLINE T* GetInstigator() const { return Cast<T>(GetInstigator()); }

			template<typename T>
			FORCEINLINE T* GetOwner() const { return Cast<T>(GetOwner()); }

			template<typename T>
			FORCEINLINE T* GetParent() const { return Cast<T>(GetParent()); }

		// SkeletalMeshPayloadType (NCsSkeletalMeshActor::NPayload::IPayload)
		#pragma region
		public:

			FORCEINLINE USkeletalMesh* GetSkeletalMesh() const { return Mesh; }
			FORCEINLINE const DeallocateMethodType& GetDeallocateMethod() const { return DeallocateMethod; }
			FORCEINLINE const float& GetLifeTime() const { return LifeTime; }
			FORCEINLINE const ECsAttachmentTransformRules& GetAttachmentTransformRule() const { return AttachmentTransformRules; }
			FORCEINLINE const FName& GetBone() const { return Bone; }
			FORCEINLINE const int32& GetTransformRules() const { return TransformRules; }
			FORCEINLINE const FTransform& GetTransform() const { return Transform; }
			FORCEINLINE ParamsType* GetParams() const { return Params; }

		#pragma endregion SkeletalMeshPayloadType (NCsSkeletalMeshActor::NPayload::IPayload)

		#undef DeallocateMethodType
		#undef ParamsType
		};

	#undef PooledPayloadType
	#undef SkeletalMeshPayloadType
	}
}