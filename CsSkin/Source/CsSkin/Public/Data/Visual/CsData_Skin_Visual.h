// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

// Interfaces
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_Skin_Visual.generated.h"

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			/**
			*
			*/
			struct CSSKIN_API IVisual : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IVisual(){}
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSSKIN_API UCsData_Skin_Visual : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSSKIN_API ICsData_Skin_Visual : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
};