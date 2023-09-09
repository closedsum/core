// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "ShaderParameters.h"
#include "VertexFactory.h"

class FMaterial;
class FSceneView;
struct FMeshBatchElement;

/**
 * Shader parameters for all LocalVertexFactory derived classes.
 */
class CSCORE_API FCsLocalVertexFactoryShaderParametersBase : public FVertexFactoryShaderParameters
{
	DECLARE_TYPE_LAYOUT(FCsLocalVertexFactoryShaderParametersBase, NonVirtual);
public:
	void Bind(const FShaderParameterMap& ParameterMap);

	void GetElementShaderBindingsBase(
		const class FSceneInterface* Scene,
		const FSceneView* View,
		const FMeshMaterialShader* Shader,
		const EVertexInputStreamType InputStreamType,
		ERHIFeatureLevel::Type FeatureLevel,
		const FVertexFactory* VertexFactory,
		const FMeshBatchElement& BatchElement,
		FRHIUniformBuffer* VertexFactoryUniformBuffer,
		FMeshDrawSingleShaderBindings& ShaderBindings,
		FVertexInputStreamArray& VertexStreams
		) const;

	FCsLocalVertexFactoryShaderParametersBase()
		: bAnySpeedTreeParamIsBound(false)
	{
	}

	// SpeedTree LOD parameter
	LAYOUT_FIELD(FShaderParameter, LODParameter);

	// True if LODParameter is bound, which puts us on the slow path in GetElementShaderBindings
	LAYOUT_FIELD(bool, bAnySpeedTreeParamIsBound);
};

/** Shader parameter class used by FLocalVertexFactory only - no derived classes. */
class CSCORE_API FCsLocalVertexFactoryShaderParameters : public FCsLocalVertexFactoryShaderParametersBase
{
	DECLARE_TYPE_LAYOUT(FCsLocalVertexFactoryShaderParameters, NonVirtual);
public:
	void GetElementShaderBindings(
		const FSceneInterface* Scene,
		const FSceneView* View,
		const FMeshMaterialShader* Shader,
		const EVertexInputStreamType InputStreamType,
		ERHIFeatureLevel::Type FeatureLevel,
		const FVertexFactory* VertexFactory,
		const FMeshBatchElement& BatchElement,
		FMeshDrawSingleShaderBindings& ShaderBindings,
		FVertexInputStreamArray& VertexStreams
	) const; 
};