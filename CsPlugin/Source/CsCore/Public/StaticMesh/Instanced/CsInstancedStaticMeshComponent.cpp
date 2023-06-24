// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "StaticMesh/Instanced/CsInstancedStaticMeshComponent.h"

// Material
#include "MeshMaterialShader.h"
// Debug
#include "ProfilingDebugging/LoadTimeTracker.h"

IMPLEMENT_TYPE_LAYOUT(FCsInstancedStaticMeshVertexFactoryShaderParameters);

CSCORE_API const int32 CsInstancedStaticMeshMaxTexCoord = 8;

IMPLEMENT_GLOBAL_SHADER_PARAMETER_STRUCT(FCsInstancedStaticMeshVertexFactoryUniformShaderParameters, "CsInstanceVF");

namespace NCsStaticMesh
{
	namespace NInstanced
	{
		class FDummyFloatBuffer : public FVertexBufferWithSRV
		{
		public:
			virtual void InitRHI() override
			{
				// Create the texture RHI.  		
				FRHIResourceCreateInfo CreateInfo(TEXT("NCsStaticMesh::NInstanced::FDummyFloatBuffer"));

				const int32 NumFloats = 4;
				VertexBufferRHI = RHICreateVertexBuffer(sizeof(float) * NumFloats, BUF_Static | BUF_ShaderResource, CreateInfo);

				float* BufferData = (float*)RHILockVertexBuffer(VertexBufferRHI, 0, sizeof(float) * NumFloats, RLM_WriteOnly);
				FMemory::Memzero(BufferData, sizeof(float) * NumFloats);
				RHIUnlockVertexBuffer(VertexBufferRHI);

				// Create a view of the buffer
				ShaderResourceViewRHI = RHICreateShaderResourceView(VertexBufferRHI, sizeof(float), PF_R32_FLOAT);
			}
		};
	}
}

TGlobalResource<NCsStaticMesh::NInstanced::FDummyFloatBuffer> GCsInstancedStaticMeshDummyFloatBuffer;

// InstanceBufferType (NCsStaticMesh::NInstanced::NInstance::FBuffer)
#pragma region

namespace NCsStaticMesh
{
	namespace NInstanced
	{
		namespace NInstance
		{
			FBuffer::FBuffer(ERHIFeatureLevel::Type InFeatureLevel, bool InRequireCPUAccess) : 
				FRenderResource(InFeatureLevel), 
				RequireCPUAccess(InRequireCPUAccess)
			{
			}

			FBuffer::~FBuffer()
			{
				CleanUp();
			}

			/** Delete existing resources */
			void FBuffer::CleanUp()
			{
				InstanceData.Reset();
			}

			void FBuffer::Init(FStaticMeshInstanceData& Other)
			{
				QUICK_SCOPE_CYCLE_COUNTER(STAT_FCsStaticMeshInstanceBuffer_Init);

				InstanceData = MakeShared<FStaticMeshInstanceData, ESPMode::ThreadSafe>();
				FMemory::Memswap(&Other, InstanceData.Get(), sizeof(FStaticMeshInstanceData));
				InstanceData->SetAllowCPUAccess(RequireCPUAccess);
			}

		#define CommandBufferType NCsStaticMesh::NInstanced::NUpdate::NCommand::FBuffer

			void FBuffer::UpdateFromCommandBuffer_GameThread(CommandBufferType& CmdBuffer)
			{
				QUICK_SCOPE_CYCLE_COUNTER(STAT_FStaticMeshInstanceBuffer_UpdateFromCommandBuffer_Concurrent);
	
				typedef NCsStaticMesh::NInstanced::NInstance::FBuffer InstanceBufferType;

				InstanceBufferType* InstanceBuffer = this;
				CommandBufferType* CmdBufferPtr	   = &CmdBuffer;

				CmdBuffer.Start();
		
				ENQUEUE_RENDER_COMMAND(InstanceBuffer_UpdateFromPreallocatedData)(
					[InstanceBuffer, CmdBufferPtr](FRHICommandListImmediate& RHICmdList)
					{
						InstanceBuffer->UpdateFromCommandBuffer_RenderThread(*CmdBufferPtr);
					});
			}

			void FBuffer::UpdateFromCommandBuffer_RenderThread(CommandBufferType& CmdBuffer)
			{
				QUICK_SCOPE_CYCLE_COUNTER(STAT_FStaticMeshInstanceBuffer_UpdateFromCommandBuffer_RenderThread);
	
				typedef NCsStaticMesh::NInstanced::NUpdate::NCommand::FEdit EditType;

				TArray<EditType>& Edits = CmdBuffer.Edits;

				for (const EditType& Edit : Edits)
				{
					// Update
					if (Edit.IsUpdate())
					{
						// Transform
						if (Edit.HasTransform())
						{
							const int32& TransformIndex = Edit.TransformIndex;

							typedef NCsStaticMesh::NInstanced::NUpdate::NCommand::FEditTransforms EditTransformsType;

							EditTransformsType& EditTransforms = CmdBuffer.EditTransforms;
							TArray<int32>& Indices			   = EditTransforms.Indices;
							TArray<FMatrix>& Transforms		   = EditTransforms.Transforms;

							const int32& InstanceIndex = Indices[TransformIndex];
							const FMatrix& Transform= Transforms[TransformIndex];

							InstanceData->SetInstance(InstanceIndex, Transform, 0);
						}
						// CustomData
						if (Edit.HasCustomData())
						{
							const int32& CustomDataIndex = Edit.CustomDataIndex;

							typedef NCsStaticMesh::NInstanced::NUpdate::NCommand::FEditCustomDatas EditCustomDatasType;

							EditCustomDatasType& EditCustomDatas = CmdBuffer.EditCustomDatas;
							TArray<int32>& Indices			     = EditCustomDatas.Indices;
							TArray<float>& CustomDatas		     = EditCustomDatas.CustomDatas;
							const int32& Stride				     = EditCustomDatas.Stride;

							const int32& InstanceIndex = Indices[CustomDataIndex];

							int32 Index = 0;

							for (int32 I = Stride - 1; I >= 0; --I)
							{
								Index			   = (Stride * CustomDataIndex) + I;
								const float& Value = CustomDatas[Index];

								InstanceData->SetInstanceCustomData(InstanceIndex, I, Value);
							}
						}
					}
					// Remove
					if (Edit.IsRemove())
					{
						const int32& InstanceIndex = Edit.InstanceIndex;

						InstanceData->NullifyInstance(InstanceIndex);
					}
					// Swap
					if (Edit.IsSwap())
					{
						const int32& InstanceIndex = Edit.InstanceIndex;
						const int32& SwapIndex	   = Edit.SwapIndex;

						InstanceData->SwapInstance(InstanceIndex, SwapIndex);
					}
				}
				UpdateRHI();

				CmdBuffer.Clear();
				CmdBuffer.Complete();
			}

		#undef CommandBufferType

			void FBuffer::InitRHI()
			{
				check(InstanceData);
				if (InstanceData->GetNumInstances() > 0)
				{
					QUICK_SCOPE_CYCLE_COUNTER(STAT_FStaticMeshInstanceBuffer_InitRHI);
					SCOPED_LOADTIMER(FStaticMeshInstanceBuffer_InitRHI);

					LLM_SCOPE(ELLMTag::InstancedMesh);
					auto AccessFlags = BUF_Static;
					CreateVertexBuffer(InstanceData->GetOriginResourceArray(), AccessFlags | BUF_ShaderResource, 16, PF_A32B32G32R32F, InstanceOriginBuffer.VertexBufferRHI, InstanceOriginSRV);
					CreateVertexBuffer(InstanceData->GetTransformResourceArray(), AccessFlags | BUF_ShaderResource, InstanceData->GetTranslationUsesHalfs() ? 8 : 16, InstanceData->GetTranslationUsesHalfs() ? PF_FloatRGBA : PF_A32B32G32R32F, InstanceTransformBuffer.VertexBufferRHI, InstanceTransformSRV);
					CreateVertexBuffer(InstanceData->GetLightMapResourceArray(), AccessFlags | BUF_ShaderResource, 8, PF_R16G16B16A16_SNORM, InstanceLightmapBuffer.VertexBufferRHI, InstanceLightmapSRV);
					if (InstanceData->GetNumCustomDataFloats() > 0)
					{
						CreateVertexBuffer(InstanceData->GetCustomDataResourceArray(), AccessFlags | BUF_ShaderResource, 4, PF_R32_FLOAT, InstanceCustomDataBuffer.VertexBufferRHI, InstanceCustomDataSRV);
						// Make sure we still create custom data SRV on platforms that do not support/use MVF 
						if (InstanceCustomDataSRV == nullptr)
						{
							InstanceCustomDataSRV = RHICreateShaderResourceView(InstanceCustomDataBuffer.VertexBufferRHI, 4, PF_R32_FLOAT);
						}
					}
					else
					{
						InstanceCustomDataSRV = GCsInstancedStaticMeshDummyFloatBuffer.ShaderResourceViewRHI;
					}
				}
			}

			void FBuffer::ReleaseRHI()
			{
				InstanceOriginSRV.SafeRelease();
				InstanceTransformSRV.SafeRelease();
				InstanceLightmapSRV.SafeRelease();
				InstanceCustomDataSRV.SafeRelease();

				InstanceOriginBuffer.ReleaseRHI();
				InstanceTransformBuffer.ReleaseRHI();
				InstanceLightmapBuffer.ReleaseRHI();
				InstanceCustomDataBuffer.ReleaseRHI();
			}

			void FBuffer::InitResource()
			{
				FRenderResource::InitResource();
				InstanceOriginBuffer.InitResource();
				InstanceTransformBuffer.InitResource();
				InstanceLightmapBuffer.InitResource();
				InstanceCustomDataBuffer.InitResource();
			}

			void FBuffer::ReleaseResource()
			{
				FRenderResource::ReleaseResource();
				InstanceOriginBuffer.ReleaseResource();
				InstanceTransformBuffer.ReleaseResource();
				InstanceLightmapBuffer.ReleaseResource();
				InstanceCustomDataBuffer.ReleaseResource();
			}

			SIZE_T FBuffer::GetResourceSize() const
			{
				if (InstanceData && InstanceData->GetNumInstances() > 0)
				{
					return InstanceData->GetResourceSize();
				}
				return 0;
			}

			void FBuffer::CreateVertexBuffer(FResourceArrayInterface* InResourceArray, uint32 InUsage, uint32 InStride, uint8 InFormat, FVertexBufferRHIRef& OutVertexBufferRHI, FShaderResourceViewRHIRef& OutInstanceSRV)
			{
				check(InResourceArray);
				check(InResourceArray->GetResourceDataSize() > 0);

				// TODO: possibility over allocated the vertex buffer when we support partial update for when working in the editor
				FRHIResourceCreateInfo CreateInfo(InResourceArray);
				OutVertexBufferRHI = RHICreateVertexBuffer(InResourceArray->GetResourceDataSize(), InUsage, CreateInfo);
	
				if (RHISupportsManualVertexFetch(GMaxRHIShaderPlatform))
				{
					OutInstanceSRV = RHICreateShaderResourceView(OutVertexBufferRHI, InStride, InFormat);
				}
			}

		#define DataType NCsStaticMesh::NInstanced::FDataType
			void FBuffer::BindInstanceVertexBuffer(const class FVertexFactory* VertexFactory, DataType& InstancedStaticMeshData) const
			{
				if (InstanceData->GetNumInstances())
				{
					if (RHISupportsManualVertexFetch(GMaxRHIShaderPlatform))
					{
						check(InstanceOriginSRV);
						check(InstanceTransformSRV);
						check(InstanceLightmapSRV);
					}
					check(InstanceCustomDataSRV); // Should not be nullptr, but can be assigned a dummy buffer
				}

				{
					InstancedStaticMeshData.InstanceOriginSRV = InstanceOriginSRV;
					InstancedStaticMeshData.InstanceTransformSRV = InstanceTransformSRV;
					InstancedStaticMeshData.InstanceLightmapSRV = InstanceLightmapSRV;
					InstancedStaticMeshData.InstanceCustomDataSRV = InstanceCustomDataSRV;
					InstancedStaticMeshData.NumCustomDataFloats = InstanceData->GetNumCustomDataFloats();
				}

				{
					InstancedStaticMeshData.InstanceOriginComponent = FVertexStreamComponent(
						&InstanceOriginBuffer,
						0,
						16,
						VET_Float4,
						EVertexStreamUsage::ManualFetch | EVertexStreamUsage::Instancing
					);

					EVertexElementType TransformType = InstanceData->GetTranslationUsesHalfs() ? VET_Half4 : VET_Float4;
					uint32 TransformStride = InstanceData->GetTranslationUsesHalfs() ? 8 : 16;

					InstancedStaticMeshData.InstanceTransformComponent[0] = FVertexStreamComponent(
						&InstanceTransformBuffer,
						0 * TransformStride,
						3 * TransformStride,
						TransformType,
						EVertexStreamUsage::ManualFetch | EVertexStreamUsage::Instancing
					);
					InstancedStaticMeshData.InstanceTransformComponent[1] = FVertexStreamComponent(
						&InstanceTransformBuffer,
						1 * TransformStride,
						3 * TransformStride,
						TransformType,
						EVertexStreamUsage::ManualFetch | EVertexStreamUsage::Instancing
					);
					InstancedStaticMeshData.InstanceTransformComponent[2] = FVertexStreamComponent(
						&InstanceTransformBuffer,
						2 * TransformStride,
						3 * TransformStride,
						TransformType,
						EVertexStreamUsage::ManualFetch | EVertexStreamUsage::Instancing
					);

					InstancedStaticMeshData.InstanceLightmapAndShadowMapUVBiasComponent = FVertexStreamComponent(
						&InstanceLightmapBuffer,
						0,
						8,
						VET_Short4N,
						EVertexStreamUsage::ManualFetch | EVertexStreamUsage::Instancing
					);
				}
			}
		#undef DataType
		}
	}
}

#pragma endregion InstanceBufferType (NCsStaticMesh::NInstanced::NInstance::FBuffer)

// PerInstanceRenderDataType (NCsStaticMesh::NInstanced::NPerInstance::FRenderData)
#pragma region

namespace NCsStaticMesh
{
	namespace NInstanced
	{
		namespace NPerInstance
		{
			FRenderData::FRenderData(FStaticMeshInstanceData& Other, ERHIFeatureLevel::Type InFeaureLevel, bool InRequireCPUAccess)
				: ResourceSize(InRequireCPUAccess ? Other.GetResourceSize() : 0)
				, InstanceBuffer(InFeaureLevel, InRequireCPUAccess)
			{
				InstanceBuffer.Init(Other);
				InstanceBuffer_GameThread = InstanceBuffer.InstanceData;

				BeginInitResource(&InstanceBuffer);

				NumInstances = 1;
			}

			FRenderData::~FRenderData()
			{
				InstanceBuffer_GameThread.Reset();
				// Should be always destructed on rendering thread
				InstanceBuffer.ReleaseResource();
			}

			void FRenderData::Init(FStaticMeshInstanceData& InOther)
			{
				InstanceBuffer.RequireCPUAccess = (InOther.GetOriginResourceArray()->GetAllowCPUAccess() || 
												   InOther.GetTransformResourceArray()->GetAllowCPUAccess() || 
												   InOther.GetLightMapResourceArray()->GetAllowCPUAccess()) ? true : InstanceBuffer.RequireCPUAccess;
				ResourceSize					= InstanceBuffer.RequireCPUAccess ? InOther.GetResourceSize() : 0;

				InOther.SetAllowCPUAccess(InstanceBuffer.RequireCPUAccess);

				InstanceBuffer_GameThread = MakeShared<FStaticMeshInstanceData, ESPMode::ThreadSafe>();
				FMemory::Memswap(&InOther, InstanceBuffer_GameThread.Get(), sizeof(FStaticMeshInstanceData));

				typedef TSharedPtr<FStaticMeshInstanceData, ESPMode::ThreadSafe> FStaticMeshInstanceDataPtr;
				typedef NCsStaticMesh::NInstanced::NInstance::FBuffer InstanceBufferType;

				FStaticMeshInstanceDataPtr InInstanceBufferDataPtr = InstanceBuffer_GameThread;
				InstanceBufferType* InInstanceBuffer		       = &InstanceBuffer;

				ENQUEUE_RENDER_COMMAND(FInstanceBuffer_UpdateFromPreallocatedData)(
					[InInstanceBufferDataPtr, InInstanceBuffer](FRHICommandListImmediate& RHICmdList)
				{
					InInstanceBuffer->InstanceData = InInstanceBufferDataPtr;

					// Nullify all Instances
					const int32 Count = InInstanceBuffer->InstanceData->GetNumInstances();

					for (int32 I = 0; I < Count; ++I)
					{
						InInstanceBuffer->InstanceData->NullifyInstance(I);
					}
					InInstanceBuffer->UpdateRHI();
				}
				);
			}

		#define CommandBufferType NCsStaticMesh::NInstanced::NUpdate::NCommand::FBuffer
			void FRenderData::UpdateFromCommandBuffer(CommandBufferType& CmdBuffer)
			{
				InstanceBuffer.UpdateFromCommandBuffer_GameThread(CmdBuffer);
			}
		#undef CommandBufferType
		}
	}
}

#pragma endregion PerInstanceRenderDataType (NCsStaticMesh::NInstanced::NPerInstance::FRenderData)

// VertexFactoryType (FCsInstancedStaticMeshVertexFactory)
#pragma region

/**
 * Should we cache the material's shadertype on this platform with this vertex factory? 
 */
bool FCsInstancedStaticMeshVertexFactory::ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters)
{
	return (Parameters.MaterialParameters.bIsUsedWithInstancedStaticMeshes || Parameters.MaterialParameters.bIsSpecialEngineMaterial)
			&& FLocalVertexFactory::ShouldCompilePermutation(Parameters);
}

void FCsInstancedStaticMeshVertexFactory::ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
{
	const bool ContainsManualVertexFetch = OutEnvironment.GetDefinitions().Contains("MANUAL_VERTEX_FETCH");
	if (!ContainsManualVertexFetch && RHISupportsManualVertexFetch(Parameters.Platform))
	{
		OutEnvironment.SetDefine(TEXT("MANUAL_VERTEX_FETCH"), TEXT("1"));
	}

	OutEnvironment.SetDefine(TEXT("USE_INSTANCING"), TEXT("1"));
	if (IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5))
	{
		OutEnvironment.SetDefine(TEXT("USE_DITHERED_LOD_TRANSITION_FOR_INSTANCED"), ALLOW_DITHERED_LOD_FOR_INSTANCED_STATIC_MESHES);
	}
	else
	{
		// On mobile dithered LOD transition has to be explicitly enabled in material and project settings
		OutEnvironment.SetDefine(TEXT("USE_DITHERED_LOD_TRANSITION_FOR_INSTANCED"), Parameters.MaterialParameters.bIsDitheredLODTransition && ALLOW_DITHERED_LOD_FOR_INSTANCED_STATIC_MESHES);
	}

	FLocalVertexFactory::ModifyCompilationEnvironment(Parameters, OutEnvironment);
}

/**
 * Copy the data from another vertex factory
 * @param Other - factory to copy from
 */
void FCsInstancedStaticMeshVertexFactory::Copy(const FCsInstancedStaticMeshVertexFactory& Other)
{
	FCsInstancedStaticMeshVertexFactory* VertexFactory = this;
	const FDataType* DataCopy = &Other.Data;
	ENQUEUE_RENDER_COMMAND(FInstancedStaticMeshVertexFactoryCopyData)(
	[VertexFactory, DataCopy](FRHICommandListImmediate& RHICmdList)
	{
		VertexFactory->Data = *DataCopy;
	});
	BeginUpdateResourceRHI(this);
}

void FCsInstancedStaticMeshVertexFactory::InitRHI()
{
	SCOPED_LOADTIMER(FInstancedStaticMeshVertexFactory_InitRHI);

	check(HasValidFeatureLevel());

#if !ALLOW_DITHERED_LOD_FOR_INSTANCED_STATIC_MESHES // position(and normal) only shaders cannot work with dithered LOD
	// If the vertex buffer containing position is not the same vertex buffer containing the rest of the data,
	// then initialize PositionStream and PositionDeclaration.
	if(Data.PositionComponent.VertexBuffer != Data.TangentBasisComponents[0].VertexBuffer)
	{
		auto AddDeclaration = [&Data](EVertexInputStreamType InputStreamType, bool bInstanced, bool bAddNormal)
		{
			FVertexDeclarationElementList StreamElements;
			StreamElements.Add(AccessPositionStreamComponent(Data.PositionComponent, 0));

			bAddNormal = bAddNormal && Data.TangentBasisComponents[1].VertexBuffer != NULL;
			if (bAddNormal)
			{
				StreamElements.Add(AccessStreamComponent(Data.TangentBasisComponents[1], 2, InputStreamType));
			}

			if (bInstanced)
			{
				// toss in the instanced location stream
				StreamElements.Add(AccessPositionStreamComponent(Data.InstanceOriginComponent, 8));
				StreamElements.Add(AccessPositionStreamComponent(Data.InstanceTransformComponent[0], 9));
				StreamElements.Add(AccessPositionStreamComponent(Data.InstanceTransformComponent[1], 10));
				StreamElements.Add(AccessPositionStreamComponent(Data.InstanceTransformComponent[2], 11));
			}

			InitDeclaration(StreamElements, InputStreamType);
		};
		AddDeclaration(EVertexInputStreamType::PositionOnly, bInstanced, false);
		AddDeclaration(EVertexInputStreamType::PositionAndNormalOnly, bInstanced, true);
	}
#endif

	FVertexDeclarationElementList Elements;
	if(Data.PositionComponent.VertexBuffer != NULL)
	{
		Elements.Add(AccessStreamComponent(Data.PositionComponent,0));
	}

	// only tangent,normal are used by the stream. the binormal is derived in the shader
	uint8 TangentBasisAttributes[2] = { 1, 2 };
	for(int32 AxisIndex = 0;AxisIndex < 2;AxisIndex++)
	{
		if(Data.TangentBasisComponents[AxisIndex].VertexBuffer != NULL)
		{
			Elements.Add(AccessStreamComponent(Data.TangentBasisComponents[AxisIndex],TangentBasisAttributes[AxisIndex]));
		}
	}

	if (Data.ColorComponentsSRV == nullptr)
	{
		Data.ColorComponentsSRV = GNullColorVertexBuffer.VertexBufferSRV;
		Data.ColorIndexMask = 0;
	}

	if(Data.ColorComponent.VertexBuffer)
	{
		Elements.Add(AccessStreamComponent(Data.ColorComponent,3));
	}
	else
	{
		//If the mesh has no color component, set the null color buffer on a new stream with a stride of 0.
		//This wastes 4 bytes of bandwidth per vertex, but prevents having to compile out twice the number of vertex factories.
		FVertexStreamComponent NullColorComponent(&GNullColorVertexBuffer, 0, 0, VET_Color, EVertexStreamUsage::ManualFetch);
		Elements.Add(AccessStreamComponent(NullColorComponent, 3));
	}

	if(Data.TextureCoordinates.Num())
	{
		const int32 BaseTexCoordAttribute = 4;
		for(int32 CoordinateIndex = 0;CoordinateIndex < Data.TextureCoordinates.Num();CoordinateIndex++)
		{
			Elements.Add(AccessStreamComponent(
				Data.TextureCoordinates[CoordinateIndex],
				BaseTexCoordAttribute + CoordinateIndex
				));
		}

		for(int32 CoordinateIndex = Data.TextureCoordinates.Num(); CoordinateIndex < (CsInstancedStaticMeshMaxTexCoord + 1) / 2; CoordinateIndex++)
		{
			Elements.Add(AccessStreamComponent(
				Data.TextureCoordinates[Data.TextureCoordinates.Num() - 1],
				BaseTexCoordAttribute + CoordinateIndex
				));
		}
	}

	if(Data.LightMapCoordinateComponent.VertexBuffer)
	{
		Elements.Add(AccessStreamComponent(Data.LightMapCoordinateComponent,15));
	}
	else if(Data.TextureCoordinates.Num())
	{
		Elements.Add(AccessStreamComponent(Data.TextureCoordinates[0],15));
	}

	// toss in the instanced location stream
	check(Data.InstanceOriginComponent.VertexBuffer);
	if (Data.InstanceOriginComponent.VertexBuffer)
	{
		Elements.Add(AccessStreamComponent(Data.InstanceOriginComponent, 8));
	}

	check(Data.InstanceTransformComponent[0].VertexBuffer);
	if (Data.InstanceTransformComponent[0].VertexBuffer)
	{
		Elements.Add(AccessStreamComponent(Data.InstanceTransformComponent[0], 9));
		Elements.Add(AccessStreamComponent(Data.InstanceTransformComponent[1], 10));
		Elements.Add(AccessStreamComponent(Data.InstanceTransformComponent[2], 11));
	}
	/*
	if (Data.InstanceLightmapAndShadowMapUVBiasComponent.VertexBuffer)
	{
		Elements.Add(AccessStreamComponent(Data.InstanceLightmapAndShadowMapUVBiasComponent,12));
	}
	*/
	// we don't need per-vertex shadow or lightmap rendering
	InitDeclaration(Elements);

	{
		FCsInstancedStaticMeshVertexFactoryUniformShaderParameters UniformParameters;
		UniformParameters.VertexFetch_InstanceOriginBuffer = GetInstanceOriginSRV();
		UniformParameters.VertexFetch_InstanceTransformBuffer = GetInstanceTransformSRV();
		UniformParameters.VertexFetch_InstanceLightmapBuffer = GetInstanceLightmapSRV();
		UniformParameters.InstanceCustomDataBuffer = GetInstanceCustomDataSRV();
		UniformParameters.NumCustomDataFloats = Data.NumCustomDataFloats;
		UniformBuffer = TUniformBufferRef<FCsInstancedStaticMeshVertexFactoryUniformShaderParameters>::CreateUniformBufferImmediate(UniformParameters, UniformBuffer_MultiFrame, EUniformBufferValidation::None);
	}
}

IMPLEMENT_VERTEX_FACTORY_PARAMETER_TYPE(FCsInstancedStaticMeshVertexFactory, SF_Vertex, FCsInstancedStaticMeshVertexFactoryShaderParameters);
IMPLEMENT_VERTEX_FACTORY_TYPE_EX(FCsInstancedStaticMeshVertexFactory,"/Engine/Private/LocalVertexFactory.ush",true,true,true,true,true,true,false);

#pragma endregion VertexFactoryType (NFCsInstancedStaticMeshVertexFactory)

// RenderDataType (NCsStaticMesh::NInstanced::FRenderData)
#pragma region

namespace NCsStaticMesh
{
	namespace NInstanced
	{
		FRenderData::FRenderData(UCsInstancedStaticMeshComponent* InComponent, ERHIFeatureLevel::Type InFeatureLevel) :
			Component(InComponent),
			PerInstanceRenderData(InComponent->PerInstanceRenderData),
			LODModels(Component->GetStaticMesh()->RenderData->LODResources),
			FeatureLevel(InFeatureLevel)
		{
			check(PerInstanceRenderData.IsValid());
			// Allocate the vertex factories for each LOD
			InitVertexFactories();
		}

		void FRenderData::InitVertexFactories()
		{
			typedef FCsInstancedStaticMeshVertexFactory VertexFactoryType;

			// Allocate the vertex factories for each LOD
			for (int32 LODIndex = 0; LODIndex < LODModels.Num(); LODIndex++)
			{
				VertexFactories.Add(new VertexFactoryType(FeatureLevel));
			}

			const int32 LightMapCoordinateIndex = Component->GetStaticMesh()->LightMapCoordinateIndex;

			ENQUEUE_RENDER_COMMAND(InstancedStaticMeshRenderData_InitVertexFactories)(
				[this, LightMapCoordinateIndex](FRHICommandListImmediate& RHICmdList)
			{
				for (int32 LODIndex = 0; LODIndex < VertexFactories.Num(); LODIndex++)
				{
					const FStaticMeshLODResources* RenderData = &LODModels[LODIndex];

					VertexFactoryType::FDataType Data;
					// Assign to the vertex factory for this LOD.
					VertexFactoryType& VertexFactory = VertexFactories[LODIndex];

					RenderData->VertexBuffers.PositionVertexBuffer.BindPositionVertexBuffer(&VertexFactory, Data);
					RenderData->VertexBuffers.StaticMeshVertexBuffer.BindTangentVertexBuffer(&VertexFactory, Data);
					RenderData->VertexBuffers.StaticMeshVertexBuffer.BindPackedTexCoordVertexBuffer(&VertexFactory, Data);
					if (LightMapCoordinateIndex < (int32)RenderData->VertexBuffers.StaticMeshVertexBuffer.GetNumTexCoords() && LightMapCoordinateIndex >= 0)
					{
						RenderData->VertexBuffers.StaticMeshVertexBuffer.BindLightMapVertexBuffer(&VertexFactory, Data, LightMapCoordinateIndex);
					}
					RenderData->VertexBuffers.ColorVertexBuffer.BindColorVertexBuffer(&VertexFactory, Data);

					check(PerInstanceRenderData);
					PerInstanceRenderData->InstanceBuffer.BindInstanceVertexBuffer(&VertexFactory, Data);

					VertexFactory.SetData(Data);
					VertexFactory.InitResource();
				}
			});
		}
	}
}

#pragma endregion (NCsStaticMesh::NInstanced::FRenderData)

// SceneProxyType (NCsStaticMesh::NInstanced::FSceneProxy)
#pragma region

namespace NCsStaticMesh
{
	namespace NInstanced
	{
		FSceneProxy::FSceneProxy(UCsInstancedStaticMeshComponent* InComponent, ERHIFeatureLevel::Type InFeatureLevel) :
			FStaticMeshSceneProxy(InComponent, true),
			StaticMesh(InComponent->GetStaticMesh()),
			InstancedRenderData(InComponent, InFeatureLevel)
		{
			bVFRequiresPrimitiveUniformBuffer = true;
			SetupProxy(InComponent);
		}

		SIZE_T FSceneProxy::GetTypeHash() const
		{
			static size_t UniquePointer;
			return reinterpret_cast<size_t>(&UniquePointer);
		}

		void FSceneProxy::GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const
		{
			QUICK_SCOPE_CYCLE_COUNTER(STAT_InstancedStaticMeshSceneProxy_GetMeshElements);

			// If the first pass rendered selected instances only, we need to render the deselected instances in a second pass
			const int32 NumSelectionGroups = 1;

			typedef NCsStaticMesh::NInstanced::NInstancing::FUserData InstancingUserDataType;

			const InstancingUserDataType* PassUserData = &UserData_AllInstances;

			for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
			{
				if (VisibilityMap & (1 << ViewIndex))
				{
					const FSceneView* View = Views[ViewIndex];

					for (int32 SelectionGroupIndex = 0; SelectionGroupIndex < NumSelectionGroups; SelectionGroupIndex++)
					{
						const int32 LODIndex				    = GetLOD(View);
						const FStaticMeshLODResources& LODModel = StaticMesh->RenderData->LODResources[LODIndex];

						for (int32 SectionIndex = 0; SectionIndex < LODModel.Sections.Num(); SectionIndex++)
						{
							const int32 NumBatches = GetNumMeshBatches();

							for (int32 BatchIndex = 0; BatchIndex < NumBatches; BatchIndex++)
							{
								FMeshBatch& MeshElement = Collector.AllocateMesh();

								if (GetMeshElement(LODIndex, BatchIndex, SectionIndex, GetDepthPriorityGroup(View), false, true, MeshElement))
								{
									//@todo-rco this is only supporting selection on the first element
									MeshElement.Elements[0].UserData					 = PassUserData;
									MeshElement.Elements[0].bUserDataIsColorVertexBuffer = false;
									MeshElement.bCanApplyViewModeOverrides				 = true;
									MeshElement.bUseSelectionOutline					 = false;
									MeshElement.bUseWireframeSelectionColoring			 = false;

									if (View->bRenderFirstInstanceOnly)
									{
										for (int32 ElementIndex = 0; ElementIndex < MeshElement.Elements.Num(); ElementIndex++)
										{
											MeshElement.Elements[ElementIndex].NumInstances = FMath::Min<uint32>(MeshElement.Elements[ElementIndex].NumInstances, 1);
										}
									}

									Collector.AddMesh(ViewIndex, MeshElement);
									INC_DWORD_STAT_BY(STAT_StaticMeshTriangles, MeshElement.GetNumPrimitives());
								}
							}
						}
					}
				}
			}
		}

		int32 FSceneProxy::CollectOccluderElements(FOccluderElementsCollector& Collector) const
		{
			return 0;
		}

		void FSceneProxy::SetupProxy(UCsInstancedStaticMeshComponent* InComponent)
		{
			// Make sure all the materials are okay to be rendered as an instanced mesh.
			for (int32 LODIndex = 0; LODIndex < LODs.Num(); LODIndex++)
			{
				FStaticMeshSceneProxy::FLODInfo& LODInfo = LODs[LODIndex];
				for (int32 SectionIndex = 0; SectionIndex < LODInfo.Sections.Num(); SectionIndex++)
				{
					FStaticMeshSceneProxy::FLODInfo::FSectionInfo& Section = LODInfo.Sections[SectionIndex];
					if (!Section.Material->CheckMaterialUsage_Concurrent(MATUSAGE_InstancedStaticMeshes))
					{
						Section.Material = UMaterial::GetDefaultMaterial(MD_Surface);
					}
				}
			}

			// Copy the parameters for LOD - all instances
			UserData_AllInstances.MeshRenderData	= InComponent->GetStaticMesh()->RenderData.Get();
			UserData_AllInstances.StartCullDistance = InComponent->GetStartCullDistance();
			UserData_AllInstances.EndCullDistance	= InComponent->GetEndCullDistance();
			UserData_AllInstances.InstancingOffset	= InComponent->GetStaticMesh()->GetBoundingBox().GetCenter();
			UserData_AllInstances.MinLOD			= ClampedMinLOD;
			UserData_AllInstances.bRenderSelected	= true;
			UserData_AllInstances.bRenderUnselected = true;
			UserData_AllInstances.RenderData		= nullptr;

			FVector MinScale(0);
			FVector MaxScale(0);
			InComponent->GetInstancesMinMaxScale(MinScale, MaxScale);

			UserData_AllInstances.AverageInstancesScale = MinScale + (MaxScale - MinScale) / 2.0f;

			// selected only
			UserData_SelectedInstances = UserData_AllInstances;
			UserData_SelectedInstances.bRenderUnselected = false;

			// unselected only
			UserData_DeselectedInstances = UserData_AllInstances;
			UserData_DeselectedInstances.bRenderSelected = false;
		}

		void FSceneProxy::DestroyRenderThreadResources()
		{
			InstancedRenderData.ReleaseResources(&GetScene(), StaticMesh);
			FStaticMeshSceneProxy::DestroyRenderThreadResources();
		}

		void FSceneProxy::SetupInstancedMeshBatch(int32 LODIndex, int32 BatchIndex, FMeshBatch& OutMeshBatch) const
		{
			OutMeshBatch.VertexFactory		 = &InstancedRenderData.VertexFactories[LODIndex];
			const uint32 NumInstances		 = InstancedRenderData.PerInstanceRenderData->GetNumInstances();
			FMeshBatchElement& BatchElement0 = OutMeshBatch.Elements[0];
			BatchElement0.UserData			 = (void*)&UserData_AllInstances;
			BatchElement0.bUserDataIsColorVertexBuffer = false;
			BatchElement0.InstancedLODIndex		 = LODIndex;
			BatchElement0.UserIndex				 = 0;
			BatchElement0.PrimitiveUniformBuffer = GetUniformBuffer();

			BatchElement0.NumInstances = NumInstances;
		}

		void FSceneProxy::GetLightRelevance(const FLightSceneProxy* LightSceneProxy, bool& bDynamic, bool& bRelevant, bool& bLightMapped, bool& bShadowMapped) const
		{
			FStaticMeshSceneProxy::GetLightRelevance(LightSceneProxy, bDynamic, bRelevant, bLightMapped, bShadowMapped);

			if (InstancedRenderData.PerInstanceRenderData->InstanceBuffer.GetNumInstances() == 0)
			{
				bRelevant = false;
			}
		}

		bool FSceneProxy::GetShadowMeshElement(int32 LODIndex, int32 BatchIndex, uint8 InDepthPriorityGroup, FMeshBatch& OutMeshBatch, bool bDitheredLODTransition) const
		{
			if (LODIndex < InstancedRenderData.VertexFactories.Num() && FStaticMeshSceneProxy::GetShadowMeshElement(LODIndex, BatchIndex, InDepthPriorityGroup, OutMeshBatch, bDitheredLODTransition))
			{
				SetupInstancedMeshBatch(LODIndex, BatchIndex, OutMeshBatch);
				return true;
			}
			return false;
		}

		/** Sets up a FMeshBatch for a specific LOD and element. */
		bool FSceneProxy::GetMeshElement(int32 LODIndex, int32 BatchIndex, int32 ElementIndex, uint8 InDepthPriorityGroup, bool bUseSelectionOutline, bool bAllowPreCulledIndices, FMeshBatch& OutMeshBatch) const
		{
			if (LODIndex < InstancedRenderData.VertexFactories.Num() && FStaticMeshSceneProxy::GetMeshElement(LODIndex, BatchIndex, ElementIndex, InDepthPriorityGroup, bUseSelectionOutline, bAllowPreCulledIndices, OutMeshBatch))
			{
				SetupInstancedMeshBatch(LODIndex, BatchIndex, OutMeshBatch);
				return true;
			}
			return false;
		};

		/** Sets up a wireframe FMeshBatch for a specific LOD. */
		bool FSceneProxy::GetWireframeMeshElement(int32 LODIndex, int32 BatchIndex, const FMaterialRenderProxy* WireframeRenderProxy, uint8 InDepthPriorityGroup, bool bAllowPreCulledIndices, FMeshBatch& OutMeshBatch) const
		{
			if (LODIndex < InstancedRenderData.VertexFactories.Num() && FStaticMeshSceneProxy::GetWireframeMeshElement(LODIndex, BatchIndex, WireframeRenderProxy, InDepthPriorityGroup, bAllowPreCulledIndices, OutMeshBatch))
			{
				SetupInstancedMeshBatch(LODIndex, BatchIndex, OutMeshBatch);
				return true;
			}
			return false;
		}

		void FSceneProxy::GetDistancefieldAtlasData(FBox& LocalVolumeBounds, FVector2D& OutDistanceMinMax, FIntVector& OutBlockMin, FIntVector& OutBlockSize, bool& bOutBuiltAsIfTwoSided, bool& bMeshWasPlane, float& SelfShadowBias, TArray<FMatrix>& ObjectLocalToWorldTransforms, bool& bOutThrottled) const
		{
			FStaticMeshSceneProxy::GetDistancefieldAtlasData(LocalVolumeBounds, OutDistanceMinMax, OutBlockMin, OutBlockSize, bOutBuiltAsIfTwoSided, bMeshWasPlane, SelfShadowBias, ObjectLocalToWorldTransforms, bOutThrottled);

			ObjectLocalToWorldTransforms.Reset();

			const uint32 NumInstances = InstancedRenderData.PerInstanceRenderData->InstanceBuffer.GetNumInstances();
			for (uint32 InstanceIndex = 0; InstanceIndex < NumInstances; InstanceIndex++)
			{
				FMatrix InstanceToLocal;
				InstancedRenderData.PerInstanceRenderData->InstanceBuffer.GetInstanceTransform(InstanceIndex, InstanceToLocal);	
				InstanceToLocal.M[3][3] = 1.0f;

				ObjectLocalToWorldTransforms.Add(InstanceToLocal * GetLocalToWorld());
			}
		}

		void FSceneProxy::GetDistanceFieldInstanceInfo(int32& NumInstances, float& BoundsSurfaceArea) const
		{
			NumInstances = DistanceFieldData ? InstancedRenderData.PerInstanceRenderData->GetNumInstances() : 0;

			if (NumInstances > 0)
			{
				FMatrix InstanceToLocal;
				const int32 InstanceIndex = 0;
				InstancedRenderData.PerInstanceRenderData->InstanceBuffer.GetInstanceTransform(InstanceIndex, InstanceToLocal);
				InstanceToLocal.M[3][3] = 1.0f;

				const FMatrix InstanceTransform = InstanceToLocal * GetLocalToWorld();
				const FVector AxisScales = InstanceTransform.GetScaleVector();
				const FVector BoxDimensions = RenderData->Bounds.BoxExtent * AxisScales * 2;

				BoundsSurfaceArea = 2 * BoxDimensions.X * BoxDimensions.Y
					+ 2 * BoxDimensions.Z * BoxDimensions.Y
					+ 2 * BoxDimensions.X * BoxDimensions.Z;
			}
		}
	}
}

#pragma endregion SceneProxyType (NCsStaticMesh::NInstanced::FSceneProxy)

void FCsInstancedStaticMeshVertexFactoryShaderParameters::GetElementShaderBindings(
	const class FSceneInterface* Scene,
	const FSceneView* View,
	const FMeshMaterialShader* Shader,
	const EVertexInputStreamType InputStreamType,
	ERHIFeatureLevel::Type FeatureLevel,
	const FVertexFactory* VertexFactory,
	const FMeshBatchElement& BatchElement,
	FMeshDrawSingleShaderBindings& ShaderBindings,
	FVertexInputStreamArray& VertexStreams
	) const
{
	// Decode VertexFactoryUserData as VertexFactoryUniformBuffer
	FRHIUniformBuffer* VertexFactoryUniformBuffer = static_cast<FRHIUniformBuffer*>(BatchElement.VertexFactoryUserData);
	FCsLocalVertexFactoryShaderParametersBase::GetElementShaderBindingsBase(Scene, View, Shader, InputStreamType, FeatureLevel, VertexFactory, BatchElement, VertexFactoryUniformBuffer, ShaderBindings, VertexStreams);

	typedef NCsStaticMesh::NInstanced::NInstancing::FUserData InstancingUserDataType;

	const InstancingUserDataType* InstancingUserData = (const InstancingUserDataType*)BatchElement.UserData;
	const auto* InstancedVertexFactory = static_cast<const FCsInstancedStaticMeshVertexFactory*>(VertexFactory);
	const int32 InstanceOffsetValue = BatchElement.UserIndex;

	ShaderBindings.Add(Shader->GetUniformBufferParameter<FCsInstancedStaticMeshVertexFactoryUniformShaderParameters>(), InstancedVertexFactory->GetUniformBuffer());
	ShaderBindings.Add(InstanceOffset, InstanceOffsetValue);

	if (InstancedVertexFactory->SupportsManualVertexFetch(FeatureLevel))
	{
		ShaderBindings.Add(VertexFetch_InstanceOriginBufferParameter, InstancedVertexFactory->GetInstanceOriginSRV());
		ShaderBindings.Add(VertexFetch_InstanceTransformBufferParameter, InstancedVertexFactory->GetInstanceTransformSRV());
		ShaderBindings.Add(VertexFetch_InstanceLightmapBufferParameter, InstancedVertexFactory->GetInstanceLightmapSRV());
	}
	if (InstanceOffsetValue > 0 && VertexStreams.Num() > 0)
	{
		VertexFactory->OffsetInstanceStreams(InstanceOffsetValue, InputStreamType, VertexStreams);
	}

	if( InstancingWorldViewOriginOneParameter.IsBound() )
	{
		FVector4 InstancingViewZCompareZero(MIN_flt, MIN_flt, MAX_flt, 1.0f);
		FVector4 InstancingViewZCompareOne(MIN_flt, MIN_flt, MAX_flt, 0.0f);
		FVector4 InstancingViewZConstant(ForceInit);
		FVector4 InstancingOffset(ForceInit);
		FVector4 InstancingWorldViewOriginZero(ForceInit);
		FVector4 InstancingWorldViewOriginOne(ForceInit);
		InstancingWorldViewOriginOne.W = 1.0f;
		if (InstancingUserData && BatchElement.InstancedLODRange)
		{
			int32 FirstLOD = InstancingUserData->MinLOD;

			//int32 DebugMin = FMath::Min(CVarMinLOD.GetValueOnRenderThread(), InstancingUserData->MeshRenderData->LODResources.Num() - 1);
			int32 DebugMin = FMath::Min(-1, InstancingUserData->MeshRenderData->LODResources.Num() - 1);
			if (DebugMin >= 0)
			{
				FirstLOD = FMath::Max(FirstLOD, DebugMin);
			}

			FBoxSphereBounds ScaledBounds = InstancingUserData->MeshRenderData->Bounds.TransformBy(FTransform(FRotator::ZeroRotator, FVector::ZeroVector, InstancingUserData->AverageInstancesScale));
			float SphereRadius = ScaledBounds.SphereRadius;
			//float MinSize = View->ViewMatrices.IsPerspectiveProjection() ? CVarFoliageMinimumScreenSize.GetValueOnRenderThread() : 0.0f;
			float MinSize = View->ViewMatrices.IsPerspectiveProjection() ? 0.000005f : 0.0f;
			float LODScale = 1.0f;//CVarFoliageLODDistanceScale.GetValueOnRenderThread();
			float LODRandom = 0.0f;//CVarRandomLODRange.GetValueOnRenderThread();
			float MaxDrawDistanceScale = GetCachedScalabilityCVars().ViewDistanceScale;

			if (BatchElement.InstancedLODIndex)
			{
				InstancingViewZConstant.X = -1.0f;
			}
			else
			{
				// this is the first LOD, so we don't have a fade-in region
				InstancingViewZConstant.X = 0.0f;
			}
			InstancingViewZConstant.Y = 0.0f;
			InstancingViewZConstant.Z = 1.0f;

			// now we subtract off the lower segments, since they will be incorporated 
			InstancingViewZConstant.Y -= InstancingViewZConstant.X;
			InstancingViewZConstant.Z -= InstancingViewZConstant.X + InstancingViewZConstant.Y;
			//not using W InstancingViewZConstant.W -= InstancingViewZConstant.X + InstancingViewZConstant.Y + InstancingViewZConstant.Z;

			for (int32 SampleIndex = 0; SampleIndex < 2; SampleIndex++)
			{
				FVector4& InstancingViewZCompare(SampleIndex ? InstancingViewZCompareOne : InstancingViewZCompareZero);

				float FinalCull = MAX_flt;
				if (MinSize > 0.0)
				{
					FinalCull = ComputeBoundsDrawDistance(MinSize, SphereRadius, View->ViewMatrices.GetProjectionMatrix()) * LODScale;
				}
				if (InstancingUserData->EndCullDistance > 0.0f)
				{
					FinalCull = FMath::Min(FinalCull, InstancingUserData->EndCullDistance * MaxDrawDistanceScale);
				}
				FinalCull *= MaxDrawDistanceScale;

				InstancingViewZCompare.Z = FinalCull;
				if (int(BatchElement.InstancedLODIndex) < InstancingUserData->MeshRenderData->LODResources.Num() - 1)
				{
					float NextCut = ComputeBoundsDrawDistance(InstancingUserData->MeshRenderData->ScreenSize[BatchElement.InstancedLODIndex + 1].GetValue(), SphereRadius, View->ViewMatrices.GetProjectionMatrix()) * LODScale;
					InstancingViewZCompare.Z = FMath::Min(NextCut, FinalCull);
				}

				InstancingViewZCompare.X = MIN_flt;
				if (int(BatchElement.InstancedLODIndex) > FirstLOD)
				{
					float CurCut = ComputeBoundsDrawDistance(InstancingUserData->MeshRenderData->ScreenSize[BatchElement.InstancedLODIndex].GetValue(), SphereRadius, View->ViewMatrices.GetProjectionMatrix()) * LODScale;
					if (CurCut < FinalCull)
					{
						InstancingViewZCompare.Y = CurCut;
					}
					else
					{
						// this LOD is completely removed by one of the other two factors
						InstancingViewZCompare.Y = MIN_flt;
						InstancingViewZCompare.Z = MIN_flt;
					}
				}
				else
				{
					// this is the first LOD, so we don't have a fade-in region
					InstancingViewZCompare.Y = MIN_flt;
				}
			}

			InstancingOffset = InstancingUserData->InstancingOffset;
			InstancingWorldViewOriginZero = View->GetTemporalLODOrigin(0);
			InstancingWorldViewOriginOne = View->GetTemporalLODOrigin(1);

			float Alpha = View->GetTemporalLODTransition();
			InstancingWorldViewOriginZero.W = 1.0f - Alpha;
			InstancingWorldViewOriginOne.W = Alpha;

			InstancingViewZCompareZero.W = LODRandom;
		}

		ShaderBindings.Add(InstancingViewZCompareZeroParameter, InstancingViewZCompareZero);
		ShaderBindings.Add(InstancingViewZCompareOneParameter, InstancingViewZCompareOne);
		ShaderBindings.Add(InstancingViewZConstantParameter, InstancingViewZConstant);
		ShaderBindings.Add(InstancingOffsetParameter, InstancingOffset);
		ShaderBindings.Add(InstancingWorldViewOriginZeroParameter, InstancingWorldViewOriginZero);
		ShaderBindings.Add(InstancingWorldViewOriginOneParameter, InstancingWorldViewOriginOne);
	}

	if( InstancingFadeOutParamsParameter.IsBound() )
	{
		FVector4 InstancingFadeOutParams(MAX_flt,0.f,1.f,1.f);
		if (InstancingUserData)
		{
			const float MaxDrawDistanceScale = GetCachedScalabilityCVars().ViewDistanceScale;
			const float StartDistance = InstancingUserData->StartCullDistance * MaxDrawDistanceScale;
			const float EndDistance = InstancingUserData->EndCullDistance * MaxDrawDistanceScale;

			InstancingFadeOutParams.X = StartDistance;
			if( EndDistance > 0 )
			{
				if( EndDistance > StartDistance )
				{
					InstancingFadeOutParams.Y = 1.f / (float)(EndDistance - StartDistance);
				}
				else
				{
					InstancingFadeOutParams.Y = 1.f;
				}
			}
			else
			{
				InstancingFadeOutParams.Y = 0.f;
			}

			InstancingFadeOutParams.Z = InstancingUserData->bRenderSelected ? 1.f : 0.f;
			InstancingFadeOutParams.W = InstancingUserData->bRenderUnselected ? 1.f : 0.f;
		}

		ShaderBindings.Add(InstancingFadeOutParamsParameter, InstancingFadeOutParams);

	}
}


UCsInstancedStaticMeshComponent::UCsInstancedStaticMeshComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Mobility = EComponentMobility::Movable;
	BodyInstance.bSimulatePhysics = false;

	bDisallowMeshPaintPerInstance = true;
}

UCsInstancedStaticMeshComponent::UCsInstancedStaticMeshComponent(FVTableHelper& Helper)
	: Super(Helper)
{
}

UCsInstancedStaticMeshComponent::~UCsInstancedStaticMeshComponent()
{
	ReleasePerInstanceRenderData();
}

// UObject Interface
#pragma region

void UCsInstancedStaticMeshComponent::BeginDestroy()
{
	ReleasePerInstanceRenderData();
	Super::BeginDestroy();
}

#pragma endregion UObject Interface

// UPrimitiveComponent Interface
#pragma region

FPrimitiveSceneProxy* UCsInstancedStaticMeshComponent::CreateSceneProxy()
{
	LLM_SCOPE(ELLMTag::InstancedMesh);

	// Verify that the mesh is valid before using it.
	const bool IsMeshValid = 
		// make sure we have instances
		PerInstanceSMData.Num() > 0 &&
		// make sure we have an actual static mesh
		GetStaticMesh() &&
		GetStaticMesh()->HasValidRenderData() &&
		// You really can't use hardware instancing on the consoles with multiple elements because they share the same index buffer. 
		// @todo: Level error or something to let LDs know this
		1;//GetStaticMesh()->LODModels(0).Elements.Num() == 1;

	if (IsMeshValid)
	{
		typedef NCsStaticMesh::NInstanced::FSceneProxy SceneProxyType;

		return ::new SceneProxyType(this, GetWorld()->FeatureLevel);
	}
	else
	{
		return nullptr;
	}
}

FBoxSphereBounds UCsInstancedStaticMeshComponent::CalcBounds(const FTransform& BoundTransform) const
{
	if (GetStaticMesh() && 
		PerInstanceSMData.Num() > 0)
	{
		FMatrix BoundTransformMatrix = BoundTransform.ToMatrixWithScale();

		FBoxSphereBounds RenderBounds = GetStaticMesh()->GetBounds();
		FBoxSphereBounds NewBounds    = RenderBounds.TransformBy(PerInstanceSMData[0].Transform * BoundTransformMatrix);

		for (int32 InstanceIndex = 1; InstanceIndex < PerInstanceSMData.Num(); InstanceIndex++)
		{
			NewBounds = NewBounds + RenderBounds.TransformBy(PerInstanceSMData[InstanceIndex].Transform * BoundTransformMatrix);
		}

		return NewBounds;
	}
	else
	{
		return FBoxSphereBounds(BoundTransform.GetLocation(), FVector::ZeroVector, 0.f);
	}
}

#pragma endregion UPrimitiveComponent Interface

#define PayloadType NCsStaticMesh::NInstanced::NInit::FPayload
void UCsInstancedStaticMeshComponent::Init(const PayloadType& Payload)
{
	// TODO: Check Payload is Valid

	FStaticMeshInstanceData Data = FStaticMeshInstanceData(GVertexElementTypeSupport.IsSupported(VET_Half2));

	MaxInstances		= Payload.MaxInstances;
	NumCustomDataFloats = Payload.NumCustomDataFloats;
	StartCullDistance	= Payload.CullDistance;
	EndCullDistance		= Payload.CullDistance;

	PerInstanceSMData.Reset(NumCustomDataFloats * NumInstances);

	Data.AllocateInstances(NumInstances, NumCustomDataFloats, EResizeBufferFlags::None, true);

	UWorld* World						= GetWorld();
	ERHIFeatureLevel::Type FeatureLevel = World != nullptr ? World->FeatureLevel.GetValue() : GMaxRHIFeatureLevel;

	bool KeepInstanceBufferCPUAccess = false;//GIsEditor || InRequireCPUAccess || ComponentRequestsCPUAccess(this, FeatureLevel);

	PerInstanceRenderData->Init(Data);

	typedef NCsStaticMesh::NInstanced::NPerInstance::FRenderData PerInstanceRenderDataType;

	PerInstanceRenderData = MakeShareable(new PerInstanceRenderDataType(Data, FeatureLevel, KeepInstanceBufferCPUAccess));

	bInitialized = true;
}
#undef PayloadType

void UCsInstancedStaticMeshComponent::Update(const FCsDeltaTime& DeltaTime)
{
	if (CmdBuffer.IsComplete())
	{
		CmdBuffer.CopyAndEmpty(QueuedCmdBuffer);

		if (CmdBuffer.HasEdits())
		{
			PerInstanceRenderData->UpdateFromCommandBuffer(CmdBuffer);
		}
	}
}

void UCsInstancedStaticMeshComponent::ReleasePerInstanceRenderData()
{
	if (PerInstanceRenderData.IsValid())
	{
		typedef NCsStaticMesh::NInstanced::NPerInstance::FRenderData PerInstanceRenderDataType;

		typedef TSharedPtr<PerInstanceRenderDataType, ESPMode::ThreadSafe> PerInstanceRenderDataPtrType;

		// Make shared pointer object on the heap
		PerInstanceRenderDataPtrType* CleanupRenderDataPtr = new PerInstanceRenderDataPtrType(PerInstanceRenderData);
		PerInstanceRenderData.Reset();

		PerInstanceRenderDataPtrType* InCleanupRenderDataPtr = CleanupRenderDataPtr;

		ENQUEUE_RENDER_COMMAND(FReleasePerInstanceRenderData)(
			[InCleanupRenderDataPtr](FRHICommandList& RHICmdList)
			{
				// Destroy the shared pointer object we allocated on the heap.
				// Resource will either be released here or by scene proxy on the render thread, whoever gets executed last
				delete InCleanupRenderDataPtr;
			});
	} //-V773
}

float UCsInstancedStaticMeshComponent::GetTextureStreamingTransformScale() const
{
	// By default if there are no per instance data, use a scale of 1.
	// This is required because some derived class use the instancing system without filling the per instance data. (like landscape grass)
	// In those cases, we assume the instance are spreaded across the bounds with a scale of 1.
	float TransformScale = 1.f; 

	if (PerInstanceSMData.Num() > 0)
	{
		TransformScale = Super::GetTextureStreamingTransformScale();

		float WeightedAxisScaleSum = 0;
		float WeightSum = 0;

		for (int32 InstanceIndex = 0; InstanceIndex < PerInstanceSMData.Num(); InstanceIndex++)
		{
			const float AxisScale = PerInstanceSMData[InstanceIndex].Transform.GetMaximumAxisScale();
			const float Weight = AxisScale; // The weight is the axis scale since we want to weight by surface coverage.
			WeightedAxisScaleSum += AxisScale * Weight;
			WeightSum += Weight;
		}

		if (WeightSum > SMALL_NUMBER)
		{
			TransformScale *= WeightedAxisScaleSum / WeightSum;
		}
	}
	return TransformScale;
}

bool UCsInstancedStaticMeshComponent::GetMaterialStreamingData(int32 MaterialIndex, FPrimitiveMaterialInfo& MaterialData) const
{
	// Same thing as StaticMesh but we take the full bounds to cover the instances.
	if (GetStaticMesh())
	{
		MaterialData.Material = GetMaterial(MaterialIndex);
		MaterialData.UVChannelData = GetStaticMesh()->GetUVChannelData(MaterialIndex);
		MaterialData.PackedRelativeBox = PackedRelativeBox_Identity;
	}
	return MaterialData.IsValid();
}

bool UCsInstancedStaticMeshComponent::BuildTextureStreamingData(ETextureStreamingBuildType BuildType, EMaterialQualityLevel::Type QualityLevel, ERHIFeatureLevel::Type FeatureLevel, TSet<FGuid>& DependentResources)
{
#if WITH_EDITORONLY_DATA // Only rebuild the data in editor 
	if (GetInstanceCount() > 0)
	{
		return Super::BuildTextureStreamingData(BuildType, QualityLevel, FeatureLevel, DependentResources);
	}
#endif
	return true;
}

void UCsInstancedStaticMeshComponent::GetStreamingRenderAssetInfo(FStreamingTextureLevelContext& LevelContext, TArray<FStreamingRenderAssetPrimitiveInfo>& OutStreamingRenderAssets) const
{
	// Don't only look the instance count but also if the bound is valid, as derived classes might not set PerInstanceSMData.
	if (GetInstanceCount() > 0 || Bounds.SphereRadius > 0)
	{
		return Super::GetStreamingRenderAssetInfo(LevelContext, OutStreamingRenderAssets);
	}
}

void UCsInstancedStaticMeshComponent::SetCullDistances(int32 InStartCullDistance, int32 InEndCullDistance)
{
	StartCullDistance = InStartCullDistance;
	EndCullDistance   = InEndCullDistance;

	MarkRenderStateDirty();
}

static bool ComponentRequestsCPUAccess(UInstancedStaticMeshComponent* InComponent, ERHIFeatureLevel::Type FeatureLevel)
{
	if (FeatureLevel > ERHIFeatureLevel::ES3_1)
	{
		static const auto CVar = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.GenerateMeshDistanceFields"));

		bool bNeedsCPUAccess = (InComponent->CastShadow && InComponent->bAffectDistanceFieldLighting 
			// Distance field algorithms need access to instance data on the CPU
			&& (CVar->GetValueOnAnyThread(true) != 0 || (InComponent->GetStaticMesh() && InComponent->GetStaticMesh()->bGenerateMeshDistanceField)));

		// Ray tracing needs instance transforms on CPU
		bNeedsCPUAccess |= IsRayTracingEnabled();

		return bNeedsCPUAccess;
	}
	return false;
}

void UCsInstancedStaticMeshComponent::GetInstancesMinMaxScale(FVector& MinScale, FVector& MaxScale) const
{
	typedef NCsStaticMesh::NInstanced::NInstance::FData InstanceDataType;

	const int32 Count = PerInstanceSMData.Num();

	if (Count > 0)
	{
		MinScale = FVector(MAX_flt);
		MaxScale = FVector(-MAX_flt);

		for (int32 I = 0; I < Count; ++I)
		{
			const InstanceDataType& InstanceData = PerInstanceSMData[I];
			FVector ScaleVector					 = InstanceData.Transform.GetScaleVector();

			MinScale = MinScale.ComponentMin(ScaleVector);
			MaxScale = MaxScale.ComponentMax(ScaleVector);
		}
	}
	else
	{
		MinScale = FVector(1.0f);
		MaxScale = FVector(1.0f);
	}
}