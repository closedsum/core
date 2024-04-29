//// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
//#pragma once
//// Types
//#include "CsMacro_Misc.h"
//#include "Managers/Time/CsTypes_Time.h"
//// Vertex Factory
//#include "VertexFactory/CsLocalVertexFactory.h"
//// Component
//#include "Components/StaticMeshComponent.h"
//
//#include "CsInstancedStaticMeshComponent.generated.h"
//
//// This must match the maximum a user could specify in the material (see 
//// FHLSLMaterialTranslator::TextureCoordinate), otherwise the material will attempt 
//// to look up a texture coordinate we didn't provide an element for.
//extern CSCORE_API const int32 CsInstancedStaticMeshMaxTexCoord;
//
//class FPrimitiveSceneProxy;
//class FStaticMeshInstanceData;
//
//BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT(FCsInstancedStaticMeshVertexFactoryUniformShaderParameters, CSCORE_API)
//	SHADER_PARAMETER_SRV(Buffer<float4>, VertexFetch_InstanceOriginBuffer)
//	SHADER_PARAMETER_SRV(Buffer<float4>, VertexFetch_InstanceTransformBuffer)
//	SHADER_PARAMETER_SRV(Buffer<float4>, VertexFetch_InstanceLightmapBuffer)
//	SHADER_PARAMETER_SRV(Buffer<float>, InstanceCustomDataBuffer)
//	SHADER_PARAMETER(int32, NumCustomDataFloats)
//END_GLOBAL_SHADER_PARAMETER_STRUCT()
//
//// InstanceDataType (NCsStaticMesh::NInstanced::NInstance::FData)
//#pragma region
//
//namespace NCsStaticMesh
//{
//	namespace NInstanced
//	{
//		namespace NInstance
//		{
//			struct CSCORE_API FData
//			{
//			public:
//
//				FMatrix Transform;
//
//				FData() :
//					Transform(FMatrix::Identity)
//				{
//				}
//			};
//		}
//	}
//}
//
//#pragma endregion InstanceDataType (NCsStaticMesh::NInstanced::NInstance::FData)
//
//// CommandBufferType (NCsStaticMesh::NInstanced::NUpdate::NCommand::FBuffer)
//#pragma region
//
//namespace NCsStaticMesh
//{
//	namespace NInstanced
//	{
//		namespace NUpdate
//		{
//			namespace NCommand
//			{
//				enum class EEdit : uint8 
//				{
//					Update,
//					Remove,
//					Swap
//				};
//
//				struct CSCORE_API FEdit
//				{
//				public:
//
//					EEdit Type;
//
//					int32 TransformIndex;
//
//					int32 CustomDataIndex;
//
//					int32 InstanceIndex;
//
//					int32 SwapIndex;
//
//					FEdit() :
//						Type(EEdit::Update),
//						TransformIndex(INDEX_NONE),
//						CustomDataIndex(INDEX_NONE),
//						InstanceIndex(INDEX_NONE)
//					{
//					}
//
//					FORCEINLINE bool IsUpdate() const { return Type == EEdit::Update; }
//					FORCEINLINE bool IsRemove() const { return Type == EEdit::Remove; }
//					FORCEINLINE bool IsSwap() const { return Type == EEdit::Swap; }
//
//					FORCEINLINE bool HasTransform() const { return TransformIndex != INDEX_NONE; }
//					FORCEINLINE bool HasCustomData() const { return CustomDataIndex != INDEX_NONE; }
//				};
//
//				struct CSCORE_API FEditTransforms
//				{
//				public:
//
//					TArray<int32> Indices;
//
//					TArray<FMatrix44f> Transforms;
//
//					FEditTransforms() :
//						Indices(),
//						Transforms()
//					{
//					}
//
//					void SetSize(const int32& InSize)
//					{
//						check(InSize > 0);
//
//						Indices.Reset(InSize);
//						Transforms.Reset(InSize);
//					}
//
//					FORCEINLINE int32 Num() const { return Indices.Num(); }
//
//					FORCEINLINE bool HasEdits() const { return Num() > 0; }
//
//					void Reset()
//					{
//						Indices.Reset(Indices.Max());
//						Transforms.Reset(Transforms.Max());
//					}
//
//					void CopyAndEmpty(FEditTransforms& From)
//					{
//						Reset();
//
//						const int32 Count = Num();
//
//						for (int32 I = 0; I < Count; ++I)
//						{
//							Indices.Add(From.Indices[I]);
//							Transforms.Add(From.Transforms[I]);
//						}
//						From.Reset();
//					}
//				};
//
//				struct CSCORE_API FEditCustomDatas
//				{
//				public:
//
//					TArray<int32> Indices;
//
//					TArray<float> CustomDatas;
//
//					int32 Stride;
//
//					FEditCustomDatas() :
//						Indices(),
//						CustomDatas(),
//						Stride()
//					{
//					}
//
//					void SetSize(const int32& InSize, const int32& InStride)
//					{
//						check(InSize > 0);
//						check(InStride > 0);
//
//						Stride = InStride;
//
//						Indices.Reset(InSize);
//						CustomDatas.Reset(Stride * InSize);
//					}
//
//					FORCEINLINE int32 Num() const { return Indices.Num(); }
//
//					FORCEINLINE bool HasEdits() const { return Num() > 0; }
//
//					void Reset()
//					{
//						Indices.Reset(Indices.Max());
//						CustomDatas.Reset(CustomDatas.Max());
//					}
//
//					void CopyAndEmpty(FEditCustomDatas& From)
//					{
//						Reset();
//
//						for (int32& Index : From.Indices)
//						{
//							Indices.Add(Index);
//						}
//
//						for (float& Value : From.CustomDatas)
//						{
//							CustomDatas.Add(Value);
//						}
//						From.Reset();
//					}
//				};
//
//				struct CSCORE_API FBuffer
//				{
//				#define EditType NCsStaticMesh::NInstanced::NUpdate::NCommand::FEdit
//				#define EditTransformsType NCsStaticMesh::NInstanced::NUpdate::NCommand::FEditTransforms
//				#define EditCustomDatasType NCsStaticMesh::NInstanced::NUpdate::NCommand::FEditCustomDatas
//
//				public:
//
//					bool bComplete;
//
//					TArray<EditType> Edits;
//
//					EditTransformsType EditTransforms;
//
//					EditCustomDatasType EditCustomDatas;
//
//					FBuffer() :
//						bComplete(false),
//						Edits(),
//						EditTransforms(),
//						EditCustomDatas()
//					{
//					}
//
//					void SetSize(const int32& InSize, const int32& InStride)
//					{
//						check(InSize > 0);
//						check(InStride > 0);
//
//						Edits.Reset(4 * InSize);
//						EditTransforms.SetSize(InSize);
//						EditCustomDatas.SetSize(InSize, InStride);
//					}
//
//					FORCEINLINE void Start() { bComplete = false; }
//					FORCEINLINE bool IsComplete() const { return bComplete; }
//					FORCEINLINE void Complete() { bComplete = true; }
//
//					FORCEINLINE bool HasEdits() const { return Edits.Num() > 0; }
//
//					void CopyAndEmpty(FBuffer& From)
//					{
//						Clear();
//
//						for (EditType& Edit : From.Edits)
//						{
//							Edits.Add(Edit);
//						}
//
//						EditTransforms.CopyAndEmpty(From.EditTransforms);
//						EditCustomDatas.CopyAndEmpty(From.EditCustomDatas);
//
//						From.Clear();
//					}
//
//					void Clear()
//					{
//						Edits.Reset(Edits.Max());
//						EditTransforms.Reset();
//						EditCustomDatas.Reset();
//					}
//
//				#undef EditType
//				#undef EditTransformsType
//				#undef EditCustomDatasType
//				};
//			}
//		}
//	}
//}
//
//#pragma endregion CommandBufferType (NCsStaticMesh::NInstanced::NUpdate::NCommand::FBuffer)
//
//// DataType (NCsStaticMesh::NInstanced::FDataType)
//#pragma region
//
//class FRHIShaderResourceView;
//
//namespace NCsStaticMesh
//{
//	namespace NInstanced
//	{
//		struct FDataType
//		{
//		public:
//
//			/** The stream to read the mesh transform from. */
//			FVertexStreamComponent InstanceOriginComponent;
//
//			/** The stream to read the mesh transform from. */
//			FVertexStreamComponent InstanceTransformComponent[3];
//
//			/** The stream to read the Lightmap Bias and Random instance ID from. */
//			FVertexStreamComponent InstanceLightmapAndShadowMapUVBiasComponent;
//
//			FRHIShaderResourceView* InstanceOriginSRV;
//			FRHIShaderResourceView* InstanceTransformSRV ;
//			FRHIShaderResourceView* InstanceLightmapSRV;
//			FRHIShaderResourceView* InstanceCustomDataSRV;
//
//			int32 NumCustomDataFloats;
//
//			FDataType() : 
//				InstanceOriginComponent(),
//				InstanceLightmapAndShadowMapUVBiasComponent(),
//				InstanceOriginSRV(nullptr),
//				InstanceTransformSRV(nullptr),
//				InstanceLightmapSRV(nullptr),
//				InstanceCustomDataSRV(nullptr),
//				NumCustomDataFloats(0)
//			{
//			}
//		};
//	}
//}
//
//#pragma endregion DataType (NCsStaticMesh::NInstanced::FDataType)
//
//// VertexFactoryType (FCsInstancedStaticMeshVertexFactory)
//#pragma region
//
///**
// * A vertex factory for instanced static meshes
// */
//struct FCsInstancedStaticMeshVertexFactory : public FLocalVertexFactory
//{
//	DECLARE_VERTEX_FACTORY_TYPE(FCsInstancedStaticMeshVertexFactory);
//
//public:
//
//	FCsInstancedStaticMeshVertexFactory(ERHIFeatureLevel::Type InFeatureLevel)
//		: FLocalVertexFactory(InFeatureLevel, "FCsInstancedStaticMeshVertexFactory")
//	{
//	}
//
//	struct FDataType : public NCsStaticMesh::NInstanced::FDataType, 
//					   public FLocalVertexFactory::FDataType
//	{
//	};
//
//	/**
//	 * Should we cache the material's shadertype on this platform with this vertex factory? 
//	 */
//	static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters);
//
//	/**
//	 * Modify compile environment to enable instancing
//	 * @param OutEnvironment - shader compile environment to modify
//	 */
//	static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);
//
//	/**
//	 * An implementation of the interface used by TSynchronizedResource to update the resource with new data from the game thread.
//	 */
//	void SetData(const FDataType& InData)
//	{
//		FLocalVertexFactory::Data = InData;
//		Data = InData;
//		UpdateRHI();
//	}
//
//	/**
//	 * Copy the data from another vertex factory
//	 * @param Other - factory to copy from
//	 */
//	void Copy(const FCsInstancedStaticMeshVertexFactory& Other);
//
//	// FRenderResource interface.
//	virtual void InitRHI() override;
//
//	/** Make sure we account for changes in the signature of GetStaticBatchElementVisibility() */
//	static CONSTEXPR uint32 NumBitsForVisibilityMask()
//	{		
//		return 8 * sizeof(uint64);
//	}
//
//#if ALLOW_DITHERED_LOD_FOR_INSTANCED_STATIC_MESHES
//	bool SupportsNullPixelShader() const { return false; }
//#endif
//
//	FORCEINLINE FRHIShaderResourceView* GetInstanceOriginSRV() const { return Data.InstanceOriginSRV; }
//	FORCEINLINE FRHIShaderResourceView* GetInstanceTransformSRV() const { return Data.InstanceTransformSRV; }
//	FORCEINLINE FRHIShaderResourceView* GetInstanceLightmapSRV() const { return Data.InstanceLightmapSRV; }
//	FORCEINLINE FRHIShaderResourceView* GetInstanceCustomDataSRV() const { return Data.InstanceCustomDataSRV; }
//	FORCEINLINE FRHIUniformBuffer* GetUniformBuffer() const { return UniformBuffer.GetReference(); }
//
//private:
//
//	FDataType Data;
//
//	TUniformBufferRef<FCsInstancedStaticMeshVertexFactoryUniformShaderParameters> UniformBuffer;
//};
//
//#pragma endregion VertexFactoryType (FCsInstancedStaticMeshVertexFactory)
//
//// ShaderParametersType (FCsInstancedStaticMeshVertexFactoryShaderParameters)
//#pragma region
//
//class CSCORE_API FCsInstancedStaticMeshVertexFactoryShaderParameters : public FCsLocalVertexFactoryShaderParametersBase
//{
//	DECLARE_TYPE_LAYOUT(FCsInstancedStaticMeshVertexFactoryShaderParameters, NonVirtual);
//
//public:
//
//	void Bind(const FShaderParameterMap& ParameterMap)
//	{
//		FCsLocalVertexFactoryShaderParametersBase::Bind(ParameterMap);
//
//		InstancingFadeOutParamsParameter.Bind(ParameterMap, TEXT("InstancingFadeOutParams"));
//		InstancingViewZCompareZeroParameter.Bind(ParameterMap, TEXT("InstancingViewZCompareZero"));
//		InstancingViewZCompareOneParameter.Bind(ParameterMap, TEXT("InstancingViewZCompareOne"));
//		InstancingViewZConstantParameter.Bind(ParameterMap, TEXT("InstancingViewZConstant"));
//		InstancingOffsetParameter.Bind(ParameterMap, TEXT("InstancingOffset"));
//		InstancingWorldViewOriginZeroParameter.Bind(ParameterMap, TEXT("InstancingWorldViewOriginZero"));
//		InstancingWorldViewOriginOneParameter.Bind(ParameterMap, TEXT("InstancingWorldViewOriginOne"));
//		VertexFetch_InstanceOriginBufferParameter.Bind(ParameterMap, TEXT("VertexFetch_InstanceOriginBuffer"));
//		VertexFetch_InstanceTransformBufferParameter.Bind(ParameterMap, TEXT("VertexFetch_InstanceTransformBuffer"));
//		VertexFetch_InstanceLightmapBufferParameter.Bind(ParameterMap, TEXT("VertexFetch_InstanceLightmapBuffer"));
//		InstanceOffset.Bind(ParameterMap, TEXT("InstanceOffset"));
//	}
//
//	void GetElementShaderBindings(
//		const class FSceneInterface* Scene,
//		const FSceneView* View,
//		const FMeshMaterialShader* Shader,
//		const EVertexInputStreamType InputStreamType,
//		ERHIFeatureLevel::Type FeatureLevel,
//		const FVertexFactory* VertexFactory,
//		const FMeshBatchElement& BatchElement,
//		FMeshDrawSingleShaderBindings& ShaderBindings,
//		FVertexInputStreamArray& VertexStreams
//		) const;
//
//private:
//	
//	LAYOUT_FIELD(FShaderParameter, InstancingFadeOutParamsParameter)
//	LAYOUT_FIELD(FShaderParameter, InstancingViewZCompareZeroParameter)
//	LAYOUT_FIELD(FShaderParameter, InstancingViewZCompareOneParameter)
//	LAYOUT_FIELD(FShaderParameter, InstancingViewZConstantParameter)
//	LAYOUT_FIELD(FShaderParameter, InstancingOffsetParameter);
//	LAYOUT_FIELD(FShaderParameter, InstancingWorldViewOriginZeroParameter)
//	LAYOUT_FIELD(FShaderParameter, InstancingWorldViewOriginOneParameter)
//
//	LAYOUT_FIELD(FShaderResourceParameter, VertexFetch_InstanceOriginBufferParameter)
//	LAYOUT_FIELD(FShaderResourceParameter, VertexFetch_InstanceTransformBufferParameter)
//	LAYOUT_FIELD(FShaderResourceParameter, VertexFetch_InstanceLightmapBufferParameter)
//	LAYOUT_FIELD(FShaderParameter, InstanceOffset)
//};
//
//#pragma endregion ShaderParametersType (FCsInstancedStaticMeshVertexFactoryShaderParameters)
//
//// InstancingUserDataType (NCsStaticMesh::NInstanced::NInstancing::FUserData)
//#pragma region
//
//// NCsStaticMesh::NInstanced::FRenderData
//CS_FWD_DECLARE_CLASS_NAMESPACE_2(NCsStaticMesh, NInstanced, FRenderData)
//
//class FStaticMeshRenderData;
//
//namespace NCsStaticMesh
//{
//	namespace NInstanced
//	{
//		namespace NInstancing
//		{
//			struct CSCORE_API FUserData
//			{
//			#define InstancedRenderDataType NCsStaticMesh::NInstanced::FRenderData
//
//			public:
//
//				InstancedRenderDataType* RenderData;
//				FStaticMeshRenderData* MeshRenderData;
//
//				int32 StartCullDistance;
//				int32 EndCullDistance;
//
//				int32 MinLOD;
//
//				bool bRenderSelected;
//				bool bRenderUnselected;
//				FVector3d AverageInstancesScale;
//				FVector3d InstancingOffset;
//
//				FUserData() :
//					RenderData(nullptr),
//					MeshRenderData(nullptr),
//					StartCullDistance(0.0f),
//					EndCullDistance(0.0f),
//					MinLOD(0),
//					bRenderSelected(true),
//					bRenderUnselected(false),
//					AverageInstancesScale(0.0f),
//					InstancingOffset(0.0f)
//				{
//				}
//
//			#undef InstancedRenderDataType
//			};
//		}
//	}
//}
//
//#pragma endregion InstancingUserDataType (NCsStaticMesh::NInstanced::NInstancing::FUserData)
//
//// InstanceBufferType (NCsStaticMesh::NInstanced::NInstance::FBuffer)
//#pragma region
//
//namespace NCsStaticMesh
//{
//	namespace NInstanced
//	{
//		namespace NInstance
//		{
//			/** A vertex buffer of positions. */
//			class CSCORE_API FBuffer : public FRenderResource
//			{
//			public:
//
//				/** Default constructor. */
//				FBuffer(ERHIFeatureLevel::Type InFeatureLevel, bool InRequireCPUAccess);
//
//				/** Destructor. */
//				~FBuffer();
//
//			private:
//
//				/** Delete existing resources */
//				void CleanUp();
//
//			public:
//
//				/**
//				 * Initializes the buffer with the component's data.
//				 * @param Other - instance data, this call assumes the memory, so this will be empty after the call
//				 */
//				void Init(FStaticMeshInstanceData& Other);
//
//			#define CommandBufferType NCsStaticMesh::NInstanced::NUpdate::NCommand::FBuffer
//				void UpdateFromCommandBuffer_GameThread(CommandBufferType& CmdBuffer);
//			private:
//				void UpdateFromCommandBuffer_RenderThread(CommandBufferType& CmdBuffer);
//			#undef CommandBufferType
//
//			public:
//
//				FORCEINLINE uint32 GetNumInstances() const
//				{
//					return InstanceData->GetNumInstances();
//				}
//
//				FORCEINLINE void GetInstanceTransform(int32 InstanceIndex, FMatrix& Transform) const
//				{
//					FRenderTransform RenderTransform(Transform);
//					InstanceData->GetInstanceTransform(InstanceIndex, RenderTransform);
//				}
//
//				FORCEINLINE void GetInstanceShaderValues(int32 InstanceIndex, FVector4f (&InstanceTransform)[3], FVector4f& InstanceLightmapAndShadowMapUVBias, FVector4f& InstanceOrigin) const
//				{
//					//InstanceData->GetInstanceShaderValues(InstanceIndex, InstanceTransform, InstanceLightmapAndShadowMapUVBias, InstanceOrigin);
//					InstanceData->GetInstanceLightMapData(InstanceIndex, InstanceLightmapAndShadowMapUVBias);
//				}
//	
//				FORCEINLINE void GetInstanceCustomDataValues(int32 InstanceIndex, TArray<float>& InstanceCustomData) const
//				{
//					InstanceData->GetInstanceCustomDataValues(InstanceIndex, InstanceCustomData);
//				}
//	
//				FORCEINLINE FStaticMeshInstanceData* GetInstanceData() const
//				{
//					return InstanceData.Get();
//				}
//
//			// FRenderResource Interface
//			#pragma region
//			public:
//
//				virtual void InitRHI() override;
//				virtual void ReleaseRHI() override;
//				virtual void InitResource() override;
//				virtual void ReleaseResource() override;
//				virtual FString GetFriendlyName() const override { return TEXT("Static-mesh instances"); }
//
//			#pragma endregion FRenderResource Interface
//
//			public:
//
//				SIZE_T GetResourceSize() const;
//
//			#define DataType NCsStaticMesh::NInstanced::FDataType
//				void BindInstanceVertexBuffer(const FVertexFactory* VertexFactory, DataType& InstancedStaticMeshData) const;
//			#undef DataType
//
//				/** The vertex data storage type */
//				TSharedPtr<FStaticMeshInstanceData, ESPMode::ThreadSafe> InstanceData;
//
//				/** Keep CPU copy of instance data*/
//				bool RequireCPUAccess;
//
//				FORCEINLINE FBufferRHIRef GetInstanceOriginBuffer() { return InstanceOriginBuffer.VertexBufferRHI; }
//				FORCEINLINE FBufferRHIRef GetInstanceTransformBuffer() { return InstanceTransformBuffer.VertexBufferRHI; }
//				FORCEINLINE FBufferRHIRef GetInstanceLightmapBuffer() { return InstanceLightmapBuffer.VertexBufferRHI; }
//				FORCEINLINE FBufferRHIRef GetInstanceCustomDataBuffer() { return InstanceCustomDataBuffer.VertexBufferRHI; }
//
//			private:
//
//				class FInstanceOriginBuffer : public FVertexBuffer
//				{
//					virtual FString GetFriendlyName() const override { return TEXT("FInstanceOriginBuffer"); }
//				} InstanceOriginBuffer;
//				FShaderResourceViewRHIRef InstanceOriginSRV;
//
//				class FInstanceTransformBuffer : public FVertexBuffer
//				{
//					virtual FString GetFriendlyName() const override { return TEXT("FInstanceTransformBuffer"); }
//				} InstanceTransformBuffer;
//				FShaderResourceViewRHIRef InstanceTransformSRV;
//
//				class FInstanceLightmapBuffer : public FVertexBuffer
//				{
//					virtual FString GetFriendlyName() const override { return TEXT("FInstanceLightmapBuffer"); }
//				} InstanceLightmapBuffer;
//				FShaderResourceViewRHIRef InstanceLightmapSRV;
//
//				class FInstanceCustomDataBuffer : public FVertexBuffer
//				{
//					virtual FString GetFriendlyName() const override { return TEXT("FInstanceCustomDataBuffer"); }
//				} InstanceCustomDataBuffer;
//				FShaderResourceViewRHIRef InstanceCustomDataSRV;	
//
//				void CreateVertexBuffer(FResourceArrayInterface* InResourceArray, uint32 InUsage, uint32 InStride, uint8 InFormat, FBufferRHIRef& OutVertexBufferRHI, FShaderResourceViewRHIRef& OutInstanceSRV);
//			};
//		}
//	}
//}
//	
//#pragma endregion  InstanceBufferType (NCsStaticMesh::NInstanced::NInstance::FBuffer)
//
//// PerInstanceRenderDataType (NCsStaticMesh::NInstanced::NPerInstance::FRenderData)
//#pragma region
//
//namespace NCsStaticMesh
//{
//	namespace NInstanced
//	{
//		namespace NPerInstance
//		{
//			/**
//			* Holds render data that can persist between scene proxy reconstruction
//			*/
//			struct CSCORE_API FRenderData
//			{
//			#define InstanceBufferType NCsStaticMesh::NInstanced::NInstance::FBuffer
//
//			public:
//
//				/** cached per-instance resource size*/
//				SIZE_T	ResourceSize;
//
//				/** Instance buffer */
//				InstanceBufferType InstanceBuffer;
//				TSharedPtr<FStaticMeshInstanceData, ESPMode::ThreadSafe> InstanceBuffer_GameThread;
//
//				int32 NumInstances;
//
//				// Should be always constructed on main thread
//				FRenderData(FStaticMeshInstanceData& Other, ERHIFeatureLevel::Type InFeaureLevel, bool InRequireCPUAccess);
//				~FRenderData();
//
//				/**
//				 * Call to update the Instance buffer with pre allocated data without recreating the FPerInstanceRenderData
//				 * @param InComponent - The owning component
//				 * @param InOther - The Instance data to copy into our instance buffer
//				 */
//				void Init(FStaticMeshInstanceData& InOther);
//
//				FORCEINLINE int32 GetNumInstances() const { return NumInstances; }
//
//			#define CommandBufferType NCsStaticMesh::NInstanced::NUpdate::NCommand::FBuffer
//				/**
//				*/
//				void UpdateFromCommandBuffer(CommandBufferType& CmdBuffer);
//			#undef CommandBufferType
//
//			#undef InstanceBufferType
//			};
//		}
//	}
//}
//
//#pragma endregion PerInstanceRenderDataType (NCsStaticMesh::NInstanced::NPerInstance::FRenderData)
//
//// RenderDataType (NCsStaticMesh::NInstanced::FRenderData)
//#pragma region
//
//class UCsInstancedStaticMeshComponent;
//
//namespace NCsStaticMesh
//{
//	namespace NInstanced
//	{
//		class CSCORE_API FRenderData
//		{
//		#define PerInstanceRenderDataType NCsStaticMesh::NInstanced::NPerInstance::FRenderData
//		#define VertexFactoryType FCsInstancedStaticMeshVertexFactory
//
//		public:
//
//			FRenderData(UCsInstancedStaticMeshComponent* InComponent, ERHIFeatureLevel::Type InFeatureLevel);
//
//			void ReleaseResources(FSceneInterface* Scene, const UStaticMesh* StaticMesh)
//			{
//				for (int32 LODIndex = 0; LODIndex < VertexFactories.Num(); LODIndex++)
//				{
//					VertexFactories[LODIndex].ReleaseResource();
//				}
//			}
//
//			/** Source component */
//			UCsInstancedStaticMeshComponent* Component;
//
//			/** Per instance render data, could be shared with component */
//			TSharedPtr<PerInstanceRenderDataType, ESPMode::ThreadSafe> PerInstanceRenderData;
//
//			/** Vertex factory */
//			TIndirectArray<VertexFactoryType> VertexFactories;
//
//			/** LOD render data from the static mesh. */
//			FStaticMeshLODResourcesArray& LODModels;
//
//			/** Feature level used when creating instance data */
//			ERHIFeatureLevel::Type FeatureLevel;
//
//		private:
//
//			void InitVertexFactories();
//
//		#undef PerInstanceRenderDataType
//		#undef VertexFactoryType
//		};
//	}
//}
//
//#pragma endregion RenderDataType (NCsStaticMesh::NInstanced::FRenderData)
//
//// SceneProxyType (NCsStaticMesh::NInstanced::FSceneProxy)
//#pragma region
//
//class UCsInstancedStaticMeshComponent;
//
//namespace NCsStaticMesh
//{
//	namespace NInstanced
//	{
//		class CSCORE_API FSceneProxy : public FStaticMeshSceneProxy
//		{
//		#define RenderDataType NCsStaticMesh::NInstanced::FRenderData
//		#define InstancingUserDataType NCsStaticMesh::NInstanced::NInstancing::FUserData
//
//		public:
//
//			FSceneProxy(UCsInstancedStaticMeshComponent* InComponent, ERHIFeatureLevel::Type InFeatureLevel);
//
//			~FSceneProxy()
//			{
//			}
//
//			SIZE_T GetTypeHash() const override;
//
//			// FPrimitiveSceneProxy interface.
//
//			virtual void DestroyRenderThreadResources() override;
//
//			virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
//			{
//				FPrimitiveViewRelevance Result;
//				if(View->Family->EngineShowFlags.InstancedStaticMeshes)
//				{
//					Result = FStaticMeshSceneProxy::GetViewRelevance(View);
//
//					Result.bDynamicRelevance = true;
//				}
//				return Result;
//			}
//
//			virtual void GetLightRelevance(const FLightSceneProxy* LightSceneProxy, bool& bDynamic, bool& bRelevant, bool& bLightMapped, bool& bShadowMapped) const override;
//			virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;
//
//			virtual int32 GetNumMeshBatches() const override
//			{
//				return 1;
//			}
//
//			/** Sets up a shadow FMeshBatch for a specific LOD. */
//			virtual bool GetShadowMeshElement(int32 LODIndex, int32 BatchIndex, uint8 InDepthPriorityGroup, FMeshBatch& OutMeshBatch, bool bDitheredLODTransition) const override;
//
//			/** Sets up a FMeshBatch for a specific LOD and element. */
//			virtual bool GetMeshElement(int32 LODIndex, int32 BatchIndex, int32 ElementIndex, uint8 InDepthPriorityGroup, bool bUseSelectionOutline, bool bAllowPreCulledIndices, FMeshBatch& OutMeshBatch) const override;
//
//			/** Sets up a wireframe FMeshBatch for a specific LOD. */
//			virtual bool GetWireframeMeshElement(int32 LODIndex, int32 BatchIndex, const FMaterialRenderProxy* WireframeRenderProxy, uint8 InDepthPriorityGroup, bool bAllowPreCulledIndices, FMeshBatch& OutMeshBatch) const override;
//
//			void GetDistancefieldAtlasData(FBox& LocalVolumeBounds, FVector2D& OutDistanceMinMax, FIntVector& OutBlockMin, FIntVector& OutBlockSize, bool& bOutBuiltAsIfTwoSided, bool& bMeshWasPlane, float& SelfShadowBias, TArray<FMatrix>& ObjectLocalToWorldTransforms, bool& bOutThrottled) const;
//
//			void GetDistanceFieldInstanceInfo(int32& NumInstances, float& BoundsSurfaceArea) const;
//
//			//int32 CollectOccluderElements(FOccluderElementsCollector& Collector) const { return 0; }
//
//			virtual bool IsDetailMesh() const override
//			{
//				return true;
//			}
//
//		protected:
//
//			/** Cache of the StaticMesh asset, needed to release SpeedTree resources*/
//			UStaticMesh* StaticMesh;
//
//			/** Per component render data */
//			RenderDataType InstancedRenderData;
//
//			/** LOD transition info. */
//			InstancingUserDataType UserData_AllInstances;
//			InstancingUserDataType UserData_SelectedInstances;
//			InstancingUserDataType UserData_DeselectedInstances;
//
//			/** Common path for the Get*MeshElement functions */
//			void SetupInstancedMeshBatch(int32 LODIndex, int32 BatchIndex, FMeshBatch& OutMeshBatch) const;
//
//		private:
//
//			void SetupProxy(UCsInstancedStaticMeshComponent* InComponent);
//
//		#undef RenderDataType
//		#undef InstancingUserDataType
//		};
//	}
//}
//
//#pragma endregion SceneProxyType (NCsStaticMesh::NInstanced::FSceneProxy)
//
//class UStaticMesh;
//
//namespace NCsStaticMesh
//{
//	namespace NInstanced
//	{
//		namespace NInit
//		{
//			struct CSCORE_API FPayload
//			{
//			public:
//
//				UStaticMesh* Mesh;
//				
//				int32 MaxInstances;
//
//				int32 NumCustomDataFloats;
//
//				int32 CullDistance;
//
//				FPayload() :
//					Mesh(nullptr),
//					MaxInstances(0),
//					NumCustomDataFloats(0),
//					CullDistance(100000.0f)
//				{
//				}
//			};
//		}
//	}
//}
//
///** A component that efficiently renders multiple instances of the same StaticMesh. */
//UCLASS()
//class CSCORE_API UCsInstancedStaticMeshComponent : public UStaticMeshComponent
//{
//	GENERATED_UCLASS_BODY()
//	
//	/** Needs implementation in InstancedStaticMesh.cpp to compile UniquePtr for forward declared class */
//	UCsInstancedStaticMeshComponent(FVTableHelper& Helper);
//	virtual ~UCsInstancedStaticMeshComponent();
//	
//// UObject Interface
//#pragma region
//public:
//
//	void BeginDestroy() override;
//
//#pragma endregion UObject Interface
//
//// UPrimitiveComponent Interface
//#pragma region
//public:
//
//	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
//
//public:
//
//	virtual FBoxSphereBounds CalcBounds(const FTransform3d& BoundTransform) const override;
//	virtual bool SupportsStaticLighting() const override { return false; }
//
//#pragma endregion UPrimitiveComponent Interface
//
//public:
//
//#define PayloadType NCsStaticMesh::NInstanced::NInit::FPayload
//	void Init(const PayloadType& Payload);
//#undef PayloadType
//
//	void Update(const FCsDeltaTime& DeltaTime);
//
//private:
//
//	bool bInitialized;
//
//	int32 MaxInstances;
//
//	int32 NumInstances;
//
//public:
//
//	FORCEINLINE int32 GetNumInstances() const { return NumInstances; }
//
//private:
//
//	/** Defines the number of floats that will be available per instance for custom data */
//	int32 NumCustomDataFloats;
//
//	/** Distance from camera at which each instance begins to fade out. */
//	int32 StartCullDistance;
//
//public:
//
//	FORCEINLINE int32 GetStartCullDistance() const { return StartCullDistance; }
//
//private:
//
//	/** Distance from camera at which each instance completely fades out. */
//	int32 EndCullDistance;
//
//public:
//
//	FORCEINLINE int32 GetEndCullDistance() const { return EndCullDistance; }
//
//private:
//
//#define InstanceDataType NCsStaticMesh::NInstanced::NInstance::FData
//	TArray<InstanceDataType> PerInstanceSMData;
//#undef InstanceDataType
//
//public:
//
//	FORCEINLINE int32 GetInstanceCount() const { return PerInstanceSMData.Num(); }
//
//#define PerInstanceRenderDataType NCsStaticMesh::NInstanced::NPerInstance::FRenderData
//	/** Render data will be initialized on demand. Released on the rendering thread. */
//	TSharedPtr<PerInstanceRenderDataType, ESPMode::ThreadSafe> PerInstanceRenderData;
//#undef PerInstanceRenderDataType
//
//private:
//
//#define CommandBufferType NCsStaticMesh::NInstanced::NUpdate::NCommand::FBuffer
//	/** Recorded modifications to per-instance data */
//	CommandBufferType CmdBuffer;
//	CommandBufferType QueuedCmdBuffer;
//#undef CommandBufferType
//
//public:
//
//	/** Get the scale coming form the component, when computing StreamingTexture data. Used to support instanced meshes. */
//	virtual float GetTextureStreamingTransformScale() const override;
//	/** Get material, UV density and bounds for a given material index. */
//	virtual bool GetMaterialStreamingData(int32 MaterialIndex, FPrimitiveMaterialInfo& MaterialData) const override;
//	/** Build the data to compute accuracte StreaminTexture data. */
//	bool BuildTextureStreamingData(ETextureStreamingBuildType BuildType, EMaterialQualityLevel::Type QualityLevel, ERHIFeatureLevel::Type FeatureLevel, TSet<FGuid>& DependentResources);
//	/** Get the StreaminTexture data. */
//	virtual void GetStreamingRenderAssetInfo(FStreamingTextureLevelContext& LevelContext, TArray<FStreamingRenderAssetPrimitiveInfo>& OutStreamingRenderAssets) const override;
//
//	/** Sets the fading start and culling end distances for this component. */
//	void SetCullDistances(int32 StartCullDistance, int32 EndCullDistance);
//
//	/** Transfers ownership of instance render data to a render thread. Instance render data will be released in scene proxy destructor or on render thread task. */
//	void ReleasePerInstanceRenderData();
//
//	void GetInstancesMinMaxScale(FVector3d& MinScale, FVector3d& MaxScale) const;
//};
