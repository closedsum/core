// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"

#include "CsData_Interaction_Select_VisualMaterial.generated.h"

class UMaterialInterface;

namespace NCsInteraction
{
	namespace NData
	{
		namespace NSelect
		{
			namespace NVisual
			{
				namespace NMaterial
				{
					struct CSINTERACTIVE_API IMaterial
					{
					public:

						static const FName Name;

					public:

						virtual ~IMaterial(){}

						virtual const TArray<UMaterialInterface*>& GetSelectMaterials() const = 0;
					};
				}
			}
		}
	}
}

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSINTERACTIVE_API UCsData_Interaction_Select_VisualMaterial : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class UMaterialInterface;

class CSINTERACTIVE_API ICsData_Interaction_Select_VisualMaterial
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual const TArray<UMaterialInterface*>& GetSelectMaterials() const = 0;
};