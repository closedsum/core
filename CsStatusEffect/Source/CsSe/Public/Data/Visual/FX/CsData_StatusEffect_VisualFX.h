// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/FX/CsTypes_FX.h"

#include "CsData_StatusEffect_VisualFX.generated.h"

namespace NCsStatusEffect
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NFX
			{
				/**
				*/
				struct CSSE_API IFX : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IFX(){}

					virtual const FCsFX& GetFX() const = 0;
				};
			}
		}
	}
}

UINTERFACE(Blueprintable)
class CSSE_API UCsData_StatusEffect_VisualFX : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSSE_API ICsData_StatusEffect_VisualFX : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

	virtual const FCsFX& GetFX() const = 0;
};