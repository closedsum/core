// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "StaticMesh/Instanced/CsLibrary_InstancedStaticMeshComponent.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Component
#include "Components/InstancedStaticMeshComponent.h"
// Engine
#include "Engine/InstancedStaticMesh.h"

namespace NCsStaticMesh
{
	namespace NInstanced
	{
		namespace NComponent
		{
			void FLibrary::InitRenderDataChecked(const FString& Context, UInstancedStaticMeshComponent* Component, const int32& NumInstances, const int32& NumCustomDataFloats)
			{
				CS_IS_PENDING_KILL_CHECKED(Component)
				CS_IS_INT_GREATER_THAN_CHECKED(NumInstances, 0)
				CS_IS_INT_GREATER_THAN_CHECKED(NumCustomDataFloats, 0)

				Component->NumCustomDataFloats = NumCustomDataFloats;

				// Update PerInstanceSMData
				Component->PerInstanceSMData.Reset(NumInstances);
				Component->PerInstanceSMData.AddDefaulted(1);
				// Update PerInstanceSMCustomData
				Component->PerInstanceSMCustomData.Reset(NumInstances * NumCustomDataFloats);
				Component->PerInstanceSMCustomData.AddDefaulted(NumCustomDataFloats);

				// Setup Data
				FStaticMeshInstanceData Data = FStaticMeshInstanceData(GVertexElementTypeSupport.IsSupported(VET_Half2));
	
				Data.AllocateInstances(NumInstances, NumCustomDataFloats, EResizeBufferFlags::AllowSlackOnReduce, true);

				FVector2D LightmapUVBias  = FVector2D(-1.0f, -1.0f);
				FVector2D ShadowmapUVBias = FVector2D(-1.0f, -1.0f);

				for (int32 I = 0; I < NumInstances; ++I)
				{
					Data.SetInstance(I, FMatrix::Identity, 0.0f, LightmapUVBias, ShadowmapUVBias);

					for (int32 J = 0; J < NumCustomDataFloats; ++J)
					{
						Data.SetInstanceCustomData(I, J, 0.0f);
					}
				}

				Component->InitPerInstanceRenderData(true, &Data);
				Component->MarkRenderStateDirty();
			}

			bool FLibrary::FUpdateRenderDataChecked::FPayload::IsValidChecked(const FString& Context) const 
			{
				return true;
			}

			#define PayloadType NCsStaticMesh::NInstanced::NComponent::FLibrary::FUpdateRenderDataChecked::FPayload
			void FLibrary::UpdateRenderDataChecked(const FString& Context, const PayloadType& Payload)
			{
			#undef PayloadType

				CS_IS_VALID_CHECKED(Payload);

				UInstancedStaticMeshComponent* Component = Payload.GetComponent();
				const int32& NumInstances				 = Payload.GetNumInstances();
				const int32& NumCustomDataFloats		 = Payload.GetNumCustomDataFloats();
				const TArray<FMatrix>& Transforms		 = Payload.GetTransforms();
				const TArray<float>& CustomDatas		 = Payload.GetCustomDatas();

				// Update PerInstanceSMData
				{
					const int32 Count = Component->PerInstanceSMData.Num();

					if (Count < NumInstances)
					{
						Component->PerInstanceSMData.AddDefaulted(NumInstances - Count);
					}
					else
					{
						Component->PerInstanceSMData.RemoveAt(NumInstances, Count - NumInstances, false);
					}
				}
				// Update PerInstanceSMCustomData
				{
					const int32 Count = Component->PerInstanceSMCustomData.Num();
					const int32 Size  = NumInstances * NumCustomDataFloats;

					if (Count < Size)
					{
						Component->PerInstanceSMCustomData.AddDefaulted(Size - Count);
					}
					else
					{
						Component->PerInstanceSMCustomData.RemoveAt(Size, Count - Size, false);
					}
				}

				// Setup Data
				FStaticMeshInstanceData Data = FStaticMeshInstanceData(GVertexElementTypeSupport.IsSupported(VET_Half2));
	
				Data.AllocateInstances(NumInstances, NumCustomDataFloats, EResizeBufferFlags::AllowSlackOnReduce, true);

				FVector2D LightmapUVBias  = FVector2D(-1.0f, -1.0f);
				FVector2D ShadowmapUVBias = FVector2D(-1.0f, -1.0f);

				for (int32 I = 0; I < NumInstances; ++I)
				{
					const FMatrix& Transform = Transforms[I];

					Data.SetInstance(I, Transform, 0.0f, LightmapUVBias, ShadowmapUVBias);

					for (int32 J = 0; J < NumCustomDataFloats; ++J)
					{
						Data.SetInstanceCustomData(I, J, CustomDatas[(I * NumCustomDataFloats) + J]);
					}
				}
				Component->PerInstanceRenderData->UpdateFromPreallocatedData(Data);
				Component->MarkRenderStateDirty();
			}
		}
	}
}