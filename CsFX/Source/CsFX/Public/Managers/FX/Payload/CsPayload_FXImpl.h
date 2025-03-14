// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interface
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/FX/Payload/CsPayload_FX.h"
// Types
#include "CsMacro_Cached.h"

class UObject;
struct FCsInterfaceMap;
class UNiagaraSystem;

// NCsFX::NParameter::IParameter
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NParameter, IParameter)
// NCsFX::NParameter::NScaled::IScaled
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NParameter, NScaled, IScaled)
// NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsFX, NParameter, NDataInterface, NSkeletalMesh, FSkeletalMeshType)

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(NCsFX, NPayload, NImpl, Impl)

namespace NCsFX
{
	namespace NPayload
	{
		namespace NImpl
		{
			using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
			using PayloadType = NCsFX::NPayload::IPayload;

			/**
			*/
			struct CSFX_API FImpl final : public PooledPayloadType,
										  public PayloadType
			{
			public:

				static const FName Name;

				using DeallocateMethodType = NCsFX::EDeallocateMethod;
				using ParameterType = NCsFX::NParameter::IParameter;
				using ScaledParameterType = NCsFX::NParameter::NScaled::IScaled;
				using SkeletalMeshParameterType = NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType;

				CS_USING_CACHED_FUNCTION_NAME_NESTED_3(NCsFX, NPayload, NImpl, Impl);

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

				FAttachmentTransformRules AttachmentTransformRules;

				FName Bone;

				int32 TransformRules;

				FTransform Transform;

				bool bAbsoluteLocation;

				bool bAbsoluteRotation;

				bool bAbsoluteScale;

				bool bApplyTransformScale;

				TArray<ParameterType*> Parameters;

				TArray<ScaledParameterType*> ScaledParameters;

				TArray<SkeletalMeshParameterType*> SkeletalMeshParameters;

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

			// PayloadType (NCsFX::Payload::IPayload)
			#pragma region
			public:

				FORCEINLINE UNiagaraSystem* GetFXSystem() const { return FXSystem; }
				FORCEINLINE const DeallocateMethodType& GetDeallocateMethod() const { return DeallocateMethod; }
				FORCEINLINE const float& GetLifeTime() const { return LifeTime; }
				FORCEINLINE const float& GetDeathTime() const { return DeathTime; }
				FORCEINLINE const bool& ShouldHideOnQueueDeallocate() const { return bHideOnQueueDeallocate; }
				FORCEINLINE const FAttachmentTransformRules& GetAttachmentTransformRule() const { return AttachmentTransformRules; }
				FORCEINLINE const FName& GetBone() const { return Bone; }
				FORCEINLINE const int32& GetTransformRules() const { return TransformRules; }
				FORCEINLINE const FTransform& GetTransform() const { return Transform; }
				FORCEINLINE const bool& GetbAbsoluteLocation() const { return bAbsoluteLocation; }
				FORCEINLINE const bool& GetbAbsoluteRotation() const { return bAbsoluteRotation; }
				FORCEINLINE const bool& GetbAbsoluteScale() const { return bAbsoluteScale; }
				FORCEINLINE const bool& ShouldApplyTransformScale() const { return bApplyTransformScale; }
				FORCEINLINE const TArray<ParameterType*>& GetParameters() const { return Parameters; }
				FORCEINLINE const TArray<ScaledParameterType*>& GetScaledParameters() const { return ScaledParameters; }
				FORCEINLINE const TArray<SkeletalMeshParameterType*>& GetSkeletalMeshParameters() const { return SkeletalMeshParameters; }

			#pragma endregion PayloadType (NCsFX::Payload::IPayload)
			};
		}
	}
}

using CsFXPayloadImplType = NCsFX::NPayload::NImpl::FImpl;