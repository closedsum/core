// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

// Interfaces
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_Skin_VisualMaterial_ParameterCollection.generated.h"

class UMaterialParameterCollection;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NMaterial
			{
				namespace NParameter
				{
					namespace NCollection
					{
						/**
						*
						*/
						struct CSSKIN_API ICollection : public ICsGetInterfaceMap
						{
						public:

							static const FName Name;

						public:

							virtual ~ICollection() {}

							/**
							*/
							virtual UMaterialParameterCollection* GetMaterialParameterCollection() const = 0;
						};
					}
				}
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSSKIN_API UCsData_Skin_VisualMaterial_ParameterCollection : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class UMaterialParameterCollection;

/**
*
*/
class CSSKIN_API ICsData_Skin_VisualMaterial_ParameterCollection : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual UMaterialParameterCollection* GetMaterialParameterCollection() const = 0;
};