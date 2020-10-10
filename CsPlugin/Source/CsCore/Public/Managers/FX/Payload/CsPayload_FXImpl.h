// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/FX/Payload/CsPayload_FX.h"

#pragma once

class UObject;
struct FCsInterfaceMap;
class UNiagaraSystem;

namespace NCsFX
{
	namespace NPayload
	{
#define PooledPayloadType NCsPooledObject::NPayload::IPayload
#define FXPayloadType NCsFX::NPayload::IPayload

		/**
		*/
		struct CSCORE_API FImpl final : public PooledPayloadType,
										public FXPayloadType
		{
		public:

			static const FName Name;

		private:

			FCsInterfaceMap* InterfaceMap;

			bool bAllocated;

		public:

			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;
	
			FCsTime Time;

			// FXPayloadType (NCsFX::Payload::IPayload)

			UNiagaraSystem* FXSystem;

			ECsFXDeallocateMethod DeallocateMethod;

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

		// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		#pragma region
		public:

			FORCEINLINE const bool& IsAllocated() const { return bAllocated; }
			FORCEINLINE UObject* GetInstigator() const { return Instigator; }
			FORCEINLINE UObject* GetOwner() const { return Owner; }
			FORCEINLINE UObject* GetParent() const { return Parent; }
			FORCEINLINE const FCsTime& GetTime() const { return Time; }
			FORCEINLINE void Allocate(){ bAllocated = true; }

			void Reset();

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)

		public:

			template<typename T>
			FORCEINLINE T* GetInstigator() const { return Cast<T>(GetInstigator()); }

			template<typename T>
			FORCEINLINE T* GetOwner() const { return Cast<T>(GetOwner()); }

			template<typename T>
			FORCEINLINE T* GetParent() const { return Cast<T>(GetParent()); }

		// FXPayloadType (NCsFX::Payload::IPayload)
		#pragma region
		public:

			FORCEINLINE UNiagaraSystem* GetFXSystem() const { return FXSystem; }
			FORCEINLINE const ECsFXDeallocateMethod& GetDeallocateMethod() const { return DeallocateMethod; }
			FORCEINLINE const float& GetLifeTime() const { return LifeTime; }
			FORCEINLINE const ECsAttachmentTransformRules& GetAttachmentTransformRule() const { return AttachmentTransformRules; }
			FORCEINLINE const FName& GetBone() const { return Bone; }
			FORCEINLINE const int32& GetTransformRules() const { return TransformRules; }
			FORCEINLINE const FTransform& GetTransform() const { return Transform; }

		#pragma endregion FXPayloadType (NCsFX::Payload::IPayload)
		};

#undef PooledPayloadType
#undef FXPayloadType
	}
}