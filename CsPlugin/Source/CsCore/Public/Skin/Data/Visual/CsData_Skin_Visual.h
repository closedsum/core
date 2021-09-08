// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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
			struct CSCORE_API IVisual : public ICsGetInterfaceMap
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
class CSCORE_API UCsData_Skin_Visual : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSCORE_API ICsData_Skin_Visual : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
};