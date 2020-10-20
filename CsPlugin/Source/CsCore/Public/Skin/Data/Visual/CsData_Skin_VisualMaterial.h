// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Material.h"

#include "CsData_Skin_VisualMaterial.generated.h"

class UMaterialInterface;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NMaterial
			{
				/**
				*
				*/
				struct CSCORE_API IMaterial : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IMaterial() {}

					/**
					*/
					virtual const TArray<UMaterialInterface*>& GetMaterials() const = 0;
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_Skin_VisualMaterial : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class UMaterialInterface;

/**
*
*/
class CSCORE_API ICsData_Skin_VisualMaterial : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual const TArray<UMaterialInterface*>& GetMaterials() const = 0;
};