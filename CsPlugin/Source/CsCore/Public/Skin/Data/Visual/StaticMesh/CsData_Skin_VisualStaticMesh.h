// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
				struct CSCORE_API IStaticMesh : public ICsGetInterfaceMap
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

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_Skin_VisualStaticMesh : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class UStaticMesh;

/**
* Interface of a Skin using a Static Mesh as a visual representation.
*/
class CSCORE_API ICsData_Skin_VisualStaticMesh : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual UStaticMesh* GetStaticMesh() const = 0;
};