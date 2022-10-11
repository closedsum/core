// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/FX/Payload/CsPayload_FX.h"

#pragma once

class UObject;
struct FCsInterfaceMap;
class UNiagaraSystem;

// NCsFX::NParameter::IParameter
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NParameter, IParameter)
// NCsFX::NParameter::NScaled::IScaled
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NParameter, NScaled, IScaled)

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

		#define DeallocateMethodType NCsFX::EDeallocateMethod
		#define ParameterType NCsFX::NParameter::IParameter
		#define ScaledParameterType NCsFX::NParameter::NScaled::IScaled

		private:

			UObject* Root;

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

			bool bAllocated;

		public:

			NCsPooledObject::EUpdate UpdateType;

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;
	
			FCsTime Time;

			uint32 PreserveChangesFromDefaultMask;

			// FXPayloadType (NCsFX::Payload::IPayload)

			UNiagaraSystem* FXSystem;

			DeallocateMethodType DeallocateMethod;

			float LifeTime;
	
			float DeathTime;

			bool bHideOnQueueDeallocate;

			ECsAttachmentTransformRules AttachmentTransformRules;

			FName Bone;

			int32 TransformRules;

			FTransform Transform;

			bool bApplyTransformScale;

			TArray<ParameterType*> Parameters;

			TArray<ScaledParameterType*> ScaledParameters;

		public:

			FImpl();
			~FImpl();

			FORCEINLINE void SetRoot(UObject* InRoot){ Root = InRoot; }
			FORCEINLINE UObject* GetRoot() const { return Root; }

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

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
			FORCEINLINE void Allocate(){ bAllocated = true; }

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

		// FXPayloadType (NCsFX::Payload::IPayload)
		#pragma region
		public:

			FORCEINLINE UNiagaraSystem* GetFXSystem() const { return FXSystem; }
			FORCEINLINE const DeallocateMethodType& GetDeallocateMethod() const { return DeallocateMethod; }
			FORCEINLINE const float& GetLifeTime() const { return LifeTime; }
			FORCEINLINE const float& GetDeathTime() const { return DeathTime; }
			FORCEINLINE const bool& ShouldHideOnQueueDeallocate() const { return bHideOnQueueDeallocate; }
			FORCEINLINE const ECsAttachmentTransformRules& GetAttachmentTransformRule() const { return AttachmentTransformRules; }
			FORCEINLINE const FName& GetBone() const { return Bone; }
			FORCEINLINE const int32& GetTransformRules() const { return TransformRules; }
			FORCEINLINE const FTransform& GetTransform() const { return Transform; }
			FORCEINLINE const bool& ShouldApplyTransformScale() const { return bApplyTransformScale; }
			FORCEINLINE const TArray<ParameterType*>& GetParameters() const { return Parameters; }
			FORCEINLINE const TArray<ScaledParameterType*>& GetScaledParameters() const { return ScaledParameters; }

		#pragma endregion FXPayloadType (NCsFX::Payload::IPayload)

		#undef DeallocateMethodType
		#undef ParameterType
		#undef ScaledParameterType
		};

	#undef PooledPayloadType
	#undef FXPayloadType
	}
}