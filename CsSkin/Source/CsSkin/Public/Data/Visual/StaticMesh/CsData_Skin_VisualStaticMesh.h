// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_StaticMesh.h"

#include "CsData_Skin_VisualStaticMesh.generated.h"

class UStaticMesh;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NStaticMesh
			{
				/**
				* Interface of a Skin using a Static Mesh as a visual representation.
				*/
				struct CSSKIN_API IStaticMesh : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IStaticMesh() {}

					/**
					*/
					virtual UStaticMesh* GetStaticMesh() const = 0;
				};
			}
		}
	}
}

using CsStaticMeshSkinDataType = NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh;

UINTERFACE(BlueprintType)
class CSSKIN_API UCsData_Skin_VisualStaticMesh : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class UStaticMesh;

/**
* Interface of a Skin using a Static Mesh as a visual representation.
*/
class CSSKIN_API ICsData_Skin_VisualStaticMesh : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual UStaticMesh* GetStaticMesh() const = 0;
};