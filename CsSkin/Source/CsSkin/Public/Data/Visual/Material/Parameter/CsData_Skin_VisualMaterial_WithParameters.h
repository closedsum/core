// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Material/CsTypes_Material.h"

#include "CsData_Skin_VisualMaterial_WithParameters.generated.h"

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NMaterial
			{
				namespace NWithParameters
				{
					/**
					*
					*/
					struct CSSKIN_API IWithParameters : public ICsGetInterfaceMap
					{
					public:

						static const FName Name;

					public:

						virtual ~IWithParameters() {}

					#define MaterialType NCsMaterial::NInterface::FWithRangeParameters

						/**
						*/
						virtual const TArray<MaterialType>& GetMaterials() const = 0;

					#undef MaterialType
					};
				}
			}
		}
	}
}

using CsMaterialWithParamsSkinDataType = NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters;

UINTERFACE(BlueprintType)
class CSSKIN_API UCsData_Skin_VisualMaterial_WithParameters : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSSKIN_API ICsData_Skin_VisualMaterial_WithParameters : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

#define MaterialType NCsMaterial::NInterface::FWithRangeParameters

	/**
	*/
	virtual const TArray<MaterialType>& GetMaterials() const = 0;

#undef MaterialType
};