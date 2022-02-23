// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Mesh/CsStaticMeshAttachment.h"

#include "CsData_Skin_VisualStaticMesh_Attachment.generated.h"

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NStaticMesh
			{
				namespace NAttachment
				{
					/**
					* Interface of a Skin having Static Mesh attachments.
					*/
					struct CSCORE_API IAttachment : public ICsGetInterfaceMap
					{
					public:

						static const FName Name;


					public:

						virtual ~IAttachment() {}

					#define AttachmentType NCsStaticMesh::NAttachment::FAttachment

						/**
						* Get the Static Mesh attachments.
						* 
						* return
						*/
						virtual const TArray<AttachmentType>& GetStaticMeshAttachments() const = 0;

					#undef AttachmentType
					};
				}
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_Skin_VisualStaticMesh_Attachment : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class UStaticMesh;

/**
* Interface of a Skin having Static Mesh attachments.
*/
class CSCORE_API ICsData_Skin_VisualStaticMesh_Attachment : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

#define AttachmentType NCsStaticMesh::NAttachment::FAttachment

	/**
	* Get the Static Mesh attachments.
	* 
	* return
	*/
	virtual const TArray<AttachmentType>& GetStaticMeshAttachments() const = 0;

#undef AttachmentType
};