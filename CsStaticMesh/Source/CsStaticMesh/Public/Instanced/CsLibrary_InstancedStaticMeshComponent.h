// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"

class UInstancedStaticMeshComponent;

namespace NCsStaticMesh
{
	namespace NInstanced
	{
		namespace NComponent
		{
			/**
			* Library of function related to InstancedStaticMeshComponent
			*/
			class CSSTATICMESH_API FLibrary final
			{
			public:

				static void InitRenderDataChecked(const FString& Context, UInstancedStaticMeshComponent* Component, const int32& NumInstances, const int32& NumCustomDataFloats);

				struct FUpdateRenderDataChecked
				{
				public:

					struct FPayload
					{
					public:

						UInstancedStaticMeshComponent* Component;

						int32 NumInstances;

						int32 NumCustomDataFloats;

						TArray<FMatrix44f>* Transforms;

						TArray<float>* CustomDatas;

						FPayload() :
							Component(nullptr),
							NumInstances(0),
							NumCustomDataFloats(0),
							Transforms(nullptr),
							CustomDatas(nullptr)
						{
						}

						FORCEINLINE UInstancedStaticMeshComponent* GetComponent() const { return Component; }
						FORCEINLINE const int32& GetNumInstances() const { return NumInstances; }
						FORCEINLINE const int32& GetNumCustomDataFloats() const { return NumCustomDataFloats; }
						FORCEINLINE const TArray<FMatrix44f>& GetTransforms() const { return *Transforms; }
						FORCEINLINE const TArray<float>& GetCustomDatas() const { return *CustomDatas; }

						bool IsValidChecked(const FString& Context) const;
					};
				};

				using PayloadType = NCsStaticMesh::NInstanced::NComponent::FLibrary::FUpdateRenderDataChecked::FPayload;

				static void UpdateRenderDataChecked(const FString& Context, const PayloadType& Payload);
			};
		}
	}
}