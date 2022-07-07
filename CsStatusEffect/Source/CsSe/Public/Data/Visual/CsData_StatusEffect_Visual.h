// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_StatusEffect_Visual.generated.h"

namespace NCsStatusEffect
{
	namespace NData
	{
		namespace NVisual
		{
			/**
			*/
			struct CSSE_API IVisual : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IVisual(){}
			};
		}
	}
}

UINTERFACE(Blueprintable)
class CSSE_API UCsData_StatusEffect_Visual : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSSE_API ICsData_StatusEffect_Visual : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;
};