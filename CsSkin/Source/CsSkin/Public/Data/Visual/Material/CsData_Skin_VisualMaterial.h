// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

// Interfaces
#include "Containers/CsGetInterfaceMap.h"

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
				struct CSSKIN_API IMaterial : public ICsGetInterfaceMap
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

using CsMaterialSkinDataType = NCsSkin::NData::NVisual::NMaterial::IMaterial;

UINTERFACE(BlueprintType)
class CSSKIN_API UCsData_Skin_VisualMaterial : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class UMaterialInterface;

/**
*
*/
class CSSKIN_API ICsData_Skin_VisualMaterial : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual const TArray<UMaterialInterface*>& GetMaterials() const = 0;
};