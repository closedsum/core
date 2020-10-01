// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActor.h"

#pragma once

class UObject;
struct FCsInterfaceMap;
class UStaticMesh;

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
		struct CSCORE_API FImpl final : public NCsPooledObject::NPayload::IPayload,
										public NCsStaticMeshActor::NPayload::IPayload
		{
		public:

			static const FName Name;

		private:

			FCsInterfaceMap* InterfaceMap;

			bool bAllocated;

		public:

			// NCsPooledObject::NPayload::IPayload

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;
	
			FCsTime Time;

			// NCsStaticMeshActor::NPayload::IPayload

			UStaticMesh* Mesh;

			ECsStaticMeshActorDeallocateMethod DeallocateMethod;

			float LifeTime;
	
			ECsAttachmentTransformRules AttachmentTransformRules;

			FName Bone;

			int32 TransformRules;

			FTransform Transform;

		public:

			FImpl();
			~FImpl();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
			{
				return InterfaceMap;
			}

		#pragma endregion ICsGetInterfaceMap

		// NCsPooledObject::NPayload::IPayload
		#pragma region
		public:

			FORCEINLINE const bool& IsAllocated() const
			{
				return bAllocated;
			}

			FORCEINLINE UObject* GetInstigator() const
			{
				return Instigator;
			}

			FORCEINLINE UObject* GetOwner() const
			{
				return Owner;
			}

			FORCEINLINE UObject* GetParent() const
			{
				return Parent;
			}

			FORCEINLINE const FCsTime& GetTime() const
			{
				return Time;
			}

			FORCEINLINE void Allocate()
			{
				bAllocated = true;
			}

			void Reset();

		#pragma endregion NCsPooledObject::NPayload::IPayload

		public:

			template<typename T>
			FORCEINLINE T* GetInstigator() const
			{
				return Cast<T>(GetInstigator());
			}

			template<typename T>
			FORCEINLINE T* GetOwner() const
			{
				return Cast<T>(GetOwner());
			}

			template<typename T>
			FORCEINLINE T* GetParent() const
			{
				return Cast<T>(GetParent());
			}

		// NCsStaticMeshActor::NPayload::IPayload
		#pragma region
		public:

			FORCEINLINE UStaticMesh* GetStaticMesh() const 
			{
				return Mesh;
			}

			FORCEINLINE const ECsStaticMeshActorDeallocateMethod& GetDeallocateMethod() const
			{
				return DeallocateMethod;
			}

			FORCEINLINE const float& GetLifeTime() const
			{
				return LifeTime;
			}

			FORCEINLINE const ECsAttachmentTransformRules& GetAttachmentTransformRule() const
			{
				return AttachmentTransformRules;
			}

			FORCEINLINE const FName& GetBone() const
			{
				return Bone;
			}

			FORCEINLINE const int32& GetTransformRules() const
			{
				return TransformRules;
			}

			FORCEINLINE const FTransform& GetTransform() const
			{
				return Transform;
			}

		#pragma endregion NCsStaticMeshActor::NPayload::IPayload
		};
	}
}