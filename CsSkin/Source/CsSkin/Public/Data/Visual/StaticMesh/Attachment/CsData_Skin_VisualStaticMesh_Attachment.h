// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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
					struct CSSKIN_API IAttachment : public ICsGetInterfaceMap
					{
					public:

						static const FName Name;

					public:

						virtual ~IAttachment() {}

					private:

						// Allow clearer names without name collisions
						struct _
						{
							using AttachmentType = NCsStaticMesh::NAttachment::FAttachment;
						};

					public:

						/**
						* Get the Static Mesh attachments.
						* 
						* return
						*/
						virtual const TArray<_::AttachmentType>& GetStaticMeshAttachments() const = 0;
					};
				}
			}
		}
	}
}

using CsStaticMeshAttachmentSkinDataType = NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment;

UINTERFACE(BlueprintType)
class CSSKIN_API UCsData_Skin_VisualStaticMesh_Attachment : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class UStaticMesh;

/**
* Interface of a Skin having Static Mesh attachments.
*/
class CSSKIN_API ICsData_Skin_VisualStaticMesh_Attachment : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

private:

	// Allow clearer names without name collisions
	struct _
	{
		using AttachmentType = NCsStaticMesh::NAttachment::FAttachment;
	};

public:

	/**
	* Get the Static Mesh attachments.
	* 
	* return
	*/
	virtual const TArray<_::AttachmentType>& GetStaticMeshAttachments() const = 0;
};