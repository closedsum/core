// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Mesh/CsStaticMeshAttachment.h"

struct FCsStaticMeshActorPooled;
class USceneComponent;

namespace NCsStaticMesh
{
	namespace NActor
	{
		namespace NPooled
		{
			struct CSSTATICMESH_API FLibrary final
			{
			public:

				static FCsStaticMeshActorPooled* AttachChecked(const FString& Context, const FCsStaticMeshAttachment& Attachment, const UObject* WorldContext, USceneComponent* Parent);

			#define AttachmentType NCsStaticMesh::NAttachment::FAttachment

				static FCsStaticMeshActorPooled* AttachChecked(const FString& Context, const AttachmentType& Attachment, const UObject* WorldContext, USceneComponent* Parent, const TArray<UMaterialInterface*>& OtherMaterials);
				static FCsStaticMeshActorPooled* AttachChecked(const FString& Context, const AttachmentType& Attachment, const UObject* WorldContext, USceneComponent* Parent);

			#undef AttachmentType
			};
		}
	}
}