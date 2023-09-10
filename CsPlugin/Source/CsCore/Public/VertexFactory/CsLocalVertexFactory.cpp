// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "VertexFactory/CsLocalVertexFactory.h"

#include "SceneView.h"
#include "MeshBatch.h"
#include "SpeedTreeWind.h"
#include "ShaderParameterUtils.h"
#include "Rendering/ColorVertexBuffer.h"
#include "MeshMaterialShader.h"
#include "ProfilingDebugging/LoadTimeTracker.h"

IMPLEMENT_TYPE_LAYOUT(FCsLocalVertexFactoryShaderParametersBase);
IMPLEMENT_TYPE_LAYOUT(FCsLocalVertexFactoryShaderParameters);

void FCsLocalVertexFactoryShaderParametersBase::Bind(const FShaderParameterMap& ParameterMap)
{
	LODParameter.Bind(ParameterMap, TEXT("SpeedTreeLODInfo"));
	bAnySpeedTreeParamIsBound = LODParameter.IsBound() || ParameterMap.ContainsParameterAllocation(TEXT("SpeedTreeData"));
}

void FCsLocalVertexFactoryShaderParametersBase::GetElementShaderBindingsBase(
	const FSceneInterface* Scene,
	const FSceneView* View,
	const FMeshMaterialShader* Shader, 
	const EVertexInputStreamType InputStreamType,
	ERHIFeatureLevel::Type FeatureLevel,
	const FVertexFactory* VertexFactory, 
	const FMeshBatchElement& BatchElement,
	FRHIUniformBuffer* VertexFactoryUniformBuffer,
	FMeshDrawSingleShaderBindings& ShaderBindings,
	FVertexInputStreamArray& VertexStreams
	) const
{
	const auto* LocalVertexFactory = static_cast<const FLocalVertexFactory*>(VertexFactory);
	
	if (LocalVertexFactory->SupportsManualVertexFetch(FeatureLevel) || UseGPUScene(GMaxRHIShaderPlatform, FeatureLevel))
	{
		if (!VertexFactoryUniformBuffer)
		{
			// No batch element override
			VertexFactoryUniformBuffer = LocalVertexFactory->GetUniformBuffer();
		}

		//ShaderBindings.Add(Shader->GetUniformBufferParameter<FLocalVertexFactoryUniformShaderParameters>(), VertexFactoryUniformBuffer);
	}

	//@todo - allow FMeshBatch to supply vertex streams (instead of requiring that they come from the vertex factory), and this userdata hack will no longer be needed for override vertex color
	if (BatchElement.bUserDataIsColorVertexBuffer)
	{
		FColorVertexBuffer* OverrideColorVertexBuffer = (FColorVertexBuffer*)BatchElement.UserData;
		check(OverrideColorVertexBuffer);

		if (!LocalVertexFactory->SupportsManualVertexFetch(FeatureLevel))
		{
			LocalVertexFactory->GetColorOverrideStream(OverrideColorVertexBuffer, VertexStreams);
		}	
	}
}

void FCsLocalVertexFactoryShaderParameters::GetElementShaderBindings(
	const FSceneInterface* Scene,
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

	FCsLocalVertexFactoryShaderParametersBase::GetElementShaderBindingsBase(
		Scene,
		View,
		Shader,
		InputStreamType,
		FeatureLevel,
		VertexFactory,
		BatchElement,
		VertexFactoryUniformBuffer,
		ShaderBindings,
		VertexStreams);
}
