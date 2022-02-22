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
					* Interface of a Skin using a Static Mesh as a visual representation.
					*/
					struct CSCORE_API IAttachment : public ICsGetInterfaceMap
					{
					public:

						static const FName Name;

					public:

						virtual ~IAttachment() {}

						/**
						*/
						//virtual UStaticMesh* GetStaticMesh() const = 0;
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
* Interface of a Skin using a Static Mesh as a visual representation.
*/
class CSCORE_API ICsData_Skin_VisualStaticMesh_Attachment : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	//virtual UStaticMesh* GetStaticMesh() const = 0;
};